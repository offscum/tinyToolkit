/**
 *
 * 作者: hm
 *
 * 说明: 时间信息
 *
 */


#include "time.h"


TOOLKIT_TEST_CASE(Time, IsLeapYear)
{
	TOOLKIT_EXPECT_TRUE(tinyToolkit::time::IsLeapYear(1960));
	TOOLKIT_EXPECT_TRUE(tinyToolkit::time::IsLeapYear(2000));
	TOOLKIT_EXPECT_TRUE(tinyToolkit::time::IsLeapYear(2020));

	TOOLKIT_EXPECT_FALSE(tinyToolkit::time::IsLeapYear(1900));
	TOOLKIT_EXPECT_FALSE(tinyToolkit::time::IsLeapYear(2019));
	TOOLKIT_EXPECT_FALSE(tinyToolkit::time::IsLeapYear(2021));
	TOOLKIT_EXPECT_FALSE(tinyToolkit::time::IsLeapYear(2100));
	TOOLKIT_EXPECT_FALSE(tinyToolkit::time::IsLeapYear(3000));
}

TOOLKIT_TEST_CASE(Time, Hour)
{
	auto timePoint = tinyToolkit::time::TimePoint(3600);

	TOOLKIT_EXPECT_GE(tinyToolkit::time::Hour(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Hour(timePoint), 1);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Hour(timePoint), tinyToolkit::time::Minute(timePoint) / 60);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Hour(timePoint), tinyToolkit::time::Second(timePoint) / 3600);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Hour(timePoint), tinyToolkit::time::Millisecond(timePoint) / 3600000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Hour(timePoint), tinyToolkit::time::Microsecond(timePoint) / 3600000000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Hour(timePoint), tinyToolkit::time::Nanosecond(timePoint) / 3600000000000);
}

TOOLKIT_TEST_CASE(Time, Minute)
{
	auto timePoint = tinyToolkit::time::TimePoint(3600);

	TOOLKIT_EXPECT_GE(tinyToolkit::time::Minute(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Minute(timePoint), 60);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Minute(timePoint), tinyToolkit::time::Hour(timePoint) * 60);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Minute(timePoint), tinyToolkit::time::Second(timePoint) / 60);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Minute(timePoint), tinyToolkit::time::Millisecond(timePoint) / 60000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Minute(timePoint), tinyToolkit::time::Microsecond(timePoint) / 60000000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Minute(timePoint), tinyToolkit::time::Nanosecond(timePoint) / 60000000000);
}

TOOLKIT_TEST_CASE(Time, Second)
{
	auto timePoint = tinyToolkit::time::TimePoint(3600);

	TOOLKIT_EXPECT_GE(tinyToolkit::time::Second(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Second(timePoint), 3600);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Second(timePoint), tinyToolkit::time::Hour(timePoint) * 3600);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Second(timePoint), tinyToolkit::time::Minute(timePoint) * 60);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Second(timePoint), tinyToolkit::time::Millisecond(timePoint) / 1000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Second(timePoint), tinyToolkit::time::Microsecond(timePoint) / 1000000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Second(timePoint), tinyToolkit::time::Nanosecond(timePoint) / 1000000000);
}

TOOLKIT_TEST_CASE(Time, Timezone)
{
	auto zone = tinyToolkit::time::Timezone();

	TOOLKIT_EXPECT_GE(zone, 0);
	TOOLKIT_EXPECT_LE(zone, 24);
}

TOOLKIT_TEST_CASE(Time, Expiration)
{
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Expiration(2, 0, 0, 0), tinyToolkit::time::Expiration(1, 0, 0, 0) + 86400);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Expiration(-1, 0, 0, 0), tinyToolkit::time::Expiration(-2, 0, 0, 0) + 86400);

	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Expiration(2, 8, 0, 0), tinyToolkit::time::Expiration(1, 0, 0, 0) + 86400 + 28800);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Expiration(-1, 8, 4, 0), tinyToolkit::time::Expiration(-2, 0, 0, 0) + 86400 + 28800 + 240);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Expiration(-1, 8, 4, 2), tinyToolkit::time::Expiration(-2, 0, 0, 0) + 86400 + 28800 + 240 + 2);

	auto second = tinyToolkit::time::Second();

	TOOLKIT_EXPECT_GE(tinyToolkit::time::Expiration(11, 0, 0, 0), second + static_cast<int64_t>(10 * 24 * 60 * 60));
	TOOLKIT_EXPECT_LE(tinyToolkit::time::Expiration(11, 0, 0, 0), second + static_cast<int64_t>(11 * 24 * 60 * 60));

	TOOLKIT_EXPECT_GE(tinyToolkit::time::Expiration(-2, 0, 0, 0), second - static_cast<int64_t>(3 * 24 * 60 * 60));
	TOOLKIT_EXPECT_LE(tinyToolkit::time::Expiration(-2, 0, 0, 0), second - static_cast<int64_t>(2 * 24 * 60 * 60));
}

