//------------------------------------------------------------------------------
// 本文件由工具自动生成
//------------------------------------------------------------------------------

#pragma once

#include <string>
#include <map>
#include <vector>
#include <set>
#include "ConfigModule.h"

{{template "RegisterC++Type" .}}
{{define "RegisterC++Type"}}{{RegisterString "std::string"}}{{RegisterBool "bool"}}{{RegisterChar "char"}}{{RegisterInt16 "int16"}}{{RegisterInt32 "int"}}{{RegisterInt64 "int64"}}{{RegisterFloat "float"}}{{RegisterDouble "double"}}{{end}}

{{range .Sheets}}
{{template "DeclareStruct" .}}
{{end}}

{{define "GetFieldTypeName"}}{{if .HasAttribute "数组"}}std::vector<{{.GetFieldTypeName}}>{{else if .HasAttribute "集合"}}std::set<{{.GetFieldTypeName}}>{{else}}{{.GetFieldTypeName}}{{end}}{{end}}
{{define "GetFieldName"}}{{if .HasAttribute "数组"}}vec{{.EnName}}{{else if .HasAttribute "集合"}}set{{.EnName}}{{else}}{{.EnName}}{{end}}{{end}}

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
	{{if .IsAttributeSpecifyValue "导出" "c++"}}
		{{if .HasAttribute "数组"}}vec{{.EnName}}.clear();
		{{else if .HasAttribute "集合"}}set{{.EnName}}.clear();
		{{else if .IsString}}{{.EnName}} = "";
		{{else if .IsBool}}{{.EnName}} = false;
		{{else if .IsChar}}{{.EnName}} = 0;
		{{else if .IsInt16}}{{.EnName}} = 0;
		{{else if .IsInt}}{{.EnName}} = 0;
		{{else if .IsInt64}}{{.EnName}} = 0;
		{{else if .IsFloat}}{{.EnName}} = 0.0f;
		{{else if .IsDouble}}{{.EnName}} = 0.0f;
		{{end}}
	{{end}}
	{{end}}
	}
	
	{{range .Fields}}
	{{if .IsProgram}}
	{{if .IsProgramByName "c++"}}
	// {{.CnName}}
	{{template "GetFieldName" .}};
	{{end}}
	{{else if .IsAttributeSpecifyValue "导出" "c++"}}
	{{template "GetFieldTypeName" .}} {{template "GetFieldName" .}}; // {{.CnName}}{{if ne .AttributeText ""}}<{{.AttributeText}}>{{end}}
	{{end}}
{{end}}
};
{{end}}

{{define "DeclareLoadJsonFunc"}}
	// 载入json配置
	bool LoadJson(const std::string& basePath) override;
{{range .Sheets}}
{{$sheet:= .}}
	bool LoadJson{{.EnName}}(const std::string& basePath);
{{end}}
{{end}}

{{define "DeclareLoadBinaryFunc"}}
	// 载入二进制配置
	bool LoadBinary(const std::string& basePath) override;
{{range .Sheets}}
{{$sheet:= .}}
	bool LoadBinary{{.EnName}}(const std::string& basePath);
{{end}}
{{end}}

{{define "DeclareFindFunc"}}
{{range .Sheets}}
{{$sheet:=.}}
{{range .Fields}}{{if .HasAttribute "唯一"}}
	// {{.CnName}}
	const {{$sheet.EnName}}* Find{{$sheet.EnName}}By{{.EnName}}({{.GetFieldTypeName}} {{.EnName}});
{{end}}
{{end}}
{{end}}
{{end}}

{{define "DeclareFields"}}
{{range .Sheets}}
{{if .IsOnlyOneLine}}
	// {{.CnName}}
	{{.EnName}} m_{{.EnName}};
{{else}}
	// {{.CnName}}
	std::vector<{{.EnName}}> m_vec{{.EnName}};
{{end}}
{{end}}

{{range .Sheets}}
{{$sheet:=.}}
{{range .Fields}}
{{if .HasAttribute "唯一"}}
	// {{.CnName}}
	std::map<{{.GetFieldTypeName}}, {{$sheet.EnName}}*> m_map{{$sheet.EnName}}By{{.EnName}};
{{end}}
{{end}}
{{end}}
{{end}}

class {{.ClassName}} : public IConfigModule
{
public:
	static {{.ClassName}} instance;

public:
	// 获取本配置类名称
	const char* Name() override{ return "{{.ClassName}}"; }

public:
	{{template "DeclareLoadBinaryFunc" .}}	

    // 清空配置
    void Clear();
	
public:
	{{template "DeclareFindFunc" .}}
	
public:
	{{template "DeclareFields" .}}
};