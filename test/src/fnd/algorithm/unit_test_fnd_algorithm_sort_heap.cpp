/**
 *	@file	unit_test_fnd_algorithm_sort_heap.cpp
 *
 *	@brief	sort_heap のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/sort_heap.hpp>
#include <bksge/fnd/algorithm/make_heap.hpp>
#include <bksge/fnd/functional/greater.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <array>
#include <vector>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace sort_heap_test
{

GTEST_TEST(AlgorithmTest, SortHeapTest)
{
	{
		int a[] { 3, 1, 4 };
		bksge::make_heap(bksge::begin(a), bksge::end(a));
		bksge::sort_heap(bksge::begin(a), bksge::end(a));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(4, a[2]);
	}
	{
		int a[] { 3, 1, 4 };
		bksge::make_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		bksge::sort_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		EXPECT_EQ(4, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(1, a[2]);
	}
	{
		std::array<int, 6> a {{ 3, 1, 4, 1, 5, 9 }};
		bksge::make_heap(bksge::begin(a), bksge::end(a));
		bksge::sort_heap(bksge::begin(a), bksge::end(a));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(4, a[3]);
		EXPECT_EQ(5, a[4]);
		EXPECT_EQ(9, a[5]);
	}
	{
		std::array<int, 6> a {{ 3, 1, 4, 1, 5, 9 }};
		bksge::make_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		bksge::sort_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		EXPECT_EQ(9, a[0]);
		EXPECT_EQ(5, a[1]);
		EXPECT_EQ(4, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(1, a[4]);
		EXPECT_EQ(1, a[5]);
	}
	{
		std::vector<int> a { 5, 4, 1, 1, 3 };
		bksge::make_heap(bksge::begin(a), bksge::end(a));
		bksge::sort_heap(bksge::begin(a), bksge::end(a));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(4, a[3]);
		EXPECT_EQ(5, a[4]);
	}
	{
		std::vector<int> a { 5, 4, 1, 1, 3 };
		bksge::make_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		bksge::sort_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		EXPECT_EQ(5, a[0]);
		EXPECT_EQ(4, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(1, a[4]);
	}
	{
		std::vector<int> a;
		bksge::sort_heap(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE(a.empty());
	}
}

}	// namespace sort_heap_test

}	// namespace bksge_algorithm_test
