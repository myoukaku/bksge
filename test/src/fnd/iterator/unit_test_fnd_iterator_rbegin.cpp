/**
 *	@file	unit_test_fnd_iterator_rbegin.cpp
 *
 *	@brief	rbegin のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/rbegin.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <array>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, RBeginTest)
{
	{
		bksge::vector<float> v;
		{
			auto it = bksge::rbegin(v);
			(void)it;
		}
	}
	{
		bksge::list<int> l;
		{
			auto it = bksge::rbegin(l);
			(void)it;
		}
	}

	BKSGE_STATIC_CONSTEXPR int a[] = {0,1,2};
	BKSGE_STATIC_CONSTEXPR std::array<float, 2> a2{{0.5f, 1.5f}};
	bksge::vector<float> v {3, 1, 4, 1, 5};
	bksge::list<int> l {6, 7, 8};

	EXPECT_TRUE(&*bksge::rbegin(a) == &a[2]);
	EXPECT_TRUE(bksge::rbegin(a2) == a2.rbegin());
	EXPECT_TRUE(bksge::rbegin(v) == v.rbegin());
	EXPECT_TRUE(bksge::rbegin(l) == l.rbegin());

	{
		auto it = bksge::rbegin(a);
		EXPECT_EQ(2, *it);
	}
	{
		auto it = bksge::rbegin(a2);
		EXPECT_EQ(1.5f, *it);
	}
	{
		auto it = bksge::rbegin(v);
		EXPECT_EQ(5, *it);
	}
	{
		auto it = bksge::rbegin(l);
		EXPECT_EQ(8, *it);
	}
}
