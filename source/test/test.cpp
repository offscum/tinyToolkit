/**
 *
 * 作者: hm
 *
 * 说明: 任务
 *
 */


#include "test.h"


namespace tinyToolkit
{
	namespace test
	{
		/**
		 *
		 * 构造函数
		 *
		 * @param name 名称
		 *
		 */
		Test::Test(const char * name) : _name(name)
		{

		}

		/**
		 *
		 * 执行失败
		 *
		 */
		void Test::OnFailed()
		{
			++_failedCount;

			_isPassed = false;
		}

		/**
		 *
		 * 是否通过
		 *
		 * @return 是否通过
		 *
		 */
		bool Test::IsPassed() const
		{
			return _isPassed;
		}

		/**
		 *
		 * 失败次数
		 *
		 * @return 失败次数
		 *
		 */
		uint32_t Test::FailedCount() const
		{
			return _failedCount;
		}

		/**
		 *
		 * 名称
		 *
		 * @return 名称
		 *
		 */
		const char * Test::Name() const
		{
			return _name;
		}
	}
}
