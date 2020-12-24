/**
 *	@file	unit_test_fnd_algorithm_partition_copy.cpp
 *
 *	@brief	partition_copy のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/partition_copy.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/vector.hpp>
#include <iterator>
#include <list>
#include <array>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace partition_copy_test
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

GTEST_TEST(AlgorithmTest, PartitionCopyTest)
{
	{
		const int a[] {1,2,3,4,5};
		int b[5] {};
		int c[5] {};
		auto ret = bksge::partition_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::begin(c), pred1);
		EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(b), 2));
		EXPECT_TRUE(ret.second == bksge::next(bksge::begin(c), 3));

		EXPECT_EQ(2, b[0]);
		EXPECT_EQ(4, b[1]);
		EXPECT_EQ(0, b[2]);
		EXPECT_EQ(0, b[3]);
		EXPECT_EQ(0, b[4]);
		EXPECT_EQ(1, c[0]);
		EXPECT_EQ(3, c[1]);
		EXPECT_EQ(5, c[2]);
		EXPECT_EQ(0, c[3]);
		EXPECT_EQ(0, c[4]);
	}
	{
		const std::array<int, 5> a {{1,2,3,4,5}};
		bksge::vector<int> b(5);
		std::list<int> c(5);
		auto ret = bksge::partition_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::begin(c), pred2());
		EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(b), 3));
		EXPECT_TRUE(ret.second == bksge::next(bksge::begin(c), 2));

		EXPECT_EQ(3, b[0]);
		EXPECT_EQ(4, b[1]);
		EXPECT_EQ(5, b[2]);
		EXPECT_EQ(0, b[3]);
		EXPECT_EQ(0, b[4]);
		auto it = c.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(0, *it++);
		EXPECT_EQ(0, *it++);
		EXPECT_EQ(0, *it++);
		EXPECT_TRUE(it == c.end());
	}
	{
		const std::list<int> a {1,2,3,4,5};
		bksge::vector<int> b;
		std::array<int, 5> c{{}};
		auto ret = bksge::partition_copy(
			bksge::begin(a),
			bksge::end(a),
			std::back_inserter(b),
			bksge::begin(c),
			[](int x) { return (x % 2) == 1; });
		//EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(b), 3));
		EXPECT_TRUE(ret.second == bksge::next(bksge::begin(c), 2));

		EXPECT_EQ(3u, b.size());
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(5, b[2]);
		EXPECT_EQ(2, c[0]);
		EXPECT_EQ(4, c[1]);
		EXPECT_EQ(0, c[2]);
		EXPECT_EQ(0, c[3]);
		EXPECT_EQ(0, c[4]);
	}
	{
		const bksge::vector<int> a;
		bksge::vector<int> b;
		std::list<int> c;
		auto ret = bksge::partition_copy(
			bksge::begin(a),
			bksge::end(a),
			std::back_inserter(b),
			std::back_inserter(c),
			[](int x) { return (x % 2) == 1; });
		(void)ret;
		//EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(b), 3));
		//EXPECT_TRUE(ret.second == bksge::next(bksge::begin(c), 2));

		EXPECT_TRUE(b.empty());
		EXPECT_TRUE(c.empty());
	}
}

}	// namespace partition_copy_test

}	// namespace bksge_algorithm_test
