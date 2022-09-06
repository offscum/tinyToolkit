/**
 *
 * 作者: hm
 *
 * 说明: 描述信息
 *
 */


#include "description.h"

#include <cstdlib>


namespace tinyToolkit
{
	namespace option
	{
		/**
		 *
		 * 构造函数
		 *
		 * @param longName 全长名称
		 * @param shortName 缩略名称
		 * @param info 信息
		 *
		 */
		Description::Description(const char * longName, const char * shortName, const char * info) : _info(info)
		{
			SetName(longName, shortName);

			_isActivate = false;
		}

		/**
		 *
		 * 构造函数
		 *
		 * @param longName 全长名称
		 * @param shortName 缩略名称
		 * @param info 信息
		 * @param value 数据
		 *
		 */
		Description::Description(const char * longName, const char * shortName, const char * info, std::shared_ptr<BasicValue> value) : _info(info),
																																		_value(std::move(value))
		{
			SetName(longName, shortName);

			_isActivate = _value->HasValue();
		}

		/**
		 *
		 * 激活
		 *
		 */
		void Description::Activate()
		{
			if (_value)
			{
				throw std::runtime_error("There are need values to activate");
			}

			_isActivate = true;
		}

		/**
		 *
		 * 激活
		 *
		 * @param value 数值
		 *
		 */
		void Description::Activate(const std::string & value)
		{
			if (_value == nullptr)
			{
				throw std::runtime_error("There are no values to activate");
			}

			switch (_value->Type())
			{
				case VALUE_TYPE::BOOL:
				{
					dynamic_cast<ActualValue<bool> *>(_value.get())->_value = (value == "true");

					break;
				}

				case VALUE_TYPE::FLOAT:
				{
					dynamic_cast<ActualValue<float> *>(_value.get())->_value = ::strtof(value.c_str(), nullptr);

					break;
				}

				case VALUE_TYPE::DOUBLE:
				{
					dynamic_cast<ActualValue<double> *>(_value.get())->_value = ::strtod(value.c_str(), nullptr);

					break;
				}

				case VALUE_TYPE::LONG_DOUBLE:
				{
					dynamic_cast<ActualValue<long double> *>(_value.get())->_value = ::strtold(value.c_str(), nullptr);

					break;
				}

				case VALUE_TYPE::INT8:
				{
					dynamic_cast<ActualValue<int8_t> *>(_value.get())->_value = static_cast<int8_t>(::strtol(value.c_str(), nullptr, 10));

					break;
				}

				case VALUE_TYPE::UINT8:
				{
					dynamic_cast<ActualValue<uint8_t> *>(_value.get())->_value = static_cast<uint8_t>(::strtoul(value.c_str(), nullptr, 10));

					break;
				}

				case VALUE_TYPE::INT16:
				{
					dynamic_cast<ActualValue<int16_t> *>(_value.get())->_value = static_cast<int16_t>(::strtol(value.c_str(), nullptr, 10));

					break;
				}

				case VALUE_TYPE::UINT16:
				{
					dynamic_cast<ActualValue<uint16_t> *>(_value.get())->_value = static_cast<uint16_t>(::strtoul(value.c_str(), nullptr, 10));

					break;
				}

				case VALUE_TYPE::INT32:
				{
					dynamic_cast<ActualValue<int32_t> *>(_value.get())->_value = static_cast<int32_t>(::strtol(value.c_str(), nullptr, 10));

					break;
				}

				case VALUE_TYPE::UINT32:
				{
					dynamic_cast<ActualValue<uint32_t> *>(_value.get())->_value = static_cast<uint32_t>(::strtoul(value.c_str(), nullptr, 10));

					break;
				}

				case VALUE_TYPE::INT64:
				{
					dynamic_cast<ActualValue<int64_t> *>(_value.get())->_value = static_cast<int64_t>(::strtoll(value.c_str(), nullptr, 10));

					break;
				}

				case VALUE_TYPE::UINT64:
				{
					dynamic_cast<ActualValue<uint64_t> *>(_value.get())->_value = static_cast<uint64_t>(::strtoull(value.c_str(), nullptr, 10));

					break;
				}

				case VALUE_TYPE::STRING:
				{
					dynamic_cast<ActualValue<std::string> *>(_value.get())->_value = value;

					break;
				}

				default:
				{
					throw std::runtime_error("Unknown value type");
				}
			}

			_isActivate = true;
		}

		/**
		 *
		 * 是否激活
		 *
		 * @return 是否有效
		 *
		 */
		bool Description::IsActivate() const
		{
			return _isActivate;
		}

		/**
		 *
		 * 是否需要数据
		 *
		 * @return 是否需要数据
		 *
		 */
		bool Description::IsRequired() const
		{
			return _value != nullptr;
		}

		/**
		 *
		 * 信息
		 *
		 * @return 信息
		 *
		 */
		const std::string & Description::Info() const
		{
			return _info;
		}

		/**
		 *
		 * 全长名称
		 *
		 * @return 全长名称
		 *
		 */
		const std::string & Description::LongName() const
		{
			return _longName;
		}

		/**
		 *
		 * 缩略名称
		 *
		 * @return 缩略名称
		 *
		 */
		const std::string & Description::ShortName() const
		{
			return _shortName;
		}

		/**
		 *
		 * 选项名称
		 *
		 * @return 选项名称
		 *
		 */
		const std::string & Description::OptionName() const
		{
			return _optionName;
		}

		/**
		 *
		 * 数据
		 *
		 * @return 数据
		 *
		 */
		const std::shared_ptr<BasicValue> & Description::Value() const
		{
			return _value;
		}

		/**
		 *
		 * 设置名称
		 *
		 * @param longName 全长名称
		 * @param shortName 缩略名称
		 *
		 */
		void Description::SetName(const char * longName, const char * shortName)
		{
			if ((longName == nullptr || longName[0] == '\0') &&
				(shortName == nullptr || shortName[0] == '\0'))
			{
				throw std::runtime_error("No option names were specified");
			}

			if (longName && longName[0] != '\0')
			{
				_longName = longName;
			}

			if (shortName && shortName[0] != '\0')
			{
				_shortName = shortName;
			}

			if (_shortName.empty())
			{
				_optionName.append("--", 2).append(_longName);
			}
			else
			{
				_optionName.append("-", 1).append(_shortName);

				if (!_longName.empty())
				{
					_optionName.append(", --", 4).append(_longName);
				}
			}
		}
	}
}
