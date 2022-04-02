#ifndef __TEST__FAILURE__H__
#define __TEST__FAILURE__H__


/**
 *
 * 作者: hm
 *
 * 说明: 失败
 *
 */


#include "message.h"


namespace tinyToolkit
{
	namespace test
	{
		class TOOLKIT_API Failure
		{
		public:
			/**
			 *
			 * 构造函数
			 *
			 * @param file 文件
			 * @param line 行号
			 * @param message 信息
			 *
			 */
			Failure(const char * file, int32_t line, const std::string & message);

		public:
			/**
			 *
			 * 重载=操作
			 *
			 * @param message 信息
			 *
			 * @return 对象
			 *
			 */
			Failure & operator=(const Message & message);
		};
	}
}


#endif // __TEST__FAILURE__H__
