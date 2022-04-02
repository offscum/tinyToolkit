#
# 定义源文件分组
#
MACRO(DEFINE_SOURCE_GROUP)

	#
	# 遍历源文件
	#
	FOREACH(source ${ARGN})

		#
		# 获取相对路径
		#
		FILE(RELATIVE_PATH SOURCE_RELATIVE_PATH ${CMAKE_CURRENT_LIST_DIR} ${source})

		#
		# 获取组名
		#
		STRING(REGEX REPLACE "(.*)/.*" \\1 SOURCE_GROUP_NAME ${SOURCE_RELATIVE_PATH})

		#
		# 判断是否为根组名
		#
		STRING(COMPARE EQUAL ${SOURCE_RELATIVE_PATH} ${SOURCE_GROUP_NAME} IS_ROOT_SOURCE_GROUP)

		#
		# 设置根组名
		#
		IF(IS_ROOT_SOURCE_GROUP)

			SET(SOURCE_GROUP_NAME "/")

		ENDIF()

		#
		# 把文件添加到对应的组
		#
		SOURCE_GROUP(${SOURCE_GROUP_NAME} FILES ${source})

	ENDFOREACH()

ENDMACRO(DEFINE_SOURCE_GROUP)


####################################################################################################


#
# 递归当前目录获取源文件
#
MACRO(RECURSE_SOURCE_FILE)

	#
	# 检测参数个数
	#
	IF(NOT ${ARGC} EQUAL 1)

		MESSAGE(FATAL_ERROR "RECURSE_SOURCE_FILE <source_list>")

	ENDIF()

	#
	# 递归当前目录获取源文件
	#
	FILE(GLOB_RECURSE ${ARGV0}	"${CMAKE_CURRENT_LIST_DIR}/*.c"
								"${CMAKE_CURRENT_LIST_DIR}/*.cc"
								"${CMAKE_CURRENT_LIST_DIR}/*.cpp"
								"${CMAKE_CURRENT_LIST_DIR}/*.h"
								"${CMAKE_CURRENT_LIST_DIR}/*.hh"
								"${CMAKE_CURRENT_LIST_DIR}/*.hpp")

	#
	# 定义源文件分组
	#
	DEFINE_SOURCE_GROUP(${${ARGV0}})

ENDMACRO(RECURSE_SOURCE_FILE)


####################################################################################################


#
# 遍历当前目录获取源文件
#
MACRO(TRAVERSE_SOURCE_FILE)

	#
	# 检测参数个数
	#
	IF(NOT ${ARGC} EQUAL 1)

		MESSAGE(FATAL_ERROR "TRAVERSE_SOURCE_FILE <source_list>")

	ENDIF()

	#
	# 遍历当前目录获取源文件
	#
	FILE(GLOB ${ARGV0}	"${CMAKE_CURRENT_LIST_DIR}/*.c"
						"${CMAKE_CURRENT_LIST_DIR}/*.cc"
						"${CMAKE_CURRENT_LIST_DIR}/*.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/*.h"
						"${CMAKE_CURRENT_LIST_DIR}/*.hh"
						"${CMAKE_CURRENT_LIST_DIR}/*.hpp")

	#
	# 定义源文件分组
	#
	DEFINE_SOURCE_GROUP(${${ARGV0}})

ENDMACRO(TRAVERSE_SOURCE_FILE)