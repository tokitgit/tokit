//------------------------------------------------------------------------------
// 本头文件由工具自动生成，请勿在本文件内做改动
// 日期：
//------------------------------------------------------------------------------

#include "TestModule.h"
#include <iostream>
#include <rapidjson/document.h>	
#include "tokit_tool.h"




TestModule TestModule::instance;





// 字符串唯一
const TestConfig* TestModule::FindTestConfigBystringfieldunique(std::string stringfieldunique)
{
	const auto itr = m_mapTestConfigBystringfieldunique.find(stringfieldunique);
	if (itr == m_mapTestConfigBystringfieldunique.end())
	{
		return nullptr;
	}

	const TestConfig* ret = itr->second;
	return ret;
}

// bool型唯一
const TestConfig* TestModule::FindTestConfigByboolfieldunique(bool boolfieldunique)
{
	const auto itr = m_mapTestConfigByboolfieldunique.find(boolfieldunique);
	if (itr == m_mapTestConfigByboolfieldunique.end())
	{
		return nullptr;
	}

	const TestConfig* ret = itr->second;
	return ret;
}

// 字符唯一
const TestConfig* TestModule::FindTestConfigBycharfieldunique(char charfieldunique)
{
	const auto itr = m_mapTestConfigBycharfieldunique.find(charfieldunique);
	if (itr == m_mapTestConfigBycharfieldunique.end())
	{
		return nullptr;
	}

	const TestConfig* ret = itr->second;
	return ret;
}

// 16位整数唯一
const TestConfig* TestModule::FindTestConfigByint16fieldunique(int int16fieldunique)
{
	const auto itr = m_mapTestConfigByint16fieldunique.find(int16fieldunique);
	if (itr == m_mapTestConfigByint16fieldunique.end())
	{
		return nullptr;
	}

	const TestConfig* ret = itr->second;
	return ret;
}

// 32位整数唯一
const TestConfig* TestModule::FindTestConfigByintfieldunique(int intfieldunique)
{
	const auto itr = m_mapTestConfigByintfieldunique.find(intfieldunique);
	if (itr == m_mapTestConfigByintfieldunique.end())
	{
		return nullptr;
	}

	const TestConfig* ret = itr->second;
	return ret;
}

// 64位整数唯一
const TestConfig* TestModule::FindTestConfigByint64fieldunique(long int64fieldunique)
{
	const auto itr = m_mapTestConfigByint64fieldunique.find(int64fieldunique);
	if (itr == m_mapTestConfigByint64fieldunique.end())
	{
		return nullptr;
	}

	const TestConfig* ret = itr->second;
	return ret;
}

// 8位无符号整数唯一
const TestConfig* TestModule::FindTestConfigByuint8fieldunique(int uint8fieldunique)
{
	const auto itr = m_mapTestConfigByuint8fieldunique.find(uint8fieldunique);
	if (itr == m_mapTestConfigByuint8fieldunique.end())
	{
		return nullptr;
	}

	const TestConfig* ret = itr->second;
	return ret;
}

// 16位无符号整数唯一
const TestConfig* TestModule::FindTestConfigByuint16fieldunique(int uint16fieldunique)
{
	const auto itr = m_mapTestConfigByuint16fieldunique.find(uint16fieldunique);
	if (itr == m_mapTestConfigByuint16fieldunique.end())
	{
		return nullptr;
	}

	const TestConfig* ret = itr->second;
	return ret;
}

// 32位无符号整数唯一
const TestConfig* TestModule::FindTestConfigByuintfieldunique(int uintfieldunique)
{
	const auto itr = m_mapTestConfigByuintfieldunique.find(uintfieldunique);
	if (itr == m_mapTestConfigByuintfieldunique.end())
	{
		return nullptr;
	}

	const TestConfig* ret = itr->second;
	return ret;
}

// 64位无符号整数唯一
const TestConfig* TestModule::FindTestConfigByuint64fieldunique(int64_t uint64fieldunique)
{
	const auto itr = m_mapTestConfigByuint64fieldunique.find(uint64fieldunique);
	if (itr == m_mapTestConfigByuint64fieldunique.end())
	{
		return nullptr;
	}

	const TestConfig* ret = itr->second;
	return ret;
}

// 浮点数唯一
const TestConfig* TestModule::FindTestConfigByfloatfieldunique(float floatfieldunique)
{
	const auto itr = m_mapTestConfigByfloatfieldunique.find(floatfieldunique);
	if (itr == m_mapTestConfigByfloatfieldunique.end())
	{
		return nullptr;
	}

	const TestConfig* ret = itr->second;
	return ret;
}

