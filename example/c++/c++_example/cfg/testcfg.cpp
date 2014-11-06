///<------------------------------------------------------------------------------
//< @file:  testcfg.cpp
//< @brief: 测试用例表
//< 本头文件由工具自动生成，请勿在本文件内做改动
//< @Copyright (c) 2014 tokit.
///<------------------------------------------------------------------------------

#include "testcfg.h"

#include <iostream>
#include <string.h>
#include <rapidxml_utils.hpp>
#include "tokit_tool.h"

testcfg_t::testcfg_t()
    : stringfield("")
    , boolfield(0)
    , charfield(0)
    , int16field(0)
    , intfield(0)
    , int64field(0)
    , uint8field(0)
    , uint16field(0)
    , uintfield(0)
    , uint64field(0)
    , floatfield(0)
    , doublefield(0)
    , stringfieldprimary("")
    , boolfieldprimary(0)
    , charfieldprimary(0)
    , int16fieldprimary(0)
    , intfieldprimary(0)
    , int64fieldprimary(0)
    , uint8fieldprimary(0)
    , uint16fieldprimary(0)
    , uintfieldprimary(0)
    , uint64fieldprimary(0)
    , floatfieldprimary(0)
    , doublefieldprimary(0)
    , stringfieldunique("")
    , boolfieldunique(0)
    , charfieldunique(0)
    , int16fieldunique(0)
    , intfieldunique(0)
    , int64fieldunique(0)
    , uint8fieldunique(0)
    , uint16fieldunique(0)
    , uintfieldunique(0)
    , uint64fieldunique(0)
    , floatfieldunique(0)
    , doublefieldunique(0)
{
}

std::string testcfg_t::print() const
{
    char buf[2048];
    snprintf(buf, sizeof(buf), "stringfield=%s boolfield=%u charfield=%d int16field=%d intfield=%d int64field="I64d" uint8field=%u uint16field=%u uintfield=%u uint64field="I64u" floatfield=%f "
        "doublefield=%lf stringfieldprimary=%s boolfieldprimary=%u charfieldprimary=%d int16fieldprimary=%d intfieldprimary=%d int64fieldprimary="I64d" uint8fieldprimary=%u uint16fieldprimary=%u uintfieldprimary=%u "
        "uint64fieldprimary="I64u" floatfieldprimary=%f doublefieldprimary=%lf stringfieldunique=%s boolfieldunique=%u charfieldunique=%d int16fieldunique=%d intfieldunique=%d int64fieldunique="I64d" uint8fieldunique=%u "
        "uint16fieldunique=%u uintfieldunique=%u uint64fieldunique="I64u" floatfieldunique=%f doublefieldunique=%lf "
        , stringfield.c_str()
        , boolfield
        , charfield
        , int16field
        , intfield
        , int64field
        , uint8field
        , uint16field
        , uintfield
        , uint64field
        , floatfield
        , doublefield
        , stringfieldprimary.c_str()
        , boolfieldprimary
        , charfieldprimary
        , int16fieldprimary
        , intfieldprimary
        , int64fieldprimary
        , uint8fieldprimary
        , uint16fieldprimary
        , uintfieldprimary
        , uint64fieldprimary
        , floatfieldprimary
        , doublefieldprimary
        , stringfieldunique.c_str()
        , boolfieldunique
        , charfieldunique
        , int16fieldunique
        , intfieldunique
        , int64fieldunique
        , uint8fieldunique
        , uint16fieldunique
        , uintfieldunique
        , uint64fieldunique
        , floatfieldunique
        , doublefieldunique);

    return buf;
}

void testcfgmgr::clear()
{
    clear_testcfg();
}

bool testcfgmgr::load()
{
	bool is_succ = true;
    is_succ &= load_testcfg();
	return is_succ;
}


