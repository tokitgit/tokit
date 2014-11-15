///<------------------------------------------------------------------------------
//< @file:   c++\c++_example\main.cpp
//< @author: 
//< @date:   2014Äê9ÔÂ24ÈÕ 20:47:27
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include "testcfg.h"
#include "dotaequipcfg.h"

#include <stdio.h>

void load()
{
    dotaequipcfgmgr::instance().load();
    testcfgmgr::instance().load();
}

void test()
{
    const dotaequipcfg_t *dotaequipcfg = dotaequipcfgmgr::instance().get_dotaequipcfg_by_id(1);
    if (NULL == dotaequipcfg){
        return;
    }

    printf("%s\n", dotaequipcfg->print().c_str());

    const dotaequipcfgmgr::id2dotaequipcfgmap &dotaequipcfgmap = dotaequipcfgmgr::instance().get_id2dotaequipcfgmap();
    if (dotaequipcfgmap.empty()){
        return;
    }

    const dotaequipcfgmgr::dotaequipcfgvec &vec = dotaequipcfgmgr::instance().get_dotaequipcfgvec();
    for (size_t n = 0; n < vec.size(); n++){
        printf("%s\n", vec[n].print().c_str());
    }

    const testcfgmgr::testcfgvec &test_vec = testcfgmgr::instance().get_testcfgvec();
    for (size_t n = 0; n < test_vec.size(); n++){
        // printf("%s\n", test_vec[n].print().c_str());
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
