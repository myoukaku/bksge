/**
 *	@file	unit_test_fnd_cmath_pow.cpp
 *
 *	@brief	pow のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/pow.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/cmath/constants.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace pow_test
{

template <typename T1, typename T2>
void PowTestFloat(double error)
{
	EXPECT_NEAR(8.0,               (double)bksge::pow(T1(2.0), T2( 3.0)), error);
	EXPECT_NEAR(4.0,               (double)bksge::pow(T1(2.0), T2( 2.0)), error);
	EXPECT_NEAR(2.0,               (double)bksge::pow(T1(2.0), T2( 1.0)), error);
	EXPECT_NEAR(1.414213562373095, (double)bksge::pow(T1(2.0), T2( 0.5)), error);
	EXPECT_NEAR(1.0,               (double)bksge::pow(T1(2.0), T2( 0.0)), error);
	EXPECT_NEAR(0.707106781186547, (double)bksge::pow(T1(2.0), T2(-0.5)), error);
	EXPECT_NEAR(0.5,               (double)bksge::pow(T1(2.0), T2(-1.0)), error);
	EXPECT_NEAR(0.25,              (double)bksge::pow(T1(2.0), T2(-2.0)), error);
	EXPECT_NEAR(0.125,             (double)bksge::pow(T1(2.0), T2(-3.0)), error);

	EXPECT_NEAR(15.625,            (double)bksge::pow(T1(2.5), T2( 3.0)), error);
	EXPECT_NEAR(6.25,              (double)bksge::pow(T1(2.5), T2( 2.0)), error);
	EXPECT_NEAR(2.5,               (double)bksge::pow(T1(2.5), T2( 1.0)), error);
	EXPECT_NEAR(1.58113883008419,  (double)bksge::pow(T1(2.5), T2( 0.5)), error);
	EXPECT_NEAR(1.0,               (double)bksge::pow(T1(2.5), T2( 0.0)), error);
	EXPECT_NEAR(0.6324555320336757,(double)bksge::pow(T1(2.5), T2(-0.5)), error);
	EXPECT_NEAR(0.4,               (double)bksge::pow(T1(2.5), T2(-1.0)), error);
	EXPECT_NEAR(0.16,              (double)bksge::pow(T1(2.5), T2(-2.0)), error);
	EXPECT_NEAR(0.064,             (double)bksge::pow(T1(2.5), T2(-3.0)), error);

	EXPECT_NEAR(27.0,              (double)bksge::pow(T1(3.0), T2( 3.0)), error);
	EXPECT_NEAR(9.0,               (double)bksge::pow(T1(3.0), T2( 2.0)), error);
	EXPECT_NEAR(3.0,               (double)bksge::pow(T1(3.0), T2( 1.0)), error);
	EXPECT_NEAR(1.732050807568877, (double)bksge::pow(T1(3.0), T2( 0.5)), error);
	EXPECT_NEAR(1.0,               (double)bksge::pow(T1(3.0), T2( 0.0)), error);
	EXPECT_NEAR(0.5773502691896259,(double)bksge::pow(T1(3.0), T2(-0.5)), error);
	EXPECT_NEAR(0.3333333333333333,(double)bksge::pow(T1(3.0), T2(-1.0)), error);
	EXPECT_NEAR(0.1111111111111111,(double)bksge::pow(T1(3.0), T2(-2.0)), error);
	EXPECT_NEAR(0.037037037037037, (double)bksge::pow(T1(3.0), T2(-3.0)), error);

	EXPECT_NEAR(-2.0,              (double)bksge::pow(T1(-2.0), T2( 1.0)), error);
	EXPECT_NEAR( 4.0,              (double)bksge::pow(T1(-2.0), T2( 2.0)), error);
	EXPECT_NEAR(-8.0,              (double)bksge::pow(T1(-2.0), T2( 3.0)), error);
	EXPECT_NEAR(-2.5,              (double)bksge::pow(T1(-2.5), T2( 1.0)), error);
	EXPECT_NEAR( 6.25,             (double)bksge::pow(T1(-2.5), T2( 2.0)), error);
	EXPECT_NEAR(-15.625,           (double)bksge::pow(T1(-2.5), T2( 3.0)), error);
	EXPECT_NEAR(-0.5,              (double)bksge::pow(T1(-2.0), T2(-1.0)), error);
	EXPECT_NEAR( 0.25,             (double)bksge::pow(T1(-2.0), T2(-2.0)), error);
	EXPECT_NEAR(-0.125,            (double)bksge::pow(T1(-2.0), T2(-3.0)), error);
	EXPECT_NEAR(-0.4,              (double)bksge::pow(T1(-2.5), T2(-1.0)), error);
	EXPECT_NEAR( 0.16,             (double)bksge::pow(T1(-2.5), T2(-2.0)), error);
	EXPECT_NEAR(-0.064,            (double)bksge::pow(T1(-2.5), T2(-3.0)), error);
}

template <typename T>
void PowTestErrorHandling(void)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	// pow(+0, exp), where exp is a negative odd integer, returns +∞ and raises FE_DIVBYZERO
	EXPECT_EQ( inf, bksge::pow(T(+0.0), T(-3.0)));
	EXPECT_EQ( inf, bksge::pow(T(+0.0), T(-5.0)));

	// pow(-0, exp), where exp is a negative odd integer, returns -∞ and raises FE_DIVBYZERO
//	EXPECT_EQ(-inf, bksge::pow(T(-0.0), T(-3.0)));
//	EXPECT_EQ(-inf, bksge::pow(T(-0.0), T(-5.0)));
	// ※BKSGEでは-0と+0を区別しない
	EXPECT_EQ( inf, bksge::pow(T(-0.0), T(-3.0)));
	EXPECT_EQ( inf, bksge::pow(T(-0.0), T(-5.0)));

	// pow(±0, exp), where exp is negative, finite, and is an even integer or a non-integer, returns +∞ and raises FE_DIVBYZERO
	EXPECT_EQ( inf, bksge::pow(T(+0.0), T(-2.0)));
	EXPECT_EQ( inf, bksge::pow(T(-0.0), T(-2.0)));
	EXPECT_EQ( inf, bksge::pow(T(+0.0), T(-0.5)));
	EXPECT_EQ( inf, bksge::pow(T(-0.0), T(-0.5)));

	// pow(±0, -∞) returns +∞ and may raise FE_DIVBYZERO
	EXPECT_EQ( inf, bksge::pow(T(+0.0), -inf));
	EXPECT_EQ( inf, bksge::pow(T(-0.0), -inf));

	// pow(+0, exp), where exp is a positive odd integer, returns +0
	EXPECT_EQ   (T(+0.0),       bksge::pow(T(+0.0), T(3.0)));
	EXPECT_EQ   (T(+0.0),       bksge::pow(T(+0.0), T(5.0)));
	EXPECT_TRUE (bksge::iszero (bksge::pow(T(+0.0), T(3.0))));
	EXPECT_TRUE (bksge::iszero (bksge::pow(T(+0.0), T(5.0))));
	EXPECT_FALSE(bksge::signbit(bksge::pow(T(+0.0), T(3.0))));
	EXPECT_FALSE(bksge::signbit(bksge::pow(T(+0.0), T(5.0))));

	// pow(-0, exp), where exp is a positive odd integer, returns -0
	EXPECT_EQ   (T(-0.0),       bksge::pow(T(-0.0), T(3.0)));
	EXPECT_EQ   (T(-0.0),       bksge::pow(T(-0.0), T(5.0)));
	EXPECT_TRUE (bksge::iszero (bksge::pow(T(-0.0), T(3.0))));
	EXPECT_TRUE (bksge::iszero (bksge::pow(T(-0.0), T(5.0))));
	EXPECT_FALSE(bksge::signbit(bksge::pow(T(-0.0), T(3.0))));
	EXPECT_FALSE(bksge::signbit(bksge::pow(T(-0.0), T(5.0))));

	// pow(±0, exp), where exp is positive non-integer or a positive even integer, returns +0
	EXPECT_EQ   (T( 0),         bksge::pow(T(+0.0), T(0.5)));
	EXPECT_EQ   (T( 0),         bksge::pow(T(-0.0), T(0.5)));
	EXPECT_EQ   (T( 0),         bksge::pow(T(+0.0), T(2.0)));
	EXPECT_EQ   (T( 0),         bksge::pow(T(-0.0), T(2.0)));
	EXPECT_TRUE (bksge::iszero (bksge::pow(T(+0.0), T(0.5))));
	EXPECT_TRUE (bksge::iszero (bksge::pow(T(-0.0), T(0.5))));
	EXPECT_TRUE (bksge::iszero (bksge::pow(T(+0.0), T(2.0))));
	EXPECT_TRUE (bksge::iszero (bksge::pow(T(-0.0), T(2.0))));
	EXPECT_FALSE(bksge::signbit(bksge::pow(T(+0.0), T(0.5))));
	EXPECT_FALSE(bksge::signbit(bksge::pow(T(-0.0), T(0.5))));
	EXPECT_FALSE(bksge::signbit(bksge::pow(T(+0.0), T(2.0))));
	EXPECT_FALSE(bksge::signbit(bksge::pow(T(-0.0), T(2.0))));

	// pow(-1, ±∞) returns 1
	EXPECT_EQ(T( 1), bksge::pow(T(-1.0),  inf));
	EXPECT_EQ(T( 1), bksge::pow(T(-1.0), -inf));

	// pow(+1, exp) returns 1 for any exp, even when exp is NaN
	EXPECT_EQ(T( 1), bksge::pow(T( 1.0), T( 0.0)));
	EXPECT_EQ(T( 1), bksge::pow(T( 1.0), T( 1.0)));
	EXPECT_EQ(T( 1), bksge::pow(T( 1.0), T(-1.0)));
	EXPECT_EQ(T( 1), bksge::pow(T( 1.0), T( 2.0)));
	EXPECT_EQ(T( 1), bksge::pow(T( 1.0), T(-2.0)));
	EXPECT_EQ(T( 1), bksge::pow(T( 1.0),  inf));
	EXPECT_EQ(T( 1), bksge::pow(T( 1.0), -inf));
	EXPECT_EQ(T( 1), bksge::pow(T( 1.0),  nan));
	EXPECT_EQ(T( 1), bksge::pow(T( 1.0), -nan));

	// pow(base, ±0) returns 1 for any base, even when base is NaN
	EXPECT_EQ(T( 1), bksge::pow(T( 2.0), T( 0.0)));
	EXPECT_EQ(T( 1), bksge::pow(T( 2.0), T(-0.0)));
	EXPECT_EQ(T( 1), bksge::pow(T( 3.0), T( 0.0)));
	EXPECT_EQ(T( 1), bksge::pow(T( 3.0), T(-0.0)));
	EXPECT_EQ(T( 1), bksge::pow(T(-2.0), T( 0.0)));
	EXPECT_EQ(T( 1), bksge::pow(T(-2.0), T(-0.0)));
	EXPECT_EQ(T( 1), bksge::pow(T(-3.0), T( 0.0)));
	EXPECT_EQ(T( 1), bksge::pow(T(-3.0), T(-0.0)));
	EXPECT_EQ(T( 1), bksge::pow( inf, T( 0.0)));
	EXPECT_EQ(T( 1), bksge::pow( inf, T(-0.0)));
	EXPECT_EQ(T( 1), bksge::pow(-inf, T( 0.0)));
	EXPECT_EQ(T( 1), bksge::pow(-inf, T(-0.0)));
	EXPECT_EQ(T( 1), bksge::pow( nan, T( 0.0)));
	EXPECT_EQ(T( 1), bksge::pow( nan, T(-0.0)));
	EXPECT_EQ(T( 1), bksge::pow(-nan, T( 0.0)));
	EXPECT_EQ(T( 1), bksge::pow(-nan, T(-0.0)));

	// pow(base, exp) returns NaN and raises FE_INVALID if base is finite and negative and exp is finite and non-integer.
	EXPECT_TRUE(bksge::isnan(bksge::pow(T(-2.0), T( 0.5))));
	EXPECT_TRUE(bksge::isnan(bksge::pow(T(-2.0), T(-0.5))));
	EXPECT_TRUE(bksge::isnan(bksge::pow(T(-2.0), T( 1.5))));
	EXPECT_TRUE(bksge::isnan(bksge::pow(T(-2.0), T(-1.5))));
	EXPECT_TRUE(bksge::isnan(bksge::pow(T(-0.5), T( 2.5))));
	EXPECT_TRUE(bksge::isnan(bksge::pow(T(-0.5), T(-2.5))));

	// pow(base, -∞) returns +∞ for any |base|<1
	EXPECT_EQ(inf, bksge::pow(T( 0.5), -inf));
	EXPECT_EQ(inf, bksge::pow(T(-0.5), -inf));
	EXPECT_EQ(inf, bksge::pow(T( 0.0), -inf));
	EXPECT_EQ(inf, bksge::pow(T(-0.0), -inf));

	// pow(base, -∞) returns +0 for any |base|>1
	EXPECT_TRUE (bksge::iszero (bksge::pow(T( 1.5), -inf)));
	EXPECT_TRUE (bksge::iszero (bksge::pow(T(-1.5), -inf)));
	EXPECT_FALSE(bksge::signbit(bksge::pow(T( 1.5), -inf)));
	EXPECT_FALSE(bksge::signbit(bksge::pow(T(-1.5), -inf)));

	// pow(base, +∞) returns +0 for any |base|<1
	EXPECT_TRUE (bksge::iszero (bksge::pow(T( 0.5), inf)));
	EXPECT_TRUE (bksge::iszero (bksge::pow(T(-0.5), inf)));
	EXPECT_FALSE(bksge::signbit(bksge::pow(T( 0.5), inf)));
	EXPECT_FALSE(bksge::signbit(bksge::pow(T(-0.5), inf)));
	EXPECT_TRUE (bksge::iszero (bksge::pow(T( 0.0), inf)));
	EXPECT_TRUE (bksge::iszero (bksge::pow(T(-0.0), inf)));
	EXPECT_FALSE(bksge::signbit(bksge::pow(T( 0.0), inf)));
	EXPECT_FALSE(bksge::signbit(bksge::pow(T(-0.0), inf)));

	// pow(base, +∞) returns +∞ for any |base|>1
	EXPECT_EQ(inf, bksge::pow(T( 1.5), inf));
	EXPECT_EQ(inf, bksge::pow(T(-1.5), inf));

	// pow(-∞, exp) returns -0 if exp is a negative odd integer
	EXPECT_EQ   (T(-0.0),       bksge::pow(-inf, T(-3.0)));
	EXPECT_EQ   (T(-0.0),       bksge::pow(-inf, T(-5.0)));
	EXPECT_TRUE (bksge::iszero (bksge::pow(-inf, T(-3.0))));
	EXPECT_TRUE (bksge::iszero (bksge::pow(-inf, T(-5.0))));
	EXPECT_FALSE(bksge::signbit(bksge::pow(-inf, T(-3.0))));
	EXPECT_FALSE(bksge::signbit(bksge::pow(-inf, T(-5.0))));

	// pow(-∞, exp) returns +0 if exp is a negative non-integer or even integer
	EXPECT_EQ   (T(+0.0),       bksge::pow(-inf, T(-2.0)));
	EXPECT_EQ   (T(+0.0),       bksge::pow(-inf, T(-4.0)));
	EXPECT_EQ   (T(+0.0),       bksge::pow(-inf, T(-0.5)));
	EXPECT_TRUE (bksge::iszero (bksge::pow(-inf, T(-2.0))));
	EXPECT_TRUE (bksge::iszero (bksge::pow(-inf, T(-4.0))));
	EXPECT_TRUE (bksge::iszero (bksge::pow(-inf, T(-0.5))));
	EXPECT_FALSE(bksge::signbit(bksge::pow(-inf, T(-2.0))));
	EXPECT_FALSE(bksge::signbit(bksge::pow(-inf, T(-4.0))));
	EXPECT_FALSE(bksge::signbit(bksge::pow(-inf, T(-0.5))));

	// pow(-∞, exp) returns -∞ if exp is a positive odd integer
	EXPECT_EQ(-inf, bksge::pow(-inf, T(3.0)));
	EXPECT_EQ(-inf, bksge::pow(-inf, T(5.0)));

	// pow(-∞, exp) returns +∞ if exp is a positive non-integer or even integer
	EXPECT_EQ(inf, bksge::pow(-inf, T(2.0)));
	EXPECT_EQ(inf, bksge::pow(-inf, T(4.0)));
	EXPECT_EQ(inf, bksge::pow(-inf, T(0.5)));

	// pow(+∞, exp) returns +0 for any negative exp
	EXPECT_EQ   (T(+0.0),       bksge::pow(inf, T(-0.5)));
	EXPECT_EQ   (T(+0.0),       bksge::pow(inf, T(-2.0)));
	EXPECT_EQ   (T(+0.0),       bksge::pow(inf, T(-3.0)));
	EXPECT_EQ   (T(+0.0),       bksge::pow(inf, -inf));
	EXPECT_TRUE (bksge::iszero (bksge::pow(inf, T(-0.5))));
	EXPECT_TRUE (bksge::iszero (bksge::pow(inf, T(-2.0))));
	EXPECT_TRUE (bksge::iszero (bksge::pow(inf, T(-3.0))));
	EXPECT_TRUE (bksge::iszero (bksge::pow(inf, -inf)));
	EXPECT_FALSE(bksge::signbit(bksge::pow(inf, T(-0.5))));
	EXPECT_FALSE(bksge::signbit(bksge::pow(inf, T(-2.0))));
	EXPECT_FALSE(bksge::signbit(bksge::pow(inf, T(-3.0))));
	EXPECT_FALSE(bksge::signbit(bksge::pow(inf, -inf)));

	// pow(+∞, exp) returns +∞ for any positive exp
	EXPECT_EQ(inf, bksge::pow(inf, T(0.5)));
	EXPECT_EQ(inf, bksge::pow(inf, T(2.0)));
	EXPECT_EQ(inf, bksge::pow(inf, T(3.0)));
	EXPECT_EQ(inf, bksge::pow(inf, inf));
}

template <typename T1, typename T2>
void PowTestInteger(void)
{
	const double error = 0.0000001;

	EXPECT_NEAR(8.0,   (double)bksge::pow(T1(2), T2( 3)), error);
	EXPECT_NEAR(4.0,   (double)bksge::pow(T1(2), T2( 2)), error);
	EXPECT_NEAR(2.0,   (double)bksge::pow(T1(2), T2( 1)), error);
	EXPECT_NEAR(1.0,   (double)bksge::pow(T1(2), T2( 0)), error);
	EXPECT_NEAR(0.5,   (double)bksge::pow(T1(2), T2(-1)), error);
	EXPECT_NEAR(0.25,  (double)bksge::pow(T1(2), T2(-2)), error);
	EXPECT_NEAR(0.125, (double)bksge::pow(T1(2), T2(-3)), error);

	EXPECT_NEAR(27.0,      (double)bksge::pow(T1(3), T2( 3)), error);
	EXPECT_NEAR( 9.0,      (double)bksge::pow(T1(3), T2( 2)), error);
	EXPECT_NEAR( 3.0,      (double)bksge::pow(T1(3), T2( 1)), error);
	EXPECT_NEAR( 1.0,      (double)bksge::pow(T1(3), T2( 0)), error);
	EXPECT_NEAR(1.0 / 3.0, (double)bksge::pow(T1(3), T2(-1)), error);
	EXPECT_NEAR(1.0 / 9.0, (double)bksge::pow(T1(3), T2(-2)), error);
}

GTEST_TEST(CMathTest, PowTest)
{
	PowTestFloat<float,       float>      (0.00001);
//	PowTestFloat<float,       double>     (0.00000000001);
	PowTestFloat<float,       long double>(0.00000000001);
//	PowTestFloat<double,      float>      (0.00000000001);
	PowTestFloat<double,      double>     (0.00000000001);
//	PowTestFloat<double,      long double>(0.00000000001);
	PowTestFloat<long double, float>      (0.00000000001);
//	PowTestFloat<long double, double>     (0.00000000001);
	PowTestFloat<long double, long double>(0.00000000001);

	PowTestErrorHandling<float>();
	PowTestErrorHandling<double>();
	PowTestErrorHandling<long double>();

//	PowTestInteger<int, int>();
	PowTestInteger<int, float>();
//	PowTestInteger<int, double>();
	PowTestInteger<int, long double>();
//	PowTestInteger<float, int>();
	PowTestInteger<double, int>();
//	PowTestInteger<long double, int>();
}

}	// namespace pow_test

}	// namespace bksge_cmath_test
