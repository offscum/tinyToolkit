/**
 *
 * 作者: hm
 *
 * 说明: 信息
 *
 */


#include "message.h"


namespace tinyToolkit
{
	namespace test
	{
		/**
		 *
		 * 内容
		 *
		 * @return 内容
		 *
		 */
		const std::string & Message::Content() const
		{
			return _content;
		}

		/**
		 *
		 * 重载<<操作
		 *
		 * @param content 内容
		 *
		 * @return 对象
		 *
		 */
		Message & Message::operator<<(bool content)
		{
			_content += content ? "true" : "false";

			return *this;
		}

		/**
		 *
		 * 重载<<操作
		 *
		 * @param content 内容
		 *
		 * @return 对象
		 *
		 */
		Message & Message::operator<<(int8_t content)
		{
			_content += content;

			return *this;
		}

		/**
		 *
		 * 重载<<操作
		 *
		 * @param content 内容
		 *
		 * @return 对象
		 *
		 */
		Message & Message::operator<<(uint8_t content)
		{
			_content += static_cast<int8_t>(content);

			return *this;
		}

		/**
		 *
		 * 重载<<操作
		 *
		 * @param content 内容
		 *
		 * @return 对象
		 *
		 */
		Message & Message::operator<<(const std::string & content)
		{
			_content += content;

			return *this;
		}
	}
}
