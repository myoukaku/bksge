/**
 *	@file	unit_test_fnd_iterator_rend.cpp
 *
 *	@brief	rend のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/rend.hpp>
#include <bksge/fnd/iterator/rbegin.hpp>
#include <array>
#include <bksge/fnd/vector.hpp>
#include <list>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, REndTest)
{
	{
		bksge::vector<float> v;
		{
			auto it1 = bksge::rbegin(v);
			auto it2 = bksge::rend(v);
			EXPECT_TRUE(it1 == it2);
		}
	}
	{
		std::list<int> l;
		{
			auto it1 = bksge::rbegin(l);
			auto it2 = bksge::rend(l);
			EXPECT_TRUE(it1 == it2);
		}
	}

	BKSGE_STATIC_CONSTEXPR int a[] = {0,1,2};
	BKSGE_STATIC_CONSTEXPR std::array<float, 2> a2{{0.5f, 1.5f}};
	bksge::vector<float> v {3,1,4,1,5};
	std::list<int> l {6, 7, 8};

//	EXPECT_TRUE(&*bksge::rend(a) == &a[-1]);
	EXPECT_TRUE(bksge::rend(a2) == a2.rend());
	EXPECT_TRUE(bksge::rend(v) == v.rend());
	EXPECT_TRUE(bksge::rend(l) == l.rend());

	{
		auto it = bksge::rbegin(a);
		EXPECT_TRUE(it != bksge::rend(a));
		++it;
		EXPECT_TRUE(it != bksge::rend(a));
		++it;
		EXPECT_TRUE(it != bksge::rend(a));
		++it;
		EXPECT_TRUE(it == bksge::rend(a));
	}
	{
		auto it = bksge::rbegin(a2);
		EXPECT_TRUE(it != bksge::rend(a2));
		++it;
		EXPECT_TRUE(it != bksge::rend(a2));
		++it;
		EXPECT_TRUE(it == bksge::rend(a2));
	}
	{
		auto it = bksge::rbegin(v);
		EXPECT_TRUE(it != bksge::rend(v));
		++it;
		EXPECT_TRUE(it != bksge::rend(v));
		++it;
		EXPECT_TRUE(it != bksge::rend(v));
		++it;
		EXPECT_TRUE(it != bksge::rend(v));
		++it;
		EXPECT_TRUE(it != bksge::rend(v));
		++it;
		EXPECT_TRUE(it == bksge::rend(v));
	}
	{
		auto it = bksge::rbegin(l);
		EXPECT_TRUE(it != bksge::rend(l));
		++it;
		EXPECT_TRUE(it != bksge::rend(l));
		++it;
		EXPECT_TRUE(it != bksge::rend(l));
		++it;
		EXPECT_TRUE(it == bksge::rend(l));
	}
}
