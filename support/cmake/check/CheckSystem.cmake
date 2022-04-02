#
# 检测系统
#
IF(MINGW)

	MESSAGE(FATAL_ERROR "Detected Mingw System, Not Support")

ELSEIF(WIN32)

	MESSAGE(STATUS "Detected Windows System")

ELSEIF(APPLE)

	MESSAGE(STATUS "Detected Apple System")

ELSEIF(ANDROID)

	MESSAGE(FATAL_ERROR "Detected Android System, Not Support")

ELSEIF(UNIX)

	MESSAGE(STATUS "Detected Unix System")

ELSE()

	MESSAGE(FATAL_ERROR "Detected Unknown System, Not Support")

ENDIF()