///<------------------------------------------------------------------------------
//< @file:   language\json\json_generator.cpp
//< @author: hongkunan
//< @date:   2014年11月6日 15:51:37
//< @brief:  
//< Copyright (c) 2014 heihuo. All rights reserved.
///<------------------------------------------------------------------------------

#include "json_generator.h"

#include <fstream>
#include <iostream>

#include "cfg.h"
#include "file_tool.h"
#include "str_tool.h"
#include "echo_tool.h"
#include "parser.h"
#include "tick_tool.h"

namespace jsontool{
    // 转码:
    //     1. 引号 -> &quot;
    void escape_json(string &str)
    {
        strtool::replace(str, "\"", "&quot;");
    }

    // 将数据拼接成json格式
    void slice_json_text(const cfg_t &cfg, std::string &json_text)
    {
        const fieldvec_t &fields = cfg.fields;
        table_t &table = *(const_cast<table_t*>(&cfg.table));

        json_text = "{\n"
                    "\"%cfg%\": [\n";

        strtool::replace(json_text, "%cfg%", cfg.en_name);
        json_text.reserve(cfg.table.size() * fields.size() * 15);

        string row_text;
        size_t n_row = cfg.table.size();
        for(size_t r = 0; r < n_row; r++){
            row_t &row = table[r];

            // 将数据拼接成形如{"a"="a1" "b"="b1" "c"="c1"....}的一行json文本
            row_text = "	{";

            size_t n_fields = fields.size();
            for(size_t col = 0; col < n_fields; col++){
                escape_json(row[col]);
                row_text += "\"" + cfg.fields[col].en_name + "\":\"" + row[col] + "\"";

                if (col + 1 < n_fields){
                    row_text += ",";
                }
            }

            if (r + 1 < n_row){
                row_text += "},\n";
            }else{
                row_text += "}\n";
            }

            json_text += row_text;
        }

        json_text += "]}";
    }
};

bool json_generator::generate()
{
    if(false == filetool::exist(m_json_dir)){
        ECHO_ERR("错误: <%s>路径不存在", m_json_dir.c_str());
        return false;
    }

    return save_as_json();
}

bool json_generator::save_as_json()
{
    // 将excel中各个工作表数据导出到对应的xml文件中
    size_t n_cfg = m_cfgbase.cfgs.size();
    for(size_t n = 0; n < n_cfg; ++n){
        const cfg_t &cfg = m_cfgbase.cfgs[n];
        const string json = m_json_dir + "\\" + strip_ext(strip_dir(cfg.en_name)) + ".json";

        string json_text;        
        jsontool::slice_json_text(cfg, json_text);

        ofstream o(json);
        o << json_text;
        ECHO_OK("导出[%s] -> [%s]成功", cfg.cn_name.c_str(), json.c_str());
    }

    return true;
}
