/**
 *	@file	unit_test_fnd_algorithm_ranges_lexicographical_compare.cpp
 *
 *	@brief	ranges::lexicographical_compare のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/lexicographical_compare.hpp>
#include <bksge/fnd/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_lexicographical_compare_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct Abs
{
	constexpr int operator()(int x) const
	{
		return x < 0 ? -x : x;
	}
};

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int const x[] = { 1,2,3,4,5 };
		int const y[] = { 1,2,3,4,5 };
		test_range<int const, input_iterator_wrapper> rx(x);
		test_range<int const, input_iterator_wrapper> ry(y);
		VERIFY(!ranges::lexicographical_compare(rx, ry));
		VERIFY(!ranges::lexicographical_compare(rx, ry, ranges::greater{}));
		VERIFY(!ranges::lexicographical_compare(rx, ry, {}, Abs{}, Abs{}));
		VERIFY(!ranges::lexicographical_compare(rx, ry, ranges::greater{}, Abs{}, Abs{}));
	}
	{
		int const x[] = { 1,2,3,4,5 };
		int const y[] = { 1,2,3,4,6 };
		test_range<int const, input_iterator_wrapper> rx(x);
		test_range<int const, input_iterator_wrapper> ry(y);
		VERIFY( ranges::lexicographical_compare(rx, ry));
		VERIFY(!ranges::lexicographical_compare(rx, ry, ranges::greater{}));
		VERIFY( ranges::lexicographical_compare(rx, ry, {}, Abs{}, Abs{}));
		VERIFY(!ranges::lexicographical_compare(rx, ry, ranges::greater{}, Abs{}, Abs{}));
	}
	{
		int const x[] = { 1,2,3,4,6 };
		int const y[] = { 1,2,3,4,5 };
		test_range<int const, input_iterator_wrapper> rx(x);
		test_range<int const, input_iterator_wrapper> ry(y);
		VERIFY(!ranges::lexicographical_compare(rx, ry));
		VERIFY( ranges::lexicographical_compare(rx, ry, ranges::greater{}));
		VERIFY(!ranges::lexicographical_compare(rx, ry, {}, Abs{}, Abs{}));
		VERIFY( ranges::lexicographical_compare(rx, ry, ranges::greater{}, Abs{}, Abs{}));
	}
	{
		int const x[] = { 1,2,3,4,5 };
		int const y[] = { 1,2,3,4,5,6 };
		test_range<int const, input_iterator_wrapper> rx(x);
		test_range<int const, input_iterator_wrapper> ry(y);
		VERIFY( ranges::lexicographical_compare(rx, ry));
		VERIFY( ranges::lexicographical_compare(rx, ry, ranges::greater{}));
		VERIFY( ranges::lexicographical_compare(rx, ry, {}, Abs{}, Abs{}));
		VERIFY( ranges::lexicographical_compare(rx, ry, ranges::greater{}, Abs{}, Abs{}));
	}
	{
		int const x[] = { 1,2,3,4,5 };
		int const y[] = { 1,2,3,4 };
		test_range<int const, input_iterator_wrapper> rx(x);
		test_range<int const, input_iterator_wrapper> ry(y);
		VERIFY(!ranges::lexicographical_compare(rx, ry));
		VERIFY(!ranges::lexicographical_compare(rx, ry, ranges::greater{}));
		VERIFY(!ranges::lexicographical_compare(rx, ry, {}, Abs{}, Abs{}));
		VERIFY(!ranges::lexicographical_compare(rx, ry, ranges::greater{}, Abs{}, Abs{}));
	}
	{
		int const x[] = { 1,2,3,4,5 };
		int const y[] = { 1,2,3,4,-6 };
		test_range<int const, input_iterator_wrapper> rx(x);
		test_range<int const, input_iterator_wrapper> ry(y);
		VERIFY(!ranges::lexicographical_compare(rx, ry));
		VERIFY( ranges::lexicographical_compare(rx, ry, ranges::greater{}));
		VERIFY( ranges::lexicographical_compare(rx, ry, {}, Abs{}, Abs{}));
		VERIFY(!ranges::lexicographical_compare(rx, ry, ranges::greater{}, Abs{}, Abs{}));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesLexicographicalCompareTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace ranges_lexicographical_compare_test

}	// namespace bksge_algorithm_test
