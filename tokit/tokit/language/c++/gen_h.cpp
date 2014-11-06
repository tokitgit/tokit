///<------------------------------------------------------------------------------
//< @file:   prop\parser\gen_h.cpp
//< @author: 洪坤安
//< @date:   2014年9月25日 23:2:18
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include "c++_generator.h"

#include <fstream>

#include "cfg.h"
#include "file_tool.h"
#include "str_tool.h"
#include "echo_tool.h"
#include "parser.h"

namespace hxx
{
	string gen_struct(const cfg_t &cfg)
	{
		string text = 
            "// %comment%\n"
            "struct %cfgtype%{\n"
                "%typedef%\n"
            "    %cfgtype%();\n\n"
            "    std::string print() const;\n\n"
                "%fields%"
            "};\n"
            ;

        static char buf[1024] = {0};

        static char* static_field_attr_describe[field_t::fieldattr_max] = {
            "",
            "<<<主键>>>",
            "<<<唯一>>>",
            "<<<数组>>>",
            "<<<集合>>>",
        };

        string typedef_text;
        for(size_t n = 0; n < cfg.fields.size(); ++n){
            const field_t &field = cfg.fields[n];

            if (field.fieldattr == field_t::fieldattr_none){
                continue;
            }

            sprintf_s(buf, "    typedef %s %s; // %s%s\n", 
                cpptool::get_field_c_type(field).c_str(), 
                cpptool::get_field_c_typedef_type(cfg, field, cpptool::gcfo_without_namespace).c_str(),
                field.comment.c_str(), 
                static_field_attr_describe[field.fieldattr]
            );

            typedef_text += buf;
        }

        string fields_text;
        for(size_t n = 0; n < cfg.fields.size(); ++n){
            const field_t &field = cfg.fields[n];
            string c_type = cpptool::get_field_c_typedef_type(cfg, field, cpptool::gcfo_without_namespace);

            sprintf_s(buf, "    %s %s; // %s%s\n", c_type.c_str(), field.en_name.c_str(), field.comment.c_str(), static_field_attr_describe[field.fieldattr]);
            fields_text += buf;
		}

        strtool::replace(text, "%comment%", cfg.cn_name);
        strtool::replace(text, "%cfgtype%", cpptool::get_cfg_type_name(cfg));
        strtool::replace(text, "%typedef%", typedef_text);
        strtool::replace(text, "%fields%", fields_text);
		return text;
	}

    string gen_mgr_n_key_map_typedef(const cfg_t &cfg)
    {
        size_t n_key = cfg.keys.size();
        if (n_key <= 1){
            return "";
        }

        bool is_key_has_str = false;

        for (size_t n = 0; n < n_key; n++){
            int keyidx = cfg.keys[n];
            const field_t &key = cfg.fields[keyidx];

            if(key.fieldtype == fieldtype_string){
                is_key_has_str = true;
                break;
            }
        }

        string text = is_key_has_str ? "    typedef std::map<std::string, %cfg%*> %map%;\n" 
                                     : "    typedef std::map<uint64_t, %cfg%*> %map%;\n";
        strtool::replace(text, "%cfg%", cpptool::get_cfg_type_name(cfg));
        strtool::replace(text, "%map%", cpptool::get_n_key_map_name(cfg));
        return text;
    }

    string gen_mgr_1_key_map_typedef(const cfg_t &cfg)
    {
        string text = "";

        for(size_t n = 0; n < cfg.fields.size(); n++){
            const field_t &field = cfg.fields[n];
            if (!field.is_1_key()){
                continue;
            }

            string map_text = "    typedef std::map<%key%, %cfg%*> %map%; // %field_cn_name% -> %cfg%\n";
            strtool::replace(map_text, "%key%", cpptool::get_field_c_typedef_type(cfg, field));
            strtool::replace(map_text, "%map%", cpptool::get_1_key_map_name(cfg, field));
            strtool::replace(map_text, "%field_cn_name%", field.cn_name);

            text += map_text;
        }

        strtool::replace(text, "%cfg%", cpptool::get_cfg_type_name(cfg));
        return text;
    }

