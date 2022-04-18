/**
 *
 * 作者: hm
 *
 * 说明: 全局唯一标识码
 *
 */


#include "unique.h"


TOOLKIT_TEST_CASE(Unique, Generate)
{
	tinyToolkit::id::Unique unique{ };

	for (int32_t i = 0; i < 100; ++i)
	{
		TOOLKIT_EXPECT_NE(unique.Generate(), unique.Generate());
	}
}
