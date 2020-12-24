/**
 *	@file	unit_test_fnd_algorithm_merge.cpp
 *
 *	@brief	merge のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/merge.hpp>
#include <bksge/fnd/functional/greater.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/vector.hpp>
#include <iterator>
#include <list>
#include <array>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace merge_test
{

GTEST_TEST(AlgorithmTest, MergeTest)
{
	{
		const int a[] { 1, 2, 3, 4 };
		const std::array<int, 4> b {{ 3, 4, 5, 6 }};
		int c[8];
		auto ret = bksge::merge(
			bksge::begin(a), bksge::end(a),
			bksge::begin(b), bksge::end(b),
			bksge::begin(c));

		EXPECT_TRUE(ret == bksge::next(bksge::begin(c), 8));

		EXPECT_EQ(1, c[0]);
		EXPECT_EQ(2, c[1]);
		EXPECT_EQ(3, c[2]);
		EXPECT_EQ(3, c[3]);
		EXPECT_EQ(4, c[4]);
		EXPECT_EQ(4, c[5]);
		EXPECT_EQ(5, c[6]);
		EXPECT_EQ(6, c[7]);
	}
	{
		const std::array<int, 4> a {{ 6, 5, 2, 1 }};
		const bksge::vector<int> b { 5, 3, 1 };
		std::list<int> c;
		auto ret = bksge::merge(
			bksge::begin(a), bksge::end(a),
			bksge::begin(b), bksge::end(b),
			std::back_inserter(c),
			bksge::greater<>());

		(void)ret;

		auto it = c.begin();
		EXPECT_EQ(6, *it++);
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it == c.end());
	}
	{
		const int a[] { 1, 2, 3 };
		const std::list<int> b { 1, 2, 3 };
		bksge::vector<int> c;
		auto ret = bksge::merge(
			bksge::begin(a), bksge::end(a),
			bksge::begin(b), bksge::end(b),
			std::back_inserter(c));

		(void)ret;

		EXPECT_EQ(6u, c.size());
		EXPECT_EQ(1, c[0]);
		EXPECT_EQ(1, c[1]);
		EXPECT_EQ(2, c[2]);
		EXPECT_EQ(2, c[3]);
		EXPECT_EQ(3, c[4]);
		EXPECT_EQ(3, c[5]);
	}
	{
		const std::list<int> a { 5, 6, 7 };
		const int b[] { 1, 2, 3 };
		bksge::vector<int> c;
		auto ret = bksge::merge(
			bksge::begin(a), bksge::end(a),
			bksge::begin(b), bksge::end(b),
			std::back_inserter(c));

		(void)ret;

		EXPECT_EQ(6u, c.size());
		EXPECT_EQ(1, c[0]);
		EXPECT_EQ(2, c[1]);
		EXPECT_EQ(3, c[2]);
		EXPECT_EQ(5, c[3]);
		EXPECT_EQ(6, c[4]);
		EXPECT_EQ(7, c[5]);
	}
	{
		const bksge::vector<int> a;
		const std::list<int> b;
		bksge::vector<int> c;
		auto ret = bksge::merge(
			bksge::begin(a), bksge::end(a),
			bksge::begin(b), bksge::end(b),
			std::back_inserter(c));

		(void)ret;

		EXPECT_TRUE(c.empty());
	}
}

}	// namespace merge_test

}	// namespace bksge_algorithm_test
