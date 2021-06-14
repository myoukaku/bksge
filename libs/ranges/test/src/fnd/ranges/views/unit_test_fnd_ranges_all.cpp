/**
 *	@file	unit_test_fnd_ranges_all.cpp
 *
 *	@brief	ranges::all のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/views/all.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_ranges_test
{

namespace all_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = { 1,2,3,4,5 };
	auto v1 = views::all(x);
	auto v2 = x | views::all;
	auto v3 = x | views::all | views::all;
	auto v4 = x | (views::all | views::all);

	static_assert(ranges::is_view<decltype(v1)>::value, "");
	static_assert(ranges::is_view<decltype(v2)>::value, "");
	static_assert(ranges::is_view<decltype(v3)>::value, "");
	static_assert(ranges::is_view<decltype(v4)>::value, "");

	static_assert(ranges::is_random_access_range<decltype(v1)>::value, "");
	static_assert(ranges::is_random_access_range<decltype(v2)>::value, "");
	static_assert(ranges::is_random_access_range<decltype(v3)>::value, "");
	static_assert(ranges::is_random_access_range<decltype(v4)>::value, "");

	VERIFY(ranges::size(v1) == 5);
	VERIFY(ranges::size(v2) == 5);
	VERIFY(ranges::size(v3) == 5);
	VERIFY(ranges::size(v4) == 5);

	VERIFY(ranges::equal(x, v1));
	VERIFY(ranges::equal(x, v2));
	VERIFY(ranges::equal(x, v3));
	VERIFY(ranges::equal(x, v4));

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AllTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace all_test

}	// namespace bksge_ranges_test
