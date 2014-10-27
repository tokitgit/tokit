///<------------------------------------------------------------------------------
//< @file:  testcfg.h
//< @brief: 测试用例表
//< 本头文件由工具自动生成，请勿在本文件内做改动
//< @Copyright (c) 2014 tokit.
///<------------------------------------------------------------------------------

#ifndef _testcfg_h_
#define _testcfg_h_

#include <string>

#include <map>
#include <vector>
#include <set>

#include "type.h"

// 测试用例表
struct testcfg_t{
    typedef std::string stringfieldprimary_t; // 字符串主键<<<主键>>>
    typedef bool boolfieldprimary_t; // bool型主键<<<主键>>>
    typedef char charfieldprimary_t; // 字符主键<<<主键>>>
    typedef int16 int16fieldprimary_t; // 16位整数主键<<<主键>>>
    typedef int32 intfieldprimary_t; // 32位整数主键<<<主键>>>
    typedef int64 int64fieldprimary_t; // 64位整数主键<<<主键>>>
    typedef uint8 uint8fieldprimary_t; // 8位无符号整数主键<<<主键>>>
    typedef uint16 uint16fieldprimary_t; // 16位无符号整数主键<<<主键>>>
    typedef uint32 uintfieldprimary_t; // 32位无符号整数主键<<<主键>>>
    typedef uint64 uint64fieldprimary_t; // 64位无符号整数主键<<<主键>>>
    typedef std::string stringfieldunique_t; // 字符串唯一<<<唯一>>>
    typedef bool boolfieldunique_t; // bool型唯一<<<唯一>>>
    typedef char charfieldunique_t; // 字符唯一<<<唯一>>>
    typedef int16 int16fieldunique_t; // 16位整数唯一<<<唯一>>>
    typedef int32 intfieldunique_t; // 32位整数唯一<<<唯一>>>
    typedef int64 int64fieldunique_t; // 64位整数唯一<<<唯一>>>
    typedef uint8 uint8fieldunique_t; // 8位无符号整数唯一<<<唯一>>>
    typedef uint16 uint16fieldunique_t; // 16位无符号整数唯一<<<唯一>>>
    typedef uint32 uintfieldunique_t; // 32位无符号整数唯一<<<唯一>>>
    typedef uint64 uint64fieldunique_t; // 64位无符号整数唯一<<<唯一>>>
    typedef float floatfieldunique_t; // 浮点数唯一<<<唯一>>>
    typedef double doublefieldunique_t; // 双精度浮点数唯一<<<唯一>>>
    typedef std::vector<std::string> stringfieldarrayvec_t; // 字符串数组<<<数组>>>
    typedef std::vector<bool> boolfieldarrayvec_t; // bool型数组<<<数组>>>
    typedef std::vector<char> charfieldarrayvec_t; // 字符数组<<<数组>>>
    typedef std::vector<int16> int16fieldarrayvec_t; // 16位整数数组<<<数组>>>
    typedef std::vector<int32> intfieldarrayvec_t; // 32位整数数组<<<数组>>>
    typedef std::vector<int64> int64fieldarrayvec_t; // 64位整数数组<<<数组>>>
    typedef std::vector<uint8> uint8fieldarrayvec_t; // 8位无符号整数数组<<<数组>>>
    typedef std::vector<uint16> uint16fieldarrayvec_t; // 16位无符号整数数组<<<数组>>>
    typedef std::vector<uint32> uintfieldarrayvec_t; // 32位无符号整数数组<<<数组>>>
    typedef std::vector<uint64> uint64fieldarrayvec_t; // 64位无符号整数数组<<<数组>>>
    typedef std::vector<float> floatfieldarrayvec_t; // 浮点数数组<<<数组>>>
    typedef std::vector<double> doublefieldarrayvec_t; // 双精度浮点数数组<<<数组>>>
    typedef std::set<std::string> stringfieldsetset_t; // 字符串集合<<<集合>>>
    typedef std::set<bool> boolfieldsetset_t; // bool型集合<<<集合>>>
    typedef std::set<char> charfieldsetset_t; // 字符集合<<<集合>>>
    typedef std::set<int16> int16fieldsetset_t; // 16位整数集合<<<集合>>>
    typedef std::set<int32> intfieldsetset_t; // 32位整数集合<<<集合>>>
    typedef std::set<int64> int64fieldsetset_t; // 64位整数集合<<<集合>>>
    typedef std::set<uint8> uint8fieldsetset_t; // 8位无符号整数集合<<<集合>>>
    typedef std::set<uint16> uint16fieldsetset_t; // 16位无符号整数集合<<<集合>>>
    typedef std::set<uint32> uintfieldsetset_t; // 32位无符号整数集合<<<集合>>>
    typedef std::set<uint64> uint64fieldsetset_t; // 64位无符号整数集合<<<集合>>>
    typedef std::set<float> floatfieldsetset_t; // 浮点数集合<<<集合>>>
    typedef std::set<double> doublefieldsetset_t; // 双精度浮点数集合<<<集合>>>

