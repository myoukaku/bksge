/**
 *	@file	unit_test_fnd_ranges_drop_view.cpp
 *
 *	@brief	ranges::drop_view のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/views/drop_view.hpp>
#include <bksge/fnd/ranges/views/take_view.hpp>
#include <bksge/fnd/ranges/views/iota_view.hpp>
#include <bksge/fnd/ranges/views/filter_view.hpp>
#include <bksge/fnd/ranges/views/transform_view.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/concepts/common_range.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/concepts/bidirectional_range.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/concepts/contiguous_range.hpp>
#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/ranges/empty.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/functional/negate.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_ranges_test
{

namespace drop_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {1, 2, 3, 4, 5};
	auto v = x | views::drop(3);
	using R = decltype(v);
	static_assert( ranges::is_view<R>::value, "");
	static_assert( ranges::is_sized_range<R>::value, "");
	static_assert( ranges::is_common_range<R>::value, "");
	static_assert( ranges::is_random_access_range<R>::value, "");
	static_assert( ranges::is_contiguous_range<R>::value, "");

	VERIFY(ranges::size(v) == 2);

	int y[] = { 4,5 };
	VERIFY(ranges::equal(v, y));

	{
		auto b = v.base();
		VERIFY(ranges::equal(b, x));
	}
	{
		auto b = views::drop(x, 3).base();
		VERIFY(ranges::equal(b, x));
	}

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {1, 2, 3, 4, 5};
	test_bidirectional_range<int> rx(x);
	auto v = rx | views::drop(3);
	using R = decltype(v);
	static_assert( ranges::is_view<R>::value, "");
	static_assert(!ranges::is_sized_range<R>::value, "");
	static_assert(!ranges::is_common_range<R>::value, "");
	static_assert( ranges::is_bidirectional_range<R>::value, "");
	static_assert(!ranges::is_random_access_range<R>::value, "");

	int y[] = { 4,5 };
	VERIFY(ranges::equal(v, y));

	{
		auto it = ranges::begin(v);
		VERIFY((it == ranges::end(v)) == false);
		VERIFY((it != ranges::end(v)) == true);
		VERIFY((ranges::end(v) == it) == false);
		VERIFY((ranges::end(v) != it) == true);
	}
	return true;
}

BKSGE_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	auto v = views::iota(0) | views::drop(10) | views::take(3);
	using R = decltype(v);
	static_assert( ranges::is_view<R>::value, "");
	static_assert(!ranges::is_sized_range<R>::value, "");
	static_assert(!ranges::is_common_range<R>::value, "");
	static_assert( ranges::is_bidirectional_range<R>::value, "");
	static_assert(!ranges::is_random_access_range<R>::value, "");

	int y[] = { 10,11,12 };
	VERIFY(ranges::equal(v, y));

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test04()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int const x[] = {1, 2, 3, 4, 5};
	auto v1 = x | views::drop(4);
	auto v2 = x | views::drop(5);
	auto v3 = x | views::drop(6);
	VERIFY(!ranges::empty(v1));
	VERIFY( ranges::empty(v2));
	VERIFY( ranges::empty(v3));

	return true;
}

struct IsOdd
{
	constexpr bool operator()(int i) const { return i % 2 == 1; }
};

BKSGE_CXX14_CONSTEXPR bool test05()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	auto v =
		views::iota(1) |							// 1,2,3,...
		views::filter(IsOdd{}) |					// 1,3,5,...
		views::take(5) |							// 1,3,5,7,9
		views::transform(bksge::negate<>{}) |		// -1,-3,-5,-7,-9
		views::drop(2);								// -5,-7,-9
	using R = decltype(v);
	static_assert( ranges::is_view<R>::value, "");
	static_assert(!ranges::is_sized_range<R>::value, "");
	static_assert(!ranges::is_common_range<R>::value, "");
	static_assert( ranges::is_bidirectional_range<R>::value, "");
	static_assert(!ranges::is_random_access_range<R>::value, "");

	int y[] = { -5,-7,-9 };
	VERIFY(ranges::equal(v, y));

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test06()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {1,2,3,4,5};
	auto const v = x | views::transform(bksge::negate<>{}) | views::drop(1);
	using R = decltype(v);
	static_assert(!ranges::is_view<R>::value, "");
	static_assert( ranges::is_sized_range<R>::value, "");
	static_assert( ranges::is_common_range<R>::value, "");
	static_assert( ranges::is_random_access_range<R>::value, "");
//	static_assert(!ranges::is_contiguous_range<R>::value, "");

	VERIFY(ranges::size(v) == 4);

	int y[] = { -2,-3,-4,-5 };
	VERIFY(ranges::equal(v, y));

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, DropViewTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test06());
}

}	// namespace drop_view_test

}	// namespace bksge_ranges_test
