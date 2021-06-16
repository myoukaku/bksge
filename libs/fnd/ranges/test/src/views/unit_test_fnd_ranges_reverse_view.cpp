/**
 *	@file	unit_test_fnd_ranges_reverse_view.cpp
 *
 *	@brief	ranges::reverse_view のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/views/reverse_view.hpp>
#include <bksge/fnd/ranges/views/filter_view.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/concepts/common_range.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/concepts/bidirectional_range.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/ranges/cbegin.hpp>
#include <bksge/fnd/ranges/cend.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/utility/as_const.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_ranges_test
{

namespace reverse_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {1, 2, 3, 4, 5};
	auto v = x | views::reverse;
	using V = decltype(v);
	static_assert(ranges::is_view<V>::value, "");
	static_assert(ranges::is_sized_range<V>::value, "");
	static_assert(ranges::is_common_range<V>::value, "");
	static_assert(ranges::is_random_access_range<V>::value, "");

	VERIFY(v.size() == 5);
	VERIFY(ranges::size(bksge::as_const(v)) == 5);

	int const y[] = {5, 4, 3, 2, 1};
	VERIFY(ranges::equal(v, y));

	VERIFY(ranges::equal(v | views::reverse, x));

	VERIFY(ranges::begin(v)  != ranges::end(v));
	VERIFY(ranges::cbegin(v) != ranges::cend(v));

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {1, 2, 3, 4, 5};
	test_bidirectional_range<int> rx(x);
	auto v = views::reverse(rx);
	using V = decltype(v);
	static_assert( ranges::is_view<V>::value, "");
	static_assert(!ranges::is_sized_range<V>::value, "");
	static_assert( ranges::is_common_range<V>::value, "");
	static_assert(!ranges::is_random_access_range<V>::value, "");
	static_assert( ranges::is_bidirectional_range<V>::value, "");

	int const y[] = {5, 4, 3, 2, 1};
	VERIFY(ranges::equal(v, y));

	VERIFY(ranges::equal(v | views::reverse, rx));

	VERIFY(ranges::equal(v.base(), rx));
	VERIFY(ranges::equal(views::reverse(rx).base(), rx));

	return true;
}

struct IsOdd
{
	constexpr bool operator()(int i) const { return i % 2 == 1; }
};

inline BKSGE_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {3,1,4,1,5,9,2,6,5};
	auto v1 = x | views::filter(IsOdd{}) | views::reverse;
	auto v2 = x | views::reverse | views::filter(IsOdd{});

	using V = decltype(v1);
	static_assert( ranges::is_view<V>::value, "");
	static_assert(!ranges::is_sized_range<V>::value, "");
	static_assert( ranges::is_common_range<V>::value, "");
	static_assert(!ranges::is_random_access_range<V>::value, "");
	static_assert( ranges::is_bidirectional_range<V>::value, "");

	int const y[] = {5,9,5,1,1,3};
	VERIFY(ranges::equal(v1, y));
	VERIFY(ranges::equal(v2, y));

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test04()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int const x[] = {1, 2, 3, 4, 5};
	int const y[] = {5, 4, 3, 2, 1};
	VERIFY(ranges::equal(x | views::reverse | (views::reverse | views::reverse), y));

	return true;
}

template<typename T>
struct test_wrapper : bidirectional_iterator_wrapper<T>
{
	static int increment_count;

	using base_t = bidirectional_iterator_wrapper<T>;
	using base_t::bidirectional_iterator_wrapper;

	test_wrapper() : base_t()
	{}

	test_wrapper(T* p) : base_t{p}
	{}

	test_wrapper operator++(int)
	{
		auto tmp = *this;
		++*this;
		return tmp;
	}

	test_wrapper& operator++()
	{
		++increment_count;
		base_t::operator++();
		return *this;
	}

	test_wrapper operator--(int)
	{
		auto tmp = *this;
		--*this;
		return tmp;
	}

	test_wrapper& operator--()
	{
		base_t::operator--();
		return *this;
	}
};

template<typename T>
int test_wrapper<T>::increment_count = 0;

inline bool test05()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {1, 2, 3, 4, 5};
	int const y[] = {5, 4, 3, 2, 1};
	test_range<int, test_wrapper> rx(x);
	auto v = rx | views::reverse;
	VERIFY(test_wrapper<int>::increment_count == 0);
	VERIFY(ranges::equal(v, y));
	VERIFY(test_wrapper<int>::increment_count == 5);
	VERIFY(ranges::equal(v, y));
	VERIFY(test_wrapper<int>::increment_count == 5);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test06()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {1, 2, 3, 4, 5};
	using Subrange = ranges::subrange<
		bksge::reverse_iterator<int*>,
		bksge::reverse_iterator<int*>,
		ranges::subrange_kind::sized
	>;
	Subrange sr(
		bksge::make_reverse_iterator(ranges::end(x)),
		bksge::make_reverse_iterator(ranges::begin(x)));

	int const y[] = {5, 4, 3, 2, 1};
	VERIFY(ranges::equal(sr, y));

	auto v = sr | views::reverse;
	using V = decltype(v);
	static_assert(ranges::is_view<V>::value, "");
	static_assert(ranges::is_sized_range<V>::value, "");
	static_assert(ranges::is_common_range<V>::value, "");
	static_assert(ranges::is_random_access_range<V>::value, "");

	VERIFY(ranges::equal(v, x));

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test07()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {1, 2, 3, 4, 5};
	test_bidirectional_range<int> rx(x);
	using Subrange = ranges::subrange<
		bksge::reverse_iterator<bidirectional_iterator_wrapper<int>>,
		bksge::reverse_iterator<bidirectional_iterator_wrapper<int>>,
		ranges::subrange_kind::unsized
	>;
	Subrange sr(
		bksge::make_reverse_iterator(ranges::next(ranges::begin(rx), 5)),
		bksge::make_reverse_iterator(ranges::begin(rx)));

	int const y[] = {5, 4, 3, 2, 1};
	VERIFY(ranges::equal(sr, y));

	auto v = sr | views::reverse;
	using V = decltype(v);
	static_assert( ranges::is_view<V>::value, "");
	static_assert(!ranges::is_sized_range<V>::value, "");
	static_assert( ranges::is_common_range<V>::value, "");
	static_assert(!ranges::is_random_access_range<V>::value, "");
	static_assert( ranges::is_bidirectional_range<V>::value, "");

	VERIFY(ranges::equal(v, rx));

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ReverseViewTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	EXPECT_TRUE(test05());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test06());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test07());
}

}	// namespace reverse_view_test

}	// namespace bksge_ranges_test
