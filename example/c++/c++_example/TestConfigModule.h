//------------------------------------------------------------------------------
// 本文件由工具自动生成
//------------------------------------------------------------------------------

#pragma once

#include <string>
#include <map>
#include <vector>
#include <set>
#include "ConfigModule.h"

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
		
		floatfield = 0.0f;
		
		doublefield = 0.0f;
		
		stringfieldunique = "";
		
		boolfieldunique = false;
		
		charfieldunique = 0;
		
		int16fieldunique = 0;
		
		intfieldunique = 0;
		
		int64fieldunique = 0;
		
		floatfieldunique = 0.0f;
		
		doublefieldunique = 0.0f;
		
		vecstringfieldarray.clear();
		
		vecboolfieldarray.clear();
		
		veccharfieldarray.clear();
		
		vecint16fieldarray.clear();
		
		vecintfieldarray.clear();
		
		vecint64fieldarray.clear();
		
		vecfloatfieldarray.clear();
		
		vecdoublefieldarray.clear();
		
	}
	
	std::string stringfield; // 字符串
	
	bool boolfield; // bool型
	
	char charfield; // 字符
	
	int16 int16field; // 16位整数
	
	int intfield; // 32位整数
	
	int64 int64field; // 64位整数
	
	float floatfield; // 浮点数
	
	double doublefield; // 双精度浮点数
	
	std::string stringfieldunique; // 字符串唯一<唯一>
	
	bool boolfieldunique; // bool型唯一<唯一>
	
	char charfieldunique; // 字符唯一<唯一>
	
	int16 int16fieldunique; // 16位整数唯一<唯一>
	
	int intfieldunique; // 32位整数唯一<唯一>
	
	int64 int64fieldunique; // 64位整数唯一<唯一>
	
	float floatfieldunique; // 浮点数唯一<唯一>
	
	double doublefieldunique; // 双精度浮点数唯一<唯一>
	
	std::vector<std::string> vecstringfieldarray; // 字符串数组<数组=,>
	
	std::vector<bool> vecboolfieldarray; // bool型数组<数组=,>
	
	std::vector<char> veccharfieldarray; // 字符数组<数组=,>
	
	std::vector<int16> vecint16fieldarray; // 16位整数数组<数组=,>
	
	std::vector<int> vecintfieldarray; // 32位整数数组<数组=,>
	
	std::vector<int64> vecint64fieldarray; // 64位整数数组<数组=,>
	
	std::vector<float> vecfloatfieldarray; // 浮点数数组<数组=,>
	
	std::vector<double> vecdoublefieldarray; // 双精度浮点数数组<数组=,>
	
};

class TestConfigModule : public IConfigModule
{
public:
	static TestConfigModule instance;

public:
	// 获取本配置类名称
	const char* Name() override{ return "TestConfigModule"; }

public:
	
	// 载入二进制配置
	bool LoadBinary(const std::string& basePath) override;

	bool LoadBinaryTestConfig(const std::string& basePath);

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
	const TestConfig* FindTestConfigByint16fieldunique(int16 int16fieldunique);

	// 32位整数唯一
	const TestConfig* FindTestConfigByintfieldunique(int intfieldunique);

	// 64位整数唯一
	const TestConfig* FindTestConfigByint64fieldunique(int64 int64fieldunique);

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
	std::map<int16, TestConfig*> m_mapTestConfigByint16fieldunique;

	// 32位整数唯一
	std::map<int, TestConfig*> m_mapTestConfigByintfieldunique;

	// 64位整数唯一
	std::map<int64, TestConfig*> m_mapTestConfigByint64fieldunique;

	// 浮点数唯一
	std::map<float, TestConfig*> m_mapTestConfigByfloatfieldunique;

	// 双精度浮点数唯一
	std::map<double, TestConfig*> m_mapTestConfigBydoublefieldunique;

};