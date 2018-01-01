//----------------------------------------------
// 摘　要: 用于存储excel文件的整体定义
//----------------------------------------------

package generator

import (
	"bytes"
	"encoding/binary"
	"errors"
	"fmt"
	"mahonia"
	"reflect"
	"strconv"
	"strings"
)

// 正常来说各个功能区域的起始行
const (
	ExcelRow_FileRegion  = 1 // 文件配置区的起始行序号
	ExcelRow_FieldRegion = 4 // 字段定义区的起始行序号
	ExcelRow_DataRegion  = 8 // 表格数据区的起始行序号
	ExcelRow_Min         = 9 // 至少应有几行
)

// 定义起始行（以防以后换excel库第一行从0开始）
const (
	FirstRow = 1
)

// 定义起始列（以防以后换excel库第一列从0开始）
const (
	FirstCol = 1
)

const (
	FieldRow_EnName    = int(iota) // 字段名
	FieldRow_FieldType             // 字段类型
	FieldRow_Attr                  // 字段属性
	FieldRow_Max
)

type EnumFieldType uint8

// tokit原生类型
const (
	FieldType_none    = EnumFieldType(iota)
	FieldType_string  = 1  // 字符串
	FieldType_bool    = 2  // bool类型
	FieldType_int8    = 3  // 8位整数
	FieldType_int16   = 4  // 16位整数
	FieldType_int32   = 5  // 32位整数
	FieldType_int64   = 6  // 64位整数
	FieldType_uint8   = 7  // 无符号的8位整数
	FieldType_uint16  = 8  // 无符号的16位整数
	FieldType_uint32  = 9  // 无符号的32位整数
	FieldType_uint64  = 10 // 无符号的64位整数
	FieldType_float   = 11 // 浮点数
	FieldType_double  = 12 // 双精度浮点数
	FieldType_program = 13 // 程序自定义
	FieldType_max
)

// 字段属性
type EnumFieldAttr uint8

const (
	FieldAttr_none  = EnumFieldAttr(iota) // 默认，表明本字段是普通成员
	FieldAttr_Key                         // 本字段的值唯一
	FieldAttr_Array                       // 数组
	FieldAttr_Set                         // 集合
	FieldAttr_Max
)

// 表格类型：水平、垂直
type enum_vertical_type int

const (
	VerticalType_Horizontal = 1 // 水平
	VerticalType_Vertical   = 2 // 垂直
)

// 字段成员，描述该字段的内部属性
type FieldInfo struct {
	FieldType         EnumFieldType     // 数据类型
	FieldTypeArgument string            // 数据类型的参数（目前仅用于指代program=xxx中的xxx参数）
	CnName            string            // 中文字段名称
	EnName            string            // 英文字段名称
	Comment           string            // 注释
	AttributeMap      map[string]string // 自定义属性列表, <键=属性名，值=属性值>
	AttributeText     string            // 自定义属性文本（仅用于在生成的文件中加上注释）
	TagId             int               // 标签id
}

// golang模板注册的字段类型名
var g_registerTemplateFieldTypes [FieldType_max + 1]string

// 字段 - 返回字段属性的中文描述（用于生成注释）
func (f *FieldInfo) GetFieldAttrDescribe() string {
	return f.AttributeText
}

// 一行（由多个单元格组成）
type Row []string

// 多行
type RowArray []Row

// 配置结构定义，与excel文件中的一个工作表相对应，描述了单个工作表的结构
type SheetInfo struct {
	CnName              string             // 配置定义文件的名称，可为中文
	EnName              string             // 配置的名称，必须为英文
	Maxcnt              int                // 最多有几条数据
	RowTopRegionBegin   int                // 文件定义区的起始行
	RowFieldRegionBegin int                // 字段定义区的起始行
	RowDataRegionBegin  int                // 配置数据区的起始行
	VerticalType        enum_vertical_type // 表格类型
	IsOnlyOneLine       bool               // 是否只有一行
	Fields              []FieldInfo        // 各成员
	Rows                RowArray           // 数据表
}

func (self *SheetInfo) IsVertical() bool {
	return VerticalType_Vertical == self.VerticalType
}

// excel文件信息 - 描述了excel文件内部各个工作表的结构
type ExcelInfo struct {
	ExcelPath string      // excel文件路径
	ClassName string      // 程序类名
	Sheets    []SheetInfo // 各个工作表
}

//******************** 备注：下面的所有方法均可以在tempate文件中直接调用 ********************//

