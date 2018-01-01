//----------------------------------------------
// 摘　要: 根据excel的数据，通过golang模板文件生成对应的文件
//----------------------------------------------

package generator

import (
	"bytes"
	"mahonia"
	"path/filepath"
	"sync"
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

// 单个任务（每个golang模板文件对应一个任务）
type Job struct {
	TargetExcel     *ExcelInfo   // 目标excel文件信息
	TemplateFile    string       // golang模板文件路径
	OutDir          string       // 生成文件夹路径
	JobType         EnumJobType  // 采用哪种方式生成文件
	JobIndex        int          // 该任务的序号
	Log             tool.LogInfo // 执行该任务时产生的日志
	RelateJobCenter *JobCenter   // 任务中心指针
}

// 任务中心（一个excel文件对应一个任务中心）
type JobCenter struct {
	TargetExcel ExcelInfo      // 目标excel文件信息
	ExcelPath   string         // excel路径
	JobList     []*Job         // 任务列表
	Log         tool.LogInfo   // 解析excel文件时产生的日志
	wait        chan int       // 等待子任务完成的通道
	waitGroup   sync.WaitGroup // 等待子任务完成的通道
}

// 任务中心 - 开始任务
func (jobCenter *JobCenter) Work() bool {
	// 解析excel文件
	if !jobCenter.ParseExcel() {
		jobCenter.Log.EchoLog()
		return false
	}

	jobCenter.Log.EchoLog()

	var jobCount int = len(jobCenter.JobList)
	jobCenter.wait = make(chan int, jobCount)

	// jobCenter.waitGroup.Add(jobCount)

	// 执行每个子任务
	for i := 0; i < jobCount; i++ {
		var job *Job = jobCenter.JobList[i]
		job.JobIndex = i + 1
		job.GoroutineWork()
	}

	// 打印执行子任务过程中产生的日志
	for i := 0; i < jobCount; i++ {
		var doneJobIndex int = <-jobCenter.wait
		var job *Job = jobCenter.JobList[doneJobIndex-1]
		job.Log.EchoLog()
	}

	// 等待所有子任务完成
	// jobCenter.waitGroup.Wait()
	return true
}

// 任务 - 开始任务
func (job *Job) Work() {
	// 检查：导出的文件夹应存在
	if !tool.Exist(job.OutDir) {
		job.Log.AddLog(tool.EnumLogType_Error, "参数错误: 找不到指定的文件夹来生成<%s>，请确认路径是否存在!", job.OutDir)
		return
	}

	// 检查：golang模板文件应存在
	if !tool.Exist(job.TemplateFile) {
		job.Log.AddLog(tool.EnumLogType_Error, "参数错误: 找不到模板文件<%s>", job.TemplateFile)
		return
	}

	// 获取文件名后缀
	var ext string = tool.GetExt(job.TemplateFile)

	if job.JobType == JobType_AllInOne {
		// 多合一模式：excel文件内的所有内容导出到同一个文件
		var fileName string = job.TargetExcel.ClassName + "." + ext
		var fullPath = tool.AppendPath(job.OutDir, job.TargetExcel.ClassName) + "." + ext

		// 开始生成文件
		if !job.GenerateByTemplate(job.TargetExcel, job.TemplateFile, fullPath) {
			job.Log.AddLog(tool.EnumLogType_Error, "生成文件<%s>失败", fullPath)
			return
		}

		tool.EchoOk("  生成文件<%s>成功", fileName)
		// job.Log.AddLog(tool.EnumLogType_Ok, "生成文件<%s>成功", fileName)
	} else if job.JobType == JobType_Split {
		// 拆分模式：将excel文件中的各个工作表导出到对应的文件
		for _, sheet := range job.TargetExcel.Sheets {
			var fileName string = sheet.EnName + "." + ext
			var fullPath string = tool.AppendPath(job.OutDir, sheet.EnName) + "." + ext

			// 开始生成文件
			if !job.GenerateByTemplate(&sheet, job.TemplateFile, fullPath) {
				job.Log.AddLog(tool.EnumLogType_Error, "生成文件<%s>失败", fullPath)
				return
			}

			tool.EchoOk("  导出[%s] -> [%s]成功", sheet.CnName, fileName)
			// job.Log.AddLog(tool.EnumLogType_Ok, "导出[%s] -> [%s]成功", sheet.CnName, fileName)
		}
	}
}

// 任务 - 开始任务(goroutine方式)
func (job *Job) GoroutineWork() {
	job.TargetExcel = &job.RelateJobCenter.TargetExcel

	// 开始任务
	job.Work()

	// 完成后向主线报告
	// job.RelateJobCenter.waitGroup.Done()
	job.RelateJobCenter.wait <- job.JobIndex
}

// 根据模板文件进行导出
func (job *Job) GenerateByTemplate(data interface{}, teamplateFileName string, out string) bool {
	// 注册函数
	var funcs = template.FuncMap{
		"Trim":                  Trim,
		"RegisterFieldTypeName": RegisterFieldTypeName,
		"Tail":                  Tail,
		"RegisterString":        RegisterString,
		"RegisterBool":          RegisterBool,
		"RegisterChar":          RegisterChar,
		"RegisterInt16":         RegisterInt16,
		"RegisterInt32":         RegisterInt32,
		"RegisterInt64":         RegisterInt64,
		"RegisterFloat":         RegisterFloat,
		"RegisterDouble":        RegisterDouble,
	}

	var fileBase = filepath.Base(teamplateFileName)

	// 加载模板
	t := template.New(fileBase).Funcs(funcs)

	// 解析模板
	tpl, err := t.ParseFiles(teamplateFileName)
	if err != nil {
		panic(err)
	}

	var buf bytes.Buffer

	// 根据模板文件将excel中的数据导出
	err = tpl.Execute(&buf, data)
	if err != nil {
		panic(err)
	}

	var text string = buf.String()

	var ext string = filepath.Ext(teamplateFileName)

	// 若生成的文件不为二进制格式
	if ext != ".bin" {
		// 尽可能清除空行
		text = tool.ClearBlankLine(text)
	}

	if ext != "xxxx.bin" {
		// 转为中文编码
		enc := mahonia.NewEncoder("GB18030")
		if ret, ok := enc.ConvertStringOK(text); ok {
			// fmt.Println("UTF-8 to GBK: ", ret, " bytes: ", []byte(ret))
			text = string(ret)
		}
	}

	// 覆盖文件（仅当文件内容变化时才覆盖，防止文件内容不变时，时间戳被修改）
	var ok bool = tool.OverWriteFile(out, &text, &job.Log)
	return ok
}
