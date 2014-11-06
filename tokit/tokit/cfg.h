///<------------------------------------------------------------------------------
//< @file:   tokit\tokit\cfg.h
//< @author: 洪坤安
//< @date:   2014年9月23日 10:24:53
//< @brief:  用于描述配置文件的文件结构
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _cfg_h_
#define _cfg_h_

#include <string>
#include <vector>

#include "cfgdef.h"

typedef _Longlong int64_t;

using namespace std;

// 字段成员，描述该字段的内部属性
struct field_t
{
    // 字段属性
    enum enum_field_attr
    {
        fieldattr_none = 0,   // 默认，表明本字段是普通成员
        fieldattr_n_key = 1,  // 本字段将与其它字段构成主键
        fieldattr_1_key,      // 本字段的值唯一
        fieldattr_array,      // 数组
        fieldattr_set,        // 集合
        fieldattr_max,
    };

    field_t()
        : fieldtype(fieldtype_none)
        , fieldattr(fieldattr_none)
    {
    }

    // 返回字段类型的名称
    string& get_field_type_name();

    bool is_1_key() const{ return fieldattr_1_key == fieldattr; } // 每条记录中本字段的值是否都唯一
    bool is_n_key() const{ return fieldattr_n_key == fieldattr; } // 本字段是否与其它字段构成主键
    bool is_array() const{ return fieldattr_array == fieldattr; }
    bool is_set() const{ return fieldattr_set == fieldattr; }

    enum_tokit_field_type fieldtype; // 数据类型
	string cn_name;         // 中文字段名称
    string en_name;         // 英文字段名称
    string comment;         // 注释
    
    enum_field_attr fieldattr;
};

typedef std::vector<field_t> fieldvec_t;
typedef std::vector<int> keyvec_t;

typedef std::vector<std::string> row_t;
typedef std::vector<row_t> table_t;

// 配置结构定义，与excel文件中的一个工作表相对应，描述了单个工作表的结构
struct cfg_t
{
    cfg_t()
        : maxcnt(0)
        , row_file_cfg_begin(0)
        , row_fields_begin(0)
        , row_data_begin(0)
    {
    }

    string cn_name;  // 配置定义文件的名称，可为中文
    string en_name;  // 配置的名称，必须为英文

    fieldvec_t fields; // 各成员
    keyvec_t keys;     // 主键索引列表（某个字段如果是主键，则将其索引加入到这个列表）

    size_t maxcnt; // 最多有几条数据

    size_t row_file_cfg_begin; // 文件定义区的起始行
    size_t row_fields_begin;   // 字段定义区的起始行
    size_t row_data_begin;     // 配置数据区的起始行

    table_t table; // 数据表

    // 根据字段名获取字段
    field_t* getfield(const char* fieldname)
    {
        for(size_t n = 0; n < fields.size(); n++){
            field_t &field = fields[n];
            if(field.en_name == fieldname){
                return &field;
            }
        }

        return NULL;
    }
    
    bool only_has_1_row() const { return 1 == maxcnt; }
};

typedef std::vector<cfg_t> cfgvec_t;

// 配置结构定义中心，与一整个excel文件相对应，描述了excel文件内部各个工作表的结构
struct cfgbase_t
{
    cfg_t* find_by_en_name(const char* en_name)
    {
        if(NULL == en_name){
            return NULL;
        }

        for(size_t n = 0; n < cfgs.size(); ++n){
            cfg_t &cfg = cfgs[n];

            if(cfg.en_name == en_name){
                return &cfg;
            }
        }

        return NULL;
    }

    
    string filename; // 本配置的文件名
    cfgvec_t cfgs;   // 各个工作表的描述
};

namespace cfgtool{
    // 字段类型的名称 -> 对应枚举
	enum_tokit_field_type type_name_2_enum(const char* tokit_type);
}

#endif //_cfg_h_