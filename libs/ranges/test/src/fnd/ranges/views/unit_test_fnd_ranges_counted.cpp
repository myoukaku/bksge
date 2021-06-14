/**
 *	@file	unit_test_fnd_ranges_counted.cpp
 *
 *	@brief	ranges::counted のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/views/counted.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/concepts/common_range.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_ranges_test
{

namespace counted_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = { 0,1,2,3,4,5,6,7,8,9 };
	auto v = views::counted(x, 5);

	int y[] = { 0,1,2,3,4 };
	VERIFY(ranges::equal(v, y));

	using R = decltype(v);
	static_assert( ranges::is_view<R>::value, "");
	static_assert( ranges::is_sized_range<R>::value, "");
	static_assert( ranges::is_common_range<R>::value, "");
	static_assert( ranges::is_random_access_range<R>::value, "");

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = { 0,1,2,3,4,5,6,7,8,9 };
	test_forward_range<int> rx(x);
	auto v = views::counted(rx.begin(), 4);

	int y[] = { 0,1,2,3 };
	VERIFY(ranges::equal(v, y));

	using R = decltype(v);
	static_assert( ranges::is_view<R>::value, "");
	static_assert( ranges::is_sized_range<R>::value, "");
	static_assert(!ranges::is_common_range<R>::value, "");
	static_assert(!ranges::is_random_access_range<R>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CountedTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace counted_test

}	// namespace bksge_ranges_test
