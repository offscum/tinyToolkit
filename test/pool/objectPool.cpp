/**
 *
 * 作者: hm
 *
 * 说明: 对象池
 *
 */


#include "objectPool.h"


TOOLKIT_TEST_CASE(ObjectPool, ObjectPool)
{
	class Object
	{
	public:
		explicit Object(int32_t val, std::atomic<int32_t> & ref) : _val(val), _ref(ref)
		{

		}

		~Object()
		{
			_ref += _val;
		}

		int32_t Value() const
		{
			return _val * _val;
		}

	private:
		int32_t _val{ 0 };

		std::atomic<int32_t> & _ref;
	};

	std::atomic<int32_t> count{ 0 };

	tinyToolkit::pool::ObjectPool<Object, 3> pool;

	TOOLKIT_EXPECT_EQ(count.load(), 0);
	TOOLKIT_EXPECT_EQ(pool.Count(), static_cast<std::size_t>(0));
	TOOLKIT_EXPECT_EQ(pool.LendCount(), static_cast<std::size_t>(0));

	auto obj1 = pool.Lend(11, count);

	TOOLKIT_EXPECT_TRUE(obj1 != nullptr);

	TOOLKIT_EXPECT_EQ(obj1->Value(), 121);
	TOOLKIT_EXPECT_EQ(count.load(), 0);
	TOOLKIT_EXPECT_EQ(pool.Count(), static_cast<std::size_t>(3));
	TOOLKIT_EXPECT_EQ(pool.LendCount(), static_cast<std::size_t>(1));

	auto obj2 = pool.Lend(22, count);

	TOOLKIT_EXPECT_TRUE(obj2 != nullptr);

	TOOLKIT_EXPECT_EQ(obj2->Value(), 484);
	TOOLKIT_EXPECT_EQ(count.load(), 0);
	TOOLKIT_EXPECT_EQ(pool.Count(), static_cast<std::size_t>(3));
	TOOLKIT_EXPECT_EQ(pool.LendCount(), static_cast<std::size_t>(2));

	auto obj3 = pool.Lend(33, count);

	TOOLKIT_EXPECT_TRUE(obj3 != nullptr);

	TOOLKIT_EXPECT_EQ(obj3->Value(), 1089);
	TOOLKIT_EXPECT_EQ(count.load(), 0);
	TOOLKIT_EXPECT_EQ(pool.Count(), static_cast<std::size_t>(3));
	TOOLKIT_EXPECT_EQ(pool.LendCount(), static_cast<std::size_t>(3));

	auto obj4 = pool.Lend(44, count);

	TOOLKIT_EXPECT_TRUE(obj4 != nullptr);

	TOOLKIT_EXPECT_EQ(count.load(), 0);
	TOOLKIT_EXPECT_EQ(pool.Count(), static_cast<std::size_t>(6));
	TOOLKIT_EXPECT_EQ(pool.LendCount(), static_cast<std::size_t>(4));

	TOOLKIT_EXPECT_FALSE(pool.Return(nullptr));

	TOOLKIT_EXPECT_EQ(count.load(), 0);
	TOOLKIT_EXPECT_EQ(pool.Count(), static_cast<std::size_t>(6));
	TOOLKIT_EXPECT_EQ(pool.LendCount(), static_cast<std::size_t>(4));

	TOOLKIT_EXPECT_FALSE(pool.Return(reinterpret_cast<Object *>(&pool)));

	TOOLKIT_EXPECT_EQ(count.load(), 0);
	TOOLKIT_EXPECT_EQ(pool.Count(), static_cast<std::size_t>(6));
	TOOLKIT_EXPECT_EQ(pool.LendCount(), static_cast<std::size_t>(4));

	TOOLKIT_EXPECT_TRUE(pool.Return(obj1));

	TOOLKIT_EXPECT_EQ(count.load(), 11);
	TOOLKIT_EXPECT_EQ(pool.Count(), static_cast<std::size_t>(6));
	TOOLKIT_EXPECT_EQ(pool.LendCount(), static_cast<std::size_t>(3));

	pool.Close();

	TOOLKIT_EXPECT_EQ(count.load(), 110);
	TOOLKIT_EXPECT_EQ(pool.Count(), static_cast<std::size_t>(0));
	TOOLKIT_EXPECT_EQ(pool.LendCount(), static_cast<std::size_t>(0));
}
