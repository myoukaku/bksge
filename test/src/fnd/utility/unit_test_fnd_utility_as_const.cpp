/**
 *	@file	unit_test_fnd_utility_as_const.cpp
 *
 *	@brief	as_const のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/as_const.hpp>
#include <bksge/fnd/string/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(UtilityTest, AsConstTest)
{
	bksge::string mutable_string = "Hello World!";
	const bksge::string& const_view = bksge::as_const(mutable_string);

	EXPECT_TRUE(const_view == mutable_string);
	EXPECT_TRUE(bksge::as_const(mutable_string) == mutable_string);

	auto iter1 = mutable_string.begin();
	auto iter2 = bksge::as_const(mutable_string).begin();

	static_assert(bksge::is_same<decltype(iter1), bksge::string::iterator>::value, "");
	static_assert(bksge::is_same<decltype(iter2), bksge::string::const_iterator>::value, "");
}
