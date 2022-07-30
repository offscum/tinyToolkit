#ifndef __TIME__TIMER_TASK__H__
#define __TIME__TIMER_TASK__H__


/**
 *
 * 作者: hm
 *
 * 说明: 定时器任务
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"

#include <ctime>
#include <cstdint>
#include <functional>


namespace tinyToolkit
{
	namespace time
	{
		class TOOLKIT_API Timer;

		class TOOLKIT_API TimerTask
		{
			friend class Timer;

		public:
			/**
			 *
			 * 构造函数
			 *
			 */
			TimerTask() = default;

			/**
			 *
			 * 构造函数
			 *
			 * @param function 函数
			 *
			 */
			explicit TimerTask(std::function<void()> function);

		public:
			/**
			 *
			 * 注册暂停事件回调函数
			 *
			 * @param function 函数
			 *
			 */
			void OnPause(std::function<void()> function);

			/**
			 *
			 * 注册取消事件回调函数
			 *
			 * @param function 函数
			 *
			 */
			void OnCancel(std::function<void()> function);

			/**
			 *
			 * 注册恢复事件回调函数
			 *
			 * @param function 函数
			 *
			 */
			void OnResume(std::function<void()> function);

			/**
			 *
			 * 注册刷新事件回调函数
			 *
			 * @param function 函数
			 *
			 */
			void OnRefresh(std::function<void()> function);

			/**
			 *
			 * 注册触发事件回调函数
			 *
			 * @param function 函数
			 *
			 */
			void OnTrigger(std::function<void()> function);

			/**
			 *
			 * 是否暂停
			 *
			 * @return 是否暂停
			 *
			 */
			bool IsPause() const;

			/**
			 *
			 * 是否有效
			 *
			 * @return 是否有效
			 *
			 */
			bool IsValid() const;

			/**
			 *
			 * 任务次数
			 *
			 * @return 任务次数
			 *
			 */
			int64_t TaskCount() const;

			/**
			 *
			 * 剩余次数
			 *
			 * @return 剩余次数
			 *
			 */
			int64_t RemainCount() const;

			/**
			 *
			 * 触发次数
			 *
			 * @return 触发次数
			 *
			 */
			std::size_t TriggerCount() const;

			/**
			 *
			 * 间隔
			 *
			 * @return 间隔
			 *
			 */
			int64_t Interval() const;

		private:
			bool _isPause{ false };

			Timer * _timer{ nullptr };

			int64_t _expire{ 0 };
			int64_t _interval{ 0 };
			int64_t _taskCount{ 0 };
			int64_t _remainCount{ 0 };
			int64_t _pauseTimestamp{ 0 };

			std::size_t _triggerCount{ 0 };

			std::function<void()> _pauseCallback{ };
			std::function<void()> _cancelCallback{ };
			std::function<void()> _resumeCallback{ };
			std::function<void()> _refreshCallback{ };
			std::function<void()> _triggerCallback{ };
		};
	}
}


#endif // __TIME__TIMER_TASK__H__
