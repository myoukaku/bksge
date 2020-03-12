/**
 *	@file	unit_test_fnd_algorithm_swap_ranges.cpp
 *
 *	@brief	swap_ranges のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/swap_ranges.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <list>
#include <vector>
#include <array>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace swap_ranges_test
{

GTEST_TEST(AlgorithmTest, SwapRangesTest)
{
	int a1[] = {1, 2, 3};
	int a2[] = {4, 5, 6};
	std::array<int, 3> a3 {{ 7, 8, 9}};
	std::array<int, 3> a4 {{10,11,12}};
	std::vector<int> v1{13,14,15};
	std::vector<int> v2{16,17,18};
	std::list<int> l1{19,20,21};
	std::list<int> l2{22,23,24};

	{
		auto it = bksge::swap_ranges(bksge::begin(a1), bksge::end(a1), bksge::begin(a2));
		EXPECT_EQ( 4, a1[0]);
		EXPECT_EQ( 5, a1[1]);
		EXPECT_EQ( 6, a1[2]);
		EXPECT_EQ( 1, a2[0]);
		EXPECT_EQ( 2, a2[1]);
		EXPECT_EQ( 3, a2[2]);
		EXPECT_TRUE(it == bksge::end(a2));
	}
	{
		auto it = bksge::swap_ranges(bksge::begin(a3), bksge::end(a3), bksge::begin(a4));
		EXPECT_EQ(10, a3[0]);
		EXPECT_EQ(11, a3[1]);
		EXPECT_EQ(12, a3[2]);
		EXPECT_EQ( 7, a4[0]);
		EXPECT_EQ( 8, a4[1]);
		EXPECT_EQ( 9, a4[2]);
		EXPECT_TRUE(it == bksge::end(a4));
	}
	{
		auto it = bksge::swap_ranges(bksge::begin(v1), bksge::end(v1), bksge::begin(v2));
		EXPECT_EQ(16, v1[0]);
		EXPECT_EQ(17, v1[1]);
		EXPECT_EQ(18, v1[2]);
		EXPECT_EQ(13, v2[0]);
		EXPECT_EQ(14, v2[1]);
		EXPECT_EQ(15, v2[2]);
		EXPECT_TRUE(it == bksge::end(v2));
	}
	{
		auto it = bksge::swap_ranges(bksge::begin(l1), bksge::end(l1), bksge::begin(l2));
		{
			auto i = l1.begin();
			EXPECT_EQ(22, *i++);
			EXPECT_EQ(23, *i++);
			EXPECT_EQ(24, *i++);
		}
		{
			auto i = l2.begin();
			EXPECT_EQ(19, *i++);
			EXPECT_EQ(20, *i++);
			EXPECT_EQ(21, *i++);
		}
		EXPECT_TRUE(it == bksge::end(l2));
	}
	{
		auto it = bksge::swap_ranges(bksge::begin(a1), bksge::end(a1), bksge::begin(a3));
		EXPECT_EQ(10, a1[0]);
		EXPECT_EQ(11, a1[1]);
		EXPECT_EQ(12, a1[2]);
		EXPECT_EQ( 4, a3[0]);
		EXPECT_EQ( 5, a3[1]);
		EXPECT_EQ( 6, a3[2]);
		EXPECT_TRUE(it == bksge::end(a3));
	}
	{
		auto it = bksge::swap_ranges(bksge::begin(a1), bksge::end(a1), bksge::begin(v1));
		EXPECT_EQ(16, a1[0]);
		EXPECT_EQ(17, a1[1]);
		EXPECT_EQ(18, a1[2]);
		EXPECT_EQ(10, v1[0]);
		EXPECT_EQ(11, v1[1]);
		EXPECT_EQ(12, v1[2]);
		EXPECT_TRUE(it == bksge::end(v1));
	}
	{
		auto it = bksge::swap_ranges(bksge::begin(a1), bksge::end(a1), bksge::begin(l1));
		EXPECT_EQ(22, a1[0]);
		EXPECT_EQ(23, a1[1]);
		EXPECT_EQ(24, a1[2]);
		{
			auto i = l1.begin();
			EXPECT_EQ(16, *i++);
			EXPECT_EQ(17, *i++);
			EXPECT_EQ(18, *i++);
		}
		EXPECT_TRUE(it == bksge::end(l1));
	}
	{
		auto it = bksge::swap_ranges(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), bksge::end(a2) - 1);
		EXPECT_EQ( 1, a1[0]);
		EXPECT_EQ( 2, a1[1]);
		EXPECT_EQ(24, a1[2]);
		EXPECT_EQ(22, a2[0]);
		EXPECT_EQ(23, a2[1]);
		EXPECT_EQ( 3, a2[2]);
		EXPECT_TRUE(it == bksge::end(a2) - 1);
	}
	{
		auto it = bksge::swap_ranges(bksge::begin(v2), bksge::end(v2) - 1, bksge::begin(l2), bksge::end(l2));
		EXPECT_EQ(19, v2[0]);
		EXPECT_EQ(20, v2[1]);
		EXPECT_EQ(15, v2[2]);
		{
			auto i = l2.begin();
			EXPECT_EQ(13, *i++);
			EXPECT_EQ(14, *i++);
			EXPECT_TRUE(it == i);
			EXPECT_EQ(21, *i++);
		}
	}
}

}	// namespace swap_ranges_test

}	// namespace bksge_algorithm_test
