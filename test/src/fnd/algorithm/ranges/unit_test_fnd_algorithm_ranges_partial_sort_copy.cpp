/**
 *	@file	unit_test_fnd_algorithm_ranges_partial_sort_copy.cpp
 *
 *	@brief	ranges::partial_sort_copy のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/partial_sort_copy.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_partial_sort_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int const x[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		int w[1] = {};
		auto res = ranges::partial_sort_copy(x, w);
		VERIFY(res.in  == x+11);
		VERIFY(res.out == w+1);
		int const y[] = { 1 };
		VERIFY(ranges::equal(w, y));
	}
	{
		int const x[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		int w[1] = {};
		auto res = ranges::partial_sort_copy(x, w, ranges::greater{});
		VERIFY(res.in  == x+11);
		VERIFY(res.out == w+1);
		int const y[] = { 9 };
		VERIFY(ranges::equal(w, y));
	}
	{
		int const x[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		int w[4] = {};
		auto res = ranges::partial_sort_copy(x, w);
		VERIFY(res.in  == x+11);
		VERIFY(res.out == w+4);
		int const y[] = { 1, 1, 2, 3 };
		VERIFY(ranges::equal(w, y));
	}
	{
		int const x[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		int w[5] = {};
		auto res = ranges::partial_sort_copy(x, w, ranges::greater{});
		VERIFY(res.in  == x+11);
		VERIFY(res.out == w+5);
		int const y[] = { 9, 6, 5, 5, 5 };
		VERIFY(ranges::equal(w, y));
	}
	{
		int const x[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		int w[6] = {};
		test_range<int const, input_iterator_wrapper> rx(x);
		test_range<int, random_access_iterator_wrapper> rw(w);
		auto res = ranges::partial_sort_copy(rx, rw);
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == rw.end());
		int const y[] = { 1, 1, 2, 3, 3, 4 };
		VERIFY(ranges::equal(w, y));
	}
	{
		int const x[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		int w[7] = {};
		test_range<int const, input_iterator_wrapper> rx(x);
		test_range<int, random_access_iterator_wrapper> rw(w);
		auto res = ranges::partial_sort_copy(rx, rw, ranges::greater{});
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == rw.end());
		int const y[] = { 9, 6, 5, 5, 5, 4, 3 };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

struct X
{
	int i;
};

inline bool test02()
{
	namespace ranges = bksge::ranges;
	{
		X const x[] = { {5},{1},{3},{2},{4},{6} };
		X w[2] = {};
		auto res = ranges::partial_sort_copy(x, w, {}, &X::i, &X::i);
		VERIFY(res.in  == x+6);
		VERIFY(res.out == w+2);
		X const y[] = { {1},{2} };
		VERIFY(ranges::equal(w, y, {}, &X::i, &X::i));
	}
	{
		X const x[] = { {5},{1},{3},{2},{4},{6} };
		X w[3] = {};
		auto res = ranges::partial_sort_copy(x, w, ranges::greater{}, &X::i, &X::i);
		VERIFY(res.in  == x+6);
		VERIFY(res.out == w+3);
		X const y[] = { {6},{5},{4} };
		VERIFY(ranges::equal(w, y, {}, &X::i, &X::i));
	}
	{
		std::vector<int> x = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		std::vector<int> w = {};
		auto res = ranges::partial_sort_copy(x, w);
		VERIFY(res.in  == x.end());
		VERIFY(res.out == w.end());
		VERIFY(w.empty());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesPartialSortCopyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_partial_sort_copy_test

}	// namespace bksge_algorithm_test
