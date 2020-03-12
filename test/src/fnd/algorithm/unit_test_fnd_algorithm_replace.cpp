/**
 *	@file	unit_test_fnd_algorithm_replace.cpp
 *
 *	@brief	replace のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/replace.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <list>
#include <vector>
#include <array>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace replace_test
{

GTEST_TEST(AlgorithmTest, ReplaceTest)
{
	{
		int a[] { 3,1,2,1,2 };
		bksge::replace(bksge::begin(a), bksge::end(a), 1, 4);
		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(4, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(4, a[3]);
		EXPECT_EQ(2, a[4]);
	}
	{
		std::array<int, 6> a {{ 3,1,2,1,2,3 }};
		bksge::replace(bksge::begin(a), bksge::end(a), 3, 5);
		EXPECT_EQ(5, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(2, a[4]);
		EXPECT_EQ(5, a[5]);
	}
	{
		std::vector<int> a { 3,1,4,1,5,9,2 };
		bksge::replace(bksge::begin(a), bksge::end(a), 2, 0);
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
		bksge::replace(bksge::begin(a), bksge::end(a), 2, 0);
		EXPECT_TRUE(a.empty());
	}
	{
		std::list<int> a { 9,1,9 };
		bksge::replace(bksge::begin(a), bksge::end(a), 9, 0);
		auto it = a.begin();
		EXPECT_EQ(0, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(0, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		std::list<int> a;
		bksge::replace(bksge::begin(a), bksge::end(a), 0, 1);
		EXPECT_TRUE(a.empty());
	}
}

}	// namespace replace_test

}	// namespace bksge_algorithm_test