TOOLKIT_TEST_CASE(Time, Nanosecond)
{
	auto timePoint = tinyToolkit::time::TimePoint(3600);

	TOOLKIT_EXPECT_GE(tinyToolkit::time::Nanosecond(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Nanosecond(timePoint), 3600000000000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Nanosecond(timePoint), tinyToolkit::time::Hour(timePoint) * 3600000000000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Nanosecond(timePoint), tinyToolkit::time::Minute(timePoint) * 60000000000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Nanosecond(timePoint), tinyToolkit::time::Second(timePoint) * 1000000000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Nanosecond(timePoint), tinyToolkit::time::Millisecond(timePoint) * 1000000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Nanosecond(timePoint), tinyToolkit::time::Microsecond(timePoint) * 1000);
}

TOOLKIT_TEST_CASE(Time, Microsecond)
{
	auto timePoint = tinyToolkit::time::TimePoint(3600);

	TOOLKIT_EXPECT_GE(tinyToolkit::time::Microsecond(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Microsecond(timePoint), 3600000000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Microsecond(timePoint), tinyToolkit::time::Hour(timePoint) * 3600000000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Microsecond(timePoint), tinyToolkit::time::Minute(timePoint) * 60000000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Microsecond(timePoint), tinyToolkit::time::Second(timePoint) * 1000000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Microsecond(timePoint), tinyToolkit::time::Millisecond(timePoint) * 1000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Microsecond(timePoint), tinyToolkit::time::Nanosecond(timePoint) / 1000);
}

TOOLKIT_TEST_CASE(Time, Millisecond)
{
	auto timePoint = tinyToolkit::time::TimePoint(3600);

	TOOLKIT_EXPECT_GE(tinyToolkit::time::Millisecond(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Millisecond(timePoint), 3600000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Millisecond(timePoint), tinyToolkit::time::Hour(timePoint) * 3600000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Millisecond(timePoint), tinyToolkit::time::Minute(timePoint) * 60000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Millisecond(timePoint), tinyToolkit::time::Second(timePoint) * 1000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Millisecond(timePoint), tinyToolkit::time::Microsecond(timePoint) / 1000);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::Millisecond(timePoint), tinyToolkit::time::Nanosecond(timePoint) / 1000000);
}

TOOLKIT_TEST_CASE(Time, FromDateTime)
{
	int64_t interval = tinyToolkit::time::Timezone() * 60 * 60;

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("1970-01-01 00:00:00"), interval == 0 ? 0 : -1);

#else

	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("1970-01-01 00:00:00"), -interval);

#endif

	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("1970-01-01 08:00:00"), 28800 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2020-02-28 00:00:00"), 1582848000 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2020-02-28 08:00:00"), 1582876800 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2020-02-29 00:00:00"), 1582934400 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2020-02-29 08:00:00"), 1582963200 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2020-03-01 00:00:00"), 1583020800 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2020-03-01 08:00:00"), 1583049600 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2021-02-28 00:00:00"), 1614470400 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2021-02-28 08:00:00"), 1614499200 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2021-02-29 00:00:00"), 1614556800 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2021-02-29 08:00:00"), 1614585600 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2021-03-01 00:00:00"), 1614556800 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2021-03-01 08:00:00"), 1614585600 - interval);

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("1970_01_01_00_00_00", "%4d_%02d_%02d_%02d_%02d_%02d"), interval == 0 ? 0 : -1);

#else

	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("1970_01_01_00_00_00", "%4d_%02d_%02d_%02d_%02d_%02d"), 0 - interval);

