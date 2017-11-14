//------------------------------------------------------------------------------
// 本头文件由工具自动生成，请勿在本文件内做改动
// 日期：
//------------------------------------------------------------------------------

#include "DotaModule.h"
#include <iostream>
#include <rapidjson/document.h>	
#include "tokit_tool.h"




DotaModule DotaModule::instance;





// 物品ID
const DotaEquipConfig* DotaModule::FindDotaEquipConfigByid(int id)
{
	const auto itr = m_mapDotaEquipConfigByid.find(id);
	if (itr == m_mapDotaEquipConfigByid.end())
	{
		return nullptr;
	}

	const DotaEquipConfig* ret = itr->second;
	return ret;
}

// 物品名称
const DotaEquipConfig* DotaModule::FindDotaEquipConfigByname(std::string name)
{
	const auto itr = m_mapDotaEquipConfigByname.find(name);
	if (itr == m_mapDotaEquipConfigByname.end())
	{
		return nullptr;
	}

	const DotaEquipConfig* ret = itr->second;
	return ret;
}




// 英雄ID
const DotaHeroConfig* DotaModule::FindDotaHeroConfigByid(int id)
{
	const auto itr = m_mapDotaHeroConfigByid.find(id);
	if (itr == m_mapDotaHeroConfigByid.end())
	{
		return nullptr;
	}

	const DotaHeroConfig* ret = itr->second;
	return ret;
}

// 英雄名称
const DotaHeroConfig* DotaModule::FindDotaHeroConfigByname(std::string name)
{
	const auto itr = m_mapDotaHeroConfigByname.find(name);
	if (itr == m_mapDotaHeroConfigByname.end())
	{
		return nullptr;
	}

	const DotaHeroConfig* ret = itr->second;
	return ret;
}




// 英雄ID
const DotaSkillConfig* DotaModule::FindDotaSkillConfigByid(int id)
{
	const auto itr = m_mapDotaSkillConfigByid.find(id);
	if (itr == m_mapDotaSkillConfigByid.end())
	{
		return nullptr;
	}

	const DotaSkillConfig* ret = itr->second;
	return ret;
}

// 英雄名称
const DotaSkillConfig* DotaModule::FindDotaSkillConfigByname(std::string name)
{
	const auto itr = m_mapDotaSkillConfigByname.find(name);
	if (itr == m_mapDotaSkillConfigByname.end())
	{
		return nullptr;
	}

	const DotaSkillConfig* ret = itr->second;
	return ret;
}




// 英雄ID
const DotaNpcConfig* DotaModule::FindDotaNpcConfigByid(int id)
{
	const auto itr = m_mapDotaNpcConfigByid.find(id);
	if (itr == m_mapDotaNpcConfigByid.end())
	{
		return nullptr;
	}

	const DotaNpcConfig* ret = itr->second;
	return ret;
}

// 英雄名称
const DotaNpcConfig* DotaModule::FindDotaNpcConfigByname(std::string name)
{
	const auto itr = m_mapDotaNpcConfigByname.find(name);
	if (itr == m_mapDotaNpcConfigByname.end())
	{
		return nullptr;
	}

	const DotaNpcConfig* ret = itr->second;
	return ret;
}




void DotaModule::Clear()
{

	m_vecDotaEquipConfig.clear();

	m_vecDotaHeroConfig.clear();

	m_vecDotaSkillConfig.clear();

	m_vecDotaNpcConfig.clear();


	m_mapDotaEquipConfigByid.clear();
	m_mapDotaEquipConfigByname.clear();

	m_mapDotaHeroConfigByid.clear();
	m_mapDotaHeroConfigByname.clear();

	m_mapDotaSkillConfigByid.clear();
	m_mapDotaSkillConfigByname.clear();

	m_mapDotaNpcConfigByid.clear();
	m_mapDotaNpcConfigByname.clear();


}




