/**
 *	@file	unit_test_fnd_algorithm_partial_sort_copy.cpp
 *
 *	@brief	partial_sort_copy のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/partial_sort_copy.hpp>
#include <bksge/fnd/functional/greater.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace partial_sort_copy_test
{

GTEST_TEST(AlgorithmTest, PartialSortCopyTest)
{
	{
		const int a[] { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		int b[1];
		auto ret = bksge::partial_sort_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(ret == bksge::end(b));
		EXPECT_EQ(1, b[0]);
	}
	{
		const int a[] { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		bksge::array<int, 2> b;
		auto ret = bksge::partial_sort_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), bksge::greater<>());
		EXPECT_TRUE(ret == bksge::end(b));
		EXPECT_EQ(9, b[0]);
		EXPECT_EQ(6, b[1]);
	}
	{
		const int a[] { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };
		bksge::vector<int> b(5);
		auto ret = bksge::partial_sort_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(ret == bksge::end(b));
		EXPECT_EQ(0, b[0]);
		EXPECT_EQ(1, b[1]);
		EXPECT_EQ(2, b[2]);
		EXPECT_EQ(3, b[3]);
		EXPECT_EQ(4, b[4]);
	}
	{
		const int a[] { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };
		bksge::vector<int> b(5);
		auto ret = bksge::partial_sort_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), bksge::greater<>());
		EXPECT_TRUE(ret == bksge::end(b));
		EXPECT_EQ(9, b[0]);
		EXPECT_EQ(8, b[1]);
		EXPECT_EQ(7, b[2]);
		EXPECT_EQ(6, b[3]);
		EXPECT_EQ(5, b[4]);
	}
	{
		const bksge::array<int, 11> a {{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 }};
		bksge::array<int, 3> b;
		auto ret = bksge::partial_sort_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(ret == bksge::end(b));
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(1, b[1]);
		EXPECT_EQ(2, b[2]);
	}
	{
		const bksge::array<int, 11> a {{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 }};
		int b[4];
		auto ret = bksge::partial_sort_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), bksge::greater<>());
		EXPECT_TRUE(ret == bksge::end(b));
		EXPECT_EQ(9, b[0]);
		EXPECT_EQ(6, b[1]);
		EXPECT_EQ(5, b[2]);
		EXPECT_EQ(5, b[3]);
	}
	{
		const bksge::array<int, 10> a {{ 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 }};
		bksge::array<int, 10> b;
		auto ret = bksge::partial_sort_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(ret == bksge::end(b));
		EXPECT_EQ(0, b[0]);
		EXPECT_EQ(1, b[1]);
		EXPECT_EQ(2, b[2]);
		EXPECT_EQ(3, b[3]);
		EXPECT_EQ(4, b[4]);
		EXPECT_EQ(5, b[5]);
		EXPECT_EQ(6, b[6]);
		EXPECT_EQ(7, b[7]);
		EXPECT_EQ(8, b[8]);
		EXPECT_EQ(9, b[9]);
	}
	{
		const bksge::array<int, 10> a {{ 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 }};
		bksge::vector<int> b(10);
		auto ret = bksge::partial_sort_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), bksge::greater<>());
		EXPECT_TRUE(ret == bksge::end(b));
		EXPECT_EQ(9, b[0]);
		EXPECT_EQ(8, b[1]);
		EXPECT_EQ(7, b[2]);
		EXPECT_EQ(6, b[3]);
		EXPECT_EQ(5, b[4]);
		EXPECT_EQ(4, b[5]);
		EXPECT_EQ(3, b[6]);
		EXPECT_EQ(2, b[7]);
		EXPECT_EQ(1, b[8]);
		EXPECT_EQ(0, b[9]);
	}
	{
		const bksge::vector<int> a { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		int b[5];
		auto ret = bksge::partial_sort_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(ret == bksge::end(b));
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(1, b[1]);
		EXPECT_EQ(2, b[2]);
		EXPECT_EQ(3, b[3]);
		EXPECT_EQ(3, b[4]);
	}
	{
		const bksge::vector<int> a { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		bksge::array<int, 6> b;
		auto ret = bksge::partial_sort_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), bksge::greater<>());
		EXPECT_TRUE(ret == bksge::end(b));
		EXPECT_EQ(9, b[0]);
		EXPECT_EQ(6, b[1]);
		EXPECT_EQ(5, b[2]);
		EXPECT_EQ(5, b[3]);
		EXPECT_EQ(5, b[4]);
		EXPECT_EQ(4, b[5]);
	}
	{
		const bksge::vector<int> a { 3, 1, 4 };
		bksge::vector<int> b(5);
		auto ret = bksge::partial_sort_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 3));
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(4, b[2]);
		EXPECT_EQ(0, b[3]);
		EXPECT_EQ(0, b[4]);
	}
	{
		const bksge::vector<int> a { 3, 1, 4 };
		int b[5] {};
		auto ret = bksge::partial_sort_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), bksge::greater<>());
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 3));
		EXPECT_EQ(4, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(1, b[2]);
		EXPECT_EQ(0, b[3]);
		EXPECT_EQ(0, b[4]);
	}
	{
		const bksge::list<int> a { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		int b[5];
		auto ret = bksge::partial_sort_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(ret == bksge::end(b));
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(1, b[1]);
		EXPECT_EQ(2, b[2]);
		EXPECT_EQ(3, b[3]);
		EXPECT_EQ(3, b[4]);
	}
	{
		const bksge::list<int> a { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		bksge::array<int, 6> b;
		auto ret = bksge::partial_sort_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), bksge::greater<>());
		EXPECT_TRUE(ret == bksge::end(b));
		EXPECT_EQ(9, b[0]);
		EXPECT_EQ(6, b[1]);
		EXPECT_EQ(5, b[2]);
		EXPECT_EQ(5, b[3]);
		EXPECT_EQ(5, b[4]);
		EXPECT_EQ(4, b[5]);
	}
	{
		const bksge::list<int> a { 3, 1, 4 };
		bksge::vector<int> b(5);
		auto ret = bksge::partial_sort_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 3));
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(4, b[2]);
		EXPECT_EQ(0, b[3]);
		EXPECT_EQ(0, b[4]);
	}
	{
		const bksge::list<int> a { 3, 1, 4 };
		int b[5] {};
		auto ret = bksge::partial_sort_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), bksge::greater<>());
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 3));
		EXPECT_EQ(4, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(1, b[2]);
		EXPECT_EQ(0, b[3]);
		EXPECT_EQ(0, b[4]);
	}
}

}	// namespace partial_sort_copy_test

}	// namespace bksge_algorithm_test
