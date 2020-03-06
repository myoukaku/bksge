/**
 *	@file	unit_test_fnd_stdexcept_length_error.cpp
 *
 *	@brief	length_error のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/stdexcept/length_error.hpp>
#include <bksge/fnd/stdexcept/logic_error.hpp>
#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <bksge/fnd/type_traits/is_polymorphic.hpp>
//#include <bksge/fnd/string.hpp>
#include <string>
#include <gtest/gtest.h>

GTEST_TEST(StdExceptTest, LengthErrorTest)
{
	static_assert(bksge::is_base_of<bksge::logic_error, bksge::length_error>::value, "");
	static_assert(bksge::is_polymorphic<bksge::length_error>::value, "");

	{
		char const* msg = "length_error message 1";
		bksge::length_error e(msg);
		EXPECT_STREQ(msg, e.what());
		bksge::length_error e2(e);
		EXPECT_STREQ(msg, e2.what());
		e2 = e;
		EXPECT_STREQ(msg, e2.what());
	}
	{
		std::string msg = "length_error message 2";
		bksge::length_error e(msg);
		EXPECT_EQ(msg, e.what());
		bksge::length_error e2(e);
		EXPECT_EQ(msg, e2.what());
		e2 = e;
		EXPECT_EQ(msg, e2.what());
	}
}
