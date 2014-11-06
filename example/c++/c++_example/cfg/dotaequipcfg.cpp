///<------------------------------------------------------------------------------
//< @file:  dotaequipcfg.cpp
//< @brief: dota装备表, dota英雄表, dota技能表, dota怪物表
//< 本头文件由工具自动生成，请勿在本文件内做改动
//< @Copyright (c) 2014 tokit.
///<------------------------------------------------------------------------------

#include "dotaequipcfg.h"

#include <iostream>
#include <string.h>
#include <rapidxml_utils.hpp>
#include "tokit_tool.h"

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

dotaskillcfg_t::dotaskillcfg_t()
    : id(0)
    , name("")
    , strength(0)
    , agile(0)
    , intelligense(0)
{
}

dotamonstercfg_t::dotamonstercfg_t()
    : id(0)
    , name("")
    , strength(0)
    , agile(0)
    , intelligense(0)
{
}

std::string dotaequipcfg_t::print() const
{
    char buf[2048];
    snprintf(buf, sizeof(buf), "id=%u name=%s desc=%s price=%u isdrop=%u attack=%d "
        , id
        , name.c_str()
        , desc.c_str()
        , price
        , isdrop
        , attack);

    return buf;
}

std::string dotaherocfg_t::print() const
{
    char buf[2048];
    snprintf(buf, sizeof(buf), "id=%u name=%s strength=%lf agile=%lf intelligense=%lf"
        , id
        , name.c_str()
        , strength
        , agile
        , intelligense);

    return buf;
}

std::string dotaskillcfg_t::print() const
{
    char buf[2048];
    snprintf(buf, sizeof(buf), "id=%u name=%s strength=%lf agile=%lf intelligense=%lf"
        , id
        , name.c_str()
        , strength
        , agile
        , intelligense);

    return buf;
}

std::string dotamonstercfg_t::print() const
{
    char buf[2048];
    snprintf(buf, sizeof(buf), "id=%u name=%s strength=%lf agile=%lf intelligense=%lf"
        , id
        , name.c_str()
        , strength
        , agile
        , intelligense);

    return buf;
}

void dotaequipcfgmgr::clear()
{
    clear_dotaequipcfg();
    clear_dotaherocfg();
    clear_dotaskillcfg();
    clear_dotamonstercfg();
}

bool dotaequipcfgmgr::load()
{
	bool is_succ = true;
    is_succ &= load_dotaequipcfg();
    is_succ &= load_dotaherocfg();
    is_succ &= load_dotaskillcfg();
    is_succ &= load_dotamonstercfg();
	return is_succ;
}


// dota装备表
bool dotaequipcfgmgr::load_dotaequipcfg()
{
    tick_t load_tick;

    rapidxml::file<> fdoc(this->get_path("dotaequipcfg.xml").c_str());
    rapidxml::xml_document<> doc;
    if(!fdoc.data()){
        std::cout << "err: load " << this->get_path("dotaequipcfg.xml") << " failed, please check the file path" << std::endl;
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
        cfg.id = strtool::str_to_uint32(node->first_attribute("id")->value());
        cfg.name = strtool::un_escape_xml(node->first_attribute("name")->value());
        cfg.desc = strtool::un_escape_xml(node->first_attribute("desc")->value());
        cfg.price = strtool::str_to_uint32(node->first_attribute("price")->value());
        cfg.isdrop = (node->last_attribute("isdrop")->value()[0] != '0');
        cfg.attack = strtool::str_to_int32(node->last_attribute("attack")->value());
        cfg.bornlist = strtool::split_str_to_vec<uint32>(node->last_attribute("bornlist")->value(), strtool::str_to_uint32);
        cfg.bornnum = strtool::split_str_to_vec<uint8>(node->last_attribute("bornnum")->value(), strtool::str_to_uint32);

        m_dotaequipcfgvec.push_back(cfg);
        dotaequipcfg_t* curcfg = &m_dotaequipcfgvec.back();
    
        m_id2dotaequipcfgmap[cfg.id] = curcfg;
        m_name2dotaequipcfgmap[cfg.name] = curcfg;
    }

    printf("load <%-20s> success, cost time = <%-6f>s\n", "dotaequipcfg.xml", load_tick.end_tick());
    return true;
}

