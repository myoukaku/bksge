﻿/**
 *	@file	unit_test_fnd_pair_compare.cpp
 *
 *	@brief	pairの比較演算子のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair/pair.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(PairTest, CompareTest)
{
	BKSGE_CXX14_CONSTEXPR bksge::pair<int, double> p1(1, 1.5);
	BKSGE_CXX14_CONSTEXPR bksge::pair<int, double> p2(1, 1.5);
	BKSGE_CXX14_CONSTEXPR bksge::pair<int, double> p3(2, 1.5);
	BKSGE_CXX14_CONSTEXPR bksge::pair<int, double> p4(0, 1.5);
	BKSGE_CXX14_CONSTEXPR bksge::pair<int, double> p5(1, 2.5);
	BKSGE_CXX14_CONSTEXPR bksge::pair<int, double> p6(1, 0.5);
	BKSGE_CXX14_CONSTEXPR bksge::pair<int, double> p7(3, 2.5);
	BKSGE_CXX14_CONSTEXPR bksge::pair<int, double> p8(0, 0.5);

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 == p1);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 == p2);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 == p3);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 == p4);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 == p5);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 == p6);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 == p7);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 == p8);

	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 != p1);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 != p2);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 != p3);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 != p4);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 != p5);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 != p6);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 != p7);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 != p8);

	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 < p1);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 < p2);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 < p3);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 < p4);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 < p5);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 < p6);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 < p7);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 < p8);

	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 > p1);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 > p2);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 > p3);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 > p4);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 > p5);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 > p6);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 > p7);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 > p8);

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 <= p1);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 <= p2);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 <= p3);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 <= p4);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 <= p5);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 <= p6);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 <= p7);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 <= p8);

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 >= p1);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 >= p2);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 >= p3);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 >= p4);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 >= p5);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 >= p6);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(p1 >= p7);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (p1 >= p8);
}
