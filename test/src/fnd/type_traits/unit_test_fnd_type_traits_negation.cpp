/**
 *	@file	unit_test_fnd_type_traits_negation.cpp
 *
 *	@brief	negation のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_unsigned.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

GTEST_TEST(TypeTraitsTest, NegationTest)
{
	IntegralConstantTest<bksge::negation<bksge::false_type>, true>();
	IntegralConstantTest<bksge::negation<bksge::true_type>,  false>();
	IntegralConstantTest<bksge::negation<bksge::is_unsigned<signed   int>>, true>();
	IntegralConstantTest<bksge::negation<bksge::is_unsigned<unsigned int>>, false>();
}