bool DotaModule::LoadDotaEquipConfig(std::string basePath)
{
	std::string jsonPath = basePath + "DotaEquipConfig.json";
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
	m_vecDotaEquipConfig.resize(n);
	
	for (int i = 0; i < n; ++i)
	{
		// 逐行提取json元素
		rapidjson::Value &v = doc[i];
		
		DotaEquipConfig& row = m_vecDotaEquipConfig[i];

		row.id = v["id"].GetInt();
		
		row.name = v["name"].GetString();
		
		row.desc = v["desc"].GetString();
		
		row.price = v["price"].GetInt();
		
		row.isdrop = v["isdrop"].GetInt();
		
		row.attack = v["attack"].GetInt();
		
		tool::split_str_to_vec<int>(v["bornlist"].GetString(), row.vecbornlist, tool::str_to_int);
		
		tool::split_str_to_vec<int>(v["bornnum"].GetString(), row.vecbornnum, tool::str_to_int);
		
		

		
			m_mapDotaEquipConfigByid[row.id] = &row;
		

		
			m_mapDotaEquipConfigByname[row.name] = &row;
		

		

		

		

		

		

		

	}
	
	return true;
}


bool DotaModule::LoadDotaHeroConfig(std::string basePath)
{
	std::string jsonPath = basePath + "DotaHeroConfig.json";
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
	m_vecDotaHeroConfig.resize(n);
	
	for (int i = 0; i < n; ++i)
	{
		// 逐行提取json元素
		rapidjson::Value &v = doc[i];
		
		DotaHeroConfig& row = m_vecDotaHeroConfig[i];

		row.id = v["id"].GetInt();
		
		row.name = v["name"].GetString();
		
		row.strength = v["strength"].GetDouble();
		
		row.agile = v["agile"].GetDouble();
		
		row.intelligense = v["intelligense"].GetDouble();
		
		

		
			m_mapDotaHeroConfigByid[row.id] = &row;
		

		
			m_mapDotaHeroConfigByname[row.name] = &row;
		

		

		

		

	}
	
	return true;
}


bool DotaModule::LoadDotaSkillConfig(std::string basePath)
{
	std::string jsonPath = basePath + "DotaSkillConfig.json";
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
	m_vecDotaSkillConfig.resize(n);
	
	for (int i = 0; i < n; ++i)
	{
		// 逐行提取json元素
		rapidjson::Value &v = doc[i];
		
		DotaSkillConfig& row = m_vecDotaSkillConfig[i];

		row.id = v["id"].GetInt();
		
		row.name = v["name"].GetString();
		
		row.strength = v["strength"].GetDouble();
		
		row.agile = v["agile"].GetDouble();
		
		row.intelligense = v["intelligense"].GetDouble();
		
		

		
			m_mapDotaSkillConfigByid[row.id] = &row;
		

		
			m_mapDotaSkillConfigByname[row.name] = &row;
		

		

		

		

	}
	
	return true;
}


bool DotaModule::LoadDotaNpcConfig(std::string basePath)
{
	std::string jsonPath = basePath + "DotaNpcConfig.json";
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
	m_vecDotaNpcConfig.resize(n);
	
	for (int i = 0; i < n; ++i)
	{
		// 逐行提取json元素
		rapidjson::Value &v = doc[i];
		
		DotaNpcConfig& row = m_vecDotaNpcConfig[i];

		row.id = v["id"].GetInt();
		
		row.name = v["name"].GetString();
		
		row.strength = v["strength"].GetDouble();
		
		row.agile = v["agile"].GetDouble();
		
		row.intelligense = v["intelligense"].GetDouble();
		
		

		
			m_mapDotaNpcConfigByid[row.id] = &row;
		

		
			m_mapDotaNpcConfigByname[row.name] = &row;
		

		

		

		

	}
	
	return true;
}



bool DotaModule::Load(std::string basePath)
{
	Clear();
		
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










