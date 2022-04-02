#ifndef __TEST__MESSAGE__H__
#define __TEST__MESSAGE__H__


/**
 *
 * 作者: hm
 *
 * 说明: 信息
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"

#include <string>
#include <cstdint>


namespace tinyToolkit
{
	namespace test
	{
		class TOOLKIT_API Message
		{
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
			 * 重载<<操作
			 *
			 * @param content 内容
			 *
			 * @return 对象
			 *
			 */
			Message & operator<<(bool content);

			/**
			 *
			 * 重载<<操作
			 *
			 * @param content 内容
			 *
			 * @return 对象
			 *
			 */
			Message & operator<<(int8_t content);

			/**
			 *
			 * 重载<<操作
			 *
			 * @param content 内容
			 *
			 * @return 对象
			 *
			 */
			Message & operator<<(uint8_t content);

			/**
			 *
			 * 重载<<操作
			 *
			 * @param content 内容
			 *
			 * @return 对象
			 *
			 */
			Message & operator<<(const std::string & content);

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
			Message & operator<<(ContentType content)
			{
				_content += std::to_string(content);

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
			template <typename ContentType>
			Message & operator<<(const ContentType * content)
			{
				_content += content ? content : "(null)";

				return *this;
			}

		private:
			std::string _content{ };
		};
	}
}


#endif // __TEST__MESSAGE__H__
