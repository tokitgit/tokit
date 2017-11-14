using System.Collections.Generic;
using Newtonsoft.Json;
using System.IO;
using UnityEngine;
using System;

{{template "RegisterCSharpType" .}}
{{range .Sheets}}{{template "DeclareClass" .}}{{end}}

public partial class {{.ClassName}}
{		
	public static {{.ClassName}} instance = new {{.ClassName}}();
	
	{{range .Sheets}}{{template "DeclareList" .}}{{end}}
	{{range .Sheets}}{{template "DeclareDictionary" .}}{{end}}
	{{range .Sheets}}{{template "DeclareFindFunc" .}}{{end}}
	{{range .Sheets}}{{template "DeclareLoadEachFunc" .}}{{end}}
	{{template "DeclareLoadAllFunc" .}}
}

{{define "RegisterCSharpType"}}{{RegisterFieldTypeName 1 "string"}}{{RegisterFieldTypeName 2 "bool"}}{{RegisterFieldTypeName 3 "char"}}{{RegisterFieldTypeName 4 "int"}}{{RegisterFieldTypeName 5 "int"}}{{RegisterFieldTypeName 6 "long"}}{{RegisterFieldTypeName 7 "int"}}{{RegisterFieldTypeName 8 "int"}}{{RegisterFieldTypeName 9 "int"}}{{RegisterFieldTypeName 10 "long"}}{{RegisterFieldTypeName 11 "float"}}{{RegisterFieldTypeName 12 "double"}}{{end}}

{{define "DeclareClass"}}
// {{.CnName}}
public partial class {{.EnName}}
{
{{range .Fields}}{{template "DeclareField" .}}{{end}} }
{{end}}

{{define "GetFieldName"}}{{if .IsArray}}m_list{{.EnName}}{{else if .IsSet}}m_set{{.EnName}}{{else}}{{.EnName}}{{end}}{{end}}
	
{{define "DeclareField"}}
{{if .IsProgram}}{{else}}	// {{.CnName}}
	public {{.GetFieldTypeName}} {{template "GetFieldName" .}};{{end}}
{{end}}

{{define "DeclareList"}}
	// {{.CnName}}
	public List<{{.EnName}}> m_list{{.EnName}} = new List<{{.EnName}}>();
{{end}}

{{define "DeclareDictionary"}}
{{range .Fields}}{{if .IsKey}}
	// {{.CnName}}
	public Dictionary<{{.GetFieldTypeName}}, {{$.EnName}}> m_map{{$.EnName}}By{{.EnName}} = new Dictionary<{{.GetFieldTypeName}}, {{$.EnName}}>();
	{{else}}{{end}}{{end}}
{{end}}

{{define "GetDictionaryTypeName"}}Dictionary<{{.GetFieldTypeName}}, {{$.EnName}}>{{end}}

{{define "DeclareFindFunc"}}
	{{range .Fields}}{{if .IsKey}}
	// {{.CnName}}
	public {{$.EnName}} Get{{$.EnName}}By{{.EnName}}({{.GetFieldTypeName}} {{.EnName}})
	{
		{{$.EnName}} ret;
		m_map{{$.EnName}}By{{.EnName}}.TryGetValue({{.EnName}}, out ret);
		return ret;
	}
	{{else}}{{end}}{{end}}
{{end}}

{{define "DeclareLoadEachFunc"}}
	// 加载单个文件
	public bool Load{{.EnName}}(string basePath)
	{
		string jsonPath = basePath + @"{{.EnName}}.json";
		string jsonText = File.ReadAllText(jsonPath, System.Text.Encoding.Default);
		
		try
		{
			m_list{{.EnName}} = (List<{{.EnName}}>)Newtonsoft.Json.JsonConvert.DeserializeObject(jsonText, typeof(List<{{.EnName}}>));
		}
		catch (Exception e)
		{
			Debug.Log("加载" + jsonPath + "配置失败，原因 = " + e.Message);
		}			

		for (int i = 0; i < m_list{{.EnName}}.Count; ++i)
		{
			{{.EnName}} row = m_list{{.EnName}}[i];
{{$tail:= Tail .Fields}}{{range $i,$v:= .Fields}}{{if .IsKey}}				m_map{{$.EnName}}By{{.EnName}}[row.{{.EnName}}] = row;{{if lt $i $tail}}
{{end}}{{end}}{{end}}		}
		
		return true;
	}
{{end}}

{{define "DeclareLoadAllFunc"}}
	// 加载配置
	public bool Load(string basePath)
	{
		{{range .Sheets}}if (!Load{{.EnName}}(basePath))
		{
			return false;
		}
		
		{{end}}return true;
	}
{{end}}