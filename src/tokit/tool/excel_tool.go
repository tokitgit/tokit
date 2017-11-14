//< @摘　要: 操作excel的方法集合


// excel_tool
package tool

import (
	"strconv"
	"xlsx"
)

// 单元格是否为空
func IsCellEmpty(sheet *xlsx.Sheet, row int, col int) bool {
	cell := sheet.Cell(row-1, col-1)
	return cell.Value == ""
}

// 获取指定单元格的文本内容，如果是数字格式，则仍然转为文本
func GetCellString(sheet *xlsx.Sheet, row int, col int) string {
	cell := sheet.Cell(row-1, col-1)
	return cell.String()
}

// 获取表格的数字
func GetCellInt(sheet *xlsx.Sheet, row int, col int) int {
	cell := sheet.Cell(row-1, col-1)
	cell.String()
	i, err := strconv.Atoi(cell.String())
	if err != nil {
		// fmt.Println("字符串转换成整数失败 = ", cell.String(), err)
		i = 0
	}

	return i
}

// 获取工作表的行数
func GetRowCount(sheet *xlsx.Sheet) int {
	return sheet.MaxRow
}

// 获取工作表的列数
func GetColumCount(sheet *xlsx.Sheet) int {
	return sheet.MaxCol
}
