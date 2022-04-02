/**
 *
 * 作者: hm
 *
 * 说明: 控制台
 *
 */


#include "console.h"

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS
#
#  include <io.h>
#
#elif TOOLKIT_PLATFORM_TYPE != TOOLKIT_PLATFORM_APPLE
#
#  include <unistd.h>
#
#endif

#include <stdexcept>


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
		Console & Console::Instance()
		{
			static Console instance{ };

			return instance;
		}

		/**
		 *
		 * 构造函数
		 *
		 * @param file 句柄
		 *
		 */
		Console::Console(FILE * file) : _file(file)
		{
			if (_file == nullptr)
			{
				throw std::runtime_error("Console handle is null");
			}

		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			_handle = reinterpret_cast<HANDLE>(::_get_osfhandle(::_fileno(_file)));

			if (_handle == INVALID_HANDLE_VALUE)
			{
				throw std::runtime_error("Console handle invalid");
			}

		#endif
		}

		/**
		 *
		 * 析构函数
		 *
		 */
		Console::~Console()
		{
			Close();
		}

		/**
		 *
		 * 关闭
		 *
		 */
		void Console::Close()
		{
			Flush();
		}

		/**
		 *
		 * 刷新
		 *
		 */
		void Console::Flush()
		{
			if (_file == nullptr)
			{
				return;
			}

			(void)::fflush(_file);
		}

		/**
		 *
		 * 显示
		 *
		 * @param message 信息
		 *
		 */
		void Console::Info(const Message & message)
		{
			Info(message.Content());
		}

		/**
		 *
		 * 显示
		 *
		 * @param content 内容
		 *
		 */
		void Console::Info(const std::string & content)
		{
		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			WORD attributes = [this]() -> WORD
			{
				CONSOLE_SCREEN_BUFFER_INFO info{ };

				if (::GetConsoleScreenBufferInfo(_handle, &info) == FALSE)
				{
					return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
				}

				return info.wAttributes;
			}();

			::SetConsoleTextAttribute(_handle, FOREGROUND_GREEN | (attributes & 0xfff0));

			Print(content.c_str(), 0, 12);

			::SetConsoleTextAttribute(_handle, attributes);

			Print(content.c_str(), 12, content.length());

		#else

			Print("\033[32m", 0, 5);
			Print(content.c_str(), 0, 12);
			Print("\033[0m", 0, 4);
			Print(content.c_str(), 12, content.length());

		#endif
		}

		/**
		 *
		 * 显示
		 *
		 * @param message 信息
		 *
		 */
		void Console::Fatal(const Message & message)
		{
			Fatal(message.Content());
		}

		/**
		 *
		 * 显示
		 *
		 * @param content 内容
		 *
		 */
		void Console::Fatal(const std::string & content)
		{
		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			WORD attributes = [this]() -> WORD
			{
				CONSOLE_SCREEN_BUFFER_INFO info{ };

				if (::GetConsoleScreenBufferInfo(_handle, &info) == FALSE)
				{
					return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
				}

				return info.wAttributes;
			}();

			::SetConsoleTextAttribute(_handle, FOREGROUND_RED | (attributes & 0xfff0));

			Print(content.c_str(), 0, 12);

			::SetConsoleTextAttribute(_handle, attributes);

			Print(content.c_str(), 12, content.length());

		#else

			Print("\033[31m", 0, 5);
			Print(content.c_str(), 0, 12);
			Print("\033[0m", 0, 4);
			Print(content.c_str(), 12, content.length());

		#endif
		}

		/**
		 *
		 * 显示
		 *
		 * @param message 信息
		 *
		 */
		void Console::Print(const Message & message)
		{
			Print(message.Content());
		}

		/**
		 *
		 * 显示
		 *
		 * @param content 内容
		 *
		 */
		void Console::Print(const std::string & content)
		{
			Print(content.c_str(), 0, content.length());
		}

		/**
		 *
		 * 显示
		 *
		 * @param content 内容
		 * @param head 头部
		 * @param tail 尾部
		 *
		 */
		void Console::Print(const char * content, std::size_t head, std::size_t tail)
		{
		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			::WriteFile(_handle, content + head, static_cast<DWORD>(tail - head), nullptr, nullptr);

		#else

			::fwrite(content + head, sizeof(char), tail - head, _file);

		#endif
		}
	}
}
