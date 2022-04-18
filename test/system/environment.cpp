/**
 *
 * 作者: hm
 *
 * 说明: 环境变量
 *
 */


#include "environment.h"


TOOLKIT_TEST_CASE(Environment, SetEnvironment)
{
	TOOLKIT_EXPECT_TRUE(tinyToolkit::system::SetEnvironment("TEST_SYSTEM_ENVIRONMENT", "SetEnvironment"));

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::system::GetEnvironment("TEST_SYSTEM_ENVIRONMENT"), "SetEnvironment");

	TOOLKIT_EXPECT_TRUE(tinyToolkit::system::SetEnvironment("TEST_SYSTEM_ENVIRONMENT", "GetEnvironment"));

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::system::GetEnvironment("TEST_SYSTEM_ENVIRONMENT"), "GetEnvironment");
}

TOOLKIT_TEST_CASE(Environment, GetEnvironment)
{
	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::system::GetEnvironment("TEST_SYSTEM_ENVIRONMENT"), "GetEnvironment");
}
