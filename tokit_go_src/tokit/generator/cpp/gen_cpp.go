///<------------------------------------------------------------------------------
//< @文件名：gen_cpp.cpp
//< @作　者：洪坤安
//< @日　期: 2014年11月13日 16:43:42
//< @摘　要: 生成c++的cpp文件
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

// gen_cpp
package cpp

import (
	"strings"
	"tokit/generator"
	"tokit/tool"
	"mahonia"
)

var g_printf_format = [generator.Fieldtype_max + 1]string{"", "%s", "%u", "%d", "%d", "%d", "\"I64d\"", "%u", "%u", "%u", "\"I64u\"", "%f", "%lf"}

// 生成结构体的构造函数
func gen_struct_ctor(cfg *generator.Cfg_t) string {
	var ctor_text string = "%cfg%::%cfg%()"

	ctor_text = strings.Replace(ctor_text, "%cfg%", get_cfg_type_name(cfg), -1)

	for n, v := range cfg.Fields {
		if v.Is_array() || v.Is_set() {
			continue
		}

		if n > 0 {
			ctor_text += "\n    , "
		} else {
			ctor_text += "\n    : "
		}

		if v.Fieldtype == generator.Fieldtype_string {
			ctor_text += v.En_name + "(\"\")"
		} else {
			ctor_text += v.En_name + "(0)"
		}
	}

	ctor_text += "\n{\n}"
	return ctor_text
}

// 生成结构体的构造函数
func gen_struct_print(cfg *generator.Cfg_t) string {
	var print_text string = "std::string %cfg%::print() const\n{%print%\n}"

	print_text = strings.Replace(print_text, "%cfg%", get_cfg_type_name(cfg), -1)

	var printf_fmt string
	var printf_argv string

	var n_fields int = len(cfg.Fields)
	for n, v := range cfg.Fields {
		if v.Is_array() || v.Is_set() {
			continue
		}

		printf_fmt += v.En_name + "=" + g_printf_format[v.Fieldtype]
		if n+1 < n_fields {
			printf_fmt += " "
		}

		if 0 == n%10 && n > 1 {
			printf_fmt += "\"\n        \""
		}

		printf_argv += "\n        , "

		if v.Fieldtype == generator.Fieldtype_string {
			printf_argv += v.En_name + ".c_str()"
		} else {
			printf_argv += v.En_name
		}
	}

	var print_stmt string

	if n_fields > 0 {
		print_stmt = "\n    char buf[2048];\n    snprintf(buf, sizeof(buf), \"%printf_fmt%\"%printf_argv%);\n\n    return buf;"

		print_stmt = strings.Replace(print_stmt, "%printf_fmt%", printf_fmt, -1)
		print_stmt = strings.Replace(print_stmt, "%printf_argv%", printf_argv, -1)
	}

	print_text = strings.Replace(print_text, "%print%", print_stmt, -1)
	return print_text
}

