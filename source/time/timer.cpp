/**
 *
 * 作者: hm
 *
 * 说明: 定时器
 *
 */


#include "timer.h"

#include <chrono>
#include <thread>


namespace tinyToolkit
{
	namespace time
	{
		const int64_t Timer::TVR_BITS;
		const int64_t Timer::TVR_SIZE;
		const int64_t Timer::TVR_MASK;

		const int64_t Timer::TVN_BITS;
		const int64_t Timer::TVN_SIZE;
		const int64_t Timer::TVN_MASK;

		const int64_t Timer::WHEEL_NUM;


		#define RANK_WHEEL_MIN(n)			(1LL << (TVR_BITS + ((n) * TVN_BITS)))
		#define ROOT_WHEEL_SITE(v)			((v) & TVR_MASK)
		#define RANK_WHEEL_SITE(v, n)		(((v) >> (TVR_BITS + ((n) * TVN_BITS))) & TVN_MASK)


		////////////////////////////////////////////////////////////////////////////////////////////////////


		/**
		 *
		 * 时间戳
		 *
		 * @return 时间戳
		 *
		 */
		static inline int64_t Timestamp()
		{
			return static_cast<int64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
		}


		////////////////////////////////////////////////////////////////////////////////////////////////////


		/**
		 *
		 * 构造函数
		 *
		 */
		Timer::Timer() : _lastTimestamp(Timestamp())
		{

		}

		/**
		 *
		 * 析构函数
		 *
		 */
		Timer::~Timer()
		{
			Clear();
		}

		/**
		 *
		 * 提交
		 *
		 * @param task 任务
		 * @param count 次数
		 * @param interval 间隔(毫秒)
		 *
		 */
		void Timer::Post(const std::function<void()> & task, int64_t count, int64_t interval)
		{
			if (count == 0 || interval <= 0)
			{
				return;
			}

			Post(std::make_shared<TimerTask>(task), count, interval);
		}

		/**
		 *
		 * 提交
		 *
		 * @param task 任务
		 * @param count 次数
		 * @param interval 间隔(毫秒)
		 *
		 */
		void Timer::Post(const std::shared_ptr<TimerTask> & task, int64_t count, int64_t interval)
		{
			if (count == 0 || interval <= 0)
			{
				return;
			}

			if (task == nullptr || task->_timer != nullptr)
			{
				return;
			}

			task->_timer = this;
			task->_expire = _tickTimestamp + interval;
			task->_interval = interval;
			task->_taskCount = count;
			task->_remainCount = count;
			task->_triggerCount = 0;
			task->_pauseTimestamp = 0;

			if (task != _currentTask)
			{
				Post(task);
			}

			_tasks.insert(task);
		}

		/**
		 *
		 * 清空
		 *
		 */
		void Timer::Clear()
		{
			for (auto & spoke : _rootWheel)
			{
				spoke.clear();
				spoke.shrink_to_fit();
			}

			for (auto & wheel : _rankWheels)
			{
				for (auto & spoke : wheel)
				{
					spoke.clear();
					spoke.shrink_to_fit();
				}
			}

			for (const auto & task : _tasks)
			{
				if (task == nullptr)
				{
					continue;
				}

				task->_timer = nullptr;
				task->_expire = 0;
				task->_isPause = false;
				task->_remainCount = 0;
				task->_pauseTimestamp = 0;
			}

			_tasks.clear();
		}

		/**
		 *
		 * 暂停
		 *
		 * @param task 任务
		 *
		 */
		void Timer::Pause(const std::shared_ptr<TimerTask> & task)
		{
			if (task == nullptr || task->_timer != this || task->_remainCount == 0 || task->_isPause)
			{
				return;
			}

			task->_isPause = true;
			task->_pauseTimestamp = _tickTimestamp;

			if (task->_pauseCallback)
			{
				task->_pauseCallback();
			}
		}

		/**
		 *
		 * 取消
		 *
		 * @param task 任务
		 *
		 */
		void Timer::Cancel(const std::shared_ptr<TimerTask> & task)
		{
			if (task == nullptr || task->_timer != this || task->_remainCount == 0)
			{
				return;
			}

			task->_timer = nullptr;
			task->_expire = 0;
			task->_isPause = false;
			task->_remainCount = 0;
			task->_pauseTimestamp = 0;

			_tasks.erase(task);

			if (task->_cancelCallback)
			{
				task->_cancelCallback();
			}
		}

		/**
		 *
		 * 恢复
		 *
		 * @param task 任务
		 *
		 */
		void Timer::Resume(const std::shared_ptr<TimerTask> & task)
		{
			if (task == nullptr || task->_timer != this || task->_remainCount == 0 || !task->_isPause)
			{
				return;
			}

			task->_isPause = false;

			if (_tickTimestamp != task->_pauseTimestamp)
			{
				int64_t expire = task->_expire;

				task->_expire += _tickTimestamp - task->_pauseTimestamp;

				if (expire <= _tickTimestamp)
				{
					Post(task);
				}
			}

			if (task->_resumeCallback)
			{
				task->_resumeCallback();
			}
		}

		/**
		 *
		 * 更新
		 *
		 * @param overtime 加时
		 *
		 */
		void Timer::Update(int64_t overtime)
		{
			int64_t timestamp = Timestamp();

			int64_t interval = timestamp - _lastTimestamp;

			if (overtime > 0)
			{
				if (interval < overtime)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(overtime - interval));

					_lastTimestamp += overtime;

					interval = overtime;
				}
				else
				{
					_lastTimestamp = timestamp;
				}
			}
			else
			{
				_lastTimestamp = timestamp;
			}

