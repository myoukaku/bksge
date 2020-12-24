/**
 *	@file	unit_test_fnd_numeric_accumulate.cpp
 *
 *	@brief	accumulate のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/numeric/accumulate.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/functional/multiplies.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <array>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(NumericTest, AccumulateTest)
{
	{
		const int a[] = { 1, 2, 3 };
		auto x1 = bksge::accumulate(bksge::begin(a), bksge::end(a), 0);
		EXPECT_EQ( 6, x1);
		auto x2 = bksge::accumulate(bksge::begin(a), bksge::end(a), 10);
		EXPECT_EQ(16, x2);
		auto x3 = bksge::accumulate(bksge::begin(a), bksge::end(a), 0, [](int x, int y) { return x + (y * y); });
		EXPECT_EQ(14, x3);
	}
	{
		const std::array<int, 4> a = {{ 11, 12, 13, 14 }};
		auto x1 = bksge::accumulate(bksge::begin(a), bksge::end(a), 0);
		EXPECT_EQ(50, x1);
		auto x2 = bksge::accumulate(bksge::begin(a), bksge::end(a), -10);
		EXPECT_EQ(40, x2);
		auto x3 = bksge::accumulate(bksge::begin(a), bksge::end(a), 100, [](int x, int y) { return x + (y * 2); });
		EXPECT_EQ(200, x3);
	}
	{
		const bksge::vector<int> v = { 3, 1, 4, 1, 5 };
		auto x1 = bksge::accumulate(bksge::begin(v), bksge::end(v), 0);
		EXPECT_EQ(14, x1);
		auto x2 = bksge::accumulate(bksge::begin(v), bksge::end(v), 20);
		EXPECT_EQ(34, x2);
		auto x3 = bksge::accumulate(bksge::begin(v), bksge::end(v), -20, [](int x, int y) { return x * y; });
		EXPECT_EQ(-1200, x3);
	}
	{
		const bksge::list<int> l = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
		auto x1 = bksge::accumulate(bksge::begin(l), bksge::end(l), 0);
		EXPECT_EQ(55, x1);
		auto x2 = bksge::accumulate(bksge::begin(l), bksge::end(l), 30);
		EXPECT_EQ(85, x2);
		auto x3 = bksge::accumulate(bksge::begin(l), bksge::end(l), -30, [](int x, int y) { return x + y + 1; });
		EXPECT_EQ(36, x3);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST int a[] = { 1, 2, 3, 4 };
		BKSGE_CXX14_CONSTEXPR auto x1 = bksge::accumulate(bksge::begin(a), bksge::end(a), 0);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(10, x1);
		BKSGE_CXX14_CONSTEXPR auto x2 = bksge::accumulate(bksge::begin(a), bksge::end(a), 10);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(20, x2);
		BKSGE_CXX14_CONSTEXPR auto x3 = bksge::accumulate(bksge::begin(a), bksge::end(a), 1, bksge::multiplies<>());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(24, x3);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST std::array<int, 5> a = {{ 11, 12, 13, 14, 15 }};
		BKSGE_CXX17_CONSTEXPR auto x1 = bksge::accumulate(bksge::begin(a), bksge::end(a), 0);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(65, x1);
		BKSGE_CXX17_CONSTEXPR auto x2 = bksge::accumulate(bksge::begin(a), bksge::end(a), -20);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(45, x2);
		BKSGE_CXX17_CONSTEXPR auto x3 = bksge::accumulate(bksge::begin(a), bksge::end(a), 1, bksge::multiplies<>());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(360360, x3);
	}
}
