///<------------------------------------------------------------------------------
//< @文件名: parser.cpp
//< @作　者: 洪坤安
//< @日　期: 2014年11月12日 14:50:42
//< @摘　要: excel解析器
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

// parser
package generator

import (
	"strings"
	"tokit/tool"
	"xlsx"
)

func nothing(n string) {

}

// 解析出各个区域的起始行
func parse_each_region_begin_row(sheet *xlsx.Sheet, row_cnt int, cfg *Cfg_t, errvec *tool.Errvec_t) bool {
	// 1. 从空行开始往下找到文件定义区的起始行
	var is_find_file_cfg bool = false
	for row := excel_row_cfg; row < row_cnt; row += 1 {
		if !tool.Is_cell_empty(sheet, row, cfg_col_1) {
			cfg.row_file_cfg_begin = row
			is_find_file_cfg = true
			break
		}
	}

	if !is_find_file_cfg {
		*errvec = append(*errvec, tool.GetErrMsg("错误：未<%s>表定义文件英文名", cfg.Cn_name))
		return false
	}

	// 2. 从文件定义区开始，跳过空行往下找到字段定义区的起始行
	for row := cfg.row_file_cfg_begin + int(Cfg_row_max); row < row_cnt; row++ {
		if !tool.Is_cell_empty(sheet, row, cfg_col_1) {
			cfg.row_fields_begin = row
			break
		}
	}

	if 0 == cfg.row_fields_begin {
		*errvec = append(*errvec, tool.GetErrMsg("错误：未在<%s>表中找到字段定义", cfg.Cn_name))
		return false
	}

	// 3. 从字段定义区开始，跳过空行找到数据区的起始行
	for row := cfg.row_fields_begin + int(Field_row_max) + 1; row < row_cnt; row++ {
		if !tool.Is_cell_empty(sheet, row, cfg_col_1) {
			cfg.row_data_begin = row
			break
		}
	}

	if 0 == cfg.row_data_begin {
		*errvec = append(*errvec, tool.GetErrMsg("错误：未在<%s>表中找到数据", cfg.Cn_name))
		return false
	}

	return true
}

