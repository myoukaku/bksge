/**
 *	@file	unit_test_fnd_numeric_ranges_partial_sum.cpp
 *
 *	@brief	ranges::partial_sum のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/numeric/ranges/partial_sum.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_numeric_test
{

namespace ranges_partial_sum_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	return true;
}

#undef VERIFY

GTEST_TEST(NumericTest, RangesPartialSumTest)
{
}

}	// namespace ranges_partial_sum_test

}	// namespace bksge_numeric_test
