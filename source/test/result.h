#ifndef __TEST__RESULT__H__
#define __TEST__RESULT__H__


/**
 *
 * 作者: hm
 *
 * 说明: 结果
 *
 */


#include "message.h"


namespace tinyToolkit
{
	namespace test
	{
		class TOOLKIT_API Result
		{
		public:
			/**
			 *
			 * 构造函数
			 *
			 * @param status 状态
			 *
			 */
			explicit Result(bool status);

			/**
			 *
			 * 移动构造函数
			 *
			 * @param rhs 右值对象
			 *
			 */
			Result(Result && rhs) noexcept;

			/**
			 *
			 * 复制构造函数
			 *
			 * @param lhs 左值对象
			 *
			 */
			Result(const Result & lhs) = default;

		public:
			/**
			 *
			 * 内容
			 *
			 * @return 内容
			 *
			 */
			const std::string & Content() const;

		public:
			/**
			 *
			 * 重载bool类型转换
			 *
			 * @return 转换结果
			 *
			 */
			explicit operator bool() const;

			/**
			 *
			 * 重载=操作
			 *
			 * @param rhs 右值对象
			 *
			 * @return 对象
			 *
			 */
			Result & operator=(Result && rhs) noexcept;

			/**
			 *
			 * 重载=操作
			 *
			 * @param lhs 左值对象
			 *
			 * @return 对象
			 *
			 */
			Result & operator=(const Result & lhs) = default;

			/**
			 *
			 * 重载<<操作
			 *
			 * @param content 内容
			 *
			 * @return 对象
			 *
			 */
			template <typename ContentType>
			Result & operator<<(ContentType && content)
			{
				AppendMessage(Message() << content);

				return *this;
			}

		private:
			/**
			 *
			 * 添加信息
			 *
			 * @param message 信息
			 *
			 */
			void AppendMessage(const Message & message);

		private:
			bool _status{ false };

			std::string _content{ };
		};
	}
}


#endif // __TEST__RESULT__H__
