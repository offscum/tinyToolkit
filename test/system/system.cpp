/**
 *
 * 作者: hm
 *
 * 说明: 系统信息
 *
 */


#include "system.h"


TOOLKIT_TEST_CASE(System, PageSize)
{
	TOOLKIT_EXPECT_GE(tinyToolkit::system::PageSize(), static_cast<int32_t>(1));
}

TOOLKIT_TEST_CASE(System, ProcessorCount)
{
	TOOLKIT_EXPECT_GE(tinyToolkit::system::ProcessorCount(), static_cast<int32_t>(1));
}

TOOLKIT_TEST_CASE(System, UserName)
{
	TOOLKIT_EXPECT_GE(tinyToolkit::system::UserName().length(), static_cast<std::size_t>(1));
}

TOOLKIT_TEST_CASE(System, ComputerName)
{
	TOOLKIT_EXPECT_GE(tinyToolkit::system::ComputerName().length(), static_cast<std::size_t>(1));
}