// 生成读取属性的语句
func gen_load_attr_statement(field *generator.Field_t) string {
	var g_load_attr_stmt = [generator.Fieldtype_max + 1]string{}
	g_load_attr_stmt[0] = ""
	g_load_attr_stmt[1] = "cfg.%field% = %cast%(%val%);"
	g_load_attr_stmt[2] = "cfg.%field% = (%val%[0] != '0');"
	g_load_attr_stmt[3] = "cfg.%field% = %cast%(%val%);"
	g_load_attr_stmt[4] = "cfg.%field% = %cast%(%val%);"
	g_load_attr_stmt[5] = "cfg.%field% = %cast%(%val%);"
	g_load_attr_stmt[6] = "cfg.%field% = %cast%(%val%);"
	g_load_attr_stmt[7] = "cfg.%field% = %cast%(%val%);"
	g_load_attr_stmt[8] = "cfg.%field% = %cast%(%val%);"
	g_load_attr_stmt[9] = "cfg.%field% = %cast%(%val%);"
	g_load_attr_stmt[10] = "cfg.%field% = %cast%(%val%);"
	g_load_attr_stmt[11] = "cfg.%field% = (float)%cast%(%val%);"
	g_load_attr_stmt[12] = "cfg.%field% = %cast%(%val%);"

	var g_cast_func_name = [generator.Fieldtype_max + 1]string{}
	g_cast_func_name[0] = ""
	g_cast_func_name[1] = "strtool::un_escape_xml"
	g_cast_func_name[2] = "strtool::str_to_bool"
	g_cast_func_name[3] = "strtool::str_to_int32"
	g_cast_func_name[4] = "strtool::str_to_int32"
	g_cast_func_name[5] = "strtool::str_to_int32"
	g_cast_func_name[6] = "strtool::str_to_int64"
	g_cast_func_name[7] = "strtool::str_to_uint32"
	g_cast_func_name[8] = "strtool::str_to_uint32"
	g_cast_func_name[9] = "strtool::str_to_uint32"
	g_cast_func_name[10] = "strtool::str_to_uint64"
	g_cast_func_name[11] = "atof"
	g_cast_func_name[12] = "atof"

	var static_load_vec_stmt string = "cfg.%field% = strtool::split_str_to_vec<%T%>(%val%, %cast%);"
	var static_load_set_stmt string = "cfg.%field% = strtool::split_str_to_set<%T%>(%val%, %cast%);"

	var static_load_str_vec_stmt string = "cfg.%field% = strtool::split(%val%);"
	var static_load_str_set_stmt string = "cfg.%field% = strtool::split_str_set(%val%);"

	var stmt string = g_load_attr_stmt[field.Fieldtype]
	if field.Is_array() {
		if field.Fieldtype == generator.Fieldtype_string {
			stmt = static_load_str_vec_stmt
		} else {
			stmt = static_load_vec_stmt
		}
	} else if field.Is_set() {
		if field.Fieldtype == generator.Fieldtype_string {
			stmt = static_load_str_set_stmt
		} else {
			stmt = static_load_set_stmt
		}
	}

	var val string = "node->first_attribute(\"%field%\")->value()"
	var cast_func *string = &g_cast_func_name[field.Fieldtype]
	stmt = strings.Replace(stmt, "%val%", val, -1)
	stmt = strings.Replace(stmt, "%field%", field.En_name, -1)
	stmt = strings.Replace(stmt, "%T%", g_cpp_types[field.Fieldtype], -1)
	stmt = strings.Replace(stmt, "%cast%", *cast_func, -1)
	return stmt
}

// 拼接字符串键值
// eg: string key = tostr(prop.type) + tostr(prop.id) + prop.name;
// eg: string key = tostr(prop.type) + prop.name;
// eg: string &key = prop.name;
func splice_str_key(keys *generator.Fieldvec_t) string {
	var ret string = "string key = "
	if len(*keys) == 1 {
		ret = "std::string &key = "
	} else {
		ret = "std::string key = "
	}

	for _, key := range *keys {
		if key.Fieldtype == generator.Fieldtype_string {
			ret += key.En_name
		} else {
			ret += "strtool::tostr(" + key.En_name + ")"
		}

		ret += " + "
	}

	ret = ret[0 : len(ret)-3]

	ret += ";"
	return ret
}

// splice the key string
// eg: string key = tostr(prop.type) + tostr(prop.id) + prop.name;
// eg: string key = tostr(prop.type) + prop.name;
// eg: string &key = prop.name;
func splice_int_key(keys generator.Fieldvec_t) string {
	var n_key int = len(keys)
	if n_key <= 1 {
		return ""
	}

	var ret string = ""
	switch n_key {
	// 2个主键
	case 2:
		ret = "uint64 key = keytool::Get3232Key("
		ret += keys[0].En_name
		ret += ", "
		ret += keys[1].En_name
		ret += ");"
		break

		// 3个主键
	case 3:
		ret = "uint64 key = keytool::Get161616Key("
		ret += keys[0].En_name
		ret += ", "
		ret += keys[1].En_name
		ret += ", "
		ret += keys[2].En_name
		ret += ");"
		break

	// 4个主键
	case 4:
		ret = "uint64 key = keytool::Get16161616Key("
		ret += keys[0].En_name
		ret += ", "
		ret += keys[1].En_name
		ret += ", "
		ret += keys[2].En_name
		ret += ", "
		ret += keys[3].En_name
		ret += ");"

		break
	}

	return ret
}

