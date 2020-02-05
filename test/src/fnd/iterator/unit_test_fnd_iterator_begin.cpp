/**
 *	@file	unit_test_fnd_iterator_begin.cpp
 *
 *	@brief	begin のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/begin.hpp>
#include <vector>
#include <array>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, BeginTest)
{
	BKSGE_STATIC_CONSTEXPR int a[] = {0,1,2};
	std::vector<float> v {3,1,4,1,5};
	std::array<float, 2> a2{{0.5f, 1.5f}};

	{
		BKSGE_CONSTEXPR auto it = bksge::begin(a);
		(void)it;
	}
	{
		auto it = bksge::begin(v);
		(void)it;
	}
	{
		auto it = bksge::begin(a2);
		(void)it;
	}

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::begin(a) == &a[0]);
	                EXPECT_TRUE(bksge::begin(v) == v.begin());
	                EXPECT_TRUE(bksge::begin(a2) == a2.begin());

	BKSGE_CONSTEXPR_EXPECT_EQ(0, *bksge::begin(a));
	                EXPECT_EQ(3, *bksge::begin(v));
	                EXPECT_EQ(0.5f, *bksge::begin(a2));

	{
		auto it = bksge::begin(a);
		EXPECT_EQ(0, *it);
		++it;
		EXPECT_EQ(1, *it);
		++it;
		EXPECT_EQ(2, *it);
		++it;
	}
	{
		auto it = bksge::begin(v);
		EXPECT_EQ(3, *it);
		++it;
		EXPECT_EQ(1, *it);
		++it;
		EXPECT_EQ(4, *it);
		++it;
		EXPECT_EQ(1, *it);
		++it;
		EXPECT_EQ(5, *it);
		++it;
	}
	{
		auto it = bksge::begin(a2);
		EXPECT_EQ(0.5f, *it);
		++it;
		EXPECT_EQ(1.5f, *it);
		++it;
	}
}
