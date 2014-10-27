///<------------------------------------------------------------------------------
//< @file:   tickutil.cpp
//< @author: 洪坤安
//< @date:   2014年9月20日 11:46:36
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include "tickutil.h"

#include <windows.h>

namespace tickutil
{
    // 获取CPU每秒的滴答次数
    Tick GetTickFrequency()
    {
        static LARGE_INTEGER static_perfFreq = {0};
        if(0 == static_perfFreq.QuadPart){
            QueryPerformanceFrequency(&static_perfFreq); 
        }

        return static_perfFreq.QuadPart;
    }

    Tick get_tick()
    {
        LARGE_INTEGER tick;

        QueryPerformanceCounter(&tick);
        return tick.QuadPart;
    }

    uint32_t tick_diff(Tick old_tick)
    {
        Tick tick_now = get_tick();

        uint32_t ms = (uint32_t)((tick_now - old_tick) * 1000 / GetTickFrequency());
        return ms;
    }
}
