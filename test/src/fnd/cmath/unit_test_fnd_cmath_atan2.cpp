/**
 *	@file	unit_test_fnd_cmath_atan2.cpp
 *
 *	@brief	atan2 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/atan2.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/cmath/constants.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace atan2_test
{

template <typename T1, typename T2>
void Atan2TestFloat(double error)
{
	using R = bksge::float_promote_t<T1, T2>;
	BKSGE_CONSTEXPR auto nan1 = bksge::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2 = bksge::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf1 = bksge::numeric_limits<T1>::infinity();
	BKSGE_CONSTEXPR auto inf2 = bksge::numeric_limits<T2>::infinity();

	BKSGE_CONSTEXPR auto pi                = bksge::pi<R>();
	BKSGE_CONSTEXPR auto half_pi           = bksge::half_pi<R>();
	BKSGE_CONSTEXPR auto three_quarters_pi = bksge::three_quarters_pi<R>();
	BKSGE_CONSTEXPR auto quarter_pi        = bksge::quarter_pi<R>();

	EXPECT_NEAR((double)pi *  0.00, (double)bksge::atan2(T1( 0.0), T2( 1.0)), error);
	EXPECT_NEAR((double)pi *  0.00, (double)bksge::atan2(T1( 0.0), T2( 2.0)), error);
	EXPECT_NEAR((double)pi *  0.00, (double)bksge::atan2(T1( 0.0), T2( 0.5)), error);
	EXPECT_NEAR((double)pi *  0.25, (double)bksge::atan2(T1( 1.0), T2( 1.0)), error);
	EXPECT_NEAR((double)pi *  0.25, (double)bksge::atan2(T1( 2.0), T2( 2.0)), error);
	EXPECT_NEAR((double)pi *  0.25, (double)bksge::atan2(T1( 0.5), T2( 0.5)), error);
	EXPECT_NEAR((double)pi *  0.50, (double)bksge::atan2(T1( 1.0), T2( 0.0)), error);
	EXPECT_NEAR((double)pi *  0.50, (double)bksge::atan2(T1( 2.0), T2( 0.0)), error);
	EXPECT_NEAR((double)pi *  0.50, (double)bksge::atan2(T1( 0.5), T2( 0.0)), error);
	EXPECT_NEAR((double)pi *  0.75, (double)bksge::atan2(T1( 1.0), T2(-1.0)), error);
	EXPECT_NEAR((double)pi *  0.75, (double)bksge::atan2(T1( 2.0), T2(-2.0)), error);
	EXPECT_NEAR((double)pi *  0.75, (double)bksge::atan2(T1( 0.5), T2(-0.5)), error);
	EXPECT_NEAR((double)pi *  1.00, (double)bksge::atan2(T1( 0.0), T2(-1.0)), error);
	EXPECT_NEAR((double)pi *  1.00, (double)bksge::atan2(T1( 0.0), T2(-2.0)), error);
	EXPECT_NEAR((double)pi *  1.00, (double)bksge::atan2(T1( 0.0), T2(-0.5)), error);
	EXPECT_NEAR((double)pi * -0.75, (double)bksge::atan2(T1(-1.0), T2(-1.0)), error);
	EXPECT_NEAR((double)pi * -0.75, (double)bksge::atan2(T1(-2.0), T2(-2.0)), error);
	EXPECT_NEAR((double)pi * -0.75, (double)bksge::atan2(T1(-0.5), T2(-0.5)), error);
	EXPECT_NEAR((double)pi * -0.50, (double)bksge::atan2(T1(-1.0), T2( 0.0)), error);
	EXPECT_NEAR((double)pi * -0.50, (double)bksge::atan2(T1(-2.0), T2( 0.0)), error);
	EXPECT_NEAR((double)pi * -0.50, (double)bksge::atan2(T1(-0.5), T2( 0.0)), error);
	EXPECT_NEAR((double)pi * -0.25, (double)bksge::atan2(T1(-1.0), T2( 1.0)), error);
	EXPECT_NEAR((double)pi * -0.25, (double)bksge::atan2(T1(-2.0), T2( 2.0)), error);
	EXPECT_NEAR((double)pi * -0.25, (double)bksge::atan2(T1(-0.5), T2( 0.5)), error);

	//If y is ±0 and x is negative or -0, ±π is returned
//	BKSGE_CONSTEXPR_EXPECT_NEAR( pi, (double)bksge::atan2(T1(+0.0), T2(-0.0)), error);
//	BKSGE_CONSTEXPR_EXPECT_NEAR(-pi, (double)bksge::atan2(T1(-0.0), T2(-0.0)), error);
	// ※BKSGEでは-0と+0を区別しない
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::atan2(T1(+0.0), T2(-0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::atan2(T1(-0.0), T2(-0.0)));

	BKSGE_CONSTEXPR_EXPECT_EQ( pi, bksge::atan2(T1(+0.0), T2(-1.0)));
//	BKSGE_CONSTEXPR_EXPECT_EQ(-pi, bksge::atan2(T1(-0.0), T2(-1.0)));
	// ※BKSGEでは-0と+0を区別しない
	BKSGE_CONSTEXPR_EXPECT_EQ( pi, bksge::atan2(T1(-0.0), T2(-1.0)));

	//If y is ±0 and x is positive or +0, ±0 is returned
	// ※BKSGEでは-0と+0を区別しない
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::atan2(T1(+0.0), T2(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::atan2(T1(-0.0), T2(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::atan2(T1(+0.0), T2(+1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::atan2(T1(-0.0), T2(+1.0)));

	//If y is ±∞ and x is finite, ±π/2 is returned
	BKSGE_CONSTEXPR_EXPECT_EQ( half_pi, bksge::atan2( inf1, T2(1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-half_pi, bksge::atan2(-inf1, T2(1.0)));

	//If y is ±∞ and x is -∞, ±3π/4 is returned
	BKSGE_CONSTEXPR_EXPECT_EQ( three_quarters_pi, bksge::atan2( inf1, -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(-three_quarters_pi, bksge::atan2(-inf1, -inf2));

	//If y is ±∞ and x is +∞, ±π/4 is returned
	BKSGE_CONSTEXPR_EXPECT_EQ( quarter_pi, bksge::atan2( inf1, inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(-quarter_pi, bksge::atan2(-inf1, inf2));

	//If x is ±0 and y is negative, -π/2 is returned
	BKSGE_CONSTEXPR_EXPECT_EQ(-half_pi, bksge::atan2(T1(-1.0), T2(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-half_pi, bksge::atan2(T1(-1.0), T2(-0.0)));

	//If x is ±0 and y is positive, +π/2 is returned
	BKSGE_CONSTEXPR_EXPECT_EQ(half_pi, bksge::atan2(T1(+1.0), T2(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(half_pi, bksge::atan2(T1(+1.0), T2(-0.0)));

	//If x is -∞ and y is finite and positive, +π is returned
	BKSGE_CONSTEXPR_EXPECT_EQ(pi, bksge::atan2(T1(+1.0), -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(pi, bksge::atan2(T1(+1.0), -inf2));

	//If x is -∞ and y is finite and negative, -π is returned
	BKSGE_CONSTEXPR_EXPECT_EQ(-pi, bksge::atan2(T1(-1.0), -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(-pi, bksge::atan2(T1(-1.0), -inf2));

	//If x is +∞ and y is finite and positive, +0 is returned
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::atan2(T1(+1.0), +inf2));

	//If x is +∞ and y is finite and negative, -0 is returned
	// ※BKSGEでは-0と+0を区別しない
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::atan2(T1(-1.0), +inf2));

	//If either x is NaN or y is NaN, NaN is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(+nan1,    T2(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(+nan1,    T2(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(+nan1,    T2(+1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(+nan1,    T2(-1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(+nan1,    +inf2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(+nan1,    -inf2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(-nan1,    T2(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(-nan1,    T2(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(-nan1,    T2(+1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(-nan1,    T2(-1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(-nan1,    +inf2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(-nan1,    -inf2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(T1(+0.0), +nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(T1(-0.0), +nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(T1(+1.0), +nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(T1(-1.0), +nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(+inf1,    +nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(-inf1,    +nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(T1(+0.0), -nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(T1(-0.0), -nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(T1(+1.0), -nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(T1(-1.0), -nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(+inf1,    -nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(-inf1,    -nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(+nan1,    +nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(+nan1,    -nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(-nan1,    +nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan2(-nan1,    -nan2)));
}

template <typename T1, typename T2>
void Atan2TestInteger(void)
{
	BKSGE_CONSTEXPR double error = 0.000000000001;

	BKSGE_CONSTEXPR auto pi = bksge::pi<double>();

	EXPECT_NEAR(pi *  0.00, (double)bksge::atan2(T1( 0), T2( 1)), error);
	EXPECT_NEAR(pi *  0.25, (double)bksge::atan2(T1( 1), T2( 1)), error);
	EXPECT_NEAR(pi *  0.50, (double)bksge::atan2(T1( 1), T2( 0)), error);
	EXPECT_NEAR(pi *  0.75, (double)bksge::atan2(T1( 1), T2(-1)), error);
	EXPECT_NEAR(pi *  1.00, (double)bksge::atan2(T1( 0), T2(-1)), error);
	EXPECT_NEAR(pi * -0.75, (double)bksge::atan2(T1(-1), T2(-1)), error);
	EXPECT_NEAR(pi * -0.50, (double)bksge::atan2(T1(-1), T2( 0)), error);
	EXPECT_NEAR(pi * -0.25, (double)bksge::atan2(T1(-1), T2( 1)), error);

	EXPECT_NEAR(pi *  0.00, (double)bksge::atan2(T1( 0), T2( 2)), error);
	EXPECT_NEAR(pi *  0.25, (double)bksge::atan2(T1( 2), T2( 2)), error);
	EXPECT_NEAR(pi *  0.50, (double)bksge::atan2(T1( 2), T2( 0)), error);
	EXPECT_NEAR(pi *  0.75, (double)bksge::atan2(T1( 2), T2(-2)), error);
	EXPECT_NEAR(pi *  1.00, (double)bksge::atan2(T1( 0), T2(-2)), error);
	EXPECT_NEAR(pi * -0.75, (double)bksge::atan2(T1(-2), T2(-2)), error);
	EXPECT_NEAR(pi * -0.50, (double)bksge::atan2(T1(-2), T2( 0)), error);
	EXPECT_NEAR(pi * -0.25, (double)bksge::atan2(T1(-2), T2( 2)), error);
}

GTEST_TEST(CMathTest, Atan2Test)
{
	Atan2TestFloat<float,       float>      (0.000001);
//	Atan2TestFloat<float,       double>     (0.000000000001);
	Atan2TestFloat<float,       long double>(0.000000000001);
//	Atan2TestFloat<double,      float>      (0.000000000001);
	Atan2TestFloat<double,      double>     (0.000000000001);
//	Atan2TestFloat<double,      long double>(0.000000000001);
	Atan2TestFloat<long double, float>      (0.000000000001);
//	Atan2TestFloat<long double, double>     (0.000000000001);
	Atan2TestFloat<long double, long double>(0.000000000001);

	Atan2TestInteger<int,         int>();
	Atan2TestInteger<int,         float>();
//	Atan2TestInteger<int,         double>();
	Atan2TestInteger<int,         long double>();
//	Atan2TestInteger<float,       int>();
	Atan2TestInteger<double,      int>();
	Atan2TestInteger<long double, int>();
}

}	// namespace atan2_test

}	// namespace bksge_cmath_test
