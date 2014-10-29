///<------------------------------------------------------------------------------
//< @file:   language\xsd\xsd_generator.h
//< @author: 洪坤安
//< @date:   2014年9月25日 16:3:37
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _xsd_generator_h_
#define _xsd_generator_h_

#include <string>
#include "generator.h"

using std::string;

class xsd_generator : public generator
{
public:
    xsd_generator(cfgbase_t &cfgbase, const string &xsd_dir)
        : generator(cfgbase)
        , m_xsd_dir(xsd_dir)
    {
    }

public:
    // @impl
    bool generate();

public:
    static string& tokit_type_2_xsd_type(enum_tokit_field_type);

private:
    bool gen_xsds();

private:
    std::string m_xsd_dir;
};

#endif //_xsd_generator_h_