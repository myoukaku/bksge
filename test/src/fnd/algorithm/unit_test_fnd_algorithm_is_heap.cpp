/**
 *	@file	unit_test_fnd_algorithm_is_heap.cpp
 *
 *	@brief	is_heap のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/is_heap.hpp>
#include <bksge/fnd/functional/greater.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace is_heap_test
{

BKSGE_CONSTEXPR bool pred1(int x, int y)
{
	return x < y;
}

GTEST_TEST(AlgorithmTest, IsHeapTest)
{
	{
		const int a[] { 1, 2, 3 };
		EXPECT_FALSE(bksge::is_heap(bksge::begin(a), bksge::end(a)));
	}
	{
		const int a[] { 1, 2, 3 };
		EXPECT_TRUE(bksge::is_heap(bksge::begin(a), bksge::end(a), bksge::greater<>()));
	}
	{
		const int a[] { 3, 2, 1 };
		EXPECT_TRUE(bksge::is_heap(bksge::begin(a), bksge::end(a)));
	}
	{
		const int a[] { 3, 2, 1 };
		EXPECT_FALSE(bksge::is_heap(bksge::begin(a), bksge::end(a), bksge::greater<>()));
	}
	{
		const int a[] { 9, 5, 4, 1, 1, 3, 2, 6 };
		EXPECT_FALSE(bksge::is_heap(bksge::begin(a), bksge::end(a)));
	}
	{
		const bksge::array<int, 3> a {{ 1, 2, 3 }};
		EXPECT_FALSE(bksge::is_heap(bksge::begin(a), bksge::end(a), pred1));
	}
	{
		const bksge::array<int, 3> a {{ 3, 2, 1 }};
		EXPECT_TRUE(bksge::is_heap(bksge::begin(a), bksge::end(a), pred1));
	}
	{
		const bksge::array<int, 8> a {{ 9, 5, 4, 1, 1, 3, 2, 6 }};
		EXPECT_FALSE(bksge::is_heap(bksge::begin(a), bksge::end(a), pred1));
	}
	{
		const bksge::vector<int> a { 9, 9, 7, 3, 4, 3, 2 };
		EXPECT_TRUE(bksge::is_heap(bksge::begin(a), bksge::end(a)));
	}
	{
		const bksge::vector<int> a { 9, 7, 7, 8, 4, 3, 2 };
		EXPECT_FALSE(bksge::is_heap(bksge::begin(a), bksge::end(a)));
	}
	{
		const bksge::vector<int> a { 3, 2, 1 };
		EXPECT_TRUE(bksge::is_heap(bksge::begin(a), bksge::end(a), [](int x, int y){return x < y;}));
	}
	{
		const bksge::vector<int> a { 1, 2, 3 };
		EXPECT_FALSE(bksge::is_heap(bksge::begin(a), bksge::end(a), [](int x, int y){return x < y;}));
	}
	{
		const bksge::vector<int> a { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		EXPECT_TRUE(bksge::is_heap(bksge::begin(a), bksge::end(a), [](int x, int y){return x < y;}));
	}
}

}	// namespace is_heap_test

}	// namespace bksge_algorithm_test