    string gen_mgr_vec_typedef(const cfg_t &cfg)
    {
        string text = "    typedef std::vector<%cfg%> %vec%;\n";
        strtool::replace(text, "%cfg%", cpptool::get_cfg_type_name(cfg));
        strtool::replace(text, "%vec%", cpptool::get_vec_name(cfg));
        return text;
    }

    string gen_mgr_typedef(const cfg_t &cfg)
    {
        if (cfg.only_has_1_row()){
            return "";
        }

        string text;
        text += "    " + cpptool::get_comment(cfg) + "\n";
        text += gen_mgr_n_key_map_typedef(cfg);
        text += gen_mgr_1_key_map_typedef(cfg);
        text += gen_mgr_vec_typedef(cfg);

        if (!text.empty()){
            text.erase(text.end() - 1);
        }

        return text;
    }

    string gen_mgr_load_func(const cfg_t &cfg)
    {
        string text = cpptool::clear_scope(cfg, cpptool::get_load_func_declare, "    ", ";");
        return text;
    }

    string gen_mgr_clear_func(const cfg_t &cfg)
    {
        string text = cpptool::clear_scope(cfg, cpptool::get_clear_func_declare, "    ", ";");
        return text;
    }

    string gen_mgr_n_key_find_func(const cfg_t &cfg)
    {
        string text = cpptool::clear_scope(cfg, cpptool::get_n_key_find_func_declare, "    ", ";\n");
        return text;
    }

    string gen_mgr_1_key_find_func(const cfg_t &cfg)
    {
        string text = cpptool::clear_scope(cfg, cpptool::get_1_key_find_func_declare_list);
        return text;
    }

    string gen_mgr_find_func(const cfg_t &cfg)
    {
        if (cfg.only_has_1_row()){
            return "";
        }

        string text;
        text += "    " + cpptool::get_comment(cfg) + "\n";
        text += gen_mgr_n_key_find_func(cfg);
        text += gen_mgr_1_key_find_func(cfg);

        if (!text.empty()){
            text.erase(text.end() - 1);
        }

        return text;
    }

    string gen_mgr_get_member_func(const cfg_t &cfg)
    {
        const string member_text = "    const %member_type%& get_%member%(){ return m_%member%; }\n";
        
        typedef std::vector<std::string> namevec_t;

        string text;

        namevec_t membernamevec;

        string member_stmt;
        string member_name;
        if (cfg.only_has_1_row()){
            text +=  member_text;

            strtool::replace(text, "%member%", cfg.en_name);
            strtool::replace(text, "%member_type%", cpptool::get_cfg_type_name(cfg));
        }else{
            size_t n_key = cfg.keys.size();
            if (n_key > 1){
                membernamevec.push_back(cpptool::get_n_key_map_name(cfg));
            }

            for(size_t n = 0; n < cfg.fields.size(); n++){
                const field_t &field = cfg.fields[n];
                if (!field.is_1_key()){
                    continue;
                }
                
                membernamevec.push_back(cpptool::get_1_key_map_name(cfg, field));
            }

            membernamevec.push_back(cpptool::get_vec_name(cfg));
        }

        for(size_t n = 0; n < membernamevec.size(); n++){
            string member_name  = membernamevec[n];
            string member_stmt = member_text;

            strtool::replace(member_stmt, "%member%", member_name);
            strtool::replace(member_stmt, "%member_type%", member_name);
            text += member_stmt;
        }

        if (!text.empty()){
            text.erase(text.end() - 1);
        }

        return text;
    }

    string gen_mgr_get_func(const cfg_t &cfg)
    {
        return gen_mgr_find_func(cfg) + "\n" + gen_mgr_get_member_func(cfg);
    }

