//----------------------------------------------
// 摘　要: 解析excel文件的内容
//----------------------------------------------

package generator

import (
	"strings"
	"tokit/tool"
	"xlsx"
)

// 解析出各个区域的起始行
func (jobCenter *JobCenter) ParseEachRegionBeginRow(sheet *xlsx.Sheet, rowCount int, sheetInfo *SheetInfo) bool {
	// 1. 找到文件定义区
	var isFindFileDefinition bool = false
	for row := ExcelRow_FileRegion; row < rowCount; row += 1 {
		if !tool.IsCellEmpty(sheet, row, FirstCol) {
			sheetInfo.RowTopRegionBegin = row
			isFindFileDefinition = true
			break
		}
	}

	if !isFindFileDefinition {
		jobCenter.Log.AddLog(tool.EnumLogType_Error, "错误：未<%s>表定义文件英文名", sheetInfo.CnName)
		return false
	}

	// 2. 找到字段定义区
	for row := sheetInfo.RowTopRegionBegin + 2; row < rowCount; row++ {
		if !tool.IsCellEmpty(sheet, row, FirstCol) {
			sheetInfo.RowFieldRegionBegin = row
			break
		}
	}

	if 0 == sheetInfo.RowFieldRegionBegin {
		jobCenter.Log.AddLog(tool.EnumLogType_Error, "错误：未在<%s>表中找到字段定义", sheetInfo.CnName)
		return false
	}

	// 3. 找到数据区
	for row := sheetInfo.RowFieldRegionBegin + int(FieldRow_Max) + 1; row < rowCount; row++ {
		if !tool.IsCellEmpty(sheet, row, FirstCol) {
			sheetInfo.RowDataRegionBegin = row
			break
		}
	}

	if 0 == sheetInfo.RowDataRegionBegin {
		jobCenter.Log.AddLog(tool.EnumLogType_Error, "错误：未在<%s>表中找到数据", sheetInfo.CnName)
		return false
	}

	return true
}

// 解析文件定义区
func (jobCenter *JobCenter) ParseTopRegion(sheet *xlsx.Sheet, rowCount int, sheetInfo *SheetInfo) bool {
	sheetInfo.VerticalType = VerticalType_Horizontal

	// 解析文件的主要定义
	for col := 1; col <= 3; col++ {
		var colName string = tool.GetCellString(sheet, sheetInfo.RowTopRegionBegin, col)
		var colValue string = tool.GetCellString(sheet, sheetInfo.RowTopRegionBegin+1, col)

		if colName == "文件名" {
			// 结构体名
			sheetInfo.EnName = colValue
		} else if colName == "程序类名" {
			// 文件名称
			jobCenter.TargetExcel.ClassName = colValue
		} else if colName == "是否只有一行" {
			if colValue == "是" || colValue == "yes" || colValue == "1" {
				sheetInfo.IsOnlyOneLine = true
			}
		}
	}

	if sheetInfo.EnName == "" {
		jobCenter.Log.AddLog(tool.EnumLogType_Error, "分析<%s>失败：必须给表填上英文名", sheetInfo.CnName)
		return false
	}

	if jobCenter.TargetExcel.ClassName == "" {
		jobCenter.Log.AddLog(tool.EnumLogType_Error, "分析<%s>失败：必须给表填上程序类名", sheetInfo.CnName)
		return false
	}

	return true
}

// 指定字符串是否包含任意一个子串
func Contain(str *string, substrs ...string) bool {
	for _, v := range substrs {
		if strings.Contains(*str, v) {
			return true
		}
	}

	return false
}

// 字段的值是否不能重复
func IsUniqueKeyByStr(str *string) bool {
	return Contain(str, "unique", "唯一")
}

// 是否是数组类型
func IsArrayByStr(str *string) bool {
	return Contain(str, "vector", "vec", "array", "数组")
}

// 是否是集合类型
func IsSetByStr(str *string) bool {
	return Contain(str, "set", "集合")
}

