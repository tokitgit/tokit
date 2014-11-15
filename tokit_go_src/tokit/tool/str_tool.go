///<------------------------------------------------------------------------------
//< @文件名：str_tool.cpp
//< @作　者：洪坤安
//< @日　期: 2014年11月12日 14:57:42
//< @摘　要:
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

// str_tool
package tool

import (
	"strings"
)

// 移掉路径，只返回文件名称
// 例如：../../xxxx.txt -> xxxx.txt
func Strip_dir(path string) string {
	var n int = strings.LastIndexAny(path, "/\\")
	if n <= 0 {
		return path
	}

	var n_len = len(path);	
	return path[n - 1 : n_len - 1]
}

// 从左数起直到最后一个分隔符的字符串
// 例如：trip_to("123_456_789", '_') = 123_456
func trip_to(str *string, delimiter string) string {
	var n int = strings.LastIndexAny(*str, delimiter)
	if n <= 0 {
		return *str
	}
	
	return (*str)[0 : n - 1]
}

// 移掉文件名后缀
// 例如：strip_ext(xxxx.txt) = xxxx
func Strip_ext(filename string) string {
	return trip_to(&filename, ".")
}
