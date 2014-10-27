///<------------------------------------------------------------------------------
//< @file:   echoutil.h
//< @author: 洪坤安
//< @date:   2014年9月20日 10:38:49
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _echoutil_h_
#define _echoutil_h_

#include <string>
#include <vector>

enum GTestColor {
    COLOR_DEFAULT,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW
};

void ColoredPrintf(GTestColor color, const char* fmt, ...);

#define ECHO_ERR(fmt, ...) ColoredPrintf(COLOR_RED, "    "fmt"\n", __VA_ARGS__)
#define ECHO_OK(fmt, ...) ColoredPrintf(COLOR_GREEN, "    "fmt"\n", __VA_ARGS__)
#define ECHO_WARN(fmt, ...) ColoredPrintf(COLOR_YELLOW, fmt"\n", __VA_ARGS__)
#define ECHO_INFO(fmt, ...) fprintf(stdout, fmt"\n", __VA_ARGS__);

typedef std::vector<std::string> errvec_t;

namespace echoutil
{
    std::string getmsg(const char* fmt, ...);

    void echo_errvec(const errvec_t&);
}

using namespace echoutil;

#endif //_echoutil_h_