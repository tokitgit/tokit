#include "file_util.h"

#include <sys/stat.h>
#include <io.h>
#include <fstream>
#include <sstream>
#include "str_util.h"
#include "echoutil.h"

using namespace std;

namespace fileutil
{
    bool is_dir_exist(const std::string &dir)
    {
        struct _stat fileStat;
        if ((_stat(dir.c_str(), &fileStat) == 0) && (fileStat.st_mode & _S_IFDIR)){
            return true;
        }

        return false;
    }

    bool exist(const std::string &path)
    {
        return _access(path.c_str(), 0) != -1;
    }

    bool dir(const std::string &path, /* out */filevec_t &files)
    {
        struct _finddata_t filefind;

        int handle = 0;
        if(-1 == (handle = _findfirst(path.c_str(), &filefind))){
            return false;
        }

        do{
            if(_A_SUBDIR != filefind.attrib){
                // 不是目录，是文件
                files.push_back(filefind.name);
            }
        } while(!_findnext(handle, &filefind));

        _findclose(handle);
        return true;
    }

    bool dir_no_ext(const std::string &path, /* out */filevec_t &files)
    {
        filevec_t ext_files;
        if(false == dir(path, ext_files)){
            return false;
        }

        for (filevec_t::iterator itr = ext_files.begin(); itr != ext_files.end(); ++itr){
            string &filename = *itr;
            files.push_back(strutil::strip_ext(filename));
        }

        return !files.empty();
    }

    char* get_whole_file_buf(const std::string &path)
    {
        if(false == exist(path)){
            return NULL;
        }

        /* 若要一个byte不漏地读入整个文件，只能采用二进制方式打开 */
        errno_t err;
        FILE *file = NULL;
        err = fopen_s(&file, path.c_str(), "rb" );  
        if (NULL == file || err > 0){
            ECHO_ERR("打开<%s>文件失败，错误号:%u", path.c_str(), err);
            return NULL;
        }  

        /* 获取文件大小 */  
        fseek (file , 0 , SEEK_END);  
        long size = ftell (file);  
        rewind (file);  

        /* 分配内存存储整个文件 */   
        char *buf = new char[size];  
        if (buf == NULL)        {  
            ECHO_ERR("载入<%s>文件失败，错误原因:分配<%ubyte>的内存失败", path.c_str(), size);
            return NULL;
        }  

        /* 将文件拷贝到buffer中 */  
        size_t ret = fread (buf, 1, size, file);  
        if (ret != size){  
            ECHO_ERR("载入<%s>文件失败，错误原因:文件读取大小不符<%u> != <%u>", path.c_str(), ret, size);
            return NULL;
        }  

        /* 现在整个文件已经在buffer中 */
        /* 关闭文件并释放内存 */
        fclose (file);
        return buf;
    }

    string get_whole_file_str(const std::string &path)
    {
        if(false == exist(path)){
            return "";
        }

        std::ifstream file(path.c_str());
        std::stringstream buf;
        buf << file.rdbuf();

        std::string contents(buf.str());
        return contents;
    }

    bool overwrite_file(const std::string &path, const std::string &new_text)
    {
        const string &old_text = get_whole_file_str(path);
        if (old_text == new_text){
            return true;
        }

        ofstream o(path);
        if (!o.good()){
            ECHO_ERR("无法生成文件，路径错误:<%s>", path.c_str());
            return false;
        }

        o << new_text;
        o.flush();
        o.close();

        return true;
    }
}