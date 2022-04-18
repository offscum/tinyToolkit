/**
 *
 * 作者: hm
 *
 * 说明: sha1
 *
 */


#include "sha1.h"

#include <cstring>


namespace tinyToolkit
{
	namespace hash
	{
		const uint32_t SHA1::BLOCK_SIZE;
		const uint32_t SHA1::DIGEST_SIZE;


		/**
		 *
		 * 构造函数
		 *
		 */
		SHA1::SHA1()
		{
			Initialization(_context);
		}

		/**
		 *
		 * 重置
		 *
		 */
		void SHA1::Reset()
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
		void SHA1::Append(const char * content)
		{
			if (content == nullptr || _context.isCorrupted)
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
		void SHA1::Append(const uint8_t * content)
		{
			if (content == nullptr || _context.isCorrupted)
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
		void SHA1::Append(const std::string & content)
		{
			if (content.empty() || _context.isCorrupted)
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
		void SHA1::Append(const char * content, std::size_t length)
		{
			if (content == nullptr || length == 0 || _context.isCorrupted)
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
		void SHA1::Append(const uint8_t * content, std::size_t length)
		{
			if (content == nullptr || length == 0 || _context.isCorrupted)
			{
				return;
			}

			Update(_context, content, static_cast<uint32_t>(length));

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
		void SHA1::Append(const std::string & content, std::size_t length)
		{
			if (content.empty() || length == 0 || _context.isCorrupted)
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
		const uint8_t * SHA1::Digest()
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
		const std::string & SHA1::Result()
		{
			Generate();

			return _result;
		}

		/**
		 *
		 * 生成
		 *
		 */
		void SHA1::Generate()
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
		void SHA1::Final(Context & context, uint8_t * digest)
		{
			Padding(context);

			for (uint32_t i = 0; i < DIGEST_SIZE; ++i)
			{
				digest[i] = static_cast<uint8_t>(context.hash[i >> 2] >> (8 * (3 - (i & 0x03))));
			}
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
		void SHA1::Update(Context & context, const uint8_t * content, uint32_t length)
		{
			while (length-- && !context.isCorrupted)
			{
				context.block[context.blockIndex++] = (*content & 0xFF);

				context.lengthLow += 8;
				context.lengthLow &= 0xFFFFFFFF;

				if (context.lengthLow == 0)
				{
					context.lengthHigh += 1;
					context.lengthHigh &= 0xFFFFFFFF;

					if (context.lengthHigh == 0)
					{
						context.isCorrupted = true;
					}
				}

				if (context.blockIndex == 64)
				{
					Transform(context);
				}

				++content;
			}
		}

		/**
		 *
		 * 填充
		 *
		 * @param context 上下文
		 *
		 */
		void SHA1::Padding(Context & context)
		{
			if (context.blockIndex > 55)
			{
				context.block[context.blockIndex++] = 0x80;

				while (context.blockIndex < 64)
				{
					context.block[context.blockIndex++] = 0;
				}

				Transform(context);

				while (context.blockIndex < 56)
				{
					context.block[context.blockIndex++] = 0;
				}
			}
			else
			{
				context.block[context.blockIndex++] = 0x80;

				while (context.blockIndex < 56)
				{
					context.block[context.blockIndex++] = 0;
				}
			}

			context.block[56] = static_cast<uint8_t>(context.lengthHigh >> 24);
			context.block[57] = static_cast<uint8_t>(context.lengthHigh >> 16);
			context.block[58] = static_cast<uint8_t>(context.lengthHigh >> 8);
			context.block[59] = static_cast<uint8_t>(context.lengthHigh);
			context.block[60] = static_cast<uint8_t>(context.lengthLow >> 24);
			context.block[61] = static_cast<uint8_t>(context.lengthLow >> 16);
			context.block[62] = static_cast<uint8_t>(context.lengthLow >> 8);
			context.block[63] = static_cast<uint8_t>(context.lengthLow);

			Transform(context);
		}

		/**
		 *
		 * 转换
		 *
		 * @param context 上下文
		 *
		 */
		void SHA1::Transform(Context & context)
		{
			static uint32_t SHA1_KEY[4] = { 0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6 };

			#define CIRCULAR_SHIFT(bits, word) (((word) << (bits)) | ((word) >> (32 - (bits))))

			uint32_t W[80]{ 0 };

			for (int32_t t = 0; t < 16; t++)
			{
				W[t]  = static_cast<uint32_t>(context.block[t * 4 + 0] << 24);
				W[t] |= static_cast<uint32_t>(context.block[t * 4 + 1] << 16);
				W[t] |= static_cast<uint32_t>(context.block[t * 4 + 2] << 8);
				W[t] |= static_cast<uint32_t>(context.block[t * 4 + 3]);
			}

			for (int32_t t = 16; t < 80; t++)
			{
				W[t] = CIRCULAR_SHIFT(1, W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16]);
			}

			uint32_t A = context.hash[0];
			uint32_t B = context.hash[1];
			uint32_t C = context.hash[2];
			uint32_t D = context.hash[3];
			uint32_t E = context.hash[4];

			for (int32_t t = 0; t < 20; t++)
			{
				uint32_t temp = CIRCULAR_SHIFT(5, A) + ((B & C) | ((~B) & D)) + E + W[t] + SHA1_KEY[0];

				E = D;
				D = C;
				C = CIRCULAR_SHIFT(30, B);
				B = A;
				A = temp;
			}

			for (int32_t t = 20; t < 40; t++)
			{
				uint32_t temp = CIRCULAR_SHIFT(5, A) + (B ^ C ^ D) + E + W[t] + SHA1_KEY[1];

				E = D;
				D = C;
				C = CIRCULAR_SHIFT(30, B);
				B = A;
				A = temp;
			}

			for (int32_t t = 40; t < 60; t++)
			{
				uint32_t temp = CIRCULAR_SHIFT(5, A) + ((B & C) | (B & D) | (C & D)) + E + W[t] + SHA1_KEY[2];

				E = D;
				D = C;
				C = CIRCULAR_SHIFT(30, B);
				B = A;
				A = temp;
			}

			for (int32_t t = 60; t < 80; t++)
			{
				uint32_t temp = CIRCULAR_SHIFT(5, A) + (B ^ C ^ D) + E + W[t] + SHA1_KEY[3];

				E = D;
				D = C;
				C = CIRCULAR_SHIFT(30, B);
				B = A;
				A = temp;
			}

			context.hash[0] += A;
			context.hash[1] += B;
			context.hash[2] += C;
			context.hash[3] += D;
			context.hash[4] += E;

			context.blockIndex = 0;
		}

		/**
		 *
		 * 初始化
		 *
		 * @param context 上下文
		 *
		 */
		void SHA1::Initialization(Context & context)
		{
			context.hash[0] = 0x67452301;
			context.hash[1] = 0xEFCDAB89;
			context.hash[2] = 0x98BADCFE;
			context.hash[3] = 0x10325476;
			context.hash[4] = 0xC3D2E1F0;
		}
	}
}
