/**
 *	@file	unit_test_fnd_type_traits_bool_constant.cpp
 *
 *	@brief	bool_constant のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/integral_constant.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>

GTEST_TEST(TypeTraitsTest, BoolConstantTest)
{
	static_assert(bksge::is_same<bksge::true_type,  bksge::integral_constant<bool, true>>::value, "");
	static_assert(bksge::is_same<bksge::false_type, bksge::integral_constant<bool, false>>::value, "");

	static_assert(bksge::is_same<bksge::true_type::type,  bksge::integral_constant<bool, true>>::value, "");
	static_assert(bksge::is_same<bksge::false_type::type, bksge::integral_constant<bool, false>>::value, "");

	static_assert(bksge::is_same<bksge::true_type::value_type,  bool>::value, "");
	static_assert(bksge::is_same<bksge::false_type::value_type, bool>::value, "");

	static_assert(bksge::true_type::value  == true, "");
	static_assert(bksge::false_type::value == false, "");

	static_assert(bksge::true_type()  == true, "");
	static_assert(bksge::false_type() == false, "");
}
