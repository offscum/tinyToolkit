#ifndef __TIME__TIME__H__
#define __TIME__TIME__H__


/**
 *
 * 作者: hm
 *
 * 说明: 时间信息
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"

#include <string>
#include <chrono>
#include <cstdint>


namespace tinyToolkit
{
	namespace time
	{
		/**
		 *
		 * 是否是闰年
		 *
		 * @param year 年份
		 *
		 * @return 是否是闰年
		 *
		 */
		TOOLKIT_API bool IsLeapYear(int32_t year);

		/**
		 *
		 * 小时时间戳
		 *
		 * @param point 时间点
		 *
		 * @return 小时时间戳
		 *
		 */
		TOOLKIT_API int64_t Hour(const std::chrono::system_clock::time_point & point = std::chrono::system_clock::now());

		/**
		 *
		 * 分钟时间戳
		 *
		 * @param point 时间点
		 *
		 * @return 分钟时间戳
		 *
		 */
		TOOLKIT_API int64_t Minute(const std::chrono::system_clock::time_point & point = std::chrono::system_clock::now());

		/**
		 *
		 * 秒数时间戳
		 *
		 * @param point 时间点
		 *
		 * @return 秒数时间戳
		 *
		 */
		TOOLKIT_API int64_t Second(const std::chrono::system_clock::time_point & point = std::chrono::system_clock::now());

		/**
		 *
		 * 时区
		 *
		 * @return 时区
		 *
		 */
		TOOLKIT_API int64_t Timezone();

		/**
		 *
		 * 到期时间戳
		 *
		 * @param day 天
		 * @param hour 时
		 * @param minute 分
		 * @param second 秒
		 *
		 * @return 到期时间戳(秒)
		 *
		 */
		TOOLKIT_API int64_t Expiration(int64_t day = 0, int32_t hour = 0, int32_t minute = 0, int32_t second = 0);

		/**
		 *
		 * 纳秒时间戳
		 *
		 * @param point 时间点
		 *
		 * @return 纳秒时间戳
		 *
		 */
		TOOLKIT_API int64_t Nanosecond(const std::chrono::system_clock::time_point & point = std::chrono::system_clock::now());

		/**
		 *
		 * 微秒时间戳
		 *
		 * @param point 时间点
		 *
		 * @return 微秒时间戳
		 *
		 */
		TOOLKIT_API int64_t Microsecond(const std::chrono::system_clock::time_point & point = std::chrono::system_clock::now());

		/**
		 *
		 * 毫秒时间戳
		 *
		 * @param point 时间点
		 *
		 * @return 毫秒时间戳
		 *
		 */
		TOOLKIT_API int64_t Millisecond(const std::chrono::system_clock::time_point & point = std::chrono::system_clock::now());

		/**
		 *
		 * 转换为秒数时间戳
		 *
		 * @param date 日期
		 * @param format 格式
		 *
		 * @return 秒数时间戳
		 *
		 */
		TOOLKIT_API int64_t FromDateTime(const char * date, const char * format = "%4d-%02d-%02d %02d:%02d:%02d");

		/**
		 *
		 * 转换为日期时间
		 *
		 * @param second 秒数时间戳
		 * @param timezone 时区
		 * @param format 格式
		 *
		 * @return 日期时间
		 *
		 */
		TOOLKIT_API std::string AsDateTime(int64_t second, int64_t timezone, const char * format = "%4d-%02d-%02d %02d:%02d:%02d");

		/**
		 *
		 * 当前UTC日期时间
		 *
		 * @param format 格式
		 *
		 * @return 日期时间
		 *
		 */
		TOOLKIT_API std::string CurrentUTCDateTime(const char * format = "%4d-%02d-%02d %02d:%02d:%02d");

		/**
		 *
		 * 当前本地日期时间
		 *
		 * @param format 格式
		 *
		 * @return 日期时间
		 *
		 */
		TOOLKIT_API std::string CurrentLocalDateTime(const char * format = "%4d-%02d-%02d %02d:%02d:%02d");

		/**
		 *
		 * 时间点
		 *
		 * @return 时间点
		 *
		 */
		TOOLKIT_API std::chrono::system_clock::time_point TimePoint();

		/**
		 *
		 * 时间点
		 *
		 * @param seconds 秒数时间戳
		 *
		 * @return 时间点
		 *
		 */
		TOOLKIT_API std::chrono::system_clock::time_point TimePoint(int64_t time);
	}
}


#endif // __TIME__TIME__H__
