/**
 *	@file	unit_test_fnd_numeric_iota.cpp
 *
 *	@brief	iota のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/numeric/iota.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <array>
#include <vector>
#include <bksge/fnd/list.hpp>
#include <gtest/gtest.h>

GTEST_TEST(NumericTest, IotaTest)
{
	{
		int a[5];
		bksge::iota(bksge::begin(a), bksge::end(a), 0);
		EXPECT_EQ(0, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(4, a[4]);
	}
	{
		std::array<int, 4> a;
		bksge::iota(bksge::begin(a), bksge::end(a), -2);
		EXPECT_EQ(-2, a[0]);
		EXPECT_EQ(-1, a[1]);
		EXPECT_EQ( 0, a[2]);
		EXPECT_EQ( 1, a[3]);
	}
	{
		std::vector<int> a(6);
		bksge::iota(bksge::begin(a), bksge::end(a), -1);
		EXPECT_EQ(-1, a[0]);
		EXPECT_EQ( 0, a[1]);
		EXPECT_EQ( 1, a[2]);
		EXPECT_EQ( 2, a[3]);
		EXPECT_EQ( 3, a[4]);
		EXPECT_EQ( 4, a[5]);
	}
	{
		bksge::list<int> a(3);
		bksge::iota(bksge::begin(a), bksge::end(a), 1);
		auto it = a.begin();
		EXPECT_EQ( 1, *it++);
		EXPECT_EQ( 2, *it++);
		EXPECT_EQ( 3, *it++);
		EXPECT_TRUE(it == a.end());
	}
}
