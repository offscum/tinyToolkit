#ifndef __TEST__UNIT__H__
#define __TEST__UNIT__H__


/**
 *
 * 作者: hm
 *
 * 说明: 单元
 *
 */


#include "case.h"
#include "environment.h"

#include <algorithm>


namespace tinyToolkit
{
	namespace test
	{
		class TOOLKIT_API Unit
		{
		public:
			/**
			 *
			 * 单例对象
			 *
			 * @return 单例对象
			 *
			 */
			static Unit & Instance();

		public:
			/**
			 *
			 * 添加环境
			 *
			 */
			template <typename EnvironmentType>
			void AddEnvironment()
			{
				_environments.push_back(std::make_shared<EnvironmentType>());
			}

			/**
			 *
			 * 添加任务
			 *
			 * @param caseName 实例名称
			 * @param testName 任务名称
			 *
			 * @return 实例
			 *
			 */
			template <typename TestType>
			const std::shared_ptr<Case> & AddTest(const char * caseName, const char * testName)
			{
				auto find = std::find_if(_cases.begin(), _cases.end(), [caseName](const std::shared_ptr<Case> & obj)
				{
					return obj->Name() == caseName;
				});

				if (find == _cases.end())
				{
					_cases.push_back(std::make_shared<Case>(caseName));

					find = std::prev(_cases.end());
				}

				++_testCount;

				(*find)->AddTest(std::make_shared<TestType>(testName));

				return *find;
			}

		public:
			/**
			 *
			 * 运行
			 *
			 * @return 结果
			 *
			 */
			int32_t Run();

			/**
			 *
			 * 当前实例
			 *
			 * @return 当前实例
			 *
			 */
			const std::shared_ptr<Case> & CurrentCase();

		private:
			/**
			 *
			 * 构造函数
			 *
			 */
			Unit() = default;

			/**
			 *
			 * 析构函数
			 *
			 */
			~Unit() = default;

		private:
			std::size_t _index{ 0 };
			std::size_t _testCount{ 0 };

			std::vector<std::shared_ptr<Case>> _cases{ };

			std::vector<std::shared_ptr<Environment>> _environments{ };
		};

		/**
		 *
		 * 添加环境
		 *
		 */
		template <typename EnvironmentType>
		void AddEnvironment()
		{
			Unit::Instance().AddEnvironment<EnvironmentType>();
		}

		/**
		 *
		 * 添加任务
		 *
		 * @param caseName 实例名称
		 * @param testName 任务名称
		 *
		 * @return 实例
		 *
		 */
		template <typename TestType>
		const std::shared_ptr<Case> & AddTest(const char * caseName, const char * testName)
		{
			return Unit::Instance().AddTest<TestType>(caseName, testName);
		}
	}
}


#define TOOLKIT_TEST_RUN() \
	tinyToolkit::test::Unit::Instance().Run()

#define TOOLKIT_TEST_CASE(caseName, testName) \
	TOOLKIT_TEST_CLASS_DECLARE(caseName, testName, tinyToolkit::test::Test)

#define TOOLKIT_TEST_SELF(caseName, testName) \
	TOOLKIT_TEST_CLASS_DECLARE(caseName, testName, caseName)

#define TOOLKIT_TEST_CLASS_NAME(caseName, testName) \
	caseName##testName##Test

#define TOOLKIT_TEST_CLASS_DECLARE(caseName, testName, parent)																																		\
	class TOOLKIT_TEST_CLASS_NAME(caseName, testName) final : public parent																															\
	{																																																\
	public:																																															\
		explicit TOOLKIT_TEST_CLASS_NAME(caseName, testName)(const char * name) : parent(name)																										\
		{																																															\
																																																	\
		};																																															\
																																																	\
		~TOOLKIT_TEST_CLASS_NAME(caseName, testName)() override = default;																															\
																																																	\
	private:																																														\
		void Run() override;																																										\
																																																	\
	private:																																														\
		static std::shared_ptr<tinyToolkit::test::Case> _case;																																		\
	};																																																\
																																																	\
	std::shared_ptr<tinyToolkit::test::Case> TOOLKIT_TEST_CLASS_NAME(caseName, testName)::_case = tinyToolkit::test::AddTest<TOOLKIT_TEST_CLASS_NAME(caseName, testName)>(#caseName, #testName);	\
																																																	\
	void TOOLKIT_TEST_CLASS_NAME(caseName, testName)::Run()


#endif // __TEST__UNIT__H__
