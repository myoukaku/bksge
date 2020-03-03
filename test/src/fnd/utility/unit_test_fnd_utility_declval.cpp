/**
 *	@file	unit_test_fnd_utility_declval.cpp
 *
 *	@brief	declval のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>

static_assert(bksge::is_same<decltype(bksge::declval<int>()   * bksge::declval<int>()), int>::value, "");
static_assert(bksge::is_same<decltype(bksge::declval<float>() * bksge::declval<int>()), float>::value, "");
static_assert(bksge::is_same<decltype(bksge::declval<int>()   * bksge::declval<float>()), float>::value, "");
static_assert(bksge::is_same<decltype(bksge::declval<float>() * bksge::declval<float>()), float>::value, "");
