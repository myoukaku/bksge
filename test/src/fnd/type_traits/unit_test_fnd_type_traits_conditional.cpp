/**
 *	@file	unit_test_fnd_type_traits_conditional.cpp
 *
 *	@brief	conditional のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>

GTEST_TEST(TypeTraitsTest, ConditionalTest)
{
	static_assert(bksge::is_same<int,  bksge::conditional<true,  int, char>::type>::value, "");
	static_assert(bksge::is_same<char, bksge::conditional<false, int, char>::type>::value, "");

	static_assert(bksge::is_same<double, bksge::conditional_t<true,  double, int>>::value, "");
	static_assert(bksge::is_same<int,    bksge::conditional_t<false, double, int>>::value, "");
}
