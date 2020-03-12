﻿/**
 *	@file	unit_test_fnd_algorithm_unique.cpp
 *
 *	@brief	unique のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/unique.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <memory>
#include <list>
#include <vector>
#include <array>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace unique_test
{

bool pred1(const std::shared_ptr<int>& x, const std::shared_ptr<int>& y)
{
	return *x == *y;
}

struct pred2
{
	bool operator()(const std::unique_ptr<int>& x, const std::unique_ptr<int>& y) const
	{
		return *x == *y;
	}
};

GTEST_TEST(AlgorithmTest, UniqueTest)
{
	{
		int a[] = { 2,5,3,3,1,2,4,2,1,1,4,4,3,3,3 };
		auto ret = bksge::unique(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 10));

		EXPECT_EQ(2, a[0]);
		EXPECT_EQ(5, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(2, a[4]);
		EXPECT_EQ(4, a[5]);
		EXPECT_EQ(2, a[6]);
		EXPECT_EQ(1, a[7]);
		EXPECT_EQ(4, a[8]);
		EXPECT_EQ(3, a[9]);
	}
	{
		std::array<int, 10> a = {{ 1,1,2,2,2,3,4,4,5,5 }};
		auto ret = bksge::unique(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 5));

		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(4, a[3]);
		EXPECT_EQ(5, a[4]);
	}
	{
		std::vector<std::shared_ptr<int>> a;
		a.emplace_back(new int(1));
		a.emplace_back(new int(4));
		a.emplace_back(new int(4));
		a.emplace_back(new int(2));
		a.emplace_back(new int(1));
		a.emplace_back(new int(1));
		a.emplace_back(new int(3));
		a.emplace_back(new int(3));
		a.emplace_back(new int(3));
		auto ret = bksge::unique(bksge::begin(a), bksge::end(a), pred1);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 5));

		EXPECT_EQ(1, *a[0]);
		EXPECT_EQ(4, *a[1]);
		EXPECT_EQ(2, *a[2]);
		EXPECT_EQ(1, *a[3]);
		EXPECT_EQ(3, *a[4]);
	}
	{
		std::vector<int> a;
		auto ret = bksge::unique(bksge::begin(a), bksge::end(a), [](int, int){ return true; });
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
		EXPECT_TRUE(a.empty());
	}
	{
		std::list<std::unique_ptr<int>> a;
		a.emplace_back(new int(1));
		a.emplace_back(new int(1));
		a.emplace_back(new int(1));
		a.emplace_back(new int(4));
		a.emplace_back(new int(4));
		a.emplace_back(new int(2));
		a.emplace_back(new int(3));
		a.emplace_back(new int(3));
		a.emplace_back(new int(3));
		auto ret = bksge::unique(bksge::begin(a), bksge::end(a), pred2());
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 4));

		auto it = a.begin();
		EXPECT_EQ(1, *(*it++));
		EXPECT_EQ(4, *(*it++));
		EXPECT_EQ(2, *(*it++));
		EXPECT_EQ(3, *(*it++));
		EXPECT_TRUE(it == ret);
	}
	{
		std::list<int> a;
		auto ret = bksge::unique(bksge::begin(a), bksge::end(a), [](int, int){ return false; });
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
		EXPECT_TRUE(a.empty());
	}
}

}	// namespace unique_test

}	// namespace bksge_algorithm_test
