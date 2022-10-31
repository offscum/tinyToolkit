#ifndef __COMMON__VERSION__H__
#define __COMMON__VERSION__H__


/**
 *
 * 作者: hm
 *
 * 说明: 版本
 *
 */


#include "function.h"


/**
 *
 * 版本字段
 *
 */
#define TOOLKIT_VERSION_MAJOR		0
#define TOOLKIT_VERSION_MINOR		1
#define TOOLKIT_VERSION_PATCH		0

/**
 *
 * 版本号
 *
 */
#define TOOLKIT_VERSION_STRING		TOOLKIT_STRINGIFY(TOOLKIT_VERSION_MAJOR.TOOLKIT_VERSION_MINOR.TOOLKIT_VERSION_PATCH)


#endif // __COMMON__VERSION__H__
