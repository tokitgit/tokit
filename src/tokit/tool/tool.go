//< @摘　要: 操作字符串的方法集合

package tool

import (
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

// 从左数起直到最后一个分隔符的字符串
// 例如：trip_to("123_456_789", '_') = 123_456
func trip_to(str *string, delimiter string) string {
	var n int = strings.LastIndexAny(*str, delimiter)
	if n <= 0 {
		return *str
	}

	return (*str)[0 : n-1]
}

// 移掉文件名后缀
// 例如：StripExt(xxxx.txt) = xxxx
func StripExt(filename string) string {
	return trip_to(&filename, ".")
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
func Exist(path *string) bool {
	_, err := os.Stat(*path)
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

func WriteFile(file_path *string, text *string) bool {
	fout, err := os.Create(*file_path)
	defer fout.Close()

	if err != nil {
		EchoErr("%s, %s", file_path, err)
		return false
	}

	fout.WriteString(*text)
	return true
}

func GetFileText(path *string, text *string) {
	fi, err := os.Open(*path)
	if err != nil {
		// panic(err)
		*text = ""
		return
	}

	defer fi.Close()

	fd, err := ioutil.ReadAll(fi)
	*text = string(fd)

	//fmt.Println("text = ", *text)
}

func OverWriteFile(path *string, new_text *string) bool {
	var old_text string
	GetFileText(path, &old_text)

	if old_text == *new_text {
		return true
	}

	if !WriteFile(path, new_text) {
		EchoErr("无法生成文件，路径错误:<%s>", path)
		return false
	}

	return true
}

func GetCurrentDirectory() string {
	dir, err := filepath.Abs(filepath.Dir(os.Args[0]))
	if err != nil {
		return ""
	}
	return strings.Replace(dir, "\\", "/", -1)
}

//*********************** 日志 ***********************//

type Errvec_t []string

func EchoErrorArray(errs *Errvec_t) {
	for _, v := range *errs {
		EchoErr("  %s", v)
	}
}

func GetErrMsg(cmd string, arg ...interface{}) string {
	return fmt.Sprintf(cmd, arg...)
}

func EchoErr(cmd string, arg ...interface{}) {
	gocolortext.ChangeColor(gocolortext.Red, true, gocolortext.None, false)
	fmt.Println(fmt.Sprintf(cmd, arg...))
	ResetConsoleColor()
}

func EchoWarn(cmd string, arg ...interface{}) {
	gocolortext.ChangeColor(gocolortext.Yellow, true, gocolortext.None, false)
	fmt.Println(fmt.Sprintf(cmd, arg...))
	ResetConsoleColor()
}

func EchoOk(cmd string, arg ...interface{}) {
	gocolortext.ChangeColor(gocolortext.Green, true, gocolortext.None, false)
	fmt.Println(fmt.Sprintf(cmd, arg...))
	ResetConsoleColor()
}

func ResetConsoleColor() {
	gocolortext.ResetColor()
}

//*********************** 时间 ***********************//

type Clock struct {
	m_tick time.Time
}

func (clock *Clock) StartTick() {
	clock.m_tick = time.Now()
}

// 返回秒
func (clock *Clock) EndTick() float64 {
	now_tick := time.Now()
	var dur_time time.Duration = now_tick.Sub(clock.m_tick)

	var elapsed_sec float64 = dur_time.Seconds()
	return elapsed_sec
}
