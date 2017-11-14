@echo off
rem 备注：excel_dir=excel文件的路径
set excel_dir=./excel/

rem 备注：tool=本工具的路径
set tool=.\tool\tokit.exe

rem 备注：gen_dir=生成的文件放在哪个文件夹
set gen_dir=./

rem 备注：template=模板文件的路径
set template=D:\proj\mine\tokit\example\tool

rem 这里解释一下windows下批处理的规则
rem 	备注：%~dp0 =当前盘符+路径，如: d:\xxx\xxx
rem
rem 同时，在批处理的for循环中，部分符号的含义如下
rem 	备注：%%s   =完全文件路径，  如: d:\abc.txt，其中的s可以是别的字母，如%%x
rem 	备注：%%~nxs=文件名带扩展，  如: abc.txt
rem 	备注：%%~ns =文件名不带扩展，如: abc

echo 1. 生成c#文件
    for /F %%x in ('dir /b /a-d /s "%excel_dir%\*.xlsx"') do (
        echo 正在处理[ %%x ]
        %tool% %%x ^
			-template %template%\C#Template.cs -out %gen_dir%\c#\CSharpExample\CSharpExample ^
			-template %template%\JsonTemplate.json -split-out %gen_dir%\json\ ^
			-template %template%\C++Template.cpp %template%\C++Template.h -out %gen_dir%\c++\c++_example\cfg
    )

pause