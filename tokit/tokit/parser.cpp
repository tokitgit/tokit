///<------------------------------------------------------------------------------
//< @file:   tokit\tokit\parser.cpp
//< @author: 洪坤安
//< @date:   2014年9月25日 16:20:30
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include "parser.h"

#include <algorithm>
#include <fstream>
#include <iostream>

#include <libxl.h>

#include "excel/CApplication.h"  
#include "excel/CRange.h"  
#include "excel/CWorkbook.h"  
#include "excel/CWorkbooks.h"  
#include "excel/CWorksheet.h"
#include "excel/CWorksheets.h"

#include "excel_util.h"
#include "str_util.h"
#include "echoutil.h"
#include "tickutil.h"
#include "file_util.h"

using namespace excelutil;
using namespace libxl;

COleSafeArray* parser::g_ole_cell_array = NULL;


namespace parseutil
{
    // 解析出各个区域的起始行
    bool parse_each_region_begin_row(libxl::Sheet &sheet, int row_cnt, cfg_t &cfg, errvec_t& errvec)
    {
        // 1. 从空行开始往下找到文件定义区的起始行
        for(int row = excel_row_cfg; row < row_cnt; row++){
            if (!is_cell_empty(sheet, row, 1)){
                cfg.row_file_cfg_begin = row;
                break;
            }
        }

        if (0 == cfg.row_file_cfg_begin){
            errvec.push_back(getmsg("错误：未<%s>表定义文件英文名", cfg.cn_name.c_str()));
            return false;
        }

        // 2. 从文件定义区开始，跳过空行往下找到字段定义区的起始行
        for(int row = cfg.row_file_cfg_begin + cfg_row_max; row < row_cnt; row++){
            if (!is_cell_empty(sheet, row, 1)){
                cfg.row_fields_begin = row;
                break;
            }
        }

        if (0 == cfg.row_fields_begin){
            errvec.push_back(getmsg("错误：未在<%s>表中找到字段定义", cfg.cn_name.c_str()));
            return false;
        }

        // 3. 从字段定义区开始，跳过空行找到数据区的起始行
        for(int row = cfg.row_fields_begin + field_row_max + 1; row < row_cnt; row++){
            if (!is_cell_empty(sheet, row, 1)){
                cfg.row_data_begin = row;
                break;
            }
        }

        if (0 == cfg.row_data_begin){
            errvec.push_back(getmsg("错误：未在<%s>表中找到数据", cfg.cn_name.c_str()));
            return false;
        }

        return true;
    }

    // 解析文件定义区
	bool parse_cfg(libxl::Sheet &sheet, int row_cnt, cfg_t &cfg, errvec_t& errvec)
	{
        if (0 == cfg.row_file_cfg_begin){
            return false;
        }

        // 文件名称
		cfg.en_name = get_cell_str(sheet, cfg.row_file_cfg_begin + cfg_row_1, cfg_col_en_name);

        // 最大数据条数
		cfg.maxcnt  = get_cell_int(sheet, cfg.row_file_cfg_begin + cfg_row_1, cfg_col_max_cnt);

        if (cfg.en_name.empty()){
            errvec.push_back(getmsg("分析<%s>失败：必须给表填上英文名", cfg.en_name.c_str()));
            return false;
        }

		return true;
	}

    bool is_unique_key_by_str(std::string &str)
    {
        bool is_unique_key = false;
        is_unique_key |= (str.find("unique") != string::npos);
        is_unique_key |= (str.find("唯一") != string::npos);
        return is_unique_key;
    }

    bool is_primary_key_by_str(std::string &str)
    {
        bool is_unique_key = false;
        is_unique_key |= (str.find("primary") != string::npos);
        is_unique_key |= (str.find("主键") != string::npos);
        return is_unique_key;
    }