// 暂时用不到的方法 - indirect returns the item at the end of indirection, and a bool to indicate if it's nil.
func indirect(v reflect.Value) (rv reflect.Value, isNil bool) {
	for ; v.Kind() == reflect.Ptr || v.Kind() == reflect.Interface; v = v.Elem() {
		if v.IsNil() {
			return v, true
		}
	}
	return v, false
}

// excel文件 - 根据工作表的名称查找工作表
func (excelInfo *ExcelInfo) FindByEnName(EnName *string) *SheetInfo {
	if "" == *EnName {
		return nil
	}

	for _, v := range excelInfo.Sheets {
		if v.EnName == *EnName {
			return &v
		}
	}

	return nil
}

// 工作表 - 根据字段名获取字段
func (self *SheetInfo) GetField(fieldName *string) *FieldInfo {
	for _, v := range self.Fields {
		if v.EnName == *fieldName {
			return &v
		}
	}

	return nil
}

// 工作表 - 返回指定索引的字段的类型名
func (self *SheetInfo) GetFieldNameAtIndex(slot int) string {
	var field *FieldInfo = &self.Fields[slot]
	return field.EnName
}

// 工作表 - 获取指定索引的字段
func (self *SheetInfo) GetFieldAtIndex(slot int) *FieldInfo {
	var field *FieldInfo = &self.Fields[slot]
	return field
}

// 工作表 - 获取指定索引的字段的类型
func (self *SheetInfo) GetFieldTypeAtIndex(slot int) EnumFieldType {
	var field *FieldInfo = &self.Fields[slot]
	return field.FieldType
}

// 工作表 - 获取行数
func (self *SheetInfo) GetRowCount() int {
	return len(self.Rows)
}

// 工作表 - 获取行数（返回字节数组）
func (self *SheetInfo) GetRowCountBytes() string {
	var rowCount = len(self.Rows)
	var buf *bytes.Buffer = new(bytes.Buffer)
	var writeError error = binary.Write(buf, binary.LittleEndian, int32(rowCount))

	if writeError != nil {
		fmt.Println("错误:", self.CnName, ", 将行数 = ", rowCount, "写入buf时失败，错误 = ", writeError.Error())
		return ""
	}

	var bytesString string = buf.String()
	if bytesString == "" {
		fmt.Println("错误:", self.CnName, ", 将行数 = ", rowCount, "写入buf时失败，转成bytes后为空，bytes = ", buf.Bytes(), ",长度=", buf.Len(), ",容量=", buf.Cap())
	}

	return bytesString
}

// 字段 - 返回字段的类型名
func (f *FieldInfo) GetFieldTypeName() string {
	return g_registerTemplateFieldTypes[f.FieldType]
}

// 字段 - 是否是数字
func (f *FieldInfo) IsNumber() bool {
	return FieldType_bool <= f.FieldType && f.FieldType < FieldType_max
}

// 字段 - 是否字符串
func (f *FieldInfo) IsString() bool {
	return FieldType_string == f.FieldType
}

// 字段 - 是否bool值
func (f *FieldInfo) IsBool() bool {
	return FieldType_bool == f.FieldType
}

// 字段 - 是否8位整数
func (f *FieldInfo) IsChar() bool {
	return FieldType_int8 == f.FieldType
}

// 字段 - 是否16位整数
func (f *FieldInfo) IsInt16() bool {
	return FieldType_int16 == f.FieldType
}

// 字段 - 是否32位整数
func (f *FieldInfo) IsInt() bool {
	return FieldType_int32 == f.FieldType
}

// 字段 - 是否64位整数
func (f *FieldInfo) IsInt64() bool {
	return FieldType_int64 == f.FieldType
}

// 字段 - 是否浮点数
func (f *FieldInfo) IsFloat() bool {
	return FieldType_float == f.FieldType
}

// 字段 - 是否双精度浮点数
func (f *FieldInfo) IsDouble() bool {
	return FieldType_double == f.FieldType
}

// 字段 - 本字段是否为程序自定义的字段
func (f *FieldInfo) IsProgram() bool {
	return FieldType_program == f.FieldType
}

// 字段 - 本字段是否为程序自定义的字段
func (f *FieldInfo) IsProgramByName(programName string) bool {
	if FieldType_program != f.FieldType {
		return false
	}

	return strings.Contains(f.FieldTypeArgument, programName)
}

// 字段 - 是否拥有指定属性
func (f *FieldInfo) HasAttribute(attributeName string) bool {
	_, ok := f.AttributeMap[attributeName]
	return ok
}

