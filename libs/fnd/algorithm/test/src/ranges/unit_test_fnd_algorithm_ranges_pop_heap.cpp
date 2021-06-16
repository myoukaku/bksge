/**
 *	@file	unit_test_fnd_algorithm_ranges_pop_heap.cpp
 *
 *	@brief	ranges::pop_heap のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/pop_heap.hpp>
#include <bksge/fnd/algorithm/ranges/make_heap.hpp>
#include <bksge/fnd/algorithm/ranges/is_heap.hpp>
#include <bksge/fnd/functional/ranges/greater.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_pop_heap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int a[] = { 3, 1, 4, 1, 5, 9 };
		int n = 6;

		test_range<int, random_access_iterator_wrapper> r0(a, a+n);
		auto it = ranges::make_heap(r0);
		VERIFY(it == r0.end());
		VERIFY(ranges::is_heap(a, a+n));

		test_range<int, random_access_iterator_wrapper> r1(a, a+n);
		it = ranges::pop_heap(r1);
		VERIFY(it == r1.end());
		--n;
		VERIFY(ranges::is_heap(a, a+n));

		test_range<int, random_access_iterator_wrapper> r2(a, a+n);
		it = ranges::pop_heap(r2);
		VERIFY(it == r2.end());
		--n;
		VERIFY(ranges::is_heap(a, a+n));

		test_range<int, random_access_iterator_wrapper> r3(a, a+n);
		it = ranges::pop_heap(r3);
		VERIFY(it == r3.end());
		--n;
		VERIFY(ranges::is_heap(a, a+n));

		test_range<int, random_access_iterator_wrapper> r4(a, a+n);
		it = ranges::pop_heap(r4);
		VERIFY(it == r4.end());
		--n;
		VERIFY(ranges::is_heap(a, a+n));
	}
	return true;
}

inline bool test02()
{
	namespace ranges = bksge::ranges;
	{
		bksge::vector<int> a { 3, 1, 4, 1, 5, 9 };

		auto it = ranges::make_heap(a);
		VERIFY(it == a.end());
		VERIFY(ranges::is_heap(a));

		it = ranges::pop_heap(a);
		VERIFY(it == a.end());
		a.pop_back();
		VERIFY(ranges::is_heap(a));

		it = ranges::pop_heap(a);
		VERIFY(it == a.end());
		a.pop_back();
		VERIFY(ranges::is_heap(a));

		it = ranges::pop_heap(a);
		VERIFY(it == a.end());
		a.pop_back();
		VERIFY(ranges::is_heap(a));

		it = ranges::pop_heap(a);
		VERIFY(it == a.end());
		a.pop_back();
		VERIFY(ranges::is_heap(a));
	}
	{
		bksge::vector<int> a { 1, 1, 2, 2, 2, 3, 5, 9 };
		auto pred = ranges::greater{};

		auto it = ranges::make_heap(a, pred);
		VERIFY(it == a.end());
		VERIFY(ranges::is_heap(a, pred));

		it = ranges::pop_heap(a, pred);
		VERIFY(it == a.end());
		a.pop_back();
		VERIFY(ranges::is_heap(a, pred));

		it = ranges::pop_heap(a, pred);
		VERIFY(it == a.end());
		a.pop_back();
		VERIFY(ranges::is_heap(a, pred));

		it = ranges::pop_heap(a, pred);
		VERIFY(it == a.end());
		a.pop_back();
		VERIFY(ranges::is_heap(a, pred));

		it = ranges::pop_heap(a, pred);
		VERIFY(it == a.end());
		a.pop_back();
		VERIFY(ranges::is_heap(a, pred));

		it = ranges::pop_heap(a, pred);
		VERIFY(it == a.end());
		a.pop_back();
		VERIFY(ranges::is_heap(a, pred));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesPopHeapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_pop_heap_test

}	// namespace bksge_algorithm_test