// 测试用例表
bool testcfgmgr::load_testcfg()
{
    tick_t load_tick;

    rapidxml::file<> fdoc(this->get_path("testcfg.xml").c_str());
    rapidxml::xml_document<> doc;
    if(!fdoc.data()){
        std::cout << "err: load " << this->get_path("testcfg.xml") << " failed, please check the file path" << std::endl;
        return false;
    }

    doc.parse<0>(fdoc.data());

    rapidxml::xml_node<>* root = doc.first_node();
    if(!root){
        std::cout << "err: parse <testcfg.xml> failed, please check xml file format" << std::endl;
        return false;
    }

    clear_testcfg();

    int n_row = 0;
    for(rapidxml::xml_node<> *node = root->first_node(); node; node = node->next_sibling()){
        ++n_row;
    }

    m_testcfgvec.reserve(n_row);

    testcfg_t cfg;
    for(rapidxml::xml_node<> *node = root->first_node(); node; node = node->next_sibling()){
        cfg.stringfield = strtool::un_escape_xml(node->first_attribute("stringfield")->value());
        cfg.boolfield = (node->first_attribute("boolfield")->value()[0] != '0');
        cfg.charfield = strtool::str_to_int32(node->first_attribute("charfield")->value());
        cfg.int16field = strtool::str_to_int32(node->first_attribute("int16field")->value());
        cfg.intfield = strtool::str_to_int32(node->first_attribute("intfield")->value());
        cfg.int64field = strtool::str_to_int64(node->first_attribute("int64field")->value());
        cfg.uint8field = strtool::str_to_uint32(node->first_attribute("uint8field")->value());
        cfg.uint16field = strtool::str_to_uint32(node->first_attribute("uint16field")->value());
        cfg.uintfield = strtool::str_to_uint32(node->first_attribute("uintfield")->value());
        cfg.uint64field = strtool::str_to_uint64(node->first_attribute("uint64field")->value());
        cfg.floatfield = (float)atof(node->first_attribute("floatfield")->value());
        cfg.doublefield = atof(node->first_attribute("doublefield")->value());
        cfg.stringfieldprimary = strtool::un_escape_xml(node->first_attribute("stringfieldprimary")->value());
        cfg.boolfieldprimary = (node->first_attribute("boolfieldprimary")->value()[0] != '0');
        cfg.charfieldprimary = strtool::str_to_int32(node->first_attribute("charfieldprimary")->value());
        cfg.int16fieldprimary = strtool::str_to_int32(node->first_attribute("int16fieldprimary")->value());
        cfg.intfieldprimary = strtool::str_to_int32(node->first_attribute("intfieldprimary")->value());
        cfg.int64fieldprimary = strtool::str_to_int64(node->first_attribute("int64fieldprimary")->value());
        cfg.uint8fieldprimary = strtool::str_to_uint32(node->first_attribute("uint8fieldprimary")->value());
        cfg.uint16fieldprimary = strtool::str_to_uint32(node->first_attribute("uint16fieldprimary")->value());
        cfg.uintfieldprimary = strtool::str_to_uint32(node->first_attribute("uintfieldprimary")->value());
        cfg.uint64fieldprimary = strtool::str_to_uint64(node->first_attribute("uint64fieldprimary")->value());
        cfg.floatfieldprimary = (float)atof(node->first_attribute("floatfieldprimary")->value());
        cfg.doublefieldprimary = atof(node->first_attribute("doublefieldprimary")->value());
        cfg.stringfieldunique = strtool::un_escape_xml(node->first_attribute("stringfieldunique")->value());
        cfg.boolfieldunique = (node->first_attribute("boolfieldunique")->value()[0] != '0');
        cfg.charfieldunique = strtool::str_to_int32(node->first_attribute("charfieldunique")->value());
        cfg.int16fieldunique = strtool::str_to_int32(node->first_attribute("int16fieldunique")->value());
        cfg.intfieldunique = strtool::str_to_int32(node->first_attribute("intfieldunique")->value());
        cfg.int64fieldunique = strtool::str_to_int64(node->first_attribute("int64fieldunique")->value());
        cfg.uint8fieldunique = strtool::str_to_uint32(node->last_attribute("uint8fieldunique")->value());
        cfg.uint16fieldunique = strtool::str_to_uint32(node->last_attribute("uint16fieldunique")->value());
        cfg.uintfieldunique = strtool::str_to_uint32(node->last_attribute("uintfieldunique")->value());
        cfg.uint64fieldunique = strtool::str_to_uint64(node->last_attribute("uint64fieldunique")->value());
        cfg.floatfieldunique = (float)atof(node->last_attribute("floatfieldunique")->value());
        cfg.doublefieldunique = atof(node->last_attribute("doublefieldunique")->value());
        cfg.stringfieldarray = strtool::split(node->last_attribute("stringfieldarray")->value());
        cfg.boolfieldarray = strtool::split_str_to_vec<bool>(node->last_attribute("boolfieldarray")->value(), strtool::str_to_bool);
        cfg.charfieldarray = strtool::split_str_to_vec<char>(node->last_attribute("charfieldarray")->value(), strtool::str_to_int32);
        cfg.int16fieldarray = strtool::split_str_to_vec<int16>(node->last_attribute("int16fieldarray")->value(), strtool::str_to_int32);
        cfg.intfieldarray = strtool::split_str_to_vec<int32>(node->last_attribute("intfieldarray")->value(), strtool::str_to_int32);
        cfg.int64fieldarray = strtool::split_str_to_vec<int64>(node->last_attribute("int64fieldarray")->value(), strtool::str_to_int64);
        cfg.uint8fieldarray = strtool::split_str_to_vec<uint8>(node->last_attribute("uint8fieldarray")->value(), strtool::str_to_uint32);
        cfg.uint16fieldarray = strtool::split_str_to_vec<uint16>(node->last_attribute("uint16fieldarray")->value(), strtool::str_to_uint32);
        cfg.uintfieldarray = strtool::split_str_to_vec<uint32>(node->last_attribute("uintfieldarray")->value(), strtool::str_to_uint32);
        cfg.uint64fieldarray = strtool::split_str_to_vec<uint64>(node->last_attribute("uint64fieldarray")->value(), strtool::str_to_uint64);
        cfg.floatfieldarray = strtool::split_str_to_vec<float>(node->last_attribute("floatfieldarray")->value(), atof);
        cfg.doublefieldarray = strtool::split_str_to_vec<double>(node->last_attribute("doublefieldarray")->value(), atof);
        cfg.stringfieldset = strtool::split_str_set(node->last_attribute("stringfieldset")->value());
        cfg.boolfieldset = strtool::split_str_to_set<bool>(node->last_attribute("boolfieldset")->value(), strtool::str_to_bool);
        cfg.charfieldset = strtool::split_str_to_set<char>(node->last_attribute("charfieldset")->value(), strtool::str_to_int32);
        cfg.int16fieldset = strtool::split_str_to_set<int16>(node->last_attribute("int16fieldset")->value(), strtool::str_to_int32);
        cfg.intfieldset = strtool::split_str_to_set<int32>(node->last_attribute("intfieldset")->value(), strtool::str_to_int32);
        cfg.int64fieldset = strtool::split_str_to_set<int64>(node->last_attribute("int64fieldset")->value(), strtool::str_to_int64);
        cfg.uint8fieldset = strtool::split_str_to_set<uint8>(node->last_attribute("uint8fieldset")->value(), strtool::str_to_uint32);
        cfg.uint16fieldset = strtool::split_str_to_set<uint16>(node->last_attribute("uint16fieldset")->value(), strtool::str_to_uint32);
        cfg.uintfieldset = strtool::split_str_to_set<uint32>(node->last_attribute("uintfieldset")->value(), strtool::str_to_uint32);
        cfg.uint64fieldset = strtool::split_str_to_set<uint64>(node->last_attribute("uint64fieldset")->value(), strtool::str_to_uint64);
        cfg.floatfieldset = strtool::split_str_to_set<float>(node->last_attribute("floatfieldset")->value(), atof);
        cfg.doublefieldset = strtool::split_str_to_set<double>(node->last_attribute("doublefieldset")->value(), atof);

        m_testcfgvec.push_back(cfg);
        testcfg_t* curcfg = &m_testcfgvec.back();
    
        std::string key = cfg.stringfieldprimary + strtool::tostr(cfg.boolfieldprimary) + strtool::tostr(cfg.charfieldprimary) + strtool::tostr(cfg.int16fieldprimary) + strtool::tostr(cfg.intfieldprimary) + strtool::tostr(cfg.int64fieldprimary) + strtool::tostr(cfg.uint8fieldprimary) + strtool::tostr(cfg.uint16fieldprimary) + strtool::tostr(cfg.uintfieldprimary) + strtool::tostr(cfg.uint64fieldprimary);
        m_testcfgmap[key] = curcfg;

        m_stringfieldunique2testcfgmap[cfg.stringfieldunique] = curcfg;
        m_boolfieldunique2testcfgmap[cfg.boolfieldunique] = curcfg;
        m_charfieldunique2testcfgmap[cfg.charfieldunique] = curcfg;
        m_int16fieldunique2testcfgmap[cfg.int16fieldunique] = curcfg;
        m_intfieldunique2testcfgmap[cfg.intfieldunique] = curcfg;
        m_int64fieldunique2testcfgmap[cfg.int64fieldunique] = curcfg;
        m_uint8fieldunique2testcfgmap[cfg.uint8fieldunique] = curcfg;
        m_uint16fieldunique2testcfgmap[cfg.uint16fieldunique] = curcfg;
        m_uintfieldunique2testcfgmap[cfg.uintfieldunique] = curcfg;
        m_uint64fieldunique2testcfgmap[cfg.uint64fieldunique] = curcfg;
        m_floatfieldunique2testcfgmap[cfg.floatfieldunique] = curcfg;
        m_doublefieldunique2testcfgmap[cfg.doublefieldunique] = curcfg;
    }

    printf("load <%-20s> success, cost time = <%-6f>s\n", "testcfg.xml", load_tick.end_tick());
    return true;
}