// 字段 - 是否拥有指定的多个属性
func (f *FieldInfo) HasAttributeList(arrayAttributeName []string) bool {
	for i := 0; i < len(arrayAttributeName); i++ {
		var attributeName string = arrayAttributeName[i]
		if f.HasAttribute(attributeName) {
			return true
		}
	}

	return false
}

// 字段 - 获取指定属性的值
// 参数attributeName：属性名
// 参数defaultValue：找不到属性、或属性值为空字符串时，默认返回该值
func (f *FieldInfo) GetAttributeValue(attributeName string, defaultValue string) string {
	value, ok := f.AttributeMap[attributeName]
	if !ok {
		return defaultValue
	}

	if value == "" {
		return defaultValue
	}

	return value
}

// 字段 - 指定的属性值中是否包含指定的字符串，找不到属性时返回false
func (f *FieldInfo) IsAttributeContainValue(attributeName string, attributeValue string) bool {
	value, ok := f.AttributeMap[attributeName]
	if !ok {
		return false
	}

	return strings.Contains(value, attributeValue)
}

// 字段 - 是否指定了该属性的值，找不到属性时返回true（备注：这里与IsAttributeContainValue方法相反）
func (f *FieldInfo) IsAttributeSpecifyValue(attributeName string, attributeValue string) bool {
	value, ok := f.AttributeMap[attributeName]
	if !ok {
		return true
	}

	return strings.Contains(value, attributeValue)
}

// 字段 - 将本字段的文本转为二进制
func (f *FieldInfo) GetBytes(text string) string {
	var attributeNameOfArray string = "数组"
	var attributeNameOfSet string = "集合"

	// 如果是数组，则拆分后再转换
	if f.HasAttribute(attributeNameOfArray) {
		// fmt.Println("数组:", f.CnName, " = ", text)

		var buf bytes.Buffer

		var splitKey string = f.GetAttributeValue(attributeNameOfArray, " ")
		var splitArray []string = strings.Split(text, splitKey)
		var arraySize int = len(splitArray)

		// 先填充数组长度
		binary.Write(&buf, binary.LittleEndian, int32(arraySize))

		// 再填充数组中的每个元素
		for i := 0; i < arraySize; i++ {
			var splitText = splitArray[i]
			var splitBytes string = f.ConvertToBytes(splitText)
			buf.Write([]byte(splitBytes))
		}

		return buf.String()
	} else if f.HasAttribute(attributeNameOfSet) {
		return ""
	} else {
		return f.ConvertToBytes(text)
	}

	return ""
}

// 字段 - 将本字段的文本转为二进制（不考虑数组）
func (f *FieldInfo) ConvertToBytes(text string) string {
	// 检查：忽略程序自定义类型
	if f.FieldType == FieldType_program {
		return ""
	}

	// 检查：打印空串
	if len(Trim(text)) == 0 {
		if f.FieldType != FieldType_string {
			fmt.Println("错误:[", f.CnName, "]传入了空文本串 = ", text, ", 类型 = ", f.FieldType)
		}
	}

	var buf *bytes.Buffer = new(bytes.Buffer)
	// buf.WriteString(f.EnName + "=")

	var convertError error = nil
	var writeError error = nil

	switch f.FieldType {
	case FieldType_bool:
		boolValue, err := strconv.ParseBool(text)
		var byteValue byte = 1
		if !boolValue {
			byteValue = 0
		}

		binary.Write(buf, binary.LittleEndian, byteValue)
		convertError = err
		break

	case FieldType_int8:
		int8Value, err := strconv.Atoi(text)
		writeError = binary.Write(buf, binary.LittleEndian, byte(int8Value))
		convertError = err
		break

	case FieldType_int16:
		int16Value, err := strconv.Atoi(text)
		writeError = binary.Write(buf, binary.LittleEndian, int16(int16Value))
		convertError = err
		break

	case FieldType_int32:
		intValue, err := strconv.Atoi(text)
		writeError = binary.Write(buf, binary.LittleEndian, int32(intValue))
		convertError = err
		break

	case FieldType_int64:
		int64Value, err := strconv.ParseInt(text, 10, 64)
		writeError = binary.Write(buf, binary.LittleEndian, int64Value)
		convertError = err
		break

	case FieldType_float:
		floatValue, err := strconv.ParseFloat(text, 32)
		writeError = binary.Write(buf, binary.LittleEndian, float32(floatValue))
		convertError = err
		break

	case FieldType_double:
		doubleValue, err := strconv.ParseFloat(text, 64)
		writeError = binary.Write(buf, binary.LittleEndian, float64(doubleValue))
		convertError = err
		break

	case FieldType_string:
		// 转为中文编码
		enc := mahonia.NewEncoder("GB18030")
		if ret, ok := enc.ConvertStringOK(text); ok {
			// fmt.Println("UTF-8 to GBK: ", ret, " bytes: ", []byte(ret))
			text = string(ret)
		}

		var stringLength int = len(text)

		// 先填充字符串长度
		binary.Write(buf, binary.LittleEndian, int32(stringLength))

		// 再填充字符串内容
		_, writeStringError := buf.WriteString(text)
		writeError = writeStringError

		// fmt.Println("*****信息:", f.CnName, " 填充文本 = ", text, ", 类型 = ", f.FieldType, "，填充长度[", writeStringLength, "], 实际长度[", stringLength, "]")

		break

	default:
		convertError = errors.New("无法识别类型" + strconv.Itoa(int(f.FieldType)))
		break
	}

	if convertError != nil {
		fmt.Println("错误:", f.CnName, " 无法识别文本 = ", text, ", 类型 = ", f.FieldType, "错误 = ", convertError.Error())
		return ""
	}

	if writeError != nil {
		fmt.Println("错误:", f.CnName, ", 将文本 = ", text, ", 类型 = ", f.FieldType, "写入buf时失败，错误 = ", writeError.Error())
		return ""
	}

	var bytesString string = buf.String()
	if bytesString == "" {
		fmt.Println("错误:[", f.CnName, "],字段内容 = [", text, "], 类型 = [", f.FieldType, "]转成bytes后为空, bytes = ", buf.Bytes(), ",长度=", buf.Len(), ",容量=", buf.Cap())
	}

	// fmt.Println("-----:[", f.CnName, "],字段内容 = [", text, "], 类型 = [", f.FieldType, "]转成bytes后为空, bytes = ", buf.Bytes(), ",长度=", len(bytesString))

	return bytesString
}

