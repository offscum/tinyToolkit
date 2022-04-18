/**
 *
 * 作者: hm
 *
 * 说明: 字节序
 *
 */


#include "endian.h"

#include <cstdint>


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
		bool IsBigEndian()
		{
			static uint32_t value = 0x0001;

			return *(reinterpret_cast<uint8_t *>(&value)) == 0;
		}

		/**
		 *
		 * 是否是小端字节序
		 *
		 * @return 是否是小端字节序
		 *
		 */
		bool IsLittleEndian()
		{
			static uint32_t value = 0x0001;

			return *(reinterpret_cast<uint8_t *>(&value)) == 1;
		}
	}
}
