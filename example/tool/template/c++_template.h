///<------------------------------------------------------------------------------
//< @file:  %cfg%.h
//< @brief: %cfg_member%
//< 本头文件由工具自动生成，请勿在本文件内做改动
//< @Copyright (c) 2014 tokit.
///<------------------------------------------------------------------------------

#ifndef _%cfg%_h_
#define _%cfg%_h_

#include <string>

#include <map>
#include <vector>
#include <set>

#include "type.h"

%structs%

// %cfg_member%
class %mgr%
{
public:
%typedefs%

public:
	%mgr%(){}
	~%mgr%(){}

	static %mgr%& instance(){
		static %mgr% static_%mgr%;
		return static_%mgr%;
	}

private:
    %mgr%& operator=(const %mgr%&){ static %mgr% mgr; return mgr; }
    %mgr% (const %mgr%&){}

public:
	// @impl 获取本配置类名称
	std::string mgr_name(){ return "%cfg%"; }

    // 获取xml文件路径
    std::string get_path(std::string xml){ return "../../xml/" + xml;}

public:
    // 载入%cfg_member%
	virtual bool load();

    // 清空%cfg_member%
    virtual void clear();

public:
%load_funcs%

public:
%clear_funcs%

public:
%get_funcs%

public:
%members%
};

#endif // _%cfg%_h_
