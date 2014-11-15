///<------------------------------------------------------------------------------
//< @文件名：echo_tool.cpp
//< @作　者：洪坤安
//< @日　期: 2014年11月12日 19:08:42
//< @摘　要:
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

// xsd_generator
package xsd

import (
	"tokit/generator"
	"tokit/tool"
)

var g_xsd_types = [generator.Fieldtype_max + 1]string{"", "xs:string", "xs:unsignedByte", "xs:byte", "xs:short", "xs:int", "xs:long", "xs:unsignedByte", "xs:unsignedShort", "xs:unsignedInt", "xs:unsignedLong", "xs:float", "xs:double"}

type Xsd_generator struct {
	M_cfgbase *generator.Cfgbase_t
	M_xsd_dir string
}

func (x *Xsd_generator) Generate() {
	if false == tool.Exist(&x.M_xsd_dir) {
		tool.EchoErr("错误: <%s>路径不存在", x.M_xsd_dir)
		return
	}

	x.gen_xsds()
}

func (x *Xsd_generator) gen_xsds() {

	for _, v := range x.M_cfgbase.Cfgs {
		var xsd string = x.M_xsd_dir + "\\" + v.Cn_name + ".xsd"
		gen_xsd(&v, &xsd)
	}
}

func gen_elem(cfg *generator.Cfg_t) string {
	var s string
	s += "<xs:element name=\"" + cfg.En_name + "s\">\n"
	s += "  <xs:complexType>\n"
	s += "    <xs:sequence minOccurs=\"0\" maxOccurs=\"unbounded\">\n"
	s += "      <xs:element name=\"" + cfg.En_name + "\">\n"
	s += "        <xs:complexType>\n"
	s += "			<xs:sequence>\n"

	for _, v := range cfg.Fields {
		s += "            <xs:attribute name=\"" + v.En_name + "\" type=\"" + g_xsd_types[v.Fieldtype] + "\"/>\n"
	}

	s += "          </xs:sequence>\n"
	s += "        </xs:complexType>\n"
	s += "      </xs:element>\n"
	s += "    </xs:sequence>\n"
	s += "  </xs:complexType>\n"
	s += "</xs:element>\n"

	return s
}

func gen_body(cfg *generator.Cfg_t) string {
	var s string
	s += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
	s += "<xs:schema xmlns:xs=\"http://www.w3.org/2001/XMLSchema\">\n"
	s += gen_elem(cfg)
	s += "</xs:schema>\n"
	return s
}

func gen_xsd(cfg *generator.Cfg_t, xsd *string) bool {
	var text string = gen_body(cfg)
	tool.WriteFile(xsd, &text)
	tool.EchoOk("导出[%s] -> [%s]成功", cfg.Cn_name, *xsd)

	return true
}
