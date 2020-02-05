/**
 *	@file	unit_test_fnd_iterator_end.cpp
 *
 *	@brief	end のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <vector>
#include <array>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, EndTest)
{
	BKSGE_STATIC_CONSTEXPR int a[] = {0,1,2};
	std::vector<float> v {3,1,4,1,5};
	std::array<float, 2> a2{{0.5f, 1.5f}};

	{
		BKSGE_CONSTEXPR auto it = bksge::end(a);
		(void)it;
	}
	{
		auto it = bksge::end(v);
		(void)it;
	}
	{
		auto it = bksge::end(a2);
		(void)it;
	}

	//BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::end(a) == &a[3]);
	EXPECT_TRUE(bksge::end(v) == v.end());
	EXPECT_TRUE(bksge::end(a2) == a2.end());

	{
		auto it = bksge::begin(a);
		EXPECT_EQ(0, *it);
		EXPECT_TRUE(it != bksge::end(a));
		++it;
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it != bksge::end(a));
		++it;
		EXPECT_EQ(2, *it);
		EXPECT_TRUE(it != bksge::end(a));
		++it;
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		auto it = bksge::begin(v);
		EXPECT_EQ(3, *it);
		EXPECT_TRUE(it != bksge::end(v));
		++it;
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it != bksge::end(v));
		++it;
		EXPECT_EQ(4, *it);
		EXPECT_TRUE(it != bksge::end(v));
		++it;
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it != bksge::end(v));
		++it;
		EXPECT_EQ(5, *it);
		EXPECT_TRUE(it != bksge::end(v));
		++it;
		EXPECT_TRUE(it == bksge::end(v));
	}
	{
		auto it = bksge::begin(a2);
		EXPECT_EQ(0.5f, *it);
		EXPECT_TRUE(it != bksge::end(a2));
		++it;
		EXPECT_EQ(1.5f, *it);
		EXPECT_TRUE(it != bksge::end(a2));
		++it;
		EXPECT_TRUE(it == bksge::end(a2));
	}
}
