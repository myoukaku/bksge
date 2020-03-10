/**
 *	@file	unit_test_fnd_algorithm_count.cpp
 *
 *	@brief	count のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/count.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include <array>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace count_test
{

GTEST_TEST(AlgorithmTest, CountTest)
{
	{
		BKSGE_CONSTEXPR_OR_CONST int a[] {1, 3, 1, 2, 3, 1, 2, 2, 1};
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0, bksge::count(bksge::begin(a), bksge::end(a), 0));
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(4, bksge::count(bksge::begin(a), bksge::end(a), 1));
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3, bksge::count(bksge::begin(a), bksge::end(a), 2));
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(2, bksge::count(bksge::begin(a), bksge::end(a), 3));
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0, bksge::count(bksge::begin(a), bksge::end(a), 4));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST std::array<int, 21> a{ { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6 } };
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(0, bksge::count(bksge::begin(a), bksge::end(a), 0));
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, bksge::count(bksge::begin(a), bksge::end(a), 1));
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, bksge::count(bksge::begin(a), bksge::end(a), 2));
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(4, bksge::count(bksge::begin(a), bksge::end(a), 3));
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, bksge::count(bksge::begin(a), bksge::end(a), 4));
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(3, bksge::count(bksge::begin(a), bksge::end(a), 5));
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, bksge::count(bksge::begin(a), bksge::end(a), 6));
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(1, bksge::count(bksge::begin(a), bksge::end(a), 7));
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, bksge::count(bksge::begin(a), bksge::end(a), 8));
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(3, bksge::count(bksge::begin(a), bksge::end(a), 9));
	}
	{
		const bksge::vector<int> v{10, 20, 10, 30, 10, 20};
		EXPECT_EQ(0, bksge::count(bksge::begin(v), bksge::end(v),  0));
		EXPECT_EQ(3, bksge::count(bksge::begin(v), bksge::end(v), 10));
		EXPECT_EQ(2, bksge::count(bksge::begin(v), bksge::end(v), 20));
		EXPECT_EQ(1, bksge::count(bksge::begin(v), bksge::end(v), 30));
		EXPECT_EQ(0, bksge::count(bksge::begin(v), bksge::end(v), 40));
	}
	{
		const bksge::vector<int> v;
		EXPECT_EQ(0, bksge::count(bksge::begin(v), bksge::end(v),  0));
		EXPECT_EQ(0, bksge::count(bksge::begin(v), bksge::end(v), 10));
		EXPECT_EQ(0, bksge::count(bksge::begin(v), bksge::end(v), 20));
		EXPECT_EQ(0, bksge::count(bksge::begin(v), bksge::end(v), 30));
		EXPECT_EQ(0, bksge::count(bksge::begin(v), bksge::end(v), 40));
	}
	{
		const bksge::list<int> l{10, 20, 40, 40, 10};
		EXPECT_EQ(0, bksge::count(bksge::begin(l), bksge::end(l),  0));
		EXPECT_EQ(2, bksge::count(bksge::begin(l), bksge::end(l), 10));
		EXPECT_EQ(1, bksge::count(bksge::begin(l), bksge::end(l), 20));
		EXPECT_EQ(0, bksge::count(bksge::begin(l), bksge::end(l), 30));
		EXPECT_EQ(2, bksge::count(bksge::begin(l), bksge::end(l), 40));
	}
	{
		const bksge::list<int> l;
		EXPECT_EQ(0, bksge::count(bksge::begin(l), bksge::end(l),  0));
		EXPECT_EQ(0, bksge::count(bksge::begin(l), bksge::end(l), 10));
		EXPECT_EQ(0, bksge::count(bksge::begin(l), bksge::end(l), 20));
		EXPECT_EQ(0, bksge::count(bksge::begin(l), bksge::end(l), 30));
		EXPECT_EQ(0, bksge::count(bksge::begin(l), bksge::end(l), 40));
	}
}

}	// namespace count_test

}	// namespace bksge_algorithm_test
