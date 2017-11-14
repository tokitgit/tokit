//------------------------------------------------------------------------------
// 本头文件由工具自动生成，请勿在本文件内做改动
// 日期：
//------------------------------------------------------------------------------

#pragma once

#include <string>
#include <map>
#include <vector>
#include <set>






// 测试用例表
struct TestConfig
{
	TestConfig()
	{
		Clear();
	}
	
	inline void Clear()
	{
	
		stringfield = "";
		
	
		boolfield = false;
		
	
		charfield = 0;
		
	
		int16field = 0;
		
	
		intfield = 0;
		
	
		int64field = 0;
		
	
		uint8field = 0;
		
	
		uint16field = 0;
		
	
		uintfield = 0;
		
	
		uint64field = 0;
		
	
		floatfield = 0.0f;
		
	
		doublefield = 0.0f;
		
	
		stringfieldprimary = "";
		
	
		boolfieldprimary = false;
		
	
		charfieldprimary = 0;
		
	
		int16fieldprimary = 0;
		
	
		intfieldprimary = 0;
		
	
		int64fieldprimary = 0;
		
	
		uint8fieldprimary = 0;
		
	
		uint16fieldprimary = 0;
		
	
		uintfieldprimary = 0;
		
	
		uint64fieldprimary = 0;
		
	
		floatfieldprimary = 0.0f;
		
	
		doublefieldprimary = 0.0f;
		
	
		stringfieldunique = "";
		
	
		boolfieldunique = false;
		
	
		charfieldunique = 0;
		
	
		int16fieldunique = 0;
		
	
		intfieldunique = 0;
		
	
		int64fieldunique = 0;
		
	
		uint8fieldunique = 0;
		
	
		uint16fieldunique = 0;
		
	
		uintfieldunique = 0;
		
	
		uint64fieldunique = 0;
		
	
		floatfieldunique = 0.0f;
		
	
		doublefieldunique = 0.0f;
		
	
		vecstringfieldarray.clear();
		
	
		vecboolfieldarray.clear();
		
	
		veccharfieldarray.clear();
		
	
		vecint16fieldarray.clear();
		
	
		vecintfieldarray.clear();
		
	
		vecint64fieldarray.clear();
		
	
		vecuint8fieldarray.clear();
		
	
		vecuint16fieldarray.clear();
		
	
		vecuintfieldarray.clear();
		
	
		vecuint64fieldarray.clear();
		
	
		vecfloatfieldarray.clear();
		
	
		vecdoublefieldarray.clear();
		
	
		setstringfieldset.clear();
		
	
		setboolfieldset.clear();
		
	
		setcharfieldset.clear();
		
	
		setint16fieldset.clear();
		
	
		setintfieldset.clear();
		
	
		setint64fieldset.clear();
		
	
		setuint8fieldset.clear();
		
	
		setuint16fieldset.clear();
		
	
		setuintfieldset.clear();
		
	
		setuint64fieldset.clear();
		
	
		setfloatfieldset.clear();
		
	
		setdoublefieldset.clear();
		
	
	}
	
	std::string stringfield; // 字符串
	bool boolfield; // bool型
	char charfield; // 字符
	int int16field; // 16位整数
	int intfield; // 32位整数
	long int64field; // 64位整数
	int uint8field; // 8位无符号整数
	int uint16field; // 16位无符号整数
	int uintfield; // 32位无符号整数
	int64_t uint64field; // 64位无符号整数
	float floatfield; // 浮点数
	double doublefield; // 双精度浮点数
	std::string stringfieldprimary; // 字符串主键<主键>
	bool boolfieldprimary; // bool型主键<主键>
	char charfieldprimary; // 字符主键<主键>
	int int16fieldprimary; // 16位整数主键<主键>
	int intfieldprimary; // 32位整数主键<主键>
	long int64fieldprimary; // 64位整数主键<主键>
	int uint8fieldprimary; // 8位无符号整数主键<主键>
	int uint16fieldprimary; // 16位无符号整数主键<主键>
	int uintfieldprimary; // 32位无符号整数主键<主键>
	int64_t uint64fieldprimary; // 64位无符号整数主键<主键>
	float floatfieldprimary; // 浮点数主键
	double doublefieldprimary; // 双精度浮点数主键
	std::string stringfieldunique; // 字符串唯一<唯一>
	bool boolfieldunique; // bool型唯一<唯一>
	char charfieldunique; // 字符唯一<唯一>
	int int16fieldunique; // 16位整数唯一<唯一>
	int intfieldunique; // 32位整数唯一<唯一>
	long int64fieldunique; // 64位整数唯一<唯一>
	int uint8fieldunique; // 8位无符号整数唯一<唯一>
	int uint16fieldunique; // 16位无符号整数唯一<唯一>
	int uintfieldunique; // 32位无符号整数唯一<唯一>
	int64_t uint64fieldunique; // 64位无符号整数唯一<唯一>
	float floatfieldunique; // 浮点数唯一<唯一>
	double doublefieldunique; // 双精度浮点数唯一<唯一>
	std::vector<std::string> vecstringfieldarray; // 字符串数组<数组>
	std::vector<bool> vecboolfieldarray; // bool型数组<数组>
	std::vector<char> veccharfieldarray; // 字符数组<数组>
	std::vector<int> vecint16fieldarray; // 16位整数数组<数组>
	std::vector<int> vecintfieldarray; // 32位整数数组<数组>
	std::vector<long> vecint64fieldarray; // 64位整数数组<数组>
	std::vector<int> vecuint8fieldarray; // 8位无符号整数数组<数组>
	std::vector<int> vecuint16fieldarray; // 16位无符号整数数组<数组>
	std::vector<int> vecuintfieldarray; // 32位无符号整数数组<数组>
	std::vector<int64_t> vecuint64fieldarray; // 64位无符号整数数组<数组>
	std::vector<float> vecfloatfieldarray; // 浮点数数组<数组>
	std::vector<double> vecdoublefieldarray; // 双精度浮点数数组<数组>
	std::set<std::string> setstringfieldset; // 字符串集合<集合>
	std::set<bool> setboolfieldset; // bool型集合<集合>
	std::set<char> setcharfieldset; // 字符集合<集合>
	std::set<int> setint16fieldset; // 16位整数集合<集合>
	std::set<int> setintfieldset; // 32位整数集合<集合>
	std::set<long> setint64fieldset; // 64位整数集合<集合>
	std::set<int> setuint8fieldset; // 8位无符号整数集合<集合>
	std::set<int> setuint16fieldset; // 16位无符号整数集合<集合>
	std::set<int> setuintfieldset; // 32位无符号整数集合<集合>
	std::set<int64_t> setuint64fieldset; // 64位无符号整数集合<集合>
	std::set<float> setfloatfieldset; // 浮点数集合<集合>
	std::set<double> setdoublefieldset; // 双精度浮点数集合<集合>
	
};















