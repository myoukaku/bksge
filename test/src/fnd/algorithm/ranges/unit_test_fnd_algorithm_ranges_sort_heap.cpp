/**
 *	@file	unit_test_fnd_algorithm_ranges_sort_heap.cpp
 *
 *	@brief	ranges::sort_heap のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/sort_heap.hpp>
#include <bksge/fnd/algorithm/ranges/make_heap.hpp>
#include <bksge/fnd/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_sort_heap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int a[] = { 3, 1, 4 };
		ranges::make_heap(a, a+3);
		ranges::sort_heap(a, a+3);
		VERIFY(1 == a[0]);
		VERIFY(3 == a[1]);
		VERIFY(4 == a[2]);
	}
	{
		int a[] = { 3, 1, 4 };
		ranges::make_heap(a, a+3, ranges::greater{});
		ranges::sort_heap(a, a+3, ranges::greater{});
		VERIFY(4 == a[0]);
		VERIFY(3 == a[1]);
		VERIFY(1 == a[2]);
	}
	{
		int a[] = { 3, 1, 4, 1, 5, 9 };
		test_range<int, random_access_iterator_wrapper> r(a);
		ranges::make_heap(r);
		ranges::sort_heap(r);
		VERIFY(1 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(4 == a[3]);
		VERIFY(5 == a[4]);
		VERIFY(9 == a[5]);
	}
	{
		int a[] = { 3, 1, 4, 1, 5, 9 };
		test_range<int, random_access_iterator_wrapper> r(a);
		ranges::make_heap(r, ranges::greater{});
		ranges::sort_heap(r, ranges::greater{});
		VERIFY(9 == a[0]);
		VERIFY(5 == a[1]);
		VERIFY(4 == a[2]);
		VERIFY(3 == a[3]);
		VERIFY(1 == a[4]);
		VERIFY(1 == a[5]);
	}
	return true;
}

inline bool test02()
{
	namespace ranges = bksge::ranges;
	{
		std::vector<int> a { 5, 4, 1, 1, 3 };
		ranges::make_heap(a);
		ranges::sort_heap(a);
		VERIFY(1 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(4 == a[3]);
		VERIFY(5 == a[4]);
	}
	{
		std::vector<int> a { 5, 4, 1, 1, 3 };
		ranges::make_heap(a, ranges::greater{});
		ranges::sort_heap(a, ranges::greater{});
		VERIFY(5 == a[0]);
		VERIFY(4 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(1 == a[3]);
		VERIFY(1 == a[4]);
	}
	{
		std::vector<int> a;
		ranges::make_heap(a);
		ranges::sort_heap(a);
		VERIFY(a.empty());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesSortHeapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_sort_heap_test

}	// namespace bksge_algorithm_test
