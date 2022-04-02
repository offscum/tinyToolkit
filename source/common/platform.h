#ifndef __COMMON__PLATFORM__H__
#define __COMMON__PLATFORM__H__


/**
 *
 * 作者: hm
 *
 * 说明: 平台
 *
 */


#define TOOLKIT_PLATFORM_APPLE		1
#define TOOLKIT_PLATFORM_LINUX		2
#define TOOLKIT_PLATFORM_WINDOWS	3


#if defined( APPLE ) || defined( __APPLE ) || defined( __APPLE__ )
#
#  if defined(__LP64__) || defined(_LP64)
#
#    define TOOLKIT_PLATFORM_BYTE 64
#
#  else
#
#    define TOOLKIT_PLATFORM_BYTE 32
#
#  endif
#
#  define TOOLKIT_PLATFORM_TYPE TOOLKIT_PLATFORM_APPLE
#
#elif defined( __linux__ )
#
#  if defined(__LP64__) || defined(_LP64)
#
#    define TOOLKIT_PLATFORM_BYTE 64
#
#  else
#
#    define TOOLKIT_PLATFORM_BYTE 32
#
#  endif
#
#  define TOOLKIT_PLATFORM_TYPE TOOLKIT_PLATFORM_LINUX
#
#elif defined( WIN64 ) || defined( _WIN64 ) || defined( __WIN64 ) || defined( _WIN64_ ) || defined( __WIN64__ )
#
#  define TOOLKIT_PLATFORM_BYTE 64
#
#  define TOOLKIT_PLATFORM_TYPE TOOLKIT_PLATFORM_WINDOWS
#
#elif defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32 ) || defined( _WIN32_ ) || defined( __WIN32__ )
#
#  define TOOLKIT_PLATFORM_BYTE 32
#
#  define TOOLKIT_PLATFORM_TYPE TOOLKIT_PLATFORM_WINDOWS
#
#else
#
#  error "platform not supported"
#
#endif


#endif // __COMMON__PLATFORM__H__
