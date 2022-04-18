/**
 *
 * 作者: hm
 *
 * 说明: 内存信息
 *
 */


#include "memory.h"


TOOLKIT_TEST_CASE(Memory, MemorySpace)
{
	int64_t free{ 0 };
	int64_t total{ 0 };

	TOOLKIT_EXPECT_TRUE(tinyToolkit::system::MemorySpace(&total, &free));

	TOOLKIT_EXPECT_GE(free, 0);
	TOOLKIT_EXPECT_GE(total, 1);
}

TOOLKIT_TEST_CASE(Memory, MemoryUsage)
{
	auto usage = tinyToolkit::system::MemoryUsage();

	TOOLKIT_EXPECT_GE(usage, 0.0);
	TOOLKIT_EXPECT_LE(usage, 1.0);
}

TOOLKIT_TEST_CASE(Memory, MemorySize)
{
	TOOLKIT_EXPECT_GE(tinyToolkit::system::MemorySize(), static_cast<int64_t>(1));
}

TOOLKIT_TEST_CASE(Memory, MemoryUsedSize)
{
	auto size = tinyToolkit::system::MemorySize();
	auto used = tinyToolkit::system::MemoryUsedSize();

	TOOLKIT_EXPECT_GE(used, static_cast<int64_t>(0));
	TOOLKIT_EXPECT_LE(used, size);
}

TOOLKIT_TEST_CASE(Memory, MemoryFreeSize)
{
	auto size = tinyToolkit::system::MemorySize();
	auto free = tinyToolkit::system::MemoryFreeSize();

	TOOLKIT_EXPECT_GE(free, static_cast<int64_t>(0));
	TOOLKIT_EXPECT_LE(free, size);
}
