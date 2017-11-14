using System.Collections.Generic;
using Newtonsoft.Json;
using System.IO;
using UnityEngine;
using System;



// 测试用例表
public partial class TestConfig
{

	// 字符串
	public string stringfield;

	// bool型
	public bool boolfield;

	// 字符
	public char charfield;

	// 16位整数
	public int int16field;

	// 32位整数
	public int intfield;

	// 64位整数
	public long int64field;

	// 8位无符号整数
	public int uint8field;

	// 16位无符号整数
	public int uint16field;

	// 32位无符号整数
	public int uintfield;

	// 64位无符号整数
	public long uint64field;

	// 浮点数
	public float floatfield;

	// 双精度浮点数
	public double doublefield;

	// 字符串主键
	public string stringfieldprimary;

	// bool型主键
	public bool boolfieldprimary;

	// 字符主键
	public char charfieldprimary;

	// 16位整数主键
	public int int16fieldprimary;

	// 32位整数主键
	public int intfieldprimary;

	// 64位整数主键
	public long int64fieldprimary;

	// 8位无符号整数主键
	public int uint8fieldprimary;

	// 16位无符号整数主键
	public int uint16fieldprimary;

	// 32位无符号整数主键
	public int uintfieldprimary;

	// 64位无符号整数主键
	public long uint64fieldprimary;

	// 浮点数主键
	public float floatfieldprimary;

	// 双精度浮点数主键
	public double doublefieldprimary;

	// 字符串唯一
	public string stringfieldunique;

	// bool型唯一
	public bool boolfieldunique;

	// 字符唯一
	public char charfieldunique;

	// 16位整数唯一
	public int int16fieldunique;

	// 32位整数唯一
	public int intfieldunique;

	// 64位整数唯一
	public long int64fieldunique;

	// 8位无符号整数唯一
	public int uint8fieldunique;

	// 16位无符号整数唯一
	public int uint16fieldunique;

	// 32位无符号整数唯一
	public int uintfieldunique;

	// 64位无符号整数唯一
	public long uint64fieldunique;

	// 浮点数唯一
	public float floatfieldunique;

	// 双精度浮点数唯一
	public double doublefieldunique;

	// 字符串数组
	public string m_liststringfieldarray;

	// bool型数组
	public bool m_listboolfieldarray;

	// 字符数组
	public char m_listcharfieldarray;

	// 16位整数数组
	public int m_listint16fieldarray;

	// 32位整数数组
	public int m_listintfieldarray;

	// 64位整数数组
	public long m_listint64fieldarray;

	// 8位无符号整数数组
	public int m_listuint8fieldarray;

	// 16位无符号整数数组
	public int m_listuint16fieldarray;

	// 32位无符号整数数组
	public int m_listuintfieldarray;

	// 64位无符号整数数组
	public long m_listuint64fieldarray;

	// 浮点数数组
	public float m_listfloatfieldarray;

	// 双精度浮点数数组
	public double m_listdoublefieldarray;

	// 字符串集合
	public string m_setstringfieldset;

	// bool型集合
	public bool m_setboolfieldset;

	// 字符集合
	public char m_setcharfieldset;

	// 16位整数集合
	public int m_setint16fieldset;

	// 32位整数集合
	public int m_setintfieldset;

	// 64位整数集合
	public long m_setint64fieldset;

	// 8位无符号整数集合
	public int m_setuint8fieldset;

	// 16位无符号整数集合
	public int m_setuint16fieldset;

	// 32位无符号整数集合
	public int m_setuintfieldset;

	// 64位无符号整数集合
	public long m_setuint64fieldset;

	// 浮点数集合
	public float m_setfloatfieldset;

	// 双精度浮点数集合
	public double m_setdoublefieldset;
 }


public partial class TestModule
{		
	public static TestModule instance = new TestModule();
	
	
	// 测试用例表
	public List<TestConfig> m_listTestConfig = new List<TestConfig>();

	

	// 字符串唯一
	public Dictionary<string, TestConfig> m_mapTestConfigBystringfieldunique = new Dictionary<string, TestConfig>();
	
