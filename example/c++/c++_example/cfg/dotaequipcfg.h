///<------------------------------------------------------------------------------
//< @file:  dotaequipcfg.h
//< @brief: dota装备表, dota英雄表
//< 本头文件由工具自动生成，请勿在本文件内做改动
//< @Copyright (c) 2014 tokit.
///<------------------------------------------------------------------------------

#ifndef _dotaequipcfg_h_
#define _dotaequipcfg_h_

#include <string>

#include <map>
#include <vector>
#include <set>

#include "type.h"

// dota装备表
struct dotaequipcfg_t{
    typedef uint32 id_t; // 物品ID<<<唯一>>>
    typedef std::string name_t; // 物品名称<<<唯一>>>
    typedef std::vector<uint32> bornlistvec_t; // 合成列表<<<数组>>>
    typedef std::vector<uint8> bornnumvec_t; // 合成数量<<<数组>>>

    dotaequipcfg_t();

    id_t id; // 物品ID<<<唯一>>>
    name_t name; // 物品名称<<<唯一>>>
    std::string desc; // 描述
    uint32 price; // 售出价格
    bool isdrop; // 是否死亡掉落
    int32 attack; // 攻击力
    bornlistvec_t bornlist; // 合成列表<<<数组>>>
    bornnumvec_t bornnum; // 合成数量<<<数组>>>
};

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


// dota装备表, dota英雄表
class dotaequipcfgmgr
{
public:
    // dota装备表
    typedef std::map<dotaequipcfg_t::id_t, dotaequipcfg_t*> id2dotaequipcfgmap; // 物品ID -> dotaequipcfg_t
    typedef std::map<dotaequipcfg_t::name_t, dotaequipcfg_t*> name2dotaequipcfgmap; // 物品名称 -> dotaequipcfg_t
    typedef std::vector<dotaequipcfg_t> dotaequipcfgvec;

    // dota英雄表
    typedef std::map<dotaherocfg_t::id_t, dotaherocfg_t*> id2dotaherocfgmap; // 英雄ID -> dotaherocfg_t
    typedef std::map<dotaherocfg_t::name_t, dotaherocfg_t*> name2dotaherocfgmap; // 英雄名称 -> dotaherocfg_t
    typedef std::vector<dotaherocfg_t> dotaherocfgvec;

public:
	dotaequipcfgmgr(){}
	~dotaequipcfgmgr(){}

	static dotaequipcfgmgr& instance(){
		static dotaequipcfgmgr static_dotaequipcfgmgr;
		return static_dotaequipcfgmgr;
	}

private:
    dotaequipcfgmgr& operator=(const dotaequipcfgmgr&){ static dotaequipcfgmgr mgr; return mgr; }
    dotaequipcfgmgr (const dotaequipcfgmgr&){}

public:
	// @impl 获取本配置类名称
	std::string mgr_name(){ return "dotaequipcfg"; }

    // 获取本配置所在路径
    std::string get_path(std::string xml){ return "../../xml/" + xml;}

public:
    // 载入dota装备表, dota英雄表
	virtual bool load();

    // 清空dota装备表, dota英雄表
    virtual void clear();

// 载入方法
public:
    bool load_dotaequipcfg();
    bool load_dotaherocfg();

// 清空方法
public:
    void clear_dotaequipcfg();
    void clear_dotaherocfg();

// 查找方法
public:
    // dota装备表
    dotaequipcfg_t* get_dotaequipcfg_by_id(dotaequipcfg_t::id_t id);
    dotaequipcfg_t* get_dotaequipcfg_by_name(const char* name);

    // dota英雄表
    dotaherocfg_t* get_dotaherocfg_by_id(dotaherocfg_t::id_t id);
    dotaherocfg_t* get_dotaherocfg_by_name(const char* name);

// 获取成员方法
public:
    // dota装备表
    const id2dotaequipcfgmap& get_id2dotaequipcfgmap(){ return m_id2dotaequipcfgmap; }
    const name2dotaequipcfgmap& get_name2dotaequipcfgmap(){ return m_name2dotaequipcfgmap; }
    const dotaequipcfgvec& get_dotaequipcfgvec(){ return m_dotaequipcfgvec; }

    // dota英雄表
    const id2dotaherocfgmap& get_id2dotaherocfgmap(){ return m_id2dotaherocfgmap; }
    const name2dotaherocfgmap& get_name2dotaherocfgmap(){ return m_name2dotaherocfgmap; }
    const dotaherocfgvec& get_dotaherocfgvec(){ return m_dotaherocfgvec; }

// 成员变量区
public:
    // dota装备表
    id2dotaequipcfgmap m_id2dotaequipcfgmap;
    name2dotaequipcfgmap m_name2dotaequipcfgmap;
    dotaequipcfgvec m_dotaequipcfgvec;

    // dota英雄表
    id2dotaherocfgmap m_id2dotaherocfgmap;
    name2dotaherocfgmap m_name2dotaherocfgmap;
    dotaherocfgvec m_dotaherocfgvec;
};

#endif // _dotaequipcfg_h_
