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

using namespace excelutil;

namespace parseutil
{
    // 解析出各个区域的起始行
    bool parse_each_region_begin_row(COleSafeArray &ole_safe_array, int row_cnt, cfg_t &cfg, errvec_t& errvec)
    {
        // 1. 从空行开始往下找到文件定义区的起始行
        for(int row = excel_row_cfg; row < row_cnt; row++){
            if (!is_cell_empty(ole_safe_array, row, 1)){
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
            if (!is_cell_empty(ole_safe_array, row, 1)){
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
            if (!is_cell_empty(ole_safe_array, row, 1)){
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
	bool parse_cfg(COleSafeArray &ole_safe_array, int row_cnt, cfg_t &cfg, errvec_t& errvec)
	{
        if (0 == cfg.row_file_cfg_begin){
            return false;
        }

		cfg.en_name = get_cell_str(ole_safe_array, cfg.row_file_cfg_begin + cfg_row_1, cfg_col_en_name);
		cfg.maxcnt  = get_cell_int(ole_safe_array, cfg.row_file_cfg_begin + cfg_row_1, cfg_col_max_cnt);

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
    bool parse_field(COleSafeArray &ole_safe_array, cfg_t &cfg, int col, field_t &field, errvec_t& errvec)
	{
        // 取出字段英文名
		field.en_name = strutil::trim(get_cell_str(ole_safe_array, cfg.row_fields_begin + field_row_en_name, col));
		if(field.en_name.empty()){
            // 碰到空字段则停止解析
			return true;
		}

        // 取出字段类型
		std::string fieldtype_cell = strutil::trim(get_cell_str(ole_safe_array, cfg.row_fields_begin + field_row_data_type, col));
		field.fieldtype = cfgutil::type_name_2_enum(fieldtype_cell.c_str());
		
        // 取出字段属性
        std::string fieldattr_cell = strutil::trim(get_cell_str(ole_safe_array, cfg.row_fields_begin + field_row_is_unique, col));

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

        field.cn_name = strutil::trim(get_cell_str(ole_safe_array, cfg.row_data_begin, col));
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
	bool parse_fields(COleSafeArray &ole_safe_array, int row_cnt, int col_cnt, cfg_t &cfg, errvec_t& errvec)
	{
        if (0 == cfg.row_fields_begin){
            return false;
        }

		bool succ = true;

        field_t field;

        // 从第一列开始，一列一列往右解析各字段，直到碰到空列
        for(int col = 1; col <= col_cnt; col++){
            // 解析该字段
            bool ok = parse_field(ole_safe_array, cfg, col, field, errvec);
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
    bool parse_data(COleSafeArray &ole_safe_array, int row_cnt, int col_cnt, cfg_t &cfg, errvec_t& errvec)
    {
        bool is_empty = (cfg.row_data_begin + 1 > (size_t)row_cnt);
        if (is_empty){
            return true;
        }

        row_t r;
        r.resize(cfg.fields.size());
        cfg.table.reserve(row_cnt - cfg.row_data_begin);

        bool is_ok = true;
        for(int row = cfg.row_data_begin + 1; row <= row_cnt; row++){
            bool is_empty_row = false;
            for(size_t col = 1; col <= cfg.fields.size(); col++){
                 fast_get_cell_str(ole_safe_array, row, col, r[col - 1]);
                
                if (r[col - 1].empty()){
                    if (1 == col){
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

	bool parse_cfg_from_sheet(CWorksheet &sheet, COleSafeArray &ole_safe_array, cfg_t &cfg, errvec_t& errvec, enum_parse_option parse_option /* = parse_option_ignore_data */)
	{
        ole_safe_array.Clear();
		pre_load_sheet(sheet, ole_safe_array);

        // 获取excel表的行数和列数
		int row_cnt = get_row_cnt(sheet);
		int col_cnt = get_col_cnt(sheet);

        if(0 == row_cnt || 0 == col_cnt){
            errvec.push_back(getmsg("跳过解析<%s>表，该表内容为空", sheet.get_Name().GetString()));
            return false;
        }

		if(row_cnt < excel_row_min){
			errvec.push_back(getmsg("分析<%s>失败：表格中当前只有<%u>行，至少应有<%u>行", sheet.get_Name().GetString(), row_cnt, excel_row_min));
			return false;
		}

        if(col_cnt < cfg_col_max - 1){
            errvec.push_back(getmsg("分析<%s>失败：表格中当前只有<%u>列，至少应有<%u>列", sheet.get_Name().GetString(), col_cnt, cfg_col_max - 1));
            return false;
        }

        // 取出工作表的名称
		cfg.cn_name = sheet.get_Name().GetString();

        // 开始解析
        bool succ = true;
        succ &= parse_each_region_begin_row(ole_safe_array, row_cnt, cfg, errvec);
		succ &= parse_cfg(ole_safe_array, row_cnt, cfg, errvec);
        succ &= parse_fields(ole_safe_array, row_cnt, col_cnt, cfg, errvec);
        // Tick tick_now = tickutil::get_tick();

        if (parse_option_read_data == parse_option){
            succ &= parse_data(ole_safe_array, row_cnt, col_cnt, cfg, errvec);
        }

        //uint32_t passed_ms = tickutil::tick_diff(tick_now);
        //double passed_sec = (double)passed_ms / 1000;
        //std::cout << "载入数据成功, 共耗时<" << passed_sec << ">秒" << std::endl;

		return succ;
	}
};

bool parser::parse_excel(const string &xlsx, cfgbase_t &cfgbase, errvec_t &errvec, enum_parse_option parse_option /* = parse_option_skip_data */)
{
    Tick tick_now = tickutil::get_tick();

    CApplication excel_app;
    CWorkbooks books;
    CWorkbook book;
    CRange range;
    CWorksheets sheets;

    COleSafeArray ole_safe_array;

    bool succ = excelutil::open_sheets_of_excel(xlsx, excel_app, books, book, sheets);
    if(false == succ){
        return false;
    }
        
    COleVariant covTrue((short)TRUE), covFalse((short)FALSE), covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

    for(int i = 0;i < sheets.get_Count(); i++){   
        cfg_t cfg;
        CWorksheet sheet = sheets.get_Item(COleVariant((long)(i+1)));   

        // 解析出工作表的内容，并将结果存放到cfg中
        bool ok = parseutil::parse_cfg_from_sheet(sheet, ole_safe_array, cfg, errvec, parse_option);
        sheet.ReleaseDispatch();

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

    if (!cfgbase.cfgs.empty()){
        // 将第一个工作表的名称作为文件名（比如excel中有2个工作表item、hero则将item作为文件名）
        cfgbase.filename = cfgbase.cfgs[0].en_name;
    }

    book.Close(COleVariant(short(FALSE)),COleVariant(xlsx.c_str()), covOptional);  
    books.Close(); 

    // 释放资源
    sheets.ReleaseDispatch();
    book.ReleaseDispatch();
    books.ReleaseDispatch();
    excel_app.Quit();
    excel_app.ReleaseDispatch();

    uint32_t passed_ms = tickutil::tick_diff(tick_now);
    double passed_sec = (double)passed_ms / 1000;
    // std::cout << "执行成功, 共耗时<" << passed_sec << ">秒" << std::endl;
    ECHO_WARN("执行完毕, 共耗时<%0.3f>秒", passed_sec);
    return succ;
}
