#ifndef _file_util_h_
#define _file_util_h_

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace fileutil
{
    // 指定路径是否存在
    // 例如：dir = "../../example"
    bool is_dir_exist(const std::string &dir);
    
    // 指定路径是否存在，可为文件路径或者文件夹路径
    // 例如：path = "../../example"
    // 又如：path = "../../abc.xml"
    // 又如：path = "../../"
    bool exist(const std::string &path);

    // 列出指定文件夹下的文件名列表（子文件夹将被忽略），含义如windows命令行下的dir
    // 例如：path = ../../*.*,   则 files = { "a.txt", "b.txt", "c.exe" }
    // 又如：path = ../../*.txt, 则 files = { "a.txt", "b.txt" }
    typedef std::vector<string> filevec_t;
    bool dir(const std::string &path, /* out */filevec_t &files);

    // 列出指定文件夹下的文件名列表，并把文件名去掉后缀
    // 例如：文件夹下有一些文件 = { "a.txt", "b.txt", "c.exe" }, 则 files = { "a", "b", "c" }
    bool dir_no_ext(const std::string &path, /* out */filevec_t &files);

    // 以二进制方式读取整个文件，根据文件大小分配缓冲区，将文件内容存入缓冲区中并返回
    // 该缓冲区通过new分配，所以要手动delete[]
    char* get_whole_file_buf(const std::string &path);

    // 以字符方式读取整个文件，返回文本内容字符串（文件大时不适合用此方法,因为返回的string将被深拷贝）
    string get_whole_file_str(const std::string &path);

    // 覆盖文件：如果文件内容不变，则不作操作，否则直接用新的文件内容替换掉原来的（这么做是希望当文件内容不变时，防止文件的时间戳发生变化）
    bool overwrite_file(const std::string &path, const std::string &text);
}

#endif // _file_util_h_
