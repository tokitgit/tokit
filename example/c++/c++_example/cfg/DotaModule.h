//------------------------------------------------------------------------------
// 本头文件由工具自动生成，请勿在本文件内做改动
// 日期：
//------------------------------------------------------------------------------

#pragma once

#include <string>
#include <map>
#include <vector>
#include <set>






// dota装备表
struct DotaEquipConfig
{
	DotaEquipConfig()
	{
		Clear();
	}
	
	inline void Clear()
	{
	
		id = 0;
		
	
		name = "";
		
	
		desc = "";
		
	
		price = 0;
		
	
		isdrop = false;
		
	
		attack = 0;
		
	
		vecbornlist.clear();
		
	
		vecbornnum.clear();
		
	
	}
	
	int id; // 物品ID<唯一>
	std::string name; // 物品名称<唯一>
	std::string desc; // 描述
	int price; // 售出价格
	bool isdrop; // 是否死亡掉落
	int attack; // 攻击力
	std::vector<int> vecbornlist; // 合成列表<数组>
	std::vector<int> vecbornnum; // 合成数量<数组>
	
};



// dota英雄表
struct DotaHeroConfig
{
	DotaHeroConfig()
	{
		Clear();
	}
	
	inline void Clear()
	{
	
		id = 0;
		
	
		name = "";
		
	
		strength = 0.0f;
		
	
		agile = 0.0f;
		
	
		intelligense = 0.0f;
		
	
	}
	
	int id; // 英雄ID<唯一>
	std::string name; // 英雄名称<唯一>
	double strength; // 力量
	double agile; // 敏捷
	double intelligense; // 智力
	
};



// dota技能表
struct DotaSkillConfig
{
	DotaSkillConfig()
	{
		Clear();
	}
	
	inline void Clear()
	{
	
		id = 0;
		
	
		name = "";
		
	
		strength = 0.0f;
		
	
		agile = 0.0f;
		
	
		intelligense = 0.0f;
		
	
	}
	
	int id; // 英雄ID<唯一>
	std::string name; // 英雄名称<唯一>
	double strength; // 力量
	double agile; // 敏捷
	double intelligense; // 智力
	
};



// dota怪物表
struct DotaNpcConfig
{
	DotaNpcConfig()
	{
		Clear();
	}
	
	inline void Clear()
	{
	
		id = 0;
		
	
		name = "";
		
	
		strength = 0.0f;
		
	
		agile = 0.0f;
		
	
		intelligense = 0.0f;
		
	
	}
	
	int id; // 英雄ID<唯一>
	std::string name; // 英雄名称<唯一>
	double strength; // 力量
	double agile; // 敏捷
	double intelligense; // 智力
	
};















class DotaModule
{
public:
	static DotaModule instance;

public:
	// 获取本配置类名称
	const char* Name(){ return "DotaModule"; }

public:
	
	// 载入配置
	bool Load(std::string basePath);


	bool LoadDotaEquipConfig(std::string basePath);


	bool LoadDotaHeroConfig(std::string basePath);


	bool LoadDotaSkillConfig(std::string basePath);


	bool LoadDotaNpcConfig(std::string basePath);



    // 清空配置
    void Clear();
	
public:
	



	// 物品ID
	const DotaEquipConfig* FindDotaEquipConfigByid(int id);

	// 物品名称
	const DotaEquipConfig* FindDotaEquipConfigByname(std::string name);




	// 英雄ID
	const DotaHeroConfig* FindDotaHeroConfigByid(int id);

	// 英雄名称
	const DotaHeroConfig* FindDotaHeroConfigByname(std::string name);




	// 英雄ID
	const DotaSkillConfig* FindDotaSkillConfigByid(int id);

	// 英雄名称
	const DotaSkillConfig* FindDotaSkillConfigByname(std::string name);




	// 英雄ID
	const DotaNpcConfig* FindDotaNpcConfigByid(int id);

	// 英雄名称
	const DotaNpcConfig* FindDotaNpcConfigByname(std::string name);



	
public:
	

	// dota装备表
	std::vector<DotaEquipConfig> m_vecDotaEquipConfig;

	// dota英雄表
	std::vector<DotaHeroConfig> m_vecDotaHeroConfig;

	// dota技能表
	std::vector<DotaSkillConfig> m_vecDotaSkillConfig;

	// dota怪物表
	std::vector<DotaNpcConfig> m_vecDotaNpcConfig;




	// 物品ID
	std::map<int, DotaEquipConfig*> m_mapDotaEquipConfigByid;

	// 物品名称
	std::map<std::string, DotaEquipConfig*> m_mapDotaEquipConfigByname;




	// 英雄ID
	std::map<int, DotaHeroConfig*> m_mapDotaHeroConfigByid;

	// 英雄名称
	std::map<std::string, DotaHeroConfig*> m_mapDotaHeroConfigByname;




	// 英雄ID
	std::map<int, DotaSkillConfig*> m_mapDotaSkillConfigByid;

	// 英雄名称
	std::map<std::string, DotaSkillConfig*> m_mapDotaSkillConfigByname;




	// 英雄ID
	std::map<int, DotaNpcConfig*> m_mapDotaNpcConfigByid;

	// 英雄名称
	std::map<std::string, DotaNpcConfig*> m_mapDotaNpcConfigByname;



};