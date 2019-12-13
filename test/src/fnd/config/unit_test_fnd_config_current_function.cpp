/**
 *	@file	unit_test_fnd_config_current_function.cpp
 *
 *	@brief	BKSGE_CURRENT_FUNCTION のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>

namespace bksge_config_current_function_test
{

static char const* s_function_name_1;
static char const* s_function_name_2;
static char const* s_function_name_3;
static char const* s_function_name_4;
static char const* s_function_name_5;

static void f1(void)
{
	s_function_name_1 = BKSGE_CURRENT_FUNCTION;
}

static void f2(void)
{
	s_function_name_2 = BKSGE_CURRENT_FUNCTION;
}

static void f2(int)
{
	s_function_name_3 = BKSGE_CURRENT_FUNCTION;
}

static void f2(int, float)
{
	s_function_name_4 = BKSGE_CURRENT_FUNCTION;
}

GTEST_TEST(ConfigTest, CurrentFunctionTest)
{
	s_function_name_5 = BKSGE_CURRENT_FUNCTION;

	f1();
	f2();
	f2(0);
	f2(0, 0.0f);

	EXPECT_TRUE(s_function_name_1 != nullptr);
	EXPECT_TRUE(s_function_name_2 != nullptr);
	EXPECT_TRUE(s_function_name_3 != nullptr);
	EXPECT_TRUE(s_function_name_4 != nullptr);
	EXPECT_TRUE(s_function_name_5 != nullptr);
	EXPECT_STRNE(s_function_name_1, s_function_name_2);
	EXPECT_STRNE(s_function_name_1, s_function_name_3);
	EXPECT_STRNE(s_function_name_1, s_function_name_4);
	EXPECT_STRNE(s_function_name_1, s_function_name_5);
	EXPECT_STRNE(s_function_name_2, s_function_name_3);
	EXPECT_STRNE(s_function_name_2, s_function_name_4);
	EXPECT_STRNE(s_function_name_2, s_function_name_5);
	EXPECT_STRNE(s_function_name_3, s_function_name_4);
	EXPECT_STRNE(s_function_name_3, s_function_name_5);
	EXPECT_STRNE(s_function_name_4, s_function_name_5);
}

}	// namespace bksge_config_current_function_test