func splice_n_key(cfg *generator.Cfg_t, prefix string) string {
	var n_key int = len(cfg.Keys)
	if n_key <= 1 {
		return ""
	}

	var is_key_has_str bool = false

	for _, keyidx := range cfg.Keys {
		if cfg.Fields[keyidx].Fieldtype == generator.Fieldtype_string {
			is_key_has_str = true
			break
		}
	}

	var keys generator.Fieldvec_t
	for _, keyidx := range cfg.Keys {
		var key generator.Field_t = cfg.Fields[keyidx]

		key.En_name = prefix + key.En_name
		keys = append(keys, key)
	}

	var text string
	if is_key_has_str {
		text = splice_str_key(&keys)
	} else {
		text = splice_int_key(keys)
	}

	return text
}

func gen_n_key_map_insert_stmt(cfg *generator.Cfg_t) string {
	var n_key int = len(cfg.Keys)
	if n_key <= 1 {
		return ""
	}

	var keys generator.Fieldvec_t
	for _, v := range cfg.Keys {
		var key generator.Field_t = cfg.Fields[v] // 注意，这里进行了赋值拷贝

		key.En_name = "cfg." + key.En_name
		keys = append(keys, key)
	}

	var map_key string = "\n        " + splice_n_key(cfg, "cfg.")
	var map_insert string = "\n        m_%map%[key] = curcfg;\n"
	map_insert = strings.Replace(map_insert, "%map%", get_n_key_map_name(cfg), -1)

	return map_key + map_insert
}

func gen_1_key_map_insert_stmt(cfg *generator.Cfg_t) string {
	var text string

	for _, v := range cfg.Fields {
		if !v.Is_1_key() || v.Is_n_key() {
			continue
		}

		var insert_stmt string = "\n        m_%map%[cfg.%key%] = curcfg;"

		insert_stmt = strings.Replace(insert_stmt, "%map%", get_1_key_map_name(cfg, &v), -1)
		insert_stmt = strings.Replace(insert_stmt, "%key%", v.En_name, -1)
		text += insert_stmt
	}

	text = strings.Replace(text, "%cfg%", cfg.En_name, -1)
	return text
}

