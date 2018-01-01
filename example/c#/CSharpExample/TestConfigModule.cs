//------------------------------------------------------------
// 本文件由工具自动生成，请勿改动
//------------------------------------------------------------

using System.Collections.Generic;
using System.IO;
using System;

// 测试用例表
public partial class TestConfig
{

	// 字符串
	public string stringfield;
	
	// bool型
	public bool boolfield;
	
	// 字符
	public byte charfield;
	
	// 16位整数
	public int int16field;
	
	// 32位整数
	public int intfield;
	
	// 64位整数
	public long int64field;
	
	// 浮点数
	public float floatfield;
	
	// 双精度浮点数
	public double doublefield;
	
	// 字符串唯一
	public string stringfieldunique;
	
	// bool型唯一
	public bool boolfieldunique;
	
	// 字符唯一
	public byte charfieldunique;
	
	// 16位整数唯一
	public int int16fieldunique;
	
	// 32位整数唯一
	public int intfieldunique;
	
	// 64位整数唯一
	public long int64fieldunique;
	
	// 浮点数唯一
	public float floatfieldunique;
	
	// 双精度浮点数唯一
	public double doublefieldunique;
	
	// 字符串数组
	public List<string> stringfieldarray;
	
	// bool型数组
	public List<bool> boolfieldarray;
	
	// 字符数组
	public List<byte> charfieldarray;
	
	// 16位整数数组
	public List<int> int16fieldarray;
	
	// 32位整数数组
	public List<int> intfieldarray;
	
	// 64位整数数组
	public List<long> int64fieldarray;
	
	// 浮点数数组
	public List<float> floatfieldarray;
	
	// 双精度浮点数数组
	public List<double> doublefieldarray;
	
}

public partial class TestConfigModule : IConfigModule
{		
	public static TestConfigModule instance;
	
	// 初始化
	public override bool Init()
	{
		instance = this;
		return true;
	}
	
	// 测试用例表
	public List<TestConfig> m_listTestConfig = new List<TestConfig>();

	// 字符串唯一
	public Dictionary<string, TestConfig> m_mapTestConfigBystringfieldunique = new Dictionary<string, TestConfig>();
	
	// bool型唯一
	public Dictionary<bool, TestConfig> m_mapTestConfigByboolfieldunique = new Dictionary<bool, TestConfig>();
	
	// 字符唯一
	public Dictionary<byte, TestConfig> m_mapTestConfigBycharfieldunique = new Dictionary<byte, TestConfig>();
	
	// 16位整数唯一
	public Dictionary<int, TestConfig> m_mapTestConfigByint16fieldunique = new Dictionary<int, TestConfig>();
	
	// 32位整数唯一
	public Dictionary<int, TestConfig> m_mapTestConfigByintfieldunique = new Dictionary<int, TestConfig>();
	
	// 64位整数唯一
	public Dictionary<long, TestConfig> m_mapTestConfigByint64fieldunique = new Dictionary<long, TestConfig>();
	
	// 浮点数唯一
	public Dictionary<float, TestConfig> m_mapTestConfigByfloatfieldunique = new Dictionary<float, TestConfig>();
	
	// 双精度浮点数唯一
	public Dictionary<double, TestConfig> m_mapTestConfigBydoublefieldunique = new Dictionary<double, TestConfig>();
	
	// 字符串唯一
	public TestConfig GetTestConfigBystringfieldunique(string stringfieldunique)
	{
		TestConfig ret;
		m_mapTestConfigBystringfieldunique.TryGetValue(stringfieldunique, out ret);
		return ret;
	}
	
	// bool型唯一
	public TestConfig GetTestConfigByboolfieldunique(bool boolfieldunique)
	{
		TestConfig ret;
		m_mapTestConfigByboolfieldunique.TryGetValue(boolfieldunique, out ret);
		return ret;
	}
	
	// 字符唯一
	public TestConfig GetTestConfigBycharfieldunique(byte charfieldunique)
	{
		TestConfig ret;
		m_mapTestConfigBycharfieldunique.TryGetValue(charfieldunique, out ret);
		return ret;
	}
	
	// 16位整数唯一
	public TestConfig GetTestConfigByint16fieldunique(int int16fieldunique)
	{
		TestConfig ret;
		m_mapTestConfigByint16fieldunique.TryGetValue(int16fieldunique, out ret);
		return ret;
	}
	
	// 32位整数唯一
	public TestConfig GetTestConfigByintfieldunique(int intfieldunique)
	{
		TestConfig ret;
		m_mapTestConfigByintfieldunique.TryGetValue(intfieldunique, out ret);
		return ret;
	}
	
	// 64位整数唯一
	public TestConfig GetTestConfigByint64fieldunique(long int64fieldunique)
	{
		TestConfig ret;
		m_mapTestConfigByint64fieldunique.TryGetValue(int64fieldunique, out ret);
		return ret;
	}
	
	// 浮点数唯一
	public TestConfig GetTestConfigByfloatfieldunique(float floatfieldunique)
	{
		TestConfig ret;
		m_mapTestConfigByfloatfieldunique.TryGetValue(floatfieldunique, out ret);
		return ret;
	}
	
