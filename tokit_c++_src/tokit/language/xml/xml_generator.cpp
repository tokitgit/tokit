///<------------------------------------------------------------------------------
//< @file:   language\xml\xml_generator.cpp
//< @author: 洪坤安
//< @date:   2014年9月25日 15:49:16
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include "xml_generator.h"

#include <fstream>
#include <iostream>

#include "cfg.h"
#include "file_tool.h"
#include "str_tool.h"
#include "echo_tool.h"
#include "tick_tool.h"

#include "parser.h"

namespace xmltool{
    // 转码:
    //     1. 引号 -> &quot;
    void escape_xml(string &str)
    {
        strtool::replace(str, "\"", "&quot;");
    }

    // 将数据拼接成xml格式
    void slice_xml_text(const cfg_t &cfg, std::string &xml_text)
    {
        const fieldvec_t &fields = cfg.fields;
        table_t &table = *(const_cast<table_t*>(&cfg.table));

        xml_text = "<" + cfg.en_name + " xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n";
        xml_text.reserve(cfg.table.size() * fields.size() * 15);

        string row_text;
        for(size_t r = 0; r < cfg.table.size(); r++){
            row_t &row = table[r];

            // 将数据拼接成形如<row a="a1" b="b1" c="c1"....>的xml文本
            row_text = "    <row";
            for(size_t c = 0; c < fields.size(); c++){
                escape_xml(row[c]);
                row_text += " " + cfg.fields[c].en_name + "=\"" + row[c] + "\"";
            }

            row_text += "/>\n";
            xml_text += row_text;
        }

        xml_text += "</" + cfg.en_name + ">";
    }
};

bool xml_generator::generate()
{
    if(false == filetool::exist(m_xml_dir)){
        ECHO_ERR("错误: <%s>路径不存在", m_xml_dir.c_str());
        return false;
    }

    return save_as_xml();
}

bool xml_generator::save_as_xml()
{

    // 将excel中各个工作表数据导出到对应的xml文件中
    size_t n_cfg = m_cfgbase.cfgs.size();
    for(size_t n = 0; n < n_cfg; ++n){
        const cfg_t &cfg = m_cfgbase.cfgs[n];
        const string xml = m_xml_dir + "\\" + strip_ext(strip_dir(cfg.en_name)) + ".xml";

        string xml_text;        
        xmltool::slice_xml_text(cfg, xml_text);

        ofstream o(xml);
        o << xml_text;
        ECHO_OK("导出[%s] -> [%s]成功", cfg.cn_name.c_str(), xml.c_str());
    }

    return true;
}
