#ifndef __OPTION__OPTION__H__
#define __OPTION__OPTION__H__


/**
 *
 * 作者: hm
 *
 * 说明: 选项处理
 *
 */


#include "descriptionGroup.h"

#include <unordered_map>


namespace tinyToolkit
{
	namespace option
	{
		class TOOLKIT_API Option
		{
		public:
			/**
			 *
			 * 解析
			 *
			 * @param argc 选项个数
			 * @param argv 选项数组
			 * @param separator 分隔符
			 *
			 */
			void Parse(int32_t argc, char * argv[], const char * separator = "=");

			/**
			 *
			 * 解析
			 *
			 * @param argc 选项个数
			 * @param argv 选项数组
			 * @param separator 分隔符
			 *
			 */
			void Parse(int32_t argc, const char * argv[], const char * separator = "=");

			/**
			 *
			 * 添加描述信息组
			 *
			 * @param group 描述信息组
			 *
			 */
			void AddDescriptionGroup(const std::shared_ptr<DescriptionGroup> & group);

			/**
			 *
			 * 是否存在
			 *
			 * @param option 选项
			 *
			 * @return 是否存在
			 *
			 */
			bool Exits(const std::string & name) const;

			/**
			 *
			 * 详细信息
			 *
			 * @return 详细信息
			 *
			 */
			std::string Verbose();

			/**
			 *
			 * 获取
			 *
			 * @param option 选项
			 *
			 * @return 数据
			 *
			 */
			template <typename ValueType>
			ValueType Get(const std::string & option)
			{
				auto find = _totalDescriptions.find(option);

				if (find == _totalDescriptions.end())
				{
					throw std::runtime_error("Option invalid: " + option);
				}

				if (!find->second->IsRequired())
				{
					throw std::runtime_error("Option not value: " + option);
				}

				if (!find->second->IsActivate())
				{
					throw std::runtime_error("Option value invalid: " + option);
				}

				auto store = dynamic_cast<ActualValue<ValueType> *>(find->second->Value().get());

				if (!store->_value.template Is<ValueType>())
				{
					throw std::runtime_error("Option value type invalid: " + option);
				}

				return store->_value.template Get<ValueType>();
			}

		private:
			std::size_t _modeWidth{ 0 };
			std::size_t _optionWidth{ 0 };

			std::vector<std::shared_ptr<DescriptionGroup>> _groups{ };

			std::unordered_map<std::string, std::shared_ptr<Description>> _longDescriptions{ };
			std::unordered_map<std::string, std::shared_ptr<Description>> _shortDescriptions{ };
			std::unordered_map<std::string, std::shared_ptr<Description>> _totalDescriptions{ };
		};
	}
}


#endif // __OPTION__OPTION__H__