// dota英雄表
bool dotaequipcfgmgr::load_dotaherocfg()
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
        cfg.id = strtool::str_to_uint32(node->first_attribute("id")->value());
        cfg.name = strtool::un_escape_xml(node->first_attribute("name")->value());
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

// dota技能表
bool dotaequipcfgmgr::load_dotaskillcfg()
{
    tick_t load_tick;

    rapidxml::file<> fdoc(this->get_path("dotaskillcfg.xml").c_str());
    rapidxml::xml_document<> doc;
    if(!fdoc.data()){
        std::cout << "err: load " << this->get_path("dotaskillcfg.xml") << " failed, please check the file path" << std::endl;
        return false;
    }

    doc.parse<0>(fdoc.data());

    rapidxml::xml_node<>* root = doc.first_node();
    if(!root){
        std::cout << "err: parse <dotaskillcfg.xml> failed, please check xml file format" << std::endl;
        return false;
    }

    clear_dotaskillcfg();

    int n_row = 0;
    for(rapidxml::xml_node<> *node = root->first_node(); node; node = node->next_sibling()){
        ++n_row;
    }

    m_dotaskillcfgvec.reserve(n_row);

    dotaskillcfg_t cfg;
    for(rapidxml::xml_node<> *node = root->first_node(); node; node = node->next_sibling()){
        cfg.id = strtool::str_to_uint32(node->first_attribute("id")->value());
        cfg.name = strtool::un_escape_xml(node->first_attribute("name")->value());
        cfg.strength = atof(node->first_attribute("strength")->value());
        cfg.agile = atof(node->last_attribute("agile")->value());
        cfg.intelligense = atof(node->last_attribute("intelligense")->value());

        m_dotaskillcfgvec.push_back(cfg);
        dotaskillcfg_t* curcfg = &m_dotaskillcfgvec.back();
    
        m_id2dotaskillcfgmap[cfg.id] = curcfg;
        m_name2dotaskillcfgmap[cfg.name] = curcfg;
    }

    printf("load <%-20s> success, cost time = <%-6f>s\n", "dotaskillcfg.xml", load_tick.end_tick());
    return true;
}