void testcfgmgr::clear_testcfg()
{
    m_testcfgvec.clear();
    m_testcfgmap.clear();
    m_stringfieldunique2testcfgmap.clear();
    m_boolfieldunique2testcfgmap.clear();
    m_charfieldunique2testcfgmap.clear();
    m_int16fieldunique2testcfgmap.clear();
    m_intfieldunique2testcfgmap.clear();
    m_int64fieldunique2testcfgmap.clear();
    m_uint8fieldunique2testcfgmap.clear();
    m_uint16fieldunique2testcfgmap.clear();
    m_uintfieldunique2testcfgmap.clear();
    m_uint64fieldunique2testcfgmap.clear();
    m_floatfieldunique2testcfgmap.clear();
    m_doublefieldunique2testcfgmap.clear();
}

// 测试用例表
const testcfg_t* testcfgmgr::get_testcfg(const char* stringfieldprimary, testcfg_t::boolfieldprimary_t boolfieldprimary, testcfg_t::charfieldprimary_t charfieldprimary, testcfg_t::int16fieldprimary_t int16fieldprimary, testcfg_t::intfieldprimary_t intfieldprimary, testcfg_t::int64fieldprimary_t int64fieldprimary, testcfg_t::uint8fieldprimary_t uint8fieldprimary, testcfg_t::uint16fieldprimary_t uint16fieldprimary, testcfg_t::uintfieldprimary_t uintfieldprimary, testcfg_t::uint64fieldprimary_t uint64fieldprimary)
{
    std::string key = stringfieldprimary + strtool::tostr(boolfieldprimary) + strtool::tostr(charfieldprimary) + strtool::tostr(int16fieldprimary) + strtool::tostr(intfieldprimary) + strtool::tostr(int64fieldprimary) + strtool::tostr(uint8fieldprimary) + strtool::tostr(uint16fieldprimary) + strtool::tostr(uintfieldprimary) + strtool::tostr(uint64fieldprimary);
    testcfgmap::iterator itr = m_testcfgmap.find(key);
    if(itr == m_testcfgmap.end()){
        return NULL;
    }

    testcfg_t *cfg = itr->second;
    return cfg;
}

