/**
 *	@file	unit_test_fnd_algorithm_minmax.cpp
 *
 *	@brief	minmax のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/minmax.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <array>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace minmax_test
{

BKSGE_CONSTEXPR bool pred1(int x, int y)
{
	return x > y;
}

struct pred2
{
	BKSGE_CONSTEXPR bool operator()(int x, int y) const
	{
		return bksge::abs(x) < bksge::abs(y);
	}
};

GTEST_TEST(AlgorithmTest, MinmaxTest)
{
	{
		BKSGE_CXX14_STATIC_CONSTEXPR int a = 2;
		BKSGE_CXX14_STATIC_CONSTEXPR int b = 3;
		BKSGE_CXX14_STATIC_CONSTEXPR auto ret = bksge::minmax(a, b);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(2, ret.first);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3, ret.second);
	}
	{
		BKSGE_CXX14_STATIC_CONSTEXPR int a = 4;
		BKSGE_CXX14_STATIC_CONSTEXPR int b = 3;
		BKSGE_CXX14_STATIC_CONSTEXPR auto ret = bksge::minmax(a, b);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3, ret.first);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(4, ret.second);
	}
	{
		BKSGE_CXX14_STATIC_CONSTEXPR int a = 2;
		BKSGE_CXX14_STATIC_CONSTEXPR int b = 3;
		BKSGE_CXX14_STATIC_CONSTEXPR auto ret = bksge::minmax(a, b, pred1);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3, ret.first);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(2, ret.second);
	}
	{
		BKSGE_CXX14_STATIC_CONSTEXPR int a = 2;
		BKSGE_CXX14_STATIC_CONSTEXPR int b = -3;
		BKSGE_CXX14_STATIC_CONSTEXPR auto ret = bksge::minmax(a, b);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(-3, ret.first);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 2, ret.second);
	}
	{
		BKSGE_CXX14_STATIC_CONSTEXPR int a = 2;
		BKSGE_CXX14_STATIC_CONSTEXPR int b = -3;
		BKSGE_CXX14_STATIC_CONSTEXPR auto ret = bksge::minmax(a, b, pred2());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 2, ret.first);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(-3, ret.second);
	}

	{
		auto ret = bksge::minmax({1, 2, 3});
		EXPECT_EQ( 1, ret.first);
		EXPECT_EQ( 3, ret.second);
	}
	{
		auto ret = bksge::minmax({4, -2, 3});
		EXPECT_EQ(-2, ret.first);
		EXPECT_EQ( 4, ret.second);
	}
	{
		auto ret = bksge::minmax({1, 2, 3}, [](int x, int y) { return x > y; });
		EXPECT_EQ( 3, ret.first);
		EXPECT_EQ( 1, ret.second);
	}
	{
		auto ret = bksge::minmax({1, 4, 2, 0, 3}, [](int x, int y) { return x > y; });
		EXPECT_EQ( 4, ret.first);
		EXPECT_EQ( 0, ret.second);
	}
}

}	// namespace minmax_test

}	// namespace bksge_algorithm_test
