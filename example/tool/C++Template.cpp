//------------------------------------------------------------
// 本文件由工具自动生成
//------------------------------------------------------------

#include "{{.ClassName}}.h"
#include <iostream>
#include "tokit_tool.h"

{{template "RegisterC++Type" .}}
{{define "RegisterC++Type"}}{{RegisterString "std::string"}}{{RegisterBool "bool"}}{{RegisterChar "char"}}{{RegisterInt16 "int16"}}{{RegisterInt32 "int"}}{{RegisterInt64 "int64"}}{{RegisterFloat "float"}}{{RegisterDouble "double"}}{{end}}

{{.ClassName}} {{.ClassName}}::instance;

{{template "DeclareFindFunc" .}}
{{template "DeclareClearFunc" .}}
{{template "DeclareLoadEachBinaryFunc" .}}
{{template "DeclareLoadAllBinaryFunc" .}}

{{define "DeclareFindFunc"}}
{{range .Sheets}}
{{$sheet:=.}}
{{range .Fields}}{{if .HasAttribute "唯一"}}
// {{.CnName}}
const {{$sheet.EnName}}* {{$.ClassName}}::Find{{$sheet.EnName}}By{{.EnName}}({{.GetFieldTypeName}} {{.EnName}})
{
	const auto itr = m_map{{$sheet.EnName}}By{{.EnName}}.find({{.EnName}});
	if (itr == m_map{{$sheet.EnName}}By{{.EnName}}.end())
	{
		return nullptr;
	}

	const {{$sheet.EnName}}* ret = itr->second;
	return ret;
}
{{else}}{{end}}{{end}}
{{end}}
{{end}}

{{define "DeclareClearFunc"}}
void {{$.ClassName}}::Clear()
{
{{range .Sheets}}
{{if .IsOnlyOneLine}}
	m_{{.EnName}}.Clear();
{{else}}
	m_vec{{.EnName}}.clear();
{{end}}
{{end}}

{{range .Sheets}}{{$sheet:= .}}{{range $i,$v:= .Fields}}{{if .HasAttribute "唯一"}}	m_map{{$sheet.EnName}}By{{.EnName}}.clear();
{{end}}{{end}}
{{end}}
}
{{end}}

{{define "GetConvertFieldFunc"}}{{if .IsString}}{{else if .IsBool}}tool::str_to_bool{{else if .IsChar}}tool::str_to_int{{else if .IsInt16}}tool::str_to_int{{else if .IsInt}}tool::str_to_int{{else if .IsInt64}}tool::str_to_int64{{else if .IsFloat}}tool::str_to_float{{else if .IsDouble}}tool::str_to_double{{else}}tool::str_to_int{{end}}{{end}}

