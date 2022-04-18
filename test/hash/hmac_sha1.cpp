/**
 *
 * 作者: hm
 *
 * 说明: hmac_sha1
 *
 */


#include "hmac_sha1.h"


TOOLKIT_TEST_CASE(HMAC_SHA1, Char)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"7C0A0333449C5FFFDEE31BDA67467C319ACAEB12",
		"A24D29CA6AB99855FED15154693C52C6AE2B2636",
		"94F9EFFDB85E1AC8E86AFB614E592686ED61345B",
		"B1A74DCB45BF65CC6E2D6118B2C61400DCB42EAD"
	};

	tinyToolkit::hash::HMAC_SHA1 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i].c_str());

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_SHA1, UChar)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"7C0A0333449C5FFFDEE31BDA67467C319ACAEB12",
		"A24D29CA6AB99855FED15154693C52C6AE2B2636",
		"94F9EFFDB85E1AC8E86AFB614E592686ED61345B",
		"B1A74DCB45BF65CC6E2D6118B2C61400DCB42EAD"
	};

	tinyToolkit::hash::HMAC_SHA1 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(reinterpret_cast<const uint8_t *>(src[i].c_str()));

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_SHA1, String)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"7C0A0333449C5FFFDEE31BDA67467C319ACAEB12",
		"A24D29CA6AB99855FED15154693C52C6AE2B2636",
		"94F9EFFDB85E1AC8E86AFB614E592686ED61345B",
		"B1A74DCB45BF65CC6E2D6118B2C61400DCB42EAD"
	};

	tinyToolkit::hash::HMAC_SHA1 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i]);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_SHA1, Char_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"7C0A0333449C5FFFDEE31BDA67467C319ACAEB12",
		"A24D29CA6AB99855FED15154693C52C6AE2B2636",
		"94F9EFFDB85E1AC8E86AFB614E592686ED61345B",
		"B1A74DCB45BF65CC6E2D6118B2C61400DCB42EAD"
	};

	tinyToolkit::hash::HMAC_SHA1 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i].c_str(), 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_SHA1, UChar_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"7C0A0333449C5FFFDEE31BDA67467C319ACAEB12",
		"A24D29CA6AB99855FED15154693C52C6AE2B2636",
		"94F9EFFDB85E1AC8E86AFB614E592686ED61345B",
		"B1A74DCB45BF65CC6E2D6118B2C61400DCB42EAD"
	};

	tinyToolkit::hash::HMAC_SHA1 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(reinterpret_cast<const uint8_t *>(src[i].c_str()), 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_SHA1, String_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"7C0A0333449C5FFFDEE31BDA67467C319ACAEB12",
		"A24D29CA6AB99855FED15154693C52C6AE2B2636",
		"94F9EFFDB85E1AC8E86AFB614E592686ED61345B",
		"B1A74DCB45BF65CC6E2D6118B2C61400DCB42EAD"
	};

	tinyToolkit::hash::HMAC_SHA1 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i], 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}
