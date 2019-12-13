/**
 *	@file	unit_test_fnd_functional_negate.cpp
 *
 *	@brief	negate のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/negate.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "constexpr_test.hpp"

GTEST_TEST(FunctionalTest, NegateTest)
{
	{
		using type = bksge::negate<int>;
		static_assert(std::is_same<type::result_type,   int>::value, "");
		static_assert(std::is_same<type::argument_type, int>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(  0, type()(  0));
		BKSGE_CONSTEXPR_EXPECT_EQ( -1, type()(  1));
		BKSGE_CONSTEXPR_EXPECT_EQ( 42, type()(-42));
	}
	{
		using type = bksge::negate<float>;
		static_assert(std::is_same<type::result_type,   float>::value, "");
		static_assert(std::is_same<type::argument_type, float>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(-0.5, type()( 0.5));
		BKSGE_CONSTEXPR_EXPECT_EQ( 1.5, type()(-1.5));
	}
	{
		using type = bksge::negate<>;
		BKSGE_CONSTEXPR_EXPECT_EQ(-1,   type()( 1));
		BKSGE_CONSTEXPR_EXPECT_EQ( 2,   type()(-2));
		BKSGE_CONSTEXPR_EXPECT_EQ( 0.5, type()(-0.5));
	}
}
