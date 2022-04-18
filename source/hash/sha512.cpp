/**
 *
 * 作者: hm
 *
 * 说明: sha512
 *
 */


#include "sha512.h"

#include <cstring>


namespace tinyToolkit
{
	namespace hash
	{
		const uint32_t SHA512::BLOCK_SIZE;
		const uint32_t SHA512::DIGEST_SIZE;


		/**
		 *
		 * 构造函数
		 *
		 */
		SHA512::SHA512()
		{
			Initialization(_context);
		}

		/**
		 *
		 * 重置
		 *
		 */
		void SHA512::Reset()
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
		void SHA512::Append(const char * content)
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
		void SHA512::Append(const uint8_t * content)
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
		void SHA512::Append(const std::string & content)
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
		void SHA512::Append(const char * content, std::size_t length)
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
		void SHA512::Append(const uint8_t * content, std::size_t length)
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
		void SHA512::Append(const std::string & content, std::size_t length)
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
		const uint8_t * SHA512::Digest()
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
		const std::string & SHA512::Result()
		{
			Generate();

			return _result;
		}

		/**
		 *
		 * 生成
		 *
		 */
		void SHA512::Generate()
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
		void SHA512::Final(Context & context, uint8_t * digest)
		{
			#define UNPACK_32(x, str)							\
			{													\
				*((str) + 3) = static_cast<uint8_t>((x));		\
				*((str) + 2) = static_cast<uint8_t>((x) >> 8);	\
				*((str) + 1) = static_cast<uint8_t>((x) >> 16);	\
				*((str) + 0) = static_cast<uint8_t>((x) >> 24);	\
			}

			#define UNPACK_64(x, str)							\
			{													\
				*((str) + 7) = static_cast<uint8_t>((x));		\
				*((str) + 6) = static_cast<uint8_t>((x) >> 8);	\
				*((str) + 5) = static_cast<uint8_t>((x) >> 16);	\
				*((str) + 4) = static_cast<uint8_t>((x) >> 24);	\
				*((str) + 3) = static_cast<uint8_t>((x) >> 32);	\
				*((str) + 2) = static_cast<uint8_t>((x) >> 40);	\
				*((str) + 1) = static_cast<uint8_t>((x) >> 48);	\
				*((str) + 0) = static_cast<uint8_t>((x) >> 56);	\
			}

			uint32_t totalLength = (context.totalLength + context.blockLength) << 3;
			uint32_t blockNumber = (1 + ((BLOCK_SIZE - 17) < (context.blockLength % BLOCK_SIZE) ? 1 : 0));
			uint32_t blockLength = blockNumber << 7;

			::memset(&context.block[context.blockLength], 0, blockLength - context.blockLength);

			context.block[context.blockLength] = 0x80;

			UNPACK_32(totalLength, context.block + blockLength - 4)

			Transform(context, context.block, blockNumber);

			for (int32_t i = 0 ; i < 8; i++)
			{
				UNPACK_64(context.hash[i], &digest[i << 3])
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
		void SHA512::Update(Context & context, const uint8_t * content, uint32_t length)
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

			::memcpy(context.block, &overValue[blockNumber << 7], fill);

			context.blockLength = fill;
			context.totalLength += (blockNumber + 1) << 7;
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
		void SHA512::Transform(Context & context, const uint8_t * block, uint32_t number)
		{
			#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
			#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

			#define SHF_R(x, n) ((x) >> (n))
			#define ROT_R(x, n) (((x) >> (n)) | ((x) << ((sizeof(x) << 3) - (n))))

			#define PACK_64(str, x)										\
			{															\
				*(x) =	(static_cast<uint64_t>(*((str) + 7))) |			\
						(static_cast<uint64_t>(*((str) + 6)) << 8) |	\
						(static_cast<uint64_t>(*((str) + 5)) << 16) |	\
						(static_cast<uint64_t>(*((str) + 4)) << 24) |	\
						(static_cast<uint64_t>(*((str) + 3)) << 32) |	\
						(static_cast<uint64_t>(*((str) + 2)) << 40) |	\
						(static_cast<uint64_t>(*((str) + 1)) << 48) |	\
						(static_cast<uint64_t>(*((str) + 0)) << 56);	\
			}

			#define SHA512_F1(x) (ROT_R(x, 28) ^ ROT_R(x, 34) ^ ROT_R(x, 39))
			#define SHA512_F2(x) (ROT_R(x, 14) ^ ROT_R(x, 18) ^ ROT_R(x, 41))
			#define SHA512_F3(x) (ROT_R(x, 1) ^ ROT_R(x, 8) ^ SHF_R(x, 7))
			#define SHA512_F4(x) (ROT_R(x, 19) ^ ROT_R(x, 61) ^ SHF_R(x, 6))

			#define SHA512_SCR(i)									\
			{														\
				Y[(i)]	= SHA512_F4(Y[(i) - 2]) + Y[(i) - 7]		\
						+ SHA512_F3(Y[(i) - 15]) + Y[(i) - 16];		\
			}

			static uint64_t SHA512_KEY[80] =
			{
				0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL, 0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL,
				0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL, 0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL,
				0xd807aa98a3030242ULL, 0x12835b0145706fbeULL, 0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL,
				0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL, 0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL,
				0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL, 0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
				0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL, 0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL,
				0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL, 0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL,
				0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL, 0x06ca6351e003826fULL, 0x142929670a0e6e70ULL,
				0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL, 0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL,
				0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL, 0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
				0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL, 0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL,
				0xd192e819d6ef5218ULL, 0xd69906245565a910ULL, 0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL,
				0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL, 0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL,
				0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL, 0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL,
				0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL, 0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
				0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL, 0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL,
				0xca273eceea26619cULL, 0xd186b8c721c0c207ULL, 0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL,
				0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL, 0x113f9804bef90daeULL, 0x1b710b35131c471bULL,
				0x28db77f523047d84ULL, 0x32caab7b40c72493ULL, 0x3c9ebe0a15c9bebcULL, 0x431d67c49c100d4cULL,
				0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL, 0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL
			};

			uint64_t X[8]{ 0 };
			uint64_t Y[80]{ 0 };

			for (uint32_t i = 0; i < number; i++)
			{
				const uint8_t * blockValue = block + (i << 7);

				for (int32_t j = 0; j < 16; j++)
				{
					PACK_64(&blockValue[j << 3], &Y[j])
				}

				for (int32_t j = 16; j < 80; j++)
				{
					SHA512_SCR(j)
				}

				for (int32_t j = 0; j < 8; j++)
				{
					X[j] = context.hash[j];
				}

				for (int32_t j = 0; j < 80; j++)
				{
					uint64_t t1 = X[7] + SHA512_F2(X[4]) + CH(X[4], X[5], X[6]) + SHA512_KEY[j] + Y[j];
					uint64_t t2 = SHA512_F1(X[0]) + MAJ(X[0], X[1], X[2]);

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
		void SHA512::Initialization(Context & context)
		{
			context.hash[0] = 0x6a09e667f3bcc908ULL;
			context.hash[1] = 0xbb67ae8584caa73bULL;
			context.hash[2] = 0x3c6ef372fe94f82bULL;
			context.hash[3] = 0xa54ff53a5f1d36f1ULL;
			context.hash[4] = 0x510e527fade682d1ULL;
			context.hash[5] = 0x9b05688c2b3e6c1fULL;
			context.hash[6] = 0x1f83d9abfb41bd6bULL;
			context.hash[7] = 0x5be0cd19137e2179ULL;
		}
	}
}