    testcfg_t();

    std::string stringfield; // 字符串
    bool boolfield; // bool型
    char charfield; // 字符
    int16 int16field; // 16位整数
    int32 intfield; // 32位整数
    int64 int64field; // 64位整数
    uint8 uint8field; // 8位无符号整数
    uint16 uint16field; // 16位无符号整数
    uint32 uintfield; // 32位无符号整数
    uint64 uint64field; // 64位无符号整数
    float floatfield; // 浮点数
    double doublefield; // 双精度浮点数
    stringfieldprimary_t stringfieldprimary; // 字符串主键<<<主键>>>
    boolfieldprimary_t boolfieldprimary; // bool型主键<<<主键>>>
    charfieldprimary_t charfieldprimary; // 字符主键<<<主键>>>
    int16fieldprimary_t int16fieldprimary; // 16位整数主键<<<主键>>>
    intfieldprimary_t intfieldprimary; // 32位整数主键<<<主键>>>
    int64fieldprimary_t int64fieldprimary; // 64位整数主键<<<主键>>>
    uint8fieldprimary_t uint8fieldprimary; // 8位无符号整数主键<<<主键>>>
    uint16fieldprimary_t uint16fieldprimary; // 16位无符号整数主键<<<主键>>>
    uintfieldprimary_t uintfieldprimary; // 32位无符号整数主键<<<主键>>>
    uint64fieldprimary_t uint64fieldprimary; // 64位无符号整数主键<<<主键>>>
    float floatfieldprimary; // 浮点数主键
    double doublefieldprimary; // 双精度浮点数主键
    stringfieldunique_t stringfieldunique; // 字符串唯一<<<唯一>>>
    boolfieldunique_t boolfieldunique; // bool型唯一<<<唯一>>>
    charfieldunique_t charfieldunique; // 字符唯一<<<唯一>>>
    int16fieldunique_t int16fieldunique; // 16位整数唯一<<<唯一>>>
    intfieldunique_t intfieldunique; // 32位整数唯一<<<唯一>>>
    int64fieldunique_t int64fieldunique; // 64位整数唯一<<<唯一>>>
    uint8fieldunique_t uint8fieldunique; // 8位无符号整数唯一<<<唯一>>>
    uint16fieldunique_t uint16fieldunique; // 16位无符号整数唯一<<<唯一>>>
    uintfieldunique_t uintfieldunique; // 32位无符号整数唯一<<<唯一>>>
    uint64fieldunique_t uint64fieldunique; // 64位无符号整数唯一<<<唯一>>>
    floatfieldunique_t floatfieldunique; // 浮点数唯一<<<唯一>>>
    doublefieldunique_t doublefieldunique; // 双精度浮点数唯一<<<唯一>>>
    stringfieldarrayvec_t stringfieldarray; // 字符串数组<<<数组>>>
    boolfieldarrayvec_t boolfieldarray; // bool型数组<<<数组>>>
    charfieldarrayvec_t charfieldarray; // 字符数组<<<数组>>>
    int16fieldarrayvec_t int16fieldarray; // 16位整数数组<<<数组>>>
    intfieldarrayvec_t intfieldarray; // 32位整数数组<<<数组>>>
    int64fieldarrayvec_t int64fieldarray; // 64位整数数组<<<数组>>>
    uint8fieldarrayvec_t uint8fieldarray; // 8位无符号整数数组<<<数组>>>
    uint16fieldarrayvec_t uint16fieldarray; // 16位无符号整数数组<<<数组>>>
    uintfieldarrayvec_t uintfieldarray; // 32位无符号整数数组<<<数组>>>
    uint64fieldarrayvec_t uint64fieldarray; // 64位无符号整数数组<<<数组>>>
    floatfieldarrayvec_t floatfieldarray; // 浮点数数组<<<数组>>>
    doublefieldarrayvec_t doublefieldarray; // 双精度浮点数数组<<<数组>>>
    stringfieldsetset_t stringfieldset; // 字符串集合<<<集合>>>
    boolfieldsetset_t boolfieldset; // bool型集合<<<集合>>>
    charfieldsetset_t charfieldset; // 字符集合<<<集合>>>
    int16fieldsetset_t int16fieldset; // 16位整数集合<<<集合>>>
    intfieldsetset_t intfieldset; // 32位整数集合<<<集合>>>
    int64fieldsetset_t int64fieldset; // 64位整数集合<<<集合>>>
    uint8fieldsetset_t uint8fieldset; // 8位无符号整数集合<<<集合>>>
    uint16fieldsetset_t uint16fieldset; // 16位无符号整数集合<<<集合>>>
    uintfieldsetset_t uintfieldset; // 32位无符号整数集合<<<集合>>>
    uint64fieldsetset_t uint64fieldset; // 64位无符号整数集合<<<集合>>>
    floatfieldsetset_t floatfieldset; // 浮点数集合<<<集合>>>
    doublefieldsetset_t doublefieldset; // 双精度浮点数集合<<<集合>>>
};


