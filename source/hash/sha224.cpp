/**
 *
 * 作者: hm
 *
 * 说明: sha224
 *
 */


#include "sha224.h"

#include <cstring>


namespace tinyToolkit
{
	namespace hash
	{
		const uint32_t SHA224::BLOCK_SIZE;
		const uint32_t SHA224::DIGEST_SIZE;


		/**
		 *
		 * 构造函数
		 *
		 */
		SHA224::SHA224()
		{
			Initialization(_context);
		}

		/**
		 *
		 * 重置
		 *
		 */
		void SHA224::Reset()
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
		void SHA224::Append(const char * content)
		{
			if (content == nullptr)
			{
				return;
			}

			Append(reinterpret_cast<const uint8_t *>(content), ::strlen(content));
		}

		/**
		 *
		 * 追加
		 *
		 * @param content 内容
		 *
		 */
		void SHA224::Append(const uint8_t * content)
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
		void SHA224::Append(const std::string & content)
		{
			if (content.empty())
			{
				return;
			}

			Append(reinterpret_cast<const uint8_t *>(content.c_str()), content.length());
		}

		/**
		 *
		 * 追加
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 */
		void SHA224::Append(const char * content, std::size_t length)
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
		void SHA224::Append(const uint8_t * content, std::size_t length)
		{
			if (content == nullptr || length == 0)
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
		void SHA224::Append(const std::string & content, std::size_t length)
		{
			if (content.empty() || length == 0)
			{
				return;
			}

			Append(reinterpret_cast<const uint8_t *>(content.c_str()), length);
		}

		/**
		 *
		 * 摘要
		 *
		 * @return 摘要
		 *
		 */
		const uint8_t * SHA224::Digest()
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
		const std::string & SHA224::Result()
		{
			Generate();

			return _result;
		}

		/**
		 *
		 * 生成
		 *
		 */
		void SHA224::Generate()
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

			static char Hex[16]{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

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
		void SHA224::Final(Context & context, uint8_t * digest)
		{
			#define UNPACK_32(x, str)							\
			{													\
				*((str) + 3) = static_cast<uint8_t>((x));		\
				*((str) + 2) = static_cast<uint8_t>((x) >> 8);	\
				*((str) + 1) = static_cast<uint8_t>((x) >> 16);	\
				*((str) + 0) = static_cast<uint8_t>((x) >> 24);	\
			}

			uint32_t totalLength = (context.totalLength + context.blockLength) << 3;
			uint32_t blockNumber = (1 + ((BLOCK_SIZE - 9) < (context.blockLength % BLOCK_SIZE) ? 1 : 0));
			uint32_t blockLength = blockNumber << 6;

			::memset(&context.block[context.blockLength], 0, blockLength - context.blockLength);

			context.block[context.blockLength] = 0x80;

			UNPACK_32(totalLength, context.block + blockLength - 4)

			Transform(context, context.block, blockNumber);

			for (int32_t i = 0 ; i < 7; i++)
			{
				UNPACK_32(context.hash[i], digest + (i << 2))
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
		void SHA224::Update(Context & context, const uint8_t * content, uint32_t length)
		{
			uint32_t fill = BLOCK_SIZE - context.blockLength;

			if (fill > length)
			{
				fill = length;
			}

			::memcpy(&context.block[context.blockLength], content, fill);

			if ((context.blockLength + length) < BLOCK_SIZE)
			{
				context.blockLength += length;

				return;
			}

			uint32_t overLength = length - fill;
			uint32_t blockNumber = overLength / BLOCK_SIZE;

			const uint8_t * overValue = content + fill;

			Transform(context, context.block, 1);
			Transform(context, overValue, blockNumber);

			fill = overLength % BLOCK_SIZE;

			::memcpy(context.block, &overValue[blockNumber << 6], fill);

			context.blockLength = fill;
			context.totalLength += (blockNumber + 1) << 6;
		}

		/**
		 *
		 * 转换
		 *
		 * @param context 上下文
		 * @param block 块
		 * @param number 个数
		 *
		 */
		void SHA224::Transform(Context & context, const uint8_t * block, uint32_t number)
		{
			#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
			#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

			#define SHF_R(x, n) ((x) >> (n))
			#define ROT_R(x, n) (((x) >> (n)) | ((x) << ((sizeof(x) << 3) - (n))))

			#define PACK_32(str, x)										\
			{															\
				*(x) =	(static_cast<uint32_t>(*((str) + 3))) |			\
						(static_cast<uint32_t>(*((str) + 2)) << 8) |	\
						(static_cast<uint32_t>(*((str) + 1)) << 16) |	\
						(static_cast<uint32_t>(*((str) + 0)) << 24);	\
			}

			#define SHA224_F1(x) (ROT_R(x, 2) ^ ROT_R(x, 13) ^ ROT_R(x, 22))
			#define SHA224_F2(x) (ROT_R(x, 6) ^ ROT_R(x, 11) ^ ROT_R(x, 25))
			#define SHA224_F3(x) (ROT_R(x, 7) ^ ROT_R(x, 18) ^ SHF_R(x, 3))
			#define SHA224_F4(x) (ROT_R(x, 17) ^ ROT_R(x, 19) ^ SHF_R(x, 10))

			#define SHA224_SCR(i)									\
			{														\
				Y[(i)]	= SHA224_F4(Y[(i) - 2]) + Y[(i) - 7]		\
						+ SHA224_F3(Y[(i) - 15]) + Y[(i) - 16];		\
			}

			static uint32_t SHA224_KEY[64]
			{
				0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
				0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
				0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
				0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
				0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC,
				0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
				0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7,
				0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
				0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
				0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
				0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3,
				0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
				0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5,
				0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
				0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
				0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
			};

			uint32_t X[8]{ 0 };
			uint32_t Y[64]{ 0 };

			for (uint32_t i = 0; i < number; i++)
			{
				const uint8_t * blockValue = block + (i << 6);

				for (int32_t j = 0; j < 16; j++)
				{
					PACK_32(&blockValue[j << 2], &Y[j])
				}

				for (int32_t j = 16; j < 64; j++)
				{
					SHA224_SCR(j)
				}

				for (int32_t j = 0; j < 8; j++)
				{
					X[j] = context.hash[j];
				}

				for (int32_t j = 0; j < 64; j++)
				{
					uint32_t t1 = X[7] + SHA224_F2(X[4]) + CH(X[4], X[5], X[6]) + SHA224_KEY[j] + Y[j];
					uint32_t t2 = SHA224_F1(X[0]) + MAJ(X[0], X[1], X[2]);

					X[7] = X[6];
					X[6] = X[5];
					X[5] = X[4];
					X[4] = X[3] + t1;
					X[3] = X[2];
					X[2] = X[1];
					X[1] = X[0];
					X[0] = t1 + t2;
				}

				for (int32_t j = 0; j < 8; j++)
				{
					context.hash[j] += X[j];
				}
			}
		}

		/**
		 *
		 * 初始化
		 *
		 * @param context 上下文
		 *
		 */
		void SHA224::Initialization(Context & context)
		{
			context.hash[0] = 0xC1059ED8;
			context.hash[1] = 0x367CD507;
			context.hash[2] = 0x3070DD17;
			context.hash[3] = 0xF70E5939;
			context.hash[4] = 0xFFC00B31;
			context.hash[5] = 0x68581511;
			context.hash[6] = 0x64F98FA7;
			context.hash[7] = 0xBEFA4FA4;
		}
	}
}
