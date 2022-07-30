/**
 *
 * 作者: hm
 *
 * 说明: 定时器任务
 *
 */


#include "timerTask.h"


namespace tinyToolkit
{
	namespace time
	{
		/**
		 *
		 * 构造函数
		 *
		 * @param function 函数
		 *
		 */
		TimerTask::TimerTask(std::function<void()> function) : _triggerCallback(std::move(function))
		{

		}

		/**
		 *
		 * 注册暂停事件回调函数
		 *
		 * @param function 函数
		 *
		 */
		void TimerTask::OnPause(std::function<void()> function)
		{
			_pauseCallback = std::move(function);
		}

		/**
		 *
		 * 注册取消事件回调函数
		 *
		 * @param function 函数
		 *
		 */
		void TimerTask::OnCancel(std::function<void()> function)
		{
			_cancelCallback = std::move(function);
		}

		/**
		 *
		 * 注册恢复事件回调函数
		 *
		 * @param function 函数
		 *
		 */
		void TimerTask::OnResume(std::function<void()> function)
		{
			_resumeCallback = std::move(function);
		}

		/**
		 *
		 * 注册刷新事件回调函数
		 *
		 * @param function 函数
		 *
		 */
		void TimerTask::OnRefresh(std::function<void()> function)
		{
			_refreshCallback = std::move(function);
		}

		/**
		 *
		 * 注册触发事件回调函数
		 *
		 * @param function 函数
		 *
		 */
		void TimerTask::OnTrigger(std::function<void()> function)
		{
			_triggerCallback = std::move(function);
		}

		/**
		 *
		 * 是否暂停
		 *
		 * @return 是否暂停
		 *
		 */
		bool TimerTask::IsPause() const
		{
			return _isPause;
		}

		/**
		 *
		 * 是否有效
		 *
		 * @return 是否有效
		 *
		 */
		bool TimerTask::IsValid() const
		{
			return _remainCount != 0;
		}

		/**
		 *
		 * 任务次数
		 *
		 * @return 任务次数
		 *
		 */
		int64_t TimerTask::TaskCount() const
		{
			return _taskCount;
		}

		/**
		 *
		 * 剩余次数
		 *
		 * @return 剩余次数
		 *
		 */
		int64_t TimerTask::RemainCount() const
		{
			return _remainCount;
		}

		/**
		 *
		 * 触发次数
		 *
		 * @return 触发次数
		 *
		 */
		std::size_t TimerTask::TriggerCount() const
		{
			return _triggerCount;
		}

		/**
		 *
		 * 间隔
		 *
		 * @return 间隔
		 *
		 */
		int64_t TimerTask::Interval() const
		{
			return _interval;
		}
	}
}
