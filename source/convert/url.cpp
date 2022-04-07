/**
 *
 * 作者: hm
 *
 * 说明: url编解码
 *
 */


#include "url.h"

#include <cstring>


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
		std::string UrlEncode(const char * content)
		{
			if (content == nullptr)
			{
				return std::string{ };
			}

			return UrlEncode(content, ::strlen(content));
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
		std::string UrlEncode(const uint8_t * content)
		{
			if (content == nullptr)
			{
				return std::string{ };
			}

			return UrlEncode(content, ::strlen(reinterpret_cast<const char *>(content)));
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
		std::string UrlEncode(const std::string & content)
		{
			if (content.empty())
			{
				return std::string{ };
			}

			return UrlEncode(content, content.length());
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
		std::string UrlEncode(const char * content, std::size_t length)
		{
			if (content == nullptr || length == 0)
			{
				return std::string{ };
			}

			return UrlEncode(reinterpret_cast<const uint8_t *>(content), length);
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
		std::string UrlEncode(const uint8_t * content, std::size_t length)
		{
			if (content == nullptr || length == 0)
			{
				return std::string{ };
			}

			std::string value{ };

			for (std::size_t i = 0; i < length; ++i)
			{
				uint8_t byte = content[i];

				if (byte == ' ')
				{
					value += "+";
				}
				else if (byte == '-' || byte == '_' || byte == '.' || byte == '!' ||
						 byte == '~' || byte == '*' || byte == '(' || byte == ')' || ::isalnum(byte))
				{
					value += static_cast<char>(byte);
				}
				else
				{
					static auto Transform = [](uint8_t tag) -> char
					{
						return static_cast<char>(tag > 9 ? tag - 10 + 'A': tag + '0');
					};

					value += "%";
					value += Transform(static_cast<uint8_t>(byte >> 4));
					value += Transform(static_cast<uint8_t>(byte % 16));
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
		std::string UrlEncode(const std::string & content, std::size_t length)
		{
			if (content.empty() || length == 0)
			{
				return std::string{ };
			}

			return UrlEncode(content.c_str(), length);
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
		std::string UrlDecode(const char * content)
		{
			if (content == nullptr)
			{
				return std::string{ };
			}

			return UrlDecode(content, ::strlen(content));
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
		std::string UrlDecode(const uint8_t * content)
		{
			if (content == nullptr)
			{
				return std::string{ };
			}

			return UrlDecode(content, ::strlen(reinterpret_cast<const char *>(content)));
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
		std::string UrlDecode(const std::string & content)
		{
			if (content.empty())
			{
				return std::string{ };
			}

			return UrlDecode(content, content.length());
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
		std::string UrlDecode(const char * content, std::size_t length)
		{
			if (content == nullptr || length == 0)
			{
				return std::string{ };
			}

			return UrlDecode(reinterpret_cast<const uint8_t *>(content), length);
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
		std::string UrlDecode(const uint8_t * content, std::size_t length)
		{
			if (content == nullptr || length == 0)
			{
				return std::string{ };
			}

			std::string value{ };

			for (std::size_t i = 0; i < length; ++i)
			{
				if (content[i] == '+')
				{
					value.push_back(' ');
				}
				else if (content[i] == '%')
				{
					static auto Transform = [](uint8_t tag) -> uint8_t
					{
						return static_cast<uint8_t>(::isdigit(tag) ? tag - '0' : tag + 10 - 'A');
					};

					uint8_t high = Transform(content[++i]);
					uint8_t low = Transform(content[++i]);

					value.push_back(static_cast<char>(high * 16 + low));
				}
				else
				{
					value.push_back(static_cast<char>(content[i]));
				}
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
		std::string UrlDecode(const std::string & content, std::size_t length)
		{
			if (content.empty() || length == 0)
			{
				return std::string{ };
			}

			return UrlDecode(content.c_str(), length);
		}
	}
}
