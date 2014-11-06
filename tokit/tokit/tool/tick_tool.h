///<------------------------------------------------------------------------------
//< @file:   tick_tool.h
//< @author: 洪坤安
//< @date:   2014年9月20日 11:46:18
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _ticktool_h_
#define _ticktool_h_

#include "type.h"

typedef uint64 Tick;
namespace ticktool
{
    Tick get_tick();

    // 返回两次时钟周期的毫秒差
    uint32_t tick_diff(Tick old_tick);
}

class tick_t
{
public:
    tick_t()
    {
        start_tick();
    }

    void start_tick()
    {
        m_tick = ticktool::get_tick();
    }

    // 返回秒
    double end_tick();

private:
    Tick m_tick;
};

#endif //_ticktool_h_