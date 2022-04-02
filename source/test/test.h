#ifndef __TEST__TEST__H__
#define __TEST__TEST__H__


/**
 *
 * 作者: hm
 *
 * 说明: 任务
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"

#include <cstdint>


namespace tinyToolkit
{
	namespace test
	{
		class TOOLKIT_API Test
		{
		public:
			/**
			 *
			 * 构造函数
			 *
			 * @param name 名称
			 *
			 */
			explicit Test(const char * name);

			/**
			 *
			 * 析构函数
			 *
			 */
			virtual ~Test() = default;

		public:
			/**
			 *
			 * 执行失败
			 *
			 */
			void OnFailed();

			/**
			 *
			 * 是否通过
			 *
			 * @return 是否通过
			 *
			 */
			bool IsPassed() const;

			/**
			 *
			 * 失败次数
			 *
			 * @return 失败次数
			 *
			 */
			uint32_t FailedCount() const;

			/**
			 *
			 * 名称
			 *
			 * @return 名称
			 *
			 */
			const char * Name() const;

		public:
			/**
			 *
			 * 执行
			 *
			 */
			virtual void Run() = 0;

		private:
			bool _isPassed{ true };

			uint32_t _failedCount{ 0 };

			const char * _name{ nullptr };
		};
	}
}


#endif // __TEST__TEST__H__
