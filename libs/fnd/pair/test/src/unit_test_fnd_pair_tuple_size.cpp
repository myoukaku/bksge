/**
 *	@file	unit_test_fnd_utility_pair_tuple_size.cpp
 *
 *	@brief	tuple_size のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_pair_test
{

namespace tuple_size_test
{

static_assert(bksge::tuple_size<bksge::pair<int, float>>::value == 2, "");
static_assert(bksge::tuple_size<bksge::pair<int, float> const>::value == 2, "");
static_assert(bksge::tuple_size<bksge::pair<int, float> volatile>::value == 2, "");
static_assert(bksge::tuple_size<bksge::pair<int, float> const volatile>::value == 2, "");

}	// namespace tuple_size_test

}	// namespace bksge_pair_test
