/**
 *	@file	unit_test_fnd_numeric_ranges_transform_reduce.cpp
 *
 *	@brief	ranges::transform_reduce のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/numeric/ranges/transform_reduce.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_numeric_test
{

namespace ranges_transform_reduce_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	return true;
}

#undef VERIFY

GTEST_TEST(NumericTest, RangesTransformReduceTest)
{
}

}	// namespace ranges_transform_reduce_test

}	// namespace bksge_numeric_test
