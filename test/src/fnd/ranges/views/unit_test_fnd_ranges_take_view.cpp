/**
 *	@file	unit_test_fnd_ranges_take_view.cpp
 *
 *	@brief	ranges::take_view のテスト
 *
 *	@author	myoukaku
 */

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
#include <bksge/fnd/ranges/cbegin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/ranges/cend.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/functional/negate.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_ranges_test
{

namespace take_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct IsOdd
{
	constexpr bool operator()(int i) const { return i % 2 == 1; }
};

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	auto v = views::iota(0) | views::take(5);
	using R = decltype(v);
	static_assert( ranges::is_view<R>::value, "");
	static_assert(!ranges::is_sized_range<R>::value, "");
	static_assert(!ranges::is_common_range<R>::value, "");
	static_assert( ranges::is_range<R>::value, "");
	static_assert( ranges::is_input_range<R>::value, "");
	static_assert( ranges::is_forward_range<R>::value, "");
	static_assert( ranges::is_bidirectional_range<R>::value, "");
	static_assert(!ranges::is_random_access_range<R>::value, "");
	static_assert(!ranges::is_contiguous_range<R>::value, "");
	static_assert( ranges::is_range<const R>::value, "");

	int y[] = {0, 1, 2, 3, 4};
	VERIFY(ranges::equal(v, y));

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	auto v = views::take(views::iota(0, 20), 5);
	using R = decltype(v);
	static_assert( ranges::is_range<R>::value, "");
	static_assert( ranges::is_view<R>::value, "");
	static_assert( ranges::is_sized_range<R>::value, "");
	static_assert( ranges::is_common_range<R>::value, "");
	static_assert( ranges::is_random_access_range<R>::value, "");
	static_assert(!ranges::is_contiguous_range<R>::value, "");
	static_assert( ranges::is_range<const R>::value, "");

	int y[] = {0, 1, 2, 3, 4};
	VERIFY(ranges::equal(v, y));

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {0, 1, 2, 3, 4, 5};
	auto v = x | views::take(3);
	using R = decltype(v);
	static_assert( ranges::is_view<R>::value, "");
	static_assert( ranges::is_sized_range<R>::value, "");
	static_assert( ranges::is_common_range<R>::value, "");
	static_assert( ranges::is_forward_range<R>::value, "");
	static_assert( ranges::is_random_access_range<R>::value, "");
	static_assert( ranges::is_range<const R>::value, "");

	int y[] = {0, 1, 2};
	VERIFY(ranges::equal(v, y));

	{
		auto b = v.base();
		VERIFY(ranges::equal(b, x));
	}
	{
		auto b = views::take(x, 5).base();
		VERIFY(ranges::equal(b, x));
	}
	{
		auto it = ranges::begin(v);
		VERIFY((it == ranges::end(v)) == false);
		VERIFY((it != ranges::end(v)) == true);
		VERIFY((ranges::end(v) == it) == false);
		VERIFY((ranges::end(v) != it) == true);
	}

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test04()
{
#if !defined(BKSGE_MSVC)
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {0,1,2,3,4,5,6,7,8,9};
	test_bidirectional_range<int> rx(x);
	auto v = rx | views::filter(IsOdd{}) | views::take(3);
	using R = decltype(v);
	static_assert(!ranges::is_range<R const>::value, "");
	static_assert( ranges::is_range<R>::value, "");
	static_assert(!ranges::is_sized_range<R>::value, "");
	static_assert( ranges::is_view<R>::value, "");
	static_assert(!ranges::is_sized_range<R>::value, "");
	static_assert(!ranges::is_common_range<R>::value, "");
	static_assert( ranges::is_input_range<R>::value, "");
	static_assert( ranges::is_forward_range<R>::value, "");
	static_assert( ranges::is_bidirectional_range<R>::value, "");
	static_assert(!ranges::is_random_access_range<R>::value, "");

	int y[] = {1,3,5};
	VERIFY(ranges::equal(v, y));

	{
		auto it = ranges::begin(v);
		VERIFY((it == ranges::end(v)) == false);
		VERIFY((it != ranges::end(v)) == true);
		VERIFY((ranges::end(v) == it) == false);
		VERIFY((ranges::end(v) != it) == true);

		VERIFY((it.base() == ranges::end(v).base()) == false);
		VERIFY((it.base() != ranges::end(v).base()) == true);
		VERIFY((ranges::end(v).base() == it.base()) == false);
		VERIFY((ranges::end(v).base() != it.base()) == true);
	}
#endif
	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test05()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {0,1,2,3,4,5,6,7,8,9};
	test_bidirectional_sized_range<int> rx(x);
	auto v = rx | views::transform(bksge::negate<>{}) | views::take(3) | views::take(5);
	using R = decltype(v);
	static_assert( ranges::is_view<R>::value, "");
	static_assert( ranges::is_sized_range<R>::value, "");
	static_assert(!ranges::is_common_range<R>::value, "");
	static_assert( ranges::is_input_range<R>::value, "");
	static_assert(!ranges::is_forward_range<R>::value, "");
	static_assert(!ranges::is_bidirectional_range<R>::value, "");
	static_assert(!ranges::is_random_access_range<R>::value, "");

	int y[] = {0,-1,-2};
	VERIFY(ranges::equal(v, y));

	{
		auto it = ranges::begin(v);
		VERIFY((it == ranges::end(v)) == false);
		VERIFY((it != ranges::end(v)) == true);
		VERIFY((ranges::end(v) == it) == false);
		VERIFY((ranges::end(v) != it) == true);
	}
	{
		auto it = ranges::cbegin(v);
		VERIFY((it == ranges::cend(v)) == false);
		VERIFY((it != ranges::cend(v)) == true);
		VERIFY((ranges::cend(v) == it) == false);
		VERIFY((ranges::cend(v) != it) == true);
	}

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test06()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {0,1,2,3,4,5,6,7,8,9};
	test_random_access_range<int> rx(x);
	auto v = rx | views::transform(bksge::negate<>{}) | views::take(3) | views::take(5);
	using R = decltype(v);
	static_assert( ranges::is_view<R>::value, "");
	static_assert( ranges::is_sized_range<R>::value, "");
	static_assert( ranges::is_common_range<R>::value, "");
	static_assert( ranges::is_input_range<R>::value, "");
	static_assert( ranges::is_forward_range<R>::value, "");
	static_assert( ranges::is_bidirectional_range<R>::value, "");
	static_assert( ranges::is_random_access_range<R>::value, "");

	int y[] = {0,-1,-2};
	VERIFY(ranges::equal(v, y));

	{
		auto it = ranges::begin(v);
		VERIFY((it == ranges::end(v)) == false);
		VERIFY((it != ranges::end(v)) == true);
		VERIFY((ranges::end(v) == it) == false);
		VERIFY((ranges::end(v) != it) == true);
	}
	{
		auto it = ranges::cbegin(v);
		VERIFY((it == ranges::cend(v)) == false);
		VERIFY((it != ranges::cend(v)) == true);
		VERIFY((ranges::cend(v) == it) == false);
		VERIFY((ranges::cend(v) != it) == true);
	}

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test07()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {1, 2, 3, 4, 5};
	test_forward_range<int> rx(x);
	auto v = rx | views::transform(bksge::negate<>{}) | views::take(4);

	// Verify that Sentinel<false> is implicitly convertible to Sentinel<true>.
	static_assert(!ranges::is_common_range<decltype(v)>::value, "");
	static_assert(!bksge::is_same_as<
		decltype(ranges::end(v)),
		decltype(ranges::cend(v))>::value, "");
	auto b = ranges::cend(v);
	b = ranges::end(v);

	int y[] = {-1,-2,-3,-4};
	VERIFY(ranges::equal(v, y));

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, TakeViewTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test06());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test07());
}

}	// namespace take_view_test

}	// namespace bksge_ranges_test
