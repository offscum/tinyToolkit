/**
 *
 * 作者: hm
 *
 * 说明: 线程池
 *
 */


#include "threadPool.h"


TOOLKIT_TEST_CASE(ThreadPool, ThreadPool)
{
	std::atomic<std::size_t> effectCount{ 0 };
	std::atomic<std::size_t> threadCount{ std::thread::hardware_concurrency() };

	tinyToolkit::pool::ThreadPool pool{ };

	TOOLKIT_EXPECT_EQ(pool.TaskCount(), static_cast<std::size_t>(0));
	TOOLKIT_EXPECT_EQ(pool.ThreadCount(), threadCount.load());

	TOOLKIT_EXPECT_TRUE(pool.IsIdle());
	TOOLKIT_EXPECT_TRUE(pool.IsValid());

	for (std::size_t i = 0; i < threadCount; ++i)
	{
		pool.Post([&]()
		{
			for (std::size_t j = 0; j < threadCount; ++j)
			{
				++effectCount;
			}

			std::this_thread::sleep_for(std::chrono::seconds(1));
		});
	}

	TOOLKIT_EXPECT_GE(pool.TaskCount(), static_cast<std::size_t>(0));
	TOOLKIT_EXPECT_EQ(pool.ThreadCount(), threadCount.load());
	TOOLKIT_EXPECT_LE(effectCount.load(), threadCount.load() * threadCount.load());

	TOOLKIT_EXPECT_TRUE(pool.IsValid());

	pool.Wait();

	TOOLKIT_EXPECT_EQ(pool.TaskCount(), static_cast<std::size_t>(0));
	TOOLKIT_EXPECT_EQ(pool.ThreadCount(), threadCount.load());
	TOOLKIT_EXPECT_EQ(effectCount.load(), threadCount.load() * threadCount.load());

	TOOLKIT_EXPECT_TRUE(pool.IsIdle());
	TOOLKIT_EXPECT_TRUE(pool.IsValid());

	pool.Close();

	TOOLKIT_EXPECT_EQ(pool.TaskCount(), static_cast<std::size_t>(0));
	TOOLKIT_EXPECT_EQ(pool.ThreadCount(), static_cast<std::size_t>(0));
	TOOLKIT_EXPECT_EQ(effectCount.load(), threadCount.load() * threadCount.load());

	TOOLKIT_EXPECT_TRUE(pool.IsIdle());
	TOOLKIT_EXPECT_FALSE(pool.IsValid());
}