const testcfg_t* testcfgmgr::get_testcfg_by_stringfieldunique(const char* stringfieldunique)
{
    stringfieldunique2testcfgmap::iterator itr = m_stringfieldunique2testcfgmap.find(stringfieldunique);
    if(itr == m_stringfieldunique2testcfgmap.end()){
        return NULL;
    }

    testcfg_t *cfg = itr->second;
    return cfg;
}

const testcfg_t* testcfgmgr::get_testcfg_by_boolfieldunique(testcfg_t::boolfieldunique_t boolfieldunique)
{
    boolfieldunique2testcfgmap::iterator itr = m_boolfieldunique2testcfgmap.find(boolfieldunique);
    if(itr == m_boolfieldunique2testcfgmap.end()){
        return NULL;
    }

    testcfg_t *cfg = itr->second;
    return cfg;
}

const testcfg_t* testcfgmgr::get_testcfg_by_charfieldunique(testcfg_t::charfieldunique_t charfieldunique)
{
    charfieldunique2testcfgmap::iterator itr = m_charfieldunique2testcfgmap.find(charfieldunique);
    if(itr == m_charfieldunique2testcfgmap.end()){
        return NULL;
    }

    testcfg_t *cfg = itr->second;
    return cfg;
}

const testcfg_t* testcfgmgr::get_testcfg_by_int16fieldunique(testcfg_t::int16fieldunique_t int16fieldunique)
{
    int16fieldunique2testcfgmap::iterator itr = m_int16fieldunique2testcfgmap.find(int16fieldunique);
    if(itr == m_int16fieldunique2testcfgmap.end()){
        return NULL;
    }

    testcfg_t *cfg = itr->second;
    return cfg;
}

