///<------------------------------------------------------------------------------
//< @file:   prop\parser\excel_util.h
//< @author: 洪坤安
//< @date:   2014年9月20日 17:59:45
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _excel_util_h_
#define _excel_util_h_

#include <string>

class CApplication;
class CWorkbooks;
class CWorkbook;
class CWorksheet;
class CWorksheets;
class COleSafeArray;

using std::string;

namespace excelutil
{
	bool open_sheets_of_excel(const string &xlsx, CApplication&, CWorkbooks&, CWorkbook&, CWorksheets&);

    // 预加载单元格，加快读取excel的速度
    void pre_load_sheet(CWorksheet &sheet, COleSafeArray &safe_array);

    bool is_cell_empty(COleSafeArray &ole_safe_array, int row, int col);

    std::string get_cell_str(COleSafeArray &ole_safe_array, int row, int col);
	
    void fast_get_cell_str(COleSafeArray &ole_safe_array, int row, int col, std::string &result);


	int get_cell_int(COleSafeArray &ole_safe_array, int row, int col);

	int get_row_cnt(CWorksheet &sheet);

	int get_col_cnt(CWorksheet &sheet);
}
#endif //_excel_util_h_