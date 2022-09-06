/**
 *
 * 作者: hm
 *
 * 说明: 内存信息
 *
 */


#include "memory.h"

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS
#
#  include <Windows.h>
#
#elif TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_APPLE
#
#  include <unistd.h>
#
#  include <mach/mach_host.h>
#
#else
#
#  include <sys/sysinfo.h>
#
#endif


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
		bool MemorySpace(int64_t * total, int64_t * free)
		{
		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			MEMORYSTATUSEX memory{ 0 };

			memory.dwLength = sizeof(memory);

			if (::GlobalMemoryStatusEx(&memory) == FALSE)
			{
				return false;
			}

			if (total)
			{
				*total = static_cast<int64_t>(memory.ullTotalPhys);
			}

			if (free)
			{
				*free = static_cast<int64_t>(memory.ullAvailPhys);
			}

		#elif TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_APPLE

			#if defined(_SC_PAGESIZE)

				auto pagesize = ::sysconf(_SC_PAGESIZE);

			#elif defined(_SC_PAGE_SIZE)

				auto pagesize = ::sysconf(_SC_PAGE_SIZE);

			#endif

			if (pagesize == -1)
			{
				return false;
			}

			if (total)
			{
				auto pages = ::sysconf(_SC_PHYS_PAGES);

				if (pages == -1)
				{
					return false;
				}

				*total = static_cast<int64_t>(pages) * static_cast<int64_t>(pagesize);
			}

			if (free)
			{
			#if TOOLKIT_PLATFORM_BYTE == 32

				vm_statistics_data_t info{ };

				mach_msg_type_number_t count = HOST_VM_INFO_COUNT;

				if (::host_statistics(::mach_host_self(), HOST_VM_INFO, reinterpret_cast<host_info_t>(&info), &count) != KERN_SUCCESS)
				{
					return false;
				}

			#else

				mach_msg_type_number_t count = HOST_VM_INFO64_COUNT;

				vm_statistics64_data_t info{ };

				if (::host_statistics64(::mach_host_self(), HOST_VM_INFO64, reinterpret_cast<host_info64_t>(&info), &count) != KERN_SUCCESS)
				{
					return false;
				}

			#endif

				*free = static_cast<int64_t>(info.free_count) * static_cast<int64_t>(pagesize);
			}

		#else

			struct sysinfo si{ };

			if (::sysinfo(&si) == -1)
			{
				return false;
			}

			if (total)
			{
				*total = static_cast<int64_t>(si.totalram) * static_cast<int64_t>(si.mem_unit);
			}

			if (free)
			{
				*free = static_cast<int64_t>(si.freeram) * static_cast<int64_t>(si.mem_unit);
			}

		#endif

			return true;
		}

		/**
		 *
		 * 内存使用率
		 *
		 * @return 内存使用率
		 *
		 */
		double MemoryUsage()
		{
			int64_t free{ 0 };
			int64_t total{ 0 };

			if (MemorySpace(&total, &free))
			{
				return static_cast<double>(total - free) / static_cast<double>(total);
			}

			return -1.0;
		}

		/**
		 *
		 * 内存大小
		 *
		 * @return 内存大小
		 *
		 */
		int64_t MemorySize()
		{
			int64_t total{ 0 };

			if (MemorySpace(&total, nullptr))
			{
				return total;
			}

			return -1;
		}

		/**
		 *
		 * 内存使用大小
		 *
		 * @return 内存使用大小
		 *
		 */
		int64_t MemoryUsedSize()
		{
			int64_t free{ 0 };
			int64_t total{ 0 };

			if (MemorySpace(&total, &free))
			{
				return total - free;
			}

			return -1;
		}

		/**
		 *
		 * 内存空闲大小
		 *
		 * @return 内存空闲大小
		 *
		 */
		int64_t MemoryFreeSize()
		{
			int64_t free{ 0 };

			if (MemorySpace(nullptr, &free))
			{
				return free;
			}

			return -1;
		}
	}
}
