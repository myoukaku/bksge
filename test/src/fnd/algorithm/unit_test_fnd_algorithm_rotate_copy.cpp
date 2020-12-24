/**
 *	@file	unit_test_fnd_algorithm_rotate_copy.cpp
 *
 *	@brief	rotate_copy のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/rotate_copy.hpp>
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

namespace rotate_copy_test
{

GTEST_TEST(AlgorithmTest, RotateCopyTest)
{
	{
		const int a[] { 1,2,3 };
		int b[3] {};
		auto it = bksge::rotate_copy(bksge::begin(a), bksge::next(bksge::begin(a), 1), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(b), 3));
		EXPECT_EQ(2, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(1, b[2]);
	}
	{
		const int a[] { 1,2,3 };
		std::array<int, 5> b {{}};
		auto it = bksge::rotate_copy(bksge::begin(a), bksge::next(bksge::begin(a), 2), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(b), 3));
		EXPECT_EQ(3, b[0]);
		EXPECT_EQ(1, b[1]);
		EXPECT_EQ(2, b[2]);
		EXPECT_EQ(0, b[3]);
		EXPECT_EQ(0, b[4]);
	}
	{
		const int a[] { 42 };
		int b[3] {};
		auto it = bksge::rotate_copy(bksge::begin(a), bksge::next(bksge::begin(a), 0), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(b), 1));
		EXPECT_EQ(42, b[0]);
		EXPECT_EQ(0, b[1]);
		EXPECT_EQ(0, b[2]);
	}
	{
		const std::array<int, 4> a {{ 1,2,3,4 }};
		int b[4] {};
		auto it = bksge::rotate_copy(bksge::begin(a), bksge::next(bksge::begin(a), 1), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(b), 4));
		EXPECT_EQ(2, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(4, b[2]);
		EXPECT_EQ(1, b[3]);
	}
	{
		const std::array<int, 4> a {{ 1,2,3,4 }};
		std::list<int> b;
		bksge::rotate_copy(bksge::begin(a), bksge::next(bksge::begin(a), 4), bksge::end(a), std::back_inserter(b));
		auto it = b.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const bksge::vector<int> a { 1,2,3,4,5 };
		bksge::vector<int> b;
		bksge::rotate_copy(bksge::begin(a), bksge::next(bksge::begin(a), 3), bksge::end(a), std::back_inserter(b));
		EXPECT_EQ(4, b[0]);
		EXPECT_EQ(5, b[1]);
		EXPECT_EQ(1, b[2]);
		EXPECT_EQ(2, b[3]);
		EXPECT_EQ(3, b[4]);
	}
	{
		const bksge::vector<int> a { 1,2,3,4 };
		int b[4] {};
		auto it = bksge::rotate_copy(bksge::begin(a), bksge::next(bksge::begin(a), 1), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(b), 4));
		EXPECT_EQ(2, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(4, b[2]);
		EXPECT_EQ(1, b[3]);
	}
	{
		const bksge::vector<int> a;
		bksge::vector<int> b;
		bksge::rotate_copy(bksge::begin(a), bksge::next(bksge::begin(a), 0), bksge::end(a), std::back_inserter(b));
		EXPECT_TRUE(b.empty());
	}
	{
		const std::list<int> a { 1,2 };
		std::list<int> b;
		bksge::rotate_copy(bksge::begin(a), bksge::next(bksge::begin(a), 1), bksge::end(a), std::back_inserter(b));
		auto it = b.begin();
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const std::list<int> a { 1,2,3 };
		std::array<int, 4> b {{}};
		auto it = bksge::rotate_copy(bksge::begin(a), bksge::next(bksge::begin(a), 2), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(b), 3));
		EXPECT_EQ(3, b[0]);
		EXPECT_EQ(1, b[1]);
		EXPECT_EQ(2, b[2]);
		EXPECT_EQ(0, b[3]);
	}
	{
		const std::list<int> a;
		std::list<int> b;
		bksge::rotate_copy(bksge::begin(a), bksge::next(bksge::begin(a), 0), bksge::end(a), std::back_inserter(b));
		EXPECT_TRUE(b.empty());
	}
}

}	// namespace rotate_copy_test

}	// namespace bksge_algorithm_test
