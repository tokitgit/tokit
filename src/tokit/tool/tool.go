//----------------------------------------------
// 摘　要: 一些通用的函数
//----------------------------------------------

package tool

import (
	"bytes"
	"fmt"
	"go-colortext"
	"io/ioutil"
	"os"
	"path/filepath"
	"strings"
	"time"
)

//*********************** 字符串 ***********************//

// 移掉路径，只返回文件名称
// 例如：../../xxxx.txt -> xxxx.txt
func StripDir(path string) string {
	var n int = strings.LastIndexAny(path, "/\\")
	if n <= 0 {
		return path
	}

	var size = len(path)
	return path[n+1 : size-1]
}

// 返回从左数起直到最后一个分隔符的字符串
// 例如：trip_to("123_456_789", '_') = 123_456
func TripTo(str *string, delimiter string) string {
	var n int = strings.LastIndexAny(*str, delimiter)
	if n <= 0 {
		return *str
	}

	return (*str)[0 : n-1]
}

// 移掉文件名后缀
// 例如：StripExt(xxxx.txt) = xxxx
func StripExt(filename string) string {
	return TripTo(&filename, ".")
}

// 获取文件后缀
// 例如：StripExt(xxxx.txt) = txt
func GetExt(fileName string) string {
	var pos int = strings.LastIndexAny(fileName, ".")
	if pos <= 0 {
		return ""
	}

	var n = len(fileName)
	return fileName[pos+1 : n]
}

// 路径拼接
func AppendPath(base string, file string) string {
	base = strings.Replace(base, "\\", "/", -1)

	if strings.HasSuffix(base, "/") {
		return base + file
	} else {
		return base + "/" + file
	}

	return ""
}

//*********************** 文件 ***********************//

// 指定路径是否存在，可为文件路径或者文件夹路径
// 例如：path = "../../example"
// 又如：path = "../../abc.xml"
// 又如：path = "../../"
func Exist(path string) bool {
	_, err := os.Stat(path)
	return err == nil
}

// 文件是否存在
func ExistFile(path string) bool {
	f, err := os.Stat(path)
	if err != nil {
		return false
	}

	return !f.IsDir()
}

// 文件夹是否存在
func ExistDir(path string) bool {
	f, err := os.Stat(path)
	if err != nil {
		return false
	}

	return f.IsDir()
}

// 写入文件
func WriteFile(file_path string, text *string) bool {
	fout, err := os.Create(file_path)
	defer fout.Close()

	if err != nil {
		EchoError("tool.WriteFile failed! path = %s, error = %s", file_path, err)
		return false
	}

	fout.WriteString(*text)
	return true
}

// 获取文件文本
func GetFileText(path string, text *string) {
	fi, err := os.Open(path)
	if err != nil {
		*text = ""
		return
	}

	defer fi.Close()

	fd, err := ioutil.ReadAll(fi)
	*text = string(fd)
}

// 覆盖文件（仅当文件内容变化时才覆盖，防止文件内容不变时，时间戳被修改）
func OverWriteFile(path string, new_text *string, log *LogInfo) bool {
	var old_text string
	GetFileText(path, &old_text)

	if old_text == *new_text {
		return true
	} else {
		// EchoError("检测到文件变动:<%s>", path)
	}

	if !WriteFile(path, new_text) {
		log.AddLog(EnumLogType_Error, "无法生成文件，路径错误:<%s>", path)
		return false
	}

	return true
}

// 获取当前文件夹
func GetCurrentDirectory() string {
	dir, err := filepath.Abs(filepath.Dir(os.Args[0]))
	if err != nil {
		return ""
	}
	return strings.Replace(dir, "\\", "/", -1)
}

//*********************** 日志 ***********************//

type EnumLogType uint8

// 日志类型
const (
	EnumLogType_None  = EnumLogType(iota)
	EnumLogType_Error = 1 // 错误
	EnumLogType_Ok    = 2 // 正确
	EnumLogType_Warn  = 3 // 警告
	EnumLogType_Info  = 4 // 普通信息
	EnumLogType_Max
)

