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
		 * 格式化
		 *
		 * @param format 格式
		 * @param args 参数
		 *
		 * @return 内容
		 *
		 */
		template <typename ... Args>
		static inline std::string WINAPI Format(const char * format, Args &&... args)
		{
			char buffer[MAX_SYM_NAME + 32 + 1]{ 0 };

			auto len = ::snprintf(buffer, sizeof(buffer) - 1, format, std::forward<Args>(args)...);

			if (len <= 0)
			{
				return std::string{ };
			}

			return std::string{ buffer, static_cast<std::string::size_type>(len <= sizeof(buffer) ? len : sizeof(buffer)) };
		}

		/**
		 *
		 * 解析符号
		 *
		 * @param handle 句柄
		 *
		 * @return 内容
		 *
		 */
		static inline std::string WINAPI ResolveSymbol(HANDLE handle)
		{
			CONTEXT context{ 0 };

			context.ContextFlags = CONTEXT_FULL;

			::RtlCaptureContext(&context);

			STACKFRAME64 stackFrame{ 0 };

			::memset(&stackFrame, 0, sizeof(stackFrame));

		#ifdef _M_IX86

			const DWORD machineType = IMAGE_FILE_MACHINE_I386;

			stackFrame.AddrPC.Offset = context.Eip;
			stackFrame.AddrPC.Mode = AddrModeFlat;
			stackFrame.AddrFrame.Offset = context.Ebp;
			stackFrame.AddrFrame.Mode = AddrModeFlat;
			stackFrame.AddrStack.Offset = context.Esp;
			stackFrame.AddrStack.Mode = AddrModeFlat;

		#elif _M_X64

			const DWORD machineType = IMAGE_FILE_MACHINE_AMD64;

			stackFrame.AddrPC.Offset = context.Rip;
			stackFrame.AddrPC.Mode = AddrModeFlat;
			stackFrame.AddrFrame.Offset = context.Rsp;
			stackFrame.AddrFrame.Mode = AddrModeFlat;
			stackFrame.AddrStack.Offset = context.Rsp;
			stackFrame.AddrStack.Mode = AddrModeFlat;

		#elif _M_IA64

			const DWORD machineType = IMAGE_FILE_MACHINE_IA64;

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

			IMAGEHLP_SYMBOL64_PACKAGE imagePackage{ };

			::memset(&imagePackage, 0, sizeof(imagePackage));

			imagePackage.sym.SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
			imagePackage.sym.MaxNameLength = MAX_SYM_NAME;

			auto threadHandle = ::GetCurrentThread();

			std::string content{ };

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

				auto hasLine = ::SymGetLineFromAddr64(handle, stackFrame.AddrPC.Offset, &displacementLine, &imageLine);
				auto hasModule = ::SymGetModuleInfo64(handle, stackFrame.AddrPC.Offset, &imageModule);
				auto hasSymbol = ::SymGetSymFromAddr64(handle, stackFrame.AddrPC.Offset, &displacementSymbol, &imagePackage.sym);

				if (hasLine)
				{
					content += Format
					(
						"    at %s:%ld(%s) [%s 0x%llx]\r\n",
						imageLine.FileName,
						imageLine.LineNumber,
						hasSymbol ? imagePackage.sym.Name : "N/A",
						hasModule ? imageModule.ModuleName : "N/A",
						imagePackage.sym.Address
					);
				}
				else
				{
					content += Format
					(
						"    at %s [%s 0x%llx]\r\n",
						hasSymbol ? imagePackage.sym.Name : "N/A",
						hasModule ? imageModule.ModuleName : "N/A",
						imagePackage.sym.Address
					);
				}
			}

			return content;
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
			std::size_t pos{ 0 };

			std::string content{ };

			while (pos < symbol.length())
			{
				auto head = symbol.find("_Z", pos);

				if (head == std::string::npos)
				{
					content += symbol.substr(pos);

					break;
				}

				auto tail = symbol.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_", head);

				if (tail == std::string::npos)
				{
					tail = symbol.length();
				}

				int32_t status{ 0 };

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
			content.append(ResolveSymbol(processHandle));

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
