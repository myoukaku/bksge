/**
 *	@file	unit_test_functional_not_equal_to.cpp
 *
 *	@brief	not_equal_to のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/functional/not_equal_to.hpp>
#include <gtest/gtest.h>
#include <string>
#include <type_traits>
#include "constexpr_test.hpp"

GTEST_TEST(FunctionalTest, NotEqualToTest)
{
	{
		using type = bksge::not_equal_to<int>;
		static_assert(std::is_same<type::result_type,          bool>::value, "");
		static_assert(std::is_same<type::first_argument_type,  int>::value, "");
		static_assert(std::is_same<type::second_argument_type, int>::value, "");
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(0, 0));
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(2, 3));
	}
	{
		using type = bksge::not_equal_to<float>;
		static_assert(std::is_same<type::result_type,          bool>::value, "");
		static_assert(std::is_same<type::first_argument_type,  float>::value, "");
		static_assert(std::is_same<type::second_argument_type, float>::value, "");
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(0.5,  0.5));
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(0.5, -0.5));
	}
	{
		using type = bksge::not_equal_to<>;
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(1, 1.0));
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(1.5, 2U));
		EXPECT_FALSE(type()(std::string("Hello"), "Hello"));
		EXPECT_TRUE (type()(std::string("Hello"), "hello"));
	}
}
