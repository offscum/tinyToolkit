/**
 *
 * 作者: hm
 *
 * 说明: base64编解码
 *
 */


#include "base64.h"


TOOLKIT_TEST_CASE(Base64, Base64Encode_Char)
{
	const std::string src = "https://www.baidu.com/?p1=123&p2=uuid";
	const std::string dst = "aHR0cHM6Ly93d3cuYmFpZHUuY29tLz9wMT0xMjMmcDI9dXVpZA==";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::Base64Encode(src.c_str()), dst);
}

TOOLKIT_TEST_CASE(Base64, Base64Encode_UChar)
{
	const std::string src = "https://www.baidu.com/?p1=123&p2=uuid";
	const std::string dst = "aHR0cHM6Ly93d3cuYmFpZHUuY29tLz9wMT0xMjMmcDI9dXVpZA==";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::Base64Encode(reinterpret_cast<const uint8_t *>(src.c_str())), dst);
}

TOOLKIT_TEST_CASE(Base64, Base64Encode_String)
{
	const std::string src = "https://www.baidu.com/?p1=123&p2=uuid";
	const std::string dst = "aHR0cHM6Ly93d3cuYmFpZHUuY29tLz9wMT0xMjMmcDI9dXVpZA==";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::Base64Encode(src), dst);
}

TOOLKIT_TEST_CASE(Base64, Base64Encode_Char_Length)
{
	const std::string src = "https://www.baidu.com/?p1=123&p2=uuid";
	const std::string dst = "aHR0cHM6Ly93d3cuYmFpZHUuY29tLw==";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::Base64Encode(src.c_str(), 22), dst);
}

TOOLKIT_TEST_CASE(Base64, Base64Encode_UChar_Length)
{
	const std::string src = "https://www.baidu.com/?p1=123&p2=uuid";
	const std::string dst = "aHR0cHM6Ly93d3cuYmFpZHUuY29tLw==";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::Base64Encode(reinterpret_cast<const uint8_t *>(src.c_str()), 22), dst);
}

TOOLKIT_TEST_CASE(Base64, Base64Encode_String_Length)
{
	const std::string src = "https://www.baidu.com/?p1=123&p2=uuid";
	const std::string dst = "aHR0cHM6Ly93d3cuYmFpZHUuY29tLw==";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::Base64Encode(src, 22), dst);
}

TOOLKIT_TEST_CASE(Base64, Base64Decode_Char)
{
	const std::string src = "aHR0cHM6Ly93d3cuYmFpZHUuY29tLz9wMT0xMjMmcDI9dXVpZA==";
	const std::string dst = "https://www.baidu.com/?p1=123&p2=uuid";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::Base64Decode(src.c_str()), dst);
}

TOOLKIT_TEST_CASE(Base64, Base64Decode_UChar)
{
	const std::string src = "aHR0cHM6Ly93d3cuYmFpZHUuY29tLz9wMT0xMjMmcDI9dXVpZA==";
	const std::string dst = "https://www.baidu.com/?p1=123&p2=uuid";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::Base64Decode(reinterpret_cast<const uint8_t *>(src.c_str())), dst);
}

TOOLKIT_TEST_CASE(Base64, Base64Decode_String)
{
	const std::string src = "aHR0cHM6Ly93d3cuYmFpZHUuY29tLz9wMT0xMjMmcDI9dXVpZA==";
	const std::string dst = "https://www.baidu.com/?p1=123&p2=uuid";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::Base64Decode(src), dst);
}

TOOLKIT_TEST_CASE(Base64, Base64Decode_Char_Length)
{
	const std::string src = "aHR0cHM6Ly93d3cuYmFpZHUuY29tLz9wMT0xMjMmcDI9dXVpZA==";
	const std::string dst = "https://www.baidu.com/";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::Base64Decode(src.c_str(), 29), dst);
}

TOOLKIT_TEST_CASE(Base64, Base64Decode_UChar_Length)
{
	const std::string src = "aHR0cHM6Ly93d3cuYmFpZHUuY29tLz9wMT0xMjMmcDI9dXVpZA==";
	const std::string dst = "https://www.baidu.com/";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::Base64Decode(reinterpret_cast<const uint8_t *>(src.c_str()), 29), dst);
}

TOOLKIT_TEST_CASE(Base64, Base64Decode_String_Length)
{
	const std::string src = "aHR0cHM6Ly93d3cuYmFpZHUuY29tLz9wMT0xMjMmcDI9dXVpZA==";
	const std::string dst = "https://www.baidu.com/";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::Base64Decode(src, 29), dst);
}
