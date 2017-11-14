package generator

import (
	"bytes"
	"mahonia"
	"path/filepath"
	"text/template"
	"tokit/tool"
)

type EnumJobType int

// 采用哪种方式生成文件
const (
	JobType_None     = EnumJobType(iota)
	JobType_AllInOne // 多合一（即单个excel文件内的所有内容只生成到同一个文件）
	JobType_Split    // 拆分（即单个excel文件将被拆分生成到多个文件，每个工作表对应一个文件）
)

// 单个任务
type Job struct {
	ExcelInfo    *ExcelInfo  // excel文件数据
	TemplateFile string      // 模板文件路径
	OutDir       string      // 生成文件路径
	JobType      EnumJobType // 采用哪种方式生成文件
}

// 任务中心
type JobCenter struct {
	JobList []Job // 任务列表
}

func (self *JobCenter) Work() {
	for _, job := range self.JobList {
		job.Work()
	}
}

func (self *Job) Work() {
	if false == tool.Exist(&self.OutDir) {
		tool.EchoErr("参数错误: 找不到指定的文件夹来生成<%s>，请确认路径是否存在!", self.OutDir)
		return
	}

	if false == tool.Exist(&self.TemplateFile) {
		tool.EchoErr("参数错误: 找不到模板文件<%s>", self.TemplateFile)
		return
	}

	var ext string = tool.GetExt(self.TemplateFile)

	// 多合一模式：excel文件的内所有内容只生成到同一个文件
	if self.JobType == JobType_AllInOne {

		var out = tool.AppendPath(self.OutDir, self.ExcelInfo.ClassName) + "." + ext

		// 开始生成文件
		if !GenerateByTemplate(self.ExcelInfo, self.TemplateFile, out) {
			tool.EchoErr("生成文件<%s>失败", out)
			return
		}

		tool.EchoOk("生成文件<%s>成功", out)

	} else if self.JobType == JobType_Split {
		// 拆分模式：将excel中各个工作表数据导出到对应的文件中
		for _, cfg := range self.ExcelInfo.Sheets {
			var out string = tool.AppendPath(self.OutDir, cfg.EnName) + "." + ext

			// 开始生成文件
			if !GenerateByTemplate(&cfg, self.TemplateFile, out) {
				tool.EchoErr("生成文件<%s>失败", out)
				return
			}

			tool.EchoOk("导出[%s] -> [%s]成功", cfg.CnName, out)
		}
	}
}

// 根据模板文件进行导出
func GenerateByTemplate(data interface{}, teamplateFileName string, out string) bool {
	var funcs = template.FuncMap{
		"Trim":                      Trim,
		"RegisterFieldTypeName":     RegisterFieldTypeName,
		"RegisterFieldAttrDescribe": RegisterFieldAttrDescribe,
		"Tail": Tail,
	}

	var fileBase = filepath.Base(teamplateFileName)
	t := template.New(fileBase).Funcs(funcs)

	// 加载模板fileBase
	tpl, err := t.ParseFiles(teamplateFileName)
	if err != nil {
		panic(err)
	}

	var buf bytes.Buffer

	//将struct与模板合成，合成结果放到os.Stdout里
	err = tpl.Execute(&buf, data)
	if err != nil {
		panic(err)
	}

	var text string = buf.String()

	enc := mahonia.NewEncoder("GB18030")
	if ret, ok := enc.ConvertStringOK(text); ok {
		// fmt.Println("UTF-8 to GBK: ", ret, " bytes: ", []byte(ret))
		text = string(ret)
	}

	var overWriteOk bool = tool.OverWriteFile(&out, &text)
	return overWriteOk
}
