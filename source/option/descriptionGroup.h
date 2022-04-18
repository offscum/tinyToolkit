#ifndef __OPTION__DESCRIPTION_GROUP__H__
#define __OPTION__DESCRIPTION_GROUP__H__


/**
 *
 * 作者: hm
 *
 * 说明: 描述信息组
 *
 */


#include "description.h"

#include <vector>


namespace tinyToolkit
{
	namespace option
	{
		class TOOLKIT_API DescriptionGroup
		{
		public:
			/**
			 *
			 * 构造函数
			 *
			 * @param caption 标题
			 *
			 */
			explicit DescriptionGroup(const char * caption);

		public:
			/**
			 *
			 * 添加描述
			 *
			 * @return 对象
			 *
			 */
			DescriptionGroup & AddDescription();

			/**
			 *
			 * 标题
			 *
			 * @return 标题
			 *
			 */
			const std::string & Caption() const;

			/**
			 *
			 * 描述信息组
			 *
			 * @return 描述信息组
			 *
			 */
			const std::vector<std::shared_ptr<Description>> & Descriptions() const;

		public:
			/**
			 *
			 * 重载()操作
			 *
			 * @param longName 全长名称
			 * @param shortName 缩略名称
			 * @param info 信息
			 *
			 * @return 对象
			 *
			 */
			DescriptionGroup & operator()(const char * longName, const char * shortName, const char * info);

			/**
			 *
			 * 重载()操作
			 *
			 * @param longName 全长名称
			 * @param shortName 缩略名称
			 * @param info 信息
			 * @param value 数据
			 *
			 * @return 对象
			 *
			 */
			DescriptionGroup & operator()(const char * longName, const char * shortName, const char * info, const std::shared_ptr<BasicValue> & value);

		private:
			std::string _caption{ };

			std::vector<std::shared_ptr<Description>> _descriptions{ };
		};
	}
}


#endif // __OPTION__DESCRIPTION_GROUP__H__
