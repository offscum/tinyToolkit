#ifndef __SYSTEM__ENDIAN__H__
#define __SYSTEM__ENDIAN__H__


/**
 *
 * 作者: hm
 *
 * 说明: 字节序
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"


namespace tinyToolkit
{
	namespace system
	{
		/**
		 *
		 * 是否是大端字节序
		 *
		 * @return 是否是大端字节序
		 *
		 */
		TOOLKIT_API bool IsBigEndian();

		/**
		 *
		 * 是否是小端字节序
		 *
		 * @return 是否是小端字节序
		 *
		 */
		TOOLKIT_API bool IsLittleEndian();
	}
}


#endif // __SYSTEM__ENDIAN__H__
