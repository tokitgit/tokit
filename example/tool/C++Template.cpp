//------------------------------------------------------------------------------
// 本头文件由工具自动生成，请勿在本文件内做改动
// 日期：
//------------------------------------------------------------------------------

#include "{{.ClassName}}.h"
#include <iostream>
#include <rapidjson/document.h>	
#include "tokit_tool.h"

{{template "RegisterC++Type" .}}
{{define "RegisterC++Type"}}{{RegisterFieldTypeName 1 "std::string"}}{{RegisterFieldTypeName 2 "bool"}}{{RegisterFieldTypeName 3 "char"}}{{RegisterFieldTypeName 4 "int"}}{{RegisterFieldTypeName 5 "int"}}{{RegisterFieldTypeName 6 "long"}}{{RegisterFieldTypeName 7 "int"}}{{RegisterFieldTypeName 8 "int"}}{{RegisterFieldTypeName 9 "int"}}{{RegisterFieldTypeName 10 "int64_t"}}{{RegisterFieldTypeName 11 "float"}}{{RegisterFieldTypeName 12 "double"}}{{end}}

{{.ClassName}} {{.ClassName}}::instance;

{{template "DeclareFindFunc" .}}
{{template "DeclareClearFunc" .}}
{{template "DeclareLoadEachFunc" .}}
{{template "DeclareLoadAllFunc" .}}

{{define "DeclareFindFunc"}}
{{range .Sheets}}
{{$cfg:=.}}
{{range .Fields}}{{if .IsKey}}
// {{.CnName}}
const {{$cfg.EnName}}* {{$.ClassName}}::Find{{$cfg.EnName}}By{{.EnName}}({{.GetFieldTypeName}} {{.EnName}})
{
	const auto itr = m_map{{$cfg.EnName}}By{{.EnName}}.find({{.EnName}});
	if (itr == m_map{{$cfg.EnName}}By{{.EnName}}.end())
	{
		return nullptr;
	}

	const {{$cfg.EnName}}* ret = itr->second;
	return ret;
}
{{else}}{{end}}{{end}}
{{end}}
{{end}}

{{define "DeclareClearFunc"}}
void {{$.ClassName}}::Clear()
{
{{range .Sheets}}
	m_vec{{.EnName}}.clear();
{{end}}

{{range .Sheets}}{{$cfg:= .}}{{range $i,$v:= .Fields}}{{if .IsKey}}	m_map{{$cfg.EnName}}By{{.EnName}}.clear();
{{end}}{{end}}
{{end}}
}
{{end}}

{{define "GetConvertFieldFunc"}}{{if eq .FieldType 1}}{{else if eq .FieldType 2}}tool::str_to_bool{{else if eq .FieldType 3}}tool::str_to_int{{else if eq .FieldType 4}}tool::str_to_int{{else if eq .FieldType 5}}tool::str_to_int{{else if eq .FieldType 6}}tool::str_to_int64{{else if eq .FieldType 7}}tool::str_to_int{{else if eq .FieldType 8}}tool::str_to_int{{else if eq .FieldType 9}}tool::str_to_int{{else if eq .FieldType 10}}tool::str_to_int64{{else if eq .FieldType 11}}tool::str_to_float{{else if eq .FieldType 12}}tool::str_to_double{{end}}{{end}}

{{define "DeclareLoadEachFunc"}}
{{range .Sheets}}
{{$cfg:= .}}
bool {{$.ClassName}}::Load{{.EnName}}(std::string basePath)
{
	std::string jsonPath = basePath + "{{.EnName}}.json";
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
	m_vec{{.EnName}}.resize(n);
	
	for (int i = 0; i < n; ++i)
	{
		// 逐行提取json元素
		rapidjson::Value &v = doc[i];
		
		{{.EnName}}& row = m_vec{{.EnName}}[i];
{{range .Fields}}
		{{if .IsArray}}{{if eq .FieldType 1}}tool::split(v["{{.EnName}}"].GetString(), row.vec{{.EnName}});{{else}}tool::split_str_to_vec<{{.GetFieldTypeName}}>(v["{{.EnName}}"].GetString(), row.vec{{.EnName}}, {{template "GetConvertFieldFunc" .}});{{end}}
		{{else if .IsSet}}{{if eq .FieldType 1}}tool::split_str_set(v["{{.EnName}}"].GetString(), row.set{{.EnName}});{{else}}tool::split_str_to_set<{{.GetFieldTypeName}}>(v["{{.EnName}}"].GetString(), row.set{{.EnName}}, {{template "GetConvertFieldFunc" .}});{{end}}
		{{else if eq .FieldType 1}}row.{{.EnName}} = v["{{.EnName}}"].GetString();
		{{else if eq .FieldType 2}}row.{{.EnName}} = v["{{.EnName}}"].GetInt();
		{{else if eq .FieldType 3}}row.{{.EnName}} = v["{{.EnName}}"].GetInt();
		{{else if eq .FieldType 4}}row.{{.EnName}} = v["{{.EnName}}"].GetInt();
		{{else if eq .FieldType 5}}row.{{.EnName}} = v["{{.EnName}}"].GetInt();
		{{else if eq .FieldType 6}}row.{{.EnName}} = v["{{.EnName}}"].GetInt();
		{{else if eq .FieldType 7}}row.{{.EnName}} = v["{{.EnName}}"].GetInt();
		{{else if eq .FieldType 8}}row.{{.EnName}} = v["{{.EnName}}"].GetInt();
		{{else if eq .FieldType 9}}row.{{.EnName}} = v["{{.EnName}}"].GetInt();
		{{else if eq .FieldType 10}}row.{{.EnName}} = v["{{.EnName}}"].GetInt();
		{{else if eq .FieldType 11}}row.{{.EnName}} = (float)v["{{.EnName}}"].GetDouble();
		{{else if eq .FieldType 12}}row.{{.EnName}} = v["{{.EnName}}"].GetDouble();
		{{end}}{{end}}
		
{{range .Fields}}
		{{if .IsKey}}
			m_map{{$cfg.EnName}}By{{.EnName}}[row.{{.EnName}}] = &row;
		{{end}}
{{end}}
	}
	
	return true;
}
{{end}}
{{end}}

{{define "DeclareLoadAllFunc"}}
bool {{.ClassName}}::Load(std::string basePath)
{
	Clear();
		
	{{range .Sheets}}if (!Load{{.EnName}}(basePath))
	{
		return false;
	}
	
	{{end}}return true;
}
{{end}}