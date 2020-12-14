/**
 *	@file	unit_test_fnd_tuple_tuple_element.cpp
 *
 *	@brief	tuple_element のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

static_assert(bksge::is_same<bksge::tuple_element_t<0, bksge::tuple<int>               >, int               >::value, "");
static_assert(bksge::is_same<bksge::tuple_element_t<0, bksge::tuple<int> const         >, int const         >::value, "");
static_assert(bksge::is_same<bksge::tuple_element_t<0, bksge::tuple<int>       volatile>, int       volatile>::value, "");
static_assert(bksge::is_same<bksge::tuple_element_t<0, bksge::tuple<int> const volatile>, int const volatile>::value, "");

static_assert(bksge::is_same<bksge::tuple_element_t<0, bksge::tuple<float, int>               >, float               >::value, "");
static_assert(bksge::is_same<bksge::tuple_element_t<0, bksge::tuple<float, int> const         >, float const         >::value, "");
static_assert(bksge::is_same<bksge::tuple_element_t<0, bksge::tuple<float, int>       volatile>, float       volatile>::value, "");
static_assert(bksge::is_same<bksge::tuple_element_t<0, bksge::tuple<float, int> const volatile>, float const volatile>::value, "");

static_assert(bksge::is_same<bksge::tuple_element_t<1, bksge::tuple<float, int>               >, int               >::value, "");
static_assert(bksge::is_same<bksge::tuple_element_t<1, bksge::tuple<float, int> const         >, int const         >::value, "");
static_assert(bksge::is_same<bksge::tuple_element_t<1, bksge::tuple<float, int>       volatile>, int       volatile>::value, "");
static_assert(bksge::is_same<bksge::tuple_element_t<1, bksge::tuple<float, int> const volatile>, int const volatile>::value, "");
