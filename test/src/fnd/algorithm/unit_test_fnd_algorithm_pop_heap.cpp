/**
 *	@file	unit_test_fnd_algorithm_pop_heap.cpp
 *
 *	@brief	pop_heap のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/pop_heap.hpp>
#include <bksge/fnd/algorithm/make_heap.hpp>
#include <bksge/fnd/functional/greater.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <gtest/gtest.h>
#include <bksge/fnd/vector.hpp>

namespace bksge_algorithm_test
{

namespace pop_heap_test
{

GTEST_TEST(AlgorithmTest, PopHeapTest)
{
	{
		bksge::vector<int> a { 3, 1, 4, 1, 5, 9 };

		bksge::make_heap(bksge::begin(a), bksge::end(a));
		EXPECT_EQ(9, a[0]);
		EXPECT_EQ(5, a[1]);
		EXPECT_EQ(4, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(1, a[4]);
		EXPECT_EQ(3, a[5]);

		bksge::pop_heap(bksge::begin(a), bksge::end(a));
		a.pop_back();
		EXPECT_EQ(5, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(4, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(1, a[4]);

		bksge::pop_heap(bksge::begin(a), bksge::end(a));
		a.pop_back();
		EXPECT_EQ(4, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(1, a[2]);
		EXPECT_EQ(1, a[3]);

		bksge::pop_heap(bksge::begin(a), bksge::end(a));
		a.pop_back();
		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(1, a[2]);

		bksge::pop_heap(bksge::begin(a), bksge::end(a));
		a.pop_back();
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(1, a[1]);
	}
	{
		bksge::vector<int> a { 1, 1, 2, 2, 2, 3, 5, 9 };

		bksge::make_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(2, a[3]);
		EXPECT_EQ(2, a[4]);
		EXPECT_EQ(3, a[5]);
		EXPECT_EQ(5, a[6]);
		EXPECT_EQ(9, a[7]);

		bksge::pop_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		a.pop_back();
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(9, a[3]);
		EXPECT_EQ(2, a[4]);
		EXPECT_EQ(3, a[5]);
		EXPECT_EQ(5, a[6]);

		bksge::pop_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		a.pop_back();
		EXPECT_EQ(2, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(9, a[3]);
		EXPECT_EQ(5, a[4]);
		EXPECT_EQ(3, a[5]);

		bksge::pop_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		a.pop_back();
		EXPECT_EQ(2, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(9, a[3]);
		EXPECT_EQ(5, a[4]);

		bksge::pop_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		a.pop_back();
		EXPECT_EQ(2, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(5, a[2]);
		EXPECT_EQ(9, a[3]);

		bksge::pop_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		a.pop_back();
		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(9, a[1]);
		EXPECT_EQ(5, a[2]);
	}
}

}	// namespace pop_heap_test

}	// namespace bksge_algorithm_test
