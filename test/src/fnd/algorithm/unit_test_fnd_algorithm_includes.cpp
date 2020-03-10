/**
 *	@file	unit_test_fnd_algorithm_includes.cpp
 *
 *	@brief	includes のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/includes.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include <array>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace includes_test
{

BKSGE_CONSTEXPR bool pred1(int x, int y)
{
	return x < y;
}

struct pred2
{
	BKSGE_CONSTEXPR bool operator()(int x, int y) const
	{
		return x > y;
	}
};

GTEST_TEST(AlgorithmTest, IncludesTest)
{
	{
		BKSGE_STATIC_CONSTEXPR int                  a[] {1,2,3,4,5,6};
		BKSGE_STATIC_CONSTEXPR int                  b[] {0,1,3};
		BKSGE_STATIC_CONSTEXPR std::array<int, 3> c  {{1,2,4}};
		BKSGE_STATIC_CONSTEXPR int                  d[] {2,4,6};
		BKSGE_STATIC_CONSTEXPR std::array<int, 3> e  {{3,5,7}};
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::includes(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b)));
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::includes(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), pred1));
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (bksge::includes(bksge::begin(a), bksge::end(a), bksge::begin(c), bksge::end(c)));
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (bksge::includes(bksge::begin(a), bksge::end(a), bksge::begin(c), bksge::end(c), pred1));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::includes(bksge::begin(a), bksge::end(a), bksge::begin(d), bksge::end(d)));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::includes(bksge::begin(a), bksge::end(a), bksge::begin(e), bksge::end(e)));
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<int, 5> a  {{10,20,30,40,50}};
		BKSGE_STATIC_CONSTEXPR std::array<int, 5> b  {{10,20,30,40,50}};
		BKSGE_STATIC_CONSTEXPR int                  c[] {10,15,20};
		BKSGE_STATIC_CONSTEXPR std::array<int, 2> d  {{ 9,10}};
		BKSGE_STATIC_CONSTEXPR int                  e[] {51};
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (bksge::includes(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b)));
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (bksge::includes(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), pred1));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::includes(bksge::begin(a), bksge::end(a), bksge::begin(c), bksge::end(c)));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::includes(bksge::begin(a), bksge::end(a), bksge::begin(c), bksge::end(c), pred1));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::includes(bksge::begin(a), bksge::end(a), bksge::begin(d), bksge::end(d)));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::includes(bksge::begin(a), bksge::end(a), bksge::begin(e), bksge::end(e)));
	}
	{
		const bksge::vector<int>   a   {9,8,7,6,5};
		const int                  b[] {9,7,5};
		const std::array<int, 3> c {{10,9,8}};
		const bksge::vector<int>   d   {9,5,4};
		const bksge::list<int>     e   {8,7,6};
		EXPECT_TRUE (bksge::includes(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), pred2()));
		EXPECT_FALSE(bksge::includes(bksge::begin(a), bksge::end(a), bksge::begin(c), bksge::end(c), pred2()));
		EXPECT_FALSE(bksge::includes(bksge::begin(a), bksge::end(a), bksge::begin(d), bksge::end(d), pred2()));
		EXPECT_TRUE (bksge::includes(bksge::begin(a), bksge::end(a), bksge::begin(e), bksge::end(e), pred2()));
	}
	{
		const bksge::list<int>     a   {90,80,70,60,50};
		const int                  b[] {90,70,50};
		const std::array<int, 3> c  {{91,90,88}};
		const bksge::vector<int>   d   {80,75,70};
		const bksge::list<int>     e   {80,70,50};
		EXPECT_TRUE (bksge::includes(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), [](int x, int y){ return x > y; }));
		EXPECT_FALSE(bksge::includes(bksge::begin(a), bksge::end(a), bksge::begin(c), bksge::end(c), [](int x, int y){ return x > y; }));
		EXPECT_FALSE(bksge::includes(bksge::begin(a), bksge::end(a), bksge::begin(d), bksge::end(d), [](int x, int y){ return x > y; }));
		EXPECT_TRUE (bksge::includes(bksge::begin(a), bksge::end(a), bksge::begin(e), bksge::end(e), [](int x, int y){ return x > y; }));
	}
}

}	// namespace includes_test

}	// namespace bksge_algorithm_test
