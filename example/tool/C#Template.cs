//------------------------------------------------------------
// 本文件由工具自动生成，请勿改动
//------------------------------------------------------------

using System.Collections.Generic;
using System.IO;
using System;

{{template "RegisterCSharpType" .}}
{{range .Sheets}}{{template "DeclareClass" .}}{{end}}

public partial class {{.ClassName}} : IConfigModule
{		
	public static {{.ClassName}} instance;
	
	// 初始化
	public override bool Init()
	{
		instance = this;
		return true;
	}
	
	{{range .Sheets}}{{template "DeclareList" .}}{{end}}
	{{range .Sheets}}{{template "DeclareDictionary" .}}{{end}}
	{{range .Sheets}}{{template "DeclareFindFunc" .}}{{end}}
	{{range .Sheets}}{{template "DeclareLoadBinaryByPointerFunction" .}}{{end}}
	{{template "DeclareLoadAllFunc" .}}
}

{{define "RegisterCSharpType"}}{{RegisterFieldTypeName 1 "string"}}{{RegisterFieldTypeName 2 "bool"}}{{RegisterFieldTypeName 3 "byte"}}{{RegisterFieldTypeName 4 "int"}}{{RegisterFieldTypeName 5 "int"}}{{RegisterFieldTypeName 6 "long"}}{{RegisterFieldTypeName 7 "int"}}{{RegisterFieldTypeName 8 "int"}}{{RegisterFieldTypeName 9 "int"}}{{RegisterFieldTypeName 10 "long"}}{{RegisterFieldTypeName 11 "float"}}{{RegisterFieldTypeName 12 "double"}}{{end}}

{{define "DeclareClass"}}
// {{.CnName}}
public partial class {{.EnName}}
{
{{range .Fields}}
{{if .IsProgram}}
	{{if .IsProgramByName "c#"}}
	// {{.CnName}}
	public {{.EnName}};
	{{end}}
{{else}}	
	{{if .HasAttribute "数组"}}
	// {{.CnName}}
	public List<{{.GetFieldTypeName}}> {{.EnName}};
	{{else if .IsAttributeSpecifyValue "导出" "c#"}}
	// {{.CnName}}
	public {{.GetFieldTypeName}} {{.EnName}};
	{{end}}
{{end}}
{{end}} 
}
{{end}}


{{define "DeclareList"}}
{{if .IsOnlyOneLine}}
	// {{.CnName}}
	public {{.EnName}} m_{{.EnName}};
{{else}}
	// {{.CnName}}
	public List<{{.EnName}}> m_list{{.EnName}} = new List<{{.EnName}}>();
{{end}}
{{end}}

{{define "DeclareDictionary"}}
{{range .Fields}}{{if .HasAttribute "唯一"}}
	// {{.CnName}}
	public Dictionary<{{.GetFieldTypeName}}, {{$.EnName}}> m_map{{$.EnName}}By{{.EnName}} = new Dictionary<{{.GetFieldTypeName}}, {{$.EnName}}>();
	{{else}}{{end}}{{end}}
{{end}}

{{define "GetDictionaryTypeName"}}Dictionary<{{.GetFieldTypeName}}, {{$.EnName}}>{{end}}

