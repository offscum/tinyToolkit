#ifndef __TEST__CONSOLE__H__
#define __TEST__CONSOLE__H__


/**
 *
 * 作者: hm
 *
 * 说明: 控制台
 *
 */


#include "message.h"

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS
#
#  include <Windows.h>
#
#endif


namespace tinyToolkit
{
	namespace test
	{
		class TOOLKIT_API Console
		{
		public:
			/**
			 *
			 * 单例对象
			 *
			 * @return 单例对象
			 *
			 */
			static Console & Instance();

		public:
			/**
			 *
			 * 构造函数
			 *
			 * @param file 句柄
			 *
			 */
			explicit Console(FILE * file = stdout);

			/**
			 *
			 * 析构函数
			 *
			 */
			~Console();

		public:
			/**
			 *
			 * 关闭
			 *
			 */
			void Close();

			/**
			 *
			 * 刷新
			 *
			 */
			void Flush();

			/**
			 *
			 * 显示
			 *
			 * @param message 信息
			 *
			 */
			void Info(const Message & message);

			/**
			 *
			 * 显示
			 *
			 * @param content 内容
			 *
			 */
			void Info(const std::string & content);

			/**
			 *
			 * 显示
			 *
			 * @param message 信息
			 *
			 */
			void Fatal(const Message & message);

			/**
			 *
			 * 显示
			 *
			 * @param content 内容
			 *
			 */
			void Fatal(const std::string & content);

			/**
			 *
			 * 显示
			 *
			 * @param message 信息
			 *
			 */
			void Print(const Message & message);

			/**
			 *
			 * 显示
			 *
			 * @param content 内容
			 *
			 */
			void Print(const std::string & content);

		private:
			/**
			 *
			 * 显示
			 *
			 * @param content 内容
			 * @param head 头部
			 * @param tail 尾部
			 *
			 */
			void Print(const char * content, std::size_t head, std::size_t tail);

		private:
			FILE * _file{ nullptr };

		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			HANDLE _handle{ };

		#endif
		};
	}
}


#endif // __TEST__CONSOLE__H__
