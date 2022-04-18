/**
 *
 * 作者: hm
 *
 * 说明: hmac_md5
 *
 */


#include "hmac_md5.h"


TOOLKIT_TEST_CASE(HMAC_MD5, Char)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"618EA5740CBA3745AD8246DBA00F0710",
		"F47B5F32B67A085CDE0F2DAFAAA14050",
		"F7947EC6066A8A1BA53C6B65BCED8318",
		"94F7DA69EFAA46394EF1C91C6171A8A4"
	};

	tinyToolkit::hash::HMAC_MD5 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i].c_str());

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_MD5, UChar)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"618EA5740CBA3745AD8246DBA00F0710",
		"F47B5F32B67A085CDE0F2DAFAAA14050",
		"F7947EC6066A8A1BA53C6B65BCED8318",
		"94F7DA69EFAA46394EF1C91C6171A8A4"
	};

	tinyToolkit::hash::HMAC_MD5 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(reinterpret_cast<const uint8_t *>(src[i].c_str()));

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_MD5, String)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"618EA5740CBA3745AD8246DBA00F0710",
		"F47B5F32B67A085CDE0F2DAFAAA14050",
		"F7947EC6066A8A1BA53C6B65BCED8318",
		"94F7DA69EFAA46394EF1C91C6171A8A4"
	};

	tinyToolkit::hash::HMAC_MD5 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i]);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_MD5, Char_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"618EA5740CBA3745AD8246DBA00F0710",
		"F47B5F32B67A085CDE0F2DAFAAA14050",
		"F7947EC6066A8A1BA53C6B65BCED8318",
		"94F7DA69EFAA46394EF1C91C6171A8A4"
	};

	tinyToolkit::hash::HMAC_MD5 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i].c_str(), 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_MD5, UChar_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"618EA5740CBA3745AD8246DBA00F0710",
		"F47B5F32B67A085CDE0F2DAFAAA14050",
		"F7947EC6066A8A1BA53C6B65BCED8318",
		"94F7DA69EFAA46394EF1C91C6171A8A4"
	};

	tinyToolkit::hash::HMAC_MD5 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(reinterpret_cast<const uint8_t *>(src[i].c_str()), 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_MD5, String_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"618EA5740CBA3745AD8246DBA00F0710",
		"F47B5F32B67A085CDE0F2DAFAAA14050",
		"F7947EC6066A8A1BA53C6B65BCED8318",
		"94F7DA69EFAA46394EF1C91C6171A8A4"
	};

	tinyToolkit::hash::HMAC_MD5 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i], 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}
