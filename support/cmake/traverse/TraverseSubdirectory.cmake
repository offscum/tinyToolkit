#
# 循环添加子目录
#
MACRO(FOREACH_ADD_SUBDIRECTORY)

	#
	# 遍历文件
	#
	FOREACH(path ${ARGN})

		#
		# 判断是否存在配置文件
		#
		IF(EXISTS ${path}/CMakeLists.txt)

			#
			# 获取相对路径
			#
			FILE(RELATIVE_PATH SUB_RELATIVE_PATH ${CMAKE_CURRENT_LIST_DIR} ${path})

			#
			# 添加子目录
			#
			ADD_SUBDIRECTORY(${SUB_RELATIVE_PATH})

		ENDIF()

	ENDFOREACH()

ENDMACRO(FOREACH_ADD_SUBDIRECTORY)


####################################################################################################


#
# 递归当前目录添加子目录
#
MACRO(RECURSE_ADD_SUBDIRECTORY)

	#
	# 检测参数个数
	#
	IF(NOT ${ARGC} EQUAL 0)

		MESSAGE(FATAL_ERROR "RECURSE_ADD_SUBDIRECTORY")

	ENDIF()

	#
	# 递归当前目录获取内容
	#
	FILE(GLOB_RECURSE SUB_PATHS "${CMAKE_CURRENT_LIST_DIR}/*")

	#
	# 循环添加子目录
	#
	FOREACH_ADD_SUBDIRECTORY(${SUB_PATHS})

ENDMACRO(RECURSE_ADD_SUBDIRECTORY)


####################################################################################################


#
# 遍历当前目录添加子目录
#
MACRO(TRAVERSE_ADD_SUBDIRECTORY)

	#
	# 检测参数个数
	#
	IF(NOT ${ARGC} EQUAL 0)

		MESSAGE(FATAL_ERROR "TRAVERSE_CURRENT_DIRECTORY_ADD_SUBDIRECTORY")

	ENDIF()

	#
	# 遍历当前目录获取内容
	#
	FILE(GLOB SUB_PATHS "${CMAKE_CURRENT_LIST_DIR}/*")

	#
	# 循环添加子目录
	#
	FOREACH_ADD_SUBDIRECTORY(${SUB_PATHS})

ENDMACRO(TRAVERSE_ADD_SUBDIRECTORY)
