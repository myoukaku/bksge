﻿/**
 *	@file	unit_test_fnd_algorithm_sort.cpp
 *
 *	@brief	sort のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/functional/greater.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace sort_test
{

GTEST_TEST(AlgorithmTest, SortTest)
{
	{
		int a[] { 3, 1, 4 };
		bksge::sort(bksge::begin(a), bksge::end(a));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(4, a[2]);
	}
	{
		int a[] { 3, 1, 4 };
		bksge::sort(bksge::begin(a), bksge::end(a), bksge::greater<>());
		EXPECT_EQ(4, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(1, a[2]);
	}
	{
		bksge::array<int, 6> a {{ 3, 1, 4, 1, 5, 9 }};
		bksge::sort(bksge::begin(a), bksge::end(a));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(4, a[3]);
		EXPECT_EQ(5, a[4]);
		EXPECT_EQ(9, a[5]);
	}
	{
		bksge::array<int, 6> a {{ 3, 1, 4, 1, 5, 9 }};
		bksge::sort(bksge::begin(a), bksge::end(a), bksge::greater<>());
		EXPECT_EQ(9, a[0]);
		EXPECT_EQ(5, a[1]);
		EXPECT_EQ(4, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(1, a[4]);
		EXPECT_EQ(1, a[5]);
	}
	{
		bksge::vector<int> a { 5, 4, 1, 1, 3 };
		bksge::sort(bksge::begin(a), bksge::end(a));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(4, a[3]);
		EXPECT_EQ(5, a[4]);
	}
	{
		bksge::vector<int> a { 5, 4, 1, 1, 3 };
		bksge::sort(bksge::begin(a), bksge::end(a), bksge::greater<>());
		EXPECT_EQ(5, a[0]);
		EXPECT_EQ(4, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(1, a[4]);
	}
	{
		bksge::vector<int> a;
		bksge::sort(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE(a.empty());
	}
}

}	// namespace sort_test

}	// namespace bksge_algorithm_test