class TestModule
{
public:
	static TestModule instance;

public:
	// 获取本配置类名称
	const char* Name(){ return "TestModule"; }

public:
	
	// 载入配置
	bool Load(std::string basePath);


	bool LoadTestConfig(std::string basePath);



    // 清空配置
    void Clear();
	
public:
	



	// 字符串唯一
	const TestConfig* FindTestConfigBystringfieldunique(std::string stringfieldunique);

	// bool型唯一
	const TestConfig* FindTestConfigByboolfieldunique(bool boolfieldunique);

	// 字符唯一
	const TestConfig* FindTestConfigBycharfieldunique(char charfieldunique);

	// 16位整数唯一
	const TestConfig* FindTestConfigByint16fieldunique(int int16fieldunique);

	// 32位整数唯一
	const TestConfig* FindTestConfigByintfieldunique(int intfieldunique);

	// 64位整数唯一
	const TestConfig* FindTestConfigByint64fieldunique(long int64fieldunique);

	// 8位无符号整数唯一
	const TestConfig* FindTestConfigByuint8fieldunique(int uint8fieldunique);

	// 16位无符号整数唯一
	const TestConfig* FindTestConfigByuint16fieldunique(int uint16fieldunique);

	// 32位无符号整数唯一
	const TestConfig* FindTestConfigByuintfieldunique(int uintfieldunique);

	// 64位无符号整数唯一
	const TestConfig* FindTestConfigByuint64fieldunique(int64_t uint64fieldunique);

	// 浮点数唯一
	const TestConfig* FindTestConfigByfloatfieldunique(float floatfieldunique);

	// 双精度浮点数唯一
	const TestConfig* FindTestConfigBydoublefieldunique(double doublefieldunique);



	
public:
	

	// 测试用例表
	std::vector<TestConfig> m_vecTestConfig;




	// 字符串唯一
	std::map<std::string, TestConfig*> m_mapTestConfigBystringfieldunique;

	// bool型唯一
	std::map<bool, TestConfig*> m_mapTestConfigByboolfieldunique;

	// 字符唯一
	std::map<char, TestConfig*> m_mapTestConfigBycharfieldunique;

	// 16位整数唯一
	std::map<int, TestConfig*> m_mapTestConfigByint16fieldunique;

	// 32位整数唯一
	std::map<int, TestConfig*> m_mapTestConfigByintfieldunique;

	// 64位整数唯一
	std::map<long, TestConfig*> m_mapTestConfigByint64fieldunique;

	// 8位无符号整数唯一
	std::map<int, TestConfig*> m_mapTestConfigByuint8fieldunique;

	// 16位无符号整数唯一
	std::map<int, TestConfig*> m_mapTestConfigByuint16fieldunique;

	// 32位无符号整数唯一
	std::map<int, TestConfig*> m_mapTestConfigByuintfieldunique;

	// 64位无符号整数唯一
	std::map<int64_t, TestConfig*> m_mapTestConfigByuint64fieldunique;

	// 浮点数唯一
	std::map<float, TestConfig*> m_mapTestConfigByfloatfieldunique;

	// 双精度浮点数唯一
	std::map<double, TestConfig*> m_mapTestConfigBydoublefieldunique;



};