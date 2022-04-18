#
# 项目名
#
SET(PROGRAM_NAME test_id)


#
# 设置可执行文件生成目录
#
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)


#
# 递归当前目录获取源文件
#
RECURSE_SOURCE_FILE(SOURCE_FILES)


#
# 链接源文件
#
ADD_EXECUTABLE(${PROGRAM_NAME} ${SOURCE_FILES})


#
# 链接库文件
#
IF(CMAKE_BUILD_TYPE STREQUAL Debug)

	TARGET_LINK_LIBRARIES(${PROGRAM_NAME} PUBLIC tinyToolkit_id_d tinyToolkit_test_d)

ELSE()

	TARGET_LINK_LIBRARIES(${PROGRAM_NAME} PUBLIC tinyToolkit_id tinyToolkit_test)

ENDIF()
