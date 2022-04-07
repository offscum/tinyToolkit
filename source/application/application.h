#ifndef __APPLICATION__APPLICATION__H__
#define __APPLICATION__APPLICATION__H__


/**
 *
 * 作者: hm
 *
 * 说明: 应用信息
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"

#include <string>
#include <cstdint>


namespace tinyToolkit
{
	namespace application
	{
		/**
		 *
		 * 是否存在
		 *
		 * @param pid 序列号
		 *
		 * @return 是否存在
		 *
		 */
		TOOLKIT_API bool Exist(uint64_t pid);

		/**
		 *
		 * 是否存在
		 *
		 * @param name 名称
		 *
		 * @return 是否存在
		 *
		 */
		TOOLKIT_API bool Exist(const std::string & name);

		/**
		 *
		 * 设置线程名称
		 *
		 * @param name 名称
		 *
		 * @return 是否设置成功
		 *
		 */
		TOOLKIT_API bool SetThreadName(const std::string & name);

		/**
		 *
		 * 占用内存
		 *
		 * @param pid 序列号
		 *
		 * @return 占用内存
		 *
		 */
		TOOLKIT_API int64_t UsedMemory(uint64_t pid);

		/**
		 *
		 * 线程序列号
		 *
		 * @return 线程序列号
		 *
		 */
		TOOLKIT_API uint64_t ThreadID();

		/**
		 *
		 * 进程序列号
		 *
		 * @return 进程序列号
		 *
		 */
		TOOLKIT_API uint64_t ProcessID();

		/**
		 *
		 * 名称
		 *
		 * @return 名称
		 *
		 */
		TOOLKIT_API std::string Name();

		/**
		 *
		 * 路径
		 *
		 * @return 路径
		 *
		 */
		TOOLKIT_API std::string Path();

		/**
		 *
		 * 编译日期时间
		 *
		 * @param date 日期
		 * @param time 时间
		 *
		 * @return 编译日期时间
		 *
		 */
		TOOLKIT_API std::string CompileDateTime(const char * date = __DATE__, const char * time = __TIME__);
	}
}


#endif // __APPLICATION__APPLICATION__H__