#endif

	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("1970_01_01_08_00_00", "%4d_%02d_%02d_%02d_%02d_%02d"), 28800 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2020_02_28_00_00_00", "%4d_%02d_%02d_%02d_%02d_%02d"), 1582848000 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2020_02_28_08_00_00", "%4d_%02d_%02d_%02d_%02d_%02d"), 1582876800 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2020_02_29_00_00_00", "%4d_%02d_%02d_%02d_%02d_%02d"), 1582934400 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2020_02_29_08_00_00", "%4d_%02d_%02d_%02d_%02d_%02d"), 1582963200 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2020_03_01_00_00_00", "%4d_%02d_%02d_%02d_%02d_%02d"), 1583020800 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2020_03_01_08_00_00", "%4d_%02d_%02d_%02d_%02d_%02d"), 1583049600 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2021_02_28_00_00_00", "%4d_%02d_%02d_%02d_%02d_%02d"), 1614470400 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2021_02_28_08_00_00", "%4d_%02d_%02d_%02d_%02d_%02d"), 1614499200 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2021_02_29_00_00_00", "%4d_%02d_%02d_%02d_%02d_%02d"), 1614556800 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2021_02_29_08_00_00", "%4d_%02d_%02d_%02d_%02d_%02d"), 1614585600 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2021_03_01_00_00_00", "%4d_%02d_%02d_%02d_%02d_%02d"), 1614556800 - interval);
	TOOLKIT_EXPECT_EQ(tinyToolkit::time::FromDateTime("2021_03_01_08_00_00", "%4d_%02d_%02d_%02d_%02d_%02d"), 1614585600 - interval);
}

TOOLKIT_TEST_CASE(Time, AsDateTime)
{
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(0, 0), "1970-01-01 00:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(0, 8), "1970-01-01 08:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(-1, 0), "1969-12-31 23:59:59");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(-1, 8), "1970-01-01 07:59:59");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1582819200, 0), "2020-02-27 16:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1582819200, 8), "2020-02-28 00:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1582848000, 0), "2020-02-28 00:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1582848000, 8), "2020-02-28 08:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1582905600, 0), "2020-02-28 16:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1582905600, 8), "2020-02-29 00:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1582934400, 0), "2020-02-29 00:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1582934400, 8), "2020-02-29 08:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1582992000, 0), "2020-02-29 16:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1582992000, 8), "2020-03-01 00:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1583020800, 0), "2020-03-01 00:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1583020800, 8), "2020-03-01 08:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1614441600, 0), "2021-02-27 16:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1614441600, 8), "2021-02-28 00:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1614470400, 0), "2021-02-28 00:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1614470400, 8), "2021-02-28 08:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1614528000, 0), "2021-02-28 16:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1614528000, 8), "2021-03-01 00:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1614556800, 0), "2021-03-01 00:00:00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1614556800, 8), "2021-03-01 08:00:00");

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(0, 0, "%4d_%02d_%02d_%02d_%02d_%02d"), "1970_01_01_00_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(0, 8, "%4d_%02d_%02d_%02d_%02d_%02d"), "1970_01_01_08_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(-1, 0, "%4d_%02d_%02d_%02d_%02d_%02d"), "1969_12_31_23_59_59");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(-1, 8, "%4d_%02d_%02d_%02d_%02d_%02d"), "1970_01_01_07_59_59");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1582819200, 0, "%4d_%02d_%02d_%02d_%02d_%02d"), "2020_02_27_16_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1582819200, 8, "%4d_%02d_%02d_%02d_%02d_%02d"), "2020_02_28_00_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1582848000, 0, "%4d_%02d_%02d_%02d_%02d_%02d"), "2020_02_28_00_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1582848000, 8, "%4d_%02d_%02d_%02d_%02d_%02d"), "2020_02_28_08_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1582905600, 0, "%4d_%02d_%02d_%02d_%02d_%02d"), "2020_02_28_16_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1582905600, 8, "%4d_%02d_%02d_%02d_%02d_%02d"), "2020_02_29_00_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1582934400, 0, "%4d_%02d_%02d_%02d_%02d_%02d"), "2020_02_29_00_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1582934400, 8, "%4d_%02d_%02d_%02d_%02d_%02d"), "2020_02_29_08_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1582992000, 0, "%4d_%02d_%02d_%02d_%02d_%02d"), "2020_02_29_16_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1582992000, 8, "%4d_%02d_%02d_%02d_%02d_%02d"), "2020_03_01_00_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1583020800, 0, "%4d_%02d_%02d_%02d_%02d_%02d"), "2020_03_01_00_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1583020800, 8, "%4d_%02d_%02d_%02d_%02d_%02d"), "2020_03_01_08_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1614441600, 0, "%4d_%02d_%02d_%02d_%02d_%02d"), "2021_02_27_16_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1614441600, 8, "%4d_%02d_%02d_%02d_%02d_%02d"), "2021_02_28_00_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1614470400, 0, "%4d_%02d_%02d_%02d_%02d_%02d"), "2021_02_28_00_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1614470400, 8, "%4d_%02d_%02d_%02d_%02d_%02d"), "2021_02_28_08_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1614528000, 0, "%4d_%02d_%02d_%02d_%02d_%02d"), "2021_02_28_16_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1614528000, 8, "%4d_%02d_%02d_%02d_%02d_%02d"), "2021_03_01_00_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1614556800, 0, "%4d_%02d_%02d_%02d_%02d_%02d"), "2021_03_01_00_00_00");
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::time::AsDateTime(1614556800, 8, "%4d_%02d_%02d_%02d_%02d_%02d"), "2021_03_01_08_00_00");
}

