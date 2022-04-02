#ifndef __COMMON__FUNCTION__H__
#define __COMMON__FUNCTION__H__


/**
 *
 * 作者: hm
 *
 * 说明: 函数
 *
 */


#define TOOLKIT_UNUSED(val)				(void)val

#define TOOLKIT_NAME_STRING(val)		#val
#define TOOLKIT_VALUE_STRING(val)		TOOLKIT_NAME_STRING(val)

#define TOOLKIT_VERSION_NUMBER(major, minor, patch) (((major) << 16) | ((minor) << 8) | (patch))


#endif // __COMMON__FUNCTION__H__
