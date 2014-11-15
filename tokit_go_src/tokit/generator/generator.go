///<------------------------------------------------------------------------------
//< @文件名：generator.cpp
//< @作　者：洪坤安
//< @日　期: 2014年11月12日 17:31:42
//< @摘　要:
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

// generator
package generator

import (
	"tokit/tool"
)

type generator interface {
	Generate()
}

type generate struct {
	excel   string
	cfgbase Cfgbase_t
	errvec  tool.Errvec_t
}

func echo_errs() {

}
