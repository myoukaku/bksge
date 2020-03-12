/**
 *	@file	unit_test_fnd_algorithm_is_unique.cpp
 *
 *	@brief	is_unique のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/list.hpp>
#include <vector>
#include <gtest/gtest.h>
#include <array>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace is_unique_test
{

GTEST_TEST(AlgorithmTest, IsUniqueTest)
{
	{
		BKSGE_STATIC_CONSTEXPR int a[] { 2,5,3,3,1,2,4,2,1,1,4,4,3,3,3 };
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] { 2,5,3,1,2,4,2,1,4,3 };
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] { 1,1,2,2,2,3,3,4,4,5 };
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] { 1,2,3,4,5 };
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<int, 15> a {{ 2,5,3,3,1,2,4,2,1,1,4,4,3,3,3 }};
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<int, 10> a {{ 2,5,3,1,2,4,2,1,4,3 }};
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<int, 10> a {{ 1,1,2,2,2,3,3,4,4,5 }};
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<int, 5> a {{ 1,2,3,4,5 }};
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		std::vector<int> a;
		EXPECT_TRUE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		std::vector<int> a { 1 };
		EXPECT_TRUE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		std::vector<int> a { 1, 1 };
		EXPECT_FALSE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		std::vector<int> a { 1, 2 };
		EXPECT_TRUE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		std::vector<int> a { 1, 2, 1 };
		EXPECT_TRUE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		std::vector<int> a { 1, 1, 2 };
		EXPECT_FALSE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		std::vector<int> a { 1, 2, 2 };
		EXPECT_FALSE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		std::vector<int> a { 1, 2, 3, 4 };
		EXPECT_TRUE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		std::vector<int> a { 1, 2, 3, 3 };
		EXPECT_FALSE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		std::vector<int> a { 1, 2, 3, 1 };
		EXPECT_TRUE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		std::vector<int> a { 3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5,0,2,8,8 };
		EXPECT_FALSE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		std::vector<int> a { 3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5,0,2,8,8 };
		EXPECT_FALSE(bksge::is_unique(bksge::begin(a), bksge::end(a), [](int x, int y){return x == y; }));
	}
	{
		bksge::list<float> a;
		EXPECT_TRUE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		bksge::list<float> a { 1, 2, 3, 1, 2, 3 };
		EXPECT_TRUE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		bksge::list<float> a { 1, 1, 2, 2, 3, 3 };
		EXPECT_FALSE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		bksge::list<float> a { 1, 2, 3, 4, 3, 2, 1 };
		EXPECT_TRUE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		bksge::list<float> a { 1, 2, 3, 4, 4, 3, 2, 1 };
		EXPECT_FALSE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
	{
		bksge::list<float> a { 3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5,0,2,8,8 };
		EXPECT_FALSE(bksge::is_unique(bksge::begin(a), bksge::end(a)));
	}
}

}	// namespace is_unique_test

}	// namespace bksge_algorithm_test
