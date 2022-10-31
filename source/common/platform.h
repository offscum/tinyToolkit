#ifndef __COMMON__PLATFORM__H__
#define __COMMON__PLATFORM__H__


/**
 *
 * 作者: hm
 *
 * 说明: 平台
 *
 */


/**
 *
 * 平台类型
 *
 */
#define TOOLKIT_PLATFORM_APPLE		1
#define TOOLKIT_PLATFORM_LINUX		2
#define TOOLKIT_PLATFORM_WINDOWS	3

/**
 *
 * 平台识别
 *
 */
#if defined(APPLE) || defined(__APPLE) || defined(__APPLE__)
#
#  ifndef TOOLKIT_PLATFORM_TYPE
#  define TOOLKIT_PLATFORM_TYPE TOOLKIT_PLATFORM_APPLE
#  endif
#
#elif defined(linux) || defined(__linux) || defined(__linux__)
#
#  ifndef TOOLKIT_PLATFORM_TYPE
#  define TOOLKIT_PLATFORM_TYPE TOOLKIT_PLATFORM_LINUX
#  endif
#
#elif defined(WIN64) || defined(_WIN64) || defined(__WIN64) || defined(_WIN64_) || defined(__WIN64__)
#
#  ifndef TOOLKIT_PLATFORM_TYPE
#  define TOOLKIT_PLATFORM_TYPE TOOLKIT_PLATFORM_WINDOWS
#  endif
#
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(_WIN32_) || defined(__WIN32__)
#
#  ifndef TOOLKIT_PLATFORM_TYPE
#  define TOOLKIT_PLATFORM_TYPE TOOLKIT_PLATFORM_WINDOWS
#  endif
#
#else
#
#  error "platform not supported"
#
#endif

/**
 *
 * 位数识别
 *
 */
#if defined(_LP64) || defined(__LP64__) || defined(WIN64) || defined(_WIN64) || defined(__WIN64) || defined(_WIN64_) || defined(__WIN64__)
#
#  ifndef TOOLKIT_PLATFORM_BYTE
#  define TOOLKIT_PLATFORM_BYTE 64
#  endif
#
#else
#
#  ifndef TOOLKIT_PLATFORM_BYTE
#  define TOOLKIT_PLATFORM_BYTE 32
#  endif
#
#endif


#endif // __COMMON__PLATFORM__H__
