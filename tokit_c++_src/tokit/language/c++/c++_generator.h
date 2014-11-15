///<------------------------------------------------------------------------------
//< @file:   language\c++\c++_generator.h
//< @author: 洪坤安
//< @date:   2014年9月25日 15:43:10
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _cpp_generator_h_
#define _cpp_generator_h_

#include <string>
#include "generator.h"

using std::string;

struct cfgbase_t;
struct cfg_t;
struct field_t;

namespace cpptool{
    enum enum_get_c_field_option{
        gcfo_with_namespace = 0,    // 指定作用域
        gcfo_without_namespace = 1, // 不指定作用域
    };

    string get_field_c_typedef_type(const cfg_t&, const field_t&, enum_get_c_field_option c_type = gcfo_with_namespace); // 获取单个字段的c++中typedef类型，对于map或vec等特殊类型的字段，也将返回typedef后的类型名
    string get_field_c_type(const field_t&); // 获取单个字段的c++中类型，对于map或vector等特殊类型的字段，将经过特殊处理
    string get_field_parameter_c_type(const cfg_t&, const field_t&); // 获取函数参数中单个字段的声明，如int id、const char* name等
    string get_n_key_map_name(const cfg_t&); // 获取多键map名（多键map的key是由多个主键组合而成的）
    string get_1_key_map_name(const cfg_t&, const field_t&); // 获取单键map名
    string get_vec_name(const cfg_t&); // 获取配置vector的名称
    string get_mgr_name(const cfgbase_t&); // 获取配置管理器的名称
    string get_comment(const cfg_t&); // 获取配置的注释
    string get_cfg_type_name(const cfg_t &cfg); // 获取配置结构体的名称

    string get_load_func_declare(const cfg_t&);// 获取载入方法声明
    string get_clear_func_name(const cfg_t&);// 获取清空方法名称
    string get_clear_func_declare(const cfg_t&);// 获取清空方法声明
    string get_n_key_find_func_declare(const cfg_t&); // 获取根据多个键值查找配置的方法声明
    string get_1_key_find_func_declare_list(const cfg_t&); // 获取根据1个键值查找配置的方法声明列表
    string get_1_key_find_func_declare(const cfg_t&, const field_t&); // 获取根据1个键值查找配置的方法声明
    string get_member_comment_list(const cfgbase_t &cfgbase); // 获取类成员的注释
}

namespace cpptool{
    // 将excel文件中的每个工作表对应生成的文本串拼接起来
    typedef string (gen_func_t)(const cfg_t&);
    string splice(const cfgbase_t &cfgbase, gen_func_t func, const char* splice_token = "\n");

    // 例如：void %mgr%::clear() -> void clear()
    string clear_scope(const cfg_t&, gen_func_t func, const char* prefix = "", const char* postfix = "");
}

class cpp_generator : public generator
{
public:
    cpp_generator(cfgbase_t &cfgbase, const string &to_dir, const string &h_templet, const string &cpp_templet)
        : generator(cfgbase)
        , m_h_templet_path(h_templet)
        , m_cpp_templet_path(cpp_templet)
        , m_to_dir(to_dir)
    {
    }

public:
    // @impl
    virtual bool generate();

public:
    // tokit原生类型 -> c++类型
    static string& raw_type_2_c_type(enum_tokit_field_type);

private:
    bool gen_h_file(const string &h_file);
	bool gen_cpp_file(const string &cpp_file);

private:
    std::string m_h_templet_path;   /* 用于生成.h的模板文件 */
    std::string m_cpp_templet_path; /* 用于生成.cpp的模板文件 */
    std::string m_to_dir;
};

#endif //_cpp_generator_h_