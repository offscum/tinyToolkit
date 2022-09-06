/**
 *
 * 作者: hm
 *
 * 说明: 线程池
 *
 */


#include "threadPool.h"

#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS
#
#  include <Windows.h>
#
#elif TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_LINUX
#
#  include <sys/prctl.h>
#
#endif

#include <string>


namespace tinyToolkit
{
	namespace pool
	{
		/**
		 *
		 * 设置线程名称
		 *
		 * @param name 名称
		 *
		 * @return 是否设置成功
		 *
		 */
		static inline bool SetThreadName(const std::string & name)
		{
		#if TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_WINDOWS

			typedef struct THREAD_NAME_INFO
			{
				DWORD type;
				LPCSTR name;
				DWORD id;
				DWORD flag;
			}THREAD_NAME_INFO;

			THREAD_NAME_INFO info{ 0x1000, name.c_str(), static_cast<DWORD>(-1), 0 };

			__try
			{
				RaiseException( 0x406D1388, 0, static_cast<DWORD>(sizeof(info) / sizeof(DWORD)), reinterpret_cast<ULONG_PTR *>(&info));
			}
			__except(EXCEPTION_CONTINUE_EXECUTION)
			{

			}

			return true;

		#elif TOOLKIT_PLATFORM_TYPE == TOOLKIT_PLATFORM_APPLE

			return ::pthread_setname_np(name.c_str()) == 0;

		#else

			return ::prctl(PR_SET_NAME, name.c_str()) == 0;

		#endif
		}


		////////////////////////////////////////////////////////////////////////////////////////////////////


		/**
		 *
		 * 构造函数
		 *
		 * @param count 线程个数
		 * @param name 名称
		 *
		 */
		ThreadPool::ThreadPool(std::size_t count, const char * name)
		{
			_idles.store(count);

			std::atomic<std::size_t> waitCounter{ count };

			for (std::size_t i = 0; i < count; ++i)
			{
				_threads.emplace_back([this, i, name, &waitCounter]() -> void
				{
					if (name)
					{
						SetThreadName(std::string(name) + "_" + std::to_string(i));
					}

					--waitCounter;

					while (_isValid)
					{
						std::function<void()> task{ };

						{
							std::unique_lock<std::mutex> lock(_mutex);

							_condition.wait(lock, [this]
							{
								return !_tasks.empty() || !_isValid;
							});

							if (!_isValid)
							{
								return;
							}

							task = std::move(_tasks.front());

							_tasks.pop();
						}

						--_idles;

						task();

						++_idles;
					}
				});
			}

			while (waitCounter)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}

		/**
		 *
		 * 析构函数
		 *
		 */
		ThreadPool::~ThreadPool()
		{
			Close();
		}

		/**
		 *
		 * 等待
		 *
		 */
		void ThreadPool::Wait() const
		{
			if (!IsValid())
			{
				return;
			}

			while (!IsIdle())
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}

		/**
		 *
		 * 关闭
		 *
		 */
		void ThreadPool::Close()
		{
			_isValid = false;

			_condition.notify_all();

			for (auto & thread : _threads)
			{
				if (thread.joinable())
				{
					thread.join();
				}
			}

			_idles = 0;

			_threads.clear();
			_threads.shrink_to_fit();

			std::queue<std::function<void()>>{ }.swap(_tasks);
		}

		/**
		 *
		 * 是否为空闲状态
		 *
		 * @return 是否为空闲状态
		 *
		 */
		bool ThreadPool::IsIdle() const
		{
			std::lock_guard<std::mutex> lock(_mutex);

			return _tasks.empty() && _idles == _threads.size();
		}

		/**
		 *
		 * 是否有效
		 *
		 * @return 是否有效
		 *
		 */
		bool ThreadPool::IsValid() const
		{
			std::lock_guard<std::mutex> lock(_mutex);

			return _isValid;
		}

		/**
		 *
		 * 任务个数
		 *
		 * @return 任务个数
		 *
		 */
		std::size_t ThreadPool::TaskCount() const
		{
			std::lock_guard<std::mutex> lock(_mutex);

			return _tasks.size();
		}

		/**
		 *
		 * 线程个数
		 *
		 * @return 线程个数
		 *
		 */
		std::size_t ThreadPool::ThreadCount() const
		{
			std::lock_guard<std::mutex> lock(_mutex);

			return _threads.size();
		}
	}
}
