///<------------------------------------------------------------------------------
//< @file:  dotaequipcfg.cpp
//< @brief: dota装备表, dota英雄表
//< 本头文件由工具自动生成，请勿在本文件内做改动
//< @Copyright (c) 2014 tokit.
///<------------------------------------------------------------------------------

#include "dotaequipcfg.h"

#include <iostream>
#include <string.h>
#include <rapidxml_utils.hpp>
#include "tokit_util.h"

dotaequipcfg_t::dotaequipcfg_t()
    : id(0)
    , name("")
    , desc("")
    , price(0)
    , isdrop(0)
    , attack(0)
{
}

dotaherocfg_t::dotaherocfg_t()
    : id(0)
    , name("")
    , strength(0)
    , agile(0)
    , intelligense(0)
{
}

void dotaequipcfgmgr::clear()
{
    clear_dotaequipcfg();
    clear_dotaherocfg();
}

bool dotaequipcfgmgr::load()
{
	bool is_succ = true;
    is_succ &= load_dotaequipcfg();
    is_succ &= load_dotaherocfg();
	return is_succ;
}


// dota装备表
bool dotaequipcfgmgr::load_dotaequipcfg()
{
    Tick tick_now = tickutil::get_tick();

    rapidxml::file<> fdoc(this->get_path("dotaequipcfg.xml").c_str());
    rapidxml::xml_document<> doc;
    if(!fdoc.data()){
        std::cout << "err: load <dotaequipcfg.xml> failed, please check the file path" << std::endl;
        return false;
    }

    doc.parse<0>(fdoc.data());

    rapidxml::xml_node<>* root = doc.first_node();
    if(!root){
        std::cout << "err: parse <dotaequipcfg.xml> failed, please check xml file format" << std::endl;
        return false;
    }

    clear_dotaequipcfg();

    int n_row = 0;
    for(rapidxml::xml_node<> *node = root->first_node(); node; node = node->next_sibling()){
        ++n_row;
    }

    m_dotaequipcfgvec.reserve(n_row);

    dotaequipcfg_t cfg;
    for(rapidxml::xml_node<> *node = root->first_node(); node; node = node->next_sibling()){
        cfg.id = strutil::str_to_uint32(node->first_attribute("id")->value());
        cfg.name = strutil::un_escape_xml(node->first_attribute("name")->value());
        cfg.desc = strutil::un_escape_xml(node->first_attribute("desc")->value());
        cfg.price = strutil::str_to_uint32(node->first_attribute("price")->value());
        cfg.isdrop = (node->last_attribute("isdrop")->value()[0] != '0');
        cfg.attack = strutil::str_to_int32(node->last_attribute("attack")->value());
        cfg.bornlist = strutil::split_str_to_vec<uint32>(node->last_attribute("bornlist")->value(), strutil::str_to_uint32);
        cfg.bornnum = strutil::split_str_to_vec<uint8>(node->last_attribute("bornnum")->value(), strutil::str_to_uint32);

        m_dotaequipcfgvec.push_back(cfg);
        dotaequipcfg_t* curcfg = &m_dotaequipcfgvec.back();
    
        m_id2dotaequipcfgmap[cfg.id] = curcfg;
        m_name2dotaequipcfgmap[cfg.name] = curcfg;
    }

    uint32_t passed_ms = tickutil::tick_diff(tick_now);
    double passed_sec = (double)passed_ms / 1000;

    printf("load <%-20s> success, cost time = <%-6f>s\n", "dotaequipcfg.xml", passed_sec);
    return true;
}

// dota英雄表
bool dotaequipcfgmgr::load_dotaherocfg()
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


void dotaequipcfgmgr::clear_dotaequipcfg()
{
    m_dotaequipcfgvec.clear();
    m_id2dotaequipcfgmap.clear();
    m_name2dotaequipcfgmap.clear();
}

void dotaequipcfgmgr::clear_dotaherocfg()
{
    m_dotaherocfgvec.clear();
    m_id2dotaherocfgmap.clear();
    m_name2dotaherocfgmap.clear();
}

// dota装备表
dotaequipcfg_t* dotaequipcfgmgr::get_dotaequipcfg_by_id(dotaequipcfg_t::id_t id)
{
    id2dotaequipcfgmap::iterator itr = m_id2dotaequipcfgmap.find(id);
    if(itr == m_id2dotaequipcfgmap.end()){
        return NULL;
    }

    dotaequipcfg_t *cfg = itr->second;
    return cfg;
}

dotaequipcfg_t* dotaequipcfgmgr::get_dotaequipcfg_by_name(const char* name)
{
    name2dotaequipcfgmap::iterator itr = m_name2dotaequipcfgmap.find(name);
    if(itr == m_name2dotaequipcfgmap.end()){
        return NULL;
    }

    dotaequipcfg_t *cfg = itr->second;
    return cfg;
}

// dota英雄表
dotaherocfg_t* dotaequipcfgmgr::get_dotaherocfg_by_id(dotaherocfg_t::id_t id)
{
    id2dotaherocfgmap::iterator itr = m_id2dotaherocfgmap.find(id);
    if(itr == m_id2dotaherocfgmap.end()){
        return NULL;
    }

    dotaherocfg_t *cfg = itr->second;
    return cfg;
}

dotaherocfg_t* dotaequipcfgmgr::get_dotaherocfg_by_name(const char* name)
{
    name2dotaherocfgmap::iterator itr = m_name2dotaherocfgmap.find(name);
    if(itr == m_name2dotaherocfgmap.end()){
        return NULL;
    }

    dotaherocfg_t *cfg = itr->second;
    return cfg;
}