// 日志
type LogInfo struct {
	lineArray []LogLine // 多行日志
}

// 单行日志数据
type LogLine struct {
	line    string      // 该行日志内容
	logType EnumLogType // 日志类型
}

// 返回字符串日志
func GetLog(cmd string, arg ...interface{}) string {
	return fmt.Sprintf(cmd, arg...)
}

// 输出错误
func EchoError(cmd string, arg ...interface{}) {
	gocolortext.ChangeColor(gocolortext.Red, true, gocolortext.None, false)
	fmt.Println(fmt.Sprintf(cmd, arg...))
	ResetConsoleColor()
}

// 输出警告
func EchoWarn(cmd string, arg ...interface{}) {
	gocolortext.ChangeColor(gocolortext.Yellow, true, gocolortext.None, false)
	fmt.Println(fmt.Sprintf(cmd, arg...))
	ResetConsoleColor()
}

// 输出成功
func EchoOk(cmd string, arg ...interface{}) {
	gocolortext.ChangeColor(gocolortext.Green, true, gocolortext.None, false)
	fmt.Println(fmt.Sprintf(cmd, arg...))
	ResetConsoleColor()
}

// 重置控制台颜色
func ResetConsoleColor() {
	gocolortext.ResetColor()
}

// 添加日志记录
func (log *LogInfo) AddLog(logType EnumLogType, logLine string, arg ...interface{}) {
	var line LogLine
	line.line = fmt.Sprintf(logLine, arg...)
	line.logType = logType

	// var before int = len(log.lineArray)
	log.lineArray = append(log.lineArray, line)

	//EchoWarn("内容 = %s, 颜色 = %d, 大小 = %d -> %d", line.line, logType, before, len(log.lineArray))
}

// 输出日志
func (log *LogInfo) EchoLog() {
	for _, logLine := range log.lineArray {
		if logLine.logType == EnumLogType_Ok {
			EchoOk("  %s", logLine.line)
		} else if logLine.logType == EnumLogType_Error {
			EchoError("  %s", logLine.line)
		} else if logLine.logType == EnumLogType_Warn {
			EchoWarn("  %s", logLine.line)
		} else {
			fmt.Println(fmt.Sprintf("  %s", logLine.line))
		}
	}
}

// 是否是空行
func IsEmptyLine(line string) bool {
	for _, v := range line {
		if v != '\r' && v != '\n' && v != '\t' && v != ' ' {
			return false
		}
	}

	return true
}

// 清空文本串中的开头和结尾的空行，并合并连续的多个空行
func ClearBlankLine(text string) string {
	var lineBreak string = "\r\n"

	// 将文本分割成行数组
	var lineArray []string = strings.Split(text, lineBreak)
	var buffer bytes.Buffer

	var length int = len(lineArray)

	// 将连续的多个空行合并成一个空行
	for i := 0; i < length; {
		var line string = lineArray[i]
		buffer.WriteString(line)
		buffer.WriteString(lineBreak)

		i++

		if IsEmptyLine(line) {
			for next := i; next < length; next++ {
				var nextLine string = lineArray[next]
				if IsEmptyLine(nextLine) {
				} else {
					i = next
					break
				}
			}
		}
	}

	// 清除开头和结尾的空行
	return strings.Trim(buffer.String(), lineBreak)
}

//*********************** 时间 ***********************//

// 计时器
type Clock struct {
	m_tick time.Time
}

// 开始计时
func (clock *Clock) StartTick() {
	clock.m_tick = time.Now()
}

// 停止计时，返回经过的时间（秒）
func (clock *Clock) EndTick() float64 {
	now_tick := time.Now()
	var dur_time time.Duration = now_tick.Sub(clock.m_tick)

	var elapsed_sec float64 = dur_time.Seconds()
	return elapsed_sec
}
