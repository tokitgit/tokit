///<------------------------------------------------------------------------------
//< @file:   language\xml\xml_generator.h
//< @author: 洪坤安
//< @date:   2014年9月25日 15:49:5
//< @brief:  导出xml数据
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _xml_generator_h_
#define _xml_generator_h_

#include <string>
#include "generator.h"

using std::string;

class xml_generator : public generator
{
public:
    xml_generator(cfgbase_t &cfgbase, const string &xml_dir)
        : generator(cfgbase)
        , m_xml_dir(xml_dir)
    {
    }

public:
    // @impl
    virtual bool generate();

private:
    // 将excel中各个工作表导出到对应的xml文件
    bool save_as_xml();

private:
    std::string m_xml_dir;
};

#endif //_xml_generator_h_