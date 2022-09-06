#ifndef __OPTION__VALUE__H__
#define __OPTION__VALUE__H__


/**
 *
 * 作者: hm
 *
 * 说明: 数据
 *
 */


#include "any.h"
#include "traits.h"


namespace tinyToolkit
{
	namespace option
	{
		class TOOLKIT_API BasicValue
		{
		public:
			/**
			 *
			 * 析构函数
			 *
			 */
			virtual ~BasicValue() = default;

		public:
			/**
			 *
			 * 是否有数据
			 *
			 * @return 是否有数据
			 *
			 */
			virtual bool HasValue() const = 0;

			/**
			 *
			 * 是否有默认值
			 *
			 * @return 是否有默认值
			 *
			 */
			virtual bool HasDefault() const = 0;

			/**
			 *
			 * 类型
			 *
			 * @return 类型
			 *
			 */
			virtual VALUE_TYPE Type() const = 0;

			/**
			 *
			 * 默认值
			 *
			 * @return 默认值
			 *
			 */
			virtual std::string Default() = 0;
		};

		template <typename ValueType>
		class TOOLKIT_API ActualValue final : public BasicValue
		{
		public:
			/**
			 *
			 * 构造函数
			 *
			 */
			ActualValue() : _type(Traits<ValueType>::type)
			{

			}

			/**
			 *
			 * 移动构造函数
			 *
			 * @param rhs 右值对象
			 *
			 */
			ActualValue(ActualValue && rhs) noexcept : _value(std::move(rhs._value)),
														_default(std::move(rhs._default)),
														_type(rhs._type)
			{

			}

			/**
			 *
			 * 拷贝构造函数
			 *
			 * @param lhs 左值对象
			 *
			 */
			ActualValue(const ActualValue & lhs) : _value(lhs._value),
													_default(lhs._default),
													_type(lhs._type)
			{

			}

			/**
			 *
			 * 构造函数
			 *
			 * @param value 默认数据
			 *
			 */
			explicit ActualValue(ValueType && value) : _value(std::move(value)),
														_default(std::move(_value.Get<ValueType>())),
														_type(Traits<ValueType>::type)
			{

			}

			/**
			 *
			 * 构造函数
			 *
			 * @param value 默认数据
			 *
			 */
			explicit ActualValue(const ValueType & value) : _value(value),
															_default(value),
															_type(Traits<ValueType>::type)
			{

			}

			/**
			 *
			 * 析构函数
			 *
			 */
			~ActualValue() override = default;

		public:
			/**
			 *
			 * 是否有数据
			 *
			 * @return 是否有数据
			 *
			 */
			bool HasValue() const override
			{
				return _value.HasValue();
			}

			/**
			 *
			 * 是否有默认值
			 *
			 * @return 是否有默认值
			 *
			 */
			bool HasDefault() const override
			{
				return _default.HasValue();
			}

			/**
			 *
			 * 类型
			 *
			 * @return 类型
			 *
			 */
			VALUE_TYPE Type() const override
			{
				return _type;
			}

			/**
			 *
			 * 默认值
			 *
			 * @return 默认值
			 *
			 */
			std::string Default() override
			{
				return HasDefault() ? ToString<ValueType>(_default.template Get<ValueType>()) : std::string{ };
			}

		private:
			/**
			 *
			 * 转换字符串
			 *
			 * @param content 内容
			 *
			 * @return 字符串
			 *
			 */
			template <typename ContentType>
			typename std::enable_if
			<
				std::is_same<ContentType, bool>::value, std::string
			>::type
			ToString(ContentType content)
			{
				return content ? "true" : "false";
			}

			/**
			 *
			 * 转换字符串
			 *
			 * @param content 内容
			 *
			 * @return 字符串
			 *
			 */
			template <typename ContentType>
			typename std::enable_if
			<
				std::is_same<ContentType, float>::value ||
				std::is_same<ContentType, double>::value ||
				std::is_same<ContentType, long double>::value ||
				std::is_same<ContentType, int8_t>::value ||
				std::is_same<ContentType, uint8_t>::value ||
				std::is_same<ContentType, int16_t>::value ||
				std::is_same<ContentType, uint16_t>::value ||
				std::is_same<ContentType, int32_t>::value ||
				std::is_same<ContentType, uint32_t>::value ||
				std::is_same<ContentType, int64_t>::value ||
				std::is_same<ContentType, uint64_t>::value,
				std::string
			>::type
			ToString(ContentType content)
			{
				return std::to_string(content);
			}

			/**
			 *
			 * 转换字符串
			 *
			 * @param content 内容
			 *
			 * @return 字符串
			 *
			 */
			template <typename ContentType>
			typename std::enable_if
			<
				std::is_same<ContentType, std::string>::value, std::string
			>::type
			ToString(ContentType content)
			{
				return content;
			}

		public:
			Any _value{ };
			Any _default{ };

			VALUE_TYPE _type{ VALUE_TYPE::UNKNOWN };
		};

		/**
		 *
		 * 数据
		 *
		 * @return 数据
		 *
		 */
		template <typename ValueType>
		std::shared_ptr<ActualValue<ValueType>> Value()
		{
			return std::make_shared<ActualValue<ValueType>>();
		}

		/**
		 *
		 * 数据
		 *
		 * @param value 默认值
		 *
		 * @return 数据
		 *
		 */
		template <typename ValueType>
		std::shared_ptr<ActualValue<ValueType>> Value(ValueType && value)
		{
			return std::make_shared<ActualValue<ValueType>>(std::forward<ValueType>(value));
		}
	}
}


#endif // __OPTION__VALUE__H__
