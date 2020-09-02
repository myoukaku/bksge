/**
 *	@file	unit_test_fnd_algorithm_ranges_min_element.cpp
 *
 *	@brief	ranges::min_element のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/min_element.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_min_element_test
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
		int const x[] = { 3, 1, -4, 1, 5, -9 };
		test_range<int const, forward_iterator_wrapper> rx(x);
		VERIFY(ranges::min_element(rx) == ranges::next(rx.begin(), 5));
		VERIFY(ranges::min_element(rx, ranges::greater{}) == ranges::next(rx.begin(), 4));
		VERIFY(ranges::min_element(rx, {}, Abs{}) == ranges::next(rx.begin(), 1));
		VERIFY(ranges::min_element(rx.begin(), rx.begin()) == rx.begin());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesMinElementTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace ranges_min_element_test

}	// namespace bksge_algorithm_test