    bool is_array_by_str(std::string &str)
    {
        bool is_array = false;
        is_array |= (str.find("vector") != string::npos);
        is_array |= (str.find("vec") != string::npos);
        is_array |= (str.find("array") != string::npos);
        is_array |= (str.find("数组") != string::npos);
        return is_array;
    }

    // 是否是集合类型
    bool is_set_by_str(std::string &str)
    {
        bool is_array = false;
        is_array |= (str.find("set") != string::npos);
        is_array |= (str.find("集合") != string::npos);
        return is_array;
    }
    
    // 解析指定列的字段定义
    bool parse_field(libxl::Sheet &sheet, cfg_t &cfg, int col, field_t &field, errvec_t& errvec)
	{
        // 取出字段英文名
		field.en_name = strutil::trim(get_cell_str(sheet, cfg.row_fields_begin + field_row_en_name, col));
		if(field.en_name.empty()){
            // 碰到空字段则停止解析
			return true;
		}

        // 取出字段类型
		std::string fieldtype_cell = strutil::trim(get_cell_str(sheet, cfg.row_fields_begin + field_row_data_type, col));
		field.fieldtype = cfgutil::type_name_2_enum(fieldtype_cell.c_str());
		
        // 取出字段属性
        std::string fieldattr_cell = strutil::trim(get_cell_str(sheet, cfg.row_fields_begin + field_row_is_unique, col));

        field.fieldattr = field_t::fieldattr_none;
        if(is_unique_key_by_str(fieldattr_cell)){
            field.fieldattr = field_t::fieldattr_1_key;
        }else if(is_primary_key_by_str(fieldattr_cell)){
            field.fieldattr = field_t::fieldattr_n_key;
        }else if(is_array_by_str(fieldattr_cell)){
            field.fieldattr = field_t::fieldattr_array;
        }else if(is_set_by_str(fieldattr_cell)){
            field.fieldattr = field_t::fieldattr_set;
        }

        field.cn_name = strutil::trim(get_cell_str(sheet, cfg.row_data_begin, col));
        field.comment = field.cn_name;

        if(field.cn_name.empty()){
            errvec.push_back(getmsg("解析第<%s>行时发生错误：中文名不允许为空", col));
            return false;
        }

        if(fieldtype_cell.empty()){
            errvec.push_back(getmsg("解析<%s>字段时发生错误：该字段的类型为空", field.cn_name.c_str()));
            return false;
        }

        if(fieldtype_none == field.fieldtype){
            errvec.push_back(getmsg("解析<%s>字段时发生错误：不支持<%s>类型的字段", field.cn_name.c_str(), fieldtype_cell.c_str()));
            return false;
        }

		return true;
	}

    // 解析字段定义区
	bool parse_fields(libxl::Sheet &sheet, int row_cnt, int col_cnt, cfg_t &cfg, errvec_t& errvec)
	{
        if (0 == cfg.row_fields_begin){
            return false;
        }

		bool succ = true;

        field_t field;

        // 从第一列开始，一列一列往右解析各字段，直到碰到空列
        for(int col = 1; col <= col_cnt; col++){
            // 解析该字段
            bool ok = parse_field(sheet, cfg, col, field, errvec);
            if(false == ok){
                succ = false;
                continue;
            }

            // 碰到空字段则停止解析
            if (field.en_name.empty()){
                break;
            }

            field_t *old_field = cfg.getfield(field.en_name.c_str());
			if(old_field){
				errvec.push_back(getmsg("错误：定义了两个同样地字段<%s>", field.en_name.c_str()));
				errvec.push_back(getmsg("       <%-6s = %s>", old_field->get_field_type_name().c_str(), old_field->en_name.c_str()));
				errvec.push_back(getmsg("       <%-6s = %s>", field.get_field_type_name().c_str(), field.en_name.c_str()));

				succ = false;
				continue;
			}

            // 如果该字段是主键之一，则将该字段的位置存入主键列表
			if(field.is_n_key()){
				cfg.keys.push_back(cfg.fields.size());
			}

			cfg.fields.push_back(field);
		}

		if(cfg.fields.empty()){
			errvec.push_back(getmsg("错误：未给<%s>表定义字段", cfg.cn_name.c_str()));
		}

        // 如果主键仅由1个字段组成，则将主键字段的属性替换为<唯一>
        size_t n_key = cfg.keys.size();
        if (1 == n_key){
            field_t &primary_key_field = cfg.fields[cfg.keys[0]];
            primary_key_field.fieldattr = field_t::fieldattr_1_key;
        }

		std::sort(cfg.keys.begin(), cfg.keys.end());
		return succ;
	}

