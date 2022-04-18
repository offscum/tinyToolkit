/**
 *
 * 作者: hm
 *
 * 说明: 堆栈信息
 *
 */


#include "stacktrace.h"


TOOLKIT_TEST_CASE(Stacktrace, Stacktrace)
{
	TOOLKIT_EXPECT_GE(tinyToolkit::debug::Stacktrace().length(), static_cast<std::size_t>(1));
}
