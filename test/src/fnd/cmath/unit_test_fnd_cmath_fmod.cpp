/**
 *	@file	unit_test_fnd_cmath_fmod.cpp
 *
 *	@brief	fmod のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/fmod.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace fmod_test
{

static_assert(bksge::is_same<float,       decltype(bksge::fmod(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::fmodf(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmod(0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmod(0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmod(0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmod(0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmod(0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmod(0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmod(0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmod(0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmod(0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmod(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmodl(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmod(0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmod(0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmod(0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmod(0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmod(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void FmodTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan1 = bksge::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2 = bksge::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf1 = bksge::numeric_limits<T1>::infinity();
	BKSGE_CONSTEXPR auto inf2 = bksge::numeric_limits<T2>::infinity();

	using R = bksge::float_promote_t<T1, T2>;

	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2.5), bksge::fmod(T1( 5.5), T2( 3.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2.5), bksge::fmod(T1(-5.5), T2( 3.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2.5), bksge::fmod(T1( 5.5), T2(-3.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2.5), bksge::fmod(T1(-5.5), T2(-3.0)));

	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.5), bksge::fmod(T1( 5.5), T2( 2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-0.5), bksge::fmod(T1(-5.5), T2( 2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.5), bksge::fmod(T1( 5.5), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-0.5), bksge::fmod(T1(-5.5), T2(-2.5)));

	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::fmod(T1( 7.5), T2( 2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-0.0), bksge::fmod(T1(-7.5), T2( 2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::fmod(T1( 7.5), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-0.0), bksge::fmod(T1(-7.5), T2(-2.5)));

	//If x is ±0 and y is not zero, ±0 is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::fmod(T1(+0.0), T2( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::fmod(T1(-0.0), T2( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::fmod(T1(+0.0), T2( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::fmod(T1(-0.0), T2( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::fmod(T1(+0.0), T2(-2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::fmod(T1(-0.0), T2(-2.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::fmod(T1(+0.0), T2(-2.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::fmod(T1(-0.0), T2(-2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::fmod(T1(+0.0), inf2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::fmod(T1(-0.0), inf2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::fmod(T1(+0.0), inf2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::fmod(T1(-0.0), inf2)));

	//If x is ±∞ and y is not NaN, NaN is returned and FE_INVALID is raised
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod( inf1, T2( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(-inf1, T2( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod( inf1, T2(-2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(-inf1, T2(-2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod( inf1, T2( 0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(-inf1, T2( 0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod( inf1, inf2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(-inf1, inf2)));

	//If y is ±0 and x is not NaN, NaN is returned and FE_INVALID is raised
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(T1( 1.0), T2(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(T1( 1.0), T2(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(T1(-2.0), T2(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(T1(-2.0), T2(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(T1( 0.0), T2(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(T1( 0.0), T2(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(inf1,     T2(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(inf1,     T2(-0.0))));

	//If y is ±∞ and x is finite, x is returned.
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 1.0), bksge::fmod(T1( 1.0), +inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 1.0), bksge::fmod(T1( 1.0), -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2.0), bksge::fmod(T1(-2.0), +inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2.0), bksge::fmod(T1(-2.0), -inf2));

	//If either argument is NaN, NaN is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(nan1, T2(1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(T1(1.0), nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(nan1, nan2)));
}

template <typename T1, typename T2>
void FmodTestInteger(void)
{
	using R = bksge::float_promote_t<T1, T2>;

	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2), bksge::fmod(T1( 5), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2), bksge::fmod(T1(-5), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2), bksge::fmod(T1( 5), T2(-3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2), bksge::fmod(T1(-5), T2(-3)));

	BKSGE_CONSTEXPR_EXPECT_EQ(R( 3), bksge::fmod(T1( 7), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-3), bksge::fmod(T1(-7), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 3), bksge::fmod(T1( 7), T2(-4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-3), bksge::fmod(T1(-7), T2(-4)));
}

GTEST_TEST(CMathTest, FmodTest)
{
//	FmodTestFloat<float,       float>      ();
	FmodTestFloat<float,       double>     ();
//	FmodTestFloat<float,       long double>();
	FmodTestFloat<double,      float>      ();
//	FmodTestFloat<double,      double>     ();
	FmodTestFloat<double,      long double>();
//	FmodTestFloat<long double, float>      ();
	FmodTestFloat<long double, double>     ();
//	FmodTestFloat<long double, long double>();

	FmodTestInteger<int,         int>();
//	FmodTestInteger<int,         float>();
	FmodTestInteger<int,         double>();
//	FmodTestInteger<int,         long double>();
	FmodTestInteger<float,       int>();
//	FmodTestInteger<double,      int>();
	FmodTestInteger<long double, int>();
}

}	// namespace fmod_test

}	// namespace bksge_cmath_test