// 解析指定列的字段定义
func (jobCenter *JobCenter) ParseField(sheet *xlsx.Sheet, sheetInfo *SheetInfo, col int, field *FieldInfo) bool {
	// 取出字段英文名
	field.EnName = strings.Trim(tool.GetCellString(sheet, sheetInfo.RowFieldRegionBegin+int(FieldRow_EnName), col), " \t")
	if field.EnName == "" {
		// 碰到空字段则停止解析
		return true
	}

	// 解析字段的中文注释
	var cnName string = strings.Trim(tool.GetCellString(sheet, sheetInfo.RowDataRegionBegin, col), " \t")
	cnName = strings.Replace(cnName, "\r\n", "", -1)
	cnName = strings.Replace(cnName, "\n", "", -1)

	field.CnName = cnName
	field.Comment = cnName

	if field.CnName == "" {
		jobCenter.Log.AddLog(tool.EnumLogType_Error, "解析第<%d>行时发生错误：中文名不允许为空", col)
		return false
	}

	// 取出字段类型文本
	var strCellFieldType string = strings.Trim(tool.GetCellString(sheet, sheetInfo.RowFieldRegionBegin+int(FieldRow_FieldType), col), " \t")
	if strCellFieldType == "" {
		jobCenter.Log.AddLog(tool.EnumLogType_Error, "解析<%s>字段时发生错误：该字段的类型为空", field.CnName)
		return false
	}

	// 识别字段类型
	field.FieldType = GetInternalTypeByName(&strCellFieldType)
	if FieldType_none == field.FieldType {
		jobCenter.Log.AddLog(tool.EnumLogType_Error, "解析<%s>字段时发生错误：不支持<%s>类型的字段", field.CnName, strCellFieldType)
		return false
	}

	// 如果是程序自定义的类型（格式program=具体的自定义类型），则取出参数
	if field.FieldType == FieldType_program {
		// 搜索=号
		var programNameIndex int = strings.Index(strCellFieldType, "=")
		if programNameIndex >= 0 {
			// 取出=号后面的程序名
			var length int = len(strCellFieldType)
			var programName string = strCellFieldType[programNameIndex+1 : length]
			field.FieldTypeArgument = programName
		}

		if field.FieldTypeArgument == "" {
			jobCenter.Log.AddLog(tool.EnumLogType_Error, "解析<%s>字段时发生错误：该字段<%s>未指定program的参数", field.CnName, strCellFieldType)
			return false
		}
	}

	// 取出字段属性
	var strCellFieldAttr string = strings.Trim(tool.GetCellString(sheet, sheetInfo.RowFieldRegionBegin+int(FieldRow_Attr), col), " \t")

	field.AttributeMap = make(map[string]string)
	field.AttributeText = strCellFieldAttr

	// 解析自定义属性列表
	if strCellFieldAttr != "" {
		var strAttributeArray []string = strings.Split(strCellFieldAttr, "|")
		for i := 0; i < len(strAttributeArray); i++ {
			var strAttribute = strAttributeArray[i]
			if strAttribute == "" {
				jobCenter.Log.AddLog(tool.EnumLogType_Error, "解析<%s>字段的<%s>中的属性<%s>时发生错误：不支持空属性", field.CnName, strCellFieldAttr, strAttribute)
				return false
			}

			var length int = len(strAttribute)

			var delimIndex int = strings.Index(strAttribute, "=")

			// 键
			var key string

			// 值
			var value string = ""

			// 搜索到=号
			if delimIndex >= 0 {
				// 取出=号前面的键
				key = strAttribute[0:delimIndex]

				// 取出=号后面的值
				value = strAttribute[delimIndex+1 : length]

				// jobCenter.Log.AddLog(tool.EnumLogType_Info, "自定义属性：<%s>字段%s=%s", field.CnName, key, value)
			} else {
				// 若未搜索到=号，取出=号前面的键
				key = strAttribute
			}

			// 记录下键值对
			field.AttributeMap[key] = value
		}
	}

	return true
}

