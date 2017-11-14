///<------------------------------------------------------------------------------
//< @file:   c++\c++_example\tokit_tool.cpp
//< @author: 
//< @date:   2014年9月27日 0:3:56
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include "tokit_tool.h"
#include <fstream>
#include <sstream>
#include <iostream>

#ifdef WIN32
    #include <windows.h>
	#include <io.h>
#else
    #include <stdio.h>
    #define __STDC_FORMAT_MACROS  
    #include <inttypes.h>
#endif

#include <string.h>
#include <time.h>

namespace tool
{
#ifdef WIN32
    // 获取CPU每秒的滴答次数
	int64_t GetTickFrequency()
    {
        static LARGE_INTEGER static_perfFreq = {0};
        if(0 == static_perfFreq.QuadPart){
            QueryPerformanceFrequency(&static_perfFreq); 
        }

        return static_perfFreq.QuadPart;
    }
#endif

	int64_t get_tick()
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

    uint32 tick_diff(int64_t old_tick)
    {
		int64_t tick_now = get_tick();

#ifdef WIN32
        uint32 ms = (uint32)((tick_now - old_tick) * 1000 / GetTickFrequency());
#else
        uint32 ms = (tick_now - old_tick) / 1000000;
#endif

        return ms;
    }

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

	void split(const char* src, std::vector<std::string>& out, const char* cut)
    {
        std::string str(src);

		int n = (int)str.size();

		std::string::size_type a = 0, b = 0;
		while (b != std::string::npos) {
			a = str.find_first_not_of(cut, b);
			if (a == std::string::npos) {
				break;
			}

			b = str.find_first_of(cut, a + 1);
			if (b == std::string::npos) {
				if (a != n) {
					out.push_back(str.substr(a));
				}

				break;
			}

			out.push_back(str.substr(a, b - a));
		}
    }

	void split_str_set(const char* src, std::set<std::string>& out, const char* cut)
    {
		std::vector<std::string> vec;
        split(src, vec, cut);

		for (int i = 0, n = (int)vec.size(); i < n; ++i) {
            out.insert(vec[i]);
        }
    }

	void split_int_vec(const char* src, std::vector<int>& out, const char* cut /*= ","*/)
	{
		std::vector<std::string> vec;
		split(src, vec, cut);

		for (int i = 0, n = (int)vec.size(); i < n; ++i) {
			int num = str_to_int(vec[i].c_str());
			out.push_back(num);
		}
	}

	void split_int_set(const char* src, std::set<int>& out, const char* cut /*= ","*/)
	{

	}

}

bool exist(const char* path)
{
	return _access(path, 0) != -1;
}

bool tool::GetFileText(const char* path, std::string &text)
{
	if (false == exist(path)) {
		text = "";
		return false;
	}

	if (false == exist(path)) {
		std::cout << "open <" << path << "> file failed: not found file!";
		text = "";
		return false;
	}

	/* 若要一个byte不漏地读入整个文件，只能采用二进制方式打开 */
	FILE *file = NULL;

	int err = fopen_s(&file, path, "rb");
	if (NULL == file || err > 0) {
		std::cout << "[error] open file <" << path << "> failed，error code = " << err << "\n";
		return false;
	}

	/* 获取文件大小 */
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	rewind(file);

	/* 分配内存存储整个文件 */
	text.resize(size );
	
	/* 将文件拷贝到buffer中 */
	size_t n = fread((void*)text.c_str(), 1, size, file);
	if (n != size) {
		std::cout << "载入<" << path << ">文件失败，错误原因:文件读取大小不符" << n << " != " << size;
		return false;
	}

	/* 现在整个文件已经在buffer中 */
	/* 关闭文件并释放内存 */
	fclose(file);
	return true;
}
