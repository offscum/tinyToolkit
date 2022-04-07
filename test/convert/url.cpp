/**
 *
 * 作者: hm
 *
 * 说明: url编解码
 *
 */


#include "url.h"


TOOLKIT_TEST_CASE(Url, UrlEncode_Char)
{
	std::string src = "https://www.baidu.com/?p1=123&p2=uuid";
	std::string dst = "https%3A%2F%2Fwww.baidu.com%2F%3Fp1%3D123%26p2%3Duuid";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::UrlEncode(src.c_str()), dst);
}

TOOLKIT_TEST_CASE(Url, UrlEncode_UChar)
{
	std::string src = "https://www.baidu.com/?p1=123&p2=uuid";
	std::string dst = "https%3A%2F%2Fwww.baidu.com%2F%3Fp1%3D123%26p2%3Duuid";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::UrlEncode(reinterpret_cast<const uint8_t *>(src.c_str())), dst);
}

TOOLKIT_TEST_CASE(Url, UrlEncode_String)
{
	std::string src = "https://www.baidu.com/?p1=123&p2=uuid";
	std::string dst = "https%3A%2F%2Fwww.baidu.com%2F%3Fp1%3D123%26p2%3Duuid";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::UrlEncode(src), dst);
}

TOOLKIT_TEST_CASE(Url, UrlEncode_Char_Length)
{
	std::string src = "https://www.baidu.com/?p1=123&p2=uuid";
	std::string dst = "https%3A%2F%2Fwww.baidu.com%2F";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::UrlEncode(src.c_str(), 22), dst);
}

TOOLKIT_TEST_CASE(Url, UrlEncode_UChar_Length)
{
	std::string src = "https://www.baidu.com/?p1=123&p2=uuid";
	std::string dst = "https%3A%2F%2Fwww.baidu.com%2F";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::UrlEncode(reinterpret_cast<const uint8_t *>(src.c_str()), 22), dst);
}

TOOLKIT_TEST_CASE(Url, UrlEncode_String_Length)
{
	std::string src = "https://www.baidu.com/?p1=123&p2=uuid";
	std::string dst = "https%3A%2F%2Fwww.baidu.com%2F";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::UrlEncode(src, 22), dst);
}

TOOLKIT_TEST_CASE(Url, UrlDecode_Char)
{
	std::string src = "https%3A%2F%2Fwww.baidu.com%2F%3Fp1%3D123%26p2%3Duuid";
	std::string dst = "https://www.baidu.com/?p1=123&p2=uuid";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::UrlDecode(src.c_str()), dst);
}

TOOLKIT_TEST_CASE(Url, UrlDecode_UChar)
{
	std::string src = "https%3A%2F%2Fwww.baidu.com%2F%3Fp1%3D123%26p2%3Duuid";
	std::string dst = "https://www.baidu.com/?p1=123&p2=uuid";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::UrlDecode(reinterpret_cast<const uint8_t *>(src.c_str())), dst);
}

TOOLKIT_TEST_CASE(Url, UrlDecode_String)
{
	std::string src = "https%3A%2F%2Fwww.baidu.com%2F%3Fp1%3D123%26p2%3Duuid";
	std::string dst = "https://www.baidu.com/?p1=123&p2=uuid";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::UrlDecode(src), dst);
}

TOOLKIT_TEST_CASE(Url, UrlDecode_Char_Length)
{
	std::string src = "https%3A%2F%2Fwww.baidu.com%2F%3Fp1%3D123%26p2%3Duuid";
	std::string dst = "https://www.baidu.com/";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::UrlDecode(src.c_str(), 30), dst);
}

TOOLKIT_TEST_CASE(Url, UrlDecode_UChar_Length)
{
	std::string src = "https%3A%2F%2Fwww.baidu.com%2F%3Fp1%3D123%26p2%3Duuid";
	std::string dst = "https://www.baidu.com/";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::UrlDecode(reinterpret_cast<const uint8_t *>(src.c_str()), 30), dst);
}

TOOLKIT_TEST_CASE(Url, UrlDecode_String_Length)
{
	std::string src = "https%3A%2F%2Fwww.baidu.com%2F%3Fp1%3D123%26p2%3Duuid";
	std::string dst = "https://www.baidu.com/";

	TOOLKIT_EXPECT_STR_EQ(tinyToolkit::convert::UrlDecode(src, 30), dst);
}
