/**
 *
 * 作者: hm
 *
 * 说明: 字节序
 *
 */


#include "endian.h"


TOOLKIT_TEST_CASE(Endian, IsBigEndian)
{
	if (tinyToolkit::system::IsBigEndian())
	{
		TOOLKIT_EXPECT_TRUE(tinyToolkit::system::IsBigEndian());
		TOOLKIT_EXPECT_FALSE(tinyToolkit::system::IsLittleEndian());
	}
	else
	{
		TOOLKIT_EXPECT_FALSE(tinyToolkit::system::IsBigEndian());
		TOOLKIT_EXPECT_TRUE(tinyToolkit::system::IsLittleEndian());
	}
}

TOOLKIT_TEST_CASE(Endian, IsLittleEndian)
{
	if (tinyToolkit::system::IsLittleEndian())
	{
		TOOLKIT_EXPECT_TRUE(tinyToolkit::system::IsLittleEndian());
		TOOLKIT_EXPECT_FALSE(tinyToolkit::system::IsBigEndian());
	}
	else
	{
		TOOLKIT_EXPECT_FALSE(tinyToolkit::system::IsLittleEndian());
		TOOLKIT_EXPECT_TRUE(tinyToolkit::system::IsBigEndian());
	}
}