{{define "DeclareFindFunc"}}
	{{range .Fields}}{{if .HasAttribute "唯一"}}
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
	public bool Load{{.EnName}}Json(string basePath)
	{
		string jsonPath = basePath + @"{{.EnName}}.json";
		string jsonText = File.ReadAllText(jsonPath, System.Text.Encoding.GetEncoding("GB2312"));
		
		try
		{
			//m_list{{.EnName}} = (List<{{.EnName}}>)Newtonsoft.Json.JsonConvert.DeserializeObject(jsonText, typeof(List<{{.EnName}}>));
			
			JArray jsonArray = JArray.Parse(jsonText);

			for (int i = 0; i < jsonArray.Count; ++i)
			{
				JToken jsonRow = jsonArray[i];			
				
				{{.EnName}} row = new {{.EnName}}();
				
			{{range $i,$v:= .Fields}}
			{{if .IsAttributeSpecifyValue "导出" "c#"}}
				{{if .HasAttribute "数组"}}
				{{$delim:= .GetAttributeValue "数组" " "}}
				
				row.{{.EnName}} = new List<{{.GetFieldTypeName}}>();
				string str{{.EnName}} = jsonRow["{{.EnName}}"].ToString();
				
				string[] splitArray{{.EnName}} = str{{.EnName}}.Split('{{$delim}}');
				
				for (int splitIndex = 0; splitIndex < splitArray{{.EnName}}.Length; ++splitIndex)
				{
					string splitValue = splitArray{{.EnName}}[splitIndex];

					{{if .IsString}}row.{{.EnName}}.Add(splitValue);
					{{else if .IsChar}}row.{{.EnName}}.Add(Convert.ToChar(splitValue));
					{{else if .IsInt16}}row.{{.EnName}}.Add(Convert.ToInt16(splitValue));
					{{else if .IsInt}}row.{{.EnName}}.Add(Convert.ToInt32(splitValue));
					{{else if .IsInt64}}row.{{.EnName}}.Add(Convert.ToInt64(splitValue));
					{{else if .IsFloat}}row.{{.EnName}}.Add(Convert.ToSingle(splitValue));
					{{else if .IsDouble}}row.{{.EnName}}.Add(Convert.ToDouble(splitValue));
					{{end}}
				}
				
				{{else if .IsString}}row.{{.EnName}} = jsonRow["{{.EnName}}"].ToString();
				{{else if .IsChar}}row.{{.EnName}} = Convert.ToChar(jsonRow["{{.EnName}}"].ToString());
				{{else if .IsInt16}}row.{{.EnName}} = Convert.ToInt16(jsonRow["{{.EnName}}"].ToString());
				{{else if .IsInt}}row.{{.EnName}} = Convert.ToInt32(jsonRow["{{.EnName}}"].ToString());
				{{else if .IsInt64}}row.{{.EnName}} = Convert.ToInt64(jsonRow["{{.EnName}}"].ToString());
				{{else if .IsFloat}}row.{{.EnName}} = Convert.ToSingle(jsonRow["{{.EnName}}"].ToString());
				{{else if .IsDouble}}row.{{.EnName}} = Convert.ToDouble(jsonRow["{{.EnName}}"].ToString());
				{{end}}
			{{end}}
			{{end}}
			
				{{if .IsOnlyOneLine}}
				m_{{.EnName}} = row;
				{{else}}
				m_list{{.EnName}}.Add(row);
				{{end}}
			}

		{{if not .IsOnlyOneLine}}
			for (int i = 0; i < m_list{{.EnName}}.Count; ++i)
			{
				{{.EnName}} row = m_list{{.EnName}}[i];
				{{range $i,$v:= .Fields}}
				{{if .HasAttribute "唯一"}}m_map{{$.EnName}}By{{.EnName}}[row.{{.EnName}}] = row;{{end}}
				{{end}}
			}
		{{end}}			
		}
		catch (Exception e)
		{
			Console.WriteLine("加载" + jsonPath + "配置失败，原因 = " + e.Message);
		}			

		return true;
	}
{{end}}

