tokit
=====

tokit是一个用于方便网游研发人员配置数据的工具。可以根据一份符合tokit格式的excel文件，生成对应的文件。

目前支持生成：

- [x] xml
- [x] xsd
- [x] c++

其中c++文件中含有自动读取xml数据的接口以及查找接口。

## 使用过程

* 1. 策划在excel中编辑完数据后
* 2. 程序人员在同一个excel中编辑好字段定义，使其符合tokit格式
* 3. 使用tokit从excel中生成c++代码，并导出xml数据文件和xsd文件。

详细步骤可见目录下的**`《Tokit使用手册.pdf》`**。

## 使用命令

使用tokit要求有一个符合tokit格式的excel文件

使用方式如下：

>`tokit.exe`  `<excel文件>`<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[ `-xsd`  `<放置xsd文件的目录>` ]  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[ `-c++`  `<h模板>`  `<cpp模板>`  `<放置c++文件的目录>` ]  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[ `-saveasxml`  `<放置xml文件的目录>` ]  

>选项：<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`-xsd`   根据excel生成xsd文件  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`-c++`   根据excel生成c++文件  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`-saveasxml`   将excel文件导出成为xml数据文件  

比如：

	假设有一个符合tokit格式的excel文件《装备.xlsx》，里面有一个工作表item，则 
		
		tokit.exe   ../装备.xlsx   -xsd   ./xsd/   「将在xsd目录下生成item.xsd文件」 
		tokit.exe   ../装备.xlsx   -c++   ./template/c++_template.h   ./template/c++_template.cpp   ./c++/  「将在c++目录下生成item.h和item.cpp文件」 
		tokit.exe   ../装备.xlsx   -saveasxml   ./xml/  「将在xml目录下生成item.xml数据文件」 
		
	这些参数可结合起来： 
		tokit.exe   ../装备.xlsx   -xsd   ./xsd/   -c++   ./template/c++_template.h   ./template/c++_template.cpp   ./c++/ -saveasxml   ./xml/  「将生成item.xsd、item.h、item.cpp和item.xml文件」


## 下载之后

下载tokit整个项目之后，运行`example`目录下的`《一键生成.bat》`脚本。

示例excel置于`example\excel`目录下，该脚本将根据`example\excel`中的各个excel文件，生成对应的xml、xsd、c++文件。

参考`example\c++\c++_example.sln`项目和`《Tokit使用手册.pdf》`，将tokit接入你自己的c++项目

## 示例


为了更快的了解tokit，现在把tokit生成的文件全部贴出来。


假设现在有一个excel文件`《dota英雄表.xlsx》`，里面的内容是

						《dota英雄表.xlsx》
