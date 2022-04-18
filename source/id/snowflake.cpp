/**
 *
 * 作者: hm
 *
 * 说明: 分布式唯一标识码
 *
 */


#include "snowflake.h"

#include <chrono>
#include <string>
#include <stdexcept>


namespace tinyToolkit
{
	namespace id
	{
		const int32_t Snowflake::USER_ID_BITS;
		const int32_t Snowflake::DEVICE_ID_BITS;
		const int32_t Snowflake::SEQUENCE_ID_BITS;

		const int32_t Snowflake::USER_ID_MAX;
		const int32_t Snowflake::DEVICE_ID_MAX;
		const int32_t Snowflake::SEQUENCE_ID_MAX;

		const int32_t Snowflake::USER_ID_SHIFT;
		const int32_t Snowflake::DEVICE_ID_SHIFT;
		const int32_t Snowflake::TIMESTAMP_ID_SHIFT;

		/**
		 *
		 * 构造函数
		 *
		 * @param user 用户序号
		 * @param device 设备序号
		 *
		 */
		Snowflake::Snowflake(int64_t user, int64_t device) : _user(user),
															 _device(device)
		{
			_baseTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
			_lastTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();

			if (_user < 0 || _user > USER_ID_MAX)
			{
				throw std::runtime_error("user can't be greater than " + std::to_string(USER_ID_MAX) + " or less than 0");
			}

			if (_device < 0 || _device > DEVICE_ID_MAX)
			{
				throw std::runtime_error("device can't be greater than " + std::to_string(DEVICE_ID_MAX) + " or less than 0");
			}
		}

		/**
		 *
		 * 生成
		 *
		 * @return 唯一标识码
		 *
		 */
		uint64_t Snowflake::Generate()
		{
			int64_t timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();

			if (timestamp < _lastTimestamp)
			{
				throw std::runtime_error("Clock moved backwards, Refusing to generate id");
			}

			static auto NextMilliseconds = [](int64_t threshold) -> int64_t
			{
				int64_t milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();

				while (milliseconds <= threshold)
				{
					milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
				}

				return milliseconds;
			};

			if (_lastTimestamp == timestamp)
			{
				_sequence = (_sequence + 1) & SEQUENCE_ID_MAX;

				if (_sequence == 0)
				{
					timestamp = NextMilliseconds(_lastTimestamp);
				}
			}
			else
			{
				_sequence = 0;
			}

			_lastTimestamp = timestamp;

			return static_cast<uint64_t>(((_lastTimestamp - _baseTimestamp) << TIMESTAMP_ID_SHIFT) | (_user << USER_ID_SHIFT) | (_device << DEVICE_ID_SHIFT) | _sequence);
		}
	}
}