    // 解析配置数据区
    bool parse_data(libxl::Sheet &sheet, int row_cnt, int col_cnt, cfg_t &cfg, errvec_t& errvec)
    {
        bool is_empty = (cfg.row_data_begin + 1 > (size_t)row_cnt);
        if (is_empty){
            return true;
        }

        bool is_ok = true;

        row_t r;
        r.resize(cfg.fields.size());
        cfg.table.reserve(row_cnt - cfg.row_data_begin);

        // 将数据区的行和列存入对应的数组
        for(int row = cfg.row_data_begin + 1; row <= row_cnt; row++){
            bool is_empty_row = false;

            for(size_t col = 1; col <= cfg.fields.size(); col++){
                 r[col - 1] = get_cell_str(sheet, row, col);
                
                 // 一旦出现某行的第一个单元格为空，则停止解析
                 if (1 == col){
                    if (r[col - 1].empty()){
                        is_empty_row = true;
                        break;
                    }
                    /*
                    else{
                        errvec.push_back(getmsg("解析第<%u>行时发生错误：<%s>字段的值为空，请检查数据后再重试", row, cfg.fields[col - 1].cn_name.c_str()));
                        cfg.table.clear();
                        is_ok = false;
                        break;
                    }
                    */
                }
            }

            if (is_empty_row){
                break;
            }

            cfg.table.push_back(r);
        }
        
        return is_ok;
    }

    // 解析出工作表的所有内容，并将解析结果存放到对应结构体中
	bool parse_cfg_from_sheet(libxl::Sheet &sheet, cfg_t &cfg, errvec_t& errvec, enum_parse_option parse_option /* = parse_option_ignore_data */)
	{
        // 1. 获取excel表的行数和列数
		int row_cnt = get_row_cnt(sheet);
		int col_cnt = get_col_cnt(sheet);

        if(0 == row_cnt || 0 == col_cnt){
            errvec.push_back(getmsg("跳过解析<%s>表，该表内容为空", sheet.name()));
            return false;
        }

		if(row_cnt < excel_row_min){
			errvec.push_back(getmsg("分析<%s>失败：表格中当前只有<%u>行，至少应有<%u>行", sheet.name(), row_cnt, excel_row_min));
			return false;
		}

        if(col_cnt < cfg_col_max - 1){
            errvec.push_back(getmsg("分析<%s>失败：表格中当前只有<%u>列，至少应有<%u>列", sheet.name(), col_cnt, cfg_col_max - 1));
            return false;
        }

        std::wstring w_name = sheet.name();

        // 2. 取出工作表的名称
		cfg.cn_name = strutil::wstring2string(sheet.name());

        // 开始解析
        bool succ = true;

        // 3. 解析各个区域的起始行，共有3个区域：文件定义区、字段定义区、数据区
        succ &= parse_each_region_begin_row(sheet, row_cnt, cfg, errvec);

        // 4. 解析文件定义区
		succ &= parse_cfg(sheet, row_cnt, cfg, errvec);

        // 5. 解析字段定义区
        succ &= parse_fields(sheet, row_cnt, col_cnt, cfg, errvec);

        // 6. 载入数据区
        if (parse_option_read_data == parse_option){
            succ &= parse_data(sheet, row_cnt, col_cnt, cfg, errvec);
        }

		return succ;
	}

