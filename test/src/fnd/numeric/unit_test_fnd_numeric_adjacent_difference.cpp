﻿/**
 *	@file	unit_test_fnd_numeric_adjacent_difference.cpp
 *
 *	@brief	adjacent_difference のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/numeric/adjacent_difference.hpp>
#include <bksge/fnd/functional/plus.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <array>
#include <vector>
#include <list>
#include <iterator>
#include <gtest/gtest.h>

GTEST_TEST(NumericTest, AdjacentDifferenceTest)
{
	{
		const int a[5] { 1, 2, 3, 4, 5 };
		int b[5];
		auto ret = bksge::adjacent_difference(bksge::begin(a), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 5));
		EXPECT_EQ( 1, b[0]);
		EXPECT_EQ( 1, b[1]);
		EXPECT_EQ( 1, b[2]);
		EXPECT_EQ( 1, b[3]);
		EXPECT_EQ( 1, b[4]);
	}
	{
		const int a[5] { 1, 2, 3, 4, 5 };
		int b[5] { 6, 7, 8, 9, 10 };
		auto ret = bksge::adjacent_difference(bksge::begin(a), bksge::end(a), bksge::begin(b), [](int a, int b) { return 2 * a - b; });
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 5));
		EXPECT_EQ( 1, b[0]);
		EXPECT_EQ( 3, b[1]);
		EXPECT_EQ( 4, b[2]);
		EXPECT_EQ( 5, b[3]);
		EXPECT_EQ( 6, b[4]);
	}
	{
		const std::array<int, 4> a {{ 3, 1, 4, 1 }};
		std::list<int> b;
		auto ret = bksge::adjacent_difference(bksge::begin(a), bksge::end(a), std::back_inserter(b));
		(void)ret;
		auto it = b.begin();
		EXPECT_EQ( 3, *it++);
		EXPECT_EQ(-2, *it++);
		EXPECT_EQ( 3, *it++);
		EXPECT_EQ(-3, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const std::array<int, 4> a {{ 3, 1, 4, 1 }};
		std::list<int> b;
		auto ret = bksge::adjacent_difference(bksge::begin(a), bksge::end(a), std::back_inserter(b), bksge::plus<>());
		(void)ret;
		auto it = b.begin();
		EXPECT_EQ( 3, *it++);
		EXPECT_EQ( 4, *it++);
		EXPECT_EQ( 5, *it++);
		EXPECT_EQ( 5, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const std::vector<int> a { -3, 2, -5 };
		std::array<int, 4> b {{}};
		auto ret = bksge::adjacent_difference(bksge::begin(a), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 3));
		EXPECT_EQ(-3, b[0]);
		EXPECT_EQ( 5, b[1]);
		EXPECT_EQ(-7, b[2]);
		EXPECT_EQ( 0, b[3]);
	}
	{
		const std::list<int> a { 2, 2, 2, 2, 2 };
		std::vector<int> b;
		auto ret = bksge::adjacent_difference(bksge::begin(a), bksge::end(a), std::back_inserter(b));
		(void)ret;
		EXPECT_EQ( 2, b[0]);
		EXPECT_EQ( 0, b[1]);
		EXPECT_EQ( 0, b[2]);
		EXPECT_EQ( 0, b[3]);
		EXPECT_EQ( 0, b[4]);
	}
	{
		std::vector<int> a { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		auto ret = bksge::adjacent_difference(bksge::begin(a), bksge::end(a) - 1, bksge::begin(a) + 1, bksge::plus<>());
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 10));
		EXPECT_EQ( 1, a[0]);
		EXPECT_EQ( 1, a[1]);
		EXPECT_EQ( 2, a[2]);
		EXPECT_EQ( 3, a[3]);
		EXPECT_EQ( 5, a[4]);
		EXPECT_EQ( 8, a[5]);
		EXPECT_EQ(13, a[6]);
		EXPECT_EQ(21, a[7]);
		EXPECT_EQ(34, a[8]);
		EXPECT_EQ(55, a[9]);
	}
	{
		const std::vector<int> a;
		std::array<int, 3> b {{ 1, 2, 3 }};
		auto ret = bksge::adjacent_difference(bksge::begin(a), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 0));
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(3, b[2]);
	}
}