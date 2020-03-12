/**
 *	@file	unit_test_fnd_algorithm_replace_if.cpp
 *
 *	@brief	replace_if のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/replace_if.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <list>
#include <vector>
#include <array>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace replace_if_test
{

bool pred1(int a)
{
	return a == 1;
}

struct pred2
{
	bool operator()(int a)
	{
		return a == 2;
	}
};

GTEST_TEST(AlgorithmTest, ReplaceIfTest)
{
	{
		int a[] { 3,1,2,1,2 };
		bksge::replace_if(bksge::begin(a), bksge::end(a), pred1, 4);
		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(4, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(4, a[3]);
		EXPECT_EQ(2, a[4]);
	}
	{
		std::array<int, 6> a {{ 3,1,2,1,2,3 }};
		bksge::replace_if(bksge::begin(a), bksge::end(a), pred2(), 5);
		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(5, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(5, a[4]);
		EXPECT_EQ(3, a[5]);
	}
	{
		std::vector<int> a { 3,1,4,1,5,9,2 };
		bksge::replace_if(bksge::begin(a), bksge::end(a), [](int a) { return a == 2; }, 0);
		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(4, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(5, a[4]);
		EXPECT_EQ(9, a[5]);
		EXPECT_EQ(0, a[6]);
	}
	{
		std::vector<int> a;
		bksge::replace_if(bksge::begin(a), bksge::end(a), [](int) { return true; }, 0);
		EXPECT_TRUE(a.empty());
	}
	{
		std::list<int> a { 1,2,3,4,5,6 };
		bksge::replace_if(bksge::begin(a), bksge::end(a), [](int a) { return a % 2 == 0; }, 0);
		auto it = a.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(0, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(0, *it++);
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(0, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		std::list<int> a;
		bksge::replace_if(bksge::begin(a), bksge::end(a), [](int) { return false; }, 1);
		EXPECT_TRUE(a.empty());
	}
}

}	// namespace replace_if_test

}	// namespace bksge_algorithm_test
