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

	tinyToolkit::application::Raise(SIGHUP);
	tinyToolkit::application::Raise(SIGPIPE);
	tinyToolkit::application::Raise(SIGCHLD);

#endif
}

TOOLKIT_TEST_CASE(Signal, RegisterExceptionSignal)
{
	static int32_t count{ 0 };

	tinyToolkit::application::RegisterExceptionSignal([](int32_t signalNo) { TOOLKIT_UNUSED(signalNo); ++count; });

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

	tinyToolkit::application::Raise(SIGILL);
	tinyToolkit::application::Raise(SIGFPE);
	tinyToolkit::application::Raise(SIGABRT);
	tinyToolkit::application::Raise(SIGSEGV);

	TOOLKIT_EXPECT_EQ(count, 4);

#else

	tinyToolkit::application::Raise(SIGILL);
	tinyToolkit::application::Raise(SIGFPE);
	tinyToolkit::application::Raise(SIGABRT);
	tinyToolkit::application::Raise(SIGSEGV);

	TOOLKIT_EXPECT_EQ(count, 4);

#endif
}

TOOLKIT_TEST_CASE(Signal, RegisterTerminateSignal)
{
	static int32_t count{ 0 };

	tinyToolkit::application::RegisterTerminateSignal([](int32_t signalNo) { TOOLKIT_UNUSED(signalNo); ++count; });

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

	tinyToolkit::application::Raise(SIGINT);
	tinyToolkit::application::Raise(SIGTERM);
	tinyToolkit::application::Raise(SIGBREAK);

	TOOLKIT_EXPECT_EQ(count, 3);

#else

	tinyToolkit::application::Raise(SIGINT);
	tinyToolkit::application::Raise(SIGQUIT); /// clion会捕获这个信号
	tinyToolkit::application::Raise(SIGTERM);
	tinyToolkit::application::Raise(SIGTSTP);

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

TOOLKIT_TEST_CASE(Signal, Raise)
{

}

TOOLKIT_TEST_CASE(Signal, RegisterSignalAction)
{

}

TOOLKIT_TEST_CASE(Signal, UnregisterSignalAction)
{

}
