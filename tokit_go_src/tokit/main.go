///<------------------------------------------------------------------------------
//< @文件名：main.cpp
//< @作　者：洪坤安
//< @日　期: 2014年11月12日 14:21:42
//< @摘　要: tokit主入口
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

// main
package main

import (
	"os"
	"tokit/generator"
	"tokit/generator/cpp"
	"tokit/generator/json"
	"tokit/generator/xml"
	"tokit/generator/xsd"
	"tokit/generator/go"
	"tokit/tool"
)

func main() {
	argc := len(os.Args)

	if argc < 2 {
		tool.EchoErr("参数格式错误，格式应为：")
		tool.EchoErr("   excel文件的路径  命令1  命令1的参数  命令2  命令2的参数...")
		tool.EchoErr("   比如: e:/hello.xlsx  -xsd  ../xsd/  -saveasxml ../xml/")

		return
	}

	var parse_option generator.Enum_parse_option = generator.GetParseOption(os.Args)

	var excel string = os.Args[1]   // excel文件的路径
	var cfgbase generator.Cfgbase_t // 存放excel文件的结构信息

	// 解析excel文件，结果存放在 cfgbase 中
	if !generator.ParseExcel(&excel, parse_option, &cfgbase) {
		return
	}

	// 根据传入参数，开始执行命令，这里不打算用goroutine，因为不方便将错误提示打印到控制台
	var pos int = 2
	for pos < argc {
		var gen_clock tool.Clock
		gen_clock.Start_tick()
		
		var cmd string = os.Args[pos]
		pos++
		switch {
		case cmd == "-xsd":
			if pos+1 > argc {
				tool.EchoErr("生成xsd的命令错误，格式应为: ")
				tool.EchoErr("   -xsd 生成的xsd文件放到哪个文件夹下")
				tool.EchoErr("   比如: -xsd  ../xsd/")

				return
			}

			var xsd_dir string = os.Args[pos]
			pos++

			// 生成xsd文件
			xsd_gen := xsd.Xsd_generator{&cfgbase, xsd_dir}
			xsd_gen.Generate()
			
			tool.EchoWarn("生成xsd完毕, 共耗时<%f>秒", gen_clock.End_tick())
		case cmd == "-c++":
			if pos+3 > argc {
				tool.EchoErr("生成c++源代码文件的命令错误，格式应为: ")
				tool.EchoErr("   -c++  h模板文件 cpp模板文件 生成的c++文件放在哪个文件夹下")
				tool.EchoErr("   比如: -c++  ../h_template.h  ../cpp_template.cpp  ./c++/")

				return
			}

			var h_templet string = os.Args[pos]
			var cpp_templet string = os.Args[pos+1]
			var cpp_dir string = os.Args[pos+2]

			pos += 3

			// 生成c++文件
			cpp_gen := cpp.Cpp_generator{&cfgbase, cpp_dir, h_templet, cpp_templet}
			cpp_gen.Generate()
			
			tool.EchoWarn("生成c++完毕, 共耗时<%f>秒", gen_clock.End_tick())
		case cmd == "-go":
			if pos+2 > argc {
				tool.EchoErr("生成go源代码文件命令错误，格式应为: ")
				tool.EchoErr("   -go  go模板文件  生成的go文件放在哪个文件夹下")
				tool.EchoErr("   比如: -go  ../go_template.go   ./go/")

				return
			}

			// 生成go文件（未开放）
			var go_templet string = os.Args[pos]
			var go_dir string = os.Args[pos+1]
			pos += 2

			go_gen := golang.Go_generator{&cfgbase, go_templet, go_dir}
			go_gen.Generate()
			
			// tool.EchoWarn("生成c++完毕, 共耗时<%f>秒", gen_clock.End_tick())
		case cmd == "-saveasxml":
			if pos+1 > argc {
				tool.EchoWarn("导出xml文件的命令错误，格式应为: ")
				tool.EchoWarn("   -saveasxml  生成的xml文件存放在哪个文件夹下")
				tool.EchoWarn("   比如: -saveasxml  ./xml/")

				return
			}

			var xml_dir string = os.Args[pos]
			pos++

			// 生成xml文件
			xml_gen := xml.Xml_generator{&cfgbase, xml_dir}
			xml_gen.Generate()
			
			tool.EchoWarn("生成xml完毕, 共耗时<%f>秒", gen_clock.End_tick())
		case cmd == "-json":
			if pos+1 > argc {
				tool.EchoWarn("导出json文件的命令错误，格式应为: ")
				tool.EchoWarn("   -json  生成的json文件存放在哪个文件夹下")
				tool.EchoWarn("   比如: -json  ./json/")

				return
			}

			var json_dir string = os.Args[pos]
			pos++

			// 生成json文件
			json_gen := json.Json_generator{&cfgbase, json_dir}
			json_gen.Generate()
			
			tool.EchoWarn("生成json完毕, 共耗时<%f>秒", gen_clock.End_tick())
		}
	}

}
