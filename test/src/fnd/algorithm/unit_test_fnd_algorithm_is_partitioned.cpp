/**
 *	@file	unit_test_fnd_algorithm_is_partitioned.cpp
 *
 *	@brief	is_partitioned のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/is_partitioned.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <array>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace is_partitioned_test
{

BKSGE_CONSTEXPR bool pred1(int x)
{
	return (x % 2) == 0;
}

struct pred2
{
	BKSGE_CONSTEXPR bool operator()(int x) const
	{
		return x > 3;
	}
};

GTEST_TEST(AlgorithmTest, IsPartitionedTest)
{
	{
		BKSGE_STATIC_CONSTEXPR int a[] {1,2,3,4,5,6,7,8,9};
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::is_partitioned(bksge::begin(a), bksge::end(a), pred1));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] {2,4,6,8,1,3,5,7,9};
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::is_partitioned(bksge::begin(a), bksge::end(a), pred1));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] {3,3,3};
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::is_partitioned(bksge::begin(a), bksge::end(a), pred2()));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] {4,4,4};
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::is_partitioned(bksge::begin(a), bksge::end(a), pred2()));
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<int, 5> a {{4,2,3,1,5}};
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(bksge::is_partitioned(bksge::begin(a), bksge::end(a), pred1));
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<int, 5> a {{4,2,3,1,5}};
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::is_partitioned(bksge::begin(a), bksge::end(a), pred2()));
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<int, 3> a {{1,2,3}};
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(bksge::is_partitioned(bksge::begin(a), bksge::end(a), pred2()));
	}
	{
		const bksge::vector<int> a {1,2,3};
		EXPECT_FALSE(bksge::is_partitioned(bksge::begin(a), bksge::end(a), pred1));
	}
	{
		const bksge::vector<int> a {1,3,2};
		EXPECT_TRUE(bksge::is_partitioned(bksge::begin(a), bksge::end(a), [](int x) { return (x % 2) == 1; }));
	}
	{
		const bksge::vector<int> a {1,2,3};
		EXPECT_TRUE(bksge::is_partitioned(bksge::begin(a), bksge::end(a), pred2()));
	}
	{
		const bksge::vector<int> a {1,3,2};
		EXPECT_FALSE(bksge::is_partitioned(bksge::begin(a), bksge::end(a), [](int x) { return x > 2; }));
	}
	{
		const bksge::list<int> a {1,2,3};
		EXPECT_FALSE(bksge::is_partitioned(bksge::begin(a), bksge::end(a), pred1));
	}
	{
		const bksge::list<int> a {1,3,2};
		EXPECT_TRUE(bksge::is_partitioned(bksge::begin(a), bksge::end(a), [](int x) { return (x % 2) == 1; }));
	}
	{
		const bksge::list<int> a {1,2,3};
		EXPECT_TRUE(bksge::is_partitioned(bksge::begin(a), bksge::end(a), pred2()));
	}
	{
		const bksge::list<int> a {1,3,2};
		EXPECT_FALSE(bksge::is_partitioned(bksge::begin(a), bksge::end(a), [](int x) { return x > 2; }));
	}
}

}	// namespace is_partitioned_test

}	// namespace bksge_algorithm_test
