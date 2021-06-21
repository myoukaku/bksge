/**
 *	@file	unit_test_fnd_cmath_remainder.cpp
 *
 *	@brief	remainder のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/remainder.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace remainder_test
{

static_assert(bksge::is_same<float,       decltype(bksge::remainder(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::remainderf(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::remainder(0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::remainder(0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::remainder(0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::remainder(0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::remainder(0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::remainder(0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::remainder(0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::remainder(0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::remainder(0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::remainder(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::remainderl(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::remainder(0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::remainder(0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::remainder(0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::remainder(0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::remainder(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void RemainderTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf1 = std::numeric_limits<T1>::infinity();
	BKSGE_CONSTEXPR auto inf2 = std::numeric_limits<T2>::infinity();

	using R = bksge::float_promote_t<T1, T2>;

	BKSGE_CONSTEXPR_EXPECT_EQ(R(-0.5), bksge::remainder(T1( 5.5), T2( 3.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.5), bksge::remainder(T1(-5.5), T2( 3.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-0.5), bksge::remainder(T1( 5.5), T2(-3.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.5), bksge::remainder(T1(-5.5), T2(-3.0)));

	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.5), bksge::remainder(T1( 5.5), T2( 2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-0.5), bksge::remainder(T1(-5.5), T2( 2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.5), bksge::remainder(T1( 5.5), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-0.5), bksge::remainder(T1(-5.5), T2(-2.5)));

	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::remainder(T1( 6.0), T2( 3.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-0.0), bksge::remainder(T1(-6.0), T2( 3.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::remainder(T1( 6.0), T2(-3.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-0.0), bksge::remainder(T1(-6.0), T2(-3.0)));

	BKSGE_CONSTEXPR_EXPECT_EQ(R( 1.0), bksge::remainder(T1( 6.0), T2( 2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-1.0), bksge::remainder(T1(-6.0), T2( 2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 1.0), bksge::remainder(T1( 6.0), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-1.0), bksge::remainder(T1(-6.0), T2(-2.5)));

	//If x is ±∞ and y is not NaN, NaN is returned and FE_INVALID is raised
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder( inf1, T2( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder(-inf1, T2( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder( inf1, T2(-2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder(-inf1, T2(-2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder( inf1, T2( 0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder(-inf1, T2( 0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder( inf1, inf2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder(-inf1, inf2)));

	//If y is ±0 and x is not NaN, NaN is returned and FE_INVALID is raised
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder(T1( 1.0), T2(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder(T1( 1.0), T2(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder(T1(-2.0), T2(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder(T1(-2.0), T2(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder(T1( 0.0), T2(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder(T1( 0.0), T2(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder(inf1,     T2(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder(inf1,     T2(-0.0))));

	//If either argument is NaN, NaN is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder(nan1, T2(1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder(nan1, T2(0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder(T1(1.0), nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder(inf1, nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remainder(nan1, nan2)));
}

template <typename T1, typename T2>
void RemainderTestInteger(void)
{
	using R = bksge::float_promote_t<T1, T2>;

	BKSGE_CONSTEXPR_EXPECT_EQ(R(-1), bksge::remainder(T1( 5), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 1), bksge::remainder(T1(-5), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-1), bksge::remainder(T1( 5), T2(-3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 1), bksge::remainder(T1(-5), T2(-3)));

	BKSGE_CONSTEXPR_EXPECT_EQ(R( 1), bksge::remainder(T1( 5), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-1), bksge::remainder(T1(-5), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 1), bksge::remainder(T1( 5), T2(-2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-1), bksge::remainder(T1(-5), T2(-2)));
}

GTEST_TEST(CMathTest, RemainderTest)
{
	RemainderTestFloat<float,       float>      ();
//	RemainderTestFloat<float,       double>     ();
	RemainderTestFloat<float,       long double>();
//	RemainderTestFloat<double,      float>      ();
	RemainderTestFloat<double,      double>     ();
//	RemainderTestFloat<double,      long double>();
	RemainderTestFloat<long double, float>      ();
//	RemainderTestFloat<long double, double>     ();
	RemainderTestFloat<long double, long double>();

//	RemainderTestInteger<int,         int>();
	RemainderTestInteger<int,         float>();
//	RemainderTestInteger<int,         double>();
	RemainderTestInteger<int,         long double>();
//	RemainderTestInteger<float,       int>();
	RemainderTestInteger<double,      int>();
//	RemainderTestInteger<long double, int>();
}

}	// namespace remainder_test

}	// namespace bksge_cmath_test
