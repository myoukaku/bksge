/**
 *	@file	unit_test_functional_modulus.cpp
 *
 *	@brief	modulus のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/functional/modulus.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "constexpr_test.hpp"

GTEST_TEST(FunctionalTest, ModulusTest)
{
	{
		using type = bksge::modulus<int>;
		static_assert(std::is_same<type::result_type,          int>::value, "");
		static_assert(std::is_same<type::first_argument_type,  int>::value, "");
		static_assert(std::is_same<type::second_argument_type, int>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ( 0, type()(  0,  1));
		BKSGE_CONSTEXPR_EXPECT_EQ( 2, type()( 42,  5));
	}
	{
		using type = bksge::modulus<>;
		BKSGE_CONSTEXPR_EXPECT_EQ( 1, type()(9, 4));
		BKSGE_CONSTEXPR_EXPECT_EQ( 0, type()(9, 3));
	}
}