func gen_load_func(cfg *generator.Cfg_t) string {
	var text string = `
// %comment%
%load_func_name%
{
    tick_t load_tick;

    rapidxml::file<> fdoc(this->get_path("%cfg%.xml").c_str());
    rapidxml::xml_document<> doc;
    if(!fdoc.data()){
        std::cout << "err: load " << this->get_path("%cfg%.xml") << " failed, please check the file path" << std::endl;
        return false;
    }

    doc.parse<0>(fdoc.data());

    rapidxml::xml_node<>* root = doc.first_node();
    if(!root){
        std::cout << "err: parse <%cfg%.xml> failed, please check xml file format" << std::endl;
        return false;
    }

    clear_%cfg%();

    int n_row = 0;
    for(rapidxml::xml_node<> *node = root->first_node(); node; node = node->next_sibling()){
        ++n_row;
    }
%vec_reserve_stmt%
    %cfgtype% cfg;
    for(rapidxml::xml_node<> *node = root->first_node(); node; node = node->next_sibling()){
`

	var vec_reserve_stmt string
	if !cfg.Only_has_1_row() {
		vec_reserve_stmt = "\n    m_%vec%.reserve(n_row);\n"
	}

	text = strings.Replace(text, "%vec_reserve_stmt%", vec_reserve_stmt, -1)
	text = strings.Replace(text, "%cfg%", cfg.En_name, -1)
	text = strings.Replace(text, "%load_func_name%", get_load_func_declare(cfg), -1)
	text = strings.Replace(text, "%comment%", cfg.Cn_name, -1)
	text = strings.Replace(text, "%vec%", get_vec_name(cfg), -1)
	text = strings.Replace(text, "%cfgtype%", get_cfg_type_name(cfg), -1)

	var load_attr_stmt string

	var n_field int = len(cfg.Fields)
	for n, v := range cfg.Fields {
		load_attr_stmt = "        " + gen_load_attr_statement(&v) + "\n"
		if n*2+1 > n_field {
			load_attr_stmt = strings.Replace(load_attr_stmt, "node->first_attribute", "node->last_attribute", -1)
		}

		text += load_attr_stmt
	}

	if !cfg.Only_has_1_row() {
		var vec_push_stmt string = `
        m_%vec%.push_back(cfg);
        %cfgtype%* curcfg = &m_%vec%.back();`

		vec_push_stmt = strings.Replace(vec_push_stmt, "%vec%", get_vec_name(cfg), -1)
		vec_push_stmt = strings.Replace(vec_push_stmt, "%cfg%", cfg.En_name, -1)
		vec_push_stmt = strings.Replace(vec_push_stmt, "%cfgtype%", get_cfg_type_name(cfg), -1)

		var map_insert_stmt string = "\n    "
		map_insert_stmt += gen_n_key_map_insert_stmt(cfg)
		map_insert_stmt += gen_1_key_map_insert_stmt(cfg)

		text += vec_push_stmt
		text += map_insert_stmt
	} else {
		var eval_stmt string = `
                        m_%cfg% = cfg;
                        break;
				`

		eval_stmt = strings.Replace(eval_stmt, "%cfg%", cfg.En_name, -1)
		text += eval_stmt
	}

	var end_stmt string = `
    }

    printf("load <%-20s> success, cost time = <%-6f>s\n", "%cfg%.xml", load_tick.end_tick());
    return true;
}
`

	end_stmt = strings.Replace(end_stmt, "%cfg%", cfg.En_name, -1)
	text += end_stmt
	return text
}

func gen_call_load_func_stmt(cfg *generator.Cfg_t) string {
	return "    is_succ &= load_" + cfg.En_name + "();"
}

func gen_call_clear_func_stmt(cfg *generator.Cfg_t) string {
	var text string = "    " + get_clear_func_name(cfg) + "();"
	return text
}

func gen_clear_func(cfg *generator.Cfg_t) string {
	var text string = `%clear_func%
{%clear_stmt%
}
`

	var clear_stmt string

	if !cfg.Only_has_1_row() {
		clear_stmt += "\n    m_" + get_vec_name(cfg) + ".clear();"

		if len(cfg.Keys) > 1 {
			clear_stmt += "\n    m_" + get_n_key_map_name(cfg) + ".clear();"
		}

		for _, v := range cfg.Fields {
			if !v.Is_1_key() || v.Is_n_key() {
				continue
			}

			clear_stmt += "\n    m_" + get_1_key_map_name(cfg, &v) + ".clear();"
		}
	} else {
		clear_stmt = "\n    m_%cfg% = %cfgtype%();"
		clear_stmt = strings.Replace(clear_stmt, "%cfgtype%", get_cfg_type_name(cfg), -1)
		clear_stmt = strings.Replace(clear_stmt, "%cfg%", cfg.En_name, -1)
	}

	text = strings.Replace(text, "%clear_func%", get_clear_func_declare(cfg), -1)
	text = strings.Replace(text, "%clear_stmt%", clear_stmt, -1)
	return text
}

