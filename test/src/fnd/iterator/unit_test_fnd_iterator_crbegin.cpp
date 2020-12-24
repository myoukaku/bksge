/**
 *	@file	unit_test_fnd_iterator_crbegin.cpp
 *
 *	@brief	crbegin のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/crbegin.hpp>
#include <bksge/fnd/vector.hpp>
#include <list>
#include <array>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, CRBeginTest)
{
	{
		bksge::vector<float> v;
		{
			auto it = bksge::crbegin(v);
			(void)it;
		}
	}
	{
		std::list<int> l;
		{
			auto it = bksge::crbegin(l);
			(void)it;
		}
	}

	BKSGE_STATIC_CONSTEXPR int a[] = {0,1,2};
	BKSGE_STATIC_CONSTEXPR std::array<float, 2> a2{{0.5f, 1.5f}};
	bksge::vector<float> v {3, 1, 4, 1, 5};
	std::list<int> l {6, 7, 8};

	EXPECT_TRUE(&*bksge::crbegin(a) == &a[2]);
	EXPECT_TRUE(bksge::crbegin(a2) == a2.crbegin());
	EXPECT_TRUE(bksge::crbegin(v) == v.crbegin());
	EXPECT_TRUE(bksge::crbegin(l) == l.crbegin());

	{
		auto it = bksge::crbegin(a);
		EXPECT_EQ(2, *it);
	}
	{
		auto it = bksge::crbegin(a2);
		EXPECT_EQ(1.5f, *it);
	}
	{
		auto it = bksge::crbegin(v);
		EXPECT_EQ(5, *it);
	}
	{
		auto it = bksge::crbegin(l);
		EXPECT_EQ(8, *it);
	}
}
