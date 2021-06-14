/**
 *	@file	unit_test_fnd_algorithm_ranges_shuffle.cpp
 *
 *	@brief	ranges::shuffle のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/shuffle.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/algorithm/ranges/is_sorted.hpp>
#include <bksge/fnd/algorithm/ranges/is_permutation.hpp>
#include <bksge/fnd/random/engines/xorshift.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_shuffle_test
{

GTEST_TEST(AlgorithmTest, RangesShuffleTest)
{
	namespace ranges = bksge::ranges;
	{
		int x[] = {0,1,2,3,4,5,6,7,8,9};
		int y[] = {0,1,2,3,4,5,6,7,8,9};
		EXPECT_TRUE (ranges::is_sorted(x));
		auto g = bksge::xorshift32();
		test_random_access_range<int> rx(x);
		auto res = ranges::shuffle(rx, g);
		EXPECT_TRUE (res == rx.end());
		EXPECT_FALSE(ranges::is_sorted(x));
		EXPECT_FALSE(ranges::equal(x, y));
		EXPECT_TRUE (ranges::is_permutation(x, y));
	}
}

}	// namespace ranges_shuffle_test

}	// namespace bksge_algorithm_test
