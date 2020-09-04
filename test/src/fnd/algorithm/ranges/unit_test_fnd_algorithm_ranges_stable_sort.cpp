/**
 *	@file	unit_test_fnd_algorithm_ranges_stable_sort.cpp
 *
 *	@brief	ranges::stable_sort のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/stable_sort.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_stable_sort_test
{

struct Foo
{
	int key;
	float value;
};

GTEST_TEST(AlgorithmTest, RangesStableSortTest)
{
	namespace ranges = bksge::ranges;
	{
		int x[] = {3,1,4,1,5,9,2};
		test_random_access_range<int> rx(x);
		auto ret = ranges::stable_sort(rx);
		EXPECT_TRUE(ret == rx.end());
		int y[] = {1,1,2,3,4,5,9};
		EXPECT_TRUE(ranges::equal(x, y));
	}
	{
		int x[] = {3,1,4,1,5,9,2};
		test_random_access_range<int> rx(x);
		auto ret = ranges::stable_sort(rx, ranges::greater{});
		EXPECT_TRUE(ret == rx.end());
		int y[] = {9,5,4,3,2,1,1};
		EXPECT_TRUE(ranges::equal(x, y));
	}
	{
		Foo x[] =
		{
			{ 3, 0.5f },
			{ 1, 1.5f },
			{ 4, 2.5f },
			{ 1, 3.5f },
			{ 5, 4.5f },
			{ 9, 5.5f },
			{ 2, 6.5f },
			{ 6, 7.5f },
			{ 5, 8.5f },
			{ 3, 9.5f },
		};
		test_random_access_range<Foo> rx(x);
		auto ret = ranges::stable_sort(rx, {}, &Foo::key);
		EXPECT_TRUE(ret == rx.end());
		EXPECT_EQ(1.5, x[0].value);
		EXPECT_EQ(3.5, x[1].value);
		EXPECT_EQ(6.5, x[2].value);
		EXPECT_EQ(0.5, x[3].value);
		EXPECT_EQ(9.5, x[4].value);
		EXPECT_EQ(2.5, x[5].value);
		EXPECT_EQ(4.5, x[6].value);
		EXPECT_EQ(8.5, x[7].value);
		EXPECT_EQ(7.5, x[8].value);
		EXPECT_EQ(5.5, x[9].value);
	}
}

}	// namespace ranges_stable_sort_test

}	// namespace bksge_algorithm_test
