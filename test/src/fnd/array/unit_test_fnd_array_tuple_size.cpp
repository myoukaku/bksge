/**
 *	@file	unit_test_fnd_array_tuple_size.cpp
 *
 *	@brief	tuple_size のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/array/array.hpp>

namespace bksge_array_test
{

namespace tuple_size_test
{

using array_type = bksge::array<int, 3>;

static_assert(bksge::tuple_size<array_type               >::value == 3, "");
static_assert(bksge::tuple_size<array_type const         >::value == 3, "");
static_assert(bksge::tuple_size<array_type       volatile>::value == 3, "");
static_assert(bksge::tuple_size<array_type const volatile>::value == 3, "");

}	// namespace tuple_size_test

}	// namespace bksge_array_test
