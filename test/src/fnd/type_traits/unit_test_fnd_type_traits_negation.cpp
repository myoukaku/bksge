/**
 *	@file	unit_test_fnd_type_traits_negation.cpp
 *
 *	@brief	negation のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/negation.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "type_traits_test_utility.hpp"

GTEST_TEST(TypeTraitsTest, NegationTest)
{
	IntegralConstantTest<bksge::negation<std::false_type>, true>();
	IntegralConstantTest<bksge::negation<std::true_type>,  false>();
	IntegralConstantTest<bksge::negation<std::is_unsigned<signed   int>>, true>();
	IntegralConstantTest<bksge::negation<std::is_unsigned<unsigned int>>, false>();
}
