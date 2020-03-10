/**
 *	@file	unit_test_fnd_algorithm_copy_n.cpp
 *
 *	@brief	copy_n のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/copy_n.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include <array>
#include <iterator>

namespace bksge_algorithm_test
{

namespace copy_n_test
{

GTEST_TEST(AlgorithmTest, CopyNTest)
{
	{
		const int a1[] { 1, 2, 3 };
		int a2[3]{};

		auto it = bksge::copy_n(bksge::begin(a1), 3, bksge::begin(a2));

		EXPECT_EQ(1, a2[0]);
		EXPECT_EQ(2, a2[1]);
		EXPECT_EQ(3, a2[2]);
		EXPECT_TRUE(it == bksge::end(a2));
	}
	{
		const int a1[] { 1, 2, 3 };
		int a2[3]{};

		auto it = bksge::copy_n(bksge::begin(a1), 2, bksge::begin(a2));

		EXPECT_EQ(1, a2[0]);
		EXPECT_EQ(2, a2[1]);
		EXPECT_EQ(0, a2[2]);
		EXPECT_TRUE(it == bksge::begin(a2) + 2);
	}
	{
		const std::array<int, 4> a1 {{ 4, 5, 6, 7 }};
		int a2[5] {{}};

		auto it = bksge::copy_n(bksge::begin(a1), 4, bksge::begin(a2));

		EXPECT_EQ(4, a2[0]);
		EXPECT_EQ(5, a2[1]);
		EXPECT_EQ(6, a2[2]);
		EXPECT_EQ(7, a2[3]);
		EXPECT_EQ(0, a2[4]);
		EXPECT_TRUE(it == bksge::begin(a2) + 4);
	}
	{
		const std::array<int, 4> a1 {{ 4, 5, 6, 7 }};
		int a2[3] {{}};

		auto it = bksge::copy_n(bksge::begin(a1), 1, bksge::begin(a2));

		EXPECT_EQ(4, a2[0]);
		EXPECT_EQ(0, a2[1]);
		EXPECT_EQ(0, a2[2]);
		EXPECT_TRUE(it == bksge::begin(a2) + 1);
	}
	{
		const bksge::vector<int> v { 5, 6, 7, 8, 9 };
		bksge::list<int> l;

		bksge::copy_n(bksge::begin(v), 5, std::back_inserter(l));

		auto it = l.begin();
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(6, *it++);
		EXPECT_EQ(7, *it++);
		EXPECT_EQ(8, *it++);
		EXPECT_EQ(9, *it++);
		EXPECT_TRUE(it == l.end());
	}
	{
		const bksge::list<int> a { 1, 2, 3 };
		bksge::list<int> b;

		bksge::copy_n(bksge::begin(a), a.size(), std::back_inserter(b));

		auto it = b.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_TRUE(it == b.end());
	}
}

}	// namespace copy_n_test

}	// namespace bksge_algorithm_test
