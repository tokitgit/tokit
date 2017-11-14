using System.Collections.Generic;
using Newtonsoft.Json;
using System.IO;
using UnityEngine;
using System;



// dota装备表
public partial class DotaEquipConfig
{

	// 物品ID
	public int id;

	// 物品名称
	public string name;

	// 描述
	public string desc;

	// 售出价格
	public int price;

	// 是否死亡掉落
	public bool isdrop;

	// 攻击力
	public int attack;

	// 合成列表
	public int m_listbornlist;

	// 合成数量
	public int m_listbornnum;
 }

// dota英雄表
public partial class DotaHeroConfig
{

	// 英雄ID
	public int id;

	// 英雄名称
	public string name;

	// 力量
	public double strength;

	// 敏捷
	public double agile;

	// 智力
	public double intelligense;
 }

// dota技能表
public partial class DotaSkillConfig
{

	// 英雄ID
	public int id;

	// 英雄名称
	public string name;

	// 力量
	public double strength;

	// 敏捷
	public double agile;

	// 智力
	public double intelligense;
 }

// dota怪物表
public partial class DotaNpcConfig
{

	// 英雄ID
	public int id;

	// 英雄名称
	public string name;

	// 力量
	public double strength;

	// 敏捷
	public double agile;

	// 智力
	public double intelligense;
 }


public partial class DotaModule
{		
	public static DotaModule instance = new DotaModule();
	
	
	// dota装备表
	public List<DotaEquipConfig> m_listDotaEquipConfig = new List<DotaEquipConfig>();

	// dota英雄表
	public List<DotaHeroConfig> m_listDotaHeroConfig = new List<DotaHeroConfig>();

	// dota技能表
	public List<DotaSkillConfig> m_listDotaSkillConfig = new List<DotaSkillConfig>();

	// dota怪物表
	public List<DotaNpcConfig> m_listDotaNpcConfig = new List<DotaNpcConfig>();

	

	// 物品ID
	public Dictionary<int, DotaEquipConfig> m_mapDotaEquipConfigByid = new Dictionary<int, DotaEquipConfig>();
	
	// 物品名称
	public Dictionary<string, DotaEquipConfig> m_mapDotaEquipConfigByname = new Dictionary<string, DotaEquipConfig>();
	


	// 英雄ID
	public Dictionary<int, DotaHeroConfig> m_mapDotaHeroConfigByid = new Dictionary<int, DotaHeroConfig>();
	
	// 英雄名称
	public Dictionary<string, DotaHeroConfig> m_mapDotaHeroConfigByname = new Dictionary<string, DotaHeroConfig>();
	


	// 英雄ID
	public Dictionary<int, DotaSkillConfig> m_mapDotaSkillConfigByid = new Dictionary<int, DotaSkillConfig>();
	
	// 英雄名称
	public Dictionary<string, DotaSkillConfig> m_mapDotaSkillConfigByname = new Dictionary<string, DotaSkillConfig>();
	


	// 英雄ID
	public Dictionary<int, DotaNpcConfig> m_mapDotaNpcConfigByid = new Dictionary<int, DotaNpcConfig>();
	
	// 英雄名称
	public Dictionary<string, DotaNpcConfig> m_mapDotaNpcConfigByname = new Dictionary<string, DotaNpcConfig>();
	

	
	
	// 物品ID
	public DotaEquipConfig GetDotaEquipConfigByid(int id)
	{
		DotaEquipConfig ret;
		m_mapDotaEquipConfigByid.TryGetValue(id, out ret);
		return ret;
	}
	
	// 物品名称
	public DotaEquipConfig GetDotaEquipConfigByname(string name)
	{
		DotaEquipConfig ret;
		m_mapDotaEquipConfigByname.TryGetValue(name, out ret);
		return ret;
	}
	

	
	// 英雄ID
	public DotaHeroConfig GetDotaHeroConfigByid(int id)
	{
		DotaHeroConfig ret;
		m_mapDotaHeroConfigByid.TryGetValue(id, out ret);
		return ret;
	}
	
	// 英雄名称
	public DotaHeroConfig GetDotaHeroConfigByname(string name)
	{
		DotaHeroConfig ret;
		m_mapDotaHeroConfigByname.TryGetValue(name, out ret);
		return ret;
	}
	

	
	// 英雄ID
	public DotaSkillConfig GetDotaSkillConfigByid(int id)
	{
		DotaSkillConfig ret;
		m_mapDotaSkillConfigByid.TryGetValue(id, out ret);
		return ret;
	}
	
