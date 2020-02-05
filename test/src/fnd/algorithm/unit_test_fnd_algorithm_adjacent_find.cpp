/**
 *	@file	unit_test_fnd_algorithm_adjacent_find.cpp
 *
 *	@brief	adjacent_find のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/adjacent_find.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/functional/greater.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace adjacent_find_test
{

BKSGE_CONSTEXPR bool pred1(int x, int y)
{
	return x < y;
}

struct pred2
{
	BKSGE_CONSTEXPR bool operator()(int x, int y) const
	{
		return x >= y;
	}
};

GTEST_TEST(AlgorithmTest, AdjacentFindTest)
{
	{
		BKSGE_STATIC_CONSTEXPR int a[] { 1,4,3,3,1,2,2 };
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::adjacent_find(bksge::begin(a), bksge::end(a));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(it == bksge::next(bksge::begin(a), 2));
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<int, 3> a {{ 1,1,1 }};
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = bksge::adjacent_find(bksge::begin(a), bksge::end(a));
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it == bksge::next(bksge::begin(a), 0));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] { 1,4,3,5,3,1,2 };
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::adjacent_find(bksge::begin(a), bksge::end(a));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(it == bksge::end(a));
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<int, 9> a {{ 9,8,5,3,2,1,3,4,5 }};
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = bksge::adjacent_find(bksge::begin(a), bksge::end(a), pred1);
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it == bksge::next(bksge::begin(a), 5));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] { 1,2,3,4,3,2,5 };
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::adjacent_find(bksge::begin(a), bksge::end(a), pred2());
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(it == bksge::next(bksge::begin(a), 3));
	}
	{
		const std::vector<int> a;
		auto const it = bksge::adjacent_find(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		const std::vector<int> a {1,1,2,2,3,3};
		auto const it = bksge::adjacent_find(bksge::begin(a), bksge::end(a), [](int x, int y) { return x != y; });
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 1));
	}
	{
		const std::list<int> a;
		auto const it = bksge::adjacent_find(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		const std::list<int> a {1,2,2,3,7,7,5,4,3};
		auto const it = bksge::adjacent_find(bksge::begin(a), bksge::end(a), bksge::greater<>());
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 5));
	}
}

}	// namespace adjacent_find_test

}	// namespace bksge_algorithm_test