// 可以直接调用的函数 - 取出开头和结尾的空占位符
func Trim(text string) string {
	return strings.Trim(text, " \n\r")
}

// 可以直接调用的函数 - 返回数组的后一个元素
func Tail(item interface{}) (int, error) {
	v := reflect.ValueOf(item)
	if !v.IsValid() {
		return 0, fmt.Errorf("len of untyped nil")
	}
	v, isNil := indirect(v)
	if isNil {
		return 0, fmt.Errorf("len of nil pointer")
	}

	switch v.Kind() {
	case reflect.Array, reflect.Chan, reflect.Map, reflect.Slice, reflect.String:
		var size int = v.Len()
		if size > 0 {
			return size - 1, nil
		}

		return 0, nil
	}
	return 0, fmt.Errorf("len of type %s", v.Type())
}

// 可以直接调用的函数 - 注册指定类型的类型名
func RegisterFieldTypeName(fieldType EnumFieldType, filedTypeName string) string {
	g_registerTemplateFieldTypes[fieldType] = filedTypeName
	return ""
}

// 可以直接调用的函数 - 注册字符串
func RegisterString(filedTypeName string) string {
	g_registerTemplateFieldTypes[FieldType_string] = filedTypeName
	return ""
}

// 可以直接调用的函数 - 注册bool
func RegisterBool(filedTypeName string) string {
	g_registerTemplateFieldTypes[FieldType_bool] = filedTypeName
	return ""
}

// 可以直接调用的函数 - 注册char
func RegisterChar(filedTypeName string) string {
	g_registerTemplateFieldTypes[FieldType_int8] = filedTypeName
	return ""
}

// 可以直接调用的函数 - 注册16位整数
func RegisterInt16(filedTypeName string) string {
	g_registerTemplateFieldTypes[FieldType_int16] = filedTypeName
	return ""
}

// 可以直接调用的函数 - 注册32位整数
func RegisterInt32(filedTypeName string) string {
	g_registerTemplateFieldTypes[FieldType_int32] = filedTypeName
	return ""
}

// 可以直接调用的函数 - 注册64位整数
func RegisterInt64(filedTypeName string) string {
	g_registerTemplateFieldTypes[FieldType_int64] = filedTypeName
	return ""
}

// 可以直接调用的函数 - 注册浮点数
func RegisterFloat(filedTypeName string) string {
	g_registerTemplateFieldTypes[FieldType_float] = filedTypeName
	return ""
}

// 可以直接调用的函数 - 注册双精度浮点数
func RegisterDouble(filedTypeName string) string {
	g_registerTemplateFieldTypes[FieldType_double] = filedTypeName
	return ""
}
