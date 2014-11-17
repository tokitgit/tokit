///<------------------------------------------------------------------------------
//< @文件名：excel_tool.cpp
//< @作　者：洪坤安
//< @日　期: 2014年11月12日 22:02:42
//< @摘　要: 操作excel的方法集合
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

// excel_tool
package tool

import (
	"xlsx"
	"strconv"
)

    // 单元格是否为空
    func Is_cell_empty(sheet *xlsx.Sheet, row int, col int) bool{
		cell := sheet.Cell(row - 1, col - 1)
		return cell.Value == "";
	}

    // 获取指定单元格的文本内容，如果是数字格式，则仍然转为文本
    func Get_cell_str(sheet *xlsx.Sheet, row int, col int) string{
		cell := sheet.Cell(row - 1, col - 1)
		return cell.String()
	}

    // 获取表格的数字
	func Get_cell_int(sheet *xlsx.Sheet, row int, col int) int{
		cell := sheet.Cell(row - 1, col - 1)
		cell.String();
		i, err := strconv.Atoi(cell.String())
		if err != nil{
			// fmt.Println("字符串转换成整数失败 = ", cell.String(), err)
			i = 0
		}

		return i
	}

	// 获取工作表的行数
	func Get_row_cnt(sheet *xlsx.Sheet) int{
		return sheet.MaxRow
	}

	// 获取工作表的列数
	func Get_col_cnt(sheet *xlsx.Sheet) int{
		return sheet.MaxCol
	}