func gen_n_key_find_func(cfg *generator.Cfg_t) string {
	var n_key int = len(cfg.Keys)
	if n_key <= 1 {
		return ""
	}

	var text string = `
%find_func%
{
    %key_stmt%
    %map%::iterator itr = m_%map%.find(key);
    if(itr == m_%map%.end()){
        return NULL;
    }

    %cfg% *cfg = itr->second;
    return cfg;
}`

	text = strings.Replace(text, "%cfg%", get_cfg_type_name(cfg), -1)
	text = strings.Replace(text, "%find_func%", get_n_key_find_func_declare(cfg), -1)
	text = strings.Replace(text, "%key_stmt%", splice_n_key(cfg, ""), -1)
	text = strings.Replace(text, "%map%", get_n_key_map_name(cfg), -1)
	return text
}

func gen_1_key_find_func(cfg *generator.Cfg_t) string {
	var templet string = `
%find_func%
{
    %map%::iterator itr = m_%map%.find(%key%);
    if(itr == m_%map%.end()){
        return NULL;
    }

    %cfg% *cfg = itr->second;
    return cfg;
}`

	var text string
	for _, v := range cfg.Fields {
		if !v.Is_1_key() || v.Is_n_key() {
			continue
		}

		var func_stmt string = templet

		func_stmt = strings.Replace(func_stmt, "%cfg%", get_cfg_type_name(cfg), -1)
		func_stmt = strings.Replace(func_stmt, "%find_func%", get_1_key_find_func_declare(cfg, &v), -1)
		func_stmt = strings.Replace(func_stmt, "%map%", get_1_key_map_name(cfg, &v), -1)
		func_stmt = strings.Replace(func_stmt, "%key%", v.En_name, -1)

		text += func_stmt + "\n"
	}

	text = strings.Replace(text, "%cfg%", cfg.En_name, -1)
	return text
}

func gen_find_func(cfg *generator.Cfg_t) string {
	if cfg.Only_has_1_row() {
		return ""
	}

	var text string
	text += get_comment(cfg)
	text += gen_n_key_find_func(cfg) + "\n" + gen_1_key_find_func(cfg)
	return text
}

func (c *Cpp_generator) gen_cpp_file(cpp_file *string) bool {
	var text string
	tool.GetFileText(&c.M_cpp_templet_path, &text)

	if text == "" {
		tool.EchoErr("生成c++文件失败：找不到模板文件<%s>", c.M_cpp_templet_path)
		return false
	}

	text = strings.Replace(text, "%cfg%", c.M_cfgbase.Filename, -1)

	text = strings.Replace(text, "%structs_ctor%", splice(c.M_cfgbase, gen_struct_ctor, "\n\n"), -1)
	text = strings.Replace(text, "%structs_print%", splice(c.M_cfgbase, gen_struct_print, "\n\n"), -1)
	text = strings.Replace(text, "%load_funcs%", splice(c.M_cfgbase, gen_load_func, "\n"), -1)
	text = strings.Replace(text, "%clear_funcs%", splice(c.M_cfgbase, gen_clear_func, "\n"), -1)
	text = strings.Replace(text, "%find_funcs%", splice(c.M_cfgbase, gen_find_func, "\n"), -1)

	text = strings.Replace(text, "%mgr%", get_mgr_name(c.M_cfgbase), -1)
	text = strings.Replace(text, "%load_stmt%", splice(c.M_cfgbase, gen_call_load_func_stmt, "\n"), -1)
	text = strings.Replace(text, "%clear_stmt%", splice(c.M_cfgbase, gen_call_clear_func_stmt, "\n"), -1)
	text = strings.Replace(text, "%cfg_member%", get_member_comment_list(c.M_cfgbase), -1)

	enc := mahonia.NewEncoder("GB18030")
    if ret, ok := enc.ConvertStringOK(text); ok {
        // fmt.Println("UTF-8 to GBK: ", ret, " bytes: ", []byte(ret))		
		text = string(ret)
    }

	var is_overwrite_file_ok bool = tool.OverWriteFile(cpp_file, &text)
	return is_overwrite_file_ok
}
