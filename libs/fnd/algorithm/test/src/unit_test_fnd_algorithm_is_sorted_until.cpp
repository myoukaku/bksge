/**
 *	@file	unit_test_fnd_algorithm_is_sorted_until.cpp
 *
 *	@brief	is_sorted_until のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/is_sorted_until.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace is_sorted_until_test
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

GTEST_TEST(AlgorithmTest, IsSortedUntilTest)
{
	{
		BKSGE_STATIC_CONSTEXPR int a[] {1,2,3,4,5};
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::is_sorted_until(bksge::begin(a), bksge::end(a));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(it == bksge::end(a));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] {1,2,3,4,5};
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::is_sorted_until(bksge::begin(a), bksge::end(a), pred1);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(it == bksge::end(a));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] {1,2,3,4,5};
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::is_sorted_until(bksge::begin(a), bksge::end(a), pred2());
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(it == bksge::next(bksge::begin(a), 1));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] {5,4,3,2,1};
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::is_sorted_until(bksge::begin(a), bksge::end(a), pred2());
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(it == bksge::end(a));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] {1,2,3,3,4,5};
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::is_sorted_until(bksge::begin(a), bksge::end(a));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(it == bksge::end(a));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] {3,1,4,2,5};
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::is_sorted_until(bksge::begin(a), bksge::end(a));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(it == bksge::next(bksge::begin(a), 1));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] {1};
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::is_sorted_until(bksge::begin(a), bksge::end(a));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(it == bksge::end(a));
	}
	{
		BKSGE_STATIC_CONSTEXPR bksge::array<int, 5> a {{1,2,3,5,4}};
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = bksge::is_sorted_until(bksge::begin(a), bksge::end(a));
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it == bksge::next(bksge::begin(a), 4));
	}
	{
		BKSGE_STATIC_CONSTEXPR bksge::array<int, 5> a {{1,1,3,4,2}};
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = bksge::is_sorted_until(bksge::begin(a), bksge::end(a), pred1);
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it == bksge::next(bksge::begin(a), 4));
	}
	{
		BKSGE_STATIC_CONSTEXPR bksge::array<int, 6> a {{3,5,6,8,10,13}};
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = bksge::is_sorted_until(bksge::begin(a), bksge::end(a));
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it == bksge::end(a));
	}
	{
		BKSGE_STATIC_CONSTEXPR bksge::array<int, 6> a {{13,10,8,6,4,1}};
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = bksge::is_sorted_until(bksge::begin(a), bksge::end(a), pred2());
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it == bksge::end(a));
	}
	{
		BKSGE_STATIC_CONSTEXPR bksge::array<int, 1> a {{3}};
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = bksge::is_sorted_until(bksge::begin(a), bksge::end(a), pred1);
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it == bksge::end(a));
	}
	{
		const bksge::vector<int> a {3,4,5};
		auto const it = bksge::is_sorted_until(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		const bksge::vector<int> a {3,3,4,4,5,5};
		auto const it = bksge::is_sorted_until(bksge::begin(a), bksge::end(a), [] (int x, int y) { return x < y; });
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		const bksge::vector<int> a {3,3,4,4,5,5};
		auto const it = bksge::is_sorted_until(bksge::begin(a), bksge::end(a), [] (int x, int y) { return x > y; });
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 2));
	}
	{
		const bksge::vector<int> a;
		auto const it = bksge::is_sorted_until(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		const bksge::list<int> a {5,5,4,4,3,3};
		auto const it = bksge::is_sorted_until(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 2));
	}
	{
		const bksge::list<int> a {5,5,4,4,3,3};
		auto const it = bksge::is_sorted_until(bksge::begin(a), bksge::end(a), [] (int x, int y) { return x < y; });
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 2));
	}
	{
		const bksge::list<int> a {5,5,4,4,3,3};
		auto const it = bksge::is_sorted_until(bksge::begin(a), bksge::end(a), [] (int x, int y) { return x > y; });
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		const bksge::list<int> a;
		auto const it = bksge::is_sorted_until(bksge::begin(a), bksge::end(a), pred1);
		EXPECT_TRUE(it == bksge::end(a));
	}
}

}	// namespace is_sorted_until_test

}	// namespace bksge_algorithm_test
