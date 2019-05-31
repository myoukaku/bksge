/**
 *	@file	unit_test_tpp_accumulate.cpp
 *
 *	@brief	accumulate のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/tpp/accumulate.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#define BKSGE_10_Ones		\
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1

#define BKSGE_100_Ones	\
	BKSGE_10_Ones, BKSGE_10_Ones, BKSGE_10_Ones, BKSGE_10_Ones, BKSGE_10_Ones, \
	BKSGE_10_Ones, BKSGE_10_Ones, BKSGE_10_Ones, BKSGE_10_Ones, BKSGE_10_Ones

#define BKSGE_500_Ones	\
	BKSGE_100_Ones, BKSGE_100_Ones, BKSGE_100_Ones, BKSGE_100_Ones, BKSGE_100_Ones

GTEST_TEST(TppTest, AccumulateTest)
{
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::tpp::accumulate<int>());
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::tpp::accumulate<int>(1));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::tpp::accumulate<int>(2));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, bksge::tpp::accumulate<int>(1, 2));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::tpp::accumulate<int>(3, 1, 2));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::tpp::accumulate<int>(3, 1, 4, 2));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::tpp::accumulate<int>(3, 1, 4, 5, 2));

	BKSGE_CONSTEXPR_EXPECT_EQ( 10, bksge::tpp::accumulate<int>(BKSGE_10_Ones));
	BKSGE_CONSTEXPR_EXPECT_EQ(100, bksge::tpp::accumulate<int>(BKSGE_100_Ones));
	BKSGE_CONSTEXPR_EXPECT_EQ(200, bksge::tpp::accumulate<int>(BKSGE_100_Ones, BKSGE_100_Ones));
	//BKSGE_CONSTEXPR_EXPECT_EQ(500, bksge::tpp::accumulate<int>(BKSGE_500_Ones));
}

#undef BKSGE_10_Ones
#undef BKSGE_100_Ones
#undef BKSGE_500_Ones
