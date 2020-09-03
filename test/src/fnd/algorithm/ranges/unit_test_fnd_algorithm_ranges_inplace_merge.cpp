/**
 *	@file	unit_test_fnd_algorithm_ranges_inplace_merge.cpp
 *
 *	@brief	ranges::inplace_merge のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/inplace_merge.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/functional/ranges/greater.hpp>
#include <bksge/fnd/functional/negate.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_inplace_merge_test
{

struct X
{
	int i;
	X(int x) : i(x) {}
};

GTEST_TEST(AlgorithmTest, RangesInplaceMergeTest)
{
	namespace ranges = bksge::ranges;
	{
		int x[] = { 1,4,5,  2,3,6 };
		test_range<int, bidirectional_iterator_wrapper> rx(x);
		auto ret = ranges::inplace_merge(rx, ranges::next(rx.begin(), 3));
		EXPECT_TRUE(ret == rx.end());
		int const y[] = {1,2,3,4,5,6};
		EXPECT_TRUE(ranges::equal(x, y));
	}
	{
		int x[] = { 7,5,2,1,  6,5,3,3,2,2 };
		test_range<int, bidirectional_iterator_wrapper> rx(x);
		auto ret = ranges::inplace_merge(rx, ranges::next(rx.begin(), 4), ranges::greater{});
		EXPECT_TRUE(ret == rx.end());
		int const y[] = {7,6,5,5,3,3,2,2,2,1};
		EXPECT_TRUE(ranges::equal(x, y));
	}
	{
		int x[] = { 1,2,4,5,6,  3 };
		test_range<int, bidirectional_iterator_wrapper> rx(x);
		auto ret = ranges::inplace_merge(rx, ranges::next(rx.begin(), 5), ranges::greater{}, bksge::negate<>{});
		EXPECT_TRUE(ret == rx.end());
		int const y[] = {1,2,3,4,5,6};
		EXPECT_TRUE(ranges::equal(x, y));
	}
	{
		X x[] = { {1},{2},{6},  {1},{3},{5} };
		test_range<X, bidirectional_iterator_wrapper> rx(x);
		auto ret = ranges::inplace_merge(rx, ranges::next(rx.begin(), 3), {}, &X::i);
		EXPECT_TRUE(ret == rx.end());
		int const y[] = {1,1,2,3,5,6};
		EXPECT_TRUE(ranges::equal(x, y, {}, &X::i));
	}
}

}	// namespace ranges_inplace_merge_test

}	// namespace bksge_algorithm_test
