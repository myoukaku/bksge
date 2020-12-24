/**
 *	@file	unit_test_fnd_algorithm_partition_point.cpp
 *
 *	@brief	partition_point のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/partition_point.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/vector.hpp>
#include <list>
#include <array>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace partition_point_test
{

BKSGE_CONSTEXPR bool pred1(int x)
{
	return (x % 2) == 0;
}

struct pred2
{
	BKSGE_CONSTEXPR bool operator()(int x) const
	{
		return x > 2;
	}
};

GTEST_TEST(AlgorithmTest, PartitionPointTest)
{
	{
		const int a[] { 4,2,3,1,5};
		auto ret = bksge::partition_point(bksge::begin(a), bksge::end(a), pred1);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 2));
	}
	{
		const int a[] { 5,7,3,1 };
		auto ret = bksge::partition_point(bksge::begin(a), bksge::end(a), pred1);
		EXPECT_TRUE(ret == bksge::begin(a));
	}
	{
		const int a[] { 8,2,0,4,2 };
		auto ret = bksge::partition_point(bksge::begin(a), bksge::end(a), pred1);
		EXPECT_TRUE(ret == bksge::end(a));
	}
	{
		const std::array<int, 5> a {{ 5,3,4,1,2 }};
		auto ret = bksge::partition_point(bksge::begin(a), bksge::end(a), pred2());
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 3));
	}
	{
		const bksge::vector<int> a { 5,3,1,4,2 };
		auto ret = bksge::partition_point(bksge::begin(a), bksge::end(a), [](int x){ return (x % 2) == 1; });
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 3));
	}
	{
		const std::list<int> a { 1,5,3,2,4 };
		auto ret = bksge::partition_point(bksge::begin(a), bksge::end(a), [](int x){ return x < 2; });
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 1));
	}
	{
		const bksge::vector<int> a;
		auto ret = bksge::partition_point(bksge::begin(a), bksge::end(a), pred1);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
	}
	{
		const std::list<int> a;
		auto ret = bksge::partition_point(bksge::begin(a), bksge::end(a), pred2());
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
	}
}

}	// namespace partition_point_test

}	// namespace bksge_algorithm_test