// 双精度浮点数唯一
const TestConfig* TestModule::FindTestConfigBydoublefieldunique(double doublefieldunique)
{
	const auto itr = m_mapTestConfigBydoublefieldunique.find(doublefieldunique);
	if (itr == m_mapTestConfigBydoublefieldunique.end())
	{
		return nullptr;
	}

	const TestConfig* ret = itr->second;
	return ret;
}




void TestModule::Clear()
{

	m_vecTestConfig.clear();


	m_mapTestConfigBystringfieldunique.clear();
	m_mapTestConfigByboolfieldunique.clear();
	m_mapTestConfigBycharfieldunique.clear();
	m_mapTestConfigByint16fieldunique.clear();
	m_mapTestConfigByintfieldunique.clear();
	m_mapTestConfigByint64fieldunique.clear();
	m_mapTestConfigByuint8fieldunique.clear();
	m_mapTestConfigByuint16fieldunique.clear();
	m_mapTestConfigByuintfieldunique.clear();
	m_mapTestConfigByuint64fieldunique.clear();
	m_mapTestConfigByfloatfieldunique.clear();
	m_mapTestConfigBydoublefieldunique.clear();


}




bool TestModule::LoadTestConfig(std::string basePath)
{
	std::string jsonPath = basePath + "TestConfig.json";
	std::string jsonText;
	if (!tool::GetFileText(jsonPath.c_str(), jsonText))
	{
		std::cout << "[error] parse failed, not found the file <" << jsonPath << ">!\n";
		return false;
	}
	
    rapidjson::Document doc;
    doc.Parse<0>(jsonText.c_str());
    if (doc.HasParseError()) {
        rapidjson::ParseErrorCode code = doc.GetParseError();
        std::cout << "[error] parse <" << jsonPath << "> failed, error code = " << code << "\n";
        return false;
    }
	
	if (!doc.IsArray())
	{
		std::cout << "[error] parse <" << jsonPath << "> failed, the rapidjson doc is not array, type = " << doc.GetType() << "\n";
		return false;
	}
	
	int n = doc.Size();
	m_vecTestConfig.resize(n);
	
	for (int i = 0; i < n; ++i)
	{
		// 逐行提取json元素
		rapidjson::Value &v = doc[i];
		
		TestConfig& row = m_vecTestConfig[i];

		row.stringfield = v["stringfield"].GetString();
		
		row.boolfield = v["boolfield"].GetInt();
		
		row.charfield = v["charfield"].GetInt();
		
		row.int16field = v["int16field"].GetInt();
		
		row.intfield = v["intfield"].GetInt();
		
		row.int64field = v["int64field"].GetInt();
		
		row.uint8field = v["uint8field"].GetInt();
		
		row.uint16field = v["uint16field"].GetInt();
		
		row.uintfield = v["uintfield"].GetInt();
		
		row.uint64field = v["uint64field"].GetInt();
		
		row.floatfield = (float)v["floatfield"].GetDouble();
		
		row.doublefield = v["doublefield"].GetDouble();
		
		row.stringfieldprimary = v["stringfieldprimary"].GetString();
		
		row.boolfieldprimary = v["boolfieldprimary"].GetInt();
		
		row.charfieldprimary = v["charfieldprimary"].GetInt();
		
		row.int16fieldprimary = v["int16fieldprimary"].GetInt();
		
		row.intfieldprimary = v["intfieldprimary"].GetInt();
		
		row.int64fieldprimary = v["int64fieldprimary"].GetInt();
		
		row.uint8fieldprimary = v["uint8fieldprimary"].GetInt();
		
		row.uint16fieldprimary = v["uint16fieldprimary"].GetInt();
		
		row.uintfieldprimary = v["uintfieldprimary"].GetInt();
		
		row.uint64fieldprimary = v["uint64fieldprimary"].GetInt();
		
		row.floatfieldprimary = (float)v["floatfieldprimary"].GetDouble();
		
		row.doublefieldprimary = v["doublefieldprimary"].GetDouble();
		
		row.stringfieldunique = v["stringfieldunique"].GetString();
		
		row.boolfieldunique = v["boolfieldunique"].GetInt();
		
		row.charfieldunique = v["charfieldunique"].GetInt();
		
		row.int16fieldunique = v["int16fieldunique"].GetInt();
		
		row.intfieldunique = v["intfieldunique"].GetInt();
		
		row.int64fieldunique = v["int64fieldunique"].GetInt();
		
		row.uint8fieldunique = v["uint8fieldunique"].GetInt();
		
		row.uint16fieldunique = v["uint16fieldunique"].GetInt();
		
		row.uintfieldunique = v["uintfieldunique"].GetInt();
		
		row.uint64fieldunique = v["uint64fieldunique"].GetInt();
		
		row.floatfieldunique = (float)v["floatfieldunique"].GetDouble();
		
		row.doublefieldunique = v["doublefieldunique"].GetDouble();
		
		tool::split(v["stringfieldarray"].GetString(), row.vecstringfieldarray);
		
		tool::split_str_to_vec<bool>(v["boolfieldarray"].GetString(), row.vecboolfieldarray, tool::str_to_bool);
		
		tool::split_str_to_vec<char>(v["charfieldarray"].GetString(), row.veccharfieldarray, tool::str_to_int);
		
		tool::split_str_to_vec<int>(v["int16fieldarray"].GetString(), row.vecint16fieldarray, tool::str_to_int);
		
		tool::split_str_to_vec<int>(v["intfieldarray"].GetString(), row.vecintfieldarray, tool::str_to_int);
		
		tool::split_str_to_vec<long>(v["int64fieldarray"].GetString(), row.vecint64fieldarray, tool::str_to_int64);
		
		tool::split_str_to_vec<int>(v["uint8fieldarray"].GetString(), row.vecuint8fieldarray, tool::str_to_int);
		
		tool::split_str_to_vec<int>(v["uint16fieldarray"].GetString(), row.vecuint16fieldarray, tool::str_to_int);
		
		tool::split_str_to_vec<int>(v["uintfieldarray"].GetString(), row.vecuintfieldarray, tool::str_to_int);
		
		tool::split_str_to_vec<int64_t>(v["uint64fieldarray"].GetString(), row.vecuint64fieldarray, tool::str_to_int64);
		
		tool::split_str_to_vec<float>(v["floatfieldarray"].GetString(), row.vecfloatfieldarray, tool::str_to_float);
		
		tool::split_str_to_vec<double>(v["doublefieldarray"].GetString(), row.vecdoublefieldarray, tool::str_to_double);
		
		tool::split_str_set(v["stringfieldset"].GetString(), row.setstringfieldset);
		
		tool::split_str_to_set<bool>(v["boolfieldset"].GetString(), row.setboolfieldset, tool::str_to_bool);
		
		tool::split_str_to_set<char>(v["charfieldset"].GetString(), row.setcharfieldset, tool::str_to_int);
		
		tool::split_str_to_set<int>(v["int16fieldset"].GetString(), row.setint16fieldset, tool::str_to_int);
		
		tool::split_str_to_set<int>(v["intfieldset"].GetString(), row.setintfieldset, tool::str_to_int);
		
		tool::split_str_to_set<long>(v["int64fieldset"].GetString(), row.setint64fieldset, tool::str_to_int64);
		
		tool::split_str_to_set<int>(v["uint8fieldset"].GetString(), row.setuint8fieldset, tool::str_to_int);
		
		tool::split_str_to_set<int>(v["uint16fieldset"].GetString(), row.setuint16fieldset, tool::str_to_int);
		
		tool::split_str_to_set<int>(v["uintfieldset"].GetString(), row.setuintfieldset, tool::str_to_int);
		
		tool::split_str_to_set<int64_t>(v["uint64fieldset"].GetString(), row.setuint64fieldset, tool::str_to_int64);
		
		tool::split_str_to_set<float>(v["floatfieldset"].GetString(), row.setfloatfieldset, tool::str_to_float);
		
		tool::split_str_to_set<double>(v["doublefieldset"].GetString(), row.setdoublefieldset, tool::str_to_double);
		
		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		
			m_mapTestConfigBystringfieldunique[row.stringfieldunique] = &row;
		

		
			m_mapTestConfigByboolfieldunique[row.boolfieldunique] = &row;
		

		
			m_mapTestConfigBycharfieldunique[row.charfieldunique] = &row;
		

		
			m_mapTestConfigByint16fieldunique[row.int16fieldunique] = &row;
		

		
			m_mapTestConfigByintfieldunique[row.intfieldunique] = &row;
		

		
			m_mapTestConfigByint64fieldunique[row.int64fieldunique] = &row;
		

		
			m_mapTestConfigByuint8fieldunique[row.uint8fieldunique] = &row;
		

		
			m_mapTestConfigByuint16fieldunique[row.uint16fieldunique] = &row;
		

		
			m_mapTestConfigByuintfieldunique[row.uintfieldunique] = &row;
		

		
			m_mapTestConfigByuint64fieldunique[row.uint64fieldunique] = &row;
		

		
			m_mapTestConfigByfloatfieldunique[row.floatfieldunique] = &row;
		

		
			m_mapTestConfigBydoublefieldunique[row.doublefieldunique] = &row;
		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

		

	}
	
	return true;
}



bool TestModule::Load(std::string basePath)
{
	Clear();
		
	if (!LoadTestConfig(basePath))
	{
		return false;
	}
	
	return true;
}










