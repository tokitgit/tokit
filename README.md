tokit
=====

tokit是一个用于方便网游研发人员配置数据的工具。可以根据一份符合tokit格式的excel文件，生成对应的xml、xsd以及c++文件。其中c++文件中含有自动读取xml数据的接口以及查找接口。

## 使用过程

* 1. 策划在excel中编辑完数据后
* 2. 程序人员在同一个excel中编辑好字段定义，使其符合tokit格式
* 3. 使用tokit从excel中生成c++代码，并导出xml数据文件和xsd文件。

详细步骤可见目录下的《Tokit使用手册.pdf》。

## 下载之后

下载tokit整个项目之后，运行example目录下的《一键生成.bat》脚本，该脚本将根据example\excel中的各个excel文件，生成对应的xml、xsd、c++文件。

参考example\c++\c++_example.sln项目和《Tokit使用手册.pdf》，将tokit接入你自己的c++项目

## 示例


为了更快的了解tokit，现在把tokit生成的文件全部贴出来。


假设现在有一个excel文件《dota英雄表.xlsx》，里面的内容是


							《dota英雄表.xlsx》
	-----------------------------------------------------------------
    程序英文名      最多有几条数据（0表示不限）
    dotaherocfg     0
    
    id              name        strength    agile       intelligense
    uint            string      double      double      double
    唯一            唯一

    英雄ID          英雄名称    力量        敏捷        智力
    1               小黑        10.5        20.00001    301.1111
    2               风行        10.5        20.00001    301.1111
    3               凤凰        10.5        20.00001    301.1111
    4               斧王        10.5        20.00001    301.1111
    5               宙斯        10.5        20.00001    301.1111
    6               虚空        10.5        20.00001    301.1111
    7               猴子        10.5        20.00001    301.1111
	-----------------------------------------------------------------



则使用tokit之后，将生成xml、xsd和c++文件



						* 1.《dotaherocfg.xml》
	-----------------------------------------------------------------
	<dotaherocfg xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
	    <row id="1" name="小黑" strength="11" agile="20" intelligense="301"/>
	    <row id="2" name="风行" strength="11" agile="20" intelligense="301"/>
	    <row id="3" name="凤凰" strength="11" agile="20" intelligense="301"/>
	    <row id="4" name="斧王" strength="11" agile="20" intelligense="301"/>
	    <row id="5" name="宙斯" strength="11" agile="20" intelligense="301"/>
	    <row id="6" name="虚空" strength="11" agile="20" intelligense="301"/>
	    <row id="7" name="猴子" strength="11" agile="20" intelligense="301"/>
	</dotaherocfg>
	-----------------------------------------------------------------



						* 2.《dota装备表.xsd》
	-----------------------------------------------------------------
	<?xml version="1.0" encoding="UTF-8"?>
	<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema">
	<xs:element name="dotaherocfgs">
	  <xs:complexType>
	    <xs:sequence minOccurs="0" maxOccurs="unbounded">
	      <xs:element name="dotaherocfg">
	        <xs:complexType>
	          <xs:sequence>
	            <xs:attribute name="id" type="xs:unsignedInt"/>
	            <xs:attribute name="name" type="xs:string"/>
	            <xs:attribute name="strength" type="xs:double"/>
	            <xs:attribute name="agile" type="xs:double"/>
	            <xs:attribute name="intelligense" type="xs:double"/>
	          </xs:sequence>
	        </xs:complexType>
	      </xs:element>
	    </xs:sequence>
	  </xs:complexType>
	</xs:element>
	</xs:schema>
	-----------------------------------------------------------------



						* 3.《dotaherocfg.h》
	-----------------------------------------------------------------
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

	    // 获取本配置所在路径
	    std::string get_path(std::string xml){ return "../../xml/" + xml;}

	public:
	    // 载入dota英雄表
		virtual bool load();

	    // 清空dota英雄表
	    virtual void clear();

	// 载入方法
	public:
	    bool load_dotaherocfg();

	// 清空方法
	public:
	    void clear_dotaherocfg();

	// 查找方法
	public:
	    // dota英雄表
	    dotaherocfg_t* get_dotaherocfg_by_id(dotaherocfg_t::id_t id);
	    dotaherocfg_t* get_dotaherocfg_by_name(const char* name);

	// 获取成员方法
	public:
	    // dota英雄表
	    const id2dotaherocfgmap& get_id2dotaherocfgmap(){ return m_id2dotaherocfgmap; }
	    const name2dotaherocfgmap& get_name2dotaherocfgmap(){ return m_name2dotaherocfgmap; }
	    const dotaherocfgvec& get_dotaherocfgvec(){ return m_dotaherocfgvec; }

	// 成员变量区
	public:
	    // dota英雄表
	    id2dotaherocfgmap m_id2dotaherocfgmap;
	    name2dotaherocfgmap m_name2dotaherocfgmap;
	    dotaherocfgvec m_dotaherocfgvec;
	};

	#endif // _dotaherocfg_h_
	-----------------------------------------------------------------


							
						* 4.《dotaherocfg.cpp》
	-----------------------------------------------------------------
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
	    Tick tick_now = tickutil::get_tick();

	    rapidxml::file<> fdoc(this->get_path("dotaherocfg.xml").c_str());
	    rapidxml::xml_document<> doc;
	    if(!fdoc.data()){
	        std::cout << "err: load <dotaherocfg.xml> failed, please check the file path" << std::endl;
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

	    uint32_t passed_ms = tickutil::tick_diff(tick_now);
	    double passed_sec = (double)passed_ms / 1000;

	    printf("load <%-20s> success, cost time = <%-6f>s\n", "dotaherocfg.xml", passed_sec);
	    return true;
	}


	void dotaherocfgmgr::clear_dotaherocfg()
	{
	    m_dotaherocfgvec.clear();
	    m_id2dotaherocfgmap.clear();
	    m_name2dotaherocfgmap.clear();
	}

	// dota英雄表
	dotaherocfg_t* dotaherocfgmgr::get_dotaherocfg_by_id(dotaherocfg_t::id_t id)
	{
	    id2dotaherocfgmap::iterator itr = m_id2dotaherocfgmap.find(id);
	    if(itr == m_id2dotaherocfgmap.end()){
	        return NULL;
	    }

	    dotaherocfg_t *cfg = itr->second;
	    return cfg;
	}

	dotaherocfg_t* dotaherocfgmgr::get_dotaherocfg_by_name(const char* name)
	{
	    name2dotaherocfgmap::iterator itr = m_name2dotaherocfgmap.find(name);
	    if(itr == m_name2dotaherocfgmap.end()){
	        return NULL;
	    }

	    dotaherocfg_t *cfg = itr->second;
	    return cfg;
	}
	-----------------------------------------------------------------



把自己的项目跟tokit对接后，载入《dotaherocfg.xml》文件的工作很简单，添加一行语句即可： dotaherocfgmgr::instance().load();