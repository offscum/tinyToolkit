#ifndef __TEST__UTIL__H__
#define __TEST__UTIL__H__


/**
 *
 * 作者: hm
 *
 * 说明: 实用函数
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"

#include <chrono>
#include <string>
#include <cstdint>


namespace tinyToolkit
{
	namespace test
	{
		/**
		 *
		 * 时间戳
		 *
		 * @return 时间戳
		 *
		 */
		TOOLKIT_API int64_t Timestamp();

		/**
		 *
		 * 耗时
		 *
		 * @param time 时间
		 *
		 * @return 耗时
		 *
		 */
		TOOLKIT_API std::string ElapsedTime(int64_t time);
	}
}


#endif // __TEST__UTIL__H__
