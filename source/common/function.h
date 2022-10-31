#ifndef __COMMON__FUNCTION__H__
#define __COMMON__FUNCTION__H__


/**
 *
 * 作者: hm
 *
 * 说明: 函数
 *
 */


/**
 *
 * 未使用
 *
 */
#define TOOLKIT_UNUSED(val)		(void)val

/**
 *
 * 拼接
 *
 */
#define TOOLKIT_SPLICE(x, y)		TOOLKIT_DO_SPLICE(x, y)
#define TOOLKIT_DO_SPLICE(x, y)		x##y

/**
 *
 * 字符串化
 *
 */
#define TOOLKIT_STRINGIFY(x)		TOOLKIT_DO_STRINGIFY(x)
#define TOOLKIT_DO_STRINGIFY(x)		#x


#endif // __COMMON__FUNCTION__H__
