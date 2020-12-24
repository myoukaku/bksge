/**
 *	@file	unit_test_fnd_algorithm_is_heap_until.cpp
 *
 *	@brief	is_heap_until のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/is_heap_until.hpp>
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

namespace is_heap_until_test
{

BKSGE_CONSTEXPR bool pred1(int x, int y)
{
	return x < y;
}

GTEST_TEST(AlgorithmTest, IsHeapUntilTest)
{
	{
		const int a[] { 1, 2, 3 };
		const auto ret = bksge::is_heap_until(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 1));
	}
	{
		const int a[] { 1, 2, 3 };
		const auto ret = bksge::is_heap_until(bksge::begin(a), bksge::end(a), bksge::greater<>());
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 3));
	}
	{
		const int a[] { 3, 2, 1 };
		const auto ret = bksge::is_heap_until(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 3));
	}
	{
		const int a[] { 3, 2, 1 };
		const auto ret = bksge::is_heap_until(bksge::begin(a), bksge::end(a), bksge::greater<>());
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 1));
	}
	{
		const int a[] { 9, 5, 4, 1, 1, 3, 2, 6 };
		const auto ret = bksge::is_heap_until(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 7));
	}
	{
		const bksge::array<int, 3> a {{ 1, 2, 3 }};
		const auto ret = bksge::is_heap_until(bksge::begin(a), bksge::end(a), pred1);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 1));
	}
	{
		const bksge::array<int, 3> a {{ 3, 2, 1 }};
		const auto ret = bksge::is_heap_until(bksge::begin(a), bksge::end(a), pred1);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 3));
	}
	{
		const bksge::array<int, 8> a {{ 9, 5, 4, 1, 1, 3, 2, 6 }};
		const auto ret = bksge::is_heap_until(bksge::begin(a), bksge::end(a), pred1);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 7));
	}
	{
		const bksge::vector<int> a { 9, 9, 7, 3, 4, 3, 2 };
		auto ret = bksge::is_heap_until(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 7));
	}
	{
		const bksge::vector<int> a { 9, 7, 7, 8, 4, 3, 2 };
		auto ret = bksge::is_heap_until(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 3));
	}
	{
		const bksge::vector<int> a { 3, 2, 1 };
		auto ret = bksge::is_heap_until(bksge::begin(a), bksge::end(a), [](int x, int y){return x < y;});
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 3));
	}
	{
		const bksge::vector<int> a { 1, 2, 3 };
		auto ret = bksge::is_heap_until(bksge::begin(a), bksge::end(a), [](int x, int y){return x < y;});
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 1));
	}
	{
		const bksge::vector<int> a { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		auto ret = bksge::is_heap_until(bksge::begin(a), bksge::end(a), [](int x, int y){return x < y;});
		EXPECT_TRUE(ret == bksge::end(a));
	}
}

}	// namespace is_heap_until_test

}	// namespace bksge_algorithm_test
