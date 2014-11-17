///<------------------------------------------------------------------------------
//< @文件名：cfg.cpp
//< @作　者：洪坤安
//< @日　期: 2014年11月17日 09:23:01
//< @摘　要: 用于存储excel文件的整体定义
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

// cfg
package generator

// 正常来说各个功能区域的起始行
type excel_row int

const (
	excel_row_cfg    = 1 // 文件配置区的起始行序号
	excel_row_fields = 4 // 字段定义区的起始行序号
	excel_row_data   = 8 // 表格数据区的起始行序号
	excel_row_min    = 9 // 至少应有几行
)

// 文件定义区
type excel_cfg_row int

const (
	cfg_row_1   = excel_row(1 + iota) // 从文件配置起的第一行
	Cfg_row_max                       // 最多有几行数据
)

type excel_cfg_col int

const (
	cfg_col_1 = iota + 1 // 第一列所对应的列序号
	cfg_col_2        // 第一列所对应的列序号

	Cfg_col_max
)

type excel_field_row uint8

const (
	field_row_en_name = excel_field_row(iota)
	field_row_data_type
	field_row_is_unique
	Field_row_max
)

type enum_tokit_field_type uint8

// tokit原生类型
const (
	Fieldtype_none   = enum_tokit_field_type(iota)
	Fieldtype_string // 字符串
	Fieldtype_bool   // bool类型
	Fieldtype_int8   // 8位整数
	Fieldtype_int16  // 16位整数
	Fieldtype_int32  // 32位整数
	Fieldtype_int64  // 64位整数
	Fieldtype_uint8  // 无符号的8位整数
	Fieldtype_uint16 // 无符号的16位整数
	Fieldtype_uint32 // 无符号的32位整数
	Fieldtype_uint64 // 无符号的64位整数
	Fieldtype_float  // 浮点数
	Fieldtype_double // 双精度浮点数
	Fieldtype_max
)

type Enum_parse_option uint8

// 解析excel的类型
const (
	parse_option_skip_data = 1 // 跳过数据解析，仅解析配置定义
	parse_option_read_data = 2 // 解析配置定义并载入数据)
)

// 字段属性
type enum_field_attr uint8

const (
	Fieldattr_none  = iota // 默认，表明本字段是普通成员
	Fieldattr_n_key        // 本字段将与其它字段构成主键
	Fieldattr_1_key        // 本字段的值唯一
	Fieldattr_array        // 数组
	Fieldattr_set          // 集合
	Fieldattr_max
)

// 字段成员，描述该字段的内部属性
type Field_t struct {
	Fieldtype enum_tokit_field_type // 数据类型
	Cn_name   string                // 中文字段名称
	En_name   string                // 英文字段名称
	Comment   string                // 注释

	Fieldattr enum_field_attr // 字段属性，目前分为：唯一、主键、数组、集合
}

// tokit可识别的数据类型数据
var g_tokit_types = [Fieldtype_max + 1]string{"", "string", "bool", "char", "int16", "int", "int64", "uint8", "uint16", "uint", "uint64", "float", "double"}

// 返回字段类型的名称
func (f *Field_t) get_field_type_name() string {
	return g_tokit_types[f.Fieldtype]
}

func type_name_2_enum(tokit_type *string) enum_tokit_field_type {
	if "" == *tokit_type {
		return Fieldtype_none
	}

	for i := Fieldtype_none + 1; i < Fieldtype_max; i++ {
		if g_tokit_types[i] == *tokit_type {
			return enum_tokit_field_type(i)
		}
	}

	return Fieldtype_none
}

// 每条记录中本字段的值是否都唯一
func (f *Field_t) Is_1_key() bool {
	return Fieldattr_1_key == f.Fieldattr
}

// 本字段是否与其它字段构成主键
func (f *Field_t) Is_n_key() bool {
	return Fieldattr_n_key == f.Fieldattr
}

func (f *Field_t) Is_array() bool {
	return Fieldattr_array == f.Fieldattr
}

func (f *Field_t) Is_set() bool {
	return Fieldattr_set == f.Fieldattr
}

type Fieldvec_t []Field_t
type keyvec_t []uint8

type row_t []string
type table_t []row_t

// 配置结构定义，与excel文件中的一个工作表相对应，描述了单个工作表的结构
type Cfg_t struct {
	Cn_name string // 配置定义文件的名称，可为中文
	En_name string // 配置的名称，必须为英文

	Fields Fieldvec_t // 各成员
	Keys   keyvec_t   // 主键索引列表（某个字段如果是主键，则将其索引加入到这个列表）

	Maxcnt int // 最多有几条数据

	row_file_cfg_begin int // 文件定义区的起始行
	row_fields_begin   int // 字段定义区的起始行
	row_data_begin     int // 配置数据区的起始行

	Table table_t // 数据表
}

// 根据字段名获取字段
func (cfg *Cfg_t) getfield(fieldname *string) *Field_t {
	for _, v := range cfg.Fields {
		if v.En_name == *fieldname {
			return &v
		}
	}

	return nil
}

func (cfg *Cfg_t) Only_has_1_row() bool {
	return 1 == cfg.Maxcnt
}

type cfgvec_t []Cfg_t

// 配置结构定义中心，与一整个excel文件相对应，描述了excel文件内部各个工作表的结构
type Cfgbase_t struct {
	Excel_path string   // 本结构对应的excel文件的路径
	Filename   string   // 本配置的文件名
	Cfgs       cfgvec_t // 各个工作表的描述
}

func (cfgbase *Cfgbase_t) find_by_en_name(en_name *string) *Cfg_t {
	if "" == *en_name {
		return nil
	}

	for _, v := range cfgbase.Cfgs {
		if v.En_name == *en_name {
			return &v
		}
	}

	return nil
}
