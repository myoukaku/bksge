/**
 *	@file	unit_test_fnd_algorithm_make_heap.cpp
 *
 *	@brief	make_heap のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/make_heap.hpp>
#include <bksge/fnd/algorithm/is_heap.hpp>
#include <bksge/fnd/functional/greater.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace make_heap_test
{

GTEST_TEST(AlgorithmTest, MakeHeapTest)
{
	{
		int a[] { 3, 1, 4 };
		bksge::make_heap(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE (bksge::is_heap(bksge::begin(a), bksge::end(a)));
		EXPECT_FALSE(bksge::is_heap(bksge::begin(a), bksge::end(a), bksge::greater<>()));
	}
	{
		int a[] { 3, 1, 4 };
		bksge::make_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		EXPECT_FALSE(bksge::is_heap(bksge::begin(a), bksge::end(a)));
		EXPECT_TRUE (bksge::is_heap(bksge::begin(a), bksge::end(a), bksge::greater<>()));
	}
	{
		bksge::array<int, 6> a {{ 3, 1, 4, 1, 5, 9 }};
		bksge::make_heap(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE (bksge::is_heap(bksge::begin(a), bksge::end(a)));
		EXPECT_FALSE(bksge::is_heap(bksge::begin(a), bksge::end(a), bksge::greater<>()));
	}
	{
		bksge::array<int, 6> a {{ 3, 1, 4, 1, 5, 9 }};
		bksge::make_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		EXPECT_FALSE(bksge::is_heap(bksge::begin(a), bksge::end(a)));
		EXPECT_TRUE (bksge::is_heap(bksge::begin(a), bksge::end(a), bksge::greater<>()));
	}
	{
		bksge::vector<int> a { 5, 4, 1, 1, 3 };
		bksge::make_heap(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE (bksge::is_heap(bksge::begin(a), bksge::end(a)));
		EXPECT_FALSE(bksge::is_heap(bksge::begin(a), bksge::end(a), bksge::greater<>()));
	}
	{
		bksge::vector<int> a { 5, 4, 1, 1, 3 };
		bksge::make_heap(bksge::begin(a), bksge::end(a), bksge::greater<>());
		EXPECT_FALSE(bksge::is_heap(bksge::begin(a), bksge::end(a)));
		EXPECT_TRUE (bksge::is_heap(bksge::begin(a), bksge::end(a), bksge::greater<>()));
	}
	{
		bksge::vector<int> a;
		bksge::make_heap(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE(a.empty());
	}
}

}	// namespace make_heap_test

}	// namespace bksge_algorithm_test
