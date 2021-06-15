/**
 *	@file	unit_test_fnd_type_traits_integral_constant.cpp
 *
 *	@brief	integral_constant のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/integral_constant.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace bksge_type_traits_test
{

namespace integral_constant_test
{

using Type1 = bksge::integral_constant<int, 0>;
static_assert(Type1::value == 0, "");
static_assert(bksge::is_same<Type1::value_type, int>::value, "");

using Type2 = bksge::integral_constant<int, 42>;
static_assert(Type2::value == 42, "");
static_assert(bksge::is_same<Type2::value_type, int>::value, "");

using Type3 = bksge::integral_constant<unsigned char, 1>;
static_assert(Type3::value == 1, "");
static_assert(bksge::is_same<Type3::value_type, unsigned char>::value, "");

}	// namespace integral_constant_test

}	// namespace bksge_type_traits_test