{{define "DeclareLoadEachJsonFunc"}}
{{range .Sheets}}
{{$sheet:= .}}
bool {{$.ClassName}}::LoadJson{{.EnName}}(const std::string& basePath)
{
	std::string jsonPath = basePath + "{{.EnName}}.json";
	std::string jsonText;
	if (!tool::GetFileText(jsonPath.c_str(), jsonText))
	{
		std::cerr << "[error] parse failed, not found the file <" << jsonPath << ">!\n";
		return false;
	}
	
    rapidjson::Document doc;
    doc.Parse<0>(jsonText.c_str());
    if (doc.HasParseError()) {
        rapidjson::ParseErrorCode code = doc.GetParseError();
        std::cerr << "[error] parse <" << jsonPath << "> failed, error code = " << code << "\n";
        return false;
    }
	
	if (!doc.IsArray())
	{
		std::cerr << "[error] parse <" << jsonPath << "> failed, the rapidjson doc is not array, type = " << doc.GetType() << "\n";
		return false;
	}
	
	int n = doc.Size();
{{if .IsOnlyOneLine}}
	if (n <= 0)
	{
		std::cerr << "[error] parse <" << jsonPath << "> failed, the row count <= 0 is invalid!\n";
		return false;
	}
	
	n = 1;	
{{else}}
		m_vec{{.EnName}}.resize(n);
{{end}}	
	
	for (int i = 0; i < n; ++i)
	{
		// 逐行提取json元素
		rapidjson::Value &v = doc[i];
	{{if .IsOnlyOneLine}}
		{{.EnName}}& row = m_{{.EnName}};
	{{else}}
		{{.EnName}}& row = m_vec{{.EnName}}[i];
	{{end}}		
		
	{{range .Fields}}
	{{if .IsAttributeSpecifyValue "导出" "c++"}}
		{{if .HasAttribute "数组"}}{{$delim:= .GetAttributeValue "数组" " "}}{{if .IsString}}tool::split(v["{{.EnName}}"].GetString(), row.vec{{.EnName}}, "{{$delim}}");{{else}}tool::split_str_to_vec<{{.GetFieldTypeName}}>(v["{{.EnName}}"].GetString(), row.vec{{.EnName}}, {{template "GetConvertFieldFunc" .}}, "{{$delim}}");{{end}}
		{{else if .HasAttribute "集合"}}{{if .IsString}}tool::split_str_set(v["{{.EnName}}"].GetString(), row.set{{.EnName}});{{else}}tool::split_str_to_set<{{.GetFieldTypeName}}>(v["{{.EnName}}"].GetString(), row.set{{.EnName}}, {{template "GetConvertFieldFunc" .}});{{end}}
		{{else if .IsString}}row.{{.EnName}} = v["{{.EnName}}"].GetString();
		{{else if .IsBool}}row.{{.EnName}} = v["{{.EnName}}"].GetInt() > 0;
		{{else if .IsChar}}row.{{.EnName}} = (char)v["{{.EnName}}"].GetInt();
		{{else if .IsInt16}}row.{{.EnName}} = (int16)v["{{.EnName}}"].GetInt();
		{{else if .IsInt}}row.{{.EnName}} = v["{{.EnName}}"].GetInt();
		{{else if .IsInt64}}row.{{.EnName}} = v["{{.EnName}}"].GetInt();
		{{else if .IsFloat}}row.{{.EnName}} = (float)v["{{.EnName}}"].GetDouble();
		{{else if .IsDouble}}row.{{.EnName}} = v["{{.EnName}}"].GetDouble();
		{{end}}
	{{end}}
	{{end}}

	{{if ne .IsOnlyOneLine true}}
	{{range .Fields}}
		{{if .HasAttribute "唯一"}}m_map{{$sheet.EnName}}By{{.EnName}}[row.{{.EnName}}] = &row;{{end}}
	{{end}}
	{{end}}
	}
	
	return true;
}
{{end}}
{{end}}


