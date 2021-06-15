/**
 *	@file	unit_test_fnd_iterator_cbegin.cpp
 *
 *	@brief	cbegin のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/cbegin.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, CBeginTest)
{
	BKSGE_STATIC_CONSTEXPR int a[] = {0,1,2};
	bksge::vector<float> v {3,1,4,1,5};
	bksge::array<float, 2> a2{{0.5f, 1.5f}};

	{
		BKSGE_CONSTEXPR auto it = bksge::cbegin(a);
		(void)it;
	}
	{
		auto it = bksge::cbegin(v);
		(void)it;
	}
	{
		auto it = bksge::cbegin(a2);
		(void)it;
	}

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::cbegin(a) == &a[0]);
	                EXPECT_TRUE(bksge::cbegin(v) == v.cbegin());
	                EXPECT_TRUE(bksge::cbegin(a2) == a2.cbegin());

	BKSGE_CONSTEXPR_EXPECT_EQ(0, *bksge::cbegin(a));
	                EXPECT_EQ(3, *bksge::cbegin(v));
	                EXPECT_EQ(0.5f, *bksge::cbegin(a2));

	{
		auto it = bksge::cbegin(a);
		EXPECT_EQ(0, *it);
		++it;
		EXPECT_EQ(1, *it);
		++it;
		EXPECT_EQ(2, *it);
		++it;
	}
	{
		auto it = bksge::cbegin(v);
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
		auto it = bksge::cbegin(a2);
		EXPECT_EQ(0.5f, *it);
		++it;
		EXPECT_EQ(1.5f, *it);
		++it;
	}
}
