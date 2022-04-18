/**
 *
 * 作者: hm
 *
 * 说明: hmac_sha224
 *
 */


#include "hmac_sha224.h"


TOOLKIT_TEST_CASE(HMAC_SHA224, Char)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"36CB661C239149619BF2A04E73BD2DABEEAE9C9E049C92F9B6637D16",
		"92CADA9B9871CD0B8E30E39756EA9BBA33722EDB3A10E66B022FC90D",
		"01220B05DE642036BFB12D7FBCEF8AF72C01C8C8BB19654DE326DB21",
		"4C7720171ED721F80A505E81C22C25833CFBC54FBF30CB066CEAC3DA"
	};

	tinyToolkit::hash::HMAC_SHA224 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i].c_str());

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_SHA224, UChar)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"36CB661C239149619BF2A04E73BD2DABEEAE9C9E049C92F9B6637D16",
		"92CADA9B9871CD0B8E30E39756EA9BBA33722EDB3A10E66B022FC90D",
		"01220B05DE642036BFB12D7FBCEF8AF72C01C8C8BB19654DE326DB21",
		"4C7720171ED721F80A505E81C22C25833CFBC54FBF30CB066CEAC3DA"
	};

	tinyToolkit::hash::HMAC_SHA224 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(reinterpret_cast<const uint8_t *>(src[i].c_str()));

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_SHA224, String)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"36CB661C239149619BF2A04E73BD2DABEEAE9C9E049C92F9B6637D16",
		"92CADA9B9871CD0B8E30E39756EA9BBA33722EDB3A10E66B022FC90D",
		"01220B05DE642036BFB12D7FBCEF8AF72C01C8C8BB19654DE326DB21",
		"4C7720171ED721F80A505E81C22C25833CFBC54FBF30CB066CEAC3DA"
	};

	tinyToolkit::hash::HMAC_SHA224 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i]);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_SHA224, Char_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"36CB661C239149619BF2A04E73BD2DABEEAE9C9E049C92F9B6637D16",
		"92CADA9B9871CD0B8E30E39756EA9BBA33722EDB3A10E66B022FC90D",
		"01220B05DE642036BFB12D7FBCEF8AF72C01C8C8BB19654DE326DB21",
		"4C7720171ED721F80A505E81C22C25833CFBC54FBF30CB066CEAC3DA"
	};

	tinyToolkit::hash::HMAC_SHA224 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i].c_str(), 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_SHA224, UChar_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"36CB661C239149619BF2A04E73BD2DABEEAE9C9E049C92F9B6637D16",
		"92CADA9B9871CD0B8E30E39756EA9BBA33722EDB3A10E66B022FC90D",
		"01220B05DE642036BFB12D7FBCEF8AF72C01C8C8BB19654DE326DB21",
		"4C7720171ED721F80A505E81C22C25833CFBC54FBF30CB066CEAC3DA"
	};

	tinyToolkit::hash::HMAC_SHA224 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(reinterpret_cast<const uint8_t *>(src[i].c_str()), 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_SHA224, String_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"36CB661C239149619BF2A04E73BD2DABEEAE9C9E049C92F9B6637D16",
		"92CADA9B9871CD0B8E30E39756EA9BBA33722EDB3A10E66B022FC90D",
		"01220B05DE642036BFB12D7FBCEF8AF72C01C8C8BB19654DE326DB21",
		"4C7720171ED721F80A505E81C22C25833CFBC54FBF30CB066CEAC3DA"
	};

	tinyToolkit::hash::HMAC_SHA224 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i], 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}
