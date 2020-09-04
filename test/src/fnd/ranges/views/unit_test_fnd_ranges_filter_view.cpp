/**
 *	@file	unit_test_fnd_ranges_filter_view.cpp
 *
 *	@brief	ranges::filter_view のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/views/filter_view.hpp>
#include <bksge/fnd/ranges/views/all.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/concepts/common_range.hpp>
#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/concepts/bidirectional_range.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_ranges_test
{

namespace filter_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct IsEven
{
	constexpr bool operator()(int i) const { return i % 2 == 0; }
};

struct IsOdd
{
	constexpr bool operator()(int i) const { return i % 2 == 1; }
};

template <int N>
struct Less
{
	constexpr bool operator()(int i) const { return i < N; }
};

template <int N>
struct NotEqual
{
	constexpr bool operator()(int i) const { return i != N; }
};

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	{
		int x[] = { 1,2,3,4,5,6,7,8,9 };
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
		auto v = ranges::filter_view(x, IsEven{});
#else
		auto v = ranges::filter_view<views::all_t<int(&)[9]>, IsEven>(x, IsEven{});
#endif
		using R = decltype(v);
		static_assert( bksge::is_same_as<int&, decltype(*v.begin())>::value, "");
		static_assert( ranges::is_view<R>::value, "");
		static_assert( ranges::is_input_range<R>::value, "");
		static_assert( ranges::is_common_range<R>::value, "");
		static_assert(!ranges::is_sized_range<R>::value, "");
		static_assert( ranges::is_bidirectional_range<R>::value, "");
		static_assert(!ranges::is_random_access_range<R>::value, "");
		static_assert( ranges::is_range<views::all_t<R>>::value, "");
		VERIFY(v.pred()(3) == false);
		VERIFY(v.pred()(4) == true);

		int const y[] = { 2,4,6,8 };
		VERIFY(ranges::equal(v, y));

		VERIFY(v.begin().base() == x+1);
		auto it = v.begin();
		VERIFY((it == v.end()) == false);
		VERIFY((it != v.end()) == true);
		VERIFY(*it == 2);
		VERIFY(it.base() == x+1);
		VERIFY(*++it == 4);
		VERIFY(*it++ == 4);
		VERIFY(*it == 6);
		VERIFY(*--it == 4);
		VERIFY(*it-- == 4);
		VERIFY(*it == 2);
	}
	{
		int x[] = { 1,2,3,4,5,6,7,8,9 };
		test_input_range<int> rx(x);
		auto v = rx | views::filter(IsEven{});
		using R = decltype(v);
		static_assert( bksge::is_same_as<int&, decltype(*v.begin())>::value, "");
		static_assert( ranges::is_view<R>::value, "");
		static_assert( ranges::is_input_range<R>::value, "");
		static_assert(!ranges::is_common_range<R>::value, "");
		static_assert(!ranges::is_sized_range<R>::value, "");
		static_assert(!ranges::is_bidirectional_range<R>::value, "");
		static_assert(!ranges::is_random_access_range<R>::value, "");
		static_assert( ranges::is_range<views::all_t<R>>::value, "");
		VERIFY(v.pred()(3) == false);
		VERIFY(v.pred()(4) == true);

		int const y[] = { 2,4,6,8 };
		VERIFY(ranges::equal(v, y));

		auto it = v.begin();
		VERIFY((it == v.end()) == false);
		VERIFY((it != v.end()) == true);
		VERIFY((v.end() == it) == false);
		VERIFY((v.end() != it) == true);
		VERIFY(*it == 2);
		VERIFY(*++it == 4);
		it++;
		VERIFY(*it == 6);
		VERIFY((v.end().base() == it.base()) == false);
		{
			auto z = v.base();
			VERIFY(ranges::equal(z, rx));
		}
		{
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
			auto z = ranges::filter_view(rx, IsEven{}).base();
#else
			auto z = ranges::filter_view<views::all_t<test_input_range<int>&>, IsEven>(rx, IsEven{}).base();
#endif
			VERIFY(ranges::equal(z, rx));
		}
	}
	{
		int const x[] = { 1,2,3,4,5,6,7,8,9 };
		test_random_access_range<int const> rx(x);
		auto v = views::filter(rx, IsOdd{});
		using R = decltype(v);
		static_assert( bksge::is_same_as<int const&, decltype(*v.begin())>::value, "");
		static_assert( ranges::is_view<R>::value, "");
		static_assert( ranges::is_input_range<R>::value, "");
		static_assert(!ranges::is_common_range<R>::value, "");
		static_assert(!ranges::is_sized_range<R>::value, "");
		static_assert( ranges::is_bidirectional_range<R>::value, "");
		static_assert(!ranges::is_random_access_range<R>::value, "");
		static_assert( ranges::is_range<views::all_t<R>>::value, "");

		int const y[] = { 1,3,5,7,9 };
		VERIFY(ranges::equal(v, y));
	}
	{
		int const x[] = { 1,2,3,4,5,6,7,8,9 };
		test_random_access_range<int const> rx(x);
		auto v = views::filter(Less<5>{})(rx);
		using R = decltype(v);
		static_assert( bksge::is_same_as<int const&, decltype(*v.begin())>::value, "");
		static_assert( ranges::is_view<R>::value, "");
		static_assert( ranges::is_input_range<R>::value, "");
		static_assert(!ranges::is_common_range<R>::value, "");
		static_assert(!ranges::is_sized_range<R>::value, "");
		static_assert( ranges::is_bidirectional_range<R>::value, "");
		static_assert(!ranges::is_random_access_range<R>::value, "");
		static_assert( ranges::is_range<views::all_t<R>>::value, "");

		int const y[] = { 1,2,3,4 };
		VERIFY(ranges::equal(v, y));
	}
	{
		int const x[] = { 1,2,3,4,5,6,7,8,9 };
		auto v = x | views::filter(IsOdd{}) | views::filter(Less<5>{});
		using R = decltype(v);
		static_assert( bksge::is_same_as<int const&, decltype(*v.begin())>::value, "");
		static_assert( ranges::is_view<R>::value, "");
		static_assert( ranges::is_input_range<R>::value, "");
		static_assert( ranges::is_common_range<R>::value, "");
		static_assert(!ranges::is_sized_range<R>::value, "");
		static_assert( ranges::is_bidirectional_range<R>::value, "");
		static_assert(!ranges::is_random_access_range<R>::value, "");
		static_assert( ranges::is_range<views::all_t<R>>::value, "");

		int const y[] = { 1,3 };
		VERIFY(ranges::equal(v, y));
	}
	{
		int x[] = { 1,2,3,4,5,6,7,8,9 };
		auto v = x | views::all |
			views::filter(NotEqual<0>{}) |
			(views::filter(NotEqual<2>{}) | views::filter(NotEqual<3>{})) |
			views::filter(NotEqual<5>{}) |
			(views::filter(NotEqual<8>{}) | views::filter(NotEqual<9>{}) | views::filter(NotEqual<10>{}));
		using R = decltype(v);
		static_assert( bksge::is_same_as<int&, decltype(*v.begin())>::value, "");
		static_assert( ranges::is_view<R>::value, "");
		static_assert( ranges::is_input_range<R>::value, "");
		static_assert( ranges::is_common_range<R>::value, "");
		static_assert(!ranges::is_sized_range<R>::value, "");
		static_assert( ranges::is_bidirectional_range<R>::value, "");
		static_assert(!ranges::is_random_access_range<R>::value, "");
		static_assert( ranges::is_range<views::all_t<R>>::value, "");

		int const y[] = { 1,4,6,7 };
		VERIFY(ranges::equal(v, y));
	}

	return true;
}

struct X
{
	int i;
};

inline bool test02()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;
	{
		X x[] = { {1},{2},{3},{4} };
		auto v = x | views::filter([](X a) { return a.i % 2 == 0; });
		auto it = v.begin();
		VERIFY(it->i == 2);
		it++;
		VERIFY(it->i == 4);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, FilterViewTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace filter_view_test

}	// namespace bksge_ranges_test
