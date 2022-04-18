/**
 *
 * 作者: hm
 *
 * 说明: 核心转储
 *
 */


#include "coreDump.h"


TOOLKIT_TEST_CASE(CoreDump, RegisterCoreDump)
{
	tinyToolkit::debug::RegisterCoreDump();
}

TOOLKIT_TEST_CASE(CoreDump, UnregisterCoreDump)
{
	tinyToolkit::debug::UnregisterCoreDump();
}
