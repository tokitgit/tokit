///<------------------------------------------------------------------------------
//< @file:   echoutil.cpp
//< @author: 洪坤安
//< @date:   2014年9月20日 10:38:58
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include "echoutil.h"
#include <windows.h>
#include <io.h>
#include <stdio.h>

/* All the functions below is copy from gtest project, to show colored message in console */
/* 下面这些颜色设置的方法来自于gtest */

typedef unsigned short WORD;

namespace posix {
    inline int IsATTY(int fd) { return _isatty(fd); }
    inline int FileNo(FILE* file) { return _fileno(file); }
}

// Returns the character attribute for the given color.
WORD GetColorAttribute(GTestColor color) {
    switch (color) {
    case COLOR_RED:    return FOREGROUND_RED | FOREGROUND_INTENSITY;
    case COLOR_GREEN:  return FOREGROUND_GREEN;// | FOREGROUND_INTENSITY;
    case COLOR_YELLOW: return FOREGROUND_RED | FOREGROUND_GREEN;
    default:           return 0;
    }
}

bool ShouldUseColor(bool stdout_is_tty) {
    return stdout_is_tty;
}

// Helpers for printing colored strings to stdout. Note that on Windows, we
// cannot simply emit special characters and have the terminal change colors.
// This routine must actually emit the characters rather than return a string
// that would be colored when printed, as can be done on Linux.
void ColoredPrintf(GTestColor color, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    static const bool in_color_mode =
        ShouldUseColor(posix::IsATTY(posix::FileNo(stdout)) != 0);
    const bool use_color = in_color_mode && (color != COLOR_DEFAULT);

    if (!use_color) {
        vprintf(fmt, args);
        va_end(args);
        return;
    }

    const HANDLE stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    // Gets the current text color.
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    GetConsoleScreenBufferInfo(stdout_handle, &buffer_info);
    const WORD old_color_attrs = buffer_info.wAttributes;

    // We need to flush the stream buffers into the console before each
    // SetConsoleTextAttribute call lest it affect the text that is already
    // printed but has not yet reached the console.
    fflush(stdout);
    SetConsoleTextAttribute(stdout_handle,
        GetColorAttribute(color));// | FOREGROUND_INTENSITY);
    vprintf(fmt, args);

    fflush(stdout);
    // Restores the text color.
    SetConsoleTextAttribute(stdout_handle, old_color_attrs);

    va_end(args);
}

namespace echoutil
{
    std::string getmsg(const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);

        static char buf[4096] = {0};
        vsnprintf_s(buf, sizeof(buf), fmt, args);

        va_end(args);
        return buf;
    }

    void echo_errvec(const errvec_t &errs)
    {
        for(size_t i = 0; i < errs.size(); i++){
            const std::string &err = errs[i];
            ECHO_ERR("  %s", err.c_str());
        }
    }
}

/* All the functions above is copy from gtest project, to show colored message in console */