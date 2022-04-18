#ifndef __SYSTEM__MEMORY__H__
#define __SYSTEM__MEMORY__H__


/**
 *
 * 作者: hm
 *
 * 说明: 内存信息
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"

#include <cstdint>


namespace tinyToolkit
{
	namespace system
	{
		/**
		 *
		 * 内存空间
		 *
		 * @param total 总体大小
		 * @param free 空闲大小
		 *
		 * @return 是否获取成功
		 *
		 */
		TOOLKIT_API bool MemorySpace(int64_t * total, int64_t * free);

		/**
		 *
		 * 内存使用率
		 *
		 * @return 内存使用率
		 *
		 */
		TOOLKIT_API double MemoryUsage();

		/**
		 *
		 * 内存大小
		 *
		 * @return 内存大小
		 *
		 */
		TOOLKIT_API int64_t MemorySize();

		/**
		 *
		 * 内存已用大小
		 *
		 * @return 内存已用大小
		 *
		 */
		TOOLKIT_API int64_t MemoryUsedSize();

		/**
		 *
		 * 内存空闲大小
		 *
		 * @return 内存空闲大小
		 *
		 */
		TOOLKIT_API int64_t MemoryFreeSize();
	}
}


#endif // __SYSTEM__MEMORY__H__
