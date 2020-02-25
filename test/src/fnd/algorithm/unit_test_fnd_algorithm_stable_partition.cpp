﻿/**
 *	@file	unit_test_fnd_algorithm_stable_partition.cpp
 *
 *	@brief	stable_partition のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/stable_partition.hpp>
#include <bksge/fnd/functional/greater.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <gtest/gtest.h>
#include <array>
#include <list>
#include <vector>

namespace bksge_algorithm_test
{

namespace stable_partition_test
{

BKSGE_CONSTEXPR bool pred1(int x)
{
	return (x % 2) == 0;
}

struct pred2
{
	BKSGE_CONSTEXPR bool operator()(int x) const
	{
		return x > 2;
	}
};

GTEST_TEST(AlgorithmTest, StablePartitionTest)
{
	{
		int a[] {1,2,3,4,5};
		auto ret = bksge::stable_partition(bksge::begin(a), bksge::end(a), pred1);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 2));
		EXPECT_EQ(2, a[0]);
		EXPECT_EQ(4, a[1]);
		EXPECT_EQ(1, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(5, a[4]);
	}
	{
		int a[] {1,3,5,7};
		auto ret = bksge::stable_partition(bksge::begin(a), bksge::end(a), pred1);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(5, a[2]);
		EXPECT_EQ(7, a[3]);
	}
	{
		int a[] {2,4,6};
		auto ret = bksge::stable_partition(bksge::begin(a), bksge::end(a), pred1);
		EXPECT_TRUE(ret == bksge::end(a));
		EXPECT_EQ(2, a[0]);
		EXPECT_EQ(4, a[1]);
		EXPECT_EQ(6, a[2]);
	}
	{
		std::array<int, 5> a {{1,2,3,4,5}};
		auto ret = bksge::stable_partition(bksge::begin(a), bksge::end(a), pred2());
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 3));
		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(4, a[1]);
		EXPECT_EQ(5, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(2, a[4]);
	}
	{
		std::vector<int> a {1,2,3,4,5};
		auto ret = bksge::stable_partition(bksge::begin(a), bksge::end(a), [](int x) { return (x % 2) == 1; });
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 3));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(5, a[2]);
		EXPECT_EQ(2, a[3]);
		EXPECT_EQ(4, a[4]);
	}
	{
		std::list<int> a {1,2,3,4,5};
		auto ret = bksge::stable_partition(bksge::begin(a), bksge::end(a), [](int x) { return x < 3; });
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 2));
		auto it = a.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(5, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		std::vector<int> a;
		auto ret = bksge::stable_partition(bksge::begin(a), bksge::end(a), pred1);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
	}
	{
		std::list<int> a;
		auto ret = bksge::stable_partition(bksge::begin(a), bksge::end(a), pred2());
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
	}
}

}	// namespace stable_partition_test

}	// namespace bksge_algorithm_test