#ifndef __TEST__ENVIRONMENT__H__
#define __TEST__ENVIRONMENT__H__


/**
 *
 * 作者: hm
 *
 * 说明: 环境
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"


namespace tinyToolkit
{
	namespace test
	{
		class TOOLKIT_API Environment
		{
		public:
			/**
			 *
			 * 析构函数
			 *
			 */
			virtual ~Environment() = default;

		public:
			/**
			 *
			 * 安装
			 *
			 */
			virtual void SetUp();

			/**
			 *
			 * 卸载
			 *
			 */
			virtual void TearDown();
		};
	}
}


#endif // __TEST__ENVIRONMENT__H__
