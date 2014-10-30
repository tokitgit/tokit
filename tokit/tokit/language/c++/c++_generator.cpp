///<------------------------------------------------------------------------------
//< @file:   language\c++\c++_generator.cpp
//< @author: 洪坤安
//< @date:   2014年9月25日 15:43:44
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include "c++_generator.h"

#include <iostream>

#include "cfg.h"
#include "file_util.h"
#include "str_util.h"
#include "echoutil.h"
#include "tickutil.h"
#include "parser.h"

namespace cpputil{
    string get_field_c_typedef_type(const cfg_t &cfg, const field_t &field, enum_get_c_field_option c_type /* = fct_with_namespace */)
    {
        string ret;
        if (field.fieldattr != field_t::fieldattr_none){
            string typedef_type;
            
            if (field.is_array()){
                typedef_type = field.en_name + "vec_t";
            }else if(field.is_set()){
                typedef_type = field.en_name + "set_t";
            }else{
                typedef_type = field.en_name + "_t";
            }

            // 检测是否需要指定作用域
            ret = (gcfo_without_namespace == c_type) ? typedef_type 
                                                     : cpputil::get_cfg_type_name(cfg) + "::" + typedef_type;
        }else{
            ret = cpp_generator::raw_type_2_c_type(field.fieldtype);
        }

        return ret;
    }

    string get_field_c_type(const field_t &field)
    {
        string text;
        string &c_type = cpp_generator::raw_type_2_c_type(field.fieldtype);

        if (field.is_array()){
            text = "std::vector<%type%>";
            strutil::replace(text, "%type%", c_type);
        }else if(field.is_set()){
            text = "std::set<%type%>";
            strutil::replace(text, "%type%", c_type);
        }else{
            text = c_type;
        }

        return text;
    }

    string get_field_parameter_c_type(const cfg_t &cfg, const field_t &field)
    {
        string paramtype = (field.fieldtype == fieldtype_string ? "const char*" : get_field_c_typedef_type(cfg, field));
        return paramtype;
    }

    string get_n_key_map_name(const cfg_t &cfg)
    {
        return cfg.en_name + "map";
    }

    string get_1_key_map_name(const cfg_t &cfg, const field_t &field)
    {
        return field.en_name + "2" + cfg.en_name + "map";
    }

    string get_vec_name(const cfg_t &cfg)
    {
        return cfg.en_name + "vec";
    }

    string get_mgr_name(const cfgbase_t &cfgbase)
    {
        return cfgbase.filename + "mgr";
    }

    string get_comment(const cfg_t &cfg)
    {
        return "// " + cfg.cn_name;
    }

    string get_cfg_type_name(const cfg_t &cfg)
    {
        return cfg.en_name + "_t";
    }

    string get_load_func_declare(const cfg_t &cfg)
    {
        string text = "bool %mgr%::load_%cfg%()";
        strutil::replace(text, "%cfg%", cfg.en_name);
        return text;
    }

    string get_clear_func_name(const cfg_t &cfg)
    {
        string text = "clear_%cfg%";
        strutil::replace(text, "%cfg%", cfg.en_name);
        return text;
    }

    string get_clear_func_declare(const cfg_t &cfg)
    {
        string text = "void %mgr%::%clear_func_name%()";
        strutil::replace(text, "%clear_func_name%", get_clear_func_name(cfg));
        return text;
    }

    string get_n_key_find_func_declare(const cfg_t &cfg)
    {
        size_t n_key = cfg.keys.size();
        if (n_key <= 1){
            return "";
        }

        // 拼接出函数参数，比如 = int id, int lvl
        string key = "";
        key.reserve(n_key * 10);
        for(size_t n = 0; n < n_key; n++){
            int keyidx = cfg.keys[n];

            const field_t &field = cfg.fields[keyidx];

            string paramtype = cpputil::get_field_parameter_c_type(cfg, field);
            key.append(paramtype + " " + field.en_name);

            if (n + 1 < n_key){
                key.append(", ");
            }
        }

        string text = "const %cfgtype%* %mgr%::get_%cfg%(%key%)";

        strutil::replace(text, "%cfg%", cfg.en_name);
        strutil::replace(text, "%cfgtype%", cpputil::get_cfg_type_name(cfg));
        strutil::replace(text, "%key%",  key);
        return text;
    }

