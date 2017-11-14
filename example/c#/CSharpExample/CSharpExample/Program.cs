using Newtonsoft.Json;
using System.IO;
using Config;
using System.Collections.Generic;

class Program
{
	public static void Test()
	{
		DotaModule.instance.Load(@"D:\proj\mine\tokit\example\json\");
	}

	static void Main(string[] args)
	{
		Test();
	}
}