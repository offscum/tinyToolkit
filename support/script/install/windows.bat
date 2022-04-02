@echo off


::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


::
:: 管理员权限
::
%1 start "" mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe","/c ""%~s0"" :: ","","runas",1)(window.close) && exit


::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


::
:: 脚本路径
::
set "shellDirectory=%~dp0"

::
:: 编译路径
::
set "buildDirectory=%shellDirectory%\cmake-build-windows"

::
:: 项目路径
::
set "projectDirectory=%shellDirectory%\..\..\.."

::
:: 安装路径
::
if exist "%SystemDrive%\Program Files (x86)" (
	set "installDirectory=%SystemDrive%\Program Files (x86)"
) else (
	set "installDirectory=%SystemDrive%\Program Files"
)


::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


::
:: 输出信息
::
echo;
echo [windows] Start build project
echo;


::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


::
:: 删除目录
::
rd /s /q %buildDirectory% >nul 2>&1

::
:: 创建目录
::
mkdir %buildDirectory%\Debug
mkdir %buildDirectory%\Release

::
:: 生成
::
cmake %projectDirectory% -B %buildDirectory%\Debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="%installDirectory%\tinyToolkit"
cmake %projectDirectory% -B %buildDirectory%\Release -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="%installDirectory%\tinyToolkit"

::
:: 编译
::
cmake --build %buildDirectory%\Debug --config Debug
cmake --build %buildDirectory%\Release --config Release

::
:: 安装
::
cmake --install %buildDirectory%\Debug --config Debug
cmake --install %buildDirectory%\Release --config Release

::
:: 删除目录
::
rd /s /q %buildDirectory% >nul 2>&1


::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


::
:: 输出信息
::
echo;
echo [windows] End build project
echo;


::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


::
:: 暂停
::
pause


::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
