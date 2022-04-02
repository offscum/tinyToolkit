/**
 *
 * 作者: hm
 *
 * 说明: 单元
 *
 */


#include "unit.h"
#include "console.h"


namespace tinyToolkit
{
	namespace test
	{
		/**
		 *
		 * 单例对象
		 *
		 * @return 单例对象
		 *
		 */
		Unit & Unit::Instance()
		{
			static Unit instance{ };

			return instance;
		}

		/**
		 *
		 * 运行
		 *
		 */
		int32_t Unit::Run()
		{
			Console::Instance().Info(Message()
				<< "[==========] Running "
				<< _testCount
				<< (_testCount > 1 ? " tests" : " test")
				<< " from "
				<< _cases.size()
				<< " test "
				<< (_cases.size() > 1 ? "cases" : "case")
				<< TOOLKIT_LINE_EOL);

			Console::Instance().Info(Message()
				<< "[----------] Global test environment set-up"
				<< TOOLKIT_LINE_EOL
				<< TOOLKIT_LINE_EOL);

			for (auto & environment : _environments)
			{
				environment->SetUp();
			}

			int64_t elapsed = 0;

			std::vector<std::string> failedList{ };
			std::vector<std::string> passedList{ };

			for (auto & iter : _cases)
			{
				Console::Instance().Info(Message()
					<< "[----------] "
					<< iter->Count()
					<< (iter->Count() > 1 ? " tests" : " test")
					<< " from "
					<< iter->Name()
					<< TOOLKIT_LINE_EOL);

				iter->Run();

				Console::Instance().Info(Message()
					<< "[----------] "
					<< iter->Count()
					<< (iter->Count() > 1 ? " tests" : " test")
					<< " from "
					<< iter->Name()
					<< " (" << iter->Elapsed()
					<< " ms total)"
					<< TOOLKIT_LINE_EOL
					<< TOOLKIT_LINE_EOL);

				failedList.insert(failedList.end(), iter->FailedList().begin(), iter->FailedList().end());
				passedList.insert(passedList.end(), iter->PassedList().begin(), iter->PassedList().end());

				elapsed += iter->Elapsed();

				++_index;
			}

			for (auto & environment : _environments)
			{
				environment->TearDown();
			}

			Console::Instance().Info(Message()
				<< "[----------] Global test environment tear-down"
				<< TOOLKIT_LINE_EOL);

			Console::Instance().Info(Message()
				<< "[==========] "
				<< _testCount
				<< (_testCount > 1 ? " tests" : " test")
				<< " from "
				<< _cases.size()
				<< " test "
				<< (_cases.size() > 1 ? "cases" : "case")
				<< " ran ("
				<< elapsed
				<< " ms total)"
				<< TOOLKIT_LINE_EOL);

			Console::Instance().Info(Message()
				<< "[  PASSED  ] "
				<< passedList.size()
				<< (passedList.size() > 1 ? " tests" : " test")
				<< TOOLKIT_LINE_EOL);

			if (!failedList.empty())
			{
				Console::Instance().Fatal(Message()
					<< "[  FAILED  ] "
					<< failedList.size()
					<< (failedList.size() > 1 ? " tests" : " test")
					<< ", listed below:"
					<< TOOLKIT_LINE_EOL);

				for (auto & iter : failedList)
				{
					Console::Instance().Fatal(Message()
						<< "[  FAILED  ] "
						<< iter
						<< TOOLKIT_LINE_EOL);
				}
			}

			return failedList.empty() ? 0 : 1;
		}

		/**
		 *
		 * 当前实例
		 *
		 * @return 当前实例
		 *
		 */
		const std::shared_ptr<Case> & Unit::CurrentCase()
		{
			return _cases[_index];
		}
	}
}