			for (int64_t i = 0; i < interval; i++)
			{
				Executes();
			}
		}

		/**
		 *
		 * 刷新
		 *
		 * @param task 任务
		 *
		 */
		void Timer::Refresh(const std::shared_ptr<TimerTask> & task)
		{
			if (task == nullptr)
			{
				return;
			}

			Refresh(task, task->TaskCount(), task->Interval());
		}

		/**
		 *
		 * 刷新
		 *
		 * @param task 任务
		 * @param count 次数
		 * @param interval 间隔(毫秒)
		 *
		 */
		void Timer::Refresh(const std::shared_ptr<TimerTask> & task, int64_t count, int64_t interval)
		{
			if (count == 0 || interval <= 0)
			{
				return;
			}

			if (task == nullptr || task->_timer != this)
			{
				return;
			}

			task->_timer = this;
			task->_expire = _tickTimestamp + interval;
			task->_isPause = false;
			task->_interval = interval;
			task->_taskCount = count;
			task->_remainCount = count;
			task->_triggerCount = 0;
			task->_pauseTimestamp = 0;

			if (task != _currentTask)
			{
				Post(task);
			}

			_tasks.insert(task);

			if (task->_refreshCallback)
			{
				task->_refreshCallback();
			}
		}

		/**
		 *
		 * 任务个数
		 *
		 * @return 任务个数
		 *
		 */
		std::size_t Timer::TaskCount() const
		{
			return _tasks.size();
		}

		/**
		 *
		 * 提交
		 *
		 * @param task 任务
		 *
		 */
		void Timer::Post(const std::shared_ptr<TimerTask> & task)
		{
			int64_t expire = task->_expire;
			int64_t offset = expire - _tickTimestamp;

			if (offset < RANK_WHEEL_MIN(0)) /// 1 << 8 ==> 256
			{
				_rootWheel[ROOT_WHEEL_SITE(expire)].push_back(task); /// expire & 255
			}
			else if (offset < RANK_WHEEL_MIN(1)) /// 1 << 14 ==> 16384
			{
				_rankWheels[0][RANK_WHEEL_SITE(expire, 0)].push_back(task); /// (expire >> 8) & 63
			}
			else if (offset < RANK_WHEEL_MIN(2)) /// 1 << 20 ==> 1048576
			{
				_rankWheels[1][RANK_WHEEL_SITE(expire, 1)].push_back(task); /// (expire >> 14) & 63
			}
			else if (offset < RANK_WHEEL_MIN(3)) /// 1 << 26 ==> 67108864
			{
				_rankWheels[2][RANK_WHEEL_SITE(expire, 2)].push_back(task); /// (expire >> 20) & 63
			}
			else if (offset < RANK_WHEEL_MIN(4)) /// 1 << 32 ==> 4294967296
			{
				_rankWheels[3][RANK_WHEEL_SITE(expire, 3)].push_back(task); /// (expire >> 26) & 63
			}
			else
			{
				expire = 0xFFFFFFFFUL + _tickTimestamp;

				_rankWheels[3][RANK_WHEEL_SITE(expire, 3)].push_back(task); /// (expire >> 26) & 63
			}
		}

		/**
		 *
		 * 执行
		 *
		 */
		void Timer::Executes()
		{
			auto index = static_cast<std::size_t>((++_tickTimestamp) & TVR_MASK);

			if (index == 0)
			{
				if (Rotate(0, static_cast<std::size_t>(RANK_WHEEL_SITE(_tickTimestamp, 0))) &&
					Rotate(1, static_cast<std::size_t>(RANK_WHEEL_SITE(_tickTimestamp, 1))) &&
					Rotate(2, static_cast<std::size_t>(RANK_WHEEL_SITE(_tickTimestamp, 2))))
				{
					Rotate(3, static_cast<std::size_t>(RANK_WHEEL_SITE(_tickTimestamp, 3)));
				}
			}

			if (_rootWheel[index].empty())
			{
				return;
			}

			std::vector<std::shared_ptr<TimerTask>> tasks{ };

			_rootWheel[index].swap(tasks);

			for (auto & task : tasks)
			{
				if (task == nullptr)
				{
					continue;
				}

				if (task->_isPause)
				{
					continue;
				}

				if (task->_expire > _tickTimestamp)
				{
					Post(task);

					continue;
				}

				if (task->_remainCount == 0)
				{
					continue;
				}

				_currentTask = task;

				++task->_triggerCount;

				if (task->_remainCount > 0)
				{
					if (--task->_remainCount == 0)
					{
						task->_timer = nullptr;
						task->_expire = 0;
						task->_isPause = false;
						task->_remainCount = 0;
						task->_pauseTimestamp = 0;

						_tasks.erase(task);
					}
				}

				if (task->_triggerCallback)
				{
					task->_triggerCallback();
				}

				if (task->_remainCount != 0)
				{
					task->_expire = _tickTimestamp + task->_interval;

					Post(task);
				}

				_currentTask = nullptr;
			}
		}

		/**
		 *
		 * 转动
		 *
		 * @param wheel 时间轮
		 * @param index 索引
		 *
		 * @return 是否转完一圈
		 *
		 */
		bool Timer::Rotate(std::size_t wheel, std::size_t index)
		{
			if (!_rankWheels[wheel][index].empty())
			{
				std::vector<std::shared_ptr<TimerTask>> tasks{};

				_rankWheels[wheel][index].swap(tasks);

				for (auto & task: tasks)
				{
					if (task == nullptr)
					{
						continue;
					}

					Post(task);
				}
			}

			return index == 0;
		}
	}
}
