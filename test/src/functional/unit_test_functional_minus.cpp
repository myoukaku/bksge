/**
 *	@file	unit_test_functional_minus.cpp
 *
 *	@brief	minus のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/functional/minus.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "constexpr_test.hpp"

GTEST_TEST(FunctionalTest, MinusTest)
{
	{
		using type = bksge::minus<int>;
		static_assert(std::is_same<type::result_type,          int>::value, "");
		static_assert(std::is_same<type::first_argument_type,  int>::value, "");
		static_assert(std::is_same<type::second_argument_type, int>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ( 0, type()(  0,  0));
		BKSGE_CONSTEXPR_EXPECT_EQ(47, type()( 42, -5));
	}
	{
		using type = bksge::minus<float>;
		static_assert(std::is_same<type::result_type,          float>::value, "");
		static_assert(std::is_same<type::first_argument_type,  float>::value, "");
		static_assert(std::is_same<type::second_argument_type, float>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(-1.75, type()(  0.5,  2.25));
		BKSGE_CONSTEXPR_EXPECT_EQ( 3.5,  type()( -1.5, -5.0));
	}
	{
		using type = bksge::minus<>;
		BKSGE_CONSTEXPR_EXPECT_EQ( 0.5, type()(  1,   0.5));
		BKSGE_CONSTEXPR_EXPECT_EQ(-9.5, type()( -1.5, 8U));
	}
}
