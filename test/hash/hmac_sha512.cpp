/**
 *
 * 作者: hm
 *
 * 说明: hmac_sha512
 *
 */


#include "hmac_sha512.h"


TOOLKIT_TEST_CASE(HMAC_SHA512, Char)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"2AAD43C04FE3DB5AB851814117EFC8C1E57D6CEE73E388062E9795222D7CA08632F63CD00F7F6065EF756B1BAD6F99FEDB7D5B98A53FB5D1220FE2BBB7EA85A1",
		"A322F98C01F3C53644DE2FB5F615C9ED40B738CE7BAAD295B8A97E1061BBB384469C8497403DE75C51B869D0C0333132E0E940746F70BA376B609CD0C80D5156",
		"EAFF61BFDA58D2E59B441359A1F7133E996857E499BF4C96D71931614F292B2D59CD51923085C89CFBDC0FAE9E0FD38DFA7A2717208515EBD59A187F90CD40E9",
		"538B4F6B950E280590AAB36344F7EABA759353951FB804E29B9B33F7152FCCA4D9325F2244C91CFECDBE3F39F4CFC8169E268DEC54852D5441B95D85A30CE033"
	};

	tinyToolkit::hash::HMAC_SHA512 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i].c_str());

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_SHA512, UChar)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"2AAD43C04FE3DB5AB851814117EFC8C1E57D6CEE73E388062E9795222D7CA08632F63CD00F7F6065EF756B1BAD6F99FEDB7D5B98A53FB5D1220FE2BBB7EA85A1",
		"A322F98C01F3C53644DE2FB5F615C9ED40B738CE7BAAD295B8A97E1061BBB384469C8497403DE75C51B869D0C0333132E0E940746F70BA376B609CD0C80D5156",
		"EAFF61BFDA58D2E59B441359A1F7133E996857E499BF4C96D71931614F292B2D59CD51923085C89CFBDC0FAE9E0FD38DFA7A2717208515EBD59A187F90CD40E9",
		"538B4F6B950E280590AAB36344F7EABA759353951FB804E29B9B33F7152FCCA4D9325F2244C91CFECDBE3F39F4CFC8169E268DEC54852D5441B95D85A30CE033"
	};

	tinyToolkit::hash::HMAC_SHA512 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(reinterpret_cast<const uint8_t *>(src[i].c_str()));

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_SHA512, String)
{
	std::vector<std::string> src{ "123", "abc", ";'.", "#$%" };
	std::vector<std::string> dst
	{
		"2AAD43C04FE3DB5AB851814117EFC8C1E57D6CEE73E388062E9795222D7CA08632F63CD00F7F6065EF756B1BAD6F99FEDB7D5B98A53FB5D1220FE2BBB7EA85A1",
		"A322F98C01F3C53644DE2FB5F615C9ED40B738CE7BAAD295B8A97E1061BBB384469C8497403DE75C51B869D0C0333132E0E940746F70BA376B609CD0C80D5156",
		"EAFF61BFDA58D2E59B441359A1F7133E996857E499BF4C96D71931614F292B2D59CD51923085C89CFBDC0FAE9E0FD38DFA7A2717208515EBD59A187F90CD40E9",
		"538B4F6B950E280590AAB36344F7EABA759353951FB804E29B9B33F7152FCCA4D9325F2244C91CFECDBE3F39F4CFC8169E268DEC54852D5441B95D85A30CE033"
	};

	tinyToolkit::hash::HMAC_SHA512 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i]);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_SHA512, Char_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"2AAD43C04FE3DB5AB851814117EFC8C1E57D6CEE73E388062E9795222D7CA08632F63CD00F7F6065EF756B1BAD6F99FEDB7D5B98A53FB5D1220FE2BBB7EA85A1",
		"A322F98C01F3C53644DE2FB5F615C9ED40B738CE7BAAD295B8A97E1061BBB384469C8497403DE75C51B869D0C0333132E0E940746F70BA376B609CD0C80D5156",
		"EAFF61BFDA58D2E59B441359A1F7133E996857E499BF4C96D71931614F292B2D59CD51923085C89CFBDC0FAE9E0FD38DFA7A2717208515EBD59A187F90CD40E9",
		"538B4F6B950E280590AAB36344F7EABA759353951FB804E29B9B33F7152FCCA4D9325F2244C91CFECDBE3F39F4CFC8169E268DEC54852D5441B95D85A30CE033"
	};

	tinyToolkit::hash::HMAC_SHA512 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i].c_str(), 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_SHA512, UChar_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"2AAD43C04FE3DB5AB851814117EFC8C1E57D6CEE73E388062E9795222D7CA08632F63CD00F7F6065EF756B1BAD6F99FEDB7D5B98A53FB5D1220FE2BBB7EA85A1",
		"A322F98C01F3C53644DE2FB5F615C9ED40B738CE7BAAD295B8A97E1061BBB384469C8497403DE75C51B869D0C0333132E0E940746F70BA376B609CD0C80D5156",
		"EAFF61BFDA58D2E59B441359A1F7133E996857E499BF4C96D71931614F292B2D59CD51923085C89CFBDC0FAE9E0FD38DFA7A2717208515EBD59A187F90CD40E9",
		"538B4F6B950E280590AAB36344F7EABA759353951FB804E29B9B33F7152FCCA4D9325F2244C91CFECDBE3F39F4CFC8169E268DEC54852D5441B95D85A30CE033"
	};

	tinyToolkit::hash::HMAC_SHA512 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(reinterpret_cast<const uint8_t *>(src[i].c_str()), 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}

TOOLKIT_TEST_CASE(HMAC_SHA512, String_Length)
{
	std::vector<std::string> src{ "123456", "abcdef", ";'.,/]", "#$%^&*" };
	std::vector<std::string> dst
	{
		"2AAD43C04FE3DB5AB851814117EFC8C1E57D6CEE73E388062E9795222D7CA08632F63CD00F7F6065EF756B1BAD6F99FEDB7D5B98A53FB5D1220FE2BBB7EA85A1",
		"A322F98C01F3C53644DE2FB5F615C9ED40B738CE7BAAD295B8A97E1061BBB384469C8497403DE75C51B869D0C0333132E0E940746F70BA376B609CD0C80D5156",
		"EAFF61BFDA58D2E59B441359A1F7133E996857E499BF4C96D71931614F292B2D59CD51923085C89CFBDC0FAE9E0FD38DFA7A2717208515EBD59A187F90CD40E9",
		"538B4F6B950E280590AAB36344F7EABA759353951FB804E29B9B33F7152FCCA4D9325F2244C91CFECDBE3F39F4CFC8169E268DEC54852D5441B95D85A30CE033"
	};

	tinyToolkit::hash::HMAC_SHA512 handle{ };

	handle.SetKey("fuck");

	for (std::size_t i = 0; i < 4; ++i)
	{
		handle.Append(src[i], 3);

		TOOLKIT_EXPECT_STR_EQ(handle.Result(), dst[i]);
	}
}