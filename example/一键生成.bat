@echo off
set excel_dir=./excel/
set tool=tool
set gen_dir=./
set template=%tool%/template
set cur_dir=%~dp0

echo 0. 清除原有数据

rem del /Q /S *.h
rem del /Q /S *.cpp
rem del /Q /S *.xsd
del /Q /S %gen_dir%\*.xml
del /Q /S %gen_dir%\*.xlsx

rem %~dp0 =当前盘符+路径，如: d:\xxx\xxx
rem 同时，在批处理的for循环中
rem %%s   =完全文件路径，  如: d:\abc.txt，其中的s可以是别的字母，如%%x
rem %%~nxs=文件名带扩展，  如: abc.txt
rem %%~ns =文件名不带扩展，如: abc


echo 1. 生成c++文件
    for /F %%x in ('dir /b /a-d /s "%excel_dir%\*.xlsx"') do (
        echo 正在处理[ %%x ]
        %tool%\tokit.exe %%x -c++ %template%/c++_template.h %template%/c++_template.cpp %gen_dir%\c++\c++_example\cfg
    )

echo 2. 导出xml文件
    for /F %%x in ('dir /b /a-d /s "%excel_dir%\*.xlsx"') do ( 
        echo 正在导出[ %%~nx.xml ]
        %tool%\tokit.exe %%x -saveasxml %gen_dir%\xml
    )

echo 3. 导出xsd文件
    for /F %%x in ('dir /b /a-d /s "%excel_dir%\*.xlsx"') do ( 
        echo 正在导出[ %%~nx.xsd ]
        %tool%\tokit.exe %%x -xsd %gen_dir%\xsd
    )

echo 4. 一次性导出c++、xml、xsd文件
    for /F %%x in ('dir /b /a-d /s "%excel_dir%\*.xlsx"') do (
        echo 正在处理[ %%x ]
        %tool%\tokit.exe %%x -c++ %template%/c++_template.h %template%/c++_template.cpp %gen_dir%\c++\c++_example\cfg -saveasxml %gen_dir%\xml -xsd %gen_dir%\xsd
    )

pause