TOOLKIT_TEST_CASE(Time, CurrentUTCDateTime)
{
	auto zone = tinyToolkit::time::Timezone();
	auto second = tinyToolkit::time::Second();
	auto formatString = tinyToolkit::time::CurrentUTCDateTime("%4d_%02d_%02d_%02d_%02d_%02d");
	auto defaultString = tinyToolkit::time::CurrentUTCDateTime();

	TOOLKIT_EXPECT_GE(tinyToolkit::time::FromDateTime(formatString.c_str(), "%4d_%02d_%02d_%02d_%02d_%02d"), second - zone * 60 * 60);
	TOOLKIT_EXPECT_LE(tinyToolkit::time::FromDateTime(formatString.c_str(), "%4d_%02d_%02d_%02d_%02d_%02d"), second - zone * 60 * 60 + 1);

	TOOLKIT_EXPECT_GE(tinyToolkit::time::FromDateTime(defaultString.c_str()), second - zone * 60 * 60);
	TOOLKIT_EXPECT_LE(tinyToolkit::time::FromDateTime(defaultString.c_str()), second - zone * 60 * 60 + 1);
}

TOOLKIT_TEST_CASE(Time, CurrentLocalDateTime)
{
	auto second = tinyToolkit::time::Second();
	auto formatString = tinyToolkit::time::CurrentLocalDateTime("%4d_%02d_%02d_%02d_%02d_%02d");
	auto defaultString = tinyToolkit::time::CurrentLocalDateTime();

	TOOLKIT_EXPECT_GE(tinyToolkit::time::FromDateTime(formatString.c_str(), "%4d_%02d_%02d_%02d_%02d_%02d"), second);
	TOOLKIT_EXPECT_LE(tinyToolkit::time::FromDateTime(formatString.c_str(), "%4d_%02d_%02d_%02d_%02d_%02d"), second + 1);

	TOOLKIT_EXPECT_GE(tinyToolkit::time::FromDateTime(defaultString.c_str()), second);
	TOOLKIT_EXPECT_LE(tinyToolkit::time::FromDateTime(defaultString.c_str()), second + 1);
}

TOOLKIT_TEST_CASE(Time, TimePoint)
{
	auto point = tinyToolkit::time::Second(tinyToolkit::time::TimePoint());
	auto second = tinyToolkit::time::Second();

	TOOLKIT_EXPECT_GE(second, point);
	TOOLKIT_EXPECT_LE(second, point + 1);
}

TOOLKIT_TEST_CASE(Time, TimePoint_Value)
{
	TOOLKIT_EXPECT_EQ(std::chrono::duration_cast<std::chrono::seconds>(tinyToolkit::time::TimePoint(0).time_since_epoch()).count(), 0);
	TOOLKIT_EXPECT_EQ(std::chrono::duration_cast<std::chrono::seconds>(tinyToolkit::time::TimePoint(-1).time_since_epoch()).count(), -1);
	TOOLKIT_EXPECT_EQ(std::chrono::duration_cast<std::chrono::seconds>(tinyToolkit::time::TimePoint(123456).time_since_epoch()).count(), 123456);
	TOOLKIT_EXPECT_EQ(std::chrono::duration_cast<std::chrono::seconds>(tinyToolkit::time::TimePoint(1234509876).time_since_epoch()).count(), 1234509876);
}
