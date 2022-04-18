/**
 *
 * 作者: hm
 *
 * 说明: hmac_sha256
 *
 */


#include "hmac_sha256.h"


TOOLKIT_TEST_CASE(HMAC_SHA256, Char)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"67570866628FC96F4A9F071544C70F4E3D7D3CB143AC0FE2CB34C307921D03F9",
		"F9C3BE17E62BD62777E6A23AB39E0D4ED7B81013C4ADA8229EE9DEF69F4597B7",
		"9942CF1768B96F42EE16F61C2C7BA22815EE2D0BFD4A97685605DE9FF0E60DA8",
		"659ECF56281C7DF6BF7190212336A9F034C0EDD17F625EF99219364700E21080"
	};

	tinyToolkit::hash::HMAC_SHA256 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i].c_str());

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_SHA256, UChar)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"67570866628FC96F4A9F071544C70F4E3D7D3CB143AC0FE2CB34C307921D03F9",
		"F9C3BE17E62BD62777E6A23AB39E0D4ED7B81013C4ADA8229EE9DEF69F4597B7",
		"9942CF1768B96F42EE16F61C2C7BA22815EE2D0BFD4A97685605DE9FF0E60DA8",
		"659ECF56281C7DF6BF7190212336A9F034C0EDD17F625EF99219364700E21080"
	};

	tinyToolkit::hash::HMAC_SHA256 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(reinterpret_cast<const uint8_t *>(src[i].c_str()));

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_SHA256, String)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"67570866628FC96F4A9F071544C70F4E3D7D3CB143AC0FE2CB34C307921D03F9",
		"F9C3BE17E62BD62777E6A23AB39E0D4ED7B81013C4ADA8229EE9DEF69F4597B7",
		"9942CF1768B96F42EE16F61C2C7BA22815EE2D0BFD4A97685605DE9FF0E60DA8",
		"659ECF56281C7DF6BF7190212336A9F034C0EDD17F625EF99219364700E21080"
	};

	tinyToolkit::hash::HMAC_SHA256 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i]);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_SHA256, Char_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"67570866628FC96F4A9F071544C70F4E3D7D3CB143AC0FE2CB34C307921D03F9",
		"F9C3BE17E62BD62777E6A23AB39E0D4ED7B81013C4ADA8229EE9DEF69F4597B7",
		"9942CF1768B96F42EE16F61C2C7BA22815EE2D0BFD4A97685605DE9FF0E60DA8",
		"659ECF56281C7DF6BF7190212336A9F034C0EDD17F625EF99219364700E21080"
	};

	tinyToolkit::hash::HMAC_SHA256 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i].c_str(), 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_SHA256, UChar_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"67570866628FC96F4A9F071544C70F4E3D7D3CB143AC0FE2CB34C307921D03F9",
		"F9C3BE17E62BD62777E6A23AB39E0D4ED7B81013C4ADA8229EE9DEF69F4597B7",
		"9942CF1768B96F42EE16F61C2C7BA22815EE2D0BFD4A97685605DE9FF0E60DA8",
		"659ECF56281C7DF6BF7190212336A9F034C0EDD17F625EF99219364700E21080"
	};

	tinyToolkit::hash::HMAC_SHA256 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(reinterpret_cast<const uint8_t *>(src[i].c_str()), 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_SHA256, String_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"67570866628FC96F4A9F071544C70F4E3D7D3CB143AC0FE2CB34C307921D03F9",
		"F9C3BE17E62BD62777E6A23AB39E0D4ED7B81013C4ADA8229EE9DEF69F4597B7",
		"9942CF1768B96F42EE16F61C2C7BA22815EE2D0BFD4A97685605DE9FF0E60DA8",
		"659ECF56281C7DF6BF7190212336A9F034C0EDD17F625EF99219364700E21080"
	};

	tinyToolkit::hash::HMAC_SHA256 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i], 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}
