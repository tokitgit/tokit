//------------------------------------------------------------
// 本文件由工具自动生成
//------------------------------------------------------------

#include "TestConfigModule.h"
#include <iostream>
#include "tokit_tool.h"

TestConfigModule TestConfigModule::instance;

// 字符串唯一
const TestConfig* TestConfigModule::FindTestConfigBystringfieldunique(std::string stringfieldunique)
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
const TestConfig* TestConfigModule::FindTestConfigByboolfieldunique(bool boolfieldunique)
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
const TestConfig* TestConfigModule::FindTestConfigBycharfieldunique(char charfieldunique)
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
const TestConfig* TestConfigModule::FindTestConfigByint16fieldunique(int16 int16fieldunique)
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
const TestConfig* TestConfigModule::FindTestConfigByintfieldunique(int intfieldunique)
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
const TestConfig* TestConfigModule::FindTestConfigByint64fieldunique(int64 int64fieldunique)
{
	const auto itr = m_mapTestConfigByint64fieldunique.find(int64fieldunique);
	if (itr == m_mapTestConfigByint64fieldunique.end())
	{
		return nullptr;
	}

	const TestConfig* ret = itr->second;
	return ret;
}

// 浮点数唯一
const TestConfig* TestConfigModule::FindTestConfigByfloatfieldunique(float floatfieldunique)
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
const TestConfig* TestConfigModule::FindTestConfigBydoublefieldunique(double doublefieldunique)
{
	const auto itr = m_mapTestConfigBydoublefieldunique.find(doublefieldunique);
	if (itr == m_mapTestConfigBydoublefieldunique.end())
	{
		return nullptr;
	}

	const TestConfig* ret = itr->second;
	return ret;
}

void TestConfigModule::Clear()
{

	m_vecTestConfig.clear();

	m_mapTestConfigBystringfieldunique.clear();
	m_mapTestConfigByboolfieldunique.clear();
	m_mapTestConfigBycharfieldunique.clear();
	m_mapTestConfigByint16fieldunique.clear();
	m_mapTestConfigByintfieldunique.clear();
	m_mapTestConfigByint64fieldunique.clear();
	m_mapTestConfigByfloatfieldunique.clear();
	m_mapTestConfigBydoublefieldunique.clear();

}

