/**
 *
 * 作者: hm
 *
 * 说明: 描述信息组
 *
 */


#include "descriptionGroup.h"


namespace tinyToolkit
{
	namespace option
	{
		/**
		 *
		 * 构造函数
		 *
		 * @param caption 标题
		 *
		 */
		DescriptionGroup::DescriptionGroup(const char * caption) : _caption(caption)
		{

		}

		/**
		 *
		 * 添加描述
		 *
		 * @return 对象
		 *
		 */
		DescriptionGroup & DescriptionGroup::AddDescription()
		{
			return *this;
		}

		/**
		 *
		 * 标题
		 *
		 * @return 标题
		 *
		 */
		const std::string & DescriptionGroup::Caption() const
		{
			return _caption;
		}

		/**
		 *
		 * 选项组
		 *
		 * @return 选项组
		 *
		 */
		const std::vector<std::shared_ptr<Description>> & DescriptionGroup::Descriptions() const
		{
			return _descriptions;
		}

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
		DescriptionGroup & DescriptionGroup::operator()(const char * longName, const char * shortName, const char * info)
		{
			_descriptions.push_back(std::make_shared<Description>(longName, shortName, info));

			return *this;
		}

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
		DescriptionGroup & DescriptionGroup::operator()(const char * longName, const char * shortName, const char * info, const std::shared_ptr<BasicValue> & value)
		{
			_descriptions.push_back(std::make_shared<Description>(longName, shortName, info, value));

			return *this;
		}
	}
}