    string get_1_key_find_func_declare_list(const cfg_t &cfg)
    {
        string text = "";

        for(size_t n = 0; n < cfg.fields.size(); n++){
            const field_t &field = cfg.fields[n];

            string field_find_func = get_1_key_find_func_declare(cfg, field);
            if (!field_find_func.empty()){
                text += "    " + field_find_func + ";\n";
            }
        }

        return text;
    }

    string get_1_key_find_func_declare(const cfg_t &cfg, const field_t &field)
    {
        if (!field.is_1_key() || field.is_n_key()){
            return "";
        }

        string text = "const %cfgtype%* %mgr%::get_%cfg%_by_%key_name%(%key%)";

        string key = cpputil::get_field_parameter_c_type(cfg, field) + " " + field.en_name;
        strutil::replace(text, "%key%", key);
        strutil::replace(text, "%key_name%", field.en_name);
        strutil::replace(text, "%cfg%", cfg.en_name);
        strutil::replace(text, "%cfgtype%", cpputil::get_cfg_type_name(cfg));
        return text;
    }

    string get_member_comment_list(const cfgbase_t &cfgbase)
    {
        string text;

        size_t n_cfg = cfgbase.cfgs.size();
        for(size_t n = 0; n < n_cfg; ++n){
            const cfg_t &cfg = cfgbase.cfgs[n];
            text += cfg.cn_name;

            if (n + 1 < n_cfg){
                text += ", ";
            }
        }

        return text;
    }
}

namespace cpputil{
    string splice_each_cfg(const cfgbase_t &cfgbase, gen_func_t func, const char* splice_str /* = "\n" */)
    {
        // 将调用func产生的文本拼接起来
        string text = "";

        size_t n_cfg = cfgbase.cfgs.size();
        for(size_t n = 0; n < n_cfg; ++n){
            const cfg_t &cfg = cfgbase.cfgs[n];
            string ret_text = func(cfg);
            if (ret_text.empty()){
                continue;
            }

            text += ret_text;
            if (n + 1 < n_cfg){
                text += splice_str;
            }
        }

        return text;
    }

    string get_member_func_decl_stmt(const cfg_t &cfg, gen_func_t func, const char* prefix /* = "" */, const char* postfix /* = "" */)
    {
        string stmt = func(cfg);
        if (stmt.empty()){
            return "";
        }

        // 清除掉对象域声明
        strutil::replace(stmt, "%mgr%::", "");
        return prefix + stmt + postfix;
    }
}

bool cpp_generator::generate()
{
    if(false == fileutil::exist(m_to_dir)){
        ECHO_ERR("参数错误: 找不到指定的生成源文件的路径<%s>，请确认路径是否存在!", m_to_dir.c_str());
        return false;
    }

    if(false == fileutil::exist(m_h_templet_path)){
        ECHO_ERR("参数错误: 找不到.h模板头文件<%s>", m_h_templet_path.c_str());
        return false;
    }

    if(false == fileutil::exist(m_cpp_templet_path)){
        ECHO_ERR("参数错误: 找不到cpp模板源文件<%s>", m_cpp_templet_path.c_str());
        return false;
    }

    string h_file = m_to_dir + "\\" + strip_ext(strip_dir(m_cfgbase.filename)) + ".h";
    string cpp_file = m_to_dir + "\\" + strip_ext(strip_dir(m_cfgbase.filename)) + ".cpp";

    if (!gen_h_file(h_file)){
        ECHO_ERR("生成h头文件<%s>失败", h_file.c_str());
        echo_errs();
        return false;
    }

    ECHO_OK("生成h头文件<%s>成功", h_file.c_str());

    if (!gen_cpp_file(cpp_file)){
        ECHO_ERR("生成cpp源文件<%s>失败", cpp_file.c_str());
        echo_errs();
        return false;
    }

    ECHO_OK("生成cpp源文件<%s>成功", cpp_file.c_str());
    return true;
}

string& cpp_generator::raw_type_2_c_type(enum_tokit_field_type fieldtype)
{
    static string static_c_types[fieldtype_max] = {
        "",
        "std::string",
        "bool",
        "char",
        "int16",
        "int32",
        "int64",
        "uint8",
        "uint16",
        "uint32",
        "uint64",
        "float",
        "double"        //"unsigned __int64",
    };

    return static_c_types[fieldtype];
}