/**
 *	@file	unit_test_fnd_stdexcept_range_error.cpp
 *
 *	@brief	range_error のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/stdexcept/range_error.hpp>
#include <bksge/fnd/stdexcept/runtime_error.hpp>
#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <bksge/fnd/type_traits/is_polymorphic.hpp>
#include <bksge/fnd/string/string.hpp>
#include <gtest/gtest.h>

GTEST_TEST(StdExceptTest, RangeErrorTest)
{
	static_assert(bksge::is_base_of<bksge::runtime_error, bksge::range_error>::value, "");
	static_assert(bksge::is_polymorphic<bksge::range_error>::value, "");

	{
		char const* msg = "range_error message 1";
		bksge::range_error e(msg);
		EXPECT_STREQ(msg, e.what());
		bksge::range_error e2(e);
		EXPECT_STREQ(msg, e2.what());
		e2 = e;
		EXPECT_STREQ(msg, e2.what());
	}
	{
		bksge::string msg = "range_error message 2";
		bksge::range_error e(msg);
		EXPECT_EQ(msg, e.what());
		bksge::range_error e2(e);
		EXPECT_EQ(msg, e2.what());
		e2 = e;
		EXPECT_EQ(msg, e2.what());
	}
}
