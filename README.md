tokit
=====

tokit是一个用于方便网游研发人员配置数据的工具。可以根据一份符合tokit格式的excel文件，生成对应的文件。

目前支持生成：

- [x] c++
- [x] c#
- [x] json

其中c++、c#文件中含有自动读取json数据的接口以及查找接口

如果你对生成的c++、c#、json文件不满意的话，你可以试着在已有的模板文件基础上修改，然后运行《一键生成.bat》看看效果，不需要重新编译

备注：
	模板文件放在tool文件夹下，目前有C#Template.cs、C++Template.cpp、C++Template.h、JsonTemplate.json
	
	这些文件的语法格式请搜索《golang模板语法》花5分钟学习一下，这些模板可以取到的数据请参考src\tokit\generator\excel_info.go

## 下载之后

下载tokit整个项目之后，双击运行《example\一键生成.bat》脚本。