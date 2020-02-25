/**
 *	@file	unit_test_fnd_algorithm_clamp.cpp
 *
 *	@brief	clamp のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/clamp.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace clamp_test
{

BKSGE_CONSTEXPR bool pred1(int x, int y)
{
	return x < y;
}

struct pred2
{
	template <typename T>
	BKSGE_CONSTEXPR bool operator()(T x, T y) const
	{
		return x > y;
	}
};

GTEST_TEST(AlgorithmTest, AdjacentFindTest)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::clamp(0, 1, 5));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::clamp(1, 1, 5));
	BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::clamp(2, 1, 5));
	BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::clamp(3, 1, 5));
	BKSGE_CONSTEXPR_EXPECT_EQ(4, bksge::clamp(4, 1, 5));
	BKSGE_CONSTEXPR_EXPECT_EQ(5, bksge::clamp(5, 1, 5));
	BKSGE_CONSTEXPR_EXPECT_EQ(5, bksge::clamp(6, 1, 5));

	BKSGE_CONSTEXPR_EXPECT_EQ(-1.5, bksge::clamp(-2.5, -1.5, 2.5));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1.5, bksge::clamp(-2.0, -1.5, 2.5));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1.5, bksge::clamp(-1.5, -1.5, 2.5));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1.0, bksge::clamp(-1.0, -1.5, 2.5));
	BKSGE_CONSTEXPR_EXPECT_EQ(-0.5, bksge::clamp(-0.5, -1.5, 2.5));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0.0, bksge::clamp( 0.0, -1.5, 2.5));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0.5, bksge::clamp( 0.5, -1.5, 2.5));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1.0, bksge::clamp( 1.0, -1.5, 2.5));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1.5, bksge::clamp( 1.5, -1.5, 2.5));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2.0, bksge::clamp( 2.0, -1.5, 2.5));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2.5, bksge::clamp( 2.5, -1.5, 2.5));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2.5, bksge::clamp( 3.0, -1.5, 2.5));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2.5, bksge::clamp( 3.5, -1.5, 2.5));

	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::clamp(0, 1, 5, pred1));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::clamp(1, 1, 5, pred1));
	BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::clamp(2, 1, 5, pred1));
	BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::clamp(3, 1, 5, pred1));
	BKSGE_CONSTEXPR_EXPECT_EQ(4, bksge::clamp(4, 1, 5, pred1));
	BKSGE_CONSTEXPR_EXPECT_EQ(5, bksge::clamp(5, 1, 5, pred1));
	BKSGE_CONSTEXPR_EXPECT_EQ(5, bksge::clamp(6, 1, 5, pred1));

	BKSGE_CONSTEXPR_EXPECT_EQ(-1.5, bksge::clamp(-2.5, 2.5, -1.5, pred2()));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1.5, bksge::clamp(-2.0, 2.5, -1.5, pred2()));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1.5, bksge::clamp(-1.5, 2.5, -1.5, pred2()));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1.0, bksge::clamp(-1.0, 2.5, -1.5, pred2()));
	BKSGE_CONSTEXPR_EXPECT_EQ(-0.5, bksge::clamp(-0.5, 2.5, -1.5, pred2()));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0.0, bksge::clamp( 0.0, 2.5, -1.5, pred2()));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0.5, bksge::clamp( 0.5, 2.5, -1.5, pred2()));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1.0, bksge::clamp( 1.0, 2.5, -1.5, pred2()));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1.5, bksge::clamp( 1.5, 2.5, -1.5, pred2()));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2.0, bksge::clamp( 2.0, 2.5, -1.5, pred2()));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2.5, bksge::clamp( 2.5, 2.5, -1.5, pred2()));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2.5, bksge::clamp( 3.0, 2.5, -1.5, pred2()));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2.5, bksge::clamp( 3.5, 2.5, -1.5, pred2()));
}

}	// namespace clamp_test

}	// namespace bksge_algorithm_test
