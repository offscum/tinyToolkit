/**
 *
 * 作者: hm
 *
 * 说明: 描述信息组
 *
 */


#include "descriptionGroup.h"


TOOLKIT_TEST_CASE(DescriptionGroup, AddDescription_Value_HasDefault)
{
	static std::vector<std::vector<std::string>> Information
	{
		{ "a",		"",			"-a",			"area description",		"area" },
		{ "",		"b",		"--b",			"beer description",		"beer" },
		{ "cook",	"",			"-cook",		"cook description",		"cook" },
		{ "",		"date",		"--date",		"date description",		"date" },
		{ "e",		"echo",		"-e, --echo",	"echo description",		"echo" },
		{ "fuck",	"f",		"-fuck, --f",	"fuck description",		"fuck" },
	};

	tinyToolkit::option::DescriptionGroup descriptionGroup("test");

	TOOLKIT_EXPECT_STR_EQ(descriptionGroup.Caption(), "test");

	descriptionGroup.AddDescription()
	(nullptr, "a", "area description", tinyToolkit::option::Value<std::string>("area"))
	("b", nullptr, "beer description", tinyToolkit::option::Value<std::string>("beer"))
	(nullptr, "cook", "cook description", tinyToolkit::option::Value<std::string>("cook"))
	("date", nullptr, "date description", tinyToolkit::option::Value<std::string>("date"))
	("echo", "e", "echo description", tinyToolkit::option::Value<std::string>("echo"))
	("f", "fuck", "fuck description", tinyToolkit::option::Value<std::string>("fuck"));

	auto descriptions = descriptionGroup.Descriptions();

	TOOLKIT_EXPECT_EQ(descriptions.size(), static_cast<std::size_t>(6));

	for (std::size_t i = 0; i < descriptions.size(); ++i)
	{
		TOOLKIT_EXPECT_TRUE(descriptions[i]->Value() != nullptr);
		TOOLKIT_EXPECT_TRUE(descriptions[i]->Value()->Type() == tinyToolkit::option::VALUE_TYPE::STRING);
		TOOLKIT_EXPECT_TRUE(descriptions[i]->Value()->HasValue());
		TOOLKIT_EXPECT_TRUE(descriptions[i]->Value()->HasDefault());
		TOOLKIT_EXPECT_TRUE(descriptions[i]->IsActivate());
		TOOLKIT_EXPECT_TRUE(descriptions[i]->IsRequired());

		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->Value()->Default(), Information[i][4]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->Info(), Information[i][3]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->LongName(), Information[i][1]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->ShortName(), Information[i][0]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->OptionName(), Information[i][2]);

		try
		{
			descriptions[i]->Activate();

			TOOLKIT_EXPECT_TRUE(false);
			TOOLKIT_EXPECT_FALSE(true);
		}
		catch (...)
		{
			TOOLKIT_EXPECT_TRUE(true);
			TOOLKIT_EXPECT_FALSE(false);
		}

		descriptions[i]->Activate("123");

		TOOLKIT_EXPECT_TRUE(descriptions[i]->Value() != nullptr);
		TOOLKIT_EXPECT_TRUE(descriptions[i]->Value()->Type() == tinyToolkit::option::VALUE_TYPE::STRING);
		TOOLKIT_EXPECT_TRUE(descriptions[i]->Value()->HasValue());
		TOOLKIT_EXPECT_TRUE(descriptions[i]->Value()->HasDefault());
		TOOLKIT_EXPECT_TRUE(descriptions[i]->IsActivate());
		TOOLKIT_EXPECT_TRUE(descriptions[i]->IsRequired());

		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->Value()->Default(), Information[i][4]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->Info(), Information[i][3]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->LongName(), Information[i][1]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->ShortName(), Information[i][0]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->OptionName(), Information[i][2]);
	}
}

