/**
 *	@file	unit_test_fnd_array_tuple_element.cpp
 *
 *	@brief	tuple_element のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/array/array.hpp>
#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>

namespace bksge_array_test
{

namespace tuple_element_test
{

using array_type = bksge::array<int, 3>;

static_assert(bksge::is_same<bksge::tuple_element_t<0, array_type>, int>::value, "");
static_assert(bksge::is_same<bksge::tuple_element_t<1, array_type>, int>::value, "");
static_assert(bksge::is_same<bksge::tuple_element_t<2, array_type>, int>::value, "");

static_assert(bksge::is_same<bksge::tuple_element_t<0, array_type const>, int const>::value, "");
static_assert(bksge::is_same<bksge::tuple_element_t<1, array_type const>, int const>::value, "");
static_assert(bksge::is_same<bksge::tuple_element_t<2, array_type const>, int const>::value, "");

static_assert(bksge::is_same<bksge::tuple_element_t<0, array_type volatile>, int volatile>::value, "");
static_assert(bksge::is_same<bksge::tuple_element_t<1, array_type volatile>, int volatile>::value, "");
static_assert(bksge::is_same<bksge::tuple_element_t<2, array_type volatile>, int volatile>::value, "");

static_assert(bksge::is_same<bksge::tuple_element_t<0, array_type const volatile>, int const volatile>::value, "");
static_assert(bksge::is_same<bksge::tuple_element_t<1, array_type const volatile>, int const volatile>::value, "");
static_assert(bksge::is_same<bksge::tuple_element_t<2, array_type const volatile>, int const volatile>::value, "");

}	// namespace tuple_element_test

}	// namespace bksge_array_test
