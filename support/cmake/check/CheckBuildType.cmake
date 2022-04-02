#
# 检查编译模式
#
IF(NOT CMAKE_BUILD_TYPE)

	SET(CMAKE_BUILD_TYPE Release)

ENDIF()


#
# 设置宏定义
#
IF(CMAKE_BUILD_TYPE STREQUAL Debug)

	ADD_DEFINITIONS(-DDEBUG)
	ADD_DEFINITIONS(-D_DEBUG)

ELSE()

	ADD_DEFINITIONS(-DRELEASE)
	ADD_DEFINITIONS(-D_RELEASE)

ENDIF()


#
# 输出编译模式
#
MESSAGE(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
