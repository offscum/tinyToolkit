/**
 *
 * 作者: hm
 *
 * 说明: 对比
 *
 */


#include "compare.h"

#include <cstring>


namespace tinyToolkit
{
	namespace test
	{
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
		Result Compare::Boolean(bool condition, const char * expression, const char * actual, const char * expected)
		{
			if (condition)
			{
				return Result(true);
			}

			return Result(false)
				<< "Value of: " << expression << TOOLKIT_LINE_EOL
				<< "  Actual: " << actual << TOOLKIT_LINE_EOL
				<< "Expected: " << expected << TOOLKIT_LINE_EOL;
		}

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
		Result Compare::StringEqual(const char * actualValue, const char * expectedValue, const char * actualExpression, const char * expectedExpression)
		{
			if (::strcmp(actualValue, expectedValue) == 0)
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
		Result Compare::StringEqual(const std::string & actualValue, const std::string & expectedValue, const char * actualExpression, const char * expectedExpression)
		{
			return StringEqual(actualValue.c_str(), expectedValue.c_str(), actualExpression, expectedExpression);
		}

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
		Result Compare::StringUnequal(const char * actualValue, const char * expectedValue, const char * actualExpression, const char * expectedExpression)
		{
			if (::strcmp(actualValue, expectedValue) != 0)
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
		Result Compare::StringUnequal(const std::string & actualValue, const std::string & expectedValue, const char * actualExpression, const char * expectedExpression)
		{
			return StringUnequal(actualValue.c_str(), expectedValue.c_str(), actualExpression, expectedExpression);
		}

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
		Result Compare::StringCaseEqual(const char * actualValue, const char * expectedValue, const char * actualExpression, const char * expectedExpression)
		{
		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			if (::_stricmp(actualValue, expectedValue) == 0)
			{
				return Result(true);
			}

		#else

			if (::strcasecmp(actualValue, expectedValue) == 0)
			{
				return Result(true);
			}

		#endif

			return Result(false)
				<< "Value of: " << actualExpression << TOOLKIT_LINE_EOL
				<< "  Actual: " << actualValue << TOOLKIT_LINE_EOL
				<< "Value of: " << expectedExpression << TOOLKIT_LINE_EOL
				<< "Expected: " << expectedValue << TOOLKIT_LINE_EOL;
		}

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
		Result Compare::StringCaseEqual(const std::string & actualValue, const std::string & expectedValue, const char * actualExpression, const char * expectedExpression)
		{
			return StringCaseEqual(actualValue.c_str(), expectedValue.c_str(), actualExpression, expectedExpression);
		}

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
		Result Compare::StringCaseUnequal(const char * actualValue, const char * expectedValue, const char * actualExpression, const char * expectedExpression)
		{
		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			if (::_stricmp(actualValue, expectedValue) != 0)
			{
				return Result(true);
			}

		#else

			if (::strcasecmp(actualValue, expectedValue) != 0)
			{
				return Result(true);
			}

		#endif

			return Result(false)
				<< "Value of: " << actualExpression << TOOLKIT_LINE_EOL
				<< "  Actual: " << actualValue << TOOLKIT_LINE_EOL
				<< "Value of: " << expectedExpression << TOOLKIT_LINE_EOL
				<< "Expected: " << expectedValue << TOOLKIT_LINE_EOL;
		}

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
		Result Compare::StringCaseUnequal(const std::string & actualValue, const std::string & expectedValue, const char * actualExpression, const char * expectedExpression)
		{
			return StringCaseUnequal(actualValue.c_str(), expectedValue.c_str(), actualExpression, expectedExpression);
		}
	}
}
