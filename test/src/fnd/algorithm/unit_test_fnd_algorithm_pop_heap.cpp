/**
 *	@file	unit_test_fnd_algorithm_pop_heap.cpp
 *
 *	@brief	pop_heap のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/pop_heap.hpp>
#include <bksge/fnd/algorithm/make_heap.hpp>
#include <bksge/fnd/algorithm/is_heap.hpp>
#include <bksge/fnd/functional/greater.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace pop_heap_test
{

GTEST_TEST(AlgorithmTest, PopHeapTest)
{
	{
		bksge::vector<int> a { 3, 1, 4, 1, 5, 9 };

		bksge::make_heap(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE(bksge::is_heap(bksge::begin(a), bksge::end(a)));

		bksge::pop_heap(bksge::begin(a), bksge::end(a));
		a.pop_back();
		EXPECT_TRUE(bksge::is_heap(bksge::begin(a), bksge::end(a)));

		bksge::pop_heap(bksge::begin(a), bksge::end(a));
		a.pop_back();
		EXPECT_TRUE(bksge::is_heap(bksge::begin(a), bksge::end(a)));

		bksge::pop_heap(bksge::begin(a), bksge::end(a));
		a.pop_back();
		EXPECT_TRUE(bksge::is_heap(bksge::begin(a), bksge::end(a)));

		bksge::pop_heap(bksge::begin(a), bksge::end(a));
		a.pop_back();
		EXPECT_TRUE(bksge::is_heap(bksge::begin(a), bksge::end(a)));
	}
	{
		bksge::vector<int> a { 1, 1, 2, 2, 2, 3, 5, 9 };

		bksge::make_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		EXPECT_TRUE(bksge::is_heap(bksge::begin(a), bksge::end(a), bksge::greater<>()));

		bksge::pop_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		a.pop_back();
		EXPECT_TRUE(bksge::is_heap(bksge::begin(a), bksge::end(a), bksge::greater<>()));

		bksge::pop_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		a.pop_back();
		EXPECT_TRUE(bksge::is_heap(bksge::begin(a), bksge::end(a), bksge::greater<>()));

		bksge::pop_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		a.pop_back();
		EXPECT_TRUE(bksge::is_heap(bksge::begin(a), bksge::end(a), bksge::greater<>()));

		bksge::pop_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		a.pop_back();
		EXPECT_TRUE(bksge::is_heap(bksge::begin(a), bksge::end(a), bksge::greater<>()));

		bksge::pop_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		a.pop_back();
		EXPECT_TRUE(bksge::is_heap(bksge::begin(a), bksge::end(a), bksge::greater<>()));
	}
}

}	// namespace pop_heap_test

}	// namespace bksge_algorithm_test
