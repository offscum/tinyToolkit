/**
 *
 * 作者: hm
 *
 * 说明: 磁盘信息
 *
 */


#include "disk.h"

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS
#
#  include <Windows.h>
#
#elif TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_APPLE
#
#  include <sys/mount.h>
#
#else
#
#  include <sys/statfs.h>
#
#endif


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
		bool DiskSpace(const char * disk, int64_t * total, int64_t * free)
		{
		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			ULARGE_INTEGER freeBytes{ 0 };
			ULARGE_INTEGER totalBytes{ 0 };

			if (::GetDiskFreeSpaceEx(disk, nullptr, &totalBytes, &freeBytes) == FALSE)
			{
				return false;
			}

			if (total)
			{
				*total = static_cast<int64_t>(totalBytes.QuadPart);
			}

			if (free)
			{
				*free = static_cast<int64_t>(freeBytes.QuadPart);
			}

		#elif TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_APPLE

			struct statfs st{ };

			if (::statfs(disk, &st) == -1)
			{
				return false;
			}

			if (total)
			{
				*total = static_cast<int64_t>(st.f_blocks) * static_cast<int64_t>(st.f_bsize);
			}

			if (free)
			{
				*free = static_cast<int64_t>(st.f_bfree) * static_cast<int64_t>(st.f_bsize);
			}

		#else

			#if TOOLKIT_PLATFORM_BYTE == 32

				struct statfs st{ };

				if (::statfs(disk, &st) == -1)
				{
					return false;
				}

			#else

				struct statfs64 st{ };

				if (::statfs64(disk, &st) == -1)
				{
					return false;
				}

			#endif

			if (total)
			{
				*total = static_cast<int64_t>(st.f_blocks) * static_cast<int64_t>(st.f_bsize);
			}

			if (free)
			{
				*free = static_cast<int64_t>(st.f_bfree) * static_cast<int64_t>(st.f_bsize);
			}

		#endif

			return true;
		}

		/**
		 *
		 * 磁盘使用率
		 *
		 * @param disk 磁盘
		 *
		 * @return 磁盘使用率
		 *
		 */
		double DiskUsage(const char * disk)
		{
			if (disk == nullptr)
			{
				return -1.0;
			}

			int64_t free{ 0 };
			int64_t total{ 0 };

			if (DiskSpace(disk, &total, &free))
			{
				return static_cast<double>(total - free) / static_cast<double>(total);
			}

			return -1.0;
		}

		/**
		 *
		 * 磁盘大小
		 *
		 * @param disk 磁盘
		 *
		 * @return 磁盘大小
		 *
		 */
		int64_t DiskSize(const char * disk)
		{
			if (disk == nullptr)
			{
				return -1;
			}

			int64_t total{ 0 };

			if (DiskSpace(disk, &total, nullptr))
			{
				return total;
			}

			return -1;
		}

		/**
		 *
		 * 磁盘已用大小
		 *
		 * @param disk 磁盘
		 *
		 * @return 磁盘已用大小
		 *
		 */
		int64_t DiskUsedSize(const char * disk)
		{
			if (disk == nullptr)
			{
				return -1;
			}

			int64_t free{ 0 };
			int64_t total{ 0 };

			if (DiskSpace(disk, &total, &free))
			{
				return total - free;
			}

			return -1;
		}

		/**
		 *
		 * 磁盘空闲大小
		 *
		 * @param disk 磁盘
		 *
		 * @return 磁盘空闲大小
		 *
		 */
		int64_t DiskFreeSize(const char * disk)
		{
			if (disk == nullptr)
			{
				return -1;
			}

			int64_t free{ 0 };

			if (DiskSpace(disk, nullptr, &free))
			{
				return free;
			}

			return -1;
		}
	}
}
