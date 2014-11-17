///<------------------------------------------------------------------------------
//< @文件名：gen_h.cpp
//< @作　者：洪坤安
//< @日　期: 2014年11月13日 16:43:42
//< @摘　要: 生成c++的头文件
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

// gen_h
package cpp

import (
	"fmt"
	"strings"
	"tokit/generator"
	"tokit/tool"
	"mahonia"
)

var g_field_attr_describe = [generator.Fieldattr_max + 1]string{"", "<<<主键>>>", "<<<唯一>>>", "<<<数组>>>", "<<<集合>>>"}

func gen_struct(cfg *generator.Cfg_t) string {
	var text string = `// %comment%
struct %cfgtype%{
%typedef%
	%cfgtype%();

	std::string print() const;

%fields%};
`

	var typedef_text string
	for _, v := range cfg.Fields {
		if v.Fieldattr == generator.Fieldattr_none {
			continue
		}

		typedef_text += fmt.Sprintf("	typedef %s %s; // %s%s\n",
			get_field_c_type(&v), get_field_c_typedef_type(cfg, &v, gcfo_without_namespace), v.Comment, g_field_attr_describe[v.Fieldattr])
	}

	var fields_text string
	for _, v := range cfg.Fields {
		var c_type string = get_field_c_typedef_type(cfg, &v, gcfo_without_namespace)
		fields_text += fmt.Sprintf("	%s %s; // %s%s\n", c_type, v.En_name, v.Comment, g_field_attr_describe[v.Fieldattr])
	}

	text = strings.Replace(text, "%comment%", cfg.Cn_name, -1)
	text = strings.Replace(text, "%cfgtype%", get_cfg_type_name(cfg), -1)
	text = strings.Replace(text, "%typedef%", typedef_text, -1)
	text = strings.Replace(text, "%fields%", fields_text, -1)
	return text
}

func gen_mgr_n_key_map_typedef(cfg *generator.Cfg_t) string {
	var n_key int = len(cfg.Keys)
	if n_key <= 1 {
		return ""
	}

	var is_key_has_str bool = false

	for _, v := range cfg.Keys {
		var key *generator.Field_t = &cfg.Fields[v]

		if key.Fieldtype == generator.Fieldtype_string {
			is_key_has_str = true
			break
		}
	}

	var text string

	if is_key_has_str {
		text = "	typedef std::map<std::string, %cfg%*> %map%;\n"
	} else {
		text = "	typedef std::map<uint64_t, %cfg%*> %map%;\n"
	}

	text = strings.Replace(text, "%cfg%", get_cfg_type_name(cfg), -1)
	text = strings.Replace(text, "%map%", get_n_key_map_name(cfg), -1)
	return text
}

func gen_mgr_1_key_map_typedef(cfg *generator.Cfg_t) string {
	var text string = ""

	for _, v := range cfg.Fields {
		if !v.Is_1_key() {
			continue
		}

		var map_text string = "	typedef std::map<%key%, %cfg%*> %map%; // %field_cn_name% -> %cfg%\n"
		map_text = strings.Replace(map_text, "%key%", get_field_c_typedef_type(cfg, &v, gcfo_with_namespace), -1)
		map_text = strings.Replace(map_text, "%map%", get_1_key_map_name(cfg, &v), -1)
		map_text = strings.Replace(map_text, "%field_cn_name%", v.Cn_name, -1)

		text += map_text
	}

	text = strings.Replace(text, "%cfg%", get_cfg_type_name(cfg), -1)
	return text
}

func gen_mgr_vec_typedef(cfg *generator.Cfg_t) string {
	var text string = "	typedef std::vector<%cfg%> %vec%;\n"
	text = strings.Replace(text, "%cfg%", get_cfg_type_name(cfg), -1)
	text = strings.Replace(text, "%vec%", get_vec_name(cfg), -1)
	return text
}

func gen_mgr_typedef(cfg *generator.Cfg_t) string {
	if cfg.Only_has_1_row() {
		return ""
	}

	var text string
	text += "	" + get_comment(cfg) + "\n"
	text += gen_mgr_n_key_map_typedef(cfg)
	text += gen_mgr_1_key_map_typedef(cfg)
	text += gen_mgr_vec_typedef(cfg)

	if text != "" {
		text = text[0 : len(text)-1]
	}

	return text
}

func gen_mgr_load_func(cfg *generator.Cfg_t) string {
	var text string = clear_scope(cfg, get_load_func_declare, "	", ";")
	return text
}

func gen_mgr_clear_func(cfg *generator.Cfg_t) string {
	var text string = clear_scope(cfg, get_clear_func_declare, "	", ";")
	return text
}

func gen_mgr_n_key_find_func(cfg *generator.Cfg_t) string {
	var text string = clear_scope(cfg, get_n_key_find_func_declare, "	", ";\n")
	return text
}

func gen_mgr_1_key_find_func(cfg *generator.Cfg_t) string {
	var text string = clear_scope(cfg, get_1_key_find_func_declare_list, "", "")
	return text
}

func gen_mgr_find_func(cfg *generator.Cfg_t) string {
	if cfg.Only_has_1_row() {
		return ""
	}

	var text string
	text += "	" + get_comment(cfg) + "\n"
	text += gen_mgr_n_key_find_func(cfg)
	text += gen_mgr_1_key_find_func(cfg)

	if text != "" {
		text = text[0 : len(text)-1]
	}

	return text
}

type namevec_t []string

