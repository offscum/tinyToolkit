#ifndef __CONVERT__BASE64__H__
#define __CONVERT__BASE64__H__


/**
 *
 * 作者: hm
 *
 * 说明: base64编解码
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"

#include <string>
#include <cstdint>


namespace tinyToolkit
{
	namespace convert
	{
		/**
		 *
		 * 编码
		 *
		 * @param content 内容
		 *
		 * @return 结果
		 *
		 */
		TOOLKIT_API std::string Base64Encode(const char * content);

		/**
		 *
		 * 编码
		 *
		 * @param content 内容
		 *
		 * @return 结果
		 *
		 */
		TOOLKIT_API std::string Base64Encode(const uint8_t * content);

		/**
		 *
		 * 编码
		 *
		 * @param content 内容
		 *
		 * @return 结果
		 *
		 */
		TOOLKIT_API std::string Base64Encode(const std::string & content);

		/**
		 *
		 * 编码
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 * @return 结果
		 *
		 */
		TOOLKIT_API std::string Base64Encode(const char * content, std::size_t length);

		/**
		 *
		 * 编码
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 * @return 结果
		 *
		 */
		TOOLKIT_API std::string Base64Encode(const uint8_t * content, std::size_t length);

		/**
		 *
		 * 编码
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 * @return 结果
		 *
		 */
		TOOLKIT_API std::string Base64Encode(const std::string & content, std::size_t length);

		/**
		 *
		 * 解码
		 *
		 * @param content 内容
		 *
		 * @return 结果
		 *
		 */
		TOOLKIT_API std::string Base64Decode(const char * content);

		/**
		 *
		 * 解码
		 *
		 * @param content 内容
		 *
		 * @return 结果
		 *
		 */
		TOOLKIT_API std::string Base64Decode(const uint8_t * content);

		/**
		 *
		 * 解码
		 *
		 * @param content 内容
		 *
		 * @return 结果
		 *
		 */
		TOOLKIT_API std::string Base64Decode(const std::string & content);

		/**
		 *
		 * 解码
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 * @return 结果
		 *
		 */
		TOOLKIT_API std::string Base64Decode(const char * content, std::size_t length);

		/**
		 *
		 * 解码
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 * @return 结果
		 *
		 */
		TOOLKIT_API std::string Base64Decode(const uint8_t * content, std::size_t length);

		/**
		 *
		 * 解码
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 * @return 结果
		 *
		 */
		TOOLKIT_API std::string Base64Decode(const std::string & content, std::size_t length);
	}
}


#endif // __CONVERT__BASE64__H__
