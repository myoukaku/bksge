/**
 *	@file	unit_test_fnd_functional_multiplies.cpp
 *
 *	@brief	multiplies のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/multiplies.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "constexpr_test.hpp"

GTEST_TEST(FunctionalTest, MultipliesTest)
{
	{
		using type = bksge::multiplies<int>;
		static_assert(std::is_same<type::result_type,          int>::value, "");
		static_assert(std::is_same<type::first_argument_type,  int>::value, "");
		static_assert(std::is_same<type::second_argument_type, int>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(   0, type()(  0,  0));
		BKSGE_CONSTEXPR_EXPECT_EQ(-210, type()( 42, -5));
	}
	{
		using type = bksge::multiplies<float>;
		static_assert(std::is_same<type::result_type,          float>::value, "");
		static_assert(std::is_same<type::first_argument_type,  float>::value, "");
		static_assert(std::is_same<type::second_argument_type, float>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ( 1.125, type()(  0.5,  2.25));
		BKSGE_CONSTEXPR_EXPECT_EQ( 7.5,   type()( -1.5, -5.0));
	}
	{
		using type = bksge::multiplies<>;
		BKSGE_CONSTEXPR_EXPECT_EQ(  0.5, type()(  1,   0.5));
		BKSGE_CONSTEXPR_EXPECT_EQ(-12.0, type()( -1.5, 8U));
	}
}
