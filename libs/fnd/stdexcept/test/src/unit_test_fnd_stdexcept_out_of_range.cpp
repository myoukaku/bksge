/**
 *	@file	unit_test_fnd_stdexcept_out_of_range.cpp
 *
 *	@brief	out_of_range のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/stdexcept/out_of_range.hpp>
#include <bksge/fnd/stdexcept/logic_error.hpp>
#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <bksge/fnd/type_traits/is_polymorphic.hpp>
#include <bksge/fnd/string/string.hpp>
#include <gtest/gtest.h>

GTEST_TEST(StdExceptTest, OutOfRangeTest)
{
	static_assert(bksge::is_base_of<bksge::logic_error, bksge::out_of_range>::value, "");
	static_assert(bksge::is_polymorphic<bksge::out_of_range>::value, "");

	{
		char const* msg = "out_of_range message 1";
		bksge::out_of_range e(msg);
		EXPECT_STREQ(msg, e.what());
		bksge::out_of_range e2(e);
		EXPECT_STREQ(msg, e2.what());
		e2 = e;
		EXPECT_STREQ(msg, e2.what());
	}
	{
		bksge::string msg = "out_of_range message 2";
		bksge::out_of_range e(msg);
		EXPECT_EQ(msg, e.what());
		bksge::out_of_range e2(e);
		EXPECT_EQ(msg, e2.what());
		e2 = e;
		EXPECT_EQ(msg, e2.what());
	}
}
