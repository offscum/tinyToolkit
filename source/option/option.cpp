/**
 *
 * 作者: hm
 *
 * 说明: 选项处理
 *
 */


#include "option.h"

#include <cstring>
#include <sstream>
#include <algorithm>


namespace tinyToolkit
{
	namespace option
	{
		/**
		 *
		 * 解析
		 *
		 * @param argc 选项个数
		 * @param argv 选项数组
		 * @param separator 分隔符
		 *
		 */
		void Option::Parse(int argc, const char * argv[], const char * separator)
		{
			if (separator == nullptr || separator[0] == '\0')
			{
				throw std::logic_error("separator invalid");
			}

			std::string opt{ };
			std::string val{ };
			std::string err{ };

			for (int32_t i = 1; i < argc; ++i)
			{
				const char * value = argv[i];
				const char * found = ::strstr(value, separator);

				std::unordered_map<std::string, std::shared_ptr<Description>>::iterator iter{ };

				if (::strncmp(value, "--", 2) == 0)
				{
					if (found)
					{
						val.assign(found + 1);
						opt.assign(value + 2, found);
					}
					else
					{
						opt.assign(value + 2);
					}

					err = "--" + opt;

					if (opt.empty())
					{
						throw std::invalid_argument("Option is empty: " + err);
					}

					iter = _longDescriptions.find(opt);

					if (iter == _longDescriptions.end())
					{
						throw std::invalid_argument("Undefined option: " + err);
					}
				}
				else if (::strncmp(value, "-", 1) == 0)
				{
					if (found)
					{
						val.assign(found + 1);
						opt.assign(value + 1, found);
					}
					else
					{
						opt.assign(value + 1);
					}

					err = "-" + opt;

					if (opt.empty())
					{
						throw std::invalid_argument("Option is empty: " + err);
					}

					iter = _shortDescriptions.find(opt);

					if (iter == _shortDescriptions.end())
					{
						throw std::invalid_argument("Undefined option: " + err);
					}
				}
				else
				{
					throw std::invalid_argument("Invalid option: " + std::string(value));
				}

				if (iter->second->IsRequired())
				{
					if (found == nullptr)
					{
						throw std::invalid_argument("Option require input value: " + err);
					}

					iter->second->Activate(val);
				}
				else
				{
					if (found)
					{
						throw std::invalid_argument("Option do not require input value: " + err);
					}

					iter->second->Activate();
				}
			}
		}

		/**
		 *
		 * 添加描述信息组
		 *
		 * @param group 描述信息组
		 *
		 */
		void Option::AddDescriptionGroup(const std::shared_ptr<DescriptionGroup> & group)
		{
			if (std::find(_groups.begin(), _groups.end(), group) != _groups.end())
			{
				throw std::runtime_error("Multiple add description group: " + group->Caption());
			}

			_groups.push_back(group);

			for (auto & description : group->Descriptions())
			{
				if (description->ShortName().empty() && description->LongName().empty())
				{
					throw std::runtime_error("definition empty: " + group->Caption());
				}

				if (!description->LongName().empty())
				{
					if (!_longDescriptions.insert(std::make_pair(description->LongName(), description)).second ||
						!_totalDescriptions.insert(std::make_pair(description->LongName(), description)).second)
					{
						throw std::runtime_error("Multiple definition: " + description->LongName());
					}
				}

				if (!description->ShortName().empty())
				{
					if (!_shortDescriptions.insert(std::make_pair(description->ShortName(), description)).second ||
						!_totalDescriptions.insert(std::make_pair(description->ShortName(), description)).second)
					{
						throw std::runtime_error("Multiple definition: " + description->ShortName());
					}
				}

				if (description->IsRequired())
				{
					if (description->Value()->HasDefault())
					{
						if (_modeWidth < (description->Value()->Default().length() + 19))
						{
							_modeWidth = description->Value()->Default().length() + 19;
						}
					}
					else
					{
						if (_modeWidth < 8)
						{
							_modeWidth = 8;
						}
					}
				}

				if (_optionWidth < description->OptionName().length())
				{
					_optionWidth = description->OptionName().length();
				}
			}
		}

		/**
		 *
		 * 是否存在
		 *
		 * @param option 选项
		 *
		 * @return 是否存在
		 *
		 */
		bool Option::Exits(const std::string & option) const
		{
			auto find = _totalDescriptions.find(option);

			if (find == _totalDescriptions.end())
			{
				return false;
			}

			return find->second->IsActivate();
		}

		/**
		 *
		 * 详细信息
		 *
		 * @return 详细信息
		 *
		 */
		std::string Option::Verbose()
		{
			std::stringstream stream{ };

			for (auto & group : _groups)
			{
				stream << TOOLKIT_LINE_EOL << group->Caption() << ":" << TOOLKIT_LINE_EOL;

				for (auto & description : group->Descriptions())
				{
					std::size_t width = _optionWidth - description->OptionName().length();

					stream << "  ";
					stream << std::string(width, ' ');
					stream << description->OptionName();
					stream << "   ";

					width = _modeWidth;

					if (description->IsRequired())
					{
						width -= 8;

						stream << "required";

						if (description->Value()->HasDefault())
						{
							width -= description->Value()->Default().length() + 11;

							stream << " (default=";
							stream << description->Value()->Default();
							stream << ")";
						}
					}

					stream << std::string(width, ' ');
					stream << "   ";
					stream << description->Info();
					stream << TOOLKIT_LINE_EOL;
				}
			}

			return stream.str();
		}
	}
}
