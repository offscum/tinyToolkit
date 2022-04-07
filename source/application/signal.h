#ifndef __APPLICATION__SIGNAL__H__
#define __APPLICATION__SIGNAL__H__


/**
 *
 * 作者: hm
 *
 * 说明: 信号处理
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"

#include <cstdint>
#include <csignal>


namespace tinyToolkit
{
	namespace application
	{
		/**
		 *
		 * 注册忽略信号动作
		 *
		 */
		TOOLKIT_API void RegisterIgnoreSignal(void(* callback)(int32_t) = SIG_IGN);

		/**
		 *
		 * 注册异常信号动作
		 *
		 * @param callback 回调函数
		 *
		 */
		TOOLKIT_API void RegisterExceptionSignal(void(* callback)(int32_t));

		/**
		 *
		 * 注册结束信号动作
		 *
		 * @param callback 回调函数
		 *
		 */
		TOOLKIT_API void RegisterTerminateSignal(void(* callback)(int32_t));

		/**
		 *
		 * 注销忽略信号动作
		 *
		 */
		TOOLKIT_API void UnregisterIgnoreSignal();

		/**
		 *
		 * 注销异常信号动作
		 *
		 */
		TOOLKIT_API void UnregisterExceptionSignal();

		/**
		 *
		 * 注销结束信号动作
		 *
		 */
		TOOLKIT_API void UnregisterTerminateSignal();

		/**
		 *
		 * 向自身发送信号
		 *
		 * @param sig 信号
		 *
		 * @return 是否发送成功
		 *
		 */
		TOOLKIT_API bool Raise(int32_t sig);

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
		TOOLKIT_API bool RegisterSignalAction(int32_t sig, void(* callback)(int32_t));

		/**
		 *
		 * 注销信号动作
		 *
		 * @param sig 信号
		 *
		 * @return 是否注销成功
		 *
		 */
		TOOLKIT_API bool UnregisterSignalAction(int32_t sig);
	}
}


#endif // __APPLICATION__SIGNAL__H__
