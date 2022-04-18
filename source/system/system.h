#ifndef __SYSTEM__SYSTEM__H__
#define __SYSTEM__SYSTEM__H__


/**
 *
 * 作者: hm
 *
 * 说明: 系统信息
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"

#include <string>
#include <cstdint>


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
		TOOLKIT_API int32_t PageSize();

		/**
		 *
		 * 处理器个数
		 *
		 * @return 处理器个数
		 *
		 */
		TOOLKIT_API int32_t ProcessorCount();

		/**
		 *
		 * 用户名
		 *
		 * @return 用户名
		 *
		 */
		TOOLKIT_API std::string UserName();

		/**
		 *
		 * 计算机名称
		 *
		 * @return 计算机名称
		 *
		 */
		TOOLKIT_API std::string ComputerName();
	}
}


#endif // __SYSTEM__SYSTEM__H__
