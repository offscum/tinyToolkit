/**
 *
 * 作者: hm
 *
 * 说明: 信号处理
 *
 */


#include "signal.h"


TOOLKIT_TEST_CASE(Signal, RegisterIgnoreSignal)
{
	tinyToolkit::application::RegisterIgnoreSignal();

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS



#else

	std::raise(SIGHUP);
	std::raise(SIGPIPE);
	std::raise(SIGCHLD);

#endif
}

TOOLKIT_TEST_CASE(Signal, RegisterExceptionSignal)
{
	static int32_t count{ 0 };

	tinyToolkit::application::RegisterExceptionSignal([](int32_t signalNo) { TOOLKIT_UNUSED(signalNo); ++count; });

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

	std::raise(SIGILL);
	std::raise(SIGFPE);
	std::raise(SIGABRT);
	std::raise(SIGSEGV);

	TOOLKIT_EXPECT_EQ(count, 4);

#else

	std::raise(SIGILL);
	std::raise(SIGFPE);
	std::raise(SIGABRT);
	std::raise(SIGSEGV);

	TOOLKIT_EXPECT_EQ(count, 4);

#endif
}

TOOLKIT_TEST_CASE(Signal, RegisterTerminateSignal)
{
	static int32_t count{ 0 };

	tinyToolkit::application::RegisterTerminateSignal([](int32_t signalNo) { TOOLKIT_UNUSED(signalNo); ++count; });

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

	std::raise(SIGINT);
	std::raise(SIGTERM);
	std::raise(SIGBREAK);

	TOOLKIT_EXPECT_EQ(count, 3);

#else

	std::raise(SIGINT);
	std::raise(SIGQUIT); /// clion会捕获这个信号
	std::raise(SIGTERM);
	std::raise(SIGTSTP);

	TOOLKIT_EXPECT_EQ(count, 4);

#endif
}

TOOLKIT_TEST_CASE(Signal, UnregisterIgnoreSignal)
{
	tinyToolkit::application::UnregisterIgnoreSignal();
}

TOOLKIT_TEST_CASE(Signal, UnregisterExceptionSignal)
{
	tinyToolkit::application::UnregisterExceptionSignal();
}

TOOLKIT_TEST_CASE(Signal, UnregisterTerminateSignal)
{
	tinyToolkit::application::UnregisterTerminateSignal();
}

TOOLKIT_TEST_CASE(Signal, RegisterSignalAction)
{

}

TOOLKIT_TEST_CASE(Signal, UnregisterSignalAction)
{

}