// 解析字段定义区
func (jobCenter *JobCenter) ParseFieldsRegion(sheet *xlsx.Sheet, rowCount int, colCount int, sheetInfo *SheetInfo) bool {
	if 0 == sheetInfo.RowFieldRegionBegin {
		jobCenter.Log.AddLog(tool.EnumLogType_Error, "错误：未找到字段定义区<%d>", sheetInfo.RowFieldRegionBegin)
		return false
	}

	var isSuccess bool = true

	var field FieldInfo

	// 从第一列开始，一列一列往右解析各字段，直到碰到空列
	for col := 1; col <= colCount; col++ {
		// 解析该字段
		var ok bool = jobCenter.ParseField(sheet, sheetInfo, col, &field)
		if false == ok {
			isSuccess = false
			continue
		}

		// 碰到空字段则停止解析
		if field.EnName == "" {
			break
		}

		var oldField *FieldInfo = sheetInfo.GetField(&field.EnName)
		if oldField != nil {
			jobCenter.Log.AddLog(tool.EnumLogType_Error, "错误：定义了两个同样地字段<%s>", field.EnName)
			jobCenter.Log.AddLog(tool.EnumLogType_Error, "       <%-6s = %s>", oldField.GetInternalTypeName(), oldField.EnName)
			jobCenter.Log.AddLog(tool.EnumLogType_Error, "       <%-6s = %s>", field.GetInternalTypeName(), field.EnName)

			isSuccess = false
			continue
		}

		// 添加该字段
		sheetInfo.Fields = append(sheetInfo.Fields, field)
	}

	// 检查：至少要有一个字段
	if len(sheetInfo.Fields) == 0 {
		jobCenter.Log.AddLog(tool.EnumLogType_Error, "错误：未给<%s>表定义字段", sheetInfo.CnName)
		return false
	}

	return isSuccess
}

// 解析数据区
func (jobCenter *JobCenter) ParseData(sheet *xlsx.Sheet, rowCount int, colCount int, sheetInfo *SheetInfo) bool {
	// 文件是否为空
	var isDataEmpty bool = (sheetInfo.RowDataRegionBegin+1 > rowCount)
	if isDataEmpty {
		return true
	}

	var ok bool = true

	var fieldCount int = len(sheetInfo.Fields)

	sheetInfo.Rows = make(RowArray, rowCount-sheetInfo.RowDataRegionBegin)

	// 将数据区的行和列存入对应的数组
	for row := int(sheetInfo.RowDataRegionBegin + 1); row <= rowCount; row++ {
		// 该行是否为空
		var isRowEmpty bool = false
		var r Row = make(Row, fieldCount)

		for col := 1; col <= fieldCount; col++ {
			var cell string = tool.GetCellString(sheet, row, col)
			if cell == "" {
				var field *FieldInfo = &sheetInfo.Fields[col-1]
				if field.IsNumber() {
					cell = "0"
				}
			}

			cell = strings.Replace(cell, "\"", "\\\"", -1)
			//cell = strings.Replace(cell, "{", "\\{", -1)
			//cell = strings.Replace(cell, "}", "\\}", -1)

			r[col-1] = cell

			// 一旦出现某行的第一个单元格为空、或该单元格以//开头，则认为该行是注释，跳过该行
			if 1 == col {
				if r[col-1] == "" {
					isRowEmpty = true
					break
				}
			}
		}

		if isRowEmpty {
			break
		}

		sheetInfo.Rows[row-sheetInfo.RowDataRegionBegin-1] = r
	}

	return ok
}

