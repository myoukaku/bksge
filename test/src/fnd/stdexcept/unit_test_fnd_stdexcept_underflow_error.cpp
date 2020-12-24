/**
 *	@file	unit_test_fnd_stdexcept_underflow_error.cpp
 *
 *	@brief	underflow_error のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/stdexcept/underflow_error.hpp>
#include <bksge/fnd/stdexcept/runtime_error.hpp>
#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <bksge/fnd/type_traits/is_polymorphic.hpp>
#include <bksge/fnd/string/string.hpp>
#include <gtest/gtest.h>

GTEST_TEST(StdExceptTest, UnderflowErrorTest)
{
	static_assert(bksge::is_base_of<bksge::runtime_error, bksge::underflow_error>::value, "");
	static_assert(bksge::is_polymorphic<bksge::underflow_error>::value, "");

	{
		char const* msg = "underflow_error message 1";
		bksge::underflow_error e(msg);
		EXPECT_STREQ(msg, e.what());
		bksge::underflow_error e2(e);
		EXPECT_STREQ(msg, e2.what());
		e2 = e;
		EXPECT_STREQ(msg, e2.what());
	}
	{
		bksge::string msg = "underflow_error message 2";
		bksge::underflow_error e(msg);
		EXPECT_EQ(msg, e.what());
		bksge::underflow_error e2(e);
		EXPECT_EQ(msg, e2.what());
		e2 = e;
		EXPECT_EQ(msg, e2.what());
	}
}
