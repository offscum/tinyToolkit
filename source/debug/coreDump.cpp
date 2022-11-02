/**
 *
 * 作者: hm
 *
 * 说明: 核心转储
 *
 */


#include "coreDump.h"

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS
#
#  include <ctime>
#  include <chrono>
#  include <memory>
#  include <string>
#  include <cstdint>
#  include <functional>
#
#  include <Windows.h>
#  include <DbgHelp.h>
#
#  pragma comment(lib, "DbgHelp.lib")
#
#else
#
#  include <sys/resource.h>
#
#endif


namespace tinyToolkit
{
	namespace debug
	{
	#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

		/**
		 *
		 * 异常过滤器
		 *
		 */
		static LPTOP_LEVEL_EXCEPTION_FILTER sExceptionFilter = nullptr;

		/**
		 *
		 * 是否是需要的文件
		 *
		 * @param path 路径
		 *
		 * @return 是否是需要的文件
		 *
		 */
		static inline BOOL WINAPI IsNeedFile(const WCHAR * path)
		{
			if (path == nullptr)
			{
				return FALSE;
			}

			WCHAR file[TOOLKIT_NAME_MAX + 1]{ 0 };

			::_wsplitpath_s(path, nullptr, 0, nullptr, 0, file, TOOLKIT_NAME_MAX, nullptr, 0);

			return ::_wcsicmp(file, L"ntdll") == 0 ? TRUE : FALSE;
		}

		/**
		 *
		 * 转储文件回调函数
		 *
		 * @param param 参数
		 * @param input 输入
		 * @param output 输出
		 *
		 * @return 是否转储成功
		 *
		 */
		static inline BOOL WINAPI DumpCallback(PVOID param, PMINIDUMP_CALLBACK_INPUT input, PMINIDUMP_CALLBACK_OUTPUT output)
		{
			TOOLKIT_UNUSED(param);

			if (input == nullptr || output == nullptr)
			{
				return FALSE;
			}

			switch (input->CallbackType)
			{
				case ModuleCallback:
				{
					if (output->ModuleWriteFlags & ModuleWriteDataSeg)
					{
						if (!IsNeedFile(input->Module.FullPath))
						{
							output->ModuleWriteFlags &= (~ModuleWriteDataSeg);
						}
					}
				}

				case ThreadCallback:
				case ThreadExCallback:
				case IncludeModuleCallback:
				case IncludeThreadCallback:
				{
					return TRUE;
				}

				default:
				{
					break;
				}
			}

			return FALSE;
		}

		/**
		 *
		 * 时区
		 *
		 * @return 时区
		 *
		 */
		static inline int64_t WINAPI TimeZone()
		{
			std::tm utc{ };
			std::tm local{ };

			/// 伦敦中午12点整, 全世界都在同一天
			auto timestamp = static_cast<int64_t>(12 * 3600);

			::gmtime_s(&utc, reinterpret_cast<time_t *>(&timestamp));

			::localtime_s(&local, reinterpret_cast<time_t *>(&timestamp));

			auto timezone = static_cast<int64_t>(local.tm_hour - utc.tm_hour);

			if (timezone < -12)
			{
				timezone += 24;
			}
			else if (timezone > 12)
			{
				timezone -= 24;
			}

			return timezone;
		}

		/**
		 *
		 * 转储文件
		 *
		 * @return 转储文件
		 *
		 */
		static inline std::string WINAPI DumpFile()
		{
			std::string content{ };

			content.reserve(TOOLKIT_PATH_MAX + 20 + 5);

			{
				char name[TOOLKIT_PATH_MAX + 1]{ 0 };

				DWORD size = ::GetModuleFileName(nullptr, name, TOOLKIT_PATH_MAX);

				if (size > TOOLKIT_PATH_MAX)
				{
					size = TOOLKIT_PATH_MAX;
				}

				if (size >= 4 && name[size - 4] == '.' && name[size - 3] == 'e' && name[size - 2] == 'x' && name[size - 1] == 'e')
				{
					size -= 4;
				}

				content.append(name, static_cast<std::size_t>(size));
			}

			content += '_';

			{
				std::tm now{ };

				auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() + (TimeZone() * 3600);

				::gmtime_s(&now, reinterpret_cast<time_t *>(&timestamp));

				content += std::to_string(now.tm_year + 1900);
				content += '_';

				if (now.tm_mon < 9)
				{
					content += '0';
				}

				content += std::to_string(now.tm_mon + 1);
				content += '_';

				if (now.tm_mday < 10)
				{
					content += '0';
				}

				content += std::to_string(now.tm_mday);
				content += '_';

				if (now.tm_hour < 10)
				{
					content += '0';
				}

				content += std::to_string(now.tm_hour);
				content += '_';

				if (now.tm_min < 10)
				{
					content += '0';
				}

				content += std::to_string(now.tm_min);
				content += '_';

				if (now.tm_sec < 10)
				{
					content += '0';
				}

				content += std::to_string(now.tm_sec);
			}

			content.append(".dmp", 4);

			return content;
		}

