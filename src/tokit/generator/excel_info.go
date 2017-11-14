// @摘　要: 用于存储excel文件的整体定义
package generator

import (
	"fmt"
	"reflect"
	"strings"
)

// 正常来说各个功能区域的起始行
const (
	excel_row_cfg    = 1 // 文件配置区的起始行序号
	excel_row_fields = 4 // 字段定义区的起始行序号
	excel_row_data   = 8 // 表格数据区的起始行序号
	excel_row_min    = 9 // 至少应有几行
)

// 定义起始行（以防以后换excel库第一行从0开始）
const (
	cfg_row_1 = 1
)

// 定义起始列（以防以后换excel库第一列从0开始）
const (
	cfg_col_1 = 1
)

const (
	field_row_EnName    = int(iota) // 字段名
	field_row_data_type             // 字段类型
	field_row_attr                  // 字段属性
	Field_row_max
)

type enum_tokit_field_type uint8

// tokit原生类型
const (
	FieldType_none    = enum_tokit_field_type(iota)
	FieldType_string  // 字符串
	FieldType_bool    // bool类型
	FieldType_int8    // 8位整数
	FieldType_int16   // 16位整数
	FieldType_int32   // 32位整数
	FieldType_int64   // 64位整数
	FieldType_uint8   // 无符号的8位整数
	FieldType_uint16  // 无符号的16位整数
	FieldType_uint32  // 无符号的32位整数
	FieldType_uint64  // 无符号的64位整数
	FieldType_float   // 浮点数
	FieldType_double  // 双精度浮点数
	FieldType_program // 程序自定义
	FieldType_max
)

// 字段属性
type enum_field_attr uint8

const (
	FieldAttr_none  = enum_field_attr(iota) // 默认，表明本字段是普通成员
	FieldAttr_KeyN                          // 本字段将与其它字段构成主键
	FieldAttr_Key                           // 本字段的值唯一
	FieldAttr_Array                         // 数组
	FieldAttr_Set                           // 集合
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
	FieldType enum_tokit_field_type // 数据类型
	FieldAttr enum_field_attr       // 字段属性，目前分为：唯一、主键、数组、集合
	CnName    string                // 中文字段名称
	EnName    string                // 英文字段名称
	Comment   string                // 注释
}

// text template中的字段类型
var g_TemplateFieldTypes [FieldType_max + 1]string

// text template中的字段属性描述
var g_FieldAttrDescribe = [FieldAttr_Max + 1]string{"", "主键", "唯一", "数组", "集合"}

// 返回字段属性的中文描述
func (f *FieldInfo) GetFieldAttrDescribe() string {
	return g_FieldAttrDescribe[f.FieldAttr]
}

// 字段是否主键
func (f *FieldInfo) IsKey() bool {
	return FieldAttr_Key == f.FieldAttr
}

// 本字段是否与其它字段构成主键
func (f *FieldInfo) IsKeyN() bool {
	return FieldAttr_KeyN == f.FieldAttr
}

func (f *FieldInfo) IsArray() bool {
	return FieldAttr_Array == f.FieldAttr
}

func (f *FieldInfo) IsSet() bool {
	return FieldAttr_Set == f.FieldAttr
}

func (f *FieldInfo) IsNumber() bool {
	return FieldType_bool <= f.FieldType && f.FieldType < FieldType_max
}

func (f *FieldInfo) IsInteger() bool {
	return FieldType_bool <= f.FieldType && f.FieldType < FieldType_max
}

// 本字段是否为程序自定义的字段
func (f *FieldInfo) IsProgram() bool {
	return FieldType_program == f.FieldType
}

type KeyArray []uint8

type RowData []string
type RowArray []RowData

// 配置结构定义，与excel文件中的一个工作表相对应，描述了单个工作表的结构
type SheetInfo struct {
	CnName              string             // 配置定义文件的名称，可为中文
	EnName              string             // 配置的名称，必须为英文
	Maxcnt              int                // 最多有几条数据
	RowTopRegionBegin   int                // 文件定义区的起始行
	RowFieldRegionBegin int                // 字段定义区的起始行
	RowDataRegionBegin  int                // 配置数据区的起始行
	VerticalType        enum_vertical_type // 表格类型
	Fields              []FieldInfo        // 各成员
	Keys                KeyArray           // 主键索引列表（某个字段如果是主键，则将其索引加入到这个列表）
	Rows                RowArray           // 数据表
}

// 根据字段名获取字段
func (self *SheetInfo) GetField(fieldName *string) *FieldInfo {
	for _, v := range self.Fields {
		if v.EnName == *fieldName {
			return &v
		}
	}

	return nil
}

func (self *SheetInfo) IsVertical() bool {
	return VerticalType_Vertical == self.VerticalType
}

// excel文件信息，描述了excel文件内部各个工作表的结构
type ExcelInfo struct {
	ExcelPath string      // excel文件路径
	ClassName string      // 程序类名
	Sheets    []SheetInfo // 各个工作表
}

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

// 返回字段类型的名称
func RegisterFieldTypeName(fieldType enum_tokit_field_type, filedTypeName string) string {
	g_TemplateFieldTypes[fieldType] = filedTypeName
	return ""
}

// 返回字段属性描述
func RegisterFieldAttrDescribe(fieldAttr enum_field_attr, filedAttrDescribe string) string {
	g_FieldAttrDescribe[fieldAttr] = filedAttrDescribe
	return ""
}

// 返回字段类型的名称
func (f *FieldInfo) GetFieldTypeName() string {
	return g_TemplateFieldTypes[f.FieldType]
}

// 返回字段类型的名称
func (self *SheetInfo) GetFieldNameAtIndex(slot int) string {
	var field *FieldInfo = &self.Fields[slot]
	return field.EnName
}

func (self *SheetInfo) GetFieldAtIndex(slot int) *FieldInfo {
	var field *FieldInfo = &self.Fields[slot]
	return field
}

func (self *SheetInfo) GetFieldTypeAtIndex(slot int) enum_tokit_field_type {
	var field *FieldInfo = &self.Fields[slot]
	return field.FieldType
}

func Trim(text string) string {
	return strings.Trim(text, " \n\r")
}

// indirect returns the item at the end of indirection, and a bool to indicate if it's nil.
func indirect(v reflect.Value) (rv reflect.Value, isNil bool) {
	for ; v.Kind() == reflect.Ptr || v.Kind() == reflect.Interface; v = v.Elem() {
		if v.IsNil() {
			return v, true
		}
	}
	return v, false
}

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
