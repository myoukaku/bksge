/**
 *	@file	unit_test_fnd_utility_to_underlying.cpp
 *
 *	@brief	to_underlying のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/to_underlying.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_utility_test
{

namespace to_underlying_test
{

enum class E1 : char { e = 1 };
enum struct E2 : long { e = 2 };
enum E3 : unsigned { e = 3 };

static_assert(bksge::is_same<char, decltype(bksge::to_underlying(E1::e))>::value, "");
static_assert(bksge::is_same<long, decltype(bksge::to_underlying(E2::e))>::value, "");
static_assert(bksge::is_same<unsigned, decltype(bksge::to_underlying(e))>::value, "");

GTEST_TEST(UtilityTest, ToUnderlyingTest)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::to_underlying(E1::e));
	BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::to_underlying(E2::e));
	BKSGE_CONSTEXPR_EXPECT_EQ(3u, bksge::to_underlying(e));
}

}	// namespace to_underlying_test

}	// namespace bksge_utility_test
