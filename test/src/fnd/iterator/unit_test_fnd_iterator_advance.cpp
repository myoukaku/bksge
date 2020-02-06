﻿/**
 *	@file	unit_test_fnd_iterator_advance.cpp
 *
 *	@brief	advance のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/advance.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <array>
#include <vector>
#include <list>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, AdvanceTest)
{
	{
		int a[] = {0,1,2};

		auto it = bksge::begin(a);
		EXPECT_EQ(0, *it);
		bksge::advance(it);
		EXPECT_EQ(1, *it);
		bksge::advance(it);
		EXPECT_EQ(2, *it);
		bksge::advance(it);
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		int a[] = {0,1,2};

		auto it = bksge::begin(a);
		EXPECT_EQ(0, *it);
		bksge::advance(it, 2);
		EXPECT_EQ(2, *it);
		bksge::advance(it, -1);
		EXPECT_EQ(1, *it);
		bksge::advance(it, 2);
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		std::vector<float> v {3,1,4,1,5};

		auto it = bksge::begin(v);
		EXPECT_EQ(3, *it);
		bksge::advance(it);
		EXPECT_EQ(1, *it);
		bksge::advance(it);
		EXPECT_EQ(4, *it);
		bksge::advance(it);
		EXPECT_EQ(1, *it);
		bksge::advance(it);
		EXPECT_EQ(5, *it);
		bksge::advance(it);
		EXPECT_TRUE(it == bksge::end(v));
	}
	{
		std::vector<float> v {3,1,4,1,5};

		auto it = bksge::begin(v);
		EXPECT_EQ(3, *it);
		bksge::advance(it, 3);
		EXPECT_EQ(1, *it);
		bksge::advance(it, -1);
		EXPECT_EQ(4, *it);
		bksge::advance(it, 2);
		EXPECT_EQ(5, *it);
		bksge::advance(it, -4);
		EXPECT_EQ(3, *it);
		bksge::advance(it, 5);
		EXPECT_TRUE(it == bksge::end(v));
	}
	{
		std::list<int> l {2, 3, 4};

		auto it = bksge::begin(l);
		EXPECT_EQ(2, *it);
		bksge::advance(it);
		EXPECT_EQ(3, *it);
		bksge::advance(it);
		EXPECT_EQ(4, *it);
		bksge::advance(it);
		EXPECT_TRUE(it == bksge::end(l));
	}
	{
		std::list<int> l {2, 3, 4};

		auto it = bksge::begin(l);
		EXPECT_EQ(2, *it);
		bksge::advance(it, 2);
		EXPECT_EQ(4, *it);
		bksge::advance(it, -2);
		EXPECT_EQ(2, *it);
		bksge::advance(it, 3);
		EXPECT_TRUE(it == bksge::end(l));
	}
	{
		std::array<float, 4> a{{1, 2, 3, 4}};

		auto it = bksge::begin(a);
		EXPECT_EQ(1, *it);
		bksge::advance(it);
		EXPECT_EQ(2, *it);
		bksge::advance(it);
		EXPECT_EQ(3, *it);
		bksge::advance(it);
		EXPECT_EQ(4, *it);
		bksge::advance(it);
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		std::array<float, 4> a{{1, 2, 3, 4}};

		auto it = bksge::begin(a);
		EXPECT_EQ(1, *it);
		bksge::advance(it, 2);
		EXPECT_EQ(3, *it);
		bksge::advance(it, -1);
		EXPECT_EQ(2, *it);
		bksge::advance(it, 3);
		EXPECT_TRUE(it == bksge::end(a));
	}
}