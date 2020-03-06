/**
 *	@file	unit_test_fnd_stdexcept_invalid_argument.cpp
 *
 *	@brief	invalid_argument のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/stdexcept/invalid_argument.hpp>
#include <bksge/fnd/stdexcept/logic_error.hpp>
#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <bksge/fnd/type_traits/is_polymorphic.hpp>
//#include <bksge/fnd/string.hpp>
#include <string>
#include <gtest/gtest.h>

GTEST_TEST(StdExceptTest, InvalidArgumentTest)
{
	static_assert(bksge::is_base_of<bksge::logic_error, bksge::invalid_argument>::value, "");
	static_assert(bksge::is_polymorphic<bksge::invalid_argument>::value, "");

	{
		char const* msg = "invalid_argument message 1";
		bksge::invalid_argument e(msg);
		EXPECT_STREQ(msg, e.what());
		bksge::invalid_argument e2(e);
		EXPECT_STREQ(msg, e2.what());
		e2 = e;
		EXPECT_STREQ(msg, e2.what());
	}
	{
		std::string msg = "invalid_argument message 2";
		bksge::invalid_argument e(msg);
		EXPECT_EQ(msg, e.what());
		bksge::invalid_argument e2(e);
		EXPECT_EQ(msg, e2.what());
		e2 = e;
		EXPECT_EQ(msg, e2.what());
	}
}
