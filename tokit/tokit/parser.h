///<------------------------------------------------------------------------------
//< @file:   tokit\tokit\parser.h
//< @author: 洪坤安
//< @date:   2014年9月25日 16:20:22
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _parser_h_
#define _parser_h_

class COleSafeArray;
class CWorksheet;

#include "cfg.h"
#include "echoutil.h"

class parser
{
public:
    // 解析出excel中的各个工作表，将解析结果存入结构体
    static bool parse_excel(const string &xlsx, cfgbase_t&, errvec_t &errvec, enum_parse_option parse_option = parse_option_skip_data);

public:
    // 用于存储excel中的单元格数组，仅在采取ole载入方式时有效
    static COleSafeArray *g_ole_cell_array;
};

#endif //_parser_h_