bool TestConfigModule::LoadBinaryTestConfig(const std::string& basePath)
{
	std::string binaryPath = basePath + "TestConfig.bin";
	std::string binaryText;
	if (!tool::GetFileText(binaryPath.c_str(), binaryText))
	{
		std::cerr << "[error] parse failed, not found the file <" << binaryPath << ">!\n";
		return false;
	}
	
	const char* buffer = binaryText.c_str();
	int size = (int)binaryText.size();
	if (size < sizeof(int))
	{
		std::cerr << "[error] parse file <" << binaryPath << "> failed, size = " << size << " is invalid, must >= " << sizeof(int) << "!\n";
		return false;
	}
	
	// 取出行数
	int rowCount = *((int*)buffer);
	if (rowCount < 0 || rowCount >= 1000000)
	{
		std::cerr << "[error] parse file <" << binaryPath << "> failed, size = " << size << " is invalid!\n";
		return false;
	}
	
	m_vecTestConfig.resize(rowCount);
	
	for (int peek = sizeof(int), rowIndex = 0; peek < size && rowIndex < rowCount; ++rowIndex)
	{
	
		TestConfig& row = m_vecTestConfig[rowIndex];
	
		// 解析该行配置
	
		if (!ConfigModule::ReadString(buffer, peek, row.stringfield))
		{
			std::cerr << "加载" << binaryPath << "二进制配置失败，原因是stringfield字符串不合法 = " << peek;
			return false;
		}		
		
		row.boolfield = (buffer[peek] != '\0');peek += sizeof(bool);
		
		row.charfield = buffer[peek];peek += sizeof(char);
		
		row.int16field = *((int16*)(buffer + peek));peek += sizeof(int16);
		
		row.intfield = *((int*)(buffer + peek));peek += sizeof(int);
		
		row.int64field = *((int64*)(buffer + peek));peek += sizeof(int64);
		
		row.floatfield = *((float*)(buffer + peek));peek += sizeof(float);
		
		row.doublefield = *((double*)(buffer + peek));peek += sizeof(double);
		
		if (!ConfigModule::ReadString(buffer, peek, row.stringfieldunique))
		{
			std::cerr << "加载" << binaryPath << "二进制配置失败，原因是stringfieldunique字符串不合法 = " << peek;
			return false;
		}		
		
		row.boolfieldunique = (buffer[peek] != '\0');peek += sizeof(bool);
		
		row.charfieldunique = buffer[peek];peek += sizeof(char);
		
		row.int16fieldunique = *((int16*)(buffer + peek));peek += sizeof(int16);
		
		row.intfieldunique = *((int*)(buffer + peek));peek += sizeof(int);
		
		row.int64fieldunique = *((int64*)(buffer + peek));peek += sizeof(int64);
		
		row.floatfieldunique = *((float*)(buffer + peek));peek += sizeof(float);
		
		row.doublefieldunique = *((double*)(buffer + peek));peek += sizeof(double);
		
		int stringfieldarrayArraySize = *((int*)(buffer + peek));
		peek += sizeof(int);
		
		if (!ConfigModule::IsArraySizeValid(stringfieldarrayArraySize))
		{
			std::cerr << "加载" << binaryPath << "二进制配置失败，原因是读取到stringfieldarray数组长度不合法 = " << stringfieldarrayArraySize;
			return false;
		}
		
		row.vecstringfieldarray.resize(stringfieldarrayArraySize);
		
		for (int i = 0; i < stringfieldarrayArraySize; ++i)
		{
			
			if (!ConfigModule::ReadString(buffer, peek, row.vecstringfieldarray[i]))
			{
				std::cerr << "加载" << binaryPath << "二进制配置失败，原因是stringfieldarray数组中的字符串不合法 = " << peek;
				return false;
			}
			
		}				
		
		int boolfieldarrayArraySize = *((int*)(buffer + peek));
		peek += sizeof(int);
		
		if (!ConfigModule::IsArraySizeValid(boolfieldarrayArraySize))
		{
			std::cerr << "加载" << binaryPath << "二进制配置失败，原因是读取到boolfieldarray数组长度不合法 = " << boolfieldarrayArraySize;
			return false;
		}
		
		row.vecboolfieldarray.resize(boolfieldarrayArraySize);
		
		for (int i = 0; i < boolfieldarrayArraySize; ++i)
		{
			row.vecboolfieldarray[i] = (buffer[peek] != '\0');peek += sizeof(bool);
			
		}				
		
		int charfieldarrayArraySize = *((int*)(buffer + peek));
		peek += sizeof(int);
		
		if (!ConfigModule::IsArraySizeValid(charfieldarrayArraySize))
		{
			std::cerr << "加载" << binaryPath << "二进制配置失败，原因是读取到charfieldarray数组长度不合法 = " << charfieldarrayArraySize;
			return false;
		}
		
		row.veccharfieldarray.resize(charfieldarrayArraySize);
		
		for (int i = 0; i < charfieldarrayArraySize; ++i)
		{
			row.veccharfieldarray[i] = buffer[peek];peek += sizeof(char);
			
		}				
		
		int int16fieldarrayArraySize = *((int*)(buffer + peek));
		peek += sizeof(int);
		
		if (!ConfigModule::IsArraySizeValid(int16fieldarrayArraySize))
		{
			std::cerr << "加载" << binaryPath << "二进制配置失败，原因是读取到int16fieldarray数组长度不合法 = " << int16fieldarrayArraySize;
			return false;
		}
		
		row.vecint16fieldarray.resize(int16fieldarrayArraySize);
		
		for (int i = 0; i < int16fieldarrayArraySize; ++i)
		{
			row.vecint16fieldarray[i] = *((int16*)(buffer + peek));peek += sizeof(int16);
			
		}				
		
		int intfieldarrayArraySize = *((int*)(buffer + peek));
		peek += sizeof(int);
		
		if (!ConfigModule::IsArraySizeValid(intfieldarrayArraySize))
		{
			std::cerr << "加载" << binaryPath << "二进制配置失败，原因是读取到intfieldarray数组长度不合法 = " << intfieldarrayArraySize;
			return false;
		}
		
		row.vecintfieldarray.resize(intfieldarrayArraySize);
		
		for (int i = 0; i < intfieldarrayArraySize; ++i)
		{
			row.vecintfieldarray[i] = *((int*)(buffer + peek));peek += sizeof(int);
			
		}				
		
		int int64fieldarrayArraySize = *((int*)(buffer + peek));
		peek += sizeof(int);
		
		if (!ConfigModule::IsArraySizeValid(int64fieldarrayArraySize))
		{
			std::cerr << "加载" << binaryPath << "二进制配置失败，原因是读取到int64fieldarray数组长度不合法 = " << int64fieldarrayArraySize;
			return false;
		}
		
		row.vecint64fieldarray.resize(int64fieldarrayArraySize);
		
		for (int i = 0; i < int64fieldarrayArraySize; ++i)
		{
			row.vecint64fieldarray[i] = *((int64*)(buffer + peek));peek += sizeof(int64);
			
		}				
		
		int floatfieldarrayArraySize = *((int*)(buffer + peek));
		peek += sizeof(int);
		
		if (!ConfigModule::IsArraySizeValid(floatfieldarrayArraySize))
		{
			std::cerr << "加载" << binaryPath << "二进制配置失败，原因是读取到floatfieldarray数组长度不合法 = " << floatfieldarrayArraySize;
			return false;
		}
		
		row.vecfloatfieldarray.resize(floatfieldarrayArraySize);
		
		for (int i = 0; i < floatfieldarrayArraySize; ++i)
		{
			row.vecfloatfieldarray[i] = *((float*)(buffer + peek));peek += sizeof(float);
			
		}				
		
		int doublefieldarrayArraySize = *((int*)(buffer + peek));
		peek += sizeof(int);
		
		if (!ConfigModule::IsArraySizeValid(doublefieldarrayArraySize))
		{
			std::cerr << "加载" << binaryPath << "二进制配置失败，原因是读取到doublefieldarray数组长度不合法 = " << doublefieldarrayArraySize;
			return false;
		}
		
		row.vecdoublefieldarray.resize(doublefieldarrayArraySize);
		
		for (int i = 0; i < doublefieldarrayArraySize; ++i)
		{
			row.vecdoublefieldarray[i] = *((double*)(buffer + peek));peek += sizeof(double);
			
		}				
		
	}
	
	for (int i = 0, size = (int)m_vecTestConfig.size(); i < size; ++i)
	{
		TestConfig& row = m_vecTestConfig[i];
		
		m_mapTestConfigBystringfieldunique[row.stringfieldunique] = &row;
		
		m_mapTestConfigByboolfieldunique[row.boolfieldunique] = &row;
		
		m_mapTestConfigBycharfieldunique[row.charfieldunique] = &row;
		
		m_mapTestConfigByint16fieldunique[row.int16fieldunique] = &row;
		
		m_mapTestConfigByintfieldunique[row.intfieldunique] = &row;
		
		m_mapTestConfigByint64fieldunique[row.int64fieldunique] = &row;
		
		m_mapTestConfigByfloatfieldunique[row.floatfieldunique] = &row;
		
		m_mapTestConfigBydoublefieldunique[row.doublefieldunique] = &row;
		
	}
	
	return true;
}

bool TestConfigModule::LoadBinary(const std::string& basePath)
{
	Clear();
		
	if (!LoadBinaryTestConfig(basePath))
	{
		return false;
	}
	
	return true;
}