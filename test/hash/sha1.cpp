/**
 *
 * 作者: hm
 *
 * 说明: sha1
 *
 */


#include "sha1.h"


TOOLKIT_TEST_CASE(SHA1, Char)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"40BD001563085FC35165329EA1FF5C5ECBDBBEEF",
		"4BE30D9814C6D4E9800E0D2EA9EC9FB00EFA887B",
		"A19272FF7102697DD02243D246A3E53B5BDF7C26",
		"F430299C6EDCF2EAAFFBA706B1BBE9211C72D280"
	};

	tinyToolkit::hash::SHA1 handle{ };

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i].c_str());

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(SHA1, UChar)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"40BD001563085FC35165329EA1FF5C5ECBDBBEEF",
		"4BE30D9814C6D4E9800E0D2EA9EC9FB00EFA887B",
		"A19272FF7102697DD02243D246A3E53B5BDF7C26",
		"F430299C6EDCF2EAAFFBA706B1BBE9211C72D280"
	};

	tinyToolkit::hash::SHA1 handle{ };

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(reinterpret_cast<const uint8_t *>(src[i].c_str()));

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(SHA1, String)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"40BD001563085FC35165329EA1FF5C5ECBDBBEEF",
		"4BE30D9814C6D4E9800E0D2EA9EC9FB00EFA887B",
		"A19272FF7102697DD02243D246A3E53B5BDF7C26",
		"F430299C6EDCF2EAAFFBA706B1BBE9211C72D280"
	};

	tinyToolkit::hash::SHA1 handle{ };

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i]);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(SHA1, Char_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"40BD001563085FC35165329EA1FF5C5ECBDBBEEF",
		"4BE30D9814C6D4E9800E0D2EA9EC9FB00EFA887B",
		"A19272FF7102697DD02243D246A3E53B5BDF7C26",
		"F430299C6EDCF2EAAFFBA706B1BBE9211C72D280"
	};

	tinyToolkit::hash::SHA1 handle{ };

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i].c_str(), 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(SHA1, UChar_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"40BD001563085FC35165329EA1FF5C5ECBDBBEEF",
		"4BE30D9814C6D4E9800E0D2EA9EC9FB00EFA887B",
		"A19272FF7102697DD02243D246A3E53B5BDF7C26",
		"F430299C6EDCF2EAAFFBA706B1BBE9211C72D280"
	};

	tinyToolkit::hash::SHA1 handle{ };

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(reinterpret_cast<const uint8_t *>(src[i].c_str()), 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(SHA1, String_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"40BD001563085FC35165329EA1FF5C5ECBDBBEEF",
		"4BE30D9814C6D4E9800E0D2EA9EC9FB00EFA887B",
		"A19272FF7102697DD02243D246A3E53B5BDF7C26",
		"F430299C6EDCF2EAAFFBA706B1BBE9211C72D280"
	};

	tinyToolkit::hash::SHA1 handle{ };

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i], 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}
