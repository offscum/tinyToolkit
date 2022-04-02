/**
 *
 * 作者: hm
 *
 * 说明: 失败
 *
 */


#include "unit.h"
#include "failure.h"
#include "console.h"


namespace tinyToolkit
{
	namespace test
	{
		/**
		 *
		 * 构造函数
		 *
		 * @param file 文件
		 * @param line 行号
		 * @param message 信息
		 *
		 */
		Failure::Failure(const char * file, int32_t line, const std::string & message)
		{
			const auto & test = Unit::Instance().CurrentCase()->CurrentTest();

			if (test->FailedCount() > 0)
			{
				Console::Instance().Print(TOOLKIT_LINE_EOL);
			}

			test->OnFailed();

			Console::Instance().Print(Message()
				<< file
				<< ":"
				<< line
				<< ": Failure"
				<< TOOLKIT_LINE_EOL
				<< message);
		}

		/**
		 *
		 * 重载=操作
		 *
		 * @param message 信息
		 *
		 * @return 对象
		 *
		 */
		Failure & Failure::operator=(const Message & message)
		{
			Console::Instance().Print(message);

			return *this;
		}
	}
}
