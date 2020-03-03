/**
 *	@file	unit_test_fnd_utility_as_const.cpp
 *
 *	@brief	as_const のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/as_const.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"

GTEST_TEST(UtilityTest, AsConstTest)
{
	std::string mutable_string = "Hello World!";
	const std::string& const_view = bksge::as_const(mutable_string);

	EXPECT_TRUE(const_view == mutable_string);
	EXPECT_TRUE(bksge::as_const(mutable_string) == mutable_string);

	auto iter1 = mutable_string.begin();
	auto iter2 = bksge::as_const(mutable_string).begin();

	static_assert(bksge::is_same<decltype(iter1), std::string::iterator>::value, "");
	static_assert(bksge::is_same<decltype(iter2), std::string::const_iterator>::value, "");
}
