/**
 *	@file	unit_test_functional_divides.cpp
 *
 *	@brief	divides のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/functional/divides.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "constexpr_test.hpp"

GTEST_TEST(FunctionalTest, DividesTest)
{
	{
		using type = bksge::divides<int>;
		static_assert(std::is_same<type::result_type,          int>::value, "");
		static_assert(std::is_same<type::first_argument_type,  int>::value, "");
		static_assert(std::is_same<type::second_argument_type, int>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ( 0, type()(  0,  1));
		BKSGE_CONSTEXPR_EXPECT_EQ(-8, type()( 42, -5));
	}
	{
		using type = bksge::divides<float>;
		static_assert(std::is_same<type::result_type,          float>::value, "");
		static_assert(std::is_same<type::first_argument_type,  float>::value, "");
		static_assert(std::is_same<type::second_argument_type, float>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ( 0.25, type()(  0.5,  2.0));
		BKSGE_CONSTEXPR_EXPECT_EQ( 0.5,  type()( -2.5, -5.0));
	}
	{
		using type = bksge::divides<>;
		BKSGE_CONSTEXPR_EXPECT_EQ( 2.0,  type()( 1,   0.5));
		BKSGE_CONSTEXPR_EXPECT_EQ(-0.25, type()(-2.0, 8U));
	}
}
