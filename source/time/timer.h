#ifndef __TIME__TIMER__H__
#define __TIME__TIMER__H__


/**
 *
 * 作者: hm
 *
 * 说明: 定时器
 *
 */


#include "timerTask.h"

#include <ctime>
#include <memory>
#include <vector>
#include <unordered_set>


namespace tinyToolkit
{
	namespace time
	{
		class TOOLKIT_API Timer
		{
			static const int64_t TVR_BITS = 8;
			static const int64_t TVR_SIZE = 1 << TVR_BITS;
			static const int64_t TVR_MASK = TVR_SIZE - 1;

			static const int64_t TVN_BITS = 6;
			static const int64_t TVN_SIZE = 1 << TVN_BITS;
			static const int64_t TVN_MASK = TVN_SIZE - 1;

			static const int64_t WHEEL_NUM = 4;

		public:
			/**
			 *
			 * 构造函数
			 *
			 */
			Timer();

			/**
			 *
			 * 析构函数
			 *
			 */
			~Timer();

		public:
			/**
			 *
			 * 提交
			 *
			 * @param task 任务
			 * @param count 次数
			 * @param interval 间隔(毫秒)
			 *
			 */
			void Post(const std::function<void()> & task, int64_t count, int64_t interval);

			/**
			 *
			 * 提交
			 *
			 * @param task 任务
			 * @param count 次数
			 * @param interval 间隔(毫秒)
			 *
			 */
			void Post(const std::shared_ptr<TimerTask> & task, int64_t count, int64_t interval);

			/**
			 *
			 * 清空
			 *
			 */
			void Clear();

			/**
			 *
			 * 暂停
			 *
			 * @param task 任务
			 *
			 */
			void Pause(const std::shared_ptr<TimerTask> & task);

			/**
			 *
			 * 取消
			 *
			 * @param task 任务
			 *
			 */
			void Cancel(const std::shared_ptr<TimerTask> & task);

			/**
			 *
			 * 恢复
			 *
			 * @param task 任务
			 *
			 */
			void Resume(const std::shared_ptr<TimerTask> & task);

			/**
			 *
			 * 更新
			 *
			 * @param overtime 加时
			 *
			 */
			void Update(int64_t overtime = 0);

			/**
			 *
			 * 刷新
			 *
			 * @param task 任务
			 *
			 */
			void Refresh(const std::shared_ptr<TimerTask> & task);

			/**
			 *
			 * 刷新
			 *
			 * @param task 任务
			 * @param count 次数
			 * @param interval 间隔(毫秒)
			 *
			 */
			void Refresh(const std::shared_ptr<TimerTask> & task, int64_t count, int64_t interval);

			/**
			 *
			 * 任务个数
			 *
			 * @return 任务个数
			 *
			 */
			std::size_t TaskCount() const;

		private:
			/**
			 *
			 * 提交
			 *
			 * @param task 任务
			 *
			 */
			void Post(const std::shared_ptr<TimerTask> & event);

			/**
			 *
			 * 执行
			 *
			 */
			void Executes();

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
			bool Rotate(std::size_t wheel, std::size_t index);

		private:
			int64_t _lastTimestamp{ 0 };
			int64_t _tickTimestamp{ 0 };

			std::shared_ptr<TimerTask> _currentTask{ };

			std::vector<std::shared_ptr<TimerTask>> _rootWheel[TVR_SIZE]{ };
			std::vector<std::shared_ptr<TimerTask>> _rankWheels[WHEEL_NUM][TVN_SIZE]{ };

			std::unordered_set<std::shared_ptr<TimerTask>> _tasks{ };
		};
	}
}


#endif // __TIME__TIMER__H__
