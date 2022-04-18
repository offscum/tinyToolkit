#ifndef __ID__UNIQUE__H__
#define __ID__UNIQUE__H__


/**
 *
 * 作者: hm
 *
 * 说明: 全局唯一标识码
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"

#include <cstdint>


namespace tinyToolkit
{
	namespace id
	{
		class TOOLKIT_API Unique
		{
			union TOOLKIT_API Context
			{
				uint64_t value{ 0 };

				struct KEY
				{
					uint32_t count;
					uint32_t timestamp;
				}key;
			};

		public:
			/**
			 *
			 * 构造函数
			 *
			 */
			Unique();

		public:
			/**
			 *
			 * 生成
			 *
			 * @return 唯一标识码
			 *
			 */
			uint64_t Generate();

		private:
			Context _context{ };
		};
	}
}


#endif // __ID__UNIQUE__H__
