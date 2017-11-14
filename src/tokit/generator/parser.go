// @摘　要: excel解析器

// parser
package generator

import (
	"strings"
	"tokit/tool"
	"xlsx"
)

// 解析出各个区域的起始行
func ParseEachRegionBeginRow(sheet *xlsx.Sheet, row_cnt int, cfg *SheetInfo, errvec *tool.Errvec_t) bool {
	// 1. 从空行开始往下找到文件定义区的起始行
	var is_find_file_cfg bool = false
	for row := excel_row_cfg; row < row_cnt; row += 1 {
		if !tool.IsCellEmpty(sheet, row, cfg_col_1) {
			cfg.RowTopRegionBegin = row
			is_find_file_cfg = true
			break
		}
	}

	if !is_find_file_cfg {
		*errvec = append(*errvec, tool.GetErrMsg("错误：未<%s>表定义文件英文名", cfg.CnName))
		return false
	}

	// 2. 从文件定义区开始，跳过空行往下找到字段定义区的起始行
	for row := cfg.RowTopRegionBegin + 2; row < row_cnt; row++ {
		if !tool.IsCellEmpty(sheet, row, cfg_col_1) {
			cfg.RowFieldRegionBegin = row
			break
		}
	}

	if 0 == cfg.RowFieldRegionBegin {
		*errvec = append(*errvec, tool.GetErrMsg("错误：未在<%s>表中找到字段定义", cfg.CnName))
		return false
	}

	// 3. 从字段定义区开始，跳过空行找到数据区的起始行
	for row := cfg.RowFieldRegionBegin + int(Field_row_max) + 1; row < row_cnt; row++ {
		if !tool.IsCellEmpty(sheet, row, cfg_col_1) {
			cfg.RowDataRegionBegin = row
			break
		}
	}

	if 0 == cfg.RowDataRegionBegin {
		*errvec = append(*errvec, tool.GetErrMsg("错误：未在<%s>表中找到数据", cfg.CnName))
		return false
	}

	return true
}

// 解析文件定义区
func ParseTopRegion(sheet *xlsx.Sheet, row_cnt int, excelInfo *ExcelInfo, cfg *SheetInfo, errvec *tool.Errvec_t) bool {
	cfg.VerticalType = VerticalType_Horizontal

	for col := 1; col <= 3; col++ {
		var col_name string = tool.GetCellString(sheet, cfg.RowTopRegionBegin, col)
		var col_value string = tool.GetCellString(sheet, cfg.RowTopRegionBegin+1, col)

		if col_name == "文件名" {
			// 文件名称
			cfg.EnName = col_value
		} else if col_name == "程序类名" {
			// 文件名称
			excelInfo.ClassName = col_value
		} else if col_name == "表格类型" {
			if col_value == "垂直" || col_value == "vertical" {
				cfg.VerticalType = VerticalType_Vertical
			}
		}
	}

	if cfg.EnName == "" {
		*errvec = append(*errvec, tool.GetErrMsg("分析<%s>失败：必须给表填上英文名", cfg.CnName))
		return false
	}

	if excelInfo.ClassName == "" {
		*errvec = append(*errvec, tool.GetErrMsg("分析<%s>失败：必须给表填上程序类名", cfg.CnName))
		return false
	}

	return true
}

func contain_1_of_n(str *string, substrs ...string) bool {
	for _, v := range substrs {
		if strings.Contains(*str, v) {
			return true
		}
	}

	return false
}

func IsUniqueKeyByStr(str *string) bool {
	var is_unique_key bool = contain_1_of_n(str, "unique", "唯一")
	return is_unique_key
}

func IsOneOfKeyByStr(str *string) bool {
	var is_primary_key bool = contain_1_of_n(str, "primary", "主键")
	return is_primary_key
}

func IsArrayByStr(str *string) bool {
	var is_array bool = contain_1_of_n(str, "vector", "vec", "array", "数组")
	return is_array
}

// 是否是集合类型
func IsSetByStr(str *string) bool {
	var is_set bool = contain_1_of_n(str, "set", "集合")
	return is_set
}

