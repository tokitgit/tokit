///<------------------------------------------------------------------------------
//< @file:   c++\c++_example\main.cpp
//< @author: 
//< @date:   2014Äê9ÔÂ24ÈÕ 20:47:27
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include "DotaModule.h"
#include "TestModule.h"
#include "tokit_tool.h"

#include <stdio.h>

void test()
{
	DotaModule::instance.Load("D:\\proj\\mine\\tokit\\example\\json\\");
	DotaModule::instance.Load("D:\\proj\\mine\\tokit\\example\\json\\");
	DotaModule::instance.Load("D:\\proj\\mine\\tokit\\example\\json\\");
	DotaModule::instance.Load("D:\\proj\\mine\\tokit\\example\\json\\");
	DotaModule::instance.Load("D:\\proj\\mine\\tokit\\example\\json\\");
	DotaModule::instance.Load("D:\\proj\\mine\\tokit\\example\\json\\");
	DotaModule::instance.Load("D:\\proj\\mine\\tokit\\example\\json\\");
	TestModule::instance.Load("D:\\proj\\mine\\tokit\\example\\json\\");
}

int main(int argc, char *argv[])
{
	int64_t n = tool::str_to_int64("-9E+18");
	test();
    // system("pause");
    return 0;
}