	// bool型唯一
	public Dictionary<bool, TestConfig> m_mapTestConfigByboolfieldunique = new Dictionary<bool, TestConfig>();
	
	// 字符唯一
	public Dictionary<char, TestConfig> m_mapTestConfigBycharfieldunique = new Dictionary<char, TestConfig>();
	
	// 16位整数唯一
	public Dictionary<int, TestConfig> m_mapTestConfigByint16fieldunique = new Dictionary<int, TestConfig>();
	
	// 32位整数唯一
	public Dictionary<int, TestConfig> m_mapTestConfigByintfieldunique = new Dictionary<int, TestConfig>();
	
	// 64位整数唯一
	public Dictionary<long, TestConfig> m_mapTestConfigByint64fieldunique = new Dictionary<long, TestConfig>();
	
	// 8位无符号整数唯一
	public Dictionary<int, TestConfig> m_mapTestConfigByuint8fieldunique = new Dictionary<int, TestConfig>();
	
	// 16位无符号整数唯一
	public Dictionary<int, TestConfig> m_mapTestConfigByuint16fieldunique = new Dictionary<int, TestConfig>();
	
	// 32位无符号整数唯一
	public Dictionary<int, TestConfig> m_mapTestConfigByuintfieldunique = new Dictionary<int, TestConfig>();
	
	// 64位无符号整数唯一
	public Dictionary<long, TestConfig> m_mapTestConfigByuint64fieldunique = new Dictionary<long, TestConfig>();
	
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
	public TestConfig GetTestConfigBycharfieldunique(char charfieldunique)
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
	
	// 8位无符号整数唯一
	public TestConfig GetTestConfigByuint8fieldunique(int uint8fieldunique)
	{
		TestConfig ret;
		m_mapTestConfigByuint8fieldunique.TryGetValue(uint8fieldunique, out ret);
		return ret;
	}
	
	// 16位无符号整数唯一
	public TestConfig GetTestConfigByuint16fieldunique(int uint16fieldunique)
	{
		TestConfig ret;
		m_mapTestConfigByuint16fieldunique.TryGetValue(uint16fieldunique, out ret);
		return ret;
	}
	
	// 32位无符号整数唯一
	public TestConfig GetTestConfigByuintfieldunique(int uintfieldunique)
	{
		TestConfig ret;
		m_mapTestConfigByuintfieldunique.TryGetValue(uintfieldunique, out ret);
		return ret;
	}
	
	// 64位无符号整数唯一
	public TestConfig GetTestConfigByuint64fieldunique(long uint64fieldunique)
	{
		TestConfig ret;
		m_mapTestConfigByuint64fieldunique.TryGetValue(uint64fieldunique, out ret);
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
	

	
	// 加载单个文件
	public bool LoadTestConfig(string basePath)
	{
		string jsonPath = basePath + @"TestConfig.json";
		string jsonText = File.ReadAllText(jsonPath, System.Text.Encoding.Default);
		
		try
		{
			m_listTestConfig = (List<TestConfig>)Newtonsoft.Json.JsonConvert.DeserializeObject(jsonText, typeof(List<TestConfig>));
		}
		catch (Exception e)
		{
			Debug.Log("加载" + jsonPath + "配置失败，原因 = " + e.Message);
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
				m_mapTestConfigByuint8fieldunique[row.uint8fieldunique] = row;
				m_mapTestConfigByuint16fieldunique[row.uint16fieldunique] = row;
				m_mapTestConfigByuintfieldunique[row.uintfieldunique] = row;
				m_mapTestConfigByuint64fieldunique[row.uint64fieldunique] = row;
				m_mapTestConfigByfloatfieldunique[row.floatfieldunique] = row;
				m_mapTestConfigBydoublefieldunique[row.doublefieldunique] = row;
		}
		
		return true;
	}

	
	// 加载配置
	public bool Load(string basePath)
	{
		if (!LoadTestConfig(basePath))
		{
			return false;
		}
		
		return true;
	}

}






	