// 解析指定列的字段定义
func ParseField(sheet *xlsx.Sheet, cfg *SheetInfo, col int, field *FieldInfo, errvec *tool.Errvec_t) bool {
	// 取出字段英文名
	field.EnName = strings.Trim(tool.GetCellString(sheet, cfg.RowFieldRegionBegin+int(field_row_EnName), col), " \t")
	if field.EnName == "" {
		// 碰到空字段则停止解析
		return true
	}

	// 取出字段类型
	var strCellFieldType string = strings.Trim(tool.GetCellString(sheet, cfg.RowFieldRegionBegin+int(field_row_data_type), col), " \t")
	field.FieldType = GetInternalTypeByName(&strCellFieldType)

	// 取出字段属性
	var strCellFieldAttr string = strings.Trim(tool.GetCellString(sheet, cfg.RowFieldRegionBegin+int(field_row_attr), col), " \t")

	field.FieldAttr = FieldAttr_none
	switch {
	case IsUniqueKeyByStr(&strCellFieldAttr):
		field.FieldAttr = FieldAttr_Key
	case IsOneOfKeyByStr(&strCellFieldAttr):
		field.FieldAttr = FieldAttr_KeyN
	case IsArrayByStr(&strCellFieldAttr):
		field.FieldAttr = FieldAttr_Array
	case IsSetByStr(&strCellFieldAttr):
		field.FieldAttr = FieldAttr_Set
	}

	// 解析字段的中文注释
	var cnName string = strings.Trim(tool.GetCellString(sheet, cfg.RowDataRegionBegin, col), " \t")
	cnName = strings.Replace(cnName, "\r\n", "", -1)
	cnName = strings.Replace(cnName, "\n", "", -1)

	field.CnName = cnName
	field.Comment = cnName

	if field.CnName == "" {
		*errvec = append(*errvec, tool.GetErrMsg("解析第<%d>行时发生错误：中文名不允许为空", col))
		return false
	}

	if strCellFieldType == "" {
		*errvec = append(*errvec, tool.GetErrMsg("解析<%s>字段时发生错误：该字段的类型为空", field.CnName))
		return false
	}

	if FieldType_none == field.FieldType {
		*errvec = append(*errvec, tool.GetErrMsg("解析<%s>字段时发生错误：不支持<%s>类型的字段", field.CnName, strCellFieldType))
		return false
	}

	return true
}

// 解析字段定义区
func ParseFieldsRegion(sheet *xlsx.Sheet, row_cnt int, col_cnt int, cfg *SheetInfo, errvec *tool.Errvec_t) bool {
	if 0 == cfg.RowFieldRegionBegin {
		return false
	}

	var succ bool = true

	var field FieldInfo

	// 从第一列开始，一列一列往右解析各字段，直到碰到空列
	for col := 1; col <= col_cnt; col++ {
		// 解析该字段
		var ok bool = ParseField(sheet, cfg, col, &field, errvec)
		if false == ok {
			succ = false
			continue
		}

		// 碰到空字段则停止解析
		if field.EnName == "" {
			break
		}

		var oldField *FieldInfo = cfg.GetField(&field.EnName)
		if oldField != nil {
			*errvec = append(*errvec, tool.GetErrMsg("错误：定义了两个同样地字段<%s>", field.EnName))
			*errvec = append(*errvec, tool.GetErrMsg("       <%-6s = %s>", oldField.GetInternalTypeName(), oldField.EnName))
			*errvec = append(*errvec, tool.GetErrMsg("       <%-6s = %s>", field.GetInternalTypeName(), field.EnName))

			succ = false
			continue
		}

		// 如果该字段是主键之一，则将该字段的位置存入主键列表
		if field.IsKeyN() {
			cfg.Keys = append(cfg.Keys, uint8(len(cfg.Fields)))
		}

		cfg.Fields = append(cfg.Fields, field)
	}

	if len(cfg.Fields) == 0 {
		*errvec = append(*errvec, tool.GetErrMsg("错误：未给<%s>表定义字段", cfg.CnName))
	}

	// 如果主键仅由1个字段组成，则将主键字段的属性替换为<唯一>
	n_key := len(cfg.Keys)
	if 1 == n_key {
		cfg.Fields[cfg.Keys[0]].FieldAttr = FieldAttr_Key
		cfg.Keys = KeyArray{}
	}

	return succ
}

// 解析数据区
func ParseData(sheet *xlsx.Sheet, row_cnt int, col_cnt int, cfg *SheetInfo, errvec *tool.Errvec_t) bool {
	var is_empty bool = (cfg.RowDataRegionBegin+1 > row_cnt)
	if is_empty {
		return true
	}

	is_ok := true

	var n_field int = len(cfg.Fields)

	cfg.Rows = make(RowArray, row_cnt-cfg.RowDataRegionBegin)

	// 将数据区的行和列存入对应的数组
	for row := int(cfg.RowDataRegionBegin + 1); row <= row_cnt; row++ {
		var is_empty_row bool = false
		var r RowData = make(RowData, n_field)

		for col := 1; col <= n_field; col++ {
			var cell string = tool.GetCellString(sheet, row, col)
			if cell == "" {
				var field *FieldInfo = &cfg.Fields[col-1]
				if field.IsNumber() {
					cell = "0"
				}
			}

			r[col-1] = cell

			// 一旦出现某行的第一个单元格为空，则停止解析
			if 1 == col {
				if r[col-1] == "" {
					is_empty_row = true
					break
				}
			}
		}

		if is_empty_row {
			break
		}

		cfg.Rows[row-cfg.RowDataRegionBegin-1] = r
	}

	return is_ok
}

