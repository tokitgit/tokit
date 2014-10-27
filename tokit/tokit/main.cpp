///<------------------------------------------------------------------------------
//< @file:   prop\parser\main.cpp
//< @author: 洪坤安
//< @date:   2014年9月10日 14:49:42
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include "parser.h"
#include "echoutil.h"
#include "file_util.h"
#include "xsd/xsd_generator.h"
#include "c++/c++_generator.h"
#include "xml/xml_generator.h"

bool parse_excel(std::string &excel, cfgbase_t &cfgbase, enum_parse_option parse_option){
    if(false == fileutil::exist(excel)){
        ECHO_ERR("错误: 找不到excel结构定义文件<%s>", excel.c_str());
        return false;
    }

    errvec_t errvec;
    if (!parser::parse_excel(excel, cfgbase, errvec, parse_option)){
        ECHO_ERR("错误：解析<%s>文件失败", excel.c_str());
        echoutil::echo_errvec(errvec);
        return false;
    }

    return true;
}

// 检测选项中是否含《--导出xml》选项，如果有则需要载入xml数据
enum_parse_option get_parse_option(int argc, char **argv)
{
    enum_parse_option parse_option = parse_option_skip_data;
    for (int i = 1; i < argc; i++){
        if (0 == strcmp(argv[i], "-saveasxml")){
            parse_option = parse_option_read_data;
            break;
        }
    }

    return parse_option;
}

int main(int argc, char **argv)
{
    if (argc < 2){
        ECHO_ERR("参数格式错误，格式应为：");
        ECHO_ERR("   excel文件的路径  命令1  命令1的参数  命令2  命令2的参数...");
        ECHO_ERR("   比如: ../../hello.xlsx  -xsd  ../xsd/  -saveasxml ../xml/");

        return 0;
    }

    std::string excel = argv[1];
    cfgbase_t cfgbase;
    enum_parse_option parse_option = get_parse_option(argc, argv);

    // 解析excel文件
    if (!parse_excel(excel, cfgbase, parse_option)){
        return 0;
    }

    // 开始执行命令
    int pos = 2;
    while(pos < argc){
        std::string cmd = argv[pos++];
        if(cmd == "-xsd"){
            if(pos + 1 > argc){
                ECHO_ERR("生成xsd的命令错误，格式应为: ");
                ECHO_ERR("   -xsd 生成的xsd文件放到哪个文件夹下");
                ECHO_ERR("   比如: -xsd  ../xsd/");

                return 0;
            }

            std::string xsd_dir  = argv[pos++];

            xsd_generator xsd_gen(cfgbase, xsd_dir);
            xsd_gen.generate();
        }else if(cmd == "-c++"){
            if(pos + 3 > argc){
                ECHO_ERR("生成c++源代码文件的命令错误，格式应为: ");
                ECHO_ERR("   -c++  h模板文件 cpp模板文件 生成的c++文件放在哪个文件夹下");
                ECHO_ERR("   比如: -c++  ../h_template.h  ../cpp_template.cpp  ./c++/");

                return 0;
            }

            std::string h_templet   = argv[pos++];
            std::string cpp_templet = argv[pos++];
            std::string cpp_dir	    = argv[pos++];

            cpp_generator cpp_gen(cfgbase, cpp_dir, h_templet, cpp_templet);
            cpp_gen.generate();
        }else if(cmd == "-go"){
            if(pos + 2 > argc){
                ECHO_ERR("生成go源代码文件命令错误，格式应为: ");
                ECHO_ERR("   -go  go模板文件  生成的go文件放在哪个文件夹下");
                ECHO_ERR("   比如: -go  ../go_template.go   ./go/");

                return 0;
            }

            std::string go_templet = argv[pos++];
            std::string go_dir	   = argv[pos++];
        }else if(cmd == "-saveasxml"){
            if(pos + 1 > argc){
                ECHO_WARN("导出xml文件的命令错误，格式应为: ");
                ECHO_WARN("   -saveasxml  生成的xml文件存放在哪个文件夹下");
                ECHO_WARN("   比如: -saveasxml  ../xml/");

                return 0;
            }

            std::string xml_dir = argv[pos++];

            xml_generator xml_gen(cfgbase, xml_dir);
            xml_gen.generate();
        }
    }

    return 0;
}
