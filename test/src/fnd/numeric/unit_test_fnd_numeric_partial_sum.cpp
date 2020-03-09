/**
 *	@file	unit_test_fnd_numeric_partial_sum.cpp
 *
 *	@brief	partial_sum のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/numeric/partial_sum.hpp>
#include <bksge/fnd/functional/minus.hpp>
#include <bksge/fnd/functional/multiplies.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <array>
#include <bksge/fnd/vector.hpp>
#include <list>
#include <iterator>
#include <gtest/gtest.h>

GTEST_TEST(NumericTest, PartialSumTest)
{
	{
		const int a[5] { 1, 2, 3, 4, 5 };
		int b[5];
		auto ret = bksge::partial_sum(bksge::begin(a), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 5));
		EXPECT_EQ( 1, b[0]);
		EXPECT_EQ( 3, b[1]);
		EXPECT_EQ( 6, b[2]);
		EXPECT_EQ(10, b[3]);
		EXPECT_EQ(15, b[4]);
	}
	{
		const int a[5] { 1, 2, 3, 4, 5 };
		int b[5] { 6, 7, 8, 9, 10 };
		auto ret = bksge::partial_sum(bksge::begin(a), bksge::end(a), bksge::begin(b), [](int a, int b) { return 2 * a - b; });
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 5));
		EXPECT_EQ(  1, b[0]);
		EXPECT_EQ(  0, b[1]);
		EXPECT_EQ( -3, b[2]);
		EXPECT_EQ(-10, b[3]);
		EXPECT_EQ(-25, b[4]);
	}
	{
		const std::array<int, 4> a {{ 3, 1, 4, 1 }};
		std::list<int> b;
		auto ret = bksge::partial_sum(bksge::begin(a), bksge::end(a), std::back_inserter(b));
		(void)ret;
		auto it = b.begin();
		EXPECT_EQ( 3, *it++);
		EXPECT_EQ( 4, *it++);
		EXPECT_EQ( 8, *it++);
		EXPECT_EQ( 9, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const std::array<int, 4> a {{ 3, 1, 4, 1 }};
		std::list<int> b;
		auto ret = bksge::partial_sum(bksge::begin(a), bksge::end(a), std::back_inserter(b), bksge::minus<>());
		(void)ret;
		auto it = b.begin();
		EXPECT_EQ( 3, *it++);
		EXPECT_EQ( 2, *it++);
		EXPECT_EQ(-2, *it++);
		EXPECT_EQ(-3, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const bksge::vector<int> a { -3, 2, -5 };
		std::array<int, 4> b {{}};
		auto ret = bksge::partial_sum(bksge::begin(a), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 3));
		EXPECT_EQ(-3, b[0]);
		EXPECT_EQ(-1, b[1]);
		EXPECT_EQ(-6, b[2]);
		EXPECT_EQ( 0, b[3]);
	}
	{
		const std::list<int> a { 2, 2, 2, 2, 2 };
		bksge::vector<int> b;
		auto ret = bksge::partial_sum(bksge::begin(a), bksge::end(a), std::back_inserter(b));
		(void)ret;
		EXPECT_EQ( 2, b[0]);
		EXPECT_EQ( 4, b[1]);
		EXPECT_EQ( 6, b[2]);
		EXPECT_EQ( 8, b[3]);
		EXPECT_EQ(10, b[4]);
	}
	{
		bksge::vector<int> a { 2, 2, 2, 2, 2 };
		auto ret = bksge::partial_sum(bksge::begin(a), bksge::end(a), bksge::begin(a), bksge::multiplies<>());
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 5));
		EXPECT_EQ( 2, a[0]);
		EXPECT_EQ( 4, a[1]);
		EXPECT_EQ( 8, a[2]);
		EXPECT_EQ(16, a[3]);
		EXPECT_EQ(32, a[4]);
	}
	{
		const bksge::vector<int> a;
		std::array<int, 3> b {{ 1, 2, 3 }};
		auto ret = bksge::partial_sum(bksge::begin(a), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 0));
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(3, b[2]);
	}
}