    string gen_mgr_n_key_member(const cfg_t &cfg)
    {
        if (cfg.only_has_1_row()){
            return "";
        }

        size_t n_key = cfg.keys.size();
        if (n_key <= 1){
            return "";
        }

        string text = "    %map% m_%map%;\n";
        strtool::replace(text, "%map%", cpptool::get_n_key_map_name(cfg));
        return text;
    }

    string gen_mgr_1_key_member(const cfg_t &cfg)
    {
        if (cfg.only_has_1_row()){
            return "";
        }

        string text = "";

        for(size_t n = 0; n < cfg.fields.size(); n++){
            const field_t &field = cfg.fields[n];
            if (!field.is_1_key() || field.is_n_key()){
                continue;
            }

            string member_text = "    %map% m_%map%; // %field_cn_name% -> %cfg%\n";

            strtool::replace(member_text, "%map%", cpptool::get_1_key_map_name(cfg, field));
            strtool::replace(member_text, "%field_cn_name%", field.cn_name);
            text += member_text;
        }
        
        strtool::replace(text, "%cfg%", cfg.en_name);
        return text;
    }

    string gen_mgr_vec_member(const cfg_t &cfg)
    {
        if (cfg.only_has_1_row()){
            return "";
        }

        string text = "    %vec% m_%vec%;\n";
        strtool::replace(text, "%vec%", cpptool::get_vec_name(cfg));
        return text;
    }

    string gen_mgr_alone_member(const cfg_t &cfg)
    {
        if (!cfg.only_has_1_row()){
            return "";
        }

        string text = "    %cfgtype% m_%cfg%;\n";
        strtool::replace(text, "%cfgtype%", cpptool::get_cfg_type_name(cfg));
        strtool::replace(text, "%cfg%", cfg.en_name);
        return text;
    }

    string gen_mgr_members(const cfg_t &cfg)
    {
        string text;
        text += "    " + cpptool::get_comment(cfg) + "\n";
        text += gen_mgr_n_key_member(cfg);
        text += gen_mgr_1_key_member(cfg);
        text += gen_mgr_vec_member(cfg);
        text += gen_mgr_alone_member(cfg);

        if (!text.empty()){
            text.erase(text.end() - 1);
        }

        return text;
    }
}

bool cpp_generator::gen_h_file(const string &h_file)
{
    // 取出h模板文件的内容
    static string static_h_template;
    if (static_h_template.empty()){
        filetool::get_whole_file_str(m_h_templet_path, static_h_template);

        if(static_h_template.empty()){
            ECHO_ERR("生成c++文件失败：找不到模板文件<%s>", m_h_templet_path.c_str());
            return false;
        }
    }

    string text = static_h_template;

    strtool::replace(text, "%cfg%", m_cfgbase.filename);

    // 1. 定义配置数据结构体
    strtool::replace(text, "%structs%", cpptool::splice(m_cfgbase, hxx::gen_struct));

    // 2. 开始实现mgr管理器，该mgr将提供载入、清空和查找接口
    strtool::replace(text, "%typedefs%", cpptool::splice(m_cfgbase, hxx::gen_mgr_typedef, "\n\n"));
    strtool::replace(text, "%load_funcs%", cpptool::splice(m_cfgbase, hxx::gen_mgr_load_func, "\n"));
    strtool::replace(text, "%clear_funcs%", cpptool::splice(m_cfgbase, hxx::gen_mgr_clear_func, "\n"));
    strtool::replace(text, "%get_funcs%", cpptool::splice(m_cfgbase, hxx::gen_mgr_get_func, "\n\n"));
    strtool::replace(text, "%members%", cpptool::splice(m_cfgbase, hxx::gen_mgr_members, "\n\n"));
    strtool::replace(text, "%cfg_member%", cpptool::get_member_comment_list(m_cfgbase));
    strtool::replace(text, "%mgr%", cpptool::get_mgr_name(m_cfgbase));
 
    bool is_overwrite_file_ok = filetool::overwrite_file(h_file, text);
    return is_overwrite_file_ok;
}
