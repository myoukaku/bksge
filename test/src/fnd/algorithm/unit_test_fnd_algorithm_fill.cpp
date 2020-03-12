/**
 *	@file	unit_test_fnd_algorithm_fill.cpp
 *
 *	@brief	fill のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/fill.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/list.hpp>
#include <vector>
#include <gtest/gtest.h>
#include <array>

namespace bksge_algorithm_test
{

namespace fill_test
{

GTEST_TEST(AlgorithmTest, FillTest)
{
	{
		int a[3];
		bksge::fill(bksge::begin(a), bksge::end(a), 42);
		EXPECT_EQ(42, a[0]);
		EXPECT_EQ(42, a[1]);
		EXPECT_EQ(42, a[2]);
	}
	{
		std::array<int, 4> a{ { 1, 2, 3, 4 } };
		bksge::fill(bksge::begin(a), bksge::end(a), -1);
		EXPECT_EQ(-1, a[0]);
		EXPECT_EQ(-1, a[1]);
		EXPECT_EQ(-1, a[2]);
		EXPECT_EQ(-1, a[3]);
	}
	{
		std::vector<int> a(5);
		bksge::fill(bksge::begin(a), bksge::end(a), 3);
		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(3, a[4]);
	}
	{
		std::vector<int> a;
		bksge::fill(bksge::begin(a), bksge::end(a), 3);
		EXPECT_TRUE(a.empty());
	}
	{
		bksge::list<int> a(3);
		bksge::fill(bksge::begin(a), bksge::end(a), 4);
		auto it = a.begin();
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		bksge::list<int> a;
		bksge::fill(bksge::begin(a), bksge::end(a), 0);
		EXPECT_TRUE(a.empty());
	}
}

}	// namespace fill_test

}	// namespace bksge_algorithm_test
