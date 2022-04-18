/**
 *
 * 作者: hm
 *
 * 说明: md5
 *
 */


#include "md5.h"

#include <cstring>


namespace tinyToolkit
{
	namespace hash
	{
		const uint32_t MD5::BLOCK_SIZE;
		const uint32_t MD5::DIGEST_SIZE;


		/**
		 *
		 * 构造函数
		 *
		 */
		MD5::MD5()
		{
			Initialization(_context);
		}

		/**
		 *
		 * 重置
		 *
		 */
		void MD5::Reset()
		{
			_isComputed = false;

			::memset(reinterpret_cast<void *>(_digest), 0, sizeof(_digest));
			::memset(reinterpret_cast<void *>(&_context), 0, sizeof(_context));

			_result.clear();
			_result.shrink_to_fit();

			Initialization(_context);
		}

		/**
		 *
		 * 追加
		 *
		 * @param content 内容
		 *
		 */
		void MD5::Append(const char * content)
		{
			if (content == nullptr)
			{
				return;
			}

			Append(content, ::strlen(content));
		}

		/**
		 *
		 * 追加
		 *
		 * @param content 内容
		 *
		 */
		void MD5::Append(const uint8_t * content)
		{
			if (content == nullptr)
			{
				return;
			}

			Append(content, ::strlen(reinterpret_cast<const char *>(content)));
		}

		/**
		 *
		 * 追加
		 *
		 * @param content 内容
		 *
		 */
		void MD5::Append(const std::string & content)
		{
			if (content.empty())
			{
				return;
			}

			Append(content, content.length());
		}

		/**
		 *
		 * 追加
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 */
		void MD5::Append(const char * content, std::size_t length)
		{
			if (content == nullptr || length == 0)
			{
				return;
			}

			Append(reinterpret_cast<const uint8_t *>(content), length);
		}

		/**
		 *
		 * 追加
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 */
		void MD5::Append(const uint8_t * content, std::size_t length)
		{
			if (content == nullptr || length == 0)
			{
				return;
			}

			Update(_context, content, length);

			_isComputed = false;
		}

		/**
		 *
		 * 追加
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 */
		void MD5::Append(const std::string & content, std::size_t length)
		{
			if (content.empty() || length == 0)
			{
				return;
			}

			Append(content.c_str(), length);
		}

		/**
		 *
		 * 摘要
		 *
		 * @return 摘要
		 *
		 */
		const uint8_t * MD5::Digest()
		{
			Generate();

			return _digest;
		}

		/**
		 *
		 * 摘要
		 *
		 * @return 摘要
		 *
		 */
		const std::string & MD5::Result()
		{
			Generate();

			return _result;
		}

		/**
		 *
		 * 生成
		 *
		 */
		void MD5::Generate()
		{
			if (_isComputed)
			{
				return;
			}

			_isComputed = true;

			Context context{ };

			::memcpy(&context, &_context, sizeof(context));

			Final(context, _digest);

			_result.clear();
			_result.shrink_to_fit();

			static char Hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

			for (auto & iter : _digest)
			{
				_result += Hex[(iter >> 4) & 0x0F];
				_result += Hex[(iter >> 0) & 0x0F];
			}
		}

		/**
		 *
		 * 完成
		 *
		 * @param context 上下文
		 * @param digest 摘要
		 *
		 */
		void MD5::Final(Context & context, uint8_t * digest)
		{
			static uint8_t PadTable[64] =
			{
				0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
			};

			static auto Encode = [](const uint32_t * input, uint8_t * output, std::size_t length)
			{
				std::size_t i = 0;
				std::size_t j = 0;

				while (j < length)
				{
					output[j + 0] = static_cast<uint8_t>((input[i] >> 0) & 0xFF);
					output[j + 1] = static_cast<uint8_t>((input[i] >> 8) & 0xFF);
					output[j + 2] = static_cast<uint8_t>((input[i] >> 16) & 0xFF);
					output[j + 3] = static_cast<uint8_t>((input[i] >> 24) & 0xFF);

					i += 1;
					j += 4;
				}
			};

			uint8_t bits[8]{ 0 };

			uint32_t index = (context.count[0] >> 3) & 0x3F;
			uint32_t fill = (index < 56) ? (56 - index) : (120 - index);

			Encode(context.count, bits, 8);

			Update(context, PadTable, fill);
			Update(context, bits, 8);

			Encode(context.state, digest, 16);
		}

