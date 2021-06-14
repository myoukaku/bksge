/**
 *	@file	unit_test_fnd_cmath_nextafter.cpp
 *
 *	@brief	nextafter のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/nextafter.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace nextafter_test
{

static_assert(bksge::is_same<float,       decltype(bksge::nextafter(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::nextafterf(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::nextafter(0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::nextafter(0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::nextafter(0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::nextafter(0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::nextafter(0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::nextafter(0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::nextafter(0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::nextafter(0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::nextafter(0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::nextafter(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::nextafterl(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::nextafter(0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::nextafter(0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::nextafter(0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::nextafter(0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::nextafter(0   , 0   ))>::value, "");

template <typename T>
void NextAfterTestFloat()
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto max = bksge::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min = bksge::numeric_limits<T>::lowest();

	EXPECT_EQ(T(2.0), bksge::nextafter(T(+2.0), T(+2.0)));
	EXPECT_LT(T(2.0), bksge::nextafter(T(+2.0), T(+3.0)));
	EXPECT_GT(T(2.0), bksge::nextafter(T(+2.0), T(+1.0)));
	EXPECT_EQ(bksge::nextafter(T(+2.0), T(+3.0)), bksge::nextafter(T(+2.0), +inf));
	EXPECT_EQ(bksge::nextafter(T(+2.0), T(+1.0)), bksge::nextafter(T(+2.0), -inf));
	EXPECT_LT(T(5.0), bksge::nextafter(T(+5.0), +inf));
	EXPECT_GT(T(5.0), bksge::nextafter(T(+5.0), -inf));
	EXPECT_EQ(max,  bksge::nextafter(max, max));
	EXPECT_EQ(+inf, bksge::nextafter(max, +inf));
	EXPECT_GT(max,  bksge::nextafter(max, -inf));
	EXPECT_EQ(min,  bksge::nextafter(min, min));
	EXPECT_EQ(-inf, bksge::nextafter(min, -inf));
	EXPECT_LT(min,  bksge::nextafter(min, +inf));

	EXPECT_EQ(max, bksge::nextafter(+inf, T(0.0)));
	EXPECT_EQ(min, bksge::nextafter(-inf, T(0.0)));

	// if either from or to is NaN, NaN is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nextafter(nan,  T(1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nextafter(nan,  min)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nextafter(nan,  max)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nextafter(nan,  +inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nextafter(nan,  -inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nextafter(T(1), nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nextafter(min,  nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nextafter(max,  nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nextafter(+inf, nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nextafter(-inf, nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nextafter(nan,  nan)));
}

GTEST_TEST(CMathTest, NextAfterTest)
{
	NextAfterTestFloat<float>();
	NextAfterTestFloat<double>();
	NextAfterTestFloat<long double>();
}

}	// namespace nextafter_test

}	// namespace bksge_cmath_test