    // 检测是否需进行ole预加载，以加快之后的读取速度
    void check_need_preload_sheet(CWorksheets &sheets, int sheet_idx, bool need_ole_load)
    {
        if (need_ole_load){
            CWorksheet ole_sheet = sheets.get_Item(COleVariant((long)(sheet_idx)));

            static COleSafeArray s_ole_safe_array;
            s_ole_safe_array.Clear();
            parser::g_ole_cell_array = &s_ole_safe_array;

            excelutil::pre_load_sheet(ole_sheet, *parser::g_ole_cell_array);
        }
    }
};

bool parser::parse_excel(const string &xlsx, cfgbase_t &cfgbase, errvec_t &errvec, enum_parse_option parse_option /* = parse_option_skip_data */)
{
    tick_t parse_tick;

    if(false == fileutil::exist(xlsx)){
        errvec.push_back(xlsx + "文件不存在!");
        return false;
    }
    
    libxl::Book *book = xlCreateXMLBook();
    
    // 我们将使用2种方法读取excel；libxl库、ole，2者区别是：
    //     a. libxl速度很快，ole速度很慢
    //     b. libxl不支持公式，ole支持公式
    
    // 1. 以libxl的方式载入excel
    std::wstring w_xlsx = strutil::string2wstring(xlsx);
    if(!book->load(w_xlsx.c_str())){
        return false;
    }

    CApplication excel_app;
    CWorkbooks books;
    CWorkbook olebook;
    CWorksheets sheets;

    bool succ = true;

    // 2. 使用libxl检测excel文件中是否含有公式
    excelutil::formula_flag_vec each_sheet_formula_flags;
    bool is_need_ole_open = is_excel_contain_formula_cell(*book, each_sheet_formula_flags);

    // 2.1. 如果有公式，则通过ole方式再加载一次excel
    if (is_need_ole_open){
        succ = excelutil::ole_open_excel(xlsx, excel_app, books, olebook, sheets);
        if (!succ){
            return false;
        }
    }

    // 3. 依次解析各个工作表
    for(int i = 0; i < book->sheetCount(); i++){   
        cfg_t cfg;
        libxl::Sheet *sheet = book->getSheet(i);
        if (!sheet){
            continue;
        }
        
        // 3.1 如果工作表中含公式，则进行ole预读取，以加快之后的读取速度
        parseutil::check_need_preload_sheet(sheets, i + 1, each_sheet_formula_flags[i]);

        // 3.2 解析出工作表的内容，并将结果存放到cfg中
        bool ok = parseutil::parse_cfg_from_sheet(*sheet, cfg, errvec, parse_option);
        if(false == ok){
            succ = false;
            continue;
        }

        cfg_t *conflict_by_prop = cfgbase.find_by_en_name(cfg.en_name.c_str());
        if(conflict_by_prop){
            errvec.push_back(getmsg("错误：定义了两个同样地文件<%s>", cfg.cn_name.c_str()));
            errvec.push_back(getmsg("       <%s = %s>", conflict_by_prop->cn_name.c_str(), conflict_by_prop->en_name.c_str()));
            errvec.push_back(getmsg("       <%s = %s>", cfg.cn_name.c_str(), cfg.en_name.c_str()));

            succ = false;
            continue;
        }

        cfgbase.cfgs.push_back(cfg);
    }

    // 将第一个工作表名作为文件名（比如，excel中有2个工作表item、hero，则将item作为文件名）
    if (!cfgbase.cfgs.empty()){
        cfgbase.filename = cfgbase.cfgs[0].en_name;
    }

    // 4. 释放ole资源
    if (is_need_ole_open){
        tick_t close_tick;
        excelutil::ole_close_excel(w_xlsx, excel_app, books, olebook, sheets);
    }

    ECHO_WARN("执行完毕, 共耗时<%0.3f>秒", parse_tick.end_tick());
    return succ;
}