		/**
		 *
		 * 更新
		 *
		 * @param context 上下文
		 * @param content 内容
		 * @param length 长度
		 *
		 */
		void MD5::Update(Context & context, const uint8_t * content, std::size_t length)
		{
			std::size_t i = 0;
			std::size_t index = (context.count[0] >> 3) & 0x3F;
			std::size_t fill = 64 - index;

			context.count[0] += static_cast<uint32_t>(length << 3);
			context.count[0] &= 0xFFFFFFFF;
			context.count[1] += static_cast<uint32_t>(length >> 29);
			context.count[1] += (context.count[0] < (length << 3)) ? 1 : 0;

			if (length >= fill)
			{
				::memcpy(context.buffer + index, content, fill);

				Transform(context, context.buffer);

				for (i = fill; (i + 64) <= length; i += 64)
				{
					Transform(context, content + i);
				}

				index = 0;
			}

			::memcpy(context.buffer + index, content + i, length - i);
		}

		/**
		 *
		 * 转换
		 *
		 * @param context 上下文
		 * @param content 内容
		 *
		 */
		void MD5::Transform(Context & context, const uint8_t * content)
		{
			uint32_t X[64]{ 0 };

			uint32_t A = context.state[0];
			uint32_t B = context.state[1];
			uint32_t C = context.state[2];
			uint32_t D = context.state[3];

			static auto Decode = [](const uint8_t * input, uint32_t * output, std::size_t length)
			{
				std::size_t i = 0;
				std::size_t j = 0;

				while (j < length)
				{
					output[i] = static_cast<uint32_t>((input[j + 0] << 0) |
														(input[j + 1] << 8) |
														(input[j + 2] << 16) |
														(input[j + 3] << 24));

					i += 1;
					j += 4;
				}
			};

			Decode(content, X, 64);

			#define P(a, b, c, d, k, s, t)							\
			{														\
				(a) += ((d) ^ ((b) & ((c) ^ (d)))) + X[(k)] + (t);	\
				(a)  = (((a) << (s)) | ((a) >> (32 - (s)))) + (b);	\
			}

			P(A, B, C, D,  0,  7, 0xD76AA478)
			P(D, A, B, C,  1, 12, 0xE8C7B756)
			P(C, D, A, B,  2, 17, 0x242070DB)
			P(B, C, D, A,  3, 22, 0xC1BDCEEE)
			P(A, B, C, D,  4,  7, 0xF57C0FAF)
			P(D, A, B, C,  5, 12, 0x4787C62A)
			P(C, D, A, B,  6, 17, 0xA8304613)
			P(B, C, D, A,  7, 22, 0xFD469501)
			P(A, B, C, D,  8,  7, 0x698098D8)
			P(D, A, B, C,  9, 12, 0x8B44F7AF)
			P(C, D, A, B, 10, 17, 0xFFFF5BB1)
			P(B, C, D, A, 11, 22, 0x895CD7BE)
			P(A, B, C, D, 12,  7, 0x6B901122)
			P(D, A, B, C, 13, 12, 0xFD987193)
			P(C, D, A, B, 14, 17, 0xA679438E)
			P(B, C, D, A, 15, 22, 0x49B40821)

			#undef P

			#define P(a, b, c, d, k, s, t)							\
			{														\
				(a) += ((c) ^ ((d) & ((b) ^ (c)))) + X[(k)] + (t);	\
				(a)  = (((a) << (s)) | ((a) >> (32 - (s)))) + (b);	\
			}

			P(A, B, C, D,  1,  5, 0xF61E2562)
			P(D, A, B, C,  6,  9, 0xC040B340)
			P(C, D, A, B, 11, 14, 0x265E5A51)
			P(B, C, D, A,  0, 20, 0xE9B6C7AA)
			P(A, B, C, D,  5,  5, 0xD62F105D)
			P(D, A, B, C, 10,  9, 0x02441453)
			P(C, D, A, B, 15, 14, 0xD8A1E681)
			P(B, C, D, A,  4, 20, 0xE7D3FBC8)
			P(A, B, C, D,  9,  5, 0x21E1CDE6)
			P(D, A, B, C, 14,  9, 0xC33707D6)
			P(C, D, A, B,  3, 14, 0xF4D50D87)
			P(B, C, D, A,  8, 20, 0x455A14ED)
			P(A, B, C, D, 13,  5, 0xA9E3E905)
			P(D, A, B, C,  2,  9, 0xFCEFA3F8)
			P(C, D, A, B,  7, 14, 0x676F02D9)
			P(B, C, D, A, 12, 20, 0x8D2A4C8A)

			#undef P

			#define P(a, b, c, d, k, s, t)							\
			{														\
				(a) += ((b) ^ (c) ^ (d)) + X[(k)] + (t);			\
				(a)  = (((a) << (s)) | ((a) >> (32 - (s)))) + (b);	\
			}

			P(A, B, C, D,  5,  4, 0xFFFA3942)
			P(D, A, B, C,  8, 11, 0x8771F681)
			P(C, D, A, B, 11, 16, 0x6D9D6122)
			P(B, C, D, A, 14, 23, 0xFDE5380C)
			P(A, B, C, D,  1,  4, 0xA4BEEA44)
			P(D, A, B, C,  4, 11, 0x4BDECFA9)
			P(C, D, A, B,  7, 16, 0xF6BB4B60)
			P(B, C, D, A, 10, 23, 0xBEBFBC70)
			P(A, B, C, D, 13,  4, 0x289B7EC6)
			P(D, A, B, C,  0, 11, 0xEAA127FA)
			P(C, D, A, B,  3, 16, 0xD4EF3085)
			P(B, C, D, A,  6, 23, 0x04881D05)
			P(A, B, C, D,  9,  4, 0xD9D4D039)
			P(D, A, B, C, 12, 11, 0xE6DB99E5)
			P(C, D, A, B, 15, 16, 0x1FA27CF8)
			P(B, C, D, A,  2, 23, 0xC4AC5665)

			#undef P

			#define P(a, b, c, d, k, s, t)							\
			{														\
				(a) += ((c) ^ ((b) | ~(d))) + X[(k)] + (t);			\
				(a)  = (((a) << (s)) | ((a) >> (32 - (s)))) + (b);	\
			}

			P(A, B, C, D,  0,  6, 0xF4292244)
			P(D, A, B, C,  7, 10, 0x432AFF97)
			P(C, D, A, B, 14, 15, 0xAB9423A7)
			P(B, C, D, A,  5, 21, 0xFC93A039)
			P(A, B, C, D, 12,  6, 0x655B59C3)
			P(D, A, B, C,  3, 10, 0x8F0CCC92)
			P(C, D, A, B, 10, 15, 0xFFEFF47D)
			P(B, C, D, A,  1, 21, 0x85845DD1)
			P(A, B, C, D,  8,  6, 0x6FA87E4F)
			P(D, A, B, C, 15, 10, 0xFE2CE6E0)
			P(C, D, A, B,  6, 15, 0xA3014314)
			P(B, C, D, A, 13, 21, 0x4E0811A1)
			P(A, B, C, D,  4,  6, 0xF7537E82)
			P(D, A, B, C, 11, 10, 0xBD3AF235)
			P(C, D, A, B,  2, 15, 0x2AD7D2BB)
			P(B, C, D, A,  9, 21, 0xEB86D391)

			#undef P

			context.state[0] += A;
			context.state[1] += B;
			context.state[2] += C;
			context.state[3] += D;
		}

		/**
		 *
		 * 初始化
		 *
		 * @param context 上下文
		 *
		 */
		void MD5::Initialization(Context & context)
		{
			context.state[0] = 0x67452301;
			context.state[1] = 0xEFCDAB89;
			context.state[2] = 0x98BADCFE;
			context.state[3] = 0x10325476;
		}
	}
}