TOOLKIT_TEST_CASE(DescriptionGroup, AddDescription_Value_NotDefault)
{
	static std::vector<std::vector<std::string>> Information
	{
		{ "a",		"",			"-a",			"area description",		"" },
		{ "",		"b",		"--b",			"beer description",		"" },
		{ "cook",	"",			"-cook",		"cook description",		"" },
		{ "",		"date",		"--date",		"date description",		"" },
		{ "e",		"echo",		"-e, --echo",	"echo description",		"" },
		{ "fuck",	"f",		"-fuck, --f",	"fuck description",		"" },
	};

	tinyToolkit::option::DescriptionGroup descriptionGroup("test");

	TOOLKIT_EXPECT_STR_EQ(descriptionGroup.Caption(), "test");

	descriptionGroup.AddDescription()
	(nullptr, "a", "area description", tinyToolkit::option::Value<std::string>())
	("b", nullptr, "beer description", tinyToolkit::option::Value<std::string>())
	(nullptr, "cook", "cook description", tinyToolkit::option::Value<std::string>())
	("date", nullptr, "date description", tinyToolkit::option::Value<std::string>())
	("echo", "e", "echo description", tinyToolkit::option::Value<std::string>())
	("f", "fuck", "fuck description", tinyToolkit::option::Value<std::string>());

	auto descriptions = descriptionGroup.Descriptions();

	TOOLKIT_EXPECT_EQ(descriptions.size(), static_cast<std::size_t>(6));

	for (std::size_t i = 0; i < descriptions.size(); ++i)
	{
		TOOLKIT_EXPECT_TRUE(descriptions[i]->Value() != nullptr);
		TOOLKIT_EXPECT_TRUE(descriptions[i]->Value()->Type() == tinyToolkit::option::VALUE_TYPE::STRING);
		TOOLKIT_EXPECT_TRUE(descriptions[i]->IsRequired());

		TOOLKIT_EXPECT_FALSE(descriptions[i]->Value()->HasValue());
		TOOLKIT_EXPECT_FALSE(descriptions[i]->Value()->HasDefault());
		TOOLKIT_EXPECT_FALSE(descriptions[i]->IsActivate());

		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->Value()->Default(), Information[i][4]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->Info(), Information[i][3]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->LongName(), Information[i][1]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->ShortName(), Information[i][0]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->OptionName(), Information[i][2]);

		try
		{
			descriptions[i]->Activate();

			TOOLKIT_EXPECT_TRUE(false);
			TOOLKIT_EXPECT_FALSE(true);
		}
		catch (...)
		{
			TOOLKIT_EXPECT_TRUE(true);
			TOOLKIT_EXPECT_FALSE(false);
		}

		descriptions[i]->Activate("123");

		TOOLKIT_EXPECT_TRUE(descriptions[i]->Value() != nullptr);
		TOOLKIT_EXPECT_TRUE(descriptions[i]->Value()->Type() == tinyToolkit::option::VALUE_TYPE::STRING);
		TOOLKIT_EXPECT_TRUE(descriptions[i]->Value()->HasValue());
		TOOLKIT_EXPECT_TRUE(descriptions[i]->IsActivate());
		TOOLKIT_EXPECT_TRUE(descriptions[i]->IsRequired());

		TOOLKIT_EXPECT_FALSE(descriptions[i]->Value()->HasDefault());

		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->Value()->Default(), Information[i][4]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->Info(), Information[i][3]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->LongName(), Information[i][1]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->ShortName(), Information[i][0]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->OptionName(), Information[i][2]);
	}
}

TOOLKIT_TEST_CASE(DescriptionGroup, AddDescription_NotValue)
{
	static std::vector<std::vector<std::string>> Information
	{
		{ "a",		"",			"-a",			"area description" },
		{ "",		"b",		"--b",			"beer description" },
		{ "cook",	"",			"-cook",		"cook description" },
		{ "",		"date",		"--date",		"date description" },
		{ "e",		"echo",		"-e, --echo",	"echo description" },
		{ "fuck",	"f",		"-fuck, --f",	"fuck description" },
	};

	tinyToolkit::option::DescriptionGroup descriptionGroup("test");

	TOOLKIT_EXPECT_STR_EQ(descriptionGroup.Caption(), "test");

	descriptionGroup.AddDescription()
	(nullptr, "a", "area description")
	("b", nullptr, "beer description")
	(nullptr, "cook", "cook description")
	("date", nullptr, "date description")
	("echo", "e", "echo description")
	("f", "fuck", "fuck description");

	auto descriptions = descriptionGroup.Descriptions();

	TOOLKIT_EXPECT_EQ(descriptions.size(), static_cast<std::size_t>(6));

	for (std::size_t i = 0; i < descriptions.size(); ++i)
	{
		TOOLKIT_EXPECT_TRUE(descriptions[i]->Value() == nullptr);

		TOOLKIT_EXPECT_FALSE(descriptions[i]->IsActivate());
		TOOLKIT_EXPECT_FALSE(descriptions[i]->IsRequired());

		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->Info(), Information[i][3]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->LongName(), Information[i][1]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->ShortName(), Information[i][0]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->OptionName(), Information[i][2]);

		try
		{
			descriptions[i]->Activate("123");

			TOOLKIT_EXPECT_TRUE(false);
			TOOLKIT_EXPECT_FALSE(true);
		}
		catch (...)
		{
			TOOLKIT_EXPECT_TRUE(true);
			TOOLKIT_EXPECT_FALSE(false);
		}

		descriptions[i]->Activate();

		TOOLKIT_EXPECT_TRUE(descriptions[i]->Value() == nullptr);
		TOOLKIT_EXPECT_TRUE(descriptions[i]->IsActivate());

		TOOLKIT_EXPECT_FALSE(descriptions[i]->IsRequired());

		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->Info(), Information[i][3]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->LongName(), Information[i][1]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->ShortName(), Information[i][0]);
		TOOLKIT_EXPECT_STR_EQ(descriptions[i]->OptionName(), Information[i][2]);
	}
}