{{define "DeclareLoadBinaryByReaderFunction"}}
	// 加载单个文件（通过BinaryReader）
	public bool Load{{.EnName}}BinaryByReader(string basePath)
	{
		string binaryPath = basePath + @"Binary/{{.EnName}}.bin";
		
		FileStream fileStream = null;
		BinaryReader binaryReader = null;
		
		try
		{
			fileStream = new FileStream(binaryPath, FileMode.Open);

			MemoryStream memoryStream = new MemoryStream();
			fileStream.CopyTo(memoryStream);
			fileStream.Close();
			memoryStream.Position = 0;

			binaryReader = new BinaryReader(memoryStream);

			while (memoryStream.Position < memoryStream.Length)  
			{
				{{.EnName}} row = new {{.EnName}}();
				
			{{range .Fields}}
			{{if .IsAttributeSpecifyValue "导出" "c#"}}
				{{if .HasAttribute "数组"}}			
				row.{{.EnName}} = new List<{{.GetFieldTypeName}}>();
				
				int {{.EnName}}ArraySize = binaryReader.ReadInt32();
				if (!ConfigModule.IsArraySizeValid({{.EnName}}ArraySize))
				{
					Console.WriteLine("加载" + binaryPath + "二进制配置失败，原因是读取到{{.EnName}}数组长度不合法 = " + {{.EnName}}ArraySize);
					return false;
				}
				
				for (int i = 0; i < {{.EnName}}ArraySize; ++i)
				{
					{{if .IsString}}row.{{.EnName}}.Add(ConfigModule.ReadString(binaryReader));
					{{else if .IsBool}}row.{{.EnName}}.Add(binaryReader.ReadByte() != 0);
					{{else if .IsChar}}row.{{.EnName}}.Add((char)binaryReader.ReadByte());
					{{else if .IsInt16}}row.{{.EnName}}.Add(binaryReader.ReadInt16());
					{{else if .IsInt}}row.{{.EnName}}.Add(binaryReader.ReadInt32());
					{{else if .IsInt64}}row.{{.EnName}}.Add(binaryReader.ReadInt64());
					{{else if .IsFloat}}row.{{.EnName}}.Add((float)binaryReader.ReadSingle());
					{{else if .IsDouble}}row.{{.EnName}}.Add(binaryReader.ReadDouble());
					{{end}}
				}				
				{{else if .IsString}}row.{{.EnName}} = ConfigModule.ReadString(binaryReader);
				{{else if .IsBool}}row.{{.EnName}} = (binaryReader.ReadByte() != 0);
				{{else if .IsChar}}row.{{.EnName}} = (char)binaryReader.ReadByte();
				{{else if .IsInt16}}row.{{.EnName}} = binaryReader.ReadInt16();
				{{else if .IsInt}}row.{{.EnName}} = binaryReader.ReadInt32();
				{{else if .IsInt64}}row.{{.EnName}} = binaryReader.ReadInt64();
				{{else if .IsFloat}}row.{{.EnName}} = (float)binaryReader.ReadSingle();
				{{else if .IsDouble}}row.{{.EnName}} = binaryReader.ReadDouble();
				{{end}}
			{{end}}
			{{end}}

			{{if .IsOnlyOneLine}}
				m_{{.EnName}} = row;
			{{else}}
				m_list{{.EnName}}.Add(row);
			{{end}}
			}
			
			memoryStream.Close();
			
			{{if not .IsOnlyOneLine}}
			for (int i = 0; i < m_list{{.EnName}}.Count; ++i)
			{
				{{.EnName}} row = m_list{{.EnName}}[i];
				{{range .Fields}}
				{{if .HasAttribute "唯一"}}m_map{{$.EnName}}By{{.EnName}}[row.{{.EnName}}] = row;{{end}}
				{{end}}
			}
			{{end}}
		}
		catch (EndOfStreamException e)
		{			
		}
		catch (Exception e)
		{
			Console.WriteLine("加载" + binaryPath + "二进制配置失败，原因 = " + e.Message);
		}			
		finally
		{
			if (binaryReader != null)
			{
				binaryReader.Close();
			}

			if (fileStream != null)
			{
				fileStream.Close();
			}
		}

		return true;
	}
{{end}}

