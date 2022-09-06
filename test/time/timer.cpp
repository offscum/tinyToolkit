/**
 *
 * 作者: hm
 *
 * 说明: 定时器
 *
 */


#include "timer.h"


TOOLKIT_TEST_CASE(Timer, Post_Function)
{
	int64_t count{ 3 };
	int64_t remain{ 3 };
	int64_t interval{ 3 };

	std::size_t number{ 1 };

	tinyToolkit::time::Timer timer{ };

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(0));

	timer.Post([&]()
	{
		--remain;

		number *= number + 10;

		TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(remain ? 1 : 0));
	}, count, interval);

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

	while (timer.TaskCount())
	{
		timer.Update();
	}

	TOOLKIT_EXPECT_EQ(number, static_cast<std::size_t>(55671));

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(0));
}

TOOLKIT_TEST_CASE(Timer, Post_Task)
{
	int64_t count{ 3 };
	int64_t remain{ 3 };
	int64_t interval{ 3 };

	std::size_t number{ 1 };

	tinyToolkit::time::Timer timer{ };

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(0));

	auto task = std::make_shared<tinyToolkit::time::TimerTask>();

	TOOLKIT_EXPECT_EQ(task->Interval(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(task->TaskCount(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(task->RemainCount(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(0));

	TOOLKIT_EXPECT_FALSE(task->IsPause());
	TOOLKIT_EXPECT_FALSE(task->IsValid());

	task->OnTrigger([&]()
	{
		--remain;

		number *= number + 10;

		TOOLKIT_EXPECT_EQ(task->Interval(), interval);
		TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
		TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
		TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

		TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(remain ? 1 : 0));

		TOOLKIT_EXPECT_TRUE(remain ? task->IsValid() : !task->IsValid());

		TOOLKIT_EXPECT_FALSE(task->IsPause());
	});

	timer.Post(task, count, interval);

	TOOLKIT_EXPECT_EQ(task->Interval(), interval);
	TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
	TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
	TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(0));

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

	TOOLKIT_EXPECT_TRUE(task->IsValid());

	TOOLKIT_EXPECT_FALSE(task->IsPause());

	while (task->IsValid())
	{
		timer.Update();
	}

	TOOLKIT_EXPECT_EQ(number, static_cast<std::size_t>(55671));

	TOOLKIT_EXPECT_EQ(task->Interval(), interval);
	TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
	TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
	TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(0));

	TOOLKIT_EXPECT_FALSE(task->IsValid());
	TOOLKIT_EXPECT_FALSE(task->IsPause());
}

TOOLKIT_TEST_CASE(Timer, Close)
{
	int64_t count{ 3 };
	int64_t remain{ 3 };
	int64_t interval{ 3 };

	std::size_t number{ 1 };

	tinyToolkit::time::Timer timer{ };

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(0));

	auto task = std::make_shared<tinyToolkit::time::TimerTask>();

	TOOLKIT_EXPECT_EQ(task->Interval(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(task->TaskCount(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(task->RemainCount(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(0));

	TOOLKIT_EXPECT_FALSE(task->IsPause());
	TOOLKIT_EXPECT_FALSE(task->IsValid());

	task->OnTrigger([&]()
	{
		--remain;

		number *= number + 10;

		TOOLKIT_EXPECT_EQ(task->Interval(), interval);
		TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
		TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
		TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

		TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

		TOOLKIT_EXPECT_TRUE(task->IsValid());

		TOOLKIT_EXPECT_FALSE(task->IsPause());

		timer.Close();

		TOOLKIT_EXPECT_EQ(task->Interval(), interval);
		TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
		TOOLKIT_EXPECT_EQ(task->RemainCount(), static_cast<int64_t>(0));
		TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

		TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(0));

		TOOLKIT_EXPECT_FALSE(task->IsPause());
		TOOLKIT_EXPECT_FALSE(task->IsValid());
	});

	timer.Post(task, count, interval);

	TOOLKIT_EXPECT_EQ(task->Interval(), interval);
	TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
	TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
	TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(0));

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

	TOOLKIT_EXPECT_TRUE(task->IsValid());

	TOOLKIT_EXPECT_FALSE(task->IsPause());

	while (task->IsValid())
	{
		timer.Update();
	}

	TOOLKIT_EXPECT_EQ(number, static_cast<std::size_t>(11));

	TOOLKIT_EXPECT_EQ(task->Interval(), interval);
	TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
	TOOLKIT_EXPECT_EQ(task->RemainCount(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(0));

	TOOLKIT_EXPECT_FALSE(task->IsValid());
	TOOLKIT_EXPECT_FALSE(task->IsPause());
}

TOOLKIT_TEST_CASE(Timer, Pause)
{
	int64_t count{ 3 };
	int64_t remain{ 3 };
	int64_t interval{ 3 };

	std::size_t number{ 1 };

	tinyToolkit::time::Timer timer{ };

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(0));

	auto task = std::make_shared<tinyToolkit::time::TimerTask>();

	TOOLKIT_EXPECT_EQ(task->Interval(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(task->TaskCount(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(task->RemainCount(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(0));

	TOOLKIT_EXPECT_FALSE(task->IsPause());
	TOOLKIT_EXPECT_FALSE(task->IsValid());

	task->OnPause([&]()
	{
		TOOLKIT_EXPECT_EQ(task->Interval(), interval);
		TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
		TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
		TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

		TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

		TOOLKIT_EXPECT_TRUE(task->IsPause());
		TOOLKIT_EXPECT_TRUE(task->IsValid());
	});

	task->OnTrigger([&]()
	{
		--remain;

		number *= number + 10;

		TOOLKIT_EXPECT_EQ(task->Interval(), interval);
		TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
		TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
		TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

		TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

		TOOLKIT_EXPECT_TRUE(task->IsValid());

		TOOLKIT_EXPECT_FALSE(task->IsPause());

		timer.Pause(task);

		TOOLKIT_EXPECT_EQ(task->Interval(), interval);
		TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
		TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
		TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

		TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

		TOOLKIT_EXPECT_TRUE(task->IsPause());
		TOOLKIT_EXPECT_TRUE(task->IsValid());
	});

	timer.Post(task, count, interval);

	TOOLKIT_EXPECT_EQ(task->Interval(), interval);
	TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
	TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
	TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(0));

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

	TOOLKIT_EXPECT_TRUE(task->IsValid());

	TOOLKIT_EXPECT_FALSE(task->IsPause());

	while (!task->IsPause())
	{
		timer.Update();
	}

	TOOLKIT_EXPECT_EQ(number, static_cast<std::size_t>(11));

	TOOLKIT_EXPECT_EQ(task->Interval(), interval);
	TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
	TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
	TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

	TOOLKIT_EXPECT_TRUE(task->IsPause());
	TOOLKIT_EXPECT_TRUE(task->IsValid());
}

TOOLKIT_TEST_CASE(Timer, Cancel)
{
	int64_t count{ 3 };
	int64_t remain{ 3 };
	int64_t interval{ 3 };

	std::size_t number{ 1 };

	tinyToolkit::time::Timer timer{ };

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(0));

	auto task = std::make_shared<tinyToolkit::time::TimerTask>();

	TOOLKIT_EXPECT_EQ(task->Interval(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(task->TaskCount(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(task->RemainCount(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(0));

	TOOLKIT_EXPECT_FALSE(task->IsPause());
	TOOLKIT_EXPECT_FALSE(task->IsValid());

	task->OnCancel([&]()
	{
		TOOLKIT_EXPECT_EQ(task->Interval(), interval);
		TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
		TOOLKIT_EXPECT_EQ(task->RemainCount(), static_cast<int64_t>(0));
		TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

		TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(0));

		TOOLKIT_EXPECT_FALSE(task->IsPause());
		TOOLKIT_EXPECT_FALSE(task->IsValid());
	});

	task->OnTrigger([&]()
	{
		--remain;

		number *= number + 10;

		TOOLKIT_EXPECT_EQ(task->Interval(), interval);
		TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
		TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
		TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

		TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

		TOOLKIT_EXPECT_TRUE(task->IsValid());

		TOOLKIT_EXPECT_FALSE(task->IsPause());

		timer.Cancel(task);

		TOOLKIT_EXPECT_EQ(task->Interval(), interval);
		TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
		TOOLKIT_EXPECT_EQ(task->RemainCount(), static_cast<int64_t>(0));
		TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

		TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(0));

		TOOLKIT_EXPECT_FALSE(task->IsPause());
		TOOLKIT_EXPECT_FALSE(task->IsValid());
	});

	timer.Post(task, count, interval);

	TOOLKIT_EXPECT_EQ(task->Interval(), interval);
	TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
	TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
	TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(0));

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

	TOOLKIT_EXPECT_TRUE(task->IsValid());

	TOOLKIT_EXPECT_FALSE(task->IsPause());

	while (task->IsValid())
	{
		timer.Update();
	}

	TOOLKIT_EXPECT_EQ(number, static_cast<std::size_t>(11));

	TOOLKIT_EXPECT_EQ(task->Interval(), interval);
	TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
	TOOLKIT_EXPECT_EQ(task->RemainCount(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(0));

	TOOLKIT_EXPECT_FALSE(task->IsPause());
	TOOLKIT_EXPECT_FALSE(task->IsValid());
}

TOOLKIT_TEST_CASE(Timer, Resume)
{
	int64_t count{ 3 };
	int64_t remain{ 3 };
	int64_t interval{ 3 };

	std::size_t number{ 1 };

	tinyToolkit::time::Timer timer{ };

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(0));

	auto task = std::make_shared<tinyToolkit::time::TimerTask>();

	TOOLKIT_EXPECT_EQ(task->Interval(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(task->TaskCount(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(task->RemainCount(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(0));

	TOOLKIT_EXPECT_FALSE(task->IsPause());
	TOOLKIT_EXPECT_FALSE(task->IsValid());

	task->OnPause([&]()
	{
		TOOLKIT_EXPECT_EQ(task->Interval(), interval);
		TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
		TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
		TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

		TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

		TOOLKIT_EXPECT_TRUE(task->IsPause());
		TOOLKIT_EXPECT_TRUE(task->IsValid());
	});

	task->OnResume([&]()
	{
		TOOLKIT_EXPECT_EQ(task->Interval(), interval);
		TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
		TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
		TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

		TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

		TOOLKIT_EXPECT_TRUE(task->IsValid());

		TOOLKIT_EXPECT_FALSE(task->IsPause());

		task->OnTrigger([&]()
		{
			--remain;

			number *= number + 10;

			TOOLKIT_EXPECT_EQ(task->Interval(), interval);
			TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
			TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
			TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

			TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(remain ? 1 : 0));

			TOOLKIT_EXPECT_TRUE(remain ? task->IsValid() : !task->IsValid());

			TOOLKIT_EXPECT_FALSE(task->IsPause());
		});
	});

	task->OnTrigger([&]()
	{
		--remain;

		number *= number + 10;

		TOOLKIT_EXPECT_EQ(task->Interval(), interval);
		TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
		TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
		TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

		TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

		TOOLKIT_EXPECT_TRUE(task->IsValid());

		TOOLKIT_EXPECT_FALSE(task->IsPause());

		timer.Pause(task);

		TOOLKIT_EXPECT_EQ(task->Interval(), interval);
		TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
		TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
		TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

		TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

		TOOLKIT_EXPECT_TRUE(task->IsPause());
		TOOLKIT_EXPECT_TRUE(task->IsValid());
	});

	timer.Post(task, count, interval);

	TOOLKIT_EXPECT_EQ(task->Interval(), interval);
	TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
	TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
	TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(0));

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

	TOOLKIT_EXPECT_TRUE(task->IsValid());

	TOOLKIT_EXPECT_FALSE(task->IsPause());

	while (!task->IsPause())
	{
		timer.Update();
	}

	TOOLKIT_EXPECT_EQ(number, static_cast<std::size_t>(11));

	TOOLKIT_EXPECT_EQ(task->Interval(), interval);
	TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
	TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
	TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

	TOOLKIT_EXPECT_TRUE(task->IsPause());
	TOOLKIT_EXPECT_TRUE(task->IsValid());

	timer.Resume(task);

	while (task->IsValid())
	{
		timer.Update();
	}

	TOOLKIT_EXPECT_EQ(number, static_cast<std::size_t>(55671));

	TOOLKIT_EXPECT_EQ(task->Interval(), interval);
	TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
	TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
	TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(0));

	TOOLKIT_EXPECT_FALSE(task->IsPause());
	TOOLKIT_EXPECT_FALSE(task->IsValid());
}

TOOLKIT_TEST_CASE(Timer, Refresh)
{
	int64_t count{ 3 };
	int64_t remain{ 3 };
	int64_t interval{ 3 };

	std::size_t number{ 1 };

	tinyToolkit::time::Timer timer{ };

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(0));

	auto task = std::make_shared<tinyToolkit::time::TimerTask>();

	TOOLKIT_EXPECT_EQ(task->Interval(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(task->TaskCount(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(task->RemainCount(), static_cast<int64_t>(0));
	TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(0));

	TOOLKIT_EXPECT_FALSE(task->IsPause());
	TOOLKIT_EXPECT_FALSE(task->IsValid());

	task->OnPause([&]()
	{
		TOOLKIT_EXPECT_EQ(task->Interval(), interval);
		TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
		TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
		TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

		TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

		TOOLKIT_EXPECT_TRUE(task->IsPause());
		TOOLKIT_EXPECT_TRUE(task->IsValid());
	});

	task->OnRefresh([&]()
	{
		TOOLKIT_EXPECT_EQ(task->Interval(), interval);
		TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
		TOOLKIT_EXPECT_EQ(task->RemainCount(), count);
		TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(0));

		TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

		TOOLKIT_EXPECT_TRUE(task->IsValid());

		TOOLKIT_EXPECT_FALSE(task->IsPause());

		remain = count;

		task->OnTrigger([&]()
		{
			--remain;

			number *= number + 10;

			TOOLKIT_EXPECT_EQ(task->Interval(), interval);
			TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
			TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
			TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

			TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(remain ? 1 : 0));

			TOOLKIT_EXPECT_TRUE(remain ? task->IsValid() : !task->IsValid());

			TOOLKIT_EXPECT_FALSE(task->IsPause());
		});
	});

	task->OnTrigger([&]()
	{
		--remain;

		number *= number + 10;

		TOOLKIT_EXPECT_EQ(task->Interval(), interval);
		TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
		TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
		TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

		TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

		TOOLKIT_EXPECT_TRUE(task->IsValid());

		TOOLKIT_EXPECT_FALSE(task->IsPause());

		timer.Pause(task);

		TOOLKIT_EXPECT_EQ(task->Interval(), interval);
		TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
		TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
		TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

		TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

		TOOLKIT_EXPECT_TRUE(task->IsPause());
		TOOLKIT_EXPECT_TRUE(task->IsValid());
	});

	timer.Post(task, count, interval);

	TOOLKIT_EXPECT_EQ(task->Interval(), interval);
	TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
	TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
	TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(0));

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

	TOOLKIT_EXPECT_TRUE(task->IsValid());

	TOOLKIT_EXPECT_FALSE(task->IsPause());

	while (!task->IsPause())
	{
		timer.Update();
	}

	TOOLKIT_EXPECT_EQ(number, static_cast<std::size_t>(11));

	TOOLKIT_EXPECT_EQ(task->Interval(), interval);
	TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
	TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
	TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(1));

	TOOLKIT_EXPECT_TRUE(task->IsPause());
	TOOLKIT_EXPECT_TRUE(task->IsValid());

	timer.Refresh(task);

	while (task->IsValid())
	{
		timer.Update();
	}

	TOOLKIT_EXPECT_EQ(number, static_cast<std::size_t>(3099816951));

	TOOLKIT_EXPECT_EQ(task->Interval(), interval);
	TOOLKIT_EXPECT_EQ(task->TaskCount(), count);
	TOOLKIT_EXPECT_EQ(task->RemainCount(), remain);
	TOOLKIT_EXPECT_EQ(task->TriggerCount(), static_cast<std::size_t>(count - remain));

	TOOLKIT_EXPECT_EQ(timer.TaskCount(), static_cast<std::size_t>(0));

	TOOLKIT_EXPECT_FALSE(task->IsPause());
	TOOLKIT_EXPECT_FALSE(task->IsValid());
}
