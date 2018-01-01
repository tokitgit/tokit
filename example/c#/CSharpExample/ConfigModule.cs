using System;
using System.Collections.Generic;
using System.IO;

public abstract class IConfigModule
{
	// 初始化
	public abstract bool Init();

	public abstract bool Load(string configDirectory);
}

// 配置管理模块
public class ConfigModule
{
	public static ConfigModule instance;

	public List<IConfigModule> m_listConfigModule = new List<IConfigModule>();

	public System.Text.Encoding m_encoding = System.Text.Encoding.GetEncoding("GB2312");

	// 初始化
	public bool Init()
	{
		instance = this;

		// 注册模块
		RegisterConfig(new TestConfigModule());

		// 加载配置
		return Reload();
	}

	public bool RegisterConfig(IConfigModule configModule)
	{
		m_listConfigModule.Add(configModule);
		return true;
	}

	// 重载配置
	public bool Reload()
	{
		string configDirectory = @"..\..\";

		bool ok = true;

		for (int i = 0; i < m_listConfigModule.Count; ++i)
		{
			IConfigModule configModule = m_listConfigModule[i];
			configModule.Init();

			if (!configModule.Load(configDirectory))
			{
				ok = false;
			}
		}

		if (!ok)
		{
			return false;
		}

		return ok;
	}

	public static unsafe string ReadByteString(byte* bytes, ref int peek)
	{
		int stringSize = *((int*)(bytes + peek));

		peek += sizeof(int);

		if (stringSize == 0)
		{
			return "";
		}

		if (stringSize < 0 || stringSize > 1000000)
		{
			Console.WriteLine("加载二进制配置失败，原因 = 读取字符串时，读取到的字符串长度不合法" + stringSize);
			return "";
		}

		int before = peek;
		peek += stringSize;

		return instance.m_encoding.GetString(bytes + before, stringSize);
	}

	public static string ReadString(BinaryReader binaryReader)
	{
		int stringSize = binaryReader.ReadInt32();
		if (stringSize == 0)
		{
			return "";
		}

		if (stringSize < 0 || stringSize > 1000000)
		{
			Console.WriteLine("加载二进制配置失败，原因 = 读取字符串时，读取到的字符串长度不合法" + stringSize);
			return "";
		}

		byte[] buffer = binaryReader.ReadBytes(stringSize);

		return instance.m_encoding.GetString(buffer);
	}

	public static bool IsArraySizeValid(int arraySize)
	{
		if (arraySize == 0)
		{
			return true;
		}

		if (arraySize < 0 || arraySize > 1000000)
		{
			Console.WriteLine("加载二进制配置失败，原因 = 读取数组时，读取数组长度不合法" + arraySize);
			return false;
		}

		return true;
	}
}