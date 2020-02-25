/**
 *	@file	unit_test_fnd_algorithm_find.cpp
 *
 *	@brief	find のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/find.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <gtest/gtest.h>
#include <array>
#include <list>
#include <vector>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace find_test
{

GTEST_TEST(AlgorithmTest, FindTest)
{
	{
		BKSGE_STATIC_CONSTEXPR int a[] {0,1,2};
		{
			BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::find(bksge::begin(a), bksge::end(a), 0);
			BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(it == bksge::begin(a));
		}
		{
			BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::find(bksge::begin(a), bksge::end(a), 1);
			BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(it == bksge::begin(a) + 1);
		}
		{
			BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::find(bksge::begin(a), bksge::end(a), 2);
			BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(it == bksge::begin(a) + 2);
		}
		{
			BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::find(bksge::begin(a), bksge::end(a), 3);
			BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(it == bksge::end(a));
		}
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<float, 8> a{{3, 4, 4, 5, 5, 5, 3, 6}};
		{
			BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = bksge::find(bksge::begin(a), bksge::end(a), 3);
			BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it == bksge::begin(a));
		}
		{
			BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = bksge::find(bksge::begin(a), bksge::end(a), 4);
			BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it == bksge::begin(a) + 1);
		}
		{
			BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = bksge::find(bksge::begin(a), bksge::end(a), 5);
			BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it == bksge::begin(a) + 3);
		}
		{
			BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = bksge::find(bksge::begin(a), bksge::end(a), 6);
			BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it == bksge::begin(a) + 7);
		}
		{
			BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = bksge::find(bksge::begin(a), bksge::end(a), 0);
			BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it == bksge::end(a));
		}
	}
	{
		int a[] {0,1,2};
		{
			auto it = bksge::find(bksge::begin(a), bksge::end(a), 0);
			EXPECT_TRUE(it == bksge::begin(a));
			*it = 10;
		}
		{
			auto it = bksge::find(bksge::begin(a), bksge::end(a), 2);
			EXPECT_TRUE(it == bksge::begin(a) + 2);
			*it = 20;
		}
		{
			auto it = bksge::find(bksge::begin(a), bksge::end(a), 3);
			EXPECT_TRUE(it == bksge::end(a));
		}
		EXPECT_EQ(10, a[0]);
		EXPECT_EQ( 1, a[1]);
		EXPECT_EQ(20, a[2]);
	}
	{
		const std::vector<int> a {7, 8, 9};
		{
			auto it = bksge::find(bksge::begin(a), bksge::end(a), 7);
			EXPECT_TRUE(it == bksge::begin(a));
		}
		{
			auto it = bksge::find(bksge::begin(a), bksge::end(a), 8);
			EXPECT_TRUE(it == bksge::begin(a) + 1);
		}
		{
			auto it = bksge::find(bksge::begin(a), bksge::end(a), 9);
			EXPECT_TRUE(it == bksge::begin(a) + 2);
		}
		{
			auto it = bksge::find(bksge::begin(a), bksge::end(a), 10);
			EXPECT_TRUE(it == bksge::end(a));
		}
	}
	{
		const std::list<int> a {0,1,2};
		{
			auto it = bksge::find(bksge::begin(a), bksge::end(a), 0);
			EXPECT_TRUE(it == bksge::begin(a));
		}
		{
			auto it = bksge::find(bksge::begin(a), bksge::end(a), 1);
			EXPECT_TRUE(it == ++bksge::begin(a));
		}
		{
			auto it = bksge::find(bksge::begin(a), bksge::end(a), 2);
			EXPECT_TRUE(it == ++(++bksge::begin(a)));
		}
		{
			auto it = bksge::find(bksge::begin(a), bksge::end(a), -1);
			EXPECT_TRUE(it == bksge::end(a));
		}
	}
	{
		std::list<int> a {0,1,2};
		{
			auto it = bksge::find(bksge::begin(a), bksge::end(a), 1);
			EXPECT_TRUE(it == ++bksge::begin(a));
			*it = 30;
		}
		{
			auto it = bksge::find(bksge::begin(a), bksge::end(a), 3);
			EXPECT_TRUE(it == bksge::end(a));
		}
		{
			auto it = a.begin();
			EXPECT_EQ( 0, *it++);
			EXPECT_EQ(30, *it++);
			EXPECT_EQ( 2, *it++);
		}
	}
}

}	// namespace find_test

}	// namespace bksge_algorithm_test
