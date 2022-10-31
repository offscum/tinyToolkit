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

	tinyToolkit::application::RegisterExceptionSignal([](int32_t sig)
	{
		TOOLKIT_UNUSED(sig);

		++count;
	});

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

	(void)std::raise(SIGILL);
	(void)std::raise(SIGFPE);
	(void)std::raise(SIGABRT);
	(void)std::raise(SIGSEGV);

	TOOLKIT_EXPECT_EQ(count, 4);

#else

	(void)std::raise(SIGILL);
	(void)std::raise(SIGFPE);
	(void)std::raise(SIGABRT);
	(void)std::raise(SIGSEGV);

	TOOLKIT_EXPECT_EQ(count, 4);

#endif
}

TOOLKIT_TEST_CASE(Signal, RegisterTerminateSignal)
{
	static int32_t count{ 0 };

	tinyToolkit::application::RegisterTerminateSignal([](int32_t sig)
	{
		TOOLKIT_UNUSED(sig);

		++count;
	});

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

	(void)std::raise(SIGINT);
	(void)std::raise(SIGTERM);
	(void)std::raise(SIGBREAK);

	TOOLKIT_EXPECT_EQ(count, 3);

#else

	(void)std::raise(SIGINT);
	(void)std::raise(SIGQUIT); /// clion会捕获这个信号
	(void)std::raise(SIGTERM);
	(void)std::raise(SIGTSTP);

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
