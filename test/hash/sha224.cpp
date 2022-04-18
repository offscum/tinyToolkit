/**
 *
 * 作者: hm
 *
 * 说明: sha224
 *
 */


#include "sha224.h"


TOOLKIT_TEST_CASE(SHA224, Char)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"78D8045D684ABD2EECE923758F3CD781489DF3A48E1278982466017F",
		"867916C509E025CD1EEF93151E82F518FCFDFCACD759965FD99E27AF",
		"A2CFCCE5B11372B4444618895DE1A979B520CF79C20307BD8F937BA4",
		"9AFDE0A3D4E20DB09618355C0B4EA22A79CD51A3418770F30110F6BB"
	};

	tinyToolkit::hash::SHA224 handle{ };

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i].c_str());

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(SHA224, UChar)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"78D8045D684ABD2EECE923758F3CD781489DF3A48E1278982466017F",
		"867916C509E025CD1EEF93151E82F518FCFDFCACD759965FD99E27AF",
		"A2CFCCE5B11372B4444618895DE1A979B520CF79C20307BD8F937BA4",
		"9AFDE0A3D4E20DB09618355C0B4EA22A79CD51A3418770F30110F6BB"
	};

	tinyToolkit::hash::SHA224 handle{ };

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(reinterpret_cast<const uint8_t *>(src[i].c_str()));

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(SHA224, String)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"78D8045D684ABD2EECE923758F3CD781489DF3A48E1278982466017F",
		"867916C509E025CD1EEF93151E82F518FCFDFCACD759965FD99E27AF",
		"A2CFCCE5B11372B4444618895DE1A979B520CF79C20307BD8F937BA4",
		"9AFDE0A3D4E20DB09618355C0B4EA22A79CD51A3418770F30110F6BB"
	};

	tinyToolkit::hash::SHA224 handle{ };

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i]);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(SHA224, Char_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"78D8045D684ABD2EECE923758F3CD781489DF3A48E1278982466017F",
		"867916C509E025CD1EEF93151E82F518FCFDFCACD759965FD99E27AF",
		"A2CFCCE5B11372B4444618895DE1A979B520CF79C20307BD8F937BA4",
		"9AFDE0A3D4E20DB09618355C0B4EA22A79CD51A3418770F30110F6BB"
	};

	tinyToolkit::hash::SHA224 handle{ };

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i].c_str(), 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(SHA224, UChar_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"78D8045D684ABD2EECE923758F3CD781489DF3A48E1278982466017F",
		"867916C509E025CD1EEF93151E82F518FCFDFCACD759965FD99E27AF",
		"A2CFCCE5B11372B4444618895DE1A979B520CF79C20307BD8F937BA4",
		"9AFDE0A3D4E20DB09618355C0B4EA22A79CD51A3418770F30110F6BB"
	};

	tinyToolkit::hash::SHA224 handle{ };

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(reinterpret_cast<const uint8_t *>(src[i].c_str()), 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(SHA224, String_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"78D8045D684ABD2EECE923758F3CD781489DF3A48E1278982466017F",
		"867916C509E025CD1EEF93151E82F518FCFDFCACD759965FD99E27AF",
		"A2CFCCE5B11372B4444618895DE1A979B520CF79C20307BD8F937BA4",
		"9AFDE0A3D4E20DB09618355C0B4EA22A79CD51A3418770F30110F6BB"
	};

	tinyToolkit::hash::SHA224 handle{ };

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i], 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}