// 测试用例表
class testcfgmgr
{
public:
    // 测试用例表
    typedef std::map<std::string, testcfg_t*> testcfgmap;
    typedef std::map<testcfg_t::stringfieldunique_t, testcfg_t*> stringfieldunique2testcfgmap; // 字符串唯一 -> testcfg_t
    typedef std::map<testcfg_t::boolfieldunique_t, testcfg_t*> boolfieldunique2testcfgmap; // bool型唯一 -> testcfg_t
    typedef std::map<testcfg_t::charfieldunique_t, testcfg_t*> charfieldunique2testcfgmap; // 字符唯一 -> testcfg_t
    typedef std::map<testcfg_t::int16fieldunique_t, testcfg_t*> int16fieldunique2testcfgmap; // 16位整数唯一 -> testcfg_t
    typedef std::map<testcfg_t::intfieldunique_t, testcfg_t*> intfieldunique2testcfgmap; // 32位整数唯一 -> testcfg_t
    typedef std::map<testcfg_t::int64fieldunique_t, testcfg_t*> int64fieldunique2testcfgmap; // 64位整数唯一 -> testcfg_t
    typedef std::map<testcfg_t::uint8fieldunique_t, testcfg_t*> uint8fieldunique2testcfgmap; // 8位无符号整数唯一 -> testcfg_t
    typedef std::map<testcfg_t::uint16fieldunique_t, testcfg_t*> uint16fieldunique2testcfgmap; // 16位无符号整数唯一 -> testcfg_t
    typedef std::map<testcfg_t::uintfieldunique_t, testcfg_t*> uintfieldunique2testcfgmap; // 32位无符号整数唯一 -> testcfg_t
    typedef std::map<testcfg_t::uint64fieldunique_t, testcfg_t*> uint64fieldunique2testcfgmap; // 64位无符号整数唯一 -> testcfg_t
    typedef std::map<testcfg_t::floatfieldunique_t, testcfg_t*> floatfieldunique2testcfgmap; // 浮点数唯一 -> testcfg_t
    typedef std::map<testcfg_t::doublefieldunique_t, testcfg_t*> doublefieldunique2testcfgmap; // 双精度浮点数唯一 -> testcfg_t
    typedef std::vector<testcfg_t> testcfgvec;

public:
	testcfgmgr(){}
	~testcfgmgr(){}

	static testcfgmgr& instance(){
		static testcfgmgr static_testcfgmgr;
		return static_testcfgmgr;
	}

private:
    testcfgmgr& operator=(const testcfgmgr&){ static testcfgmgr mgr; return mgr; }
    testcfgmgr (const testcfgmgr&){}

public:
	// @impl 获取本配置类名称
	std::string mgr_name(){ return "testcfg"; }

    // 获取本配置所在路径
    std::string get_path(std::string xml){ return "../../xml/" + xml;}

public:
    // 载入测试用例表
	virtual bool load();

