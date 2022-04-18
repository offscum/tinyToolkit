/**
 *
 * 作者: hm
 *
 * 说明: 选项
 *
 */


#include "option.h"


TOOLKIT_TEST_CASE(Option, Verbose)
{
	tinyToolkit::option::Option option{ };

	TOOLKIT_EXPECT_STR_EQ(option.Verbose(), "");

	{
		std::string content = TOOLKIT_LINE_EOL
								"group_1:"
								TOOLKIT_LINE_EOL
								"  -h, --help      help message"
								TOOLKIT_LINE_EOL;

		auto group_1 = std::make_shared<tinyToolkit::option::DescriptionGroup>("group_1");

		group_1->AddDescription()
		("help", "h", "help message");

		option.AddDescriptionGroup(group_1);

		TOOLKIT_EXPECT_STR_EQ(option.Verbose(), content);
	}

	{
		std::string content = TOOLKIT_LINE_EOL
								"group_1:"
								TOOLKIT_LINE_EOL
								"  -h, --help              help message"
								TOOLKIT_LINE_EOL
								TOOLKIT_LINE_EOL
								"group_2:"
								TOOLKIT_LINE_EOL
								"  -t, --test   required   test message"
								TOOLKIT_LINE_EOL
								"  -f, --fuck   required   fuck message"
								TOOLKIT_LINE_EOL;

		auto group_2 = std::make_shared<tinyToolkit::option::DescriptionGroup>("group_2");

		group_2->AddDescription()
		("test", "t", "test message", tinyToolkit::option::Value<int8_t>())
		("fuck", "f", "fuck message", tinyToolkit::option::Value<int32_t>());

		option.AddDescriptionGroup(group_2);

		TOOLKIT_EXPECT_STR_EQ(option.Verbose(), content);
	}

	{
		std::string content = TOOLKIT_LINE_EOL
								"group_1:"
								TOOLKIT_LINE_EOL
								"    -h, --help                                help message"
								TOOLKIT_LINE_EOL
								TOOLKIT_LINE_EOL
								"group_2:"
								TOOLKIT_LINE_EOL
								"    -t, --test   required                     test message"
								TOOLKIT_LINE_EOL
								"    -f, --fuck   required                     fuck message"
								TOOLKIT_LINE_EOL
								TOOLKIT_LINE_EOL
								"group_3:"
								TOOLKIT_LINE_EOL
								"      -i, --id   required (default=123)       id message"
								TOOLKIT_LINE_EOL
								"  -l, --logger   required (default=console)   logger message"
								TOOLKIT_LINE_EOL;

		auto group_3 = std::make_shared<tinyToolkit::option::DescriptionGroup>("group_3");

		group_3->AddDescription()
		("id", "i", "id message", tinyToolkit::option::Value<int64_t>(123))
		("logger", "l", "logger message", tinyToolkit::option::Value<std::string>("console"));

		option.AddDescriptionGroup(group_3);

		TOOLKIT_EXPECT_STR_EQ(option.Verbose(), content);
	}
}

