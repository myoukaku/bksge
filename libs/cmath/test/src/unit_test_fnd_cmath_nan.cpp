/**
 *	@file	unit_test_fnd_cmath_nan.cpp
 *
 *	@brief	nan のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/nan.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace nan_test
{

static_assert(bksge::is_same<float,       decltype(bksge::nanf(nullptr))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::nan (nullptr))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::nanl(nullptr))>::value, "");

GTEST_TEST(CMathTest, NanTest)
{
	EXPECT_TRUE(bksge::isnan(bksge::nanf("")));
	EXPECT_TRUE(bksge::isnan(bksge::nanf("1")));
	EXPECT_TRUE(bksge::isnan(bksge::nanf("2")));

	EXPECT_TRUE(bksge::isnan(bksge::nan("")));
	EXPECT_TRUE(bksge::isnan(bksge::nan("1")));
	EXPECT_TRUE(bksge::isnan(bksge::nan("2")));

	EXPECT_TRUE(bksge::isnan(bksge::nanl("")));
	EXPECT_TRUE(bksge::isnan(bksge::nanl("1")));
	EXPECT_TRUE(bksge::isnan(bksge::nanl("2")));
}

}	// namespace nan_test

}	// namespace bksge_cmath_test