{{define "DeclareLoadEachBinaryFunc"}}
{{range .Sheets}}
{{$sheet:= .}}
bool {{$.ClassName}}::LoadBinary{{.EnName}}(const std::string& basePath)
{
	std::string binaryPath = basePath + "{{.EnName}}.bin";
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
	
	{{if not .IsOnlyOneLine}}
	m_vec{{.EnName}}.resize(rowCount);
	{{end}}
	
	for (int peek = sizeof(int), rowIndex = 0; peek < size && rowIndex < rowCount; ++rowIndex)
	{
	{{if .IsOnlyOneLine}}
		{{.EnName}}& row = m_{{.EnName}};
	{{else}}
		{{.EnName}}& row = m_vec{{.EnName}}[rowIndex];
	{{end}}
		
		// 解析该行配置
	{{range .Fields}}
	{{if .IsAttributeSpecifyValue "导出" "c++"}}
		{{if .HasAttribute "数组"}}			
		
		int {{.EnName}}ArraySize = *((int*)(buffer + peek));
		peek += sizeof(int);
		
		if (!ConfigModule::IsArraySizeValid({{.EnName}}ArraySize))
		{
			std::cerr << "加载" << binaryPath << "二进制配置失败，原因是读取到{{.EnName}}数组长度不合法 = " << {{.EnName}}ArraySize;
			return false;
		}
		
		row.vec{{.EnName}}.resize({{.EnName}}ArraySize);
		
		for (int i = 0; i < {{.EnName}}ArraySize; ++i)
		{
			{{if .IsString}}
			if (!ConfigModule::ReadString(buffer, peek, row.vec{{.EnName}}[i]))
			{
				std::cerr << "加载" << binaryPath << "二进制配置失败，原因是{{.EnName}}数组中的字符串不合法 = " << peek;
				return false;
			}
			{{else if .IsBool}}row.vec{{.EnName}}[i] = (buffer[peek] != '\0');peek += sizeof(bool);
			{{else if .IsChar}}row.vec{{.EnName}}[i] = buffer[peek];peek += sizeof(char);
			{{else if .IsInt16}}row.vec{{.EnName}}[i] = *((int16*)(buffer + peek));peek += sizeof(int16);
			{{else if .IsInt}}row.vec{{.EnName}}[i] = *((int*)(buffer + peek));peek += sizeof(int);
			{{else if .IsInt64}}row.vec{{.EnName}}[i] = *((int64*)(buffer + peek));peek += sizeof(int64);
			{{else if .IsFloat}}row.vec{{.EnName}}[i] = *((float*)(buffer + peek));peek += sizeof(float);
			{{else if .IsDouble}}row.vec{{.EnName}}[i] = *((double*)(buffer + peek));peek += sizeof(double);
			{{end}}
		}				
		{{else if .IsString}}
		if (!ConfigModule::ReadString(buffer, peek, row.{{.EnName}}))
		{
			std::cerr << "加载" << binaryPath << "二进制配置失败，原因是{{.EnName}}字符串不合法 = " << peek;
			return false;
		}		
		{{else if .IsBool}}row.{{.EnName}} = (buffer[peek] != '\0');peek += sizeof(bool);
		{{else if .IsChar}}row.{{.EnName}} = buffer[peek];peek += sizeof(char);
		{{else if .IsInt16}}row.{{.EnName}} = *((int16*)(buffer + peek));peek += sizeof(int16);
		{{else if .IsInt}}row.{{.EnName}} = *((int*)(buffer + peek));peek += sizeof(int);
		{{else if .IsInt64}}row.{{.EnName}} = *((int64*)(buffer + peek));peek += sizeof(int64);
		{{else if .IsFloat}}row.{{.EnName}} = *((float*)(buffer + peek));peek += sizeof(float);
		{{else if .IsDouble}}row.{{.EnName}} = *((double*)(buffer + peek));peek += sizeof(double);
		{{end}}
	{{end}}
	{{end}}
	}
	
	{{if ne .IsOnlyOneLine true}}		
	for (int i = 0, size = (int)m_vec{{.EnName}}.size(); i < size; ++i)
	{
		{{.EnName}}& row = m_vec{{.EnName}}[i];
		{{range .Fields}}
		{{if .HasAttribute "唯一"}}m_map{{$sheet.EnName}}By{{.EnName}}[row.{{.EnName}}] = &row;{{end}}
		{{end}}
	}
	{{end}}
	return true;
}
{{end}}
{{end}}

{{define "DeclareLoadAllJsonFunc"}}
bool {{.ClassName}}::LoadJson(const std::string& basePath)
{
	Clear();
		
	{{range .Sheets}}if (!LoadJson{{.EnName}}(basePath))
	{
		return false;
	}
	
	{{end}}return true;
}
{{end}}

{{define "DeclareLoadAllBinaryFunc"}}
bool {{.ClassName}}::LoadBinary(const std::string& basePath)
{
	Clear();
		
	{{range .Sheets}}if (!LoadBinary{{.EnName}}(basePath))
	{
		return false;
	}
	
	{{end}}return true;
}
{{end}}