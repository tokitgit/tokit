///<------------------------------------------------------------------------------
//< @file:   c++\c++_example\tokit_tool.h
//< @author: 
//< @date:   2014年9月27日 0:2:43
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _tokit_tool_h_
#define _tokit_tool_h_

#include <string>
#include <vector>
#include <set>

#include "type.h"
#include <stdlib.h>

#ifdef WIN32
    #define snprintf sprintf_s
    #define I64d "%I64d"
    #define I64u "%I64u"
#else
    #define I64d "%lld"
    #define I64u "%llu"
#endif

using namespace std;

namespace tool
{
	bool GetFileText(const char* path, std::string &text);

    int64_t get_tick();

    // 返回两次时钟周期的毫秒差
    uint32 tick_diff(int64_t old_tick);
 
	// 替换字符串，传入的字符串将被修改
    // 例如：replace("this is an expmple", "is", "") = "th  an expmple"
    // 又如: replace("dbdb", "db", "bd") = "bdbd"
    string& replace(string &str, const char *old, const char* to);

    inline bool str_to_bool(const char* str)
    {
		char c = str[0];
        return !(c == '0' || c == '\0');
    }

    inline int32 str_to_int(const char* str)
    {
        return atoi(str);
    }

    inline int64 str_to_int64(const char* str)
    {
        double val = 0; 
        val = strtod(str, NULL); 

        return (int64)val;
    }

	inline float str_to_float(const char* str)
	{
		double val = 0;
		val = strtod(str, NULL);

		return (float)val;
	}

	inline double str_to_double(const char* str)
	{
		double val = 0;
		val = strtod(str, NULL);

		return val;
	}

    inline std::string un_escape_xml(const char* old_str)
    {
        std::string str(old_str);
        replace(str, "&quot;", "\"");

        return str;
    }

    // 将字符串拆分成数组
	void split(const char* src, std::vector<std::string>&, const char* cut = ",");

	// 将字符串拆分成集合
	void split_str_set(const char* src, std::set<std::string>& out, const char* cut = ",");

	// 将字符串拆分成整数数组
	void split_int_vec(const char* src, std::vector<int>& out, const char* cut = ",");

	// 将字符串拆分成整数集合
	void split_int_set(const char* src, std::set<int>& out, const char* cut = ",");

	// 将字符串拆分成整数数组
	void split_float_vec(const char* src, std::vector<float>& out, const char* cut = ",");

	// 将字符串拆分成整数集合
	void split_float_set(const char* src, std::set<float>& out, const char* cut = ",");

    template <typename T, typename CastFunction>
    inline void split_str_to_vec(const char* src, std::vector<T>& out, CastFunction (*cast_func)(const char*), const char* cut = ",")
    {
		std::vector<std::string> vec;
        split(src, vec, cut);

		for (int i = 0, n = (int)vec.size(); i < n; ++i) {
			const std::string& elem = vec[i];
			T t = (T)cast_func(elem.c_str());
			out.push_back(t);
		}
    }

    template <typename T, typename CastFunction>
    inline void split_str_to_set(const char* src, std::set<T>& out, CastFunction (*cast_func)(const char*), const char* cut = ",")
    {
		std::vector<std::string> vec;
		split(src, vec, cut);

		for (int i = 0, n = (int)vec.size(); i < n; ++i) {
			const std::string& elem = vec[i];
			T t = (T)cast_func(elem.c_str());
			out.insert(t);
		}
    }
};

#endif //_tokit_tool_h_