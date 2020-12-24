/**
 *	@file	unit_test_fnd_stdexcept_runtime_error.cpp
 *
 *	@brief	runtime_error のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/stdexcept/runtime_error.hpp>
#include <bksge/fnd/exception/exception.hpp>
#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <bksge/fnd/type_traits/is_polymorphic.hpp>
#include <bksge/fnd/string/string.hpp>
#include <gtest/gtest.h>

GTEST_TEST(StdExceptTest, RuntimeErrorTest)
{
	static_assert(bksge::is_base_of<bksge::exception, bksge::runtime_error>::value, "");
	static_assert(bksge::is_polymorphic<bksge::runtime_error>::value, "");

	{
		char const* msg = "runtime_error message 1";
		bksge::runtime_error e(msg);
		EXPECT_STREQ(msg, e.what());
		bksge::runtime_error e2(e);
		EXPECT_STREQ(msg, e2.what());
		e2 = e;
		EXPECT_STREQ(msg, e2.what());
	}
	{
		bksge::string msg = "runtime_error message 2";
		bksge::runtime_error e(msg);
		EXPECT_EQ(msg, e.what());
		bksge::runtime_error e2(e);
		EXPECT_EQ(msg, e2.what());
		e2 = e;
		EXPECT_EQ(msg, e2.what());
	}
}
