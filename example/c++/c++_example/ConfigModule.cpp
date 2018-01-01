#include <iostream>
#include "ConfigModule.h"
#include "TestConfigModule.h"

bool ConfigModule::Init()
{
	// 注册模块
	RegisterConfig(TestConfigModule::instance);
	return Reload();
}

bool ConfigModule::Reload()
{
	// std::string clientResourcePath = "E:\\proj\\mine\\game\\client\\Config\\";
	m_resourcePath = "binary\\";

	bool ok = true;

	// 开始加载每个模块的配置
	for (int i = 0; i < (int)m_vecConfigModule.size(); ++i)
	{
		IConfigModule* configModule = m_vecConfigModule[i];

		// 通过二进制方式读取
		if (!configModule->LoadBinary(m_resourcePath))
		{
			ok = false;
		}
	}

	return ok;
}

bool ConfigModule::RegisterConfig(IConfigModule& configModule)
{
	m_vecConfigModule.push_back(&configModule);
	return true;
}

bool ConfigModule::ReadString(const char* buffer, int& peek, std::string& str)
{
	// 内存分布：|  字符串大小(int)  |  字符串内容(char[])  |
	int stringSize = *((int*)(buffer + peek));
	peek += sizeof(int);

	if (stringSize == 0)
	{
		// 空字符串是正常的
		return true;
	}

	int before = peek;
	peek += stringSize;

	if (stringSize < 0 || stringSize > 1000000)
	{
		std::cerr << "加载二进制配置失败，原因 = 读取字符串时，读取到的字符串长度不合法 = " <<  stringSize;
		return false;
	}

	str.append(buffer + before, stringSize);
	return true;
}

bool ConfigModule::IsArraySizeValid(int arraySize)
{
	if (arraySize == 0)
	{
		return true;
	}

	if (arraySize < 0 || arraySize > 1000000)
	{
		std::cerr << "加载二进制配置失败，原因 = 读取数组时，读取数组长度不合法 = " << arraySize;
		return false;
	}

	return true;
}