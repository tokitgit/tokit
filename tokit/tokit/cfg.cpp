///<------------------------------------------------------------------------------
//< @file:   tokit\tokit\cfg.cpp
//< @author: 洪坤安
//< @date:   2014年9月25日 16:36:1
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include "cfg.h"
#include "str_tool.h"

#include "echo_tool.h"
#include <algorithm>

namespace cfgtool
{
    // tokit可识别的数据类型数据
    string tokit_types[fieldtype_max] = {
        "",
        "string",
        "bool",
        "char",
        "int16",
        "int",
        "int64",
        "uint8",
        "uint16",
        "uint",
        "uint64",
        "float",
        "double"
    };

    enum_tokit_field_type type_name_2_enum(const char* tokit_type)
    {
        if (NULL == tokit_type){
            return fieldtype_none;
        }

        for(int i = fieldtype_none + 1; i < fieldtype_max; i++){
            if(tokit_types[i] == tokit_type){
                return (enum_tokit_field_type)i;
            }
        }

        return fieldtype_none;
    }
}

string& field_t::get_field_type_name()
{
    return cfgtool::tokit_types[fieldtype];
}
