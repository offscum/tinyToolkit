/**
 *
 * 作者: hm
 *
 * 说明: 磁盘信息
 *
 */


#include "disk.h"


TOOLKIT_TEST_CASE(Disk, DiskSpace)
{
	int64_t free{ 0 };
	int64_t total{ 0 };

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

	TOOLKIT_EXPECT_TRUE(tinyToolkit::system::DiskSpace("C:", &total, &free));

#else

	TOOLKIT_EXPECT_TRUE(tinyToolkit::system::DiskSpace("/", &total, &free));

#endif

	TOOLKIT_EXPECT_GE(free, 0);
	TOOLKIT_EXPECT_GE(total, 1);
}

TOOLKIT_TEST_CASE(Disk, DiskUsage)
{
#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

	auto usage = tinyToolkit::system::DiskUsage("C:");

#else

	auto usage = tinyToolkit::system::DiskUsage("/");

#endif

	TOOLKIT_EXPECT_GE(usage, 0.0);
	TOOLKIT_EXPECT_LE(usage, 1.0);
}

TOOLKIT_TEST_CASE(Disk, DiskSize)
{
#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

	auto size = tinyToolkit::system::DiskSize("C:");

#else

	auto size = tinyToolkit::system::DiskSize("/");

#endif

	TOOLKIT_EXPECT_GE(size, static_cast<int64_t>(1));
}

TOOLKIT_TEST_CASE(Disk, DiskUsedSize)
{
#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

	auto size = tinyToolkit::system::DiskSize("C:");
	auto used = tinyToolkit::system::DiskUsedSize("C:");

#else

	auto size = tinyToolkit::system::DiskSize("/");
	auto used = tinyToolkit::system::DiskUsedSize("/");

#endif

	TOOLKIT_EXPECT_GE(used, static_cast<int64_t>(0));
	TOOLKIT_EXPECT_LE(used, size);
}

TOOLKIT_TEST_CASE(Disk, DiskFreeSize)
{
#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

	auto size = tinyToolkit::system::DiskSize("C:");
	auto free = tinyToolkit::system::DiskFreeSize("C:");

#else

	auto size = tinyToolkit::system::DiskSize("/");
	auto free = tinyToolkit::system::DiskFreeSize("/");

#endif

	TOOLKIT_EXPECT_GE(free, static_cast<int64_t>(0));
	TOOLKIT_EXPECT_LE(free, size);
}

