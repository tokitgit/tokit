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
    static bool parse_excel(const string &xlsx, cfgbase_t&, errvec_t &errvec, enum_parse_option parse_option = parse_option_skip_data);
};

#endif //_parser_h_