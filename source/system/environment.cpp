/**
 *
 * 作者: hm
 *
 * 说明: 环境变量
 *
 */


#include "environment.h"

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS
#
#  include <Windows.h>
#
#endif


namespace tinyToolkit
{
	namespace system
	{
		/**
		 *
		 * 设置环境变量
		 *
		 * @param field 字段
		 * @param value 数值
		 *
		 * @return 环境变量
		 *
		 */
		bool SetEnvironment(const char * field, const char * value)
		{
			if (field == nullptr || value == nullptr)
			{
				return false;
			}

		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			return ::SetEnvironmentVariable(field, value) == TRUE;

		#else

			return ::setenv(field, value, 1) == 0;

		#endif
		}

		/**
		 *
		 * 获取环境变量
		 *
		 * @param field 字段
		 *
		 * @return 环境变量
		 *
		 */
		std::string GetEnvironment(const char * field)
		{
			if (field == nullptr)
			{
				return std::string{ };
			}

		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			char result[256]{ 0 };

			if (::GetEnvironmentVariable(field, result, static_cast<DWORD>(sizeof(result))) == 0)
			{
				return std::string{ };
			}

			return result;

		#else

			char * result = ::getenv(field);

			return result ? result : std::string{ };

		#endif
		}
	}
}
