/**
 *
 * 作者: hm
 *
 * 说明: base64编解码
 *
 */


#include "base64.h"

#include <cstring>
#include <stdexcept>


namespace tinyToolkit
{
	namespace convert
	{
		/**
		 *
		 * 编码
		 *
		 * @param content 内容
		 *
		 * @return 结果
		 *
		 */
		std::string Base64Encode(const char * content)
		{
			if (content == nullptr)
			{
				return std::string{ };
			}

			return Base64Encode(reinterpret_cast<const uint8_t *>(content), ::strlen(content));
		}

		/**
		 *
		 * 编码
		 *
		 * @param content 内容
		 *
		 * @return 结果
		 *
		 */
		std::string Base64Encode(const uint8_t * content)
		{
			if (content == nullptr)
			{
				return std::string{ };
			}

			return Base64Encode(content, ::strlen(reinterpret_cast<const char *>(content)));
		}

		/**
		 *
		 * 编码
		 *
		 * @param content 内容
		 *
		 * @return 结果
		 *
		 */
		std::string Base64Encode(const std::string & content)
		{
			if (content.empty())
			{
				return std::string{ };
			}

			return Base64Encode(reinterpret_cast<const uint8_t *>(content.c_str()), content.length());
		}

		/**
		 *
		 * 编码
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 * @return 结果
		 *
		 */
		std::string Base64Encode(const char * content, std::size_t length)
		{
			if (content == nullptr || length == 0)
			{
				return std::string{ };
			}

			return Base64Encode(reinterpret_cast<const uint8_t *>(content), length);
		}

		/**
		 *
		 * 编码
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 * @return 结果
		 *
		 */
		std::string Base64Encode(const uint8_t * content, std::size_t length)
		{
			if (content == nullptr || length == 0)
			{
				return std::string{ };
			}

			static char EncodeTable[64]
			{
				'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
				'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
				'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
				'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
				'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
				'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
				'w', 'x', 'y', 'z', '0', '1', '2', '3',
				'4', '5', '6', '7', '8', '9', '+', '/'
			};

			std::string value{ };

			while (length > 2)
			{
				value += EncodeTable[content[0] >> 2];
				value += EncodeTable[((content[0] & 0x03) << 4) + (content[1] >> 4)];
				value += EncodeTable[((content[1] & 0x0f) << 2) + (content[2] >> 6)];
				value += EncodeTable[content[2] & 0x3f];

				length -= 3;
				content += 3;
			}

			if (length > 0)
			{
				value += EncodeTable[content[0] >> 2];

				if (length % 3 == 1)
				{
					value += EncodeTable[(content[0] & 0x03) << 4];
					value += "==";
				}
				else if (length % 3 == 2)
				{
					value += EncodeTable[((content[0] & 0x03) << 4) + (content[1] >> 4)];
					value += EncodeTable[ (content[1] & 0x0f) << 2];
					value += "=";
				}
			}

			return value;
		}

		/**
		 *
		 * 编码
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 * @return 结果
		 *
		 */
		std::string Base64Encode(const std::string & content, std::size_t length)
		{
			if (content.empty() || length == 0)
			{
				return std::string{ };
			}

			return Base64Encode(reinterpret_cast<const uint8_t *>(content.c_str()), length);
		}

		/**
		 *
		 * 解码
		 *
		 * @param content 内容
		 *
		 * @return 结果
		 *
		 */
		std::string Base64Decode(const char * content)
		{
			if (content == nullptr)
			{
				return std::string{ };
			}

			return Base64Decode(reinterpret_cast<const uint8_t *>(content), ::strlen(content));
		}

		/**
		 *
		 * 解码
		 *
		 * @param content 内容
		 *
		 * @return 结果
		 *
		 */
		std::string Base64Decode(const uint8_t * content)
		{
			if (content == nullptr)
			{
				return std::string{ };
			}

			return Base64Decode(content, ::strlen(reinterpret_cast<const char *>(content)));
		}

		/**
		 *
		 * 解码
		 *
		 * @param content 内容
		 *
		 * @return 结果
		 *
		 */
		std::string Base64Decode(const std::string & content)
		{
			if (content.empty())
			{
				return std::string{ };
			}

			return Base64Decode(reinterpret_cast<const uint8_t *>(content.c_str()), content.length());
		}

		/**
		 *
		 * 解码
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 * @return 结果
		 *
		 */
		std::string Base64Decode(const char * content, std::size_t length)
		{
			if (content == nullptr || length == 0)
			{
				return std::string{ };
			}

			return Base64Decode(reinterpret_cast<const uint8_t *>(content), length);
		}

		/**
		 *
		 * 解码
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 * @return 结果
		 *
		 */
		std::string Base64Decode(const uint8_t * content, std::size_t length)
		{
			if (content == nullptr || length == 0)
			{
				return std::string{ };
			}

			static char DecodeTable[256]
			{
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
				52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1,  0, -1, -1,
				-1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
				15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
				-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
				41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
			};

			char ch;

			int32_t bin{ 0 };

			std::size_t i{ 0 };

			std::string value{ };

			while ((ch = static_cast<char>(*content++)) != '\0' && i <= length)
			{
				auto pos = i % 4;

				if (ch == '=')
				{
					/**
					 *
					 * 先说明一个概念 : 在解码时, 4个字符为一组进行一轮字符匹配.
					 *
					 * 两个条件 :
					 * 1、如果某一轮匹配的第二个是 "=" 且第三个字符不是 "=" , 说明这个带解析字符串不合法, 直接返回空
					 * 2、如果当前 "=" 不是第二个字符, 且后面的字符只包含空白符, 则说明这个这个条件合法, 可以继续.
					 *
					 */
					if (*content != '=' && pos == 1)
					{
						throw std::runtime_error("Decode content is invalid");
					}

					continue;
				}

				ch = DecodeTable[static_cast<uint8_t>(ch)];

				if (ch < 0)
				{
					continue;
				}

				switch (pos)
				{
					case 0:
					{
						bin = ch << 2;

						break;
					}

					case 1:
					{
						bin |= ch >> 4;

						value.push_back(static_cast<char>(bin));

						bin = (ch & 0x0f) << 4;

						break;
					}

					case 2:
					{
						bin |= ch >> 2;

						value.push_back(static_cast<char>(bin));

						bin = (ch & 0x03) << 6;

						break;
					}

					case 3:
					{
						bin |= ch;

						value.push_back(static_cast<char>(bin));

						break;
					}

					default:
					{
						break;
					}
				}

				++i;
			}

			return value;
		}

		/**
		 *
		 * 解码
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 * @return 结果
		 *
		 */
		std::string Base64Decode(const std::string & content, std::size_t length)
		{
			if (content.empty() || length == 0)
			{
				return std::string{ };
			}

			return Base64Decode(reinterpret_cast<const uint8_t *>(content.c_str()), length);
		}
	}
}
