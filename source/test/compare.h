#ifndef __TEST__COMPARE__H__
#define __TEST__COMPARE__H__


/**
 *
 * 作者: hm
 *
 * 说明: 对比
 *
 */


#include "result.h"
#include "failure.h"


namespace tinyToolkit
{
	namespace test
	{
		class TOOLKIT_API Compare
		{
		public:
			/**
			 *
			 * 等于
			 *
			 * @param actualValue 实际值
			 * @param expectedValue 期望值
			 * @param actualExpression 实际表达式
			 * @param expectedExpression 期望表达式
			 *
			 * @return 结果
			 *
			 */
			template <typename ActualType, typename ExpectedType>
			static Result Equal(ActualType && actualValue, ExpectedType && expectedValue, const char * actualExpression, const char * expectedExpression)
			{
				if (actualValue == expectedValue)
				{
					return Result(true);
				}

				return Result(false)
					<< "Value of: " << actualExpression << TOOLKIT_LINE_EOL
					<< "  Actual: " << actualValue << TOOLKIT_LINE_EOL
					<< "Value of: " << expectedExpression << TOOLKIT_LINE_EOL
					<< "Expected: " << expectedValue << TOOLKIT_LINE_EOL;
			}

			/**
			 *
			 * 不等于
			 *
			 * @param actualValue 实际值
			 * @param expectedValue 期望值
			 * @param actualExpression 实际表达式
			 * @param expectedExpression 期望表达式
			 *
			 * @return 结果
			 *
			 */
			template <typename ActualType, typename ExpectedType>
			static Result Unequal(ActualType && actualValue, ExpectedType && expectedValue, const char * actualExpression, const char * expectedExpression)
			{
				if (actualValue != expectedValue)
				{
					return Result(true);
				}

				return Result(false)
					<< "Value of: " << actualExpression << TOOLKIT_LINE_EOL
					<< "  Actual: " << actualValue << TOOLKIT_LINE_EOL
					<< "Value of: " << expectedExpression << TOOLKIT_LINE_EOL
					<< "Expected: " << expectedValue << TOOLKIT_LINE_EOL;
			}

			/**
			 *
			 * 小于
			 *
			 * @param actualValue 实际值
			 * @param expectedValue 期望值
			 * @param actualExpression 实际表达式
			 * @param expectedExpression 期望表达式
			 *
			 * @return 结果
			 *
			 */
			template <typename ActualType, typename ExpectedType>
			static Result LessThan(ActualType && actualValue, ExpectedType && expectedValue, const char * actualExpression, const char * expectedExpression)
			{
				if (actualValue < expectedValue)
				{
					return Result(true);
				}

				return Result(false)
					<< "Value of: " << actualExpression << TOOLKIT_LINE_EOL
					<< "  Actual: " << actualValue << TOOLKIT_LINE_EOL
					<< "Value of: " << expectedExpression << TOOLKIT_LINE_EOL
					<< "Expected: " << expectedValue << TOOLKIT_LINE_EOL;
			}

			/**
			 *
			 * 小于等于
			 *
			 * @param actualValue 实际值
			 * @param expectedValue 期望值
			 * @param actualExpression 实际表达式
			 * @param expectedExpression 期望表达式
			 *
			 * @return 结果
			 *
			 */
			template <typename ActualType, typename ExpectedType>
			static Result LessThanOrEqual(ActualType && actualValue, ExpectedType && expectedValue, const char * actualExpression, const char * expectedExpression)
			{
				if (actualValue <= expectedValue)
				{
					return Result(true);
				}

				return Result(false)
					<< "Value of: " << actualExpression << TOOLKIT_LINE_EOL
					<< "  Actual: " << actualValue << TOOLKIT_LINE_EOL
					<< "Value of: " << expectedExpression << TOOLKIT_LINE_EOL
					<< "Expected: " << expectedValue << TOOLKIT_LINE_EOL;
			}

			/**
			 *
			 * 大于
			 *
			 * @param actualValue 实际值
			 * @param expectedValue 期望值
			 * @param actualExpression 实际表达式
			 * @param expectedExpression 期望表达式
			 *
			 * @return 结果
			 *
			 */
			template <typename ActualType, typename ExpectedType>
			static Result GreaterThan(ActualType && actualValue, ExpectedType && expectedValue, const char * actualExpression, const char * expectedExpression)
			{
				if (actualValue > expectedValue)
				{
					return Result(true);
				}

				return Result(false)
					<< "Value of: " << actualExpression << TOOLKIT_LINE_EOL
					<< "  Actual: " << actualValue << TOOLKIT_LINE_EOL
					<< "Value of: " << expectedExpression << TOOLKIT_LINE_EOL
					<< "Expected: " << expectedValue << TOOLKIT_LINE_EOL;
			}

