/**
 *
 * 作者: hm
 *
 * 说明: hmac_md5
 *
 */


#include "hmac_md5.h"

#include <cstring>


namespace tinyToolkit
{
	namespace hash
	{
		const uint32_t HMAC_MD5::PAD_SIZE;
		const uint32_t HMAC_MD5::DIGEST_SIZE;


		/**
		 *
		 * 构造函数
		 *
		 */
		HMAC_MD5::HMAC_MD5()
		{
			Initialization(_context);
		}

		/**
		 *
		 * 重置
		 *
		 */
		void HMAC_MD5::Reset()
		{
			_isComputed = false;

			::memset(reinterpret_cast<void *>(_digest), 0, sizeof(_digest));
			::memset(reinterpret_cast<void *>(&_context), 0, sizeof(_context));

			_md5.Reset();

			_result.clear();
			_result.shrink_to_fit();

			Initialization(_context);
		}

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 密钥
		 *
		 */
		void HMAC_MD5::SetKey(const char * key)
		{
			if (key == nullptr)
			{
				return;
			}

			SetKey(reinterpret_cast<const uint8_t *>(key), ::strlen(key));
		}

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 密钥
		 *
		 */
		void HMAC_MD5::SetKey(const uint8_t * key)
		{
			if (key == nullptr)
			{
				return;
			}

			SetKey(key, ::strlen(reinterpret_cast<const char *>(key)));
		}

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 密钥
		 *
		 */
		void HMAC_MD5::SetKey(const std::string & key)
		{
			if (key.empty())
			{
				return;
			}

			SetKey(reinterpret_cast<const uint8_t *>(key.c_str()), key.length());
		}

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 密钥
		 * @param length 长度
		 *
		 */
		void HMAC_MD5::SetKey(const char * key, std::size_t length)
		{
			if (key == nullptr || length == 0)
			{
				return;
			}

			SetKey(reinterpret_cast<const uint8_t *>(key), length);
		}

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 密钥
		 * @param length 长度
		 *
		 */
		void HMAC_MD5::SetKey(const uint8_t * key, std::size_t length)
		{
			if (key == nullptr || length == 0)
			{
				return;
			}

			if (length > PAD_SIZE)
			{
				MD5 md5{ };

				md5.Append(key, length);

				for (uint32_t i = 0; i < PAD_SIZE; ++i)
				{
					_context.inPad[i] = md5.Digest()[i] ^ 0x36;
					_context.outPad[i] = md5.Digest()[i] ^ 0x5c;
				}
			}
			else
			{
				::memset(_context.inPad, 0x36, PAD_SIZE);
				::memset(_context.outPad, 0x5c, PAD_SIZE);

				for (std::size_t i = 0; i < length; ++i)
				{
					_context.inPad[i] = key[i] ^ 0x36;
					_context.outPad[i] = key[i] ^ 0x5c;
				}
			}

			Append(_context.inPad, PAD_SIZE);
		}

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 密钥
		 * @param length 长度
		 *
		 */
		void HMAC_MD5::SetKey(const std::string & key, std::size_t length)
		{
			if (key.empty() || length == 0)
			{
				return;
			}

			SetKey(reinterpret_cast<const uint8_t *>(key.c_str()), length);
		}

		/**
		 *
		 * 追加
		 *
		 * @param content 内容
		 *
		 */
		void HMAC_MD5::Append(const char * content)
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
		void HMAC_MD5::Append(const uint8_t * content)
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
		void HMAC_MD5::Append(const std::string & content)
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
		void HMAC_MD5::Append(const char * content, std::size_t length)
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
		void HMAC_MD5::Append(const uint8_t * content, std::size_t length)
		{
			if (content == nullptr || length == 0)
			{
				return;
			}

			_md5.Append(content, length);

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
		void HMAC_MD5::Append(const std::string & content, std::size_t length)
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
		const uint8_t * HMAC_MD5::Digest()
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
		const std::string & HMAC_MD5::Result()
		{
			Generate();

			return _result;
		}

		/**
		 *
		 * 生成
		 *
		 */
		void HMAC_MD5::Generate()
		{
			if (_isComputed)
			{
				return;
			}

			_isComputed = true;

			MD5 md5{ };

			md5.Append(_context.outPad, PAD_SIZE);
			md5.Append(_md5.Digest(), DIGEST_SIZE);

			::memcpy(_digest, md5.Digest(), DIGEST_SIZE);

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
		 * 初始化
		 *
		 * @param context 上下文
		 *
		 */
		void HMAC_MD5::Initialization(Context & context)
		{
			::memset(context.inPad, 0x36, PAD_SIZE);
			::memset(context.outPad, 0x5c, PAD_SIZE);
		}
	}
}
