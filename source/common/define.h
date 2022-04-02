#ifndef __COMMON__DEFINE__H__
#define __COMMON__DEFINE__H__


/**
 *
 * 作者: hm
 *
 * 说明: 定义
 *
 */


#include "platform.h"


#ifdef DEBUG
#
#  define TOOLKIT_BUILD_TYPE "DEBUG"
#
#else
#
#  define TOOLKIT_BUILD_TYPE "RELEASE"
#
#endif


#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS
#
#  ifndef TOOLKIT_FILE
#  define TOOLKIT_FILE		__FILE__
#  endif
#
#  ifndef TOOLKIT_LINE
#  define TOOLKIT_LINE		__LINE__
#  endif
#
#  ifndef TOOLKIT_FUNC
#  define TOOLKIT_FUNC		__FUNCSIG__
#  endif
#
#else
#
#  ifndef TOOLKIT_FILE
#  define TOOLKIT_FILE		__FILE__
#  endif
#
#  ifndef TOOLKIT_LINE
#  define TOOLKIT_LINE		__LINE__
#  endif
#
#  ifndef TOOLKIT_FUNC
#  define TOOLKIT_FUNC		__PRETTY_FUNCTION__
#  endif
#
#endif


#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS
#
#  ifndef TOOLKIT_NAME_MAX
#  define TOOLKIT_NAME_MAX		_MAX_FNAME
#  endif
#
#  ifndef TOOLKIT_PATH_MAX
#  define TOOLKIT_PATH_MAX		_MAX_PATH
#  endif
#
#  ifndef TOOLKIT_PATH_SEP
#  define TOOLKIT_PATH_SEP		'\\'
#  endif
#
#  ifndef TOOLKIT_LINE_EOL
#  define TOOLKIT_LINE_EOL		"\r\n"
#  endif
#
#else
#
#  ifndef TOOLKIT_NAME_MAX
#  define TOOLKIT_NAME_MAX		256
#  endif
#
#  ifndef TOOLKIT_PATH_MAX
#  define TOOLKIT_PATH_MAX		4096
#  endif
#
#  ifndef TOOLKIT_PATH_SEP
#  define TOOLKIT_PATH_SEP		'/'
#  endif
#
#  ifndef TOOLKIT_LINE_EOL
#  define TOOLKIT_LINE_EOL		"\n"
#  endif
#
#endif


#endif // __COMMON__DEFINE__H__
