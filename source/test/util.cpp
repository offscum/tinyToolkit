/**
 *
 * 作者: hm
 *
 * 说明: 实用函数
 *
 */


#include "util.h"


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
		int64_t Timestamp()
		{
			return static_cast<int64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
		}

		/**
		 *
		 * 耗时
		 *
		 * @param time 时间
		 *
		 * @return 耗时
		 *
		 */
		std::string ElapsedTime(int64_t time)
		{
			if (time < 1000)
			{
				return std::to_string(time) + " ns";
			}
			else if (time < 1000000)
			{
				return std::to_string(time / 1000) + " us";
			}
			else if (time < 1000000000)
			{
				return std::to_string(time / 1000000) + " ms";
			}
			else
			{
				return std::to_string(time / 1000000000) + " s";
			}
		}
	}
}
