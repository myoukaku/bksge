/**
 *	@file	unit_test_fnd_iterator_cend.cpp
 *
 *	@brief	cend のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/cend.hpp>
#include <bksge/fnd/iterator/cbegin.hpp>
#include <array>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, CEndTest)
{
	BKSGE_STATIC_CONSTEXPR int a[] = {0,1,2};
	bksge::vector<float> v {3,1,4,1,5};
	std::array<float, 2> a2{{0.5f, 1.5f}};

	{
		BKSGE_CONSTEXPR auto it = bksge::cend(a);
		(void)it;
	}
	{
		auto it = bksge::cend(v);
		(void)it;
	}
	{
		auto it = bksge::cend(a2);
		(void)it;
	}

	//BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::cend(a) == &a[3]);
	EXPECT_TRUE(bksge::cend(v) == v.cend());
	EXPECT_TRUE(bksge::cend(a2) == a2.cend());

	{
		auto it = bksge::cbegin(a);
		EXPECT_EQ(0, *it);
		EXPECT_TRUE(it != bksge::cend(a));
		++it;
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it != bksge::cend(a));
		++it;
		EXPECT_EQ(2, *it);
		EXPECT_TRUE(it != bksge::cend(a));
		++it;
		EXPECT_TRUE(it == bksge::cend(a));
	}
	{
		auto it = bksge::cbegin(v);
		EXPECT_EQ(3, *it);
		EXPECT_TRUE(it != bksge::cend(v));
		++it;
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it != bksge::cend(v));
		++it;
		EXPECT_EQ(4, *it);
		EXPECT_TRUE(it != bksge::cend(v));
		++it;
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it != bksge::cend(v));
		++it;
		EXPECT_EQ(5, *it);
		EXPECT_TRUE(it != bksge::cend(v));
		++it;
		EXPECT_TRUE(it == bksge::cend(v));
	}
	{
		auto it = bksge::cbegin(a2);
		EXPECT_EQ(0.5f, *it);
		EXPECT_TRUE(it != bksge::cend(a2));
		++it;
		EXPECT_EQ(1.5f, *it);
		EXPECT_TRUE(it != bksge::cend(a2));
		++it;
		EXPECT_TRUE(it == bksge::cend(a2));
	}
}
