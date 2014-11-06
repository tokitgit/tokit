///<------------------------------------------------------------------------------
//< @file:   tokit\tokit\generator.cpp
//< @author: 洪坤安
//< @date:   2014年9月25日 14:46:17
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include "generator.h"
#include "parser.h"
#include "file_tool.h"

void generator::echo_errs()
{
    echotool::echo_errvec(m_errvec);
    m_errvec.clear();
}
