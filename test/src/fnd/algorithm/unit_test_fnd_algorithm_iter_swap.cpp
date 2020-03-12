/**
 *	@file	unit_test_fnd_algorithm_iter_swap.cpp
 *
 *	@brief	iter_swap のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/iter_swap.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/list.hpp>
#include <vector>
#include <gtest/gtest.h>
#include <array>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace iter_swap_test
{

GTEST_TEST(AlgorithmTest, IterSwapTest)
{
	int a1[] = {1, 2, 3};
	int a2[] = {4, 5, 6};
	std::array<int, 3> a3 {{ 7, 8, 9}};
	std::array<int, 3> a4 {{10,11,12}};
	std::vector<int> v1{13,14,15};
	std::vector<int> v2{16,17,18};
	bksge::list<int> l1{19,20,21};
	bksge::list<int> l2{22,23,24};

	bksge::iter_swap(bksge::begin(a1), bksge::begin(a2));
	EXPECT_EQ( 4, a1[0]);
	EXPECT_EQ( 2, a1[1]);
	EXPECT_EQ( 3, a1[2]);
	EXPECT_EQ( 1, a2[0]);
	EXPECT_EQ( 5, a2[1]);
	EXPECT_EQ( 6, a2[2]);

	bksge::iter_swap(bksge::begin(a3), bksge::begin(a4) + 2);
	EXPECT_EQ(12, a3[0]);
	EXPECT_EQ( 8, a3[1]);
	EXPECT_EQ( 9, a3[2]);
	EXPECT_EQ(10, a4[0]);
	EXPECT_EQ(11, a4[1]);
	EXPECT_EQ( 7, a4[2]);

	bksge::iter_swap(bksge::begin(v1), bksge::begin(v2));
	EXPECT_EQ(16, v1[0]);
	EXPECT_EQ(14, v1[1]);
	EXPECT_EQ(15, v1[2]);
	EXPECT_EQ(13, v2[0]);
	EXPECT_EQ(17, v2[1]);
	EXPECT_EQ(18, v2[2]);

	bksge::iter_swap(++bksge::begin(l1), bksge::begin(l2));
	{
		auto i = l1.begin();
		EXPECT_EQ(19, *i++);
		EXPECT_EQ(22, *i++);
		EXPECT_EQ(21, *i++);
	}
	{
		auto i = l2.begin();
		EXPECT_EQ(20, *i++);
		EXPECT_EQ(23, *i++);
		EXPECT_EQ(24, *i++);
	}

	bksge::iter_swap(bksge::begin(a1), bksge::begin(l1));
	EXPECT_EQ(19, a1[0]);
	EXPECT_EQ( 2, a1[1]);
	EXPECT_EQ( 3, a1[2]);
	{
		auto i = l1.begin();
		EXPECT_EQ( 4, *i++);
		EXPECT_EQ(22, *i++);
		EXPECT_EQ(21, *i++);
	}
}

}	// namespace iter_swap_test

}	// namespace bksge_algorithm_test