// 解析出单个工作表
func ParseSheet(sheet *xlsx.Sheet, excelInfo *ExcelInfo, cfg *SheetInfo, errvec *tool.Errvec_t) bool {
	// 1. 获取excel表的行数和列数
	var row_cnt int = tool.GetRowCount(sheet)
	var col_cnt int = tool.GetColumCount(sheet)

	if 0 == row_cnt || 0 == col_cnt {
		*errvec = append(*errvec, tool.GetErrMsg("跳过解析<%s>表，该表内容为空", sheet.Name))
		return false
	}

	if row_cnt < excel_row_min {
		*errvec = append(*errvec, tool.GetErrMsg("分析<%s>失败：表格中当前只有<%u>行，至少应有<%u>行", sheet.Name, row_cnt, excel_row_min))
		return false
	}

	if col_cnt < 1 {
		*errvec = append(*errvec, tool.GetErrMsg("分析<%s>失败：表格中当前只有<%u>列，至少应有<%u>列", sheet.Name, col_cnt, 1))
		return false
	}

	// 2. 取出工作表的名称
	cfg.CnName = sheet.Name

	succ := true

	// 3. 解析各个区域的起始行，共有3个区域：文件定义区、字段定义区、数据区
	succ = succ && ParseEachRegionBeginRow(sheet, row_cnt, cfg, errvec)

	// 4. 解析文件定义区
	succ = succ && ParseTopRegion(sheet, row_cnt, excelInfo, cfg, errvec)

	// 5. 解析字段定义区
	succ = succ && ParseFieldsRegion(sheet, row_cnt, col_cnt, cfg, errvec)

	// 6. 载入数据区
	succ = succ && ParseData(sheet, row_cnt, col_cnt, cfg, errvec)

	return succ
}

// 解析出excel中的各个工作表，将解析结果存入结构体
func ParseSheets(excel *string, excelInfo *ExcelInfo, errmsgs *tool.Errvec_t) bool {
	var parse_clock tool.Clock
	parse_clock.StartTick()

	if false == tool.Exist(excel) {
		*errmsgs = append(*errmsgs, *excel+"文件不存在!")
		return false
	}

	// 1. 载入excel文件
	xlFile, err := xlsx.OpenFile(*excel)
	if err != nil {
		*errmsgs = append(*errmsgs, tool.GetErrMsg("错误：解析<%s>文件失败，请确保该文件存在且未被打开!", *excel))
		return false
	}

	var succ bool = true

	// 2. 依次解析各个工作表
	for _, sheet := range xlFile.Sheets {
		var sheetInfo SheetInfo

		// 2.1 解析出工作表的内容，并将结果存放到cfg中
		var ok bool = ParseSheet(sheet, excelInfo, &sheetInfo, errmsgs)
		if false == ok {
			succ = false
			continue
		}

		var conflict *SheetInfo = excelInfo.FindByEnName(&sheetInfo.EnName)
		if nil != conflict {
			*errmsgs = append(*errmsgs, tool.GetErrMsg("错误：定义了两个同样地文件<%s>", sheetInfo.CnName))
			*errmsgs = append(*errmsgs, tool.GetErrMsg("       <%s = %s>", conflict.CnName, conflict.EnName))
			*errmsgs = append(*errmsgs, tool.GetErrMsg("       <%s = %s>", sheetInfo.CnName, sheetInfo.EnName))

			succ = false
			continue
		}

		excelInfo.Sheets = append(excelInfo.Sheets, sheetInfo)
	}

	var excelFileName string = tool.StripDir(*excel)
	tool.EchoWarn("解析<%s>完毕, 共耗时<%f>秒", excelFileName, parse_clock.EndTick())
	return succ
}

// 解析excel文件
func ParseExcel(excel *string, excelInfo *ExcelInfo) bool {
	if false == tool.Exist(excel) {
		tool.EchoErr("错误: 找不到excel文件<%s>", *excel)
		return false
	}

	var errvec tool.Errvec_t
	if false == ParseSheets(excel, excelInfo, &errvec) {
		// tool.EchoErr("错误：解析<%s>文件失败，请确保该文件存在且未被打开", *excel)
		tool.EchoErrorArray(&errvec)
		return false
	}

	return true
}

// 内部字段类型
var g_InternalTypeNames = [FieldType_max + 1]string{"", "string", "bool", "char", "int16", "int", "int64", "uint8", "uint16", "uint", "uint64", "float", "double", "program"}

// 返回内部字段类型的名称
func (f *FieldInfo) GetInternalTypeName() string {
	return g_InternalTypeNames[f.FieldType]
}

// 根据名称找到相应的内部字段类型
func GetInternalTypeByName(fieldType *string) enum_tokit_field_type {
	if "" == *fieldType {
		return FieldType_none
	}

	for i := FieldType_none + 1; i < FieldType_max; i++ {
		if g_InternalTypeNames[i] == *fieldType {
			return enum_tokit_field_type(i)
		}
	}

	return FieldType_none
}
