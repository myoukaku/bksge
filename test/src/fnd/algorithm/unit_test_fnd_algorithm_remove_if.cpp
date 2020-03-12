/**
 *	@file	unit_test_fnd_algorithm_remove_if.cpp
 *
 *	@brief	remove_if のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/remove_if.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/list.hpp>
#include <vector>
#include <gtest/gtest.h>
#include <array>

namespace bksge_algorithm_test
{

namespace remove_if_test
{

bool pred1(int x)
{
	return x == 1;
}

struct pred2
{
	bool operator()(int x) const
	{
		return x > 1;
	}
};

GTEST_TEST(AlgorithmTest, RemoveIfTest)
{
	{
		int a[] = {1,2,3,1,3,1,2};
		auto ret = bksge::remove_if(bksge::begin(a), bksge::end(a), pred1);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 4));
		EXPECT_EQ(2, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(2, a[3]);
	}
	{
		int a[] = {1,2,3,1,3,1,2};
		auto ret = bksge::remove_if(bksge::begin(a), bksge::end(a), [](int x) { return x < 0; });
		EXPECT_TRUE(ret == bksge::end(a));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(3, a[4]);
		EXPECT_EQ(1, a[5]);
		EXPECT_EQ(2, a[6]);
	}
	{
		int a[] = {1,2,3,1,3,1,2};
		auto ret = bksge::remove_if(bksge::begin(a), bksge::end(a), [](int x) { return x > 0; });
		EXPECT_TRUE(ret == bksge::begin(a));
	}
	{
		std::array<int, 7> a = {{1,2,3,1,3,1,2}};
		auto ret = bksge::remove_if(bksge::begin(a), bksge::end(a), pred2());
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 3));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(1, a[2]);
		EXPECT_EQ(7u, a.size());	// remove_ifしてもコンテナのサイズは変わらない
	}
	{
		std::array<int, 4> a = {{1,1,1,1}};
		auto ret = bksge::remove_if(bksge::begin(a), bksge::end(a), [](int x) { return x == 1; });
		EXPECT_TRUE(ret == bksge::begin(a));
		EXPECT_EQ(4u, a.size());	// remove_ifしてもコンテナのサイズは変わらない
	}
	{
		std::vector<int> a = {1,2,3,1,3,1,2,2};
		auto ret = bksge::remove_if(bksge::begin(a), bksge::end(a), [](int x) { return (x % 2) == 0; });
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 5));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(1, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(1, a[4]);
		EXPECT_EQ(8u, a.size());	// remove_ifしてもコンテナのサイズは変わらない
	}
	{
		std::vector<int> a;
		auto ret = bksge::remove_if(bksge::begin(a), bksge::end(a), pred1);
		EXPECT_TRUE(ret == bksge::end(a));
		EXPECT_EQ(0u, a.size());
	}
	{
		bksge::list<int> a = {1,2,3,1,3,1,2,1,1};
		auto ret = bksge::remove_if(bksge::begin(a), bksge::end(a), [](int x) { return (x % 2) == 1; });
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 2));
		auto it = a.begin();
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_TRUE(it != a.end());	// remove_ifしてもコンテナのサイズは変わらない
	}
	{
		bksge::list<int> a;
		auto ret = bksge::remove_if(bksge::begin(a), bksge::end(a), [](int x) { return (x % 2) == 1; });
		EXPECT_TRUE(ret == bksge::end(a));
		EXPECT_EQ(0u, a.size());
	}
}

}	// namespace remove_if_test

}	// namespace bksge_algorithm_test
