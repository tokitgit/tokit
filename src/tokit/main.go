//< @摘　要: tokit主入口

// main
package main

import (
	"os"
	"strings"
	"tokit/generator"
	"tokit/tool"
)

func main() {
	argc := len(os.Args)

	if argc < 2 {
		tool.EchoErr("参数格式错误，格式应为：")
		tool.EchoErr("   excel文件的路径  命令1  命令1的参数  命令2  命令2的参数...")
		tool.EchoErr("   比如: e:/hello.xlsx  -xsd  ../xsd/  -xml ../xml/")

		return
	}

	var excel string = os.Args[1]     // excel文件的路径
	var excelInfo generator.ExcelInfo // excel文件信息

	// 解析excel文件，结果存放在 excelInfo 中
	if !generator.ParseExcel(&excel, &excelInfo) {
		return
	}

	var jobCenter generator.JobCenter

	// 根据传入参数，开始执行命令，这里不打算用goroutine，因为不方便将错误提示打印到控制台
	var index int = 2
	for index < argc {
		var cmd string = os.Args[index]
		index++

		switch {
		case cmd == "-template":
			if index >= argc {
				tool.EchoErr("参数错误：-template后应跟上至少一个模板文件，格式应为: ")
				tool.EchoErr("   -template  模板文件1 模板文件2 ... -out 生成文件夹")
				return
			}

			var templateList []string
			var outDir string = "."
			var jobType generator.EnumJobType = generator.JobType_None

			for index < argc {
				var arg string = os.Args[index]
				if arg == "-out" {
					// '-out'参数后跟一个文件夹路径
					if index >= argc {
						tool.EchoErr("参数错误：-out后应跟上文件夹路径")
						return
					}

					if !tool.ExistDir(outDir) {
						tool.EchoErr("参数错误：-out所指定的文件夹<%s>路径不存在", outDir)
						return
					}

					outDir = os.Args[index+1]
					jobType = generator.JobType_AllInOne
					index += 2
					break
				} else if arg == "-split-out" {
					// '-split-out'参数后跟一个文件夹路径
					if index >= argc {
						tool.EchoErr("参数错误：-split-out后应跟上文件夹路径")
						return
					}

					if !tool.ExistDir(outDir) {
						tool.EchoErr("参数错误：-split-out所指定的文件夹<%s>路径不存在", outDir)
						return
					}

					outDir = os.Args[index+1]
					jobType = generator.JobType_Split
					index += 2
					break
				} else if strings.HasPrefix(arg, "-") {
					// 此处忽略其他参数
					break
				} else {
					// 模板文件
					var templateFile string = arg

					// 检查：模板文件应存在
					if !tool.ExistFile(templateFile) {
						tool.EchoErr("参数错误：-template所指定的文件路径<%s>不存在", templateFile)
						return
					}

					templateList = append(templateList, templateFile)
					index++
				}
			}

			for _, templateFile := range templateList {
				var job generator.Job
				job.ExcelInfo = &excelInfo
				job.TemplateFile = templateFile
				job.OutDir = outDir
				job.JobType = jobType
				jobCenter.JobList = append(jobCenter.JobList, job)
			}
		}
	}

	jobCenter.Work()
}
