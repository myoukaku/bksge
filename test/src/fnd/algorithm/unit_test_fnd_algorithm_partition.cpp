/**
 *	@file	unit_test_fnd_algorithm_partition.cpp
 *
 *	@brief	partition のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/partition.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/vector.hpp>
#include <list>
#include <array>
#include <forward_list>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace partition_test
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

GTEST_TEST(AlgorithmTest, PartitionTest)
{
	{
		int a[] {1,2,3,4,5};
		auto ret = bksge::partition(bksge::begin(a), bksge::end(a), pred1);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 2));
		EXPECT_TRUE (pred1(a[0]));
		EXPECT_TRUE (pred1(a[1]));
		EXPECT_FALSE(pred1(a[2]));
		EXPECT_FALSE(pred1(a[3]));
		EXPECT_FALSE(pred1(a[4]));
	}
	{
		int a[] {1,3,5,7};
		auto ret = bksge::partition(bksge::begin(a), bksge::end(a), pred1);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
		EXPECT_FALSE(pred1(a[0]));
		EXPECT_FALSE(pred1(a[1]));
		EXPECT_FALSE(pred1(a[2]));
		EXPECT_FALSE(pred1(a[3]));
	}
	{
		int a[] {2,4,6};
		auto ret = bksge::partition(bksge::begin(a), bksge::end(a), pred1);
		EXPECT_TRUE(ret == bksge::end(a));
		EXPECT_TRUE(pred1(a[0]));
		EXPECT_TRUE(pred1(a[1]));
		EXPECT_TRUE(pred1(a[2]));
	}
	{
		std::array<int, 5> a {{1,2,3,4,5}};
		auto ret = bksge::partition(bksge::begin(a), bksge::end(a), pred2());
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 3));
		EXPECT_TRUE (pred2()(a[0]));
		EXPECT_TRUE (pred2()(a[1]));
		EXPECT_TRUE (pred2()(a[2]));
		EXPECT_FALSE(pred2()(a[3]));
		EXPECT_FALSE(pred2()(a[4]));
	}
	{
		bksge::vector<int> a {1,2,3,4,5};
		auto ret = bksge::partition(bksge::begin(a), bksge::end(a), [](int x) { return (x % 2) == 1; });
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 3));
		EXPECT_TRUE ((a[0] % 2) == 1);
		EXPECT_TRUE ((a[1] % 2) == 1);
		EXPECT_TRUE ((a[2] % 2) == 1);
		EXPECT_TRUE ((a[3] % 2) == 0);
		EXPECT_TRUE ((a[4] % 2) == 0);
	}
	{
		std::list<int> a {1,2,3,4,5};
		auto ret = bksge::partition(bksge::begin(a), bksge::end(a), [](int x) { return x < 3; });
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 2));
		auto it = a.begin();
		EXPECT_TRUE (*it++ < 3);
		EXPECT_TRUE (*it++ < 3);
		EXPECT_FALSE(*it++ < 3);
		EXPECT_FALSE(*it++ < 3);
		EXPECT_FALSE(*it++ < 3);
		EXPECT_TRUE(it == a.end());
	}
	{
		std::forward_list<int> a {1,2,3,4,5};
		auto ret = bksge::partition(bksge::begin(a), bksge::end(a), pred1);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 2));
		auto it = a.begin();
		EXPECT_TRUE (pred1(*it++));
		EXPECT_TRUE (pred1(*it++));
		EXPECT_FALSE(pred1(*it++));
		EXPECT_FALSE(pred1(*it++));
		EXPECT_FALSE(pred1(*it++));
		EXPECT_TRUE(it == a.end());
	}
	{
		std::forward_list<int> a {1,2,3,4,5};
		auto ret = bksge::partition(bksge::begin(a), bksge::end(a), pred2());
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 3));
		auto it = a.begin();
		EXPECT_TRUE (pred2()(*it++));
		EXPECT_TRUE (pred2()(*it++));
		EXPECT_TRUE (pred2()(*it++));
		EXPECT_FALSE(pred2()(*it++));
		EXPECT_FALSE(pred2()(*it++));
		EXPECT_TRUE(it == a.end());
	}
	{
		std::forward_list<int> a {1,2,3,4,5};
		auto ret = bksge::partition(bksge::begin(a), bksge::end(a), [](int x) { return x < 2; });
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 1));
		auto it = a.begin();
		EXPECT_TRUE (*it++ < 2);
		EXPECT_FALSE(*it++ < 2);
		EXPECT_FALSE(*it++ < 2);
		EXPECT_FALSE(*it++ < 2);
		EXPECT_FALSE(*it++ < 2);
		EXPECT_TRUE(it == a.end());
	}
	{
		bksge::vector<int> a;
		auto ret = bksge::partition(bksge::begin(a), bksge::end(a), pred1);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
	}
	{
		std::list<int> a;
		auto ret = bksge::partition(bksge::begin(a), bksge::end(a), pred2());
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
	}
}

}	// namespace partition_test

}	// namespace bksge_algorithm_test
