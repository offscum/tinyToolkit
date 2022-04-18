#ifndef __SYSTEM__DISK__H__
#define __SYSTEM__DISK__H__


/**
 *
 * 作者: hm
 *
 * 说明: 磁盘信息
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
		 * 磁盘空间
		 *
		 * @param disk 磁盘
		 * @param total 总体大小
		 * @param free 空闲大小
		 *
		 * @return 是否获取成功
		 *
		 */
		TOOLKIT_API bool DiskSpace(const char * disk, int64_t * total, int64_t * free);

		/**
		 *
		 * 磁盘使用率
		 *
		 * @param disk 磁盘
		 *
		 * @return 磁盘使用率
		 *
		 */
		TOOLKIT_API double DiskUsage(const char * disk);

		/**
		 *
		 * 磁盘大小
		 *
		 * @param disk 磁盘
		 *
		 * @return 磁盘大小
		 *
		 */
		TOOLKIT_API int64_t DiskSize(const char * disk);

		/**
		 *
		 * 磁盘已用大小
		 *
		 * @param disk 磁盘
		 *
		 * @return 磁盘已用大小
		 *
		 */
		TOOLKIT_API int64_t DiskUsedSize(const char * disk);

		/**
		 *
		 * 磁盘空闲大小
		 *
		 * @param disk 磁盘
		 *
		 * @return 磁盘空闲大小
		 *
		 */
		TOOLKIT_API int64_t DiskFreeSize(const char * disk);
	}
}


#endif // __SYSTEM__DISK__H__
