﻿/**
 *	@file	unit_test_fnd_algorithm_reverse_copy.cpp
 *
 *	@brief	reverse_copy のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/reverse_copy.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/iterator/back_inserter.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace reverse_copy_test
{

GTEST_TEST(AlgorithmTest, ReverseCopyTest)
{
	{
		const int a[] { 1,2,3 };
		int b[3] {};
		auto it = bksge::reverse_copy(bksge::begin(a), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(b), 3));
		EXPECT_EQ(3, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(1, b[2]);
	}
	{
		const int a[] { 1,2,3 };
		bksge::array<int, 5> b {{}};
		auto it = bksge::reverse_copy(bksge::begin(a), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(b), 3));
		EXPECT_EQ(3, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(1, b[2]);
		EXPECT_EQ(0, b[3]);
		EXPECT_EQ(0, b[4]);
	}
	{
		const int a[] { 4 };
		int b[3] {};
		auto it = bksge::reverse_copy(bksge::begin(a), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(b), 1));
		EXPECT_EQ(4, b[0]);
		EXPECT_EQ(0, b[1]);
		EXPECT_EQ(0, b[2]);
	}
	{
		const bksge::array<int, 4> a {{ 1,2,3,4 }};
		int b[4] {};
		auto it = bksge::reverse_copy(bksge::begin(a), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(b), 4));
		EXPECT_EQ(4, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(2, b[2]);
		EXPECT_EQ(1, b[3]);
	}
	{
		const bksge::array<int, 4> a {{ 1,2,3,4 }};
		bksge::list<int> b;
		bksge::reverse_copy(bksge::begin(a), bksge::end(a), bksge::back_inserter(b));
		auto it = b.begin();
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const bksge::vector<int> a { 1,2,3,4,5 };
		bksge::vector<int> b;
		bksge::reverse_copy(bksge::begin(a), bksge::end(a), bksge::back_inserter(b));
		EXPECT_EQ(5, b[0]);
		EXPECT_EQ(4, b[1]);
		EXPECT_EQ(3, b[2]);
		EXPECT_EQ(2, b[3]);
		EXPECT_EQ(1, b[4]);
	}
	{
		const bksge::vector<int> a { 1,2,3,4 };
		int b[4] {};
		auto it = bksge::reverse_copy(bksge::begin(a), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(b), 4));
		EXPECT_EQ(4, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(2, b[2]);
		EXPECT_EQ(1, b[3]);
	}
	{
		const bksge::vector<int> a;
		bksge::vector<int> b;
		bksge::reverse_copy(bksge::begin(a), bksge::end(a), bksge::back_inserter(b));
		EXPECT_TRUE(b.empty());
	}
	{
		const bksge::list<int> a { 1,2 };
		bksge::list<int> b;
		bksge::reverse_copy(bksge::begin(a), bksge::end(a), bksge::back_inserter(b));
		auto it = b.begin();
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const bksge::list<int> a { 1,2,3 };
		bksge::array<int, 4> b {{}};
		auto it = bksge::reverse_copy(bksge::begin(a), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(b), 3));
		EXPECT_EQ(3, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(1, b[2]);
		EXPECT_EQ(0, b[3]);
	}
	{
		const bksge::list<int> a;
		bksge::list<int> b;
		bksge::reverse_copy(bksge::begin(a), bksge::end(a), bksge::back_inserter(b));
		EXPECT_TRUE(b.empty());
	}
}

}	// namespace reverse_copy_test

}	// namespace bksge_algorithm_test