	// 双精度浮点数唯一
	public TestConfig GetTestConfigBydoublefieldunique(double doublefieldunique)
	{
		TestConfig ret;
		m_mapTestConfigBydoublefieldunique.TryGetValue(doublefieldunique, out ret);
		return ret;
	}
	
	// 读取文件内容（声明了unsafe修饰符）
	public unsafe bool UnsafeLoadTestConfigBinary(string binaryPath, Byte[] bytes)
	{
		fixed (byte* p = bytes)
		{
			if (bytes.Length < sizeof(int))
			{
				Console.WriteLine("加载" + binaryPath + "二进制配置失败，原因是文件的大小" + bytes.Length + "不合法，必须 >= " + sizeof(int));
				return false;
			}
			
			// 取出行数
			int rowCount = *((int*)p);
			if (rowCount < 0 || rowCount >= 1000000)
			{
				Console.WriteLine("加载" + binaryPath + "二进制配置失败，原因是读取到文件开头的行数" + rowCount + "不合法");
				return false;
			}			
			
			m_listTestConfig.Capacity = rowCount;
						
			for (int peek = sizeof(int); peek < bytes.Length;)
			{
				TestConfig row = new TestConfig();
				
				// 解析该行配置
			
				row.stringfield = ConfigModule.ReadByteString(p, ref peek);
				
				row.boolfield = (p[peek] != '\0');peek += sizeof(bool);
				
				row.charfield = (byte)p[peek];peek += sizeof(byte);
				
				row.int16field = *((short*)(p + peek));peek += sizeof(short);
				
				row.intfield = *((int*)(p + peek));peek += sizeof(int);
				
				row.int64field = *((long*)(p + peek));peek += sizeof(long);
				
				row.floatfield = *((float*)(p + peek));peek += sizeof(float);
				
				row.doublefield = *((double*)(p + peek));peek += sizeof(double);
				
				row.stringfieldunique = ConfigModule.ReadByteString(p, ref peek);
				
				row.boolfieldunique = (p[peek] != '\0');peek += sizeof(bool);
				
				row.charfieldunique = (byte)p[peek];peek += sizeof(byte);
				
				row.int16fieldunique = *((short*)(p + peek));peek += sizeof(short);
				
				row.intfieldunique = *((int*)(p + peek));peek += sizeof(int);
				
				row.int64fieldunique = *((long*)(p + peek));peek += sizeof(long);
				
				row.floatfieldunique = *((float*)(p + peek));peek += sizeof(float);
				
				row.doublefieldunique = *((double*)(p + peek));peek += sizeof(double);
				
				row.stringfieldarray = new List<string>();
				
				int stringfieldarrayArraySize = *((int*)(p + peek));peek += sizeof(int);
				if (!ConfigModule.IsArraySizeValid(stringfieldarrayArraySize))
				{
					Console.WriteLine("加载" + binaryPath + "二进制配置失败，原因是读取到stringfieldarray数组长度不合法 = " + stringfieldarrayArraySize);
					return false;
				}
				
				row.stringfieldarray.Capacity = stringfieldarrayArraySize;
				
				for (int i = 0; i < stringfieldarrayArraySize; ++i)
				{
					row.stringfieldarray.Add(ConfigModule.ReadByteString(p, ref peek));
					
				}
				
				row.boolfieldarray = new List<bool>();
				
				int boolfieldarrayArraySize = *((int*)(p + peek));peek += sizeof(int);
				if (!ConfigModule.IsArraySizeValid(boolfieldarrayArraySize))
				{
					Console.WriteLine("加载" + binaryPath + "二进制配置失败，原因是读取到boolfieldarray数组长度不合法 = " + boolfieldarrayArraySize);
					return false;
				}
				
				row.boolfieldarray.Capacity = boolfieldarrayArraySize;
				
				for (int i = 0; i < boolfieldarrayArraySize; ++i)
				{
					row.boolfieldarray.Add(p[peek] != '\0');peek += sizeof(bool);
					
				}
				
				row.charfieldarray = new List<byte>();
				
				int charfieldarrayArraySize = *((int*)(p + peek));peek += sizeof(int);
				if (!ConfigModule.IsArraySizeValid(charfieldarrayArraySize))
				{
					Console.WriteLine("加载" + binaryPath + "二进制配置失败，原因是读取到charfieldarray数组长度不合法 = " + charfieldarrayArraySize);
					return false;
				}
				
				row.charfieldarray.Capacity = charfieldarrayArraySize;
				
				for (int i = 0; i < charfieldarrayArraySize; ++i)
				{
					row.charfieldarray.Add((byte)p[peek]);peek += sizeof(byte);
					
				}
				
				row.int16fieldarray = new List<int>();
				
				int int16fieldarrayArraySize = *((int*)(p + peek));peek += sizeof(int);
				if (!ConfigModule.IsArraySizeValid(int16fieldarrayArraySize))
				{
					Console.WriteLine("加载" + binaryPath + "二进制配置失败，原因是读取到int16fieldarray数组长度不合法 = " + int16fieldarrayArraySize);
					return false;
				}
				
				row.int16fieldarray.Capacity = int16fieldarrayArraySize;
				
				for (int i = 0; i < int16fieldarrayArraySize; ++i)
				{
					row.int16fieldarray.Add(*((short*)(p + peek)));peek += sizeof(short);
					
				}
				
				row.intfieldarray = new List<int>();
				
				int intfieldarrayArraySize = *((int*)(p + peek));peek += sizeof(int);
				if (!ConfigModule.IsArraySizeValid(intfieldarrayArraySize))
				{
					Console.WriteLine("加载" + binaryPath + "二进制配置失败，原因是读取到intfieldarray数组长度不合法 = " + intfieldarrayArraySize);
					return false;
				}
				
				row.intfieldarray.Capacity = intfieldarrayArraySize;
				
				for (int i = 0; i < intfieldarrayArraySize; ++i)
				{
					row.intfieldarray.Add(*((int*)(p + peek)));peek += sizeof(int);
					
				}
				
				row.int64fieldarray = new List<long>();
				
				int int64fieldarrayArraySize = *((int*)(p + peek));peek += sizeof(int);
				if (!ConfigModule.IsArraySizeValid(int64fieldarrayArraySize))
				{
					Console.WriteLine("加载" + binaryPath + "二进制配置失败，原因是读取到int64fieldarray数组长度不合法 = " + int64fieldarrayArraySize);
					return false;
				}
				
				row.int64fieldarray.Capacity = int64fieldarrayArraySize;
				
				for (int i = 0; i < int64fieldarrayArraySize; ++i)
				{
					row.int64fieldarray.Add(*((long*)(p + peek)));peek += sizeof(long);
					
				}
				
				row.floatfieldarray = new List<float>();
				
				int floatfieldarrayArraySize = *((int*)(p + peek));peek += sizeof(int);
				if (!ConfigModule.IsArraySizeValid(floatfieldarrayArraySize))
				{
					Console.WriteLine("加载" + binaryPath + "二进制配置失败，原因是读取到floatfieldarray数组长度不合法 = " + floatfieldarrayArraySize);
					return false;
				}
				
				row.floatfieldarray.Capacity = floatfieldarrayArraySize;
				
				for (int i = 0; i < floatfieldarrayArraySize; ++i)
				{
					row.floatfieldarray.Add(*((float*)(p + peek)));peek += sizeof(float);
					
				}
				
				row.doublefieldarray = new List<double>();
				
				int doublefieldarrayArraySize = *((int*)(p + peek));peek += sizeof(int);
				if (!ConfigModule.IsArraySizeValid(doublefieldarrayArraySize))
				{
					Console.WriteLine("加载" + binaryPath + "二进制配置失败，原因是读取到doublefieldarray数组长度不合法 = " + doublefieldarrayArraySize);
					return false;
				}
				
				row.doublefieldarray.Capacity = doublefieldarrayArraySize;
				
				for (int i = 0; i < doublefieldarrayArraySize; ++i)
				{
					row.doublefieldarray.Add(*((double*)(p + peek)));peek += sizeof(double);
					
				}
				
				m_listTestConfig.Add(row);
			
			}
		}
		
		for (int i = 0; i < m_listTestConfig.Count; ++i)
		{
			TestConfig row = m_listTestConfig[i];
			
			m_mapTestConfigBystringfieldunique[row.stringfieldunique] = row;
			
			m_mapTestConfigByboolfieldunique[row.boolfieldunique] = row;
			
			m_mapTestConfigBycharfieldunique[row.charfieldunique] = row;
			
			m_mapTestConfigByint16fieldunique[row.int16fieldunique] = row;
			
			m_mapTestConfigByintfieldunique[row.intfieldunique] = row;
			
			m_mapTestConfigByint64fieldunique[row.int64fieldunique] = row;
			
			m_mapTestConfigByfloatfieldunique[row.floatfieldunique] = row;
			
			m_mapTestConfigBydoublefieldunique[row.doublefieldunique] = row;
			
		}
		
		return true;
	}

	// 加载单个文件（通过原始指针方式）
	public bool LoadTestConfigBinaryByPointer(string basePath)
	{
		string binaryPath = basePath + @"Binary/TestConfig.bin";

		try
		{
			FileStream fileStream = new FileStream(binaryPath, FileMode.Open);

			Byte[] bytes = new Byte[fileStream.Length];
			fileStream.Read(bytes, 0, (int)fileStream.Length);
			fileStream.Close();

			if (!UnsafeLoadTestConfigBinary(binaryPath, bytes))
			{
				return false;
			}
		}
		catch (Exception e)
		{
			Console.WriteLine("加载" + binaryPath + "二进制配置失败，原因 = " + e.Message);
			return false;
		}			
		
		return true;
	}

	// 加载配置
	public override bool Load(string configDirectory)
	{
		
		if (!LoadTestConfigBinaryByPointer(configDirectory))
		{
			return false;
		}
		
		return true;
	}

}