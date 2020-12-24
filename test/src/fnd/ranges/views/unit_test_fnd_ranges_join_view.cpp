/**
 *	@file	unit_test_fnd_ranges_join_view.cpp
 *
 *	@brief	ranges::join_view のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/views/join_view.hpp>
#include <bksge/fnd/ranges/views/iota_view.hpp>
#include <bksge/fnd/ranges/views/transform_view.hpp>
#include <bksge/fnd/ranges/views/filter_view.hpp>
#include <bksge/fnd/ranges/views/subrange.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/common_range.hpp>
#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/concepts/bidirectional_range.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/cbegin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/ranges/cend.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/iterator/counted_iterator.hpp>
#include <bksge/fnd/iterator/default_sentinel.hpp>
#include <bksge/fnd/string/string.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_ranges_test
{

namespace join_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[3][4] =
	{
		{ 1, 2, 3, 4},
		{11,12,13,14},
		{21,22,23,24},
	};
	auto v = x | views::join;

	using R = decltype(v);
	static_assert( ranges::is_view<R>::value, "");
	static_assert(!ranges::is_view<R const>::value, "");
	static_assert( ranges::is_common_range<R>::value, "");
	static_assert( ranges::is_common_range<R const>::value, "");
	static_assert(!ranges::is_sized_range<R>::value, "");
	static_assert(!ranges::is_sized_range<R const>::value, "");
	static_assert( ranges::is_bidirectional_range<R>::value, "");
	static_assert( ranges::is_bidirectional_range<R const>::value, "");
	static_assert(!ranges::is_random_access_range<R>::value, "");
	static_assert(!ranges::is_random_access_range<R const>::value, "");

	int y[] = {1,2,3,4,11,12,13,14,21,22,23,24};
	VERIFY(ranges::equal(v, y));

	auto it = ranges::cbegin(v);
	VERIFY(*(it++) == 1);
	VERIFY(*it     == 2);
	VERIFY(*(++it) == 3);
	VERIFY(*(it--) == 3);
	VERIFY(*it     == 2);
	VERIFY(*(--it) == 1);

 	return true;
}

struct X
{
	constexpr auto operator()(int i) const
	->decltype(bksge::ranges::views::iota(0, i))
	{
		return bksge::ranges::views::iota(0, i);
	}
};

BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	auto v = (views::iota(0, 5)
		| views::transform(X{})
		| views::join);

	using R = decltype(v);
	static_assert( ranges::is_view<R>::value, "");
	static_assert(!ranges::is_view<R const>::value, "");
	static_assert(!ranges::is_common_range<R>::value, "");
	static_assert(!ranges::is_common_range<R const>::value, "");
	static_assert(!ranges::is_sized_range<R>::value, "");
	static_assert(!ranges::is_sized_range<R const>::value, "");
	static_assert( ranges::is_input_range<R>::value, "");
	static_assert(!ranges::is_input_range<R const>::value, "");
	static_assert(!ranges::is_forward_range<R>::value, "");
	static_assert(!ranges::is_forward_range<R const>::value, "");

	int y[] = {0,0,1,0,1,2,0,1,2,3};
	VERIFY(ranges::equal(v, y));

	auto it = ranges::begin(v);
	VERIFY((it == ranges::end(v)) == false);
	VERIFY((it != ranges::end(v)) == true);
	VERIFY((ranges::end(v) == it) == false);
	VERIFY((ranges::end(v) != it) == true);

	return true;
}

struct F
{
	template <typename Range>
	constexpr bool operator()(Range&&) const { return true; }
};

BKSGE_CXX14_CONSTEXPR bool test03()
{
#if !defined(BKSGE_MSVC)
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	auto v = views::iota(0, 5)
		| views::transform(X{})
		| views::filter(F{})
		| views::join;

	using R = decltype(v);
	static_assert( ranges::is_view<R>::value, "");
	static_assert(!ranges::is_view<R const>::value, "");
	static_assert(!ranges::is_common_range<R>::value, "");
	static_assert(!ranges::is_common_range<R const>::value, "");
	static_assert(!ranges::is_sized_range<R>::value, "");
	static_assert(!ranges::is_sized_range<R const>::value, "");
	static_assert( ranges::is_input_range<R>::value, "");
	static_assert(!ranges::is_input_range<R const>::value, "");
	static_assert(!ranges::is_forward_range<R>::value, "");
	static_assert(!ranges::is_forward_range<R const>::value, "");

	int y[] = {0,0,1,0,1,2,0,1,2,3};
	VERIFY(ranges::equal(v, y));
#endif
 	return true;
}

inline bool test04()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	std::vector<bksge::string> x = {""};
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
	auto i = bksge::counted_iterator(x.begin(), 1);
	auto r = ranges::subrange{i, bksge::default_sentinel};
#else
	using Iterator = std::vector<bksge::string>::iterator;
	using CountedIterator = bksge::counted_iterator<Iterator>;
	using Subrange = ranges::subrange<CountedIterator, bksge::default_sentinel_t>;
	auto i = CountedIterator(x.begin(), 1);
	auto r = Subrange{i, bksge::default_sentinel};
#endif
	auto v = r | views::transform(bksge::identity{}) | views::join;

	// Verify that _Iterator<false> is implicitly convertible to _Iterator<true>.
	static_assert(!bksge::is_same_as<decltype(ranges::begin(v)), decltype(ranges::cbegin(v))>::value, "");
	auto a = ranges::cbegin(v);
	a = ranges::begin(v);

	// Verify that _Sentinel<false> is implicitly convertible to _Sentinel<true>.
	static_assert(!ranges::is_common_range<decltype(v)>::value, "");
	static_assert(!bksge::is_same_as<decltype(ranges::end(v)), decltype(ranges::cend(v))>::value, "");
	auto b = ranges::cend(v);
	b = ranges::end(v);

	return true;
}

struct Y
{
	int i;
};

BKSGE_CXX14_CONSTEXPR bool test05()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	Y x[2][3] =
	{
		{{1},{2},{3}},
		{{4},{5},{6}},
	};
	auto v = x | views::join;

	using R = decltype(v);
	static_assert( ranges::is_view<R>::value, "");
	static_assert(!ranges::is_view<R const>::value, "");
	static_assert( ranges::is_common_range<R>::value, "");
	static_assert( ranges::is_common_range<R const>::value, "");
	static_assert(!ranges::is_sized_range<R>::value, "");
	static_assert(!ranges::is_sized_range<R const>::value, "");
	static_assert( ranges::is_bidirectional_range<R>::value, "");
	static_assert( ranges::is_bidirectional_range<R const>::value, "");
	static_assert(!ranges::is_random_access_range<R>::value, "");
	static_assert(!ranges::is_random_access_range<R const>::value, "");

	auto it = ranges::cbegin(v);
	VERIFY((it == ranges::cend(v)) == false);
	VERIFY((it != ranges::cend(v)) == true);

	VERIFY(it->i == 1);
	++it;
	VERIFY(it->i == 2);
	it++;
	VERIFY(it->i == 3);
	it++;
	VERIFY(it->i == 4);
	++it;
	VERIFY(it->i == 5);
	it++;
	VERIFY(it->i == 6);
	it++;
	VERIFY((it == ranges::cend(v)) == true);
	VERIFY((it != ranges::cend(v)) == false);

	return true;
}

inline bool test06()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	std::vector<std::vector<std::vector<int>>> nested_vectors =
	{
		{{1, 2, 3}, {4, 5}, {6}},
		{{7}, {8, 9}, {10, 11, 12}},
		{{13}}
	};
	auto joined = nested_vectors | views::join | views::join;

	using V = decltype(joined);
	static_assert(bksge::is_same_as<ranges::range_value_t<V>, int>::value, "");

	int y[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
	VERIFY(ranges::equal(joined, y));

	auto it = ranges::cend(joined);
	VERIFY(*(--it) == 13);
	VERIFY(*(--it) == 12);
	VERIFY(*(--it) == 11);
	VERIFY(*(--it) == 10);
	VERIFY(*(--it) ==  9);
	VERIFY(*(--it) ==  8);
	VERIFY(*(--it) ==  7);
	VERIFY(*(--it) ==  6);
	VERIFY(*(--it) ==  5);
	VERIFY(*(--it) ==  4);
	VERIFY(*(--it) ==  3);
	VERIFY(*(--it) ==  2);
	VERIFY(*(--it) ==  1);
	VERIFY(it == ranges::cbegin(joined));

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinViewTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	EXPECT_TRUE(test04());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
	EXPECT_TRUE(test06());
}

}	// namespace join_view_test

}	// namespace bksge_ranges_test
