///<------------------------------------------------------------------------------
//< @文件名：file_tool.cpp
//< @作　者：洪坤安
//< @日　期: 2014年11月12日 14:22:42
//< @摘　要: 操作文件的方法集合
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

// file_tool
package tool

import (
	//"fmt"
	"io/ioutil"
	"os"
)

// 指定路径是否存在，可为文件路径或者文件夹路径
// 例如：path = "../../example"
// 又如：path = "../../abc.xml"
// 又如：path = "../../"
func Exist(path *string) bool {
	if _, err := os.Stat(*path); err == nil {
		return true
	}

	return false
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
