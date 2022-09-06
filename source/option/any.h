#ifndef __OPTION__ANY__H__
#define __OPTION__ANY__H__


/**
 *
 * 作者: hm
 *
 * 说明: 任意类型
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"

#include <memory>
#include <stdexcept>


namespace tinyToolkit
{
	namespace option
	{
		class TOOLKIT_API Any
		{
			class TOOLKIT_API IStorage
			{
			public:
				/**
				 *
				 * 析构函数
				 *
				 */
				virtual ~IStorage() = default;

			public:
				/**
				 *
				 * 克隆
				 *
				 * @return 对象
				 *
				 */
				virtual std::unique_ptr<IStorage> Clone() = 0;

				/**
				 *
				 * 类型
				 *
				 * @return 类型
				 *
				 */
				virtual const std::type_info & Type() const = 0;
			};

			template <typename ValueType>
			class TOOLKIT_API Storage final : public IStorage
			{
			public:
				/**
				 *
				 * 构造函数
				 *
				 * @param content 内容
				 *
				 */
				template <typename ContentType>
				explicit Storage(ContentType && content) : _value(std::forward<ContentType>(content))
				{

				}

				/**
				 *
				 * 析构函数
				 *
				 */
				~Storage() override = default;

			public:
				/**
				 *
				 * 克隆
				 *
				 * @return 对象
				 *
				 */
				std::unique_ptr<IStorage> Clone() override
				{
					return std::unique_ptr<IStorage>(new Storage<ValueType>(_value));
				}

				/**
				 *
				 * 类型
				 *
				 * @return 类型
				 *
				 */
				const std::type_info & Type() const override
				{
					return typeid(ValueType);
				}

			public:
				ValueType _value;
			};

		public:
			/**
			 *
			 * 构造函数
			 *
			 */
			Any() = default;

			/**
			 *
			 * 移动构造函数
			 *
			 * @param rhs 右值对象
			 *
			 */
			Any(Any && rhs) noexcept;

			/**
			 *
			 * 拷贝构造函数
			 *
			 * @param lhs 左值对象
			 *
			 */
			Any(const Any & lhs);

			/**
			 *
			 * 构造函数
			 *
			 * @param value 内容
			 *
			 */
			template <typename ValueType>
			explicit Any(ValueType && value) : _content(new Storage<typename std::decay<ValueType>::type>(std::forward<ValueType>(value)))
			{

			}

		public:
			/**
			 *
			 * 重置
			 *
			 */
			void Reset();

			/**
			 *
			 * 是否符合类型
			 *
			 * @return 是否符合类型
			 *
			 */
			template <typename ValueType>
			bool Is() const
			{
				return _content->Type() == typeid(ValueType);
			}

			/**
			 *
			 * 是否有数据
			 *
			 * @return 是否有数据
			 *
			 */
			bool HasValue() const;

			/**
			 *
			 * 获取
			 *
			 * @return 内容
			 *
			 */
			template <typename ValueType>
			ValueType Get()
			{
				if (!_content)
				{
					throw std::logic_error("Can not cast nullptr");
				}

				if (!Is<ValueType>())
				{
					throw std::logic_error("Can not cast difference type");
				}

				auto pointer = dynamic_cast<Storage<ValueType> *>(_content.get());

				if (pointer == nullptr)
				{
					throw std::logic_error("cast result nullptr");
				}

				return pointer->_value;
			}

		public:
			/**
			 *
			 * 重载=操作
			 *
			 * @param rhs 右值对象
			 *
			 * @return 对象
			 *
			 */
			Any & operator=(Any && rhs) noexcept;

			/**
			 *
			 * 重载=操作
			 *
			 * @param lhs 左值对象
			 *
			 * @return 对象
			 *
			 */
			Any & operator=(const Any & lhs);

			/**
			 *
			 * 重载=操作
			 *
			 * @param value 数据
			 *
			 * @return 对象
			 *
			 */
			template <typename ValueType>
			Any & operator=(ValueType && value)
			{
				_content.reset(new Storage<typename std::decay<ValueType>::type>(std::forward<ValueType>(value)));

				return *this;
			}

		private:
			std::unique_ptr<IStorage> _content{ };
		};
	}
}


#endif // __OPTION__ANY__H__
