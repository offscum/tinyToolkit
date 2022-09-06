/**
 *
 * 作者: hm
 *
 * 说明: 实例
 *
 */


#include "case.h"
#include "util.h"
#include "console.h"

#include <chrono>


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
		Case::Case(const char * name) : _name(name)
		{

		}

		/**
		 *
		 * 执行
		 *
		 */
		void Case::Run()
		{
			for (auto & test : _tests)
			{
				Console::Instance().Info(Message()
					<< "[ RUN      ] "
					<< Name()
					<< "."
					<< test->Name()
					<< TOOLKIT_LINE_EOL);

				auto head = Timestamp();

				test->Run();

				auto used = Timestamp() - head;

				_elapsed += used;

				if (test->IsPassed())
				{
					_passedList.push_back(std::string(Name()).append(".").append(test->Name()));

					Console::Instance().Info(Message()
						<< "[       OK ] "
						<< Name()
						<< "."
						<< test->Name()
						<< " ("
						<< ElapsedTime(used)
						<< ")"
						<< TOOLKIT_LINE_EOL);
				}
				else
				{
					_failedList.push_back(std::string(Name()).append(".").append(test->Name()));

					Console::Instance().Fatal(Message()
						<< "[  FAILED  ] "
						<< Name()
						<< "."
						<< test->Name()
						<< " ("
						<< ElapsedTime(used)
						<< ")"
						<< TOOLKIT_LINE_EOL);
				}

				++_index;
			}
		}

		/**
		 *
		 * 添加任务
		 *
		 * @param test 任务
		 *
		 */
		void Case::AddTest(const std::shared_ptr<Test> & test)
		{
			_tests.push_back(test);
		}

		/**
		 *
		 * 耗时
		 *
		 * @return 耗时
		 *
		 */
		int64_t Case::Elapsed() const
		{
			return _elapsed;
		}

		/**
		 *
		 * 任务数
		 *
		 * @return 任务数
		 *
		 */
		std::size_t Case::Count() const
		{
			return _tests.size();
		}

		/**
		 *
		 * 名称
		 *
		 * @return 名称
		 *
		 */
		const char * Case::Name() const
		{
			return _name;
		}

		/**
		 *
		 * 当前任务
		 *
		 * @return 当前任务
		 *
		 */
		const std::shared_ptr<Test> & Case::CurrentTest()
		{
			return _tests[_index];
		}

		/**
		 *
		 * 失败列表
		 *
		 * @return 失败列表
		 *
		 */
		const std::vector<std::string> & Case::FailedList() const
		{
			return _failedList;
		}

		/**
		 *
		 * 通过列表
		 *
		 * @return 通过列表
		 *
		 */
		const std::vector<std::string> & Case::PassedList() const
		{
			return _passedList;
		}
	}
}