func gen_mgr_get_member_func(cfg *generator.Cfg_t) string {
	var member_text string = "	const %member_type%& get_%member%(){ return m_%member%; }\n"
	var text string
	var membernamevec namevec_t

	if cfg.Only_has_1_row() {
		text += member_text

		text = strings.Replace(text, "%member%", cfg.En_name, -1)
		text = strings.Replace(text, "%member_type%", get_cfg_type_name(cfg), -1)
	} else {

		var n_key int = len(cfg.Keys)
		if n_key > 1 {
			membernamevec = append(membernamevec, get_n_key_map_name(cfg))
		}

		for _, v := range cfg.Fields {
			if !v.Is_1_key() {
				continue
			}

			membernamevec = append(membernamevec, get_1_key_map_name(cfg, &v))
		}

		membernamevec = append(membernamevec, get_vec_name(cfg))
	}

	for _, v := range membernamevec {
		var member_name string = v
		var member_stmt string = member_text

		member_stmt = strings.Replace(member_stmt, "%member%", member_name, -1)
		member_stmt = strings.Replace(member_stmt, "%member_type%", member_name, -1)
		text += member_stmt
	}

	if text != "" {
		text = text[0 : len(text)-1]
	}

	return text
}

func gen_mgr_get_func(cfg *generator.Cfg_t) string {
	return gen_mgr_find_func(cfg) + "\n" + gen_mgr_get_member_func(cfg)
}

func gen_mgr_n_key_member(cfg *generator.Cfg_t) string {
	if cfg.Only_has_1_row() {
		return ""
	}

	var n_key int = len(cfg.Keys)
	if n_key <= 1 {
		return ""
	}

	var text string = "	%map% m_%map%;\n"
	text = strings.Replace(text, "%map%", get_n_key_map_name(cfg), -1)
	return text
}

func gen_mgr_1_key_member(cfg *generator.Cfg_t) string {
	if cfg.Only_has_1_row() {
		return ""
	}

	var text string = ""

	for _, v := range cfg.Fields {
		if !v.Is_1_key() || v.Is_n_key() {
			continue
		}

		var member_text string = "	%map% m_%map%; // %field_cn_name% -> %cfg%\n"

		member_text = strings.Replace(member_text, "%map%", get_1_key_map_name(cfg, &v), -1)
		member_text = strings.Replace(member_text, "%field_cn_name%", v.Cn_name, -1)
		text += member_text
	}

	text = strings.Replace(text, "%cfg%", cfg.En_name, -1)
	return text
}

func gen_mgr_vec_member(cfg *generator.Cfg_t) string {
	if cfg.Only_has_1_row() {
		return ""
	}

	var text string = "	%vec% m_%vec%;\n"
	text = strings.Replace(text, "%vec%", get_vec_name(cfg), -1)
	return text
}

func gen_mgr_alone_member(cfg *generator.Cfg_t) string {
	if !cfg.Only_has_1_row() {
		return ""
	}

	var text string = "	%cfgtype% m_%cfg%;\n"
	text = strings.Replace(text, "%cfgtype%", get_cfg_type_name(cfg), -1)
	text = strings.Replace(text, "%cfg%", cfg.En_name, -1)
	return text
}

func gen_mgr_members(cfg *generator.Cfg_t) string {
	var text string
	text += "	" + get_comment(cfg) + "\n"
	text += gen_mgr_n_key_member(cfg)
	text += gen_mgr_1_key_member(cfg)
	text += gen_mgr_vec_member(cfg)
	text += gen_mgr_alone_member(cfg)

	if text != "" {
		text = text[0 : len(text)-1]
	}

	return text
}

func (c *Cpp_generator) gen_h_file(h_file *string) bool {
	// 取出h模板文件的内容
	var text string
	tool.GetFileText(&c.M_h_templet_path, &text)

	if text == "" {
		tool.EchoErr("生成c++文件失败：找不到模板文件<%s>", c.M_h_templet_path)
		return false
	}

	text = strings.Replace(text, "%cfg%", c.M_cfgbase.Filename, -1)

	// 1. 定义配置数据结构体
	text = strings.Replace(text, "%structs%", splice(c.M_cfgbase, gen_struct, "\n"), -1)

	// 2. 开始实现mgr管理器，该mgr将提供载入、清空和查找接口
	text = strings.Replace(text, "%typedefs%", splice(c.M_cfgbase, gen_mgr_typedef, "\n\n"), -1)
	text = strings.Replace(text, "%load_funcs%", splice(c.M_cfgbase, gen_mgr_load_func, "\n"), -1)
	text = strings.Replace(text, "%clear_funcs%", splice(c.M_cfgbase, gen_mgr_clear_func, "\n"), -1)
	text = strings.Replace(text, "%get_funcs%", splice(c.M_cfgbase, gen_mgr_get_func, "\n\n"), -1)
	text = strings.Replace(text, "%members%", splice(c.M_cfgbase, gen_mgr_members, "\n\n"), -1)
	text = strings.Replace(text, "%cfg_member%", get_member_comment_list(c.M_cfgbase), -1)
	text = strings.Replace(text, "%mgr%", get_mgr_name(c.M_cfgbase), -1)

	enc := mahonia.NewEncoder("GB18030")
    if ret, ok := enc.ConvertStringOK(text); ok {
        // fmt.Println("UTF-8 to GBK: ", ret, " bytes: ", []byte(ret))		
		text = string(ret)
    }

	var is_overwrite_file_ok bool = tool.OverWriteFile(h_file, &text)
	return is_overwrite_file_ok
}
