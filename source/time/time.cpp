/**
 *
 * 作者: hm
 *
 * 说明: 时间信息
 *
 */


#include "time.h"

#include <ctime>
#include <cstdio>
#include <stdexcept>


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
		bool IsLeapYear(int32_t year)
		{
			return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
		}

		/**
		 *
		 * 小时时间戳
		 *
		 * @param point 时间点
		 *
		 * @return 小时时间戳
		 *
		 */
		int64_t Hour(const std::chrono::system_clock::time_point & point)
		{
			return std::chrono::duration_cast<std::chrono::hours>(point.time_since_epoch()).count();
		}

		/**
		 *
		 * 分钟时间戳
		 *
		 * @param point 时间点
		 *
		 * @return 分钟时间戳
		 *
		 */
		int64_t Minute(const std::chrono::system_clock::time_point & point)
		{
			return std::chrono::duration_cast<std::chrono::minutes>(point.time_since_epoch()).count();
		}

		/**
		 *
		 * 秒数时间戳
		 *
		 * @param point 时间点
		 *
		 * @return 秒数时间戳
		 *
		 */
		int64_t Second(const std::chrono::system_clock::time_point & point)
		{
			return std::chrono::duration_cast<std::chrono::seconds>(point.time_since_epoch()).count();
		}

		/**
		 *
		 * 时区
		 *
		 * @return 时区
		 *
		 */
		int64_t Timezone()
		{
			std::tm utc{ };
			std::tm local{ };

			int64_t timestamp = 12 * 3600; /// 伦敦中午12点整, 全世界都在同一天

		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			::gmtime_s(&utc, reinterpret_cast<std::time_t *>(&timestamp));

			::localtime_s(&local, reinterpret_cast<std::time_t *>(&timestamp));

		#else

			::gmtime_r(reinterpret_cast<std::time_t *>(&timestamp), &utc);

			::localtime_r(reinterpret_cast<std::time_t *>(&timestamp), &local);

		#endif

			auto timezone = static_cast<int64_t>(local.tm_hour - utc.tm_hour);

			if (timezone < -12)
			{
				timezone += 24;
			}
			else if (timezone > 12)
			{
				timezone -= 24;
			}

			return timezone;
		}

		/**
		 *
		 * 到期时间戳
		 *
		 * @param day 天
		 * @param hour 时
		 * @param minute 分
		 * @param second 秒
		 *
		 * @return 到期时间戳
		 *
		 */
		int64_t Expiration(int64_t day, int32_t hour, int32_t minute, int32_t second)
		{
			if (hour < 0 || hour > 23)
			{
				throw std::range_error("Hour out of range [0 ~ 23]");
			}

			if (minute < 0 || minute > 59)
			{
				throw std::range_error("Minutes out of range [0 ~ 59]");
			}

			if (second < 0 || second > 59)
			{
				throw std::range_error("Seconds out of range [0 ~ 59]");
			}

			std::tm now{ };

			int64_t timestamp = Second();

		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			::localtime_s(&now, reinterpret_cast<std::time_t *>(&timestamp));

		#else

			::localtime_r(reinterpret_cast<std::time_t *>(&timestamp), &now);

		#endif

			now.tm_sec = second;
			now.tm_min = minute;
			now.tm_hour = hour;

			return std::mktime(&now) + (day * 86400);
		}

		/**
		 *
		 * 纳秒时间戳
		 *
		 * @param point 时间点
		 *
		 * @return 纳秒时间戳
		 *
		 */
		int64_t Nanosecond(const std::chrono::system_clock::time_point & point)
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>(point.time_since_epoch()).count();
		}

		/**
		 *
		 * 微秒时间戳
		 *
		 * @param point 时间点
		 *
		 * @return 微秒时间戳
		 *
		 */
		int64_t Microsecond(const std::chrono::system_clock::time_point & point)
		{
			return std::chrono::duration_cast<std::chrono::microseconds>(point.time_since_epoch()).count();
		}

		/**
		 *
		 * 毫秒时间戳
		 *
		 * @param point 时间点
		 *
		 * @return 毫秒时间戳
		 *
		 */
		int64_t Millisecond(const std::chrono::system_clock::time_point & point)
		{
			return std::chrono::duration_cast<std::chrono::milliseconds>(point.time_since_epoch()).count();
		}

		/**
		 *
		 * 转换为秒数时间戳
		 *
		 * @param date 日期时间
		 * @param format 格式
		 *
		 * @return 秒数时间戳
		 *
		 */
		int64_t FromDateTime(const char * date, const char * format)
		{
			if (date == nullptr || format == nullptr)
			{
				return 0;
			}

			std::tm now{ };

		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			::sscanf_s(date, format, &now.tm_year, &now.tm_mon, &now.tm_mday, &now.tm_hour, &now.tm_min, &now.tm_sec);

		#else

			::sscanf(date, format, &now.tm_year, &now.tm_mon, &now.tm_mday, &now.tm_hour, &now.tm_min, &now.tm_sec);

		#endif

			now.tm_year -= 1900;
			now.tm_mon -= 1;

			return std::mktime(&now);
		}

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
		std::string AsDateTime(int64_t second, int64_t timezone, const char * format)
		{
			if (format == nullptr)
			{
				return std::string{ };
			}

			std::tm now{ };

			int64_t timestamp = second + (timezone * 3600);

		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			::gmtime_s(&now, reinterpret_cast<std::time_t *>(&timestamp));

		#else

			::gmtime_r(reinterpret_cast<std::time_t *>(&timestamp), &now);

		#endif

			char content[TOOLKIT_NAME_MAX + 1]{ 0 };

			auto len = ::snprintf
			(
				content,
				TOOLKIT_NAME_MAX,
				format,
				now.tm_year + 1900,
				now.tm_mon + 1,
				now.tm_mday,
				now.tm_hour,
				now.tm_min,
				now.tm_sec
			);

			if (len < 0)
			{
				len = 0;
			}
			else if (len > TOOLKIT_NAME_MAX)
			{
				len = TOOLKIT_NAME_MAX;
			}

			content[len] = '\0';

			return content;
		}

		/**
		 *
		 * 当前UTC日期时间
		 *
		 * @param format 格式
		 *
		 * @return 日期时间
		 *
		 */
		std::string CurrentUTCDateTime(const char * format)
		{
			return AsDateTime(Second(), 0, format);
		}

		/**
		 *
		 * 当前本地日期时间
		 *
		 * @param format 格式
		 *
		 * @return 日期时间
		 *
		 */
		std::string CurrentLocalDateTime(const char * format)
		{
			return AsDateTime(Second(), Timezone(), format);
		}

		/**
		 *
		 * 时间点
		 *
		 * @return 时间点
		 *
		 */
		std::chrono::system_clock::time_point TimePoint()
		{
			return std::chrono::system_clock::now();
		}

		/**
		 *
		 * 时间点
		 *
		 * @param seconds 秒数时间戳
		 *
		 * @return 时间点
		 *
		 */
		std::chrono::system_clock::time_point TimePoint(int64_t time)
		{
			return std::chrono::time_point_cast<std::chrono::system_clock::duration>
			(
				std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>
				(
					std::chrono::seconds(time)
				)
			);
		}
	}
}
