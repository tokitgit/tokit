///<------------------------------------------------------------------------------
//< @file:   c++\c++_example\main.cpp
//< @author: 
//< @date:   2014年9月24日 20:47:27
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include "testcfg.h"
#include "dotaequipcfg.h"

#include <stdio.h>

void load()
{
    testcfgmgr::instance().load();
    dotaequipcfgmgr::instance().load();
}

void test()
{
    dotaequipcfg_t *dotaequipcfg = dotaequipcfgmgr::instance().get_dotaequipcfg_by_id(1);
    if (NULL == dotaequipcfg){
        return;
    }

    dotaherocfg_t *dotaherocfg = dotaequipcfgmgr::instance().get_dotaherocfg_by_name("小黑");
    if (NULL == dotaherocfg){
        return;
    }

    const dotaequipcfgmgr::id2dotaequipcfgmap &dotaequipcfgmap = dotaequipcfgmgr::instance().get_id2dotaequipcfgmap();
    if (dotaequipcfgmap.empty()){
        return;
    }
}

void hello()
{
    load();
    test();
}

int main(int argc, char *argv[])
{
    hello();

    // system("pause");
    return 0;
}
