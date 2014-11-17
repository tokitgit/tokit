///<------------------------------------------------------------------------------
//< @文件名：json_generator.cpp
//< @作　者：洪坤安
//< @日　期: 2014年11月12日 19:08:42
//< @摘　要: 生成json文件
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

// Json_generator
package json

import (
	"strings"
	"tokit/generator"
	"tokit/tool"
)

type Json_generator struct {
	M_cfgbase  *generator.Cfgbase_t
	M_json_dir string
}

func (x *Json_generator) Generate() {
	if false == tool.Exist(&x.M_json_dir) {
		tool.EchoErr("错误: <%s>路径不存在", x.M_json_dir)
		return
	}

	x.save_as_json()
}

func (x *Json_generator) save_as_json() {
	// 将excel中各个工作表数据导出到对应的json文件中
	for _, v := range x.M_cfgbase.Cfgs {
		var json string = x.M_json_dir + "\\" + v.En_name + ".json"

		var json_text string
		get_json_text(&v, &json_text)

		tool.WriteFile(&json, &json_text)
		tool.EchoOk("导出[%s] -> [%s]成功", v.Cn_name, json)
	}
}

// 转码:
//     1. 引号 -> &quot;
func escape_json(str *string) {
	*str = strings.Replace(*str, "\"", "&quot;", -1)
}

// 将数据拼接成json格式
func get_json_text(cfg *generator.Cfg_t, json_text *string) {
	*json_text = "{\n\"%cfg%\": [\n"

	*json_text = strings.Replace(*json_text, "%cfg%", cfg.En_name, -1)

	var row_text string

	var n_row int = len(cfg.Table)
	var n_field int = len(cfg.Fields)
	for r, row := range cfg.Table {
		// 将数据拼接成形如{"a"="a1" "b"="b1" "c"="c1"....}的一行json文本
		row_text = "	{"

		for col := 0; col < n_field; col++ {
			escape_json(&row[col])
			row_text += "\"" + cfg.Fields[col].En_name + "\":\"" + row[col] + "\""

			if col+1 < n_field {
				row_text += ","
			}
		}

		if r+1 < n_row {
			row_text += "},\n"
		} else {
			row_text += "}\n"
		}

		*json_text += row_text
	}

	*json_text += "]}"
}
