#ifndef __POOL__THREAD_POOL__H__
#define __POOL__THREAD_POOL__H__


/**
 *
 * 作者: hm
 *
 * 说明: 线程池
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"

#include <mutex>
#include <queue>
#include <atomic>
#include <thread>
#include <vector>
#include <functional>
#include <condition_variable>


namespace tinyToolkit
{
	namespace pool
	{
		class TOOLKIT_API ThreadPool
		{
		public:
			/**
			 *
			 * 构造函数
			 *
			 * @param count 线程个数
			 * @param name 名称
			 *
			 */
			explicit ThreadPool(std::size_t count = std::thread::hardware_concurrency(), const char * name = nullptr);

			/**
			 *
			 * 析构函数
			 *
			 */
			~ThreadPool();

		public:
			/**
			 *
			 * 等待
			 *
			 */
			void Wait() const;

			/**
			 *
			 * 关闭
			 *
			 */
			void Close();

			/**
			 *
			 * 提交
			 *
			 * @param function 函数
			 * @param args 参数
			 *
			 * @return 是否提交成功
			 *
			 */
			template <typename FunctionType, typename ... Args>
			bool Post(FunctionType && function, Args &&... args)
			{
				if (!_isValid)
				{
					return false;
				}

				auto task = std::bind(std::forward<FunctionType>(function), std::forward<Args>(args)...);

				{
					std::lock_guard<std::mutex> lock(_mutex);

					_tasks.emplace([task]()
					{
						task();
					});
				}

				_condition.notify_one();

				return true;
			}

			/**
			 *
			 * 是否为空闲状态
			 *
			 * @return 是否为空闲状态
			 *
			 */
			bool IsIdle() const;

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
			 * 任务个数
			 *
			 * @return 任务个数
			 *
			 */
			std::size_t TaskCount() const;

			/**
			 *
			 * 线程个数
			 *
			 * @return 线程个数
			 *
			 */
			std::size_t ThreadCount() const;

		private:
			bool _isValid{ true };

			mutable std::mutex _mutex{ };

			std::condition_variable _condition{ };

			std::atomic<std::size_t> _idles{ 0 };

			std::vector<std::thread> _threads{ };

			std::queue<std::function<void()>> _tasks{ };
		};
	}
}


#endif // __POOL__THREAD_POOL__H__
