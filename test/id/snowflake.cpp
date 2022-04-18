/**
 *
 * 作者: hm
 *
 * 说明: 分布式唯一标识码
 *
 */


#include "snowflake.h"


TOOLKIT_TEST_CASE(Snowflake, Generate)
{
	tinyToolkit::id::Snowflake snowflake(64, 128);

	for (int32_t i = 0; i < 100; ++i)
	{
		TOOLKIT_EXPECT_NE(snowflake.Generate(), snowflake.Generate());
	}
}
