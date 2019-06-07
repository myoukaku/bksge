﻿/**
 *	@file	unit_test_functional_less.cpp
 *
 *	@brief	less のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/functional/less.hpp>
#include <gtest/gtest.h>
#include <string>
#include <type_traits>
#include "constexpr_test.hpp"

GTEST_TEST(FunctionalTest, LessTest)
{
	{
		using type = bksge::less<int>;
		static_assert(std::is_same<type::result_type,          bool>::value, "");
		static_assert(std::is_same<type::first_argument_type,  int>::value, "");
		static_assert(std::is_same<type::second_argument_type, int>::value, "");
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(2, 2));
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(2, 3));
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(2, 1));
	}
	{
		using type = bksge::less<float>;
		static_assert(std::is_same<type::result_type,          bool>::value, "");
		static_assert(std::is_same<type::first_argument_type,  float>::value, "");
		static_assert(std::is_same<type::second_argument_type, float>::value, "");
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(-1.5f, -1.5f));
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(-1.5f, -1.6f));
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(-1.6f, -1.5f));
	}
	{
		using type = bksge::less<>;
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(3U, 3.0));
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(3U, 3.1));
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(3U, 2.9));
		EXPECT_FALSE(type()(std::string("A"), "A"));
		EXPECT_TRUE (type()(std::string("A"), "B"));
		EXPECT_FALSE(type()(std::string("B"), "A"));
	}
}
