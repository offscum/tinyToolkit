/**
 *
 * 作者: hm
 *
 * 说明: 结果
 *
 */


#include "result.h"


namespace tinyToolkit
{
	namespace test
	{
		/**
		 *
		 * 构造函数
		 *
		 * @param status 状态
		 *
		 */
		Result::Result(bool status) : _status(status)
		{

		}

		/**
		 *
		 * 移动构造函数
		 *
		 * @param rhs 右值对象
		 *
		 */
		Result::Result(Result && rhs) noexcept : _status(rhs._status),
												 _content(std::move(rhs._content))
		{

		}

		/**
		 *
		 * 内容
		 *
		 * @return 内容
		 *
		 */
		const std::string & Result::Content() const
		{
			return _content;
		}

		/**
		 *
		 * 重载bool类型转换
		 *
		 * @return 转换结果
		 *
		 */
		Result::operator bool() const
		{
			return _status;
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
		Result & Result::operator=(Result && rhs) noexcept
		{
			if (this != &rhs)
			{
				_status = rhs._status;

				_content = std::move(rhs._content);
			}

			return *this;
		}

		/**
		 *
		 * 添加信息
		 *
		 * @param message 信息
		 *
		 */
		void Result::AppendMessage(const Message & message)
		{
			_content += message.Content();
		}
	}
}
