/**
 *
 * 作者: hm
 *
 * 说明: 堆栈信息
 *
 */


#include "stacktrace.h"

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS
#
#  include <cstdio>
#  include <cstring>
#
#  include <Windows.h>
#  include <DbgHelp.h>
#
#  pragma comment(lib, "DbgHelp.lib")
#
#else
#
#  include <memory>
#  include <cstdint>
#
#  include <unistd.h>
#  include <cxxabi.h>
#  include <execinfo.h>
#
#endif


namespace tinyToolkit
{
	namespace debug
	{
	#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

		/**
		 *
		 * 格式化符号
		 *
		 * @param content 内容
		 * @param format 格式
		 * @param args 参数
		 *
		 */
		template <typename ... Args>
		static inline void WINAPI FormatSymbol(std::string & content, const char * format, Args &&... args)
		{
			char buffer[MAX_SYM_NAME + 1]{ 0 };

			auto len = ::snprintf(buffer, sizeof(buffer) - 1, format, std::forward<Args>(args)...);

			if (len < 0)
			{
				len = 0;
			}
			else if (len > MAX_SYM_NAME)
			{
				len = MAX_SYM_NAME;
			}

			buffer[len] = '\0';

			content.append(buffer, static_cast<std::size_t>(len));
			content.append(TOOLKIT_LINE_EOL);
		}

		/**
		 *
		 * 解析符号
		 *
		 * @param handle 句柄
		 * @param content 内容
		 *
		 */
		static inline void WINAPI ResolveSymbol(HANDLE handle, std::string & content)
		{
			CONTEXT context{ 0 };

			context.ContextFlags = CONTEXT_FULL;

			::RtlCaptureContext(&context);

			STACKFRAME64 stackFrame{ 0 };

			::memset(&stackFrame, 0, sizeof(stackFrame));

		#ifdef _M_IX86

			DWORD machineType = IMAGE_FILE_MACHINE_I386;

			stackFrame.AddrPC.Offset = context.Eip;
			stackFrame.AddrPC.Mode = AddrModeFlat;
			stackFrame.AddrFrame.Offset = context.Ebp;
			stackFrame.AddrFrame.Mode = AddrModeFlat;
			stackFrame.AddrStack.Offset = context.Esp;
			stackFrame.AddrStack.Mode = AddrModeFlat;

		#elif _M_X64

			DWORD machineType = IMAGE_FILE_MACHINE_AMD64;

			stackFrame.AddrPC.Offset = context.Rip;
			stackFrame.AddrPC.Mode = AddrModeFlat;
			stackFrame.AddrFrame.Offset = context.Rsp;
			stackFrame.AddrFrame.Mode = AddrModeFlat;
			stackFrame.AddrStack.Offset = context.Rsp;
			stackFrame.AddrStack.Mode = AddrModeFlat;

		#elif _M_IA64

			DWORD machineType = IMAGE_FILE_MACHINE_IA64;

			stackFrame.AddrPC.Offset = context.StIIP;
			stackFrame.AddrPC.Mode = AddrModeFlat;
			stackFrame.AddrFrame.Offset = context.IntSp;
			stackFrame.AddrFrame.Mode = AddrModeFlat;
			stackFrame.AddrBStore.Offset = context.RsBSP;
			stackFrame.AddrBStore.Mode = AddrModeFlat;
			stackFrame.AddrStack.Offset = context.IntSp;
			stackFrame.AddrStack.Mode = AddrModeFlat;

		#else
		#error "Platform not supported!"
		#endif

			IMAGEHLP_LINE64 imageLine{ };

			::memset(&imageLine, 0, sizeof(imageLine));

			imageLine.SizeOfStruct = sizeof(imageLine);

			IMAGEHLP_MODULE64 imageModule{ };

			::memset(&imageModule, 0, sizeof(imageModule));

			imageModule.SizeOfStruct = sizeof(imageModule);

			auto imageSymbol = (IMAGEHLP_SYMBOL64 *)::malloc(sizeof(IMAGEHLP_SYMBOL64) + MAX_SYM_NAME);

			if (imageSymbol == nullptr)
			{
				return;
			}

			::memset(imageSymbol, 0, sizeof(*imageSymbol));

			imageSymbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
			imageSymbol->MaxNameLength = MAX_SYM_NAME;

			auto threadHandle = ::GetCurrentThread();

			while (true)
			{
				if (::StackWalk64(machineType, handle, threadHandle, &stackFrame, &context, nullptr, ::SymFunctionTableAccess64, ::SymGetModuleBase64, nullptr) == FALSE)
				{
					break;
				}

				if (stackFrame.AddrPC.Offset == 0)
				{
					break;
				}

				DWORD displacementLine{ 0 };
				DWORD64 displacementSymbol{ 0 };

				auto lineRet = ::SymGetLineFromAddr64(handle, stackFrame.AddrPC.Offset, &displacementLine, &imageLine);
				auto moduleRet = ::SymGetModuleInfo64(handle, stackFrame.AddrPC.Offset, &imageModule);
				auto symbolRet = ::SymGetSymFromAddr64(handle, stackFrame.AddrPC.Offset, &displacementSymbol, imageSymbol);

				if (lineRet)
				{
					FormatSymbol(content, "    at %s:%ld(%s) [%s 0x%llx]", imageLine.FileName, imageLine.LineNumber, symbolRet ? imageSymbol->Name : "function-name not available", moduleRet ? imageModule.ModuleName : "(module-name not available)", "(filename not available)", imageSymbol->Address);
				}
				else
				{
					FormatSymbol(content, "    at %s(%s) [%s %s]", "(filename not available)", symbolRet ? imageSymbol->Name : "(function-name not available)", moduleRet ? imageModule.ModuleName : "(module-name not available)", "(filename not available)");
				}
			}

			::free(imageSymbol);
		}

