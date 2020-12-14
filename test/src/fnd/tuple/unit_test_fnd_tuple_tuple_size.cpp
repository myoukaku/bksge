/**
 *	@file	unit_test_fnd_tuple_tuple_size.cpp
 *
 *	@brief	tuple_size のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple_size.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

static_assert(bksge::tuple_size<bksge::tuple<>               >::value == 0, "");
static_assert(bksge::tuple_size<bksge::tuple<> const         >::value == 0, "");
static_assert(bksge::tuple_size<bksge::tuple<>       volatile>::value == 0, "");
static_assert(bksge::tuple_size<bksge::tuple<> const volatile>::value == 0, "");

static_assert(bksge::tuple_size<bksge::tuple<int>               >::value == 1, "");
static_assert(bksge::tuple_size<bksge::tuple<int> const         >::value == 1, "");
static_assert(bksge::tuple_size<bksge::tuple<int>       volatile>::value == 1, "");
static_assert(bksge::tuple_size<bksge::tuple<int> const volatile>::value == 1, "");

static_assert(bksge::tuple_size<bksge::tuple<void>               >::value == 1, "");
static_assert(bksge::tuple_size<bksge::tuple<void> const         >::value == 1, "");
static_assert(bksge::tuple_size<bksge::tuple<void>       volatile>::value == 1, "");
static_assert(bksge::tuple_size<bksge::tuple<void> const volatile>::value == 1, "");

static_assert(bksge::tuple_size<bksge::tuple<float, int&>               >::value == 2, "");
static_assert(bksge::tuple_size<bksge::tuple<float, int&> const         >::value == 2, "");
static_assert(bksge::tuple_size<bksge::tuple<float, int&>       volatile>::value == 2, "");
static_assert(bksge::tuple_size<bksge::tuple<float, int&> const volatile>::value == 2, "");

static_assert(bksge::tuple_size<bksge::tuple<const float, int&, void>               >::value == 3, "");
static_assert(bksge::tuple_size<bksge::tuple<const float, int&, void> const         >::value == 3, "");
static_assert(bksge::tuple_size<bksge::tuple<const float, int&, void>       volatile>::value == 3, "");
static_assert(bksge::tuple_size<bksge::tuple<const float, int&, void> const volatile>::value == 3, "");
