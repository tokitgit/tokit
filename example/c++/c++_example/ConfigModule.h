#pragma once
#include <vector>

class IConfigModule
{
public:
	virtual const char* Name() = 0;

	virtual bool LoadBinary(const std::string& configDirectory) = 0;
};

// 配置模块（用于统一管理配置的加载）
class ConfigModule
{
public:
	// 初始化
	bool Init();

	// 重载配置
	bool Reload();

	// 注册一个配置模块
	bool RegisterConfig(IConfigModule& configModule);

public:
	// 从二进制串中读取字符串
	static bool ReadString(const char* buffer, int& peek, std::string& str);

	// 数组大小是否合法
	static bool IsArraySizeValid(int arraySize);

public:
	std::string m_resourcePath;

	std::vector<IConfigModule*> m_vecConfigModule;
};