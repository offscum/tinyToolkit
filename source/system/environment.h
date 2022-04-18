#ifndef __SYSTEM__ENVIRONMENT__H__
#define __SYSTEM__ENVIRONMENT__H__


/**
 *
 * 作者: hm
 *
 * 说明: 环境变量
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"

#include <string>


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
		 * @return 是否设置成功
		 *
		 */
		TOOLKIT_API bool SetEnvironment(const char * field, const char * value);

		/**
		 *
		 * 获取环境变量
		 *
		 * @param field 字段
		 *
		 * @return 环境变量
		 *
		 */
		TOOLKIT_API std::string GetEnvironment(const char * field);
	}
}


#endif // __SYSTEM__ENVIRONMENT__H__