// 解析单个工作表
func (jobCenter *JobCenter) ParseSheet(sheet *xlsx.Sheet) bool {
	var sheetInfo SheetInfo

	// 1. 获取excel表的行数和列数
	var rowCount int = tool.GetRowCount(sheet)
	var colCount int = tool.GetColumCount(sheet)

	if 0 == rowCount || 0 == colCount {
		jobCenter.Log.AddLog(tool.EnumLogType_Error, "跳过解析<%s>表，该表内容为空", sheet.Name)
		return false
	}

	if rowCount < ExcelRow_Min {
		jobCenter.Log.AddLog(tool.EnumLogType_Error, "分析<%s>失败：表格中当前只有<%u>行，至少应有<%u>行", sheet.Name, rowCount, ExcelRow_Min)
		return false
	}

	if colCount < 1 {
		jobCenter.Log.AddLog(tool.EnumLogType_Error, "分析<%s>失败：表格中当前只有<%u>列，至少应有<%u>列", sheet.Name, colCount, 1)
		return false
	}

	// 2. 取出工作表的名称
	sheetInfo.CnName = sheet.Name

	var ok bool = true

	// 3. 解析各个区域的起始行，共有3个区域：文件定义区、字段定义区、数据区
	ok = ok && jobCenter.ParseEachRegionBeginRow(sheet, rowCount, &sheetInfo)

	// 4. 解析文件定义区
	ok = ok && jobCenter.ParseTopRegion(sheet, rowCount, &sheetInfo)

	// 5. 解析字段定义区
	ok = ok && jobCenter.ParseFieldsRegion(sheet, rowCount, colCount, &sheetInfo)

	// 6. 载入数据区
	ok = ok && jobCenter.ParseData(sheet, rowCount, colCount, &sheetInfo)

	if !ok {
		return false
	}

	// 检查：工作表的表名不能冲突
	var conflict *SheetInfo = jobCenter.TargetExcel.FindByEnName(&sheetInfo.EnName)
	if nil != conflict {
		jobCenter.Log.AddLog(tool.EnumLogType_Error, "错误：定义了两个同样地文件<%s>", sheetInfo.CnName)
		jobCenter.Log.AddLog(tool.EnumLogType_Error, "       <%s = %s>", conflict.CnName, conflict.EnName)
		jobCenter.Log.AddLog(tool.EnumLogType_Error, "       <%s = %s>", sheetInfo.CnName, sheetInfo.EnName)

		return false
	}

	// 将工作表信息加到数组
	jobCenter.TargetExcel.Sheets = append(jobCenter.TargetExcel.Sheets, sheetInfo)
	return ok
}

// 解析excel文件
func (jobCenter *JobCenter) ParseExcel() bool {
	// 检查：excel文件必须存在
	if false == tool.Exist(jobCenter.ExcelPath) {
		jobCenter.Log.AddLog(tool.EnumLogType_Error, "错误: 找不到excel文件<%s>", jobCenter.ExcelPath)
		return false
	}

	// 开始计时
	var parseClock tool.Clock
	parseClock.StartTick()

	// 1. 载入excel文件
	xlFile, err := xlsx.OpenFile(jobCenter.ExcelPath)
	if err != nil {
		jobCenter.Log.AddLog(tool.EnumLogType_Error, "错误：解析<%s>文件失败，请确保该文件存在且未被打开! 错误信息 = %s", jobCenter.ExcelPath, err.Error())
		return false
	}

	// 2. 依次解析各个工作表
	var ok bool = true

	for _, sheet := range xlFile.Sheets {
		if !jobCenter.ParseSheet(sheet) {
			ok = false
		}
	}

	// 结束计时
	var cost float64 = parseClock.EndTick()

	var excelFileName string = tool.StripDir(jobCenter.ExcelPath)

	jobCenter.Log.AddLog(tool.EnumLogType_Warn, "解析<%s>完毕, 共耗时<%f>秒", excelFileName, cost)
	return ok
}

// 内部字段类型
var g_InternalTypeNames = [FieldType_max + 1]string{"", "string", "bool", "char", "int16", "int", "int64", "uint8", "uint16", "uint", "uint64", "float", "double", "program"}

// 返回内部字段类型的名称
func (f *FieldInfo) GetInternalTypeName() string {
	return g_InternalTypeNames[f.FieldType]
}

// 根据名称找到相应的内部字段类型
func GetInternalTypeByName(fieldTypeName *string) EnumFieldType {
	if "" == *fieldTypeName {
		return FieldType_none
	}

	// 基本类型，例如int、string
	for i := FieldType_none + 1; i < FieldType_max; i++ {
		if g_InternalTypeNames[i] == *fieldTypeName {
			return EnumFieldType(i)
		}
	}

	// 程序自定义，例如program=c++
	if strings.HasPrefix(*fieldTypeName, "program=") {
		return FieldType_program
	}

	return FieldType_none
}
