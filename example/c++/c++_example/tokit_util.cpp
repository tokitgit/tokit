///<------------------------------------------------------------------------------
//< @file:   c++\c++_example\tokit_util.cpp
//< @author: 
//< @date:   2014年9月27日 0:3:56
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include "tokit_util.h"

#ifdef WIN32
    #include <windows.h>
#else
    #include <stdio.h>
    #define __STDC_FORMAT_MACROS  
    #include <inttypes.h>
#endif

#include <string.h>
#include <time.h>

namespace keyutil
{
    uint64 Get16161616Key(uint16 w, uint16 x, uint16 y, uint16 z)
    {
        uint64 key_w = w;
        key_w <<= 32;

        uint64 key_x = x;
        key_x <<= 32;

        uint64 key_y = y;
        key_y <<= 32;

        uint64 key = key_w + key_x + key_y + z;
        return key;
    }

    uint64 Get161616Key(uint16 x, uint16 y, uint16 z)
    {
        uint64 key_x = x;
        key_x <<= 32;

        uint64 key_y = y;
        key_y <<= 32;

        uint64 key = key_x + key_y + z;
        return key;
    }

    uint64 Get3232Key(uint32 x, uint32 y)
    {
        uint64 key_x = x;
        key_x <<= 32;

        uint64 key = key_x + y;
        return key;
    }
}

namespace tickutil
{
#ifdef WIN32
    // 获取CPU每秒的滴答次数
    Tick GetTickFrequency()
    {
        static LARGE_INTEGER static_perfFreq = {0};
        if(0 == static_perfFreq.QuadPart){
            QueryPerformanceFrequency(&static_perfFreq); 
        }

        return static_perfFreq.QuadPart;
    }
#endif

    Tick get_tick()
    {
#ifdef WIN32
        LARGE_INTEGER tick;

        QueryPerformanceCounter(&tick);
        return tick.QuadPart;
#else
        timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);

        return ts.tv_sec * 1000000000 + ts.tv_nsec;
#endif
    }

    uint32 tick_diff(Tick old_tick)
    {
        Tick tick_now = get_tick();

#ifdef WIN32
        uint32 ms = (uint32)((tick_now - old_tick) * 1000 / GetTickFrequency());
#else
        uint32 ms = (tick_now - old_tick) / 1000000;
#endif

        return ms;
    }
}

// 返回秒
double tick_t::end_tick()
{
    Tick tick_now = tickutil::get_tick();
    Tick diff = tick_now - m_tick;

    double passed_sec = (double)diff / tickutil::GetTickFrequency();
    return passed_sec;
}

namespace strutil
{
    // 替换字符串
    // 例如：replace("this is an expmple", "is", "") = "th  an expmple"
    string& replace(string &str, const char *old, const char* to)
    {
        string::size_type pos = 0;
        int len_old = strlen(old);
        int len_new = strlen(to);

        while((pos = str.find(old, pos)) != string::npos){   
            str.replace(pos, len_old, to);   
            pos += len_new;
        }

        return str;
    }

    string& replace(string &str, const char *old, const string& to){
        string::size_type pos = 0;
        int len_old = strlen(old);
        int len_new = to.size();

        while((pos = str.find(old, pos)) != string::npos){   
            str.replace(pos, len_old, to);   
            pos += len_new;
        }

        return str;
    }

    // 循环替换，即每次字符串被替换后，再在替换过的字符串中进行替换
    // 例如: replace("dbdb", "db", "bd") = "bbbd"
    // 又如: replace("good", "o", "oo") = "将会导致死循环"
    string& cycle_replace(string &str, const char *old, const char* to)
    {
        string::size_type pos = 0;
        int len_old = strlen(old);

        while((pos = str.find(to)) != string::npos){
            str.replace(pos, len_old, to);   
        }

        return str;  
    }

    // 将无符号64位整数转换为字符串
    // 例如：tostr(100123) = "100123"
    string tostr(uint64 n)
    {
        char buf[64] = {0};

#ifdef WIN32
        errno_t err = _ui64toa_s (n, buf, sizeof(buf), 10);
        if(err){
            return "";
        }

        return buf;
#else
        
        snprintf(buf, sizeof(buf), "%" PRIu64 "", n);

        // snprintf(buf, sizeof(buf), "%llu", n);
        return buf;
#endif
    }

    stringvec_t split(const string &src, char cut /* = ',' */)
    {
        stringvec_t vec;

        std::string::size_type pos1 = 0, pos2 = 0;
        while (pos2 != std::string::npos){
            pos1 = src.find_first_not_of(cut, pos2);
            if (pos1 == std::string::npos){
                break;
            }

            pos2 = src.find_first_of(cut, pos1 + 1);
            if (pos2 == std::string::npos){
                if (pos1 != src.size()){
                    vec.push_back(src.substr(pos1));
                }

                break;
            
            }

            vec.push_back(src.substr(pos1, pos2 - pos1));
        }

        return vec;
    }

    stringvec_t split(const char* src, char cut /* = ',' */)
    {
        string str(src);
        return split(str, cut);
    }

    stringset_t split_str_set(const string &src, char cut /* = ',' */)
    {
        stringset_t str_set;

        stringvec_t strvec = split(src, cut);
        for (size_t n = 0; n < strvec.size(); n++){
            std::string &str = strvec[n];
            str_set.insert(str);
        }

        return str_set;
    }
}