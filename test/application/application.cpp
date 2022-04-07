/**
 *
 * 作者: hm
 *
 * 说明: 应用信息
 *
 */


#include "application.h"


TOOLKIT_TEST_CASE(Application, Exist_ID)
{
	TOOLKIT_EXPECT_TRUE(tinyToolkit::application::Exist(tinyToolkit::application::ProcessID()));
}

TOOLKIT_TEST_CASE(Application, Exist_Name)
{
	TOOLKIT_EXPECT_TRUE(tinyToolkit::application::Exist(tinyToolkit::application::Name()));
}

TOOLKIT_TEST_CASE(Application, SetThreadName)
{
	TOOLKIT_EXPECT_TRUE(tinyToolkit::application::SetThreadName("test_thread"));
}

TOOLKIT_TEST_CASE(Application, UsedMemory)
{
	TOOLKIT_EXPECT_GE(tinyToolkit::application::UsedMemory(tinyToolkit::application::ProcessID()), static_cast<int64_t>(0));
}

TOOLKIT_TEST_CASE(Application, ThreadID)
{
	TOOLKIT_EXPECT_GE(tinyToolkit::application::ThreadID(), static_cast<uint64_t>(1));

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS || TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_APPLE

	TOOLKIT_EXPECT_NE(tinyToolkit::application::ThreadID(), tinyToolkit::application::ProcessID());

	TOOLKIT_EXPECT_FALSE(tinyToolkit::application::Exist(tinyToolkit::application::ThreadID()));

#else

	TOOLKIT_EXPECT_EQ(tinyToolkit::application::ThreadID(), tinyToolkit::application::ProcessID());

	TOOLKIT_EXPECT_TRUE(tinyToolkit::application::Exist(tinyToolkit::application::ThreadID()));

#endif
}

TOOLKIT_TEST_CASE(Application, ProcessID)
{
	TOOLKIT_EXPECT_GE(tinyToolkit::application::ProcessID(), static_cast<uint64_t>(1));

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS || TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_APPLE

	TOOLKIT_EXPECT_NE(tinyToolkit::application::ProcessID(), tinyToolkit::application::ThreadID());

#else

	TOOLKIT_EXPECT_EQ(tinyToolkit::application::ProcessID(), tinyToolkit::application::ThreadID());

#endif

	TOOLKIT_EXPECT_TRUE(tinyToolkit::application::Exist(tinyToolkit::application::ProcessID()));
}

TOOLKIT_TEST_CASE(Application, Name)
{
#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::application::Name(), "test_application.exe");

#else

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::application::Name(), "test_application");

#endif
}

TOOLKIT_TEST_CASE(Application, Path)
{
	auto tail = [](const std::string & path) -> std::string
	{
		return path.substr(path.rfind(TOOLKIT_PATH_SEP));
	}(tinyToolkit::application::Path());

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

	TOOLKIT_EXPECT_STR_EQ(tail, "\\test_application.exe");

#else

	TOOLKIT_EXPECT_STR_EQ(tail, "/test_application");

#endif
}

TOOLKIT_TEST_CASE(Application, CompileDateTime)
{
	TOOLKIT_EXPECT_EQ(tinyToolkit::application::CompileDateTime().length(), static_cast<std::size_t>(19));
}
