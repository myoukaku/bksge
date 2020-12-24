/**
 *	@file	unit_test_fnd_iterator_crend.cpp
 *
 *	@brief	crend のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/crend.hpp>
#include <bksge/fnd/iterator/crbegin.hpp>
#include <bksge/fnd/vector.hpp>
#include <array>
#include <list>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, CREndTest)
{
	{
		bksge::vector<float> v;
		{
			auto it1 = bksge::crbegin(v);
			auto it2 = bksge::crend(v);
			EXPECT_TRUE(it1 == it2);
		}
	}
	{
		std::list<int> l;
		{
			auto it1 = bksge::crbegin(l);
			auto it2 = bksge::crend(l);
			EXPECT_TRUE(it1 == it2);
		}
	}

	BKSGE_STATIC_CONSTEXPR int a[] = {0,1,2};
	BKSGE_STATIC_CONSTEXPR std::array<float, 2> a2{{0.5f, 1.5f}};
	bksge::vector<float> v {3,1,4,1,5};
	std::list<int> l {6, 7, 8};

//	EXPECT_TRUE(&*bksge::crend(a) == &a[-1]);
	EXPECT_TRUE(bksge::crend(a2) == a2.crend());
	EXPECT_TRUE(bksge::crend(v) == v.crend());
	EXPECT_TRUE(bksge::crend(l) == l.crend());

	{
		auto it = bksge::crbegin(a);
		EXPECT_TRUE(it != bksge::crend(a));
		++it;
		EXPECT_TRUE(it != bksge::crend(a));
		++it;
		EXPECT_TRUE(it != bksge::crend(a));
		++it;
		EXPECT_TRUE(it == bksge::crend(a));
	}
	{
		auto it = bksge::crbegin(a2);
		EXPECT_TRUE(it != bksge::crend(a2));
		++it;
		EXPECT_TRUE(it != bksge::crend(a2));
		++it;
		EXPECT_TRUE(it == bksge::crend(a2));
	}
	{
		auto it = bksge::crbegin(v);
		EXPECT_TRUE(it != bksge::crend(v));
		++it;
		EXPECT_TRUE(it != bksge::crend(v));
		++it;
		EXPECT_TRUE(it != bksge::crend(v));
		++it;
		EXPECT_TRUE(it != bksge::crend(v));
		++it;
		EXPECT_TRUE(it != bksge::crend(v));
		++it;
		EXPECT_TRUE(it == bksge::crend(v));
	}
	{
		auto it = bksge::crbegin(l);
		EXPECT_TRUE(it != bksge::crend(l));
		++it;
		EXPECT_TRUE(it != bksge::crend(l));
		++it;
		EXPECT_TRUE(it != bksge::crend(l));
		++it;
		EXPECT_TRUE(it == bksge::crend(l));
	}
}
