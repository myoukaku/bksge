/**
 *	@file	unit_test_fnd_algorithm_partial_sort.cpp
 *
 *	@brief	partial_sort のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/partial_sort.hpp>
#include <bksge/fnd/functional/greater.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <gtest/gtest.h>
#include <array>
#include <bksge/fnd/vector.hpp>

namespace bksge_algorithm_test
{

namespace partial_sort_test
{

GTEST_TEST(AlgorithmTest, PartialSortTest)
{
	{
		int a[] { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		bksge::partial_sort(bksge::begin(a), bksge::next(bksge::begin(a), 1), bksge::end(a));
		EXPECT_EQ(1, a[0]);
	}
	{
		int a[] { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		bksge::partial_sort(bksge::begin(a), bksge::next(bksge::begin(a), 2), bksge::end(a), bksge::greater<>());
		EXPECT_EQ(9, a[0]);
		EXPECT_EQ(6, a[1]);
	}
	{
		int a[] { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };
		bksge::partial_sort(bksge::begin(a), bksge::next(bksge::begin(a), 5), bksge::end(a));
		EXPECT_EQ(0, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(4, a[4]);
	}
	{
		int a[] { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };
		bksge::partial_sort(bksge::begin(a), bksge::next(bksge::begin(a), 5), bksge::end(a), bksge::greater<>());
		EXPECT_EQ(9, a[0]);
		EXPECT_EQ(8, a[1]);
		EXPECT_EQ(7, a[2]);
		EXPECT_EQ(6, a[3]);
		EXPECT_EQ(5, a[4]);
	}
	{
		std::array<int, 11> a {{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 }};
		bksge::partial_sort(bksge::begin(a), bksge::next(bksge::begin(a), 3), bksge::end(a));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(2, a[2]);
	}
	{
		std::array<int, 11> a {{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 }};
		bksge::partial_sort(bksge::begin(a), bksge::next(bksge::begin(a), 4), bksge::end(a), bksge::greater<>());
		EXPECT_EQ(9, a[0]);
		EXPECT_EQ(6, a[1]);
		EXPECT_EQ(5, a[2]);
		EXPECT_EQ(5, a[3]);
	}
	{
		std::array<int, 10> a {{ 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 }};
		bksge::partial_sort(bksge::begin(a), bksge::next(bksge::begin(a), 10), bksge::end(a));
		EXPECT_EQ(0, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(4, a[4]);
		EXPECT_EQ(5, a[5]);
		EXPECT_EQ(6, a[6]);
		EXPECT_EQ(7, a[7]);
		EXPECT_EQ(8, a[8]);
		EXPECT_EQ(9, a[9]);
	}
	{
		std::array<int, 10> a {{ 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 }};
		bksge::partial_sort(bksge::begin(a), bksge::next(bksge::begin(a), 10), bksge::end(a), bksge::greater<>());
		EXPECT_EQ(9, a[0]);
		EXPECT_EQ(8, a[1]);
		EXPECT_EQ(7, a[2]);
		EXPECT_EQ(6, a[3]);
		EXPECT_EQ(5, a[4]);
		EXPECT_EQ(4, a[5]);
		EXPECT_EQ(3, a[6]);
		EXPECT_EQ(2, a[7]);
		EXPECT_EQ(1, a[8]);
		EXPECT_EQ(0, a[9]);
	}
	{
		bksge::vector<int> a { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		bksge::partial_sort(bksge::begin(a), bksge::next(bksge::begin(a), 5), bksge::end(a));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(3, a[4]);
	}
	{
		bksge::vector<int> a { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		bksge::partial_sort(bksge::begin(a), bksge::next(bksge::begin(a), 6), bksge::end(a), bksge::greater<>());
		EXPECT_EQ(9, a[0]);
		EXPECT_EQ(6, a[1]);
		EXPECT_EQ(5, a[2]);
		EXPECT_EQ(5, a[3]);
		EXPECT_EQ(5, a[4]);
		EXPECT_EQ(4, a[5]);
	}
	{
		bksge::vector<int> a { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };
		bksge::partial_sort(bksge::begin(a), bksge::next(bksge::begin(a), 1), bksge::end(a));
		EXPECT_EQ(0, a[0]);
	}
	{
		bksge::vector<int> a { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };
		bksge::partial_sort(bksge::begin(a), bksge::next(bksge::begin(a), 1), bksge::end(a), bksge::greater<>());
		EXPECT_EQ(9, a[0]);
	}
	{
		bksge::vector<int> a;
		bksge::partial_sort(bksge::begin(a), bksge::next(bksge::begin(a), 0), bksge::end(a));
		EXPECT_TRUE(a.empty());
	}
}

}	// namespace partial_sort_test

}	// namespace bksge_algorithm_test
