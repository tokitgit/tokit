using Newtonsoft.Json;

public class JsonSetting
{
	public static Newtonsoft.Json.JsonSerializerSettings setting = new Newtonsoft.Json.JsonSerializerSettings();

	public static bool Init()
	{
		JsonConvert.DefaultSettings = new System.Func<JsonSerializerSettings>(() => 
		{
			//空值处理
			setting.NullValueHandling = NullValueHandling.Ignore;

			//高级用法九中的Bool类型转换 设置
			setting.Converters.Add(new BoolConverter());

			return setting;
		});

		return true;
	}

	public class BoolConverter : JsonConverter
	{
		public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
		{
			writer.WriteValue(((bool)value) ? 1 : 0);
		}

		public override object ReadJson(JsonReader reader, System.Type objectType, object existingValue, JsonSerializer serializer)
		{
			return reader.Value.ToString() == "1";
		}

		public override bool CanConvert(System.Type objectType)
		{
			return objectType == typeof(bool);
		}
	}
}