![dotahero](https://github.com/tokitgit/tokit/blob/master/doc/image/dotahero.jpg)

<br>
<br>
	
则使用tokit之后，将生成xml、xsd和c++文件

<br>
<br>

						* 1.《dotaherocfg.xml》
![dotahero_xml](https://github.com/tokitgit/tokit/blob/master/doc/image/dotahero_xml.jpg)

<br>
<br>

						* 2.《dota装备表.xsd》
![dotahero_xsd](https://github.com/tokitgit/tokit/blob/master/doc/image/dotahero_xsd.jpg)

<br>
<br>

						* 3.《dotaherocfg.h》
```cpp
///<------------------------------------------------------------------------------
//< @file:  dotaherocfg.h
//< @brief: dota英雄表
//< 本头文件由工具自动生成，请勿在本文件内做改动
//< @Copyright (c) 2014 tokit.
///<------------------------------------------------------------------------------

#ifndef _dotaherocfg_h_
#define _dotaherocfg_h_

#include <string>

#include <map>
#include <vector>
#include <set>

#include "type.h"

// dota英雄表
struct dotaherocfg_t{
    typedef uint32 id_t; // 英雄ID<<<唯一>>>
    typedef std::string name_t; // 英雄名称<<<唯一>>>

    dotaherocfg_t();

    std::string print() const;

    id_t id; // 英雄ID<<<唯一>>>
    name_t name; // 英雄名称<<<唯一>>>
    double strength; // 力量
    double agile; // 敏捷
    double intelligense; // 智力
};


// dota英雄表
class dotaherocfgmgr
{
public:
    // dota英雄表
    typedef std::map<dotaherocfg_t::id_t, dotaherocfg_t*> id2dotaherocfgmap; // 英雄ID -> dotaherocfg_t
    typedef std::map<dotaherocfg_t::name_t, dotaherocfg_t*> name2dotaherocfgmap; // 英雄名称 -> dotaherocfg_t
    typedef std::vector<dotaherocfg_t> dotaherocfgvec;

public:
	dotaherocfgmgr(){}
	~dotaherocfgmgr(){}

	static dotaherocfgmgr& instance(){
		static dotaherocfgmgr static_dotaherocfgmgr;
		return static_dotaherocfgmgr;
	}

private:
    dotaherocfgmgr& operator=(const dotaherocfgmgr&){ static dotaherocfgmgr mgr; return mgr; }
    dotaherocfgmgr (const dotaherocfgmgr&){}

public:
	// @impl 获取本配置类名称
	std::string mgr_name(){ return "dotaherocfg"; }

    // 获取xml文件路径
    std::string get_path(std::string xml){ return "../../xml/" + xml;}

public:
    // 载入dota英雄表
	virtual bool load();

    // 清空dota英雄表
    virtual void clear();

public:
    bool load_dotaherocfg();

public:
    void clear_dotaherocfg();

public:
    // dota英雄表
    const dotaherocfg_t* get_dotaherocfg_by_id(dotaherocfg_t::id_t id);
    const dotaherocfg_t* get_dotaherocfg_by_name(const char* name);
    const id2dotaherocfgmap& get_id2dotaherocfgmap(){ return m_id2dotaherocfgmap; }
    const name2dotaherocfgmap& get_name2dotaherocfgmap(){ return m_name2dotaherocfgmap; }
    const dotaherocfgvec& get_dotaherocfgvec(){ return m_dotaherocfgvec; }

public:
    // dota英雄表
    id2dotaherocfgmap m_id2dotaherocfgmap; // 英雄ID -> dotaherocfg
    name2dotaherocfgmap m_name2dotaherocfgmap; // 英雄名称 -> dotaherocfg
    dotaherocfgvec m_dotaherocfgvec;
};

#endif // _dotaherocfg_h_
```

<br>
<br>

						* 4.《dotaherocfg.cpp》
```cpp
///<------------------------------------------------------------------------------
//< @file:  dotaherocfg.cpp
//< @brief: dota英雄表
//< 本头文件由工具自动生成，请勿在本文件内做改动
//< @Copyright (c) 2014 tokit.
///<------------------------------------------------------------------------------

#include "dotaherocfg.h"

#include <iostream>
#include <string.h>
#include <rapidxml_utils.hpp>
#include "tokit_util.h"

dotaherocfg_t::dotaherocfg_t()
    : id(0)
    , name("")
    , strength(0)
    , agile(0)
    , intelligense(0)
{
}

std::string dotaherocfg_t::print() const
{
    char buf[2048];
    sprintf_s(buf, sizeof(buf), "id=%u name=%s strength=%lf agile=%lf intelligense=%lf"
        , id
        , name.c_str()
        , strength
        , agile
        , intelligense);

    return buf;
}

void dotaherocfgmgr::clear()
{
    clear_dotaherocfg();
}

bool dotaherocfgmgr::load()
{
	bool is_succ = true;
    is_succ &= load_dotaherocfg();
	return is_succ;
}


// dota英雄表
bool dotaherocfgmgr::load_dotaherocfg()
{
    tick_t load_tick;

    rapidxml::file<> fdoc(this->get_path("dotaherocfg.xml").c_str());
    rapidxml::xml_document<> doc;
    if(!fdoc.data()){
        std::cout << "err: load " << this->get_path("dotaherocfg.xml") << " failed, please check the file path" << std::endl;
        return false;
    }

    doc.parse<0>(fdoc.data());

    rapidxml::xml_node<>* root = doc.first_node();
    if(!root){
        std::cout << "err: parse <dotaherocfg.xml> failed, please check xml file format" << std::endl;
        return false;
    }

    clear_dotaherocfg();

    int n_row = 0;
    for(rapidxml::xml_node<> *node = root->first_node(); node; node = node->next_sibling()){
        ++n_row;
    }

    m_dotaherocfgvec.reserve(n_row);

    dotaherocfg_t cfg;
    for(rapidxml::xml_node<> *node = root->first_node(); node; node = node->next_sibling()){
        cfg.id = strutil::str_to_uint32(node->first_attribute("id")->value());
        cfg.name = strutil::un_escape_xml(node->first_attribute("name")->value());
        cfg.strength = atof(node->first_attribute("strength")->value());
        cfg.agile = atof(node->last_attribute("agile")->value());
        cfg.intelligense = atof(node->last_attribute("intelligense")->value());

        m_dotaherocfgvec.push_back(cfg);
        dotaherocfg_t* curcfg = &m_dotaherocfgvec.back();
    
        m_id2dotaherocfgmap[cfg.id] = curcfg;
        m_name2dotaherocfgmap[cfg.name] = curcfg;
    }

    printf("load <%-20s> success, cost time = <%-6f>s\n", "dotaherocfg.xml", load_tick.end_tick());
    return true;
}


void dotaherocfgmgr::clear_dotaherocfg()
{
    m_dotaherocfgvec.clear();
    m_id2dotaherocfgmap.clear();
    m_name2dotaherocfgmap.clear();
}

// dota英雄表
const dotaherocfg_t* dotaherocfgmgr::get_dotaherocfg_by_id(dotaherocfg_t::id_t id)
{
    id2dotaherocfgmap::iterator itr = m_id2dotaherocfgmap.find(id);
    if(itr == m_id2dotaherocfgmap.end()){
        return NULL;
    }

    dotaherocfg_t *cfg = itr->second;
    return cfg;
}

const dotaherocfg_t* dotaherocfgmgr::get_dotaherocfg_by_name(const char* name)
{
    name2dotaherocfgmap::iterator itr = m_name2dotaherocfgmap.find(name);
    if(itr == m_name2dotaherocfgmap.end()){
        return NULL;
    }

    dotaherocfg_t *cfg = itr->second;
    return cfg;
}
```


把自己的项目跟tokit对接后，载入`《dotaherocfg.xml》`文件的工作很简单，添加一行语句即可： 
```c++		
dotaherocfgmgr::instance().load();
```