	// 英雄名称
	public DotaSkillConfig GetDotaSkillConfigByname(string name)
	{
		DotaSkillConfig ret;
		m_mapDotaSkillConfigByname.TryGetValue(name, out ret);
		return ret;
	}
	

	
	// 英雄ID
	public DotaNpcConfig GetDotaNpcConfigByid(int id)
	{
		DotaNpcConfig ret;
		m_mapDotaNpcConfigByid.TryGetValue(id, out ret);
		return ret;
	}
	
	// 英雄名称
	public DotaNpcConfig GetDotaNpcConfigByname(string name)
	{
		DotaNpcConfig ret;
		m_mapDotaNpcConfigByname.TryGetValue(name, out ret);
		return ret;
	}
	

	
	// 加载单个文件
	public bool LoadDotaEquipConfig(string basePath)
	{
		string jsonPath = basePath + @"DotaEquipConfig.json";
		string jsonText = File.ReadAllText(jsonPath, System.Text.Encoding.Default);
		
		try
		{
			m_listDotaEquipConfig = (List<DotaEquipConfig>)Newtonsoft.Json.JsonConvert.DeserializeObject(jsonText, typeof(List<DotaEquipConfig>));
		}
		catch (Exception e)
		{
			Debug.Log("加载" + jsonPath + "配置失败，原因 = " + e.Message);
		}			

		for (int i = 0; i < m_listDotaEquipConfig.Count; ++i)
		{
			DotaEquipConfig row = m_listDotaEquipConfig[i];
				m_mapDotaEquipConfigByid[row.id] = row;
				m_mapDotaEquipConfigByname[row.name] = row;
		}
		
		return true;
	}

	// 加载单个文件
	public bool LoadDotaHeroConfig(string basePath)
	{
		string jsonPath = basePath + @"DotaHeroConfig.json";
		string jsonText = File.ReadAllText(jsonPath, System.Text.Encoding.Default);
		
		try
		{
			m_listDotaHeroConfig = (List<DotaHeroConfig>)Newtonsoft.Json.JsonConvert.DeserializeObject(jsonText, typeof(List<DotaHeroConfig>));
		}
		catch (Exception e)
		{
			Debug.Log("加载" + jsonPath + "配置失败，原因 = " + e.Message);
		}			

		for (int i = 0; i < m_listDotaHeroConfig.Count; ++i)
		{
			DotaHeroConfig row = m_listDotaHeroConfig[i];
				m_mapDotaHeroConfigByid[row.id] = row;
				m_mapDotaHeroConfigByname[row.name] = row;
		}
		
		return true;
	}

	// 加载单个文件
	public bool LoadDotaSkillConfig(string basePath)
	{
		string jsonPath = basePath + @"DotaSkillConfig.json";
		string jsonText = File.ReadAllText(jsonPath, System.Text.Encoding.Default);
		
		try
		{
			m_listDotaSkillConfig = (List<DotaSkillConfig>)Newtonsoft.Json.JsonConvert.DeserializeObject(jsonText, typeof(List<DotaSkillConfig>));
		}
		catch (Exception e)
		{
			Debug.Log("加载" + jsonPath + "配置失败，原因 = " + e.Message);
		}			

		for (int i = 0; i < m_listDotaSkillConfig.Count; ++i)
		{
			DotaSkillConfig row = m_listDotaSkillConfig[i];
				m_mapDotaSkillConfigByid[row.id] = row;
				m_mapDotaSkillConfigByname[row.name] = row;
		}
		
		return true;
	}

	// 加载单个文件
	public bool LoadDotaNpcConfig(string basePath)
	{
		string jsonPath = basePath + @"DotaNpcConfig.json";
		string jsonText = File.ReadAllText(jsonPath, System.Text.Encoding.Default);
		
		try
		{
			m_listDotaNpcConfig = (List<DotaNpcConfig>)Newtonsoft.Json.JsonConvert.DeserializeObject(jsonText, typeof(List<DotaNpcConfig>));
		}
		catch (Exception e)
		{
			Debug.Log("加载" + jsonPath + "配置失败，原因 = " + e.Message);
		}			

		for (int i = 0; i < m_listDotaNpcConfig.Count; ++i)
		{
			DotaNpcConfig row = m_listDotaNpcConfig[i];
				m_mapDotaNpcConfigByid[row.id] = row;
				m_mapDotaNpcConfigByname[row.name] = row;
		}
		
		return true;
	}

	
	// 加载配置
	public bool Load(string basePath)
	{
		if (!LoadDotaEquipConfig(basePath))
		{
			return false;
		}
		
		if (!LoadDotaHeroConfig(basePath))
		{
			return false;
		}
		
		if (!LoadDotaSkillConfig(basePath))
		{
			return false;
		}
		
		if (!LoadDotaNpcConfig(basePath))
		{
			return false;
		}
		
		return true;
	}

}






	