TOOLKIT_TEST_CASE(Option, Parse)
{
	tinyToolkit::option::Option option{ };

	auto group_1 = std::make_shared<tinyToolkit::option::DescriptionGroup>("group_1");
	auto group_2 = std::make_shared<tinyToolkit::option::DescriptionGroup>("group_2");
	auto group_3 = std::make_shared<tinyToolkit::option::DescriptionGroup>("group_3");
	auto group_4 = std::make_shared<tinyToolkit::option::DescriptionGroup>("group_4");

	group_1->AddDescription()
	("help", "h", "help message");

	group_2->AddDescription()
	("float", "f", "float message", tinyToolkit::option::Value<float>())
	("double", "d", "double message", tinyToolkit::option::Value<double>());

	group_3->AddDescription()
	("int8_t", "i8", "int8_t message", tinyToolkit::option::Value<int8_t>(1))
	("uint8_t", "u8", "uint8_t message", tinyToolkit::option::Value<uint8_t>(10))
	("int16_t", "i16", "int16_t message", tinyToolkit::option::Value<int16_t>(100))
	("uint16_t", "u16", "uint16_t message", tinyToolkit::option::Value<uint16_t>(1000))
	("int32_t", "i32", "int32_t message", tinyToolkit::option::Value<int32_t>(10000))
	("uint32_t", "u32", "uint32_t message", tinyToolkit::option::Value<uint32_t>(100000))
	("int64_t", "i64", "int64_t message", tinyToolkit::option::Value<int64_t>(1000000))
	("uint64_t", "u64", "uint64_t message", tinyToolkit::option::Value<uint64_t>(10000000));

	group_4->AddDescription()
	("string", "s", "string message", tinyToolkit::option::Value<std::string>("config/CONFIG.json"));

	TOOLKIT_EXPECT_FALSE(option.Exits("s"));
	TOOLKIT_EXPECT_FALSE(option.Exits("i8"));
	TOOLKIT_EXPECT_FALSE(option.Exits("u8"));
	TOOLKIT_EXPECT_FALSE(option.Exits("i16"));
	TOOLKIT_EXPECT_FALSE(option.Exits("u16"));
	TOOLKIT_EXPECT_FALSE(option.Exits("i32"));
	TOOLKIT_EXPECT_FALSE(option.Exits("u32"));
	TOOLKIT_EXPECT_FALSE(option.Exits("i64"));
	TOOLKIT_EXPECT_FALSE(option.Exits("u64"));

	TOOLKIT_EXPECT_FALSE(option.Exits("string"));
	TOOLKIT_EXPECT_FALSE(option.Exits("int8_t"));
	TOOLKIT_EXPECT_FALSE(option.Exits("uint8_t"));
	TOOLKIT_EXPECT_FALSE(option.Exits("int16_t"));
	TOOLKIT_EXPECT_FALSE(option.Exits("uint16_t"));
	TOOLKIT_EXPECT_FALSE(option.Exits("int32_t"));
	TOOLKIT_EXPECT_FALSE(option.Exits("uint32_t"));
	TOOLKIT_EXPECT_FALSE(option.Exits("int64_t"));
	TOOLKIT_EXPECT_FALSE(option.Exits("uint64_t"));

	TOOLKIT_EXPECT_FALSE(option.Exits("f"));
	TOOLKIT_EXPECT_FALSE(option.Exits("d"));

	TOOLKIT_EXPECT_FALSE(option.Exits("help"));
	TOOLKIT_EXPECT_FALSE(option.Exits("float"));
	TOOLKIT_EXPECT_FALSE(option.Exits("double"));

	option.AddDescriptionGroup(group_1);
	option.AddDescriptionGroup(group_2);
	option.AddDescriptionGroup(group_3);
	option.AddDescriptionGroup(group_4);

	TOOLKIT_EXPECT_TRUE(option.Exits("s"));
	TOOLKIT_EXPECT_TRUE(option.Exits("i8"));
	TOOLKIT_EXPECT_TRUE(option.Exits("u8"));
	TOOLKIT_EXPECT_TRUE(option.Exits("i16"));
	TOOLKIT_EXPECT_TRUE(option.Exits("u16"));
	TOOLKIT_EXPECT_TRUE(option.Exits("i32"));
	TOOLKIT_EXPECT_TRUE(option.Exits("u32"));
	TOOLKIT_EXPECT_TRUE(option.Exits("i64"));
	TOOLKIT_EXPECT_TRUE(option.Exits("u64"));

	TOOLKIT_EXPECT_TRUE(option.Exits("string"));
	TOOLKIT_EXPECT_TRUE(option.Exits("int8_t"));
	TOOLKIT_EXPECT_TRUE(option.Exits("uint8_t"));
	TOOLKIT_EXPECT_TRUE(option.Exits("int16_t"));
	TOOLKIT_EXPECT_TRUE(option.Exits("uint16_t"));
	TOOLKIT_EXPECT_TRUE(option.Exits("int32_t"));
	TOOLKIT_EXPECT_TRUE(option.Exits("uint32_t"));
	TOOLKIT_EXPECT_TRUE(option.Exits("int64_t"));
	TOOLKIT_EXPECT_TRUE(option.Exits("uint64_t"));

	TOOLKIT_EXPECT_FALSE(option.Exits("f"));
	TOOLKIT_EXPECT_FALSE(option.Exits("d"));

	TOOLKIT_EXPECT_FALSE(option.Exits("help"));
	TOOLKIT_EXPECT_FALSE(option.Exits("float"));
	TOOLKIT_EXPECT_FALSE(option.Exits("double"));

	const char * argv[] =
	{
		"test_option",
		"--help",
		"-f=0.01",
		"-d=0.02"
	};

	option.Parse(static_cast<int32_t>(sizeof(argv) / sizeof(const char *)), argv);

	TOOLKIT_EXPECT_EQ(option.Get<float>("f"), 0.01f);
	TOOLKIT_EXPECT_EQ(option.Get<float>("float"), 0.01f);
	TOOLKIT_EXPECT_EQ(option.Get<double>("d"), 0.02);
	TOOLKIT_EXPECT_EQ(option.Get<double>("double"), 0.02);
	TOOLKIT_EXPECT_EQ(option.Get<int8_t>("i8"), static_cast<int8_t>(1));
	TOOLKIT_EXPECT_EQ(option.Get<int8_t>("int8_t"), static_cast<int8_t>(1));
	TOOLKIT_EXPECT_EQ(option.Get<uint8_t>("u8"), static_cast<uint8_t>(10));
	TOOLKIT_EXPECT_EQ(option.Get<uint8_t>("uint8_t"), static_cast<uint8_t>(10));
	TOOLKIT_EXPECT_EQ(option.Get<int16_t>("i16"), static_cast<int16_t>(100));
	TOOLKIT_EXPECT_EQ(option.Get<int16_t>("int16_t"), static_cast<int16_t>(100));
	TOOLKIT_EXPECT_EQ(option.Get<uint16_t>("u16"), static_cast<uint16_t>(1000));
	TOOLKIT_EXPECT_EQ(option.Get<uint16_t>("uint16_t"), static_cast<uint16_t>(1000));
	TOOLKIT_EXPECT_EQ(option.Get<int32_t>("i32"), static_cast<int32_t>(10000));
	TOOLKIT_EXPECT_EQ(option.Get<int32_t>("int32_t"), static_cast<int32_t>(10000));
	TOOLKIT_EXPECT_EQ(option.Get<uint32_t>("u32"), static_cast<uint32_t>(100000));
	TOOLKIT_EXPECT_EQ(option.Get<uint32_t>("uint32_t"), static_cast<uint32_t>(100000));
	TOOLKIT_EXPECT_EQ(option.Get<int64_t>("i64"), static_cast<int64_t>(1000000));
	TOOLKIT_EXPECT_EQ(option.Get<int64_t>("int64_t"), static_cast<int64_t>(1000000));
	TOOLKIT_EXPECT_EQ(option.Get<uint64_t>("u64"), static_cast<uint64_t>(10000000));
	TOOLKIT_EXPECT_EQ(option.Get<uint64_t>("uint64_t"), static_cast<uint64_t>(10000000));

	TOOLKIT_EXPECT_STR_EQ(option.Get<std::string>("s"), "config/CONFIG.json");
	TOOLKIT_EXPECT_STR_EQ(option.Get<std::string>("string"), "config/CONFIG.json");
}
