/**
 *	@file	unit_test_fnd_algorithm_ranges_stable_partition.cpp
 *
 *	@brief	ranges::stable_partition のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/stable_partition.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/list.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_stable_partition_test
{

BKSGE_CONSTEXPR bool is_even(int x)
{
	return (x % 2) == 0;
}

GTEST_TEST(AlgorithmTest, RangesStablePartitionTest)
{
	namespace ranges = bksge::ranges;
	{
		int x[] = {1,2,3,4,5};
		test_bidirectional_range<int> rx(x);
		auto ret = ranges::stable_partition(rx, is_even);
		EXPECT_TRUE(ret.begin() == ranges::next(rx.begin(), 2));
		EXPECT_TRUE(ret.end()   == rx.end());
		int const y[] = {2,4,1,3,5};
		EXPECT_TRUE(ranges::equal(x, y));
	}
	{
		bksge::list<int> x = {3,1,4,1,5,9,2,6,5};
		auto ret = ranges::stable_partition(x, [](int x) { return x > 3;});
		EXPECT_TRUE(ret.begin() == ranges::next(x.begin(), 5));
		EXPECT_TRUE(ret.end()   == x.end());
		int const y[] = {4,5,9,6,5,3,1,1,2};
		EXPECT_TRUE(ranges::equal(x, y));
	}
}

}	// namespace ranges_stable_partition_test

}	// namespace bksge_algorithm_test
