#!/usr/bin/env bash


####################################################################################################


#
# 脚本路径
#
shellDirectory=$(cd "$(dirname "$0")" || exit; pwd)

#
# 编译路径
#
buildDirectory=$shellDirectory/cmake-build-linux

#
# 项目路径
#
projectDirectory=$shellDirectory/../../..

#
# 安装路径
#
installDirectory=/usr/local


####################################################################################################


#
# 输出信息
#
echo -e ""
echo -e "\033[1m\033[36m[linux] Start build project\033[0m"
echo -e ""


####################################################################################################


#
# 删除目录
#
rm -rf "$buildDirectory"

#
# 创建目录
#
mkdir -p "$buildDirectory"/Debug
mkdir -p "$buildDirectory"/Release

#
# 生成
#
cmake "$projectDirectory" -B "$buildDirectory"/Debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="$installDirectory"
cmake "$projectDirectory" -B "$buildDirectory"/Release -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$installDirectory"

#
# 编译
#
cmake --build "$buildDirectory"/Debug --config Debug
cmake --build "$buildDirectory"/Release --config Release

#
# 安装
#
cmake --install "$buildDirectory"/Debug --config Debug
cmake --install "$buildDirectory"/Release --config Release

#
# 删除目录
#
rm -rf "$buildDirectory"


####################################################################################################


#
# 输出信息
#
echo -e ""
echo -e "\033[1m\033[36m[linux] End build project\033[0m"
echo -e ""


####################################################################################################
