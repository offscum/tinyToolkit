#ifndef __OPTION__TRAITS__H__
#define __OPTION__TRAITS__H__


/**
 *
 * 作者: hm
 *
 * 说明: 类型萃取
 *
 */


#include "type.h"

#include <string>


namespace tinyToolkit
{
	namespace option
	{
		template <typename ValueType>
		struct TOOLKIT_API Traits
		{
			static const VALUE_TYPE type = VALUE_TYPE::UNKNOWN;
		};

		#define INTERNAL_OPTION_TRAITS(t1, t2) \
			template<> \
			struct TOOLKIT_API Traits<t1> \
			{ \
				static const VALUE_TYPE type = t2; \
			};

		INTERNAL_OPTION_TRAITS(bool,			VALUE_TYPE::BOOL)
		INTERNAL_OPTION_TRAITS(float,			VALUE_TYPE::FLOAT)
		INTERNAL_OPTION_TRAITS(double,			VALUE_TYPE::DOUBLE)
		INTERNAL_OPTION_TRAITS(long double,		VALUE_TYPE::LONG_DOUBLE)
		INTERNAL_OPTION_TRAITS(int8_t,			VALUE_TYPE::INT8)
		INTERNAL_OPTION_TRAITS(uint8_t,			VALUE_TYPE::UINT8)
		INTERNAL_OPTION_TRAITS(int16_t,			VALUE_TYPE::INT16)
		INTERNAL_OPTION_TRAITS(uint16_t,		VALUE_TYPE::UINT16)
		INTERNAL_OPTION_TRAITS(int32_t,			VALUE_TYPE::INT32)
		INTERNAL_OPTION_TRAITS(uint32_t,		VALUE_TYPE::UINT32)
		INTERNAL_OPTION_TRAITS(int64_t,			VALUE_TYPE::INT64)
		INTERNAL_OPTION_TRAITS(uint64_t,		VALUE_TYPE::UINT64)
		INTERNAL_OPTION_TRAITS(std::string,		VALUE_TYPE::STRING)

		#undef INTERNAL_OPTION_TRAITS
	}
}


#endif // __OPTION__TRAITS__H__
