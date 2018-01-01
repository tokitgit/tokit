@echo off
set excel_dir=excel
set copy_dir=无用文件
set tool=.\tool\tokit.exe
set template=.\tool

echo 1. 拷贝临时文件
	xcopy %excel_dir% %copy_dir% /D /Y

echo 2. 生成文件
    for /F %%x in ('dir /b /a-d /s "%copy_dir%\*.xlsx"') do (
        echo 正在处理[ %%x ]
        %tool% %%x ^
			-template %template%\JsonTemplate.json -split-out "json" ^
			-template %template%\C#BinaryTemplate.bin -split-out "c#\CSharpExample\binary" ^
			-template %template%\C#Template.cs -out "c#\CSharpExample" ^
			-template %template%\C++BinaryTemplate.bin -split-out "c++\c++_example\binary" ^
			-template %template%\C++Template.cpp %template%\C++Template.h -out "c++\c++_example"			
    )

echo.

pause
rem echo 生成结束！8秒后自动关闭！
rem @choice /t 8 /d y /n >nul