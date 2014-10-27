///<------------------------------------------------------------------------------
//< @file:   tokit\tokit\cfgdef.h
//< @author: 洪坤安
//< @date:   2014年9月25日 16:35:49
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _cfgdef_h_
#define _cfgdef_h_

typedef _Longlong int64_t;

using namespace std;

// 正常来说各个功能区域的起始行
enum excel_row
{
    excel_row_none   = 0,
    
    excel_row_cfg    = 1, // 文件配置区
    excel_row_fields = 4, // 字段类型定义区
    excel_row_data   = 8, // 表格数据区
	excel_row_min = 9, // 至少应有几行
};

enum excel_cfg_row
{
    cfg_row_1   = 1, // 从文件配置起的第一行
    cfg_row_max,     // 最多有几行数据
};

enum excel_cfg_col
{
    cfg_col_none    = 0,
    cfg_col_en_name = 1,
    cfg_col_max_cnt = 2,

    cfg_col_max,
};

enum excel_field_row
{
    field_row_en_name   = 0,
    field_row_data_type = 1,
    field_row_is_unique = 2,
    field_row_max
};

// tokit原生类型
enum enum_tokit_field_type
{
    fieldtype_none   = 0, 
    fieldtype_string = 1,  // 字符串
    fieldtype_bool   = 2,  // bool类型
    fieldtype_int8   = 3,  // 单字节整数
    fieldtype_int16  = 4,  // 双字节整数
    fieldtype_int32  = 5,  // 四字节整数
    fieldtype_int64  = 6,  // 八字节整数
    fieldtype_uint8  = 7,  // 单字节无符号整数
    fieldtype_uint16 = 8,  // 双字节无符号整数
    fieldtype_uint32 = 9,  // 四字节无符号整数
    fieldtype_uint64 = 10, // 八字节无符号整数
    fieldtype_float  = 11, // 浮点数
    fieldtype_double = 12, // 双精度浮点数
    fieldtype_max,
};

// 解析excel的类型
enum enum_parse_option
{
    parse_option_skip_data = 1, // 跳过数据解析，仅解析配置定义
    parse_option_read_data = 2, // 解析配置定义并载入数据
};

#endif //_cfgdef_h_