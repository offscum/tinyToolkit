#ifndef __HASH__SHA224__H__
#define __HASH__SHA224__H__


/**
 *
 * 作者: hm
 *
 * 说明: sha224
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"

#include <string>
#include <cstdint>


namespace tinyToolkit
{
	namespace hash
	{
		class TOOLKIT_API SHA224
		{
			static const uint32_t BLOCK_SIZE = 64;
			static const uint32_t DIGEST_SIZE = 28;

			typedef struct Context
			{
				uint8_t block[2 * BLOCK_SIZE]{ 0 };

				uint32_t hash[8]{ 0 };

				uint32_t totalLength{ 0 };
				uint32_t blockLength{ 0 };
			}Context;

		public:
			/**
			 *
			 * 构造函数
			 *
			 */
			SHA224();

		public:
			/**
			 *
			 * 重置
			 *
			 */
			void Reset();

			/**
			 *
			 * 追加
			 *
			 * @param content 内容
			 *
			 */
			void Append(const char * content);

			/**
			 *
			 * 追加
			 *
			 * @param content 内容
			 *
			 */
			void Append(const uint8_t * content);

			/**
			 *
			 * 追加
			 *
			 * @param content 内容
			 *
			 */
			void Append(const std::string & content);

			/**
			 *
			 * 追加
			 *
			 * @param content 内容
			 * @param length 长度
			 *
			 */
			void Append(const char * content, std::size_t length);

			/**
			 *
			 * 追加
			 *
			 * @param content 内容
			 * @param length 长度
			 *
			 */
			void Append(const uint8_t * content, std::size_t length);

			/**
			 *
			 * 追加
			 *
			 * @param content 内容
			 * @param length 长度
			 *
			 */
			void Append(const std::string & content, std::size_t length);

			/**
			 *
			 * 摘要
			 *
			 * @return 摘要
			 *
			 */
			const uint8_t * Digest();

			/**
			 *
			 * 摘要
			 *
			 * @return 摘要
			 *
			 */
			const std::string & Result();

		private:
			/**
			 *
			 * 生成
			 *
			 */
			void Generate();

			/**
			 *
			 * 完成
			 *
			 * @param context 上下文
			 * @param digest 摘要
			 *
			 */
			static void Final(Context & context, uint8_t * digest);

			/**
			 *
			 * 更新
			 *
			 * @param context 上下文
			 * @param content 内容
			 * @param length 长度
			 *
			 */
			static void Update(Context & context, const uint8_t * content, uint32_t length);

			/**
			 *
			 * 转换
			 *
			 * @param context 上下文
			 * @param block 块
			 * @param number 个数
			 *
			 */
			static void Transform(Context & context, const uint8_t * block, uint32_t number);

			/**
			 *
			 * 初始化
			 *
			 * @param context 上下文
			 *
			 */
			static void Initialization(Context & context);

		private:
			bool _isComputed{ false };

			uint8_t _digest[DIGEST_SIZE]{ 0 };

			Context _context{ };

			std::string _result{ };
		};
	}
}


#endif // __HASH__SHA224__H__
