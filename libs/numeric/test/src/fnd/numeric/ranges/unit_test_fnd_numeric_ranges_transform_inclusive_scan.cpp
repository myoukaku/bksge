/**
 *	@file	unit_test_fnd_numeric_ranges_transform_inclusive_scan.cpp
 *
 *	@brief	ranges::transform_inclusive_scan のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/numeric/ranges/transform_inclusive_scan.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_numeric_test
{

namespace ranges_transform_inclusive_scan_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	return true;
}

#undef VERIFY

GTEST_TEST(NumericTest, RangesTransformInclusiveScanTest)
{
}

}	// namespace ranges_transform_inclusive_scan_test

}	// namespace bksge_numeric_test
