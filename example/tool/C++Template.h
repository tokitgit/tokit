//------------------------------------------------------------------------------
// 本头文件由工具自动生成，请勿在本文件内做改动
// 日期：
//------------------------------------------------------------------------------

#pragma once

#include <string>
#include <map>
#include <vector>
#include <set>

{{template "RegisterC++Type" .}}
{{define "RegisterC++Type"}}{{RegisterFieldTypeName 1 "std::string"}}{{RegisterFieldTypeName 2 "bool"}}{{RegisterFieldTypeName 3 "char"}}{{RegisterFieldTypeName 4 "int"}}{{RegisterFieldTypeName 5 "int"}}{{RegisterFieldTypeName 6 "long"}}{{RegisterFieldTypeName 7 "int"}}{{RegisterFieldTypeName 8 "int"}}{{RegisterFieldTypeName 9 "int"}}{{RegisterFieldTypeName 10 "int64_t"}}{{RegisterFieldTypeName 11 "float"}}{{RegisterFieldTypeName 12 "double"}}{{end}}

{{range .Sheets}}
{{template "DeclareStruct" .}}
{{end}}

{{define "GetFieldTypeName"}}{{if .IsArray}}std::vector<{{.GetFieldTypeName}}>{{else if .IsSet}}std::set<{{.GetFieldTypeName}}>{{else}}{{.GetFieldTypeName}}{{end}}{{end}}
{{define "GetFieldName"}}{{if .IsArray}}vec{{.EnName}}{{else if .IsSet}}set{{.EnName}}{{else}}{{.EnName}}{{end}}{{end}}
{{define "GetAttrDescribe"}}{{if gt .FieldAttr 0}}<{{.GetFieldAttrDescribe}}>{{end}}{{end}}

{{define "DeclareStruct"}}
// {{.CnName}}
struct {{.EnName}}
{
	{{.EnName}}()
	{
		Clear();
	}
	
	inline void Clear()
	{
	{{range .Fields}}
		{{if .IsArray}}vec{{.EnName}}.clear();
		{{else if .IsSet}}set{{.EnName}}.clear();
		{{else if eq .FieldType 1}}{{.EnName}} = "";
		{{else if eq .FieldType 2}}{{.EnName}} = false;
		{{else if eq .FieldType 3}}{{.EnName}} = 0;
		{{else if eq .FieldType 4}}{{.EnName}} = 0;
		{{else if eq .FieldType 5}}{{.EnName}} = 0;
		{{else if eq .FieldType 6}}{{.EnName}} = 0;
		{{else if eq .FieldType 7}}{{.EnName}} = 0;
		{{else if eq .FieldType 8}}{{.EnName}} = 0;
		{{else if eq .FieldType 9}}{{.EnName}} = 0;
		{{else if eq .FieldType 10}}{{.EnName}} = 0;
		{{else if eq .FieldType 11}}{{.EnName}} = 0.0f;
		{{else if eq .FieldType 12}}{{.EnName}} = 0.0f;
		{{end}}
	{{end}}
	}
	
	{{range .Fields}}{{template "GetFieldTypeName" .}} {{template "GetFieldName" .}}; // {{.CnName}}{{template "GetAttrDescribe" .}}
	{{end}}
};
{{end}}

{{define "DeclareLoadFunc"}}
	// 载入配置
	bool Load(std::string basePath);
{{range .Sheets}}
{{$cfg:= .}}
	bool Load{{.EnName}}(std::string basePath);
{{end}}
{{end}}

{{define "DeclareFindFunc"}}
{{range .Sheets}}
{{$cfg:=.}}
{{range .Fields}}{{if .IsKey}}
	// {{.CnName}}
	const {{$cfg.EnName}}* Find{{$cfg.EnName}}By{{.EnName}}({{.GetFieldTypeName}} {{.EnName}});
{{else}}{{end}}{{end}}
{{end}}
{{end}}

{{define "DeclareFields"}}
{{range .Sheets}}
	// {{.CnName}}
	std::vector<{{.EnName}}> m_vec{{.EnName}};
{{end}}
{{range .Sheets}}
{{$cfg:=.}}
{{range .Fields}}{{if .IsKey}}
	// {{.CnName}}
	std::map<{{.GetFieldTypeName}}, {{$cfg.EnName}}*> m_map{{$cfg.EnName}}By{{.EnName}};
{{else}}{{end}}{{end}}
{{end}}
{{end}}

class {{.ClassName}}
{
public:
	static {{.ClassName}} instance;

public:
	// 获取本配置类名称
	const char* Name(){ return "{{.ClassName}}"; }

public:
	{{template "DeclareLoadFunc" .}}

    // 清空配置
    void Clear();
	
public:
	{{template "DeclareFindFunc" .}}
	
public:
	{{template "DeclareFields" .}}
};