// dota怪物表
bool dotaequipcfgmgr::load_dotamonstercfg()
{
    tick_t load_tick;

    rapidxml::file<> fdoc(this->get_path("dotamonstercfg.xml").c_str());
    rapidxml::xml_document<> doc;
    if(!fdoc.data()){
        std::cout << "err: load " << this->get_path("dotamonstercfg.xml") << " failed, please check the file path" << std::endl;
        return false;
    }

    doc.parse<0>(fdoc.data());

    rapidxml::xml_node<>* root = doc.first_node();
    if(!root){
        std::cout << "err: parse <dotamonstercfg.xml> failed, please check xml file format" << std::endl;
        return false;
    }

    clear_dotamonstercfg();

    int n_row = 0;
    for(rapidxml::xml_node<> *node = root->first_node(); node; node = node->next_sibling()){
        ++n_row;
    }

    m_dotamonstercfgvec.reserve(n_row);

    dotamonstercfg_t cfg;
    for(rapidxml::xml_node<> *node = root->first_node(); node; node = node->next_sibling()){
        cfg.id = strtool::str_to_uint32(node->first_attribute("id")->value());
        cfg.name = strtool::un_escape_xml(node->first_attribute("name")->value());
        cfg.strength = atof(node->first_attribute("strength")->value());
        cfg.agile = atof(node->last_attribute("agile")->value());
        cfg.intelligense = atof(node->last_attribute("intelligense")->value());

        m_dotamonstercfgvec.push_back(cfg);
        dotamonstercfg_t* curcfg = &m_dotamonstercfgvec.back();
    
        m_id2dotamonstercfgmap[cfg.id] = curcfg;
        m_name2dotamonstercfgmap[cfg.name] = curcfg;
    }

    printf("load <%-20s> success, cost time = <%-6f>s\n", "dotamonstercfg.xml", load_tick.end_tick());
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

void dotaequipcfgmgr::clear_dotaskillcfg()
{
    m_dotaskillcfgvec.clear();
    m_id2dotaskillcfgmap.clear();
    m_name2dotaskillcfgmap.clear();
}

void dotaequipcfgmgr::clear_dotamonstercfg()
{
    m_dotamonstercfgvec.clear();
    m_id2dotamonstercfgmap.clear();
    m_name2dotamonstercfgmap.clear();
}

// dota装备表
const dotaequipcfg_t* dotaequipcfgmgr::get_dotaequipcfg_by_id(dotaequipcfg_t::id_t id)
{
    id2dotaequipcfgmap::iterator itr = m_id2dotaequipcfgmap.find(id);
    if(itr == m_id2dotaequipcfgmap.end()){
        return NULL;
    }

    dotaequipcfg_t *cfg = itr->second;
    return cfg;
}

const dotaequipcfg_t* dotaequipcfgmgr::get_dotaequipcfg_by_name(const char* name)
{
    name2dotaequipcfgmap::iterator itr = m_name2dotaequipcfgmap.find(name);
    if(itr == m_name2dotaequipcfgmap.end()){
        return NULL;
    }

    dotaequipcfg_t *cfg = itr->second;
    return cfg;
}

// dota英雄表
const dotaherocfg_t* dotaequipcfgmgr::get_dotaherocfg_by_id(dotaherocfg_t::id_t id)
{
    id2dotaherocfgmap::iterator itr = m_id2dotaherocfgmap.find(id);
    if(itr == m_id2dotaherocfgmap.end()){
        return NULL;
    }

    dotaherocfg_t *cfg = itr->second;
    return cfg;
}

const dotaherocfg_t* dotaequipcfgmgr::get_dotaherocfg_by_name(const char* name)
{
    name2dotaherocfgmap::iterator itr = m_name2dotaherocfgmap.find(name);
    if(itr == m_name2dotaherocfgmap.end()){
        return NULL;
    }

    dotaherocfg_t *cfg = itr->second;
    return cfg;
}

// dota技能表
const dotaskillcfg_t* dotaequipcfgmgr::get_dotaskillcfg_by_id(dotaskillcfg_t::id_t id)
{
    id2dotaskillcfgmap::iterator itr = m_id2dotaskillcfgmap.find(id);
    if(itr == m_id2dotaskillcfgmap.end()){
        return NULL;
    }

    dotaskillcfg_t *cfg = itr->second;
    return cfg;
}

const dotaskillcfg_t* dotaequipcfgmgr::get_dotaskillcfg_by_name(const char* name)
{
    name2dotaskillcfgmap::iterator itr = m_name2dotaskillcfgmap.find(name);
    if(itr == m_name2dotaskillcfgmap.end()){
        return NULL;
    }

    dotaskillcfg_t *cfg = itr->second;
    return cfg;
}

// dota怪物表
const dotamonstercfg_t* dotaequipcfgmgr::get_dotamonstercfg_by_id(dotamonstercfg_t::id_t id)
{
    id2dotamonstercfgmap::iterator itr = m_id2dotamonstercfgmap.find(id);
    if(itr == m_id2dotamonstercfgmap.end()){
        return NULL;
    }

    dotamonstercfg_t *cfg = itr->second;
    return cfg;
}

const dotamonstercfg_t* dotaequipcfgmgr::get_dotamonstercfg_by_name(const char* name)
{
    name2dotamonstercfgmap::iterator itr = m_name2dotamonstercfgmap.find(name);
    if(itr == m_name2dotamonstercfgmap.end()){
        return NULL;
    }

    dotamonstercfg_t *cfg = itr->second;
    return cfg;
}
