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
#include <vector>
#include <libxl.h>
#include <xstring>

class CApplication;
class CWorkbooks;
class CWorkbook;
class CWorksheet;
class CWorksheets;
class COleSafeArray;

using std::string;

namespace excelutil
{
    // 通过ole的方式打开excel（实际上是打开一个系统现有的excel进程，让该进程加载该excel文件，所以此时要求加载的excel文件处于关闭状态，否则会打开失败）
    bool ole_open_excel(const string &xlsx, CApplication&, CWorkbooks&, CWorkbook&, CWorksheets&);

	void ole_close_excel(const std::wstring &xlsx, CApplication&, CWorkbooks&, CWorkbook&, CWorksheets&);

    // 预加载单元格，将excel工作表的内容预加载到数组中，加快之后读取excel的速度
    void pre_load_sheet(CWorksheet &sheet, COleSafeArray &safe_array);

    // 检测excel文件中是否含有公式（一个个单元格地遍历检测），并将检测结果存入数组
    typedef std::vector<bool> formula_flag_vec;
    bool is_excel_contain_formula_cell(libxl::Book&, formula_flag_vec&);

    // 单元格是否为空
    bool is_cell_empty(libxl::Sheet &sheet, int row, int col);

    // 获取指定单元格的文本内容，如果是数字格式，则仍然转为文本
    std::string& get_cell_str(libxl::Sheet &sheet, int row, int col);

    // 获取表格的数字
	int get_cell_int(libxl::Sheet &sheet, int row, int col);

	int get_row_cnt(libxl::Sheet &sheet);

	int get_col_cnt(libxl::Sheet &sheet);
}
#endif //_excel_util_h_