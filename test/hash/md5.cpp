/**
 *
 * 作者: hm
 *
 * 说明: md5
 *
 */


#include "md5.h"


TOOLKIT_TEST_CASE(MD5, Char)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"202CB962AC59075B964B07152D234B70",
		"A906449D5769FA7361D7ECC6AA3F6D28",
		"ED393D01253EA24A213E60624497E737",
		"22C60DF3392A25F0BE7540042CC9A321"
	};

	tinyToolkit::hash::MD5 handle{ };

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i].c_str());

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(MD5, UChar)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"202CB962AC59075B964B07152D234B70",
		"A906449D5769FA7361D7ECC6AA3F6D28",
		"ED393D01253EA24A213E60624497E737",
		"22C60DF3392A25F0BE7540042CC9A321"
	};

	tinyToolkit::hash::MD5 handle{ };

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(reinterpret_cast<const uint8_t *>(src[i].c_str()));

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(MD5, String)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"202CB962AC59075B964B07152D234B70",
		"A906449D5769FA7361D7ECC6AA3F6D28",
		"ED393D01253EA24A213E60624497E737",
		"22C60DF3392A25F0BE7540042CC9A321"
	};

	tinyToolkit::hash::MD5 handle{ };

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i]);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(MD5, Char_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"202CB962AC59075B964B07152D234B70",
		"A906449D5769FA7361D7ECC6AA3F6D28",
		"ED393D01253EA24A213E60624497E737",
		"22C60DF3392A25F0BE7540042CC9A321"
	};

	tinyToolkit::hash::MD5 handle{ };

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i].c_str(), 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(MD5, UChar_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"202CB962AC59075B964B07152D234B70",
		"A906449D5769FA7361D7ECC6AA3F6D28",
		"ED393D01253EA24A213E60624497E737",
		"22C60DF3392A25F0BE7540042CC9A321"
	};

	tinyToolkit::hash::MD5 handle{ };

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(reinterpret_cast<const uint8_t *>(src[i].c_str()), 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(MD5, String_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"202CB962AC59075B964B07152D234B70",
		"A906449D5769FA7361D7ECC6AA3F6D28",
		"ED393D01253EA24A213E60624497E737",
		"22C60DF3392A25F0BE7540042CC9A321"
	};

	tinyToolkit::hash::MD5 handle{ };

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i], 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}