			/**
			 *
			 * 大于等于
			 *
			 * @param actualValue 实际值
			 * @param expectedValue 期望值
			 * @param actualExpression 实际表达式
			 * @param expectedExpression 期望表达式
			 *
			 * @return 结果
			 *
			 */
			template <typename ActualType, typename ExpectedType>
			static Result GreaterThanOrEqual(ActualType && actualValue, ExpectedType && expectedValue, const char * actualExpression, const char * expectedExpression)
			{
				if (actualValue >= expectedValue)
				{
					return Result(true);
				}

				return Result(false)
					<< "Value of: " << actualExpression << TOOLKIT_LINE_EOL
					<< "  Actual: " << actualValue << TOOLKIT_LINE_EOL
					<< "Value of: " << expectedExpression << TOOLKIT_LINE_EOL
					<< "Expected: " << expectedValue << TOOLKIT_LINE_EOL;
			}

		public:
			/**
			 *
			 * 布尔值判断
			 *
			 * @param condition 条件
			 * @param expression 表达式
			 * @param actual 实际值
			 * @param expected 期望值
			 *
			 * @return 结果
			 *
			 */
			static Result Boolean(bool condition, const char * expression, const char * actual, const char * expected);

			/**
			 *
			 * 字符串相等
			 *
			 * @param actualValue 实际值
			 * @param expectedValue 期望值
			 * @param actualExpression 实际表达式
			 * @param expectedExpression 期望表达式
			 *
			 * @return 结果
			 *
			 */
			static Result StringEqual(const char * actualValue, const char * expectedValue, const char * actualExpression, const char * expectedExpression);

			/**
			 *
			 * 字符串相等
			 *
			 * @param actualValue 实际值
			 * @param expectedValue 期望值
			 * @param actualExpression 实际表达式
			 * @param expectedExpression 期望表达式
			 *
			 * @return 结果
			 *
			 */
			static Result StringEqual(const std::string & actualValue, const std::string & expectedValue, const char * actualExpression, const char * expectedExpression);

			/**
			 *
			 * 字符串相等
			 *
			 * @param actualValue 实际值
			 * @param expectedValue 期望值
			 * @param actualExpression 实际表达式
			 * @param expectedExpression 期望表达式
			 *
			 * @return 结果
			 *
			 */
			static Result StringUnequal(const char * actualValue, const char * expectedValue, const char * actualExpression, const char * expectedExpression);

			/**
			 *
			 * 字符串相等
			 *
			 * @param actualValue 实际值
			 * @param expectedValue 期望值
			 * @param actualExpression 实际表达式
			 * @param expectedExpression 期望表达式
			 *
			 * @return 结果
			 *
			 */
			static Result StringUnequal(const std::string & actualValue, const std::string & expectedValue, const char * actualExpression, const char * expectedExpression);

			/**
			 *
			 * 字符串相等 (忽略大小写)
			 *
			 * @param actualValue 实际值
			 * @param expectedValue 期望值
			 * @param actualExpression 实际表达式
			 * @param expectedExpression 期望表达式
			 *
			 * @return 结果
			 *
			 */
			static Result StringCaseEqual(const char * actualValue, const char * expectedValue, const char * actualExpression, const char * expectedExpression);

			/**
			 *
			 * 字符串相等 (忽略大小写)
			 *
			 * @param actualValue 实际值
			 * @param expectedValue 期望值
			 * @param actualExpression 实际表达式
			 * @param expectedExpression 期望表达式
			 *
			 * @return 结果
			 *
			 */
			static Result StringCaseEqual(const std::string & actualValue, const std::string & expectedValue, const char * actualExpression, const char * expectedExpression);

			/**
			 *
			 * 字符串不相等 (忽略大小写)
			 *
			 * @param actualValue 实际值
			 * @param expectedValue 期望值
			 * @param actualExpression 实际表达式
			 * @param expectedExpression 期望表达式
			 *
			 * @return 结果
			 *
			 */
			static Result StringCaseUnequal(const char * actualValue, const char * expectedValue, const char * actualExpression, const char * expectedExpression);

			/**
			 *
			 * 字符串不相等 (忽略大小写)
			 *
			 * @param actualValue 实际值
			 * @param expectedValue 期望值
			 * @param actualExpression 实际表达式
			 * @param expectedExpression 期望表达式
			 *
			 * @return 结果
			 *
			 */
			static Result StringCaseUnequal(const std::string & actualValue, const std::string & expectedValue, const char * actualExpression, const char * expectedExpression);
		};
	}
}


