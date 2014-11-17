///<------------------------------------------------------------------------------
//< @文件名：c++_generator.cpp
//< @作　者：洪坤安
//< @日　期: 2014年11月12日 19:06:42
//< @摘　要: 生成c++文件
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

// c++_generator
package cpp

import (
	"strings"
	"tokit/generator"
	"tokit/tool"
)

var g_cpp_types = [generator.Fieldtype_max + 1]string{"", "std::string", "bool", "char", "int16", "int32", "int64", "uint8", "uint16", "uint32", "uint64", "float", "double"}

type enum_get_c_field_option uint8

const (
	gcfo_with_namespace    = 0 // 指定作用域
	gcfo_without_namespace = 1 // 不指定作用域
)

type Cpp_generator struct {
	M_cfgbase *generator.Cfgbase_t

	M_to_dir           string /* 生成的c++文件目录 */
	M_h_templet_path   string /* 用于生成.h的模板文件 */
	M_cpp_templet_path string /* 用于生成.cpp的模板文件 */
}

func (c *Cpp_generator) Generate() {
    if false == tool.Exist(&c.M_to_dir) {
        tool.EchoErr("参数错误: 找不到指定的生成源文件的路径<%s>，请确认路径是否存在!", c.M_to_dir);
        return
    }

    if false == tool.Exist(&c.M_h_templet_path) {
        tool.EchoErr("参数错误: 找不到.h模板头文件<%s>", c.M_h_templet_path);
        return
    }

    if(false == tool.Exist(&c.M_cpp_templet_path)){
        tool.EchoErr("参数错误: 找不到cpp模板源文件<%s>", c.M_cpp_templet_path);
        return
    }

	var filename string = tool.Strip_ext(tool.Strip_dir(c.M_cfgbase.Filename))

    var h_file string = c.M_to_dir + "\\" + filename + ".h"
    var cpp_file string = c.M_to_dir + "\\" + filename + ".cpp"

    // 开始生成
    // 1. c++的h头文件
    if !c.gen_h_file(&h_file) {
        tool.EchoErr("生成h头文件<%s>失败", h_file);
        return
    }

    tool.EchoOk("生成h头文件<%s>成功", h_file);

    // 2. c++的cpp头文件
    if !c.gen_cpp_file(&cpp_file){
        tool.EchoErr("生成cpp源文件<%s>失败", cpp_file);
        return
    }

    tool.EchoOk("生成cpp源文件<%s>成功", cpp_file);
}

// 将excel文件中的每个工作表对应生成的文本串拼接起来
func splice(cfgbase *generator.Cfgbase_t, f func(*generator.Cfg_t) string, splice_token string) string {
	// 将调用func产生的文本拼接起来
	var text string
	var n_cfg int = len(cfgbase.Cfgs)

	for n, v := range cfgbase.Cfgs {
		var each_cfg_text string = f(&v)

		if each_cfg_text == "" {
			continue
		}

		text += each_cfg_text

		if n+1 < n_cfg {
			text += splice_token
		}
	}

	return text
}

func clear_scope(cfg *generator.Cfg_t, f func(*generator.Cfg_t) string, prefix string, postfix string) string {
	var stmt string = f(cfg)
	if stmt == "" {
		return ""
	}

	// 清除掉对象域声明
	stmt = strings.Replace(stmt, "%mgr%::", "", -1)
	return prefix + stmt + postfix
}

func get_field_c_typedef_type(cfg *generator.Cfg_t, field *generator.Field_t, c_type enum_get_c_field_option) string {
	var ret string

	if field.Fieldattr != generator.Fieldattr_none {
		var typedef_type string

		switch {
		case field.Is_array():
			typedef_type = field.En_name + "vec_t"
		case field.Is_set():
			typedef_type = field.En_name + "set_t"
		default:
			typedef_type = field.En_name + "_t"
		}

		// 检测是否需要指定作用域
		if gcfo_without_namespace == c_type {
			ret = typedef_type
		} else {
			ret = get_cfg_type_name(cfg) + "::" + typedef_type
		}
	} else {
		ret = g_cpp_types[field.Fieldtype]
	}

	return ret
}

