/**
 *	@file	unit_test_fnd_functional_plus.cpp
 *
 *	@brief	plus のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/plus.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(FunctionalTest, PlusTest)
{
	{
		using type = bksge::plus<int>;
		//static_assert(bksge::is_same<type::result_type,          int>::value, "");
		//static_assert(bksge::is_same<type::first_argument_type,  int>::value, "");
		//static_assert(bksge::is_same<type::second_argument_type, int>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ( 0, type()(  0,  0));
		BKSGE_CONSTEXPR_EXPECT_EQ(37, type()( 42, -5));
	}
	{
		using type = bksge::plus<float>;
		//static_assert(bksge::is_same<type::result_type,          float>::value, "");
		//static_assert(bksge::is_same<type::first_argument_type,  float>::value, "");
		//static_assert(bksge::is_same<type::second_argument_type, float>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ( 2.75, type()(  0.5,  2.25));
		BKSGE_CONSTEXPR_EXPECT_EQ(-6.5,  type()( -1.5, -5.0));
	}
	{
		using type = bksge::plus<>;
		BKSGE_CONSTEXPR_EXPECT_EQ( 1.5, type()(  1,   0.5));
		BKSGE_CONSTEXPR_EXPECT_EQ( 6.5, type()( -1.5, 8U));
		EXPECT_EQ("Hello world", type()(bksge::string("Hello "), "world"));
	}
}
