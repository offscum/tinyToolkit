/**
 *
 * 作者: hm
 *
 * 说明: 信号处理
 *
 */


#include "signal.h"


namespace tinyToolkit
{
	namespace application
	{
		/**
		 *
		 * 注册忽略信号动作
		 *
		 * @param callback 回调函数
		 *
		 */
		void RegisterIgnoreSignal(void(* callback)(int32_t))
		{
		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

            TOOLKIT_UNUSED(callback);

        #else

			RegisterSignalAction(SIGHUP, callback);
			RegisterSignalAction(SIGPIPE, callback);
			RegisterSignalAction(SIGCHLD, callback);

		#endif
		}

		/**
		 *
		 * 注册异常信号动作
		 *
		 * @param callback 回调函数
		 *
		 */
		void RegisterExceptionSignal(void(* callback)(int32_t))
		{
			RegisterSignalAction(SIGILL, callback);
			RegisterSignalAction(SIGFPE, callback);
			RegisterSignalAction(SIGABRT, callback);
			RegisterSignalAction(SIGSEGV, callback);

		#if TOOLKIT_PLATFORM_TYPE != TOOLKIT_PLATFORM_WINDOWS

			RegisterSignalAction(SIGBUS, callback);

		#endif
		}

		/**
		 *
		 * 注册结束信号动作
		 *
		 * @param callback 回调函数
		 *
		 */
		void RegisterTerminateSignal(void(* callback)(int32_t))
		{
		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			RegisterSignalAction(SIGINT, callback);
			RegisterSignalAction(SIGTERM, callback);
			RegisterSignalAction(SIGBREAK, callback);

		#else

			RegisterSignalAction(SIGINT, callback);
			RegisterSignalAction(SIGQUIT, callback);
			RegisterSignalAction(SIGTERM, callback);
			RegisterSignalAction(SIGTSTP, callback);

		#endif
		}

		/**
		 *
		 * 注销忽略信号动作
		 *
		 */
		void UnregisterIgnoreSignal()
		{
		#if TOOLKIT_PLATFORM_TYPE != TOOLKIT_PLATFORM_WINDOWS

			UnregisterSignalAction(SIGHUP);
			UnregisterSignalAction(SIGPIPE);
			UnregisterSignalAction(SIGCHLD);

		#endif
		}

		/**
		 *
		 * 注销异常信号动作
		 *
		 */
		void UnregisterExceptionSignal()
		{
			UnregisterSignalAction(SIGILL);
			UnregisterSignalAction(SIGFPE);
			UnregisterSignalAction(SIGABRT);
			UnregisterSignalAction(SIGSEGV);

		#if TOOLKIT_PLATFORM_TYPE != TOOLKIT_PLATFORM_WINDOWS

			UnregisterSignalAction(SIGBUS);

		#endif
		}

		/**
		 *
		 * 注销结束信号动作
		 *
		 */
		void UnregisterTerminateSignal()
		{
		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			UnregisterSignalAction(SIGINT);
			UnregisterSignalAction(SIGTERM);
			UnregisterSignalAction(SIGBREAK);

		#else

			UnregisterSignalAction(SIGINT);
			UnregisterSignalAction(SIGQUIT);
			UnregisterSignalAction(SIGTERM);
			UnregisterSignalAction(SIGTSTP);

		#endif
		}

		/**
		 *
		 * 注册信号动作
		 *
		 * @param sig 信号
		 * @param callback 回调函数
		 *
		 * @return 是否注册成功
		 *
		 */
		bool RegisterSignalAction(int32_t sig, void(* callback)(int32_t))
		{
		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			return std::signal(sig, callback) == callback;

		#else

			struct sigaction action{ };

			action.sa_flags = SA_SIGINFO;
			action.sa_handler = callback;

			#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_APPLE

				sigemptyset(&action.sa_mask);

			#else

				::sigemptyset(&action.sa_mask);

			#endif

			#ifdef SA_RESTART

				action.sa_flags |= SA_RESTART;

			#endif

			return ::sigaction(sig, &action, nullptr) == 0;

		#endif
		}

		/**
		 *
		 * 注销信号动作
		 *
		 * @param sig 信号
		 *
		 * @return 是否注销成功
		 *
		 */
		bool UnregisterSignalAction(int32_t sig)
		{
			return RegisterSignalAction(sig, SIG_DFL);
		}
	}
}
