/**
 *	@file	unit_test_fnd_algorithm_binary_search.cpp
 *
 *	@brief	binary_search のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/binary_search.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <array>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace binary_search_test
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

GTEST_TEST(AlgorithmTest, BinarySearchTest)
{
	{
		const int a[] { 1,2,3,4,5 };
		EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 1));
		EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 4));
		EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 5));
		EXPECT_FALSE(bksge::binary_search(bksge::begin(a), bksge::end(a), 0));
		EXPECT_FALSE(bksge::binary_search(bksge::begin(a), bksge::end(a), 6));
	}
	{
		const int a[] { 1,1,2,3,3,3,4,4,5 };
		EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 1, pred1));
		EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 2, pred1));
		EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 3, pred1));
		EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 4, pred1));
		EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 5, pred1));
		EXPECT_FALSE(bksge::binary_search(bksge::begin(a), bksge::end(a), 0, pred1));
		EXPECT_FALSE(bksge::binary_search(bksge::begin(a), bksge::end(a), 6, pred1));
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<int,5> a {{ 3,1,4,6,5 }};
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 4));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::binary_search(bksge::begin(a), bksge::end(a), 0));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::binary_search(bksge::begin(a), bksge::end(a), 6));
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<int,5> a {{ 5,4,3,2,1 }};
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 1, pred2()));
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 2, pred2()));
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 3, pred2()));
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 4, pred2()));
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 5, pred2()));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::binary_search(bksge::begin(a), bksge::end(a), 0, pred2()));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::binary_search(bksge::begin(a), bksge::end(a), 6, pred2()));
	}
	{
		const bksge::vector<int> a { 1,2,3,4,5 };
		EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 1, [](int x, int y) { return x < y; }));
		EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 2, [](int x, int y) { return x < y; }));
		EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 3, [](int x, int y) { return x < y; }));
		EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 4, [](int x, int y) { return x < y; }));
		EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 5, [](int x, int y) { return x < y; }));
		EXPECT_FALSE(bksge::binary_search(bksge::begin(a), bksge::end(a), 0, [](int x, int y) { return x < y; }));
		EXPECT_FALSE(bksge::binary_search(bksge::begin(a), bksge::end(a), 6, [](int x, int y) { return x < y; }));
	}
	{
		const bksge::list<int> a { 5,3,3,2,0 };
		EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 0, [](int x, int y) { return x > y; }));
		EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 2, [](int x, int y) { return x > y; }));
		EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 3, [](int x, int y) { return x > y; }));
		EXPECT_TRUE (bksge::binary_search(bksge::begin(a), bksge::end(a), 5, [](int x, int y) { return x > y; }));
		EXPECT_FALSE(bksge::binary_search(bksge::begin(a), bksge::end(a), 1, [](int x, int y) { return x > y; }));
		EXPECT_FALSE(bksge::binary_search(bksge::begin(a), bksge::end(a), 4, [](int x, int y) { return x > y; }));
	}
	{
		const bksge::vector<int> a;
		EXPECT_FALSE(bksge::binary_search(bksge::begin(a), bksge::end(a), 0));
		EXPECT_FALSE(bksge::binary_search(bksge::begin(a), bksge::end(a), 1));
		EXPECT_FALSE(bksge::binary_search(bksge::begin(a), bksge::end(a), 2));
	}
	{
		const bksge::list<int> a;
		EXPECT_FALSE(bksge::binary_search(bksge::begin(a), bksge::end(a), 0, [](int x, int y) { return x < y; }));
		EXPECT_FALSE(bksge::binary_search(bksge::begin(a), bksge::end(a), 1, [](int x, int y) { return x < y; }));
		EXPECT_FALSE(bksge::binary_search(bksge::begin(a), bksge::end(a), 2, [](int x, int y) { return x < y; }));
	}
}

}	// namespace binary_search_test

}	// namespace bksge_algorithm_test
