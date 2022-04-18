/**
 *
 * 作者: hm
 *
 * 说明: 任意类型
 *
 */


#include "any.h"


namespace tinyToolkit
{
	namespace option
	{
		/**
		 *
		 * 移动构造函数
		 *
		 * @param rhs 右值对象
		 *
		 */
		Any::Any(Any && rhs) noexcept : _content(std::move(rhs._content))
		{

		}

		/**
		 *
		 * 拷贝构造函数
		 *
		 * @param lhs 左值对象
		 *
		 */
		Any::Any(const Any & lhs) : _content(lhs._content ? lhs._content->Clone() : nullptr)
		{

		}

		/**
		 *
		 * 重置
		 *
		 */
		void Any::Reset()
		{
			_content.reset();
		}

		/**
		 *
		 * 是否有数据
		 *
		 * @return 是否有数据
		 *
		 */
		bool Any::HasValue() const
		{
			return _content != nullptr;
		}

		/**
		 *
		 * 重载=操作
		 *
		 * @param rhs 右值对象
		 *
		 * @return 对象
		 *
		 */
		Any & Any::operator=(Any && rhs) noexcept
		{
			if (this != &rhs)
			{
				_content = std::move(rhs._content);
			}

			return *this;
		}

		/**
		 *
		 * 重载=操作
		 *
		 * @param lhs 左值对象
		 *
		 * @return 对象
		 *
		 */
		Any & Any::operator=(const Any & lhs)
		{
			if (this != &lhs)
			{
				_content = lhs._content ? lhs._content->Clone() : nullptr;
			}

			return *this;
		}
	}
}
