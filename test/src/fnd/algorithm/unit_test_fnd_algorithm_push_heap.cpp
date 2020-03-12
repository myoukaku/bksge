/**
 *	@file	unit_test_fnd_algorithm_push_heap.cpp
 *
 *	@brief	push_heap のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/push_heap.hpp>
#include <bksge/fnd/algorithm/make_heap.hpp>
#include <bksge/fnd/functional/greater.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <vector>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace push_heap_test
{

GTEST_TEST(AlgorithmTest, PushHeapTest)
{
	{
		std::vector<int> a { 3, 1, 4 };

		bksge::make_heap(bksge::begin(a), bksge::end(a));
		EXPECT_EQ(4, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(3, a[2]);

		a.push_back(2);
		bksge::push_heap(bksge::begin(a), bksge::end(a));
		EXPECT_EQ(4, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(1, a[3]);

		a.push_back(5);
		bksge::push_heap(bksge::begin(a), bksge::end(a));
		EXPECT_EQ(5, a[0]);
		EXPECT_EQ(4, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(2, a[4]);

		a.push_back(0);
		bksge::push_heap(bksge::begin(a), bksge::end(a));
		EXPECT_EQ(5, a[0]);
		EXPECT_EQ(4, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(2, a[4]);
		EXPECT_EQ(0, a[5]);

		a.push_back(4);
		bksge::push_heap(bksge::begin(a), bksge::end(a));
		EXPECT_EQ(5, a[0]);
		EXPECT_EQ(4, a[1]);
		EXPECT_EQ(4, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(2, a[4]);
		EXPECT_EQ(0, a[5]);
		EXPECT_EQ(3, a[6]);
	}
	{
		std::vector<int> a { 3, 2, 1 };

		bksge::make_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);

		a.push_back(2);
		bksge::push_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(2, a[3]);

		a.push_back(3);
		bksge::push_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(2, a[3]);
		EXPECT_EQ(3, a[4]);

		a.push_back(1);
		bksge::push_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(1, a[2]);
		EXPECT_EQ(2, a[3]);
		EXPECT_EQ(3, a[4]);
		EXPECT_EQ(3, a[5]);

		a.push_back(0);
		bksge::push_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		EXPECT_EQ(0, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(1, a[2]);
		EXPECT_EQ(2, a[3]);
		EXPECT_EQ(3, a[4]);
		EXPECT_EQ(3, a[5]);
		EXPECT_EQ(1, a[6]);
	}
}

}	// namespace push_heap_test

}	// namespace bksge_algorithm_test