	#else

		/**
		 *
		 * 解析符号
		 *
		 * @param symbol 符号
		 *
		 * @return 符号信息
		 *
		 */
		static inline std::string ResolveSymbol(const std::string & symbol)
		{
			std::size_t pos = 0;
			std::size_t head;
			std::size_t tail;

			std::string content{ };

			while (pos < symbol.length())
			{
				head = symbol.find("_Z", pos);

				if (head == std::string::npos)
				{
					content += symbol.substr(pos);

					break;
				}

				tail = symbol.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_", head);

				if (tail == std::string::npos)
				{
					tail = symbol.length();
				}

				int32_t status = 0;

				std::unique_ptr<char, void(*)(void *)> link
				{
					::abi::__cxa_demangle
					(
						symbol.substr(head, tail - head).c_str(),
						nullptr,
						nullptr,
						&status
					),
					::free
				};

				if (status == 0)
				{
					content += symbol.substr(pos, head - pos);
					content += link.get();

					pos = tail;
				}
				else
				{
					pos = head + 2;
				}
			}

			return content;
		}

	#endif


		////////////////////////////////////////////////////////////////////////////////////////////////////


		/**
		 *
		 * 堆栈内容
		 *
		 * @return 堆栈内容
		 *
		 */
		std::string Stacktrace()
		{
			std::string content{ };

		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			HANDLE processHandle = ::GetCurrentProcess();

			if (::SymInitialize(processHandle, nullptr, TRUE) == FALSE)
			{
				return std::string{ };
			}

			::SymSetOptions(::SymGetOptions() | SYMOPT_LOAD_LINES | SYMOPT_FAIL_CRITICAL_ERRORS);

			content.append("StackTrace [pid=", 16);
			content.append(std::to_string(::GetCurrentProcessId()));
			content.append("]:", 2);
			content.append(TOOLKIT_LINE_EOL);

			ResolveSymbol(processHandle, content);

			::SymCleanup(processHandle);

		#else

			void * stack[1024]{ };

			auto size = ::backtrace(stack, 1024);

			if (size <= 0)
			{
				return std::string{ };
			}

			std::unique_ptr<char *, void(*)(void *)> symbols
			(
				::backtrace_symbols(stack, size),
				::free
			);

			content.append("StackTrace [pid=", 16);
			content.append(std::to_string(::getpid()));
			content.append("]:", 2);
			content.append(TOOLKIT_LINE_EOL);

			for (int32_t i = 0; i < size; ++i)
			{
				auto result = ResolveSymbol(symbols.get()[i]);

				if (result.empty())
				{
					continue;
				}

				content.append("    at ", 7);
				content.append(result);
				content.append(TOOLKIT_LINE_EOL);
			}

		#endif

			return content;
		}
	}
}
