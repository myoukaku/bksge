/**
 *	@file	unit_test_fnd_algorithm_ranges_is_sorted_until.cpp
 *
 *	@brief	ranges::is_sorted_until のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/is_sorted_until.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include <forward_list>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_is_sorted_until_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int a[] = {1,2,3,4,5};
		auto it = ranges::is_sorted_until(a);
		VERIFY(it == a+5);
	}
	{
		int a[] = {1,2,3,4,5};
		auto it = ranges::is_sorted_until(a, ranges::greater{});
		VERIFY(it == a+1);
	}
	{
		int a[] = {1,2,5,3,4};
		auto it = ranges::is_sorted_until(a);
		VERIFY(it == a+3);
	}
	{
		int a[] = {9,9,8,8,8,5,3,1,2};
		auto it = ranges::is_sorted_until(a, ranges::greater{});
		VERIFY(it == a+8);
	}
	{
		int a[] = {1,2,2,3,3,3,4,1};
		test_range<int, forward_iterator_wrapper> r(a);
		auto it = ranges::is_sorted_until(r);
		VERIFY(it == ranges::next(r.begin(), 7));
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
	{
		X a[] = { {1},{2},{3},{0},{4},{5} };
		auto it = ranges::is_sorted_until(a, {}, &X::i);
		VERIFY(it == a+3);
	}
	{
		std::forward_list<int> const a = {3,3,4,4,5,5};
		auto it = ranges::is_sorted_until(a, [] (int x, int y) { return x < y; });
		EXPECT_TRUE(it == a.end());
	}
	{
		std::forward_list<int> const a = {3,3,4,4,5,5};
		auto it = ranges::is_sorted_until(a, [] (int x, int y) { return x > y; });
		EXPECT_TRUE(it == ranges::next(a.begin(), 2));
	}
	{
		std::forward_list<int> const a = {};
		auto it = ranges::is_sorted_until(a);
		EXPECT_TRUE(it == a.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesIsSortedUntilTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_is_sorted_until_test

}	// namespace bksge_algorithm_test
