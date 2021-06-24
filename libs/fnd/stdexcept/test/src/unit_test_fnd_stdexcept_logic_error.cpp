/**
 *	@file	unit_test_fnd_stdexcept_logic_error.cpp
 *
 *	@brief	logic_error のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/stdexcept/logic_error.hpp>
#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <bksge/fnd/type_traits/is_polymorphic.hpp>
#include <bksge/fnd/string/string.hpp>
#include <gtest/gtest.h>
#include <exception>

GTEST_TEST(StdExceptTest, LogicErrorTest)
{
	static_assert(bksge::is_base_of<std::exception, bksge::logic_error>::value, "");
	static_assert(bksge::is_polymorphic<bksge::logic_error>::value, "");

	{
		char const* msg = "logic_error message 1";
		bksge::logic_error e(msg);
		EXPECT_STREQ(msg, e.what());
		bksge::logic_error e2(e);
		EXPECT_STREQ(msg, e2.what());
		e2 = e;
		EXPECT_STREQ(msg, e2.what());
	}
	{
		bksge::string msg = "logic_error message 2";
		bksge::logic_error e(msg);
		EXPECT_EQ(msg, e.what());
		bksge::logic_error e2(e);
		EXPECT_EQ(msg, e2.what());
		e2 = e;
		EXPECT_EQ(msg, e2.what());
	}
}
