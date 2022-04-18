#ifndef __OPTION__TYPE__H__
#define __OPTION__TYPE__H__


/**
 *
 * 作者: hm
 *
 * 说明: 类型
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"

#include <cstdint>


namespace tinyToolkit
{
	namespace option
	{
		enum class VALUE_TYPE : uint8_t
		{
			BOOL,
			FLOAT,
			DOUBLE,
			LONG_DOUBLE,
			INT8,
			UINT8,
			INT16,
			UINT16,
			INT32,
			UINT32,
			INT64,
			UINT64,
			STRING,
			UNKNOWN,
		};
	}
}


#endif // __OPTION__TYPE__H__
