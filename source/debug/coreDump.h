#ifndef __DEBUG__CORE_DUMP__H__
#define __DEBUG__CORE_DUMP__H__


/**
 *
 * 作者: hm
 *
 * 说明: 核心转储
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"


namespace tinyToolkit
{
	namespace debug
	{
		/**
		 *
		 * 注册核心转储
		 *
		 */
		TOOLKIT_API void RegisterCoreDump();

		/**
		 *
		 * 注销核心转储
		 *
		 */
		TOOLKIT_API void UnregisterCoreDump();
	}
}


#endif // __DEBUG__CORE_DUMP__H__
