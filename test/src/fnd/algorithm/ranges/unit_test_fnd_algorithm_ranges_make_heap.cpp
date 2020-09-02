/**
 *	@file	unit_test_fnd_algorithm_ranges_make_heap.cpp
 *
 *	@brief	ranges::make_heap のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/make_heap.hpp>
#include <bksge/fnd/algorithm/ranges/is_heap.hpp>
#include <bksge/fnd/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_make_heap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int a[] = { 3, 1, 4 };
		auto it = ranges::make_heap(a);
		VERIFY(it == a+3);
		VERIFY(ranges::is_heap(a));
	}
	{
		int a[] = { 3, 1, 4 };
		auto it = ranges::make_heap(a, ranges::greater{});
		VERIFY(it == a+3);
		VERIFY(ranges::is_heap(a, ranges::greater{}));
	}
	{
		int a[] = { 3, 1, 4, 1, 5, 9 };
		test_range<int, random_access_iterator_wrapper> r(a);
		auto it = ranges::make_heap(r);
		VERIFY(it == r.end());
		VERIFY(ranges::is_heap(r));
	}
	{
		int a[] = { 3, 1, 4, 1, 5, 9 };
		test_range<int, random_access_iterator_wrapper> r(a);
		auto it = ranges::make_heap(r, ranges::greater{});
		VERIFY(it == r.end());
		VERIFY(ranges::is_heap(r, ranges::greater{}));
	}
	return true;
}

inline bool test02()
{
	namespace ranges = bksge::ranges;
	{
		std::vector<int> a { 5, 4, 1, 1, 3 };
		auto it = ranges::make_heap(a);
		VERIFY(it == a.end());
		VERIFY(ranges::is_heap(a));
	}
	{
		std::vector<int> a { 5, 4, 1, 1, 3 };
		auto it = ranges::make_heap(a, ranges::greater{});
		VERIFY(it == a.end());
		VERIFY(ranges::is_heap(a, ranges::greater{}));
	}
	{
		std::vector<int> a;
		auto it = ranges::make_heap(a);
		VERIFY(it == a.end());
		VERIFY(a.empty());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesMakeHeapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_make_heap_test

}	// namespace bksge_algorithm_test
