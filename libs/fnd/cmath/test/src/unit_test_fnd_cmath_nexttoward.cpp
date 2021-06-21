/**
 *	@file	unit_test_fnd_cmath_nexttoward.cpp
 *
 *	@brief	nexttoward のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/nexttoward.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace nexttoward_test
{

static_assert(bksge::is_same<float,       decltype(bksge::nexttoward(0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::nexttowardf(0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::nexttoward(0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::nexttoward(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::nexttowardl(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::nexttoward(0,    0.0l))>::value, "");

template <typename T>
void NextTowardTestFloat()
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::lowest();

	EXPECT_EQ(T(2.0), bksge::nexttoward(T(+2.0), T(+2.0)));
	EXPECT_LT(T(2.0), bksge::nexttoward(T(+2.0), T(+3.0)));
	EXPECT_GT(T(2.0), bksge::nexttoward(T(+2.0), T(+1.0)));
	EXPECT_EQ(bksge::nexttoward(T(+2.0), T(+3.0)), bksge::nexttoward(T(+2.0), +inf));
	EXPECT_EQ(bksge::nexttoward(T(+2.0), T(+1.0)), bksge::nexttoward(T(+2.0), -inf));
	EXPECT_LT(T(5.0), bksge::nexttoward(T(+5.0), +inf));
	EXPECT_GT(T(5.0), bksge::nexttoward(T(+5.0), -inf));
	EXPECT_EQ(max,  bksge::nexttoward(max, max));
	EXPECT_EQ(+inf, bksge::nexttoward(max, +inf));
	EXPECT_GT(max,  bksge::nexttoward(max, -inf));
	EXPECT_EQ(min,  bksge::nexttoward(min, min));
	EXPECT_EQ(-inf, bksge::nexttoward(min, -inf));
	EXPECT_LT(min,  bksge::nexttoward(min, +inf));

	EXPECT_EQ(max, bksge::nexttoward(+inf, T(0.0)));
	EXPECT_EQ(min, bksge::nexttoward(-inf, T(0.0)));

	// if either from or to is NaN, NaN is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nexttoward(nan,  T(1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nexttoward(nan,  min)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nexttoward(nan,  max)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nexttoward(nan,  +inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nexttoward(nan,  -inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nexttoward(T(1), nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nexttoward(min,  nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nexttoward(max,  nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nexttoward(+inf, nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nexttoward(-inf, nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::nexttoward(nan,  nan)));
}

GTEST_TEST(CMathTest, NextTowardTest)
{
	NextTowardTestFloat<float>();
	NextTowardTestFloat<double>();
	NextTowardTestFloat<long double>();
}

}	// namespace nexttoward_test

}	// namespace bksge_cmath_test
