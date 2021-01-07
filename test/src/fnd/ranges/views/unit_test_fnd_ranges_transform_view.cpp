/**
 *	@file	unit_test_fnd_ranges_transform_view.cpp
 *
 *	@brief	ranges::transform_view のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/views/transform_view.hpp>
#include <bksge/fnd/ranges/views/all.hpp>
#include <bksge/fnd/ranges/views/filter_view.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/concepts/common_range.hpp>
#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/concepts/bidirectional_range.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/compare/is_eq.hpp>
#include <bksge/fnd/compare/is_neq.hpp>
#include <bksge/fnd/iterator/ranges/distance.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_ranges_test
{

namespace transform_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct Multiply
{
	int n;
	constexpr int operator()(int i) const { return i * n; }
};

struct Add
{
	int n;
	constexpr int operator()(int i) const { return i + n; }
};

struct IsEven
{
	constexpr bool operator()(int i) const { return i % 2 == 0; }
};

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;
	{
		int x[] = { 1,2,3,4,5 };
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
		auto v = ranges::transform_view(x, Multiply{2});
#else
		auto v = ranges::transform_view<views::all_t<int(&)[5]>, Multiply>(x, Multiply{2});
#endif
		using R = decltype(v);
		static_assert( bksge::is_same_as<int, decltype(*v.begin())>::value, "");
		static_assert( ranges::is_view<R>::value, "");
		static_assert( ranges::is_input_range<R>::value, "");
		static_assert( ranges::is_common_range<R>::value, "");
		static_assert( ranges::is_sized_range<R>::value, "");
		static_assert( ranges::is_bidirectional_range<R>::value, "");
		static_assert( ranges::is_random_access_range<R>::value, "");
		static_assert( ranges::is_range<views::all_t<R>>::value, "");

		VERIFY(v.size() == 5);

		int const y[] = { 2,4,6,8,10 };
		VERIFY(ranges::equal(v, y));

		VERIFY(v.begin().base() == x+0);
		auto it = v.begin();
		VERIFY(it.base() == x+0);
		VERIFY((it == v.end()) == false);
		VERIFY((it != v.end()) == true);
		VERIFY((it <  v.end()) == true);
		VERIFY((it <= v.end()) == true);
		VERIFY((it >  v.end()) == false);
		VERIFY((it >= v.end()) == false);
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		VERIFY(bksge::is_eq(it <=> v.begin()));
		VERIFY(bksge::is_neq(it <=> v.end()));
#endif
		VERIFY(*it == 2);
		VERIFY(it[1] == 4);
		VERIFY(*++it == 4);
		VERIFY(*it++ == 4);
		VERIFY(*it == 6);
		VERIFY(*--it == 4);
		VERIFY(*it-- == 4);
		VERIFY(*it == 2);
		VERIFY(*(it+1) == 4);
		VERIFY(*(it+=3) == 8);
		VERIFY(*(it-1) == 6);
		VERIFY(*(it-=2) == 4);
		VERIFY(*(1+it) == 6);
	}
	{
		int x[] = { 1,2,3,4,5 };
#if 0//defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
		VERIFY(ranges::transform_view(x, Multiply{3}).base().begin(), x+5);
		auto const v = ranges::transform_view(x, Multiply{3});
#else
		VERIFY(ranges::transform_view<views::all_t<int(&)[5]>, Multiply>(x, Multiply{3}).base().begin(), x+5);
		auto const v = ranges::transform_view<views::all_t<int(&)[5]>, Multiply>(x, Multiply{3});
#endif
		VERIFY(v.size() == 5);

		int const y[] = { 3,6,9,12,15 };
		VERIFY(ranges::equal(v, y));
	}
	{
		int const x[] = { 1,2,3,4,5 };
		test_input_range<int const> rx(x);
		auto v = rx | views::transform(Add{10});
		using R = decltype(v);
		static_assert( bksge::is_same_as<int, decltype(*v.begin())>::value, "");
		static_assert( ranges::is_view<R>::value, "");
		static_assert( ranges::is_input_range<R>::value, "");
		static_assert(!ranges::is_common_range<R>::value, "");
		static_assert(!ranges::is_sized_range<R>::value, "");
		static_assert(!ranges::is_bidirectional_range<R>::value, "");
		static_assert(!ranges::is_random_access_range<R>::value, "");
		static_assert( ranges::is_range<views::all_t<R>>::value, "");

		int const y[] = { 11,12,13,14,15 };
		VERIFY(ranges::equal(v, y));

		auto it = v.begin();
		VERIFY((it == v.end()) == false);
		VERIFY((it != v.end()) == true);
		VERIFY((v.end() == it) == false);
		VERIFY((v.end() != it) == true);
		VERIFY((it.base() == v.end().base()) == false);
		VERIFY((it.base() != v.end().base()) == true);
		VERIFY(*it == 11);
		VERIFY(*++it == 12);
		it++;
		VERIFY(*it == 13);
	}
	{
		int x[] = { 1,2,3,4,5 };
		test_random_access_range<int> rx(x);
		auto const v = rx | views::transform(Add{5});
		VERIFY(v.base().begin() == rx.begin());
		VERIFY(v.size() == 5);

		int const y[] = { 6,7,8,9,10 };
		VERIFY(ranges::equal(v, y));
	}
	{
		int x[] = { 1,2,3,4,5 };
		test_random_access_range<int> rx(x);
		auto v1 = rx | views::transform(Add{5}) | views::transform(Multiply{2});
		auto v2 = rx | (views::transform(Add{5}) | views::transform(Multiply{2}));
		auto v3 = rx | views::transform(Multiply{2}) | views::transform(Add{5});
		auto v4 = rx | (views::transform(Multiply{2}) | views::transform(Add{5}));

		int const y1[] = { 12,14,16,18,20 };
		int const y2[] = {  7, 9,11,13,15 };
		VERIFY(ranges::equal(v1, y1));
		VERIFY(ranges::equal(v2, y1));
		VERIFY(ranges::equal(v3, y2));
		VERIFY(ranges::equal(v4, y2));
	}
	return true;
}

struct X
{
	int i, j;
};

inline bool test02()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;
	{
		X x[] = { {1,2},{3,4},{5,6},{7,8},{9,10} };
		test_random_access_range<X> rx(x);
		auto v = rx | views::transform(&X::i);
		VERIFY(ranges::size(v) == 5);
		VERIFY(ranges::distance(v.begin(), v.end()) == 5);
		int const y[] = { 1,3,5,7,9 };
		VERIFY(ranges::equal(v, y));
	}
	{
		X x[] = { {1,2},{3,4},{5,6},{7,8},{9,10} };
		test_random_access_range<X> rx(x);
		auto v = rx | views::transform(&X::i) | views::transform(Multiply{3});
		VERIFY(ranges::size(v) == 5);
		VERIFY(ranges::distance(v.begin(), v.end()) == 5);
		VERIFY(v.begin() - v.end() == -5);
		int const y[] = { 3,9,15,21,27 };
		VERIFY(ranges::equal(v, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, TransformViewTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace transform_view_test

}	// namespace bksge_ranges_test
