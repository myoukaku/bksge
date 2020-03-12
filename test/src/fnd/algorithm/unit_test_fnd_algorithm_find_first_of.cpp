/**
 *	@file	unit_test_fnd_algorithm_find_first_of.cpp
 *
 *	@brief	find_first_of のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/find_first_of.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/list.hpp>
#include <vector>
#include <gtest/gtest.h>
#include <array>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace find_first_of_test
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

GTEST_TEST(AlgorithmTest, FindFirstOfTest)
{
	{
		BKSGE_STATIC_CONSTEXPR int a[] { 1, 3, 7, 4, 2 };
		BKSGE_STATIC_CONSTEXPR int b[] { 2, 4, 6, 8 };
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::find_first_of(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(it, bksge::next(bksge::begin(a), 3));
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(4, *it);
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] { 1, 3, 7, 4, 2 };
		BKSGE_STATIC_CONSTEXPR int b[] { 2, 4, 6, 8 };
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::find_first_of(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), pred1);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(it, bksge::next(bksge::begin(a), 0));
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1, *it);
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] { 1, 3, 7, 4, 2 };
		BKSGE_STATIC_CONSTEXPR int b[] { 2, 4, 6, 8 };
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::find_first_of(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), pred2());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(it, bksge::next(bksge::begin(a), 1));
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3, *it);
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] { 1, 3, 7, 4, 2 };
		BKSGE_STATIC_CONSTEXPR std::array<int, 2> b {{ 6, 8 }};
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = bksge::find_first_of(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(it, bksge::end(a));
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<int, 5> a {{ 1, 3, 5, 7, 9 }};
		BKSGE_STATIC_CONSTEXPR int b[] { 3, 1 };
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = bksge::find_first_of(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(it, bksge::next(bksge::begin(a), 0));
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(1, *it);
	}
	{
		const std::vector<int> a { 1, 3, 7, 4, 2 };
		const bksge::list<int> b { 2, 4, 6, 8 };
		auto it = bksge::find_first_of(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_EQ(it, bksge::next(bksge::begin(a), 3));
		EXPECT_EQ(4, *it);
	}
	{
		const bksge::list<int> a { 1, 3, 7, 4, 2 };
		const int b[] { 2, 4, 6, 8 };
		auto it = bksge::find_first_of(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), pred1);
		EXPECT_EQ(it, bksge::next(bksge::begin(a), 0));
		EXPECT_EQ(1, *it);
	}
	{
		const int a[] { 1, 3, 7, 4, 2 };
		const std::vector<int> b { 2, 4, 6, 8 };
		auto it = bksge::find_first_of(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), pred2());
		EXPECT_EQ(it, bksge::next(bksge::begin(a), 1));
		EXPECT_EQ(3, *it);
	}
	{
		const bksge::list<int> a {1,2,3,4,5,6,7};
		const bksge::list<int> b {5};
		auto it = bksge::find_first_of(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), [](int x, int y) { return x > y; });
		EXPECT_EQ(it, bksge::next(bksge::begin(a), 5));
		EXPECT_EQ(6, *it);
	}
	{
		const bksge::list<int> a { 1, 3, 7, 4, 2 };
		const std::vector<int> b;
		auto it = bksge::find_first_of(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_EQ(it, bksge::end(a));
	}
	{
		const std::vector<int> a;
		const bksge::list<int> b { 2, 4, 6, 8 };
		auto it = bksge::find_first_of(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_EQ(it, bksge::end(a));
	}
	{
		const bksge::list<int> a;
		const bksge::list<int> b;
		auto it = bksge::find_first_of(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_EQ(it, bksge::end(a));
	}
	{
		const bksge::list<int> a;
		const bksge::list<int> b;
		auto it = bksge::find_first_of(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), [](int , int ){ return true; });
		EXPECT_EQ(it, bksge::end(a));
	}
}

}	// namespace find_first_of_test

}	// namespace bksge_algorithm_test