const testcfg_t* testcfgmgr::get_testcfg_by_intfieldunique(testcfg_t::intfieldunique_t intfieldunique)
{
    intfieldunique2testcfgmap::iterator itr = m_intfieldunique2testcfgmap.find(intfieldunique);
    if(itr == m_intfieldunique2testcfgmap.end()){
        return NULL;
    }

    testcfg_t *cfg = itr->second;
    return cfg;
}

const testcfg_t* testcfgmgr::get_testcfg_by_int64fieldunique(testcfg_t::int64fieldunique_t int64fieldunique)
{
    int64fieldunique2testcfgmap::iterator itr = m_int64fieldunique2testcfgmap.find(int64fieldunique);
    if(itr == m_int64fieldunique2testcfgmap.end()){
        return NULL;
    }

    testcfg_t *cfg = itr->second;
    return cfg;
}

const testcfg_t* testcfgmgr::get_testcfg_by_uint8fieldunique(testcfg_t::uint8fieldunique_t uint8fieldunique)
{
    uint8fieldunique2testcfgmap::iterator itr = m_uint8fieldunique2testcfgmap.find(uint8fieldunique);
    if(itr == m_uint8fieldunique2testcfgmap.end()){
        return NULL;
    }

    testcfg_t *cfg = itr->second;
    return cfg;
}

const testcfg_t* testcfgmgr::get_testcfg_by_uint16fieldunique(testcfg_t::uint16fieldunique_t uint16fieldunique)
{
    uint16fieldunique2testcfgmap::iterator itr = m_uint16fieldunique2testcfgmap.find(uint16fieldunique);
    if(itr == m_uint16fieldunique2testcfgmap.end()){
        return NULL;
    }

    testcfg_t *cfg = itr->second;
    return cfg;
}

const testcfg_t* testcfgmgr::get_testcfg_by_uintfieldunique(testcfg_t::uintfieldunique_t uintfieldunique)
{
    uintfieldunique2testcfgmap::iterator itr = m_uintfieldunique2testcfgmap.find(uintfieldunique);
    if(itr == m_uintfieldunique2testcfgmap.end()){
        return NULL;
    }

    testcfg_t *cfg = itr->second;
    return cfg;
}

const testcfg_t* testcfgmgr::get_testcfg_by_uint64fieldunique(testcfg_t::uint64fieldunique_t uint64fieldunique)
{
    uint64fieldunique2testcfgmap::iterator itr = m_uint64fieldunique2testcfgmap.find(uint64fieldunique);
    if(itr == m_uint64fieldunique2testcfgmap.end()){
        return NULL;
    }

    testcfg_t *cfg = itr->second;
    return cfg;
}

const testcfg_t* testcfgmgr::get_testcfg_by_floatfieldunique(testcfg_t::floatfieldunique_t floatfieldunique)
{
    floatfieldunique2testcfgmap::iterator itr = m_floatfieldunique2testcfgmap.find(floatfieldunique);
    if(itr == m_floatfieldunique2testcfgmap.end()){
        return NULL;
    }

    testcfg_t *cfg = itr->second;
    return cfg;
}

const testcfg_t* testcfgmgr::get_testcfg_by_doublefieldunique(testcfg_t::doublefieldunique_t doublefieldunique)
{
    doublefieldunique2testcfgmap::iterator itr = m_doublefieldunique2testcfgmap.find(doublefieldunique);
    if(itr == m_doublefieldunique2testcfgmap.end()){
        return NULL;
    }

    testcfg_t *cfg = itr->second;
    return cfg;
}
