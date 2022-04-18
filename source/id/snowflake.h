#ifndef __ID__SNOWFLAKE__H__
#define __ID__SNOWFLAKE__H__


/**
 *
 * 作者: hm
 *
 * 说明: 分布式唯一标识码
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"

#include <cstdint>


namespace tinyToolkit
{
	namespace id
	{
		/**
		 *
		 * 无效位					时间戳						用户序号		设备序号			序列号
		 *	0 - 000 0000 0000 0000 0000 0000 0000 0000 0000 - 0000 0000 - 0000 0000 - 0000 0000 0000
		 *
		 */
		class TOOLKIT_API Snowflake
		{
			static const int32_t USER_ID_BITS = 8;
			static const int32_t DEVICE_ID_BITS = 8;
			static const int32_t SEQUENCE_ID_BITS = 12;

			static const int32_t USER_ID_MAX = ~(-1 * (1 << USER_ID_BITS));
			static const int32_t DEVICE_ID_MAX = ~(-1 * (1 << DEVICE_ID_BITS));
			static const int32_t SEQUENCE_ID_MAX = ~(-1 * (1 << SEQUENCE_ID_BITS));

			static const int32_t USER_ID_SHIFT = SEQUENCE_ID_BITS + DEVICE_ID_BITS;
			static const int32_t DEVICE_ID_SHIFT = SEQUENCE_ID_BITS;
			static const int32_t TIMESTAMP_ID_SHIFT = SEQUENCE_ID_BITS + DEVICE_ID_BITS + USER_ID_BITS;

		public:
			/**
			 *
			 * 构造函数
			 *
			 * @param user 用户序号
			 * @param device 设备序号
			 *
			 */
			Snowflake(int64_t user, int64_t device);

		public:
			/**
			 *
			 * 生成
			 *
			 * @return 唯一标识码
			 *
			 */
			uint64_t Generate();

		private:
			int64_t _user{ 0 };
			int64_t _device{ 0 };
			int64_t _sequence{ 0 };
			int64_t _baseTimestamp{ 0 };
			int64_t _lastTimestamp{ 0 };
		};
	}
}


#endif // __ID__SNOWFLAKE__H__
