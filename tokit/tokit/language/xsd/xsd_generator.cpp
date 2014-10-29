///<------------------------------------------------------------------------------
//< @file:   prop\parser\gen_xsd.cpp
//< @author: 洪坤安
//< @date:   2014年4月5日 17:39:38
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include "xsd_generator.h"

#include <fstream>

#include "cfg.h"
#include "file_util.h"
#include "str_util.h"
#include "echoutil.h"
#include "parser.h"

namespace xsdutil{
    void gen_head(ofstream &o, const cfg_t &cfg)
    {
	    o << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
    }

    void gen_elem(ofstream &o, const cfg_t &cfg)
    {
	    o << "<xs:element name=\"" << cfg.en_name << "s\">" << std::endl;
	    o << "  <xs:complexType>" << endl;
	    o << "    <xs:sequence minOccurs=\"0\" maxOccurs=\"unbounded\">" << endl;
	    o << "      <xs:element name=\"" << cfg.en_name << "\">" << std::endl;
	    o << "        <xs:complexType>" << endl;
	    o << "          <xs:sequence>" << endl;

        /*
        for(size_t n = 0; n < cfg.fields.size(); n++){
            const field_t &field = cfg.fields[n];
		    string& xsd_type = cfgutil::raw_type_2_xsd_type(field.fieldtype);
		    o << "            <xs:element name=\"" << field.fieldname << "\" type=\"" << xsd_type << "\"/>" << endl;
	    }
        */

        for(size_t n = 0; n < cfg.fields.size(); n++){
		    const field_t &field = cfg.fields[n];

		    string& xsd_type = xsd_generator::tokit_type_2_xsd_type(field.fieldtype);
		    o << "            <xs:attribute name=\"" << field.en_name << "\" type=\"" << xsd_type << "\"/>" << endl;
	    }

        o << "          </xs:sequence>" << endl;
	    o << "        </xs:complexType>" << endl;    
	    o << "      </xs:element>" << endl;
	    o << "    </xs:sequence>" << endl;
	    o << "  </xs:complexType>" << endl;    
	    o << "</xs:element>" << endl;
    }

    void gen_body(ofstream &o, const cfg_t &cfg)
    {
	    o << "<xs:schema xmlns:xs=\"http://www.w3.org/2001/XMLSchema\">" << endl;
	    gen_elem(o, cfg);
	    o << "</xs:schema>" << endl;
    }

    void gen_xsd(const cfg_t &cfg, const string &xsd)
    {
	    ofstream o(xsd);

	    gen_head(o, cfg);
	    gen_body(o, cfg);

        ECHO_OK("导出[%s] -> [%s]成功", cfg.cn_name.c_str(), xsd.c_str());
    }
}


bool xsd_generator::generate()
{
    if(false == fileutil::exist(m_xsd_dir)){
        ECHO_ERR("错误: <%s>路径不存在", m_xsd_dir.c_str());
        return false;
    }

    return gen_xsds();
}

bool xsd_generator::gen_xsds()
{
    size_t n_cfg = m_cfgbase.cfgs.size();
    for(size_t n = 0; n < n_cfg; ++n){
        const cfg_t &cfg = m_cfgbase.cfgs[n];
        const string xsd = m_xsd_dir + "\\" + strip_ext(strip_dir(cfg.cn_name)) + ".xsd";
        xsdutil::gen_xsd(cfg, xsd);
    }

    return true;
}

string& xsd_generator::tokit_type_2_xsd_type(enum_tokit_field_type fieldtype)
{
    static string static_xsd_types[fieldtype_max] = {
        "",
        "xs:string",
        "xs:unsignedByte",
        "xs:byte",
        "xs:short",
        "xs:int",
        "xs:long",
        "xs:unsignedByte",
        "xs:unsignedShort",
        "xs:unsignedInt",
        "xs:unsignedLong",
        "xs:float",
        "xs:double"
    };

    return static_xsd_types[fieldtype];
}