{{define "DeclareLoadBinaryByPointerFunction"}}
	// 读取文件内容（声明了unsafe修饰符）
	public unsafe bool UnsafeLoad{{.EnName}}Binary(string binaryPath, Byte[] bytes)
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
			
			{{if not .IsOnlyOneLine}}
			m_list{{.EnName}}.Capacity = rowCount;
			{{end}}			
			
			for (int peek = sizeof(int); peek < bytes.Length;)
			{
				{{.EnName}} row = new {{.EnName}}();
				
				// 解析该行配置
			{{range .Fields}}
			{{if .IsAttributeSpecifyValue "导出" "c#"}}
				{{if .HasAttribute "数组"}}			
				row.{{.EnName}} = new List<{{.GetFieldTypeName}}>();
				
				int {{.EnName}}ArraySize = *((int*)(p + peek));peek += sizeof(int);
				if (!ConfigModule.IsArraySizeValid({{.EnName}}ArraySize))
				{
					Console.WriteLine("加载" + binaryPath + "二进制配置失败，原因是读取到{{.EnName}}数组长度不合法 = " + {{.EnName}}ArraySize);
					return false;
				}
				
				row.{{.EnName}}.Capacity = {{.EnName}}ArraySize;
				
				for (int i = 0; i < {{.EnName}}ArraySize; ++i)
				{
					{{if .IsString}}row.{{.EnName}}.Add(ConfigModule.ReadByteString(p, ref peek));
					{{else if .IsBool}}row.{{.EnName}}.Add(p[peek] != '\0');peek += sizeof(bool);
					{{else if .IsChar}}row.{{.EnName}}.Add((byte)p[peek]);peek += sizeof(byte);
					{{else if .IsInt16}}row.{{.EnName}}.Add(*((short*)(p + peek)));peek += sizeof(short);
					{{else if .IsInt}}row.{{.EnName}}.Add(*((int*)(p + peek)));peek += sizeof(int);
					{{else if .IsInt64}}row.{{.EnName}}.Add(*((long*)(p + peek)));peek += sizeof(long);
					{{else if .IsFloat}}row.{{.EnName}}.Add(*((float*)(p + peek)));peek += sizeof(float);
					{{else if .IsDouble}}row.{{.EnName}}.Add(*((double*)(p + peek)));peek += sizeof(double);
					{{end}}
				}
				{{else if .IsString}}row.{{.EnName}} = ConfigModule.ReadByteString(p, ref peek);
				{{else if .IsBool}}row.{{.EnName}} = (p[peek] != '\0');peek += sizeof(bool);
				{{else if .IsChar}}row.{{.EnName}} = (byte)p[peek];peek += sizeof(byte);
				{{else if .IsInt16}}row.{{.EnName}} = *((short*)(p + peek));peek += sizeof(short);
				{{else if .IsInt}}row.{{.EnName}} = *((int*)(p + peek));peek += sizeof(int);
				{{else if .IsInt64}}row.{{.EnName}} = *((long*)(p + peek));peek += sizeof(long);
				{{else if .IsFloat}}row.{{.EnName}} = *((float*)(p + peek));peek += sizeof(float);
				{{else if .IsDouble}}row.{{.EnName}} = *((double*)(p + peek));peek += sizeof(double);
				{{end}}
			{{end}}
			{{end}}
			
			{{if .IsOnlyOneLine}}
				m_{{.EnName}} = row;
			{{else}}
				m_list{{.EnName}}.Add(row);
			{{end}}
			}
		}
		
		{{if not .IsOnlyOneLine}}
		for (int i = 0; i < m_list{{.EnName}}.Count; ++i)
		{
			{{.EnName}} row = m_list{{.EnName}}[i];
			{{range .Fields}}
			{{if .HasAttribute "唯一"}}m_map{{$.EnName}}By{{.EnName}}[row.{{.EnName}}] = row;{{end}}
			{{end}}
		}
		{{end}}
		
		return true;
	}

	// 加载单个文件（通过原始指针方式）
	public bool Load{{.EnName}}BinaryByPointer(string basePath)
	{
		string binaryPath = basePath + @"Binary/{{.EnName}}.bin";

		try
		{
			FileStream fileStream = new FileStream(binaryPath, FileMode.Open);

			Byte[] bytes = new Byte[fileStream.Length];
			fileStream.Read(bytes, 0, (int)fileStream.Length);
			fileStream.Close();

			if (!UnsafeLoad{{.EnName}}Binary(binaryPath, bytes))
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
{{end}}

{{define "DeclareLoadAllFunc"}}
	// 加载配置
	public override bool Load(string configDirectory)
	{
		{{range .Sheets}}
		if (!Load{{.EnName}}BinaryByPointer(configDirectory))
		{
			return false;
		}
		{{end}}
		
		return true;
	}
{{end}}