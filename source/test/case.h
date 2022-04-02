#ifndef __TEST__CASE__H__
#define __TEST__CASE__H__


/**
 *
 * 作者: hm
 *
 * 说明: 实例
 *
 */


#include "test.h"

#include <memory>
#include <vector>
#include <string>


namespace tinyToolkit
{
	namespace test
	{
		class TOOLKIT_API Case
		{
		public:
			/**
			 *
			 * 构造函数
			 *
			 * @param name 名称
			 *
			 */
			explicit Case(const char * name);

			/**
			 *
			 * 析构函数
			 *
			 */
			virtual ~Case() = default;

		public:
			/**
			 *
			 * 执行
			 *
			 */
			void Run();

			/**
			 *
			 * 添加任务
			 *
			 * @param test 任务
			 *
			 */
			void AddTest(const std::shared_ptr<Test> & test);

			/**
			 *
			 * 耗时
			 *
			 * @return 耗时
			 *
			 */
			int64_t Elapsed() const;

			/**
			 *
			 * 任务数
			 *
			 * @return 任务数
			 *
			 */
			std::size_t Count() const;

			/**
			 *
			 * 名称
			 *
			 * @return 名称
			 *
			 */
			const char * Name() const;

			/**
			 *
			 * 当前任务
			 *
			 * @return 当前任务
			 *
			 */
			const std::shared_ptr<Test> & CurrentTest();

			/**
			 *
			 * 失败列表
			 *
			 * @return 失败列表
			 *
			 */
			const std::vector<std::string> & FailedList() const;

			/**
			 *
			 * 通过列表
			 *
			 * @return 通过列表
			 *
			 */
			const std::vector<std::string> & PassedList() const;

		private:
			int64_t _elapsed{ 0 };

			std::size_t _index{ 0 };

			const char * _name{ nullptr };

			std::vector<std::string> _failedList{ };
			std::vector<std::string> _passedList{ };

			std::vector<std::shared_ptr<Test>> _tests{ };
		};
	}
}


#endif // __TEST__CASE__H__
