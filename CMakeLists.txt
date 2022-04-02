#
# cmake支持的最低版本
#
CMAKE_MINIMUM_REQUIRED(VERSION 3.0 FATAL_ERROR)


#
# 版本号
#
SET(LIBRARY_VERSION 0.0.1)


#
# 项目名
#
PROJECT(tinyToolkit VERSION ${LIBRARY_VERSION})


#
# 输出信息
#
MESSAGE(STATUS "Version: ${LIBRARY_VERSION}")
MESSAGE(STATUS "Install: ${CMAKE_INSTALL_PREFIX}")


#
# 设置模块目录
#
SET(CMAKE_MODULE_PATH	${CMAKE_CURRENT_LIST_DIR}/support/cmake/check
						${CMAKE_CURRENT_LIST_DIR}/support/cmake/traverse)


#
# 添加cmake模块
#
INCLUDE(TraverseSource)
INCLUDE(TraverseSubdirectory)


#
# 添加cmake模块
#
INCLUDE(CheckSystem)
INCLUDE(CheckPlatform)
INCLUDE(CheckCompiler)
INCLUDE(CheckBuildType)
INCLUDE(CheckGlobalType)


#
# 包含资源目录
#
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/source)


#
# 添加子目录
#
ADD_SUBDIRECTORY(source)