// 解析文件定义区
func parse_cfg(sheet *xlsx.Sheet, row_cnt int, cfg *Cfg_t, errvec *tool.Errvec_t) bool {
	// 文件名称
	cfg.En_name = tool.Get_cell_str(sheet, cfg.row_file_cfg_begin+int(cfg_row_1), int(cfg_col_1))

	// 最大数据条数
	cfg.Maxcnt = tool.Get_cell_int(sheet, cfg.row_file_cfg_begin+int(cfg_row_1), int(cfg_col_2))

	if cfg.En_name == "" {
		*errvec = append(*errvec, tool.GetErrMsg("分析<%s>失败：必须给表填上英文名", cfg.En_name))
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

func is_unique_key_by_str(str *string) bool {
	var is_unique_key bool = contain_1_of_n(str, "unique", "唯一")
	return is_unique_key
}

func is_primary_key_by_str(str *string) bool {
	var is_primary_key bool = contain_1_of_n(str, "primary", "主键")
	return is_primary_key
}

func is_array_by_str(str *string) bool {
	var is_array bool = contain_1_of_n(str, "vector", "vec", "array", "数组")
	return is_array
}

// 是否是集合类型
func is_set_by_str(str *string) bool {
	var is_set bool = contain_1_of_n(str, "set", "集合")
	return is_set
}

// 解析指定列的字段定义
func parse_field(sheet *xlsx.Sheet, cfg *Cfg_t, col int, field *Field_t, errvec *tool.Errvec_t) bool {
	// 取出字段英文名
	field.En_name = strings.Trim(tool.Get_cell_str(sheet, cfg.row_fields_begin+int(field_row_en_name), col), " \t")
	if field.En_name == "" {
		// 碰到空字段则停止解析
		return true
	}

	// 取出字段类型
	var fieldtype_cell string = strings.Trim(tool.Get_cell_str(sheet, cfg.row_fields_begin+int(field_row_data_type), col), " \t")
	field.Fieldtype = type_name_2_enum(&fieldtype_cell)

	// 取出字段属性
	var fieldattr_cell string = strings.Trim(tool.Get_cell_str(sheet, cfg.row_fields_begin+int(field_row_is_unique), col), " \t")

	field.Fieldattr = Fieldattr_none
	switch {
	case is_unique_key_by_str(&fieldattr_cell):
		field.Fieldattr = Fieldattr_1_key
	case is_primary_key_by_str(&fieldattr_cell):
		field.Fieldattr = Fieldattr_n_key
	case is_array_by_str(&fieldattr_cell):
		field.Fieldattr = Fieldattr_array
	case is_set_by_str(&fieldattr_cell):
		field.Fieldattr = Fieldattr_set
	}

	field.Cn_name = strings.Trim(tool.Get_cell_str(sheet, cfg.row_data_begin, col), " \t")
	field.Comment = field.Cn_name

	if field.Cn_name == "" {
		*errvec = append(*errvec, tool.GetErrMsg("解析第<%s>行时发生错误：中文名不允许为空", col))
		return false
	}

	if fieldtype_cell == "" {
		*errvec = append(*errvec, tool.GetErrMsg("解析<%s>字段时发生错误：该字段的类型为空", field.Cn_name))
		return false
	}

	if Fieldtype_none == field.Fieldtype {
		*errvec = append(*errvec, tool.GetErrMsg("解析<%s>字段时发生错误：不支持<%s>类型的字段", field.Cn_name, fieldtype_cell))
		return false
	}

	return true
}

// 解析字段定义区
func parse_fields(sheet *xlsx.Sheet, row_cnt int, col_cnt int, cfg *Cfg_t, errvec *tool.Errvec_t) bool {
	if 0 == cfg.row_fields_begin {
		return false
	}

	var succ bool = true

	var field Field_t

	// 从第一列开始，一列一列往右解析各字段，直到碰到空列
	for col := 1; col <= col_cnt; col++ {
		// 解析该字段
		var ok bool = parse_field(sheet, cfg, col, &field, errvec)
		if false == ok {
			succ = false
			continue
		}

		// 碰到空字段则停止解析
		if field.En_name == "" {
			break
		}

		var old_field *Field_t = cfg.getfield(&field.En_name)
		if old_field != nil {
			*errvec = append(*errvec, tool.GetErrMsg("错误：定义了两个同样地字段<%s>", field.En_name))
			*errvec = append(*errvec, tool.GetErrMsg("       <%-6s = %s>", old_field.get_field_type_name(), old_field.En_name))
			*errvec = append(*errvec, tool.GetErrMsg("       <%-6s = %s>", field.get_field_type_name(), field.En_name))

			succ = false
			continue
		}

		// 如果该字段是主键之一，则将该字段的位置存入主键列表
		if field.Is_n_key() {
			cfg.Keys = append(cfg.Keys, uint8(len(cfg.Fields)))
		}

		cfg.Fields = append(cfg.Fields, field)
	}

	if len(cfg.Fields) == 0 {
		*errvec = append(*errvec, tool.GetErrMsg("错误：未给<%s>表定义字段", cfg.Cn_name))
	}

	// 如果主键仅由1个字段组成，则将主键字段的属性替换为<唯一>
	n_key := len(cfg.Keys)
	if 1 == n_key {
		cfg.Fields[cfg.Keys[0]].Fieldattr = Fieldattr_1_key
		cfg.Keys = keyvec_t{}
	}

	return succ
}

// 解析配置数据区
func parse_data(sheet *xlsx.Sheet, row_cnt int, col_cnt int, cfg *Cfg_t, errvec *tool.Errvec_t) bool {
	var is_empty bool = (cfg.row_data_begin+1 > row_cnt)
	if is_empty {
		return true
	}

	is_ok := true

	var n_field int = len(cfg.Fields)

	cfg.Table = make(table_t, 0, row_cnt-cfg.row_data_begin)

	// 将数据区的行和列存入对应的数组
	for row := int(cfg.row_data_begin + 1); row <= row_cnt; row++ {
		var is_empty_row bool = false
		var r row_t = make(row_t, n_field)

		for col := 1; col <= n_field; col++ {
			r[col-1] = tool.Get_cell_str(sheet, row, col)

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

		cfg.Table = append(cfg.Table, r)
	}

	return is_ok
}

// 解析出单个工作表
func parse_sheet(sheet *xlsx.Sheet, cfg *Cfg_t, errvec *tool.Errvec_t, parse_option Enum_parse_option) bool {
	// 1. 获取excel表的行数和列数
	var row_cnt int = tool.Get_row_cnt(sheet)
	var col_cnt int = tool.Get_col_cnt(sheet)

	if 0 == row_cnt || 0 == col_cnt {
		*errvec = append(*errvec, tool.GetErrMsg("跳过解析<%s>表，该表内容为空", sheet.Name))
		return false
	}

	if row_cnt < excel_row_min {
		*errvec = append(*errvec, tool.GetErrMsg("分析<%s>失败：表格中当前只有<%u>行，至少应有<%u>行", sheet.Name, row_cnt, excel_row_min))
		return false
	}

	if col_cnt < int(Cfg_col_max-1) {
		*errvec = append(*errvec, tool.GetErrMsg("分析<%s>失败：表格中当前只有<%u>列，至少应有<%u>列", sheet.Name, col_cnt, Cfg_col_max-1))
		return false
	}

	// 2. 取出工作表的名称
	cfg.Cn_name = sheet.Name

	succ := true

	// 3. 解析各个区域的起始行，共有3个区域：文件定义区、字段定义区、数据区
	succ = succ && parse_each_region_begin_row(sheet, row_cnt, cfg, errvec)

	// 4. 解析文件定义区
	succ = succ && parse_cfg(sheet, row_cnt, cfg, errvec)

	// 5. 解析字段定义区
	succ = succ && parse_fields(sheet, row_cnt, col_cnt, cfg, errvec)

	// 6. 载入数据区
	if parse_option_read_data == parse_option {
		succ = succ && parse_data(sheet, row_cnt, col_cnt, cfg, errvec)
	}

	return succ
}

// 解析出excel中的各个工作表，将解析结果存入结构体
func parse_excel(excel *string, cfgbase *Cfgbase_t, errmsgs *tool.Errvec_t, parse_option Enum_parse_option) bool {
	var parse_clock tool.Clock
	parse_clock.Start_tick()

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
		var cfg Cfg_t

		// 2.1 解析出工作表的内容，并将结果存放到cfg中
		var ok bool = parse_sheet(sheet, &cfg, errmsgs, parse_option)
		if false == ok {
			succ = false
			continue
		}

		var conflict_by_prop *Cfg_t = cfgbase.find_by_en_name(&cfg.En_name)
		if nil != conflict_by_prop {
			*errmsgs = append(*errmsgs, tool.GetErrMsg("错误：定义了两个同样地文件<%s>", cfg.Cn_name))
			*errmsgs = append(*errmsgs, tool.GetErrMsg("       <%s = %s>", conflict_by_prop.Cn_name, conflict_by_prop.En_name))
			*errmsgs = append(*errmsgs, tool.GetErrMsg("       <%s = %s>", cfg.Cn_name, cfg.En_name))

			succ = false
			continue
		}

		cfgbase.Cfgs = append(cfgbase.Cfgs, cfg)
	}

	// 将第一个工作表名作为文件名（比如，excel中有2个工作表item、hero，则将item作为文件名）
	if len(cfgbase.Cfgs) > 0 {
		cfgbase.Filename = cfgbase.Cfgs[0].En_name
	}

	tool.EchoWarn("执行完毕, 共耗时<%f>秒", parse_clock.End_tick())
	return succ
}

// 解析excel文件
func ParseExcel(excel *string, parse_option Enum_parse_option, cfgbase *Cfgbase_t) bool {
	if false == tool.Exist(excel) {
		tool.EchoErr("错误: 找不到excel文件<%s>", *excel)
		return false
	}

	var errvec tool.Errvec_t
	if false == parse_excel(excel, cfgbase, &errvec, parse_option) {
		// tool.EchoErr("错误：解析<%s>文件失败，请确保该文件存在且未被打开", *excel)
		tool.Echo_errvec(&errvec)
		return false
	}

	return true
}

// 检测选项中是否含《--导出xml》选项，如果有则需要载入xml数据
func GetParseOption(args []string) Enum_parse_option {
	var parse_option Enum_parse_option = parse_option_skip_data
	for _, cmd := range args {
		switch {
		case cmd == "-saveasxml":
		case cmd == "-json":
			parse_option = parse_option_read_data
			break
		}
	}

	return parse_option
}
