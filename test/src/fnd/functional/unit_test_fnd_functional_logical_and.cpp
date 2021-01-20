/**
 *	@file	unit_test_fnd_functional_logical_and.cpp
 *
 *	@brief	logical_and のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/logical_and.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(FunctionalTest, LogicalAndTest)
{
	{
		using type = bksge::logical_and<int>;
		//static_assert(bksge::is_same<type::result_type,          bool>::value, "");
		//static_assert(bksge::is_same<type::first_argument_type,  int>::value, "");
		//static_assert(bksge::is_same<type::second_argument_type, int>::value, "");
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(0, 0));
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(1, 0));
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(0, 1));
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(1, 1));
	}
	{
		using type = bksge::logical_and<>;
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(false, false));
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(true , false));
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(false, true ));
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(true , true ));
	}
}
