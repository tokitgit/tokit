///<------------------------------------------------------------------------------
//< @文件名：echo_tool.cpp
//< @作　者：洪坤安
//< @日　期: 2014年11月12日 14:53:42
//< @摘　要:
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

// echo_tool
package tool

import "fmt"
import "go-colortext"

type Errvec_t []string

func Echo_errvec(errs *Errvec_t) {
	for _, v := range *errs {
		EchoErr("  %s", v)
	}
}

func GetErrMsg(cmd string, arg ...interface{}) string{
	return fmt.Sprintf(cmd, arg...)
}

func EchoErr(cmd string, arg ...interface{}) {
	gocolortext.ChangeColor(gocolortext.Red, true, gocolortext.None, false)
	fmt.Println(fmt.Sprintf(cmd, arg...))
}

func EchoWarn(cmd string, arg ...interface{}) {
	gocolortext.ChangeColor(gocolortext.Yellow, true, gocolortext.None, false)
	fmt.Println(fmt.Sprintf(cmd, arg...))
}

func EchoOk(cmd string, arg ...interface{}) {
	gocolortext.ChangeColor(gocolortext.Green, true, gocolortext.None, false)
	fmt.Println(fmt.Sprintf(cmd, arg...))
}

func ResetConsoleColor() {
	gocolortext.ResetColor()
}