#define TOOLKIT_EXPECT_EQ(actual, expected) \
	TOOLKIT_TEST_EQ_(actual, expected, #actual, #expected)

#define TOOLKIT_EXPECT_NE(actual, expected) \
	TOOLKIT_TEST_NE_(actual, expected, #actual, #expected)

#define TOOLKIT_EXPECT_LT(actual, expected) \
	TOOLKIT_TEST_LT_(actual, expected, #actual, #expected)

#define TOOLKIT_EXPECT_LE(actual, expected) \
	TOOLKIT_TEST_LE_(actual, expected, #actual, #expected)

#define TOOLKIT_EXPECT_GT(actual, expected) \
	TOOLKIT_TEST_GT_(actual, expected, #actual, #expected)

#define TOOLKIT_EXPECT_GE(actual, expected) \
	TOOLKIT_TEST_GE_(actual, expected, #actual, #expected)

#define TOOLKIT_EXPECT_STR_EQ(actual, expected) \
	TOOLKIT_TEST_STR_EQ_(actual, expected, #actual, #expected)

#define TOOLKIT_EXPECT_STR_NE(actual, expected) \
	TOOLKIT_TEST_STR_NE_(actual, expected, #actual, #expected)

#define TOOLKIT_EXPECT_STR_CASE_EQ(actual, expected) \
	TOOLKIT_TEST_STR_CASE_EQ_(actual, expected, #actual, #expected)

#define TOOLKIT_EXPECT_STR_CASE_NE(actual, expected) \
	TOOLKIT_TEST_STR_CASE_NE_(actual, expected, #actual, #expected)

#define TOOLKIT_EXPECT_TRUE(condition) \
	TOOLKIT_TEST_BOOLEAN_((condition), #condition, false, true)

#define TOOLKIT_EXPECT_FALSE(condition) \
	TOOLKIT_TEST_BOOLEAN_(!(condition), #condition, true, false)


#define TOOLKIT_TEST_AS_(function)																							\
	if (const tinyToolkit::test::Result _resultAnonymous_ = (function))														\
		;																													\
	else																													\
		tinyToolkit::test::Failure(TOOLKIT_FILE, TOOLKIT_LINE, _resultAnonymous_.Content()) = tinyToolkit::test::Message()

#define TOOLKIT_TEST_EQ_(actualValue, expectedValue, actualExpression, expectedExpression) \
	TOOLKIT_TEST_AS_(tinyToolkit::test::Compare::Equal(actualValue, expectedValue, actualExpression, expectedExpression))

#define TOOLKIT_TEST_NE_(actualValue, expectedValue, actualExpression, expectedExpression) \
	TOOLKIT_TEST_AS_(tinyToolkit::test::Compare::Unequal(actualValue, expectedValue, actualExpression, expectedExpression))

#define TOOLKIT_TEST_LT_(actualValue, expectedValue, actualExpression, expectedExpression) \
	TOOLKIT_TEST_AS_(tinyToolkit::test::Compare::LessThan(actualValue, expectedValue, actualExpression, expectedExpression))

#define TOOLKIT_TEST_LE_(actualValue, expectedValue, actualExpression, expectedExpression) \
	TOOLKIT_TEST_AS_(tinyToolkit::test::Compare::LessThanOrEqual(actualValue, expectedValue, actualExpression, expectedExpression))

#define TOOLKIT_TEST_GT_(actualValue, expectedValue, actualExpression, expectedExpression) \
	TOOLKIT_TEST_AS_(tinyToolkit::test::Compare::GreaterThan(actualValue, expectedValue, actualExpression, expectedExpression))

#define TOOLKIT_TEST_GE_(actualValue, expectedValue, actualExpression, expectedExpression) \
	TOOLKIT_TEST_AS_(tinyToolkit::test::Compare::GreaterThanOrEqual(actualValue, expectedValue, actualExpression, expectedExpression))

#define TOOLKIT_TEST_STR_EQ_(actualValue, expectedValue, actualExpression, expectedExpression) \
	TOOLKIT_TEST_AS_(tinyToolkit::test::Compare::StringEqual(actualValue, expectedValue, actualExpression, expectedExpression))

#define TOOLKIT_TEST_STR_NE_(actualValue, expectedValue, actualExpression, expectedExpression) \
	TOOLKIT_TEST_AS_(tinyToolkit::test::Compare::StringUnequal(actualValue, expectedValue, actualExpression, expectedExpression))

#define TOOLKIT_TEST_STR_CASE_EQ_(actualValue, expectedValue, actualExpression, expectedExpression) \
	TOOLKIT_TEST_AS_(tinyToolkit::test::Compare::StringCaseEqual(actualValue, expectedValue, actualExpression, expectedExpression))

#define TOOLKIT_TEST_STR_CASE_NE_(actualValue, expectedValue, actualExpression, expectedExpression) \
	TOOLKIT_TEST_AS_(tinyToolkit::test::Compare::StringCaseUnequal(actualValue, expectedValue, actualExpression, expectedExpression))

#define TOOLKIT_TEST_BOOLEAN_(condition, expression, actual, expected) \
	TOOLKIT_TEST_AS_(tinyToolkit::test::Compare::Boolean(condition, expression, #actual, #expected))


#endif // __TEST__COMPARE__H__