		/**
		 *
		 * 生成最小转储文件
		 *
		 * @param exception 异常
		 *
		 * @return 生成结果
		 *
		 */
		static inline LONG WINAPI GenerateMiniDump(PEXCEPTION_POINTERS exception)
		{
			std::unique_ptr<typename std::remove_pointer<HANDLE>::type, std::function<void(HANDLE)>> const fileHandle
			(
				::CreateFile(DumpFile().c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr),

				[](HANDLE handle)
				{
					if (handle && (handle != INVALID_HANDLE_VALUE))
					{
						::CloseHandle(handle);
					}
				}
			);

			if (fileHandle == nullptr || fileHandle.get() == INVALID_HANDLE_VALUE)
			{
				return EXCEPTION_CONTINUE_EXECUTION;
			}

			auto dumpType = static_cast<MINIDUMP_TYPE>
			(
				MiniDumpScanMemory |
				MiniDumpWithFullMemory |
				MiniDumpWithHandleData |
				MiniDumpWithThreadInfo |
				MiniDumpWithFullMemoryInfo |
				MiniDumpWithUnloadedModules |
				MiniDumpWithProcessThreadData |
				MiniDumpWithFullAuxiliaryState |
				MiniDumpIgnoreInaccessibleMemory |
				MiniDumpWithPrivateReadWriteMemory |
				MiniDumpWithIndirectlyReferencedMemory
			);

			MINIDUMP_EXCEPTION_INFORMATION exceptionInformation{ };

			exceptionInformation.ThreadId = ::GetCurrentThreadId();
			exceptionInformation.ClientPointers = FALSE;
			exceptionInformation.ExceptionPointers = exception;

			MINIDUMP_CALLBACK_INFORMATION callbackInformation{ };

			callbackInformation.CallbackParam = nullptr;
			callbackInformation.CallbackRoutine = static_cast<MINIDUMP_CALLBACK_ROUTINE>(DumpCallback);

			::MiniDumpWriteDump
			(
				::GetCurrentProcess(),
				::GetCurrentProcessId(),
				fileHandle.get(),
				dumpType,
				&exceptionInformation,
				nullptr,
				&callbackInformation
			);

			return EXCEPTION_EXECUTE_HANDLER;
		}

		/**
		 *
		 * 异常处理
		 *
		 * @param exception 异常
		 *
		 * @return 结果
		 *
		 */
		static inline LONG WINAPI ExceptionFilter(LPEXCEPTION_POINTERS exception)
		{
			if (::IsDebuggerPresent())
			{
				return EXCEPTION_CONTINUE_SEARCH;
			}

			return GenerateMiniDump(exception);
		}

	#endif


		////////////////////////////////////////////////////////////////////////////////////////////////////


		/**
		 *
		 * 注册核心转储
		 *
		 */
		void RegisterCoreDump()
		{
		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			if (sExceptionFilter == nullptr)
			{
				sExceptionFilter = ::SetUnhandledExceptionFilter(ExceptionFilter);
			}

		#elif TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_APPLE

			struct rlimit limit{ };

			limit.rlim_cur = RLIM_INFINITY;
			limit.rlim_max = RLIM_INFINITY;

			::setrlimit(RLIMIT_CORE, &limit);

		#else

			#if TOOLKIT_PLATFORM_BYTE == 32

				struct rlimit limit{ };

				limit.rlim_cur = RLIM_INFINITY;
				limit.rlim_max = RLIM_INFINITY;

				::setrlimit(RLIMIT_CORE, &limit);

			#else

				struct rlimit64 limit{ };

				limit.rlim_cur = RLIM64_INFINITY;
				limit.rlim_max = RLIM64_INFINITY;

				::setrlimit64(RLIMIT_CORE, &limit);

			#endif

		#endif
		}

		/**
		 *
		 * 注销核心转储
		 *
		 */
		void UnregisterCoreDump()
		{
		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			if (sExceptionFilter)
			{
				::SetUnhandledExceptionFilter(nullptr);

				sExceptionFilter = nullptr;
			}

		#elif TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_APPLE

			struct rlimit limit{ };

			limit.rlim_cur = 0;
			limit.rlim_max = 0;

			::setrlimit(RLIMIT_CORE, &limit);

		#else

			#if TOOLKIT_PLATFORM_BYTE == 32

				struct rlimit limit{ };

				limit.rlim_cur = 0;
				limit.rlim_max = 0;

				::setrlimit(RLIMIT_CORE, &limit);

			#else

				struct rlimit64 limit{ };

				limit.rlim_cur = 0;
				limit.rlim_max = 0;

				::setrlimit64(RLIMIT_CORE, &limit);

			#endif

		#endif
		}
	}
}
