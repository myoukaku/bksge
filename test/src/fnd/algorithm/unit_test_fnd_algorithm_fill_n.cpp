/**
 *	@file	unit_test_fnd_algorithm_fill_n.cpp
 *
 *	@brief	fill_n のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/fill_n.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/back_inserter.hpp>
#include <list>
#include <vector>
#include <array>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace fill_n_test
{

GTEST_TEST(AlgorithmTest, FillNTest)
{
	{
		int a1[3];
		auto it = bksge::fill_n(bksge::begin(a1), 3, 1);
		EXPECT_EQ(1, a1[0]);
		EXPECT_EQ(1, a1[1]);
		EXPECT_EQ(1, a1[2]);
		EXPECT_TRUE(it == bksge::end(a1));

		it = bksge::fill_n(bksge::begin(a1), 2, 2);
		EXPECT_EQ(2, a1[0]);
		EXPECT_EQ(2, a1[1]);
		EXPECT_EQ(1, a1[2]);
		EXPECT_TRUE(it == bksge::begin(a1) + 2);

		it = bksge::fill_n(bksge::begin(a1), 0, 3);
		EXPECT_EQ(2, a1[0]);
		EXPECT_EQ(2, a1[1]);
		EXPECT_EQ(1, a1[2]);
		EXPECT_TRUE(it == bksge::begin(a1));
	}
	{
		std::array<int, 4> a2{ { 1, 2, 3, 4 } };
		auto it = bksge::fill_n(bksge::begin(a2), 3, -1);
		EXPECT_EQ(-1, a2[0]);
		EXPECT_EQ(-1, a2[1]);
		EXPECT_EQ(-1, a2[2]);
		EXPECT_EQ( 4, a2[3]);
		EXPECT_TRUE(it == bksge::begin(a2) + 3);
	}
	{
		std::vector<int> v1(5);
		auto it = bksge::fill_n(bksge::begin(v1), 2, 3);
		EXPECT_EQ(3, v1[0]);
		EXPECT_EQ(3, v1[1]);
		EXPECT_EQ(0, v1[2]);
		EXPECT_EQ(0, v1[3]);
		EXPECT_EQ(0, v1[4]);
		EXPECT_TRUE(it == bksge::begin(v1) + 2);
	}
	{
		std::vector<int> v2;
		bksge::fill_n(bksge::back_inserter(v2), 3, 11);
		EXPECT_EQ(11, v2[0]);
		EXPECT_EQ(11, v2[1]);
		EXPECT_EQ(11, v2[2]);
	}
	{
		std::list<int> l1(3);
		bksge::fill_n(bksge::begin(l1), 3, 4);
		auto it = l1.begin();
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_TRUE(it == l1.end());
	}
	{
		std::list<int> l2;
		bksge::fill_n(bksge::back_inserter(l2), 2, 12);
		auto it = l2.begin();
		EXPECT_EQ(12, *it++);
		EXPECT_EQ(12, *it++);
		EXPECT_TRUE(it == l2.end());
	}
}

}	// namespace fill_n_test

}	// namespace bksge_algorithm_test