func get_field_c_type(field *generator.Field_t) string {
	var text string
	var c_type *string = &g_cpp_types[field.Fieldtype]

	switch {
	case field.Is_array():
		text = "std::vector<%type%>"
		text = strings.Replace(text, "%type%", *c_type, -1)
	case field.Is_set():
		text = "std::set<%type%>"
		text = strings.Replace(text, "%type%", *c_type, -1)
	default:
		text = *c_type
	}

	return text
}

func get_field_parameter_c_type(cfg *generator.Cfg_t, field *generator.Field_t) string {
	var paramtype string = "const char*"
	if field.Fieldtype != generator.Fieldtype_string {
		paramtype = get_field_c_typedef_type(cfg, field, gcfo_with_namespace)
	}

	return paramtype
}

func get_n_key_map_name(cfg *generator.Cfg_t) string {
	return cfg.En_name + "map"
}

func get_1_key_map_name(cfg *generator.Cfg_t, field *generator.Field_t) string {
	return field.En_name + "2" + cfg.En_name + "map"
}

func get_vec_name(cfg *generator.Cfg_t) string {
	return cfg.En_name + "vec"
}

func get_mgr_name(cfgbase *generator.Cfgbase_t) string {
	return cfgbase.Filename + "mgr"
}

func get_comment(cfg *generator.Cfg_t) string {
	return "// " + cfg.Cn_name
}

func get_cfg_type_name(cfg *generator.Cfg_t) string {
	return cfg.En_name + "_t"
}

func get_load_func_declare(cfg *generator.Cfg_t) string {
	var text string = "bool %mgr%::load_%cfg%()"
	text = strings.Replace(text, "%cfg%", cfg.En_name, -1)
	return text
}

func get_clear_func_name(cfg *generator.Cfg_t) string {
	var text string = "clear_%cfg%"
	text = strings.Replace(text, "%cfg%", cfg.En_name, -1)
	return text
}

func get_clear_func_declare(cfg *generator.Cfg_t) string {
	var text string = "void %mgr%::%clear_func_name%()"
	text = strings.Replace(text, "%clear_func_name%", get_clear_func_name(cfg), -1)
	return text
}

func get_n_key_find_func_declare(cfg *generator.Cfg_t) string {
	var n_key int = len(cfg.Keys)
	if n_key <= 1 {
		return ""
	}

	// 拼接出函数参数，比如 = int id, int lvl
	var key string

	for n, v := range cfg.Keys {
		var field *generator.Field_t = &cfg.Fields[v]

		var paramtype string = get_field_parameter_c_type(cfg, field)
		key += paramtype + " " + field.En_name

		if n+1 < n_key {
			key += ", "
		}
	}

	var text string = "const %cfgtype%* %mgr%::get_%cfg%(%key%)"

	text = strings.Replace(text, "%cfg%", cfg.En_name, -1)
	text = strings.Replace(text, "%cfgtype%", get_cfg_type_name(cfg), -1)
	text = strings.Replace(text, "%key%", key, -1)
	return text
}

func get_1_key_find_func_declare_list(cfg *generator.Cfg_t) string {
	var text string

	for _, v := range cfg.Fields {
		var field_find_func string = get_1_key_find_func_declare(cfg, &v)
		if field_find_func != "" {
			text += "    " + field_find_func + ";\n"
		}
	}
	return text
}

func get_1_key_find_func_declare(cfg *generator.Cfg_t, field *generator.Field_t) string {
	if !field.Is_1_key() || field.Is_n_key() {
		return ""
	}

	var text string = "const %cfgtype%* %mgr%::get_%cfg%_by_%key_name%(%key%)"

	var key string = get_field_parameter_c_type(cfg, field) + " " + field.En_name
	text = strings.Replace(text, "%key%", key, -1)
	text = strings.Replace(text, "%key_name%", field.En_name, -1)
	text = strings.Replace(text, "%cfg%", cfg.En_name, -1)
	text = strings.Replace(text, "%cfgtype%", get_cfg_type_name(cfg), -1)
	return text
}

func get_member_comment_list(cfgbase *generator.Cfgbase_t) string {
	var text string
	var n_cfg int = len(cfgbase.Cfgs)

	for n, v := range cfgbase.Cfgs {
		text += v.Cn_name

		if n+1 < n_cfg {
			text += ", "
		}
	}

	return text
}
