/**
 *
 * 作者: hm
 *
 * 说明: 系统信息
 *
 */


#include "system.h"

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS
#
#  include <Windows.h>
#
#else
#
#  include <pwd.h>
#  include <unistd.h>
#
#endif


namespace tinyToolkit
{
	namespace system
	{
		/**
		 *
		 * 内存页大小
		 *
		 * @return 内存页大小
		 *
		 */
		int32_t PageSize()
		{
		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			SYSTEM_INFO info{ 0 };

			::GetSystemInfo(&info);

			return static_cast<int32_t>(info.dwPageSize);

		#else

			#if defined(_SC_PAGESIZE)

				return static_cast<int32_t>(::sysconf(_SC_PAGESIZE));

			#elif defined(_SC_PAGE_SIZE)

				return static_cast<int32_t>(::sysconf(_SC_PAGE_SIZE));

			#else

				return -1;

			#endif

		#endif
		}

		/**
		 *
		 * 处理器个数
		 *
		 * @return 处理器个数
		 *
		 */
		int32_t ProcessorCount()
		{
		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			SYSTEM_INFO info{ 0 };

			::GetSystemInfo(&info);

			return static_cast<int32_t>(info.dwNumberOfProcessors);

		#else

			return static_cast<int32_t>(::sysconf(_SC_NPROCESSORS_CONF));

		#endif
		}

		/**
		 *
		 * 用户名
		 *
		 * @return 用户名
		 *
		 */
		std::string UserName()
		{
			char content[TOOLKIT_NAME_MAX + 1]{ 0 };

		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			DWORD size = TOOLKIT_NAME_MAX;

			if (::GetUserName(content, &size) == FALSE)
			{
				return std::string{ };
			}

		#else

			struct passwd pwd{ };
			struct passwd * result{ nullptr };

			::getpwuid_r(::getuid(), &pwd, content, TOOLKIT_NAME_MAX, &result);

			if (result == nullptr)
			{
				return std::string{ };
			}

		#endif

			return content;
		}

		/**
		 *
		 * 计算机名称
		 *
		 * @return 计算机名称
		 *
		 */
		std::string ComputerName()
		{
			char content[TOOLKIT_NAME_MAX + 1]{ 0 };

		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			DWORD size = TOOLKIT_NAME_MAX;

			if (::GetComputerName(content, &size) == FALSE)
			{
				return std::string{ };
			}

		#else

			if (::gethostname(content, TOOLKIT_NAME_MAX))
			{
				return std::string{ };
			}

		#endif

			return content;
		}
	}
}