    // 清空测试用例表
    virtual void clear();

// 载入方法
public:
    bool load_testcfg();

// 清空方法
public:
    void clear_testcfg();

// 查找方法
public:
    // 测试用例表
    testcfg_t* get_testcfg(const char* stringfieldprimary, testcfg_t::boolfieldprimary_t boolfieldprimary, testcfg_t::charfieldprimary_t charfieldprimary, testcfg_t::int16fieldprimary_t int16fieldprimary, testcfg_t::intfieldprimary_t intfieldprimary, testcfg_t::int64fieldprimary_t int64fieldprimary, testcfg_t::uint8fieldprimary_t uint8fieldprimary, testcfg_t::uint16fieldprimary_t uint16fieldprimary, testcfg_t::uintfieldprimary_t uintfieldprimary, testcfg_t::uint64fieldprimary_t uint64fieldprimary);
    testcfg_t* get_testcfg_by_stringfieldunique(const char* stringfieldunique);
    testcfg_t* get_testcfg_by_boolfieldunique(testcfg_t::boolfieldunique_t boolfieldunique);
    testcfg_t* get_testcfg_by_charfieldunique(testcfg_t::charfieldunique_t charfieldunique);
    testcfg_t* get_testcfg_by_int16fieldunique(testcfg_t::int16fieldunique_t int16fieldunique);
    testcfg_t* get_testcfg_by_intfieldunique(testcfg_t::intfieldunique_t intfieldunique);
    testcfg_t* get_testcfg_by_int64fieldunique(testcfg_t::int64fieldunique_t int64fieldunique);
    testcfg_t* get_testcfg_by_uint8fieldunique(testcfg_t::uint8fieldunique_t uint8fieldunique);
    testcfg_t* get_testcfg_by_uint16fieldunique(testcfg_t::uint16fieldunique_t uint16fieldunique);
    testcfg_t* get_testcfg_by_uintfieldunique(testcfg_t::uintfieldunique_t uintfieldunique);
    testcfg_t* get_testcfg_by_uint64fieldunique(testcfg_t::uint64fieldunique_t uint64fieldunique);
    testcfg_t* get_testcfg_by_floatfieldunique(testcfg_t::floatfieldunique_t floatfieldunique);
    testcfg_t* get_testcfg_by_doublefieldunique(testcfg_t::doublefieldunique_t doublefieldunique);

// 获取成员方法
public:
    // 测试用例表
    const testcfgmap& get_testcfgmap(){ return m_testcfgmap; }
    const stringfieldunique2testcfgmap& get_stringfieldunique2testcfgmap(){ return m_stringfieldunique2testcfgmap; }
    const boolfieldunique2testcfgmap& get_boolfieldunique2testcfgmap(){ return m_boolfieldunique2testcfgmap; }
    const charfieldunique2testcfgmap& get_charfieldunique2testcfgmap(){ return m_charfieldunique2testcfgmap; }
    const int16fieldunique2testcfgmap& get_int16fieldunique2testcfgmap(){ return m_int16fieldunique2testcfgmap; }
    const intfieldunique2testcfgmap& get_intfieldunique2testcfgmap(){ return m_intfieldunique2testcfgmap; }
    const int64fieldunique2testcfgmap& get_int64fieldunique2testcfgmap(){ return m_int64fieldunique2testcfgmap; }
    const uint8fieldunique2testcfgmap& get_uint8fieldunique2testcfgmap(){ return m_uint8fieldunique2testcfgmap; }
    const uint16fieldunique2testcfgmap& get_uint16fieldunique2testcfgmap(){ return m_uint16fieldunique2testcfgmap; }
    const uintfieldunique2testcfgmap& get_uintfieldunique2testcfgmap(){ return m_uintfieldunique2testcfgmap; }
    const uint64fieldunique2testcfgmap& get_uint64fieldunique2testcfgmap(){ return m_uint64fieldunique2testcfgmap; }
    const floatfieldunique2testcfgmap& get_floatfieldunique2testcfgmap(){ return m_floatfieldunique2testcfgmap; }
    const doublefieldunique2testcfgmap& get_doublefieldunique2testcfgmap(){ return m_doublefieldunique2testcfgmap; }
    const testcfgvec& get_testcfgvec(){ return m_testcfgvec; }

// 成员变量区
public:
    // 测试用例表
    testcfgmap m_testcfgmap;
    stringfieldunique2testcfgmap m_stringfieldunique2testcfgmap;
    boolfieldunique2testcfgmap m_boolfieldunique2testcfgmap;
    charfieldunique2testcfgmap m_charfieldunique2testcfgmap;
    int16fieldunique2testcfgmap m_int16fieldunique2testcfgmap;
    intfieldunique2testcfgmap m_intfieldunique2testcfgmap;
    int64fieldunique2testcfgmap m_int64fieldunique2testcfgmap;
    uint8fieldunique2testcfgmap m_uint8fieldunique2testcfgmap;
    uint16fieldunique2testcfgmap m_uint16fieldunique2testcfgmap;
    uintfieldunique2testcfgmap m_uintfieldunique2testcfgmap;
    uint64fieldunique2testcfgmap m_uint64fieldunique2testcfgmap;
    floatfieldunique2testcfgmap m_floatfieldunique2testcfgmap;
    doublefieldunique2testcfgmap m_doublefieldunique2testcfgmap;
    testcfgvec m_testcfgvec;
};

#endif // _testcfg_h_
