/**
 *	@file	unit_test_fnd_cmath_smoothstep.cpp
 *
 *	@brief	smoothstep のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/smoothstep.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace smoothstep_test
{

static_assert(bksge::is_same<float,       decltype(bksge::smoothstep(0.0f, 0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0.0f, 0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0f, 0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0.0f, 0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0.0f, 0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0.0f, 0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0f, 0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0.0f, 0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0f, 0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0f, 0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0f, 0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0f, 0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0.0f, 0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0.0f, 0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0f, 0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0.0f, 0   , 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0.0 , 0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0.0 , 0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0 , 0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0.0 , 0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0.0 , 0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0.0 , 0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0 , 0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0.0 , 0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0 , 0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0 , 0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0 , 0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0 , 0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0.0 , 0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0.0 , 0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0 , 0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0.0 , 0   , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0l, 0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0l, 0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0l, 0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0l, 0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0l, 0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0l, 0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0l, 0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0l, 0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0l, 0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0l, 0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0l, 0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0l, 0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0l, 0   , 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0l, 0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0l, 0   , 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0.0l, 0   , 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0   , 0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0   , 0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0   , 0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0   , 0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0   , 0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0   , 0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0   , 0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0   , 0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0   , 0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0   , 0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0   , 0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0   , 0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0   , 0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0   , 0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::smoothstep(0   , 0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::smoothstep(0   , 0   , 0   ))>::value, "");

template <typename T1, typename T2, typename T3>
void SmoothStepTestFloat(void)
{
	BKSGE_CONSTEXPR double error = 0.0000001;

	BKSGE_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan3 = std::numeric_limits<T3>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf1 = std::numeric_limits<T1>::infinity();
	BKSGE_CONSTEXPR auto inf2 = std::numeric_limits<T2>::infinity();
	BKSGE_CONSTEXPR auto inf3 = std::numeric_limits<T3>::infinity();

	BKSGE_CONSTEXPR_EXPECT_NEAR(0.00000, (double)bksge::smoothstep(T1(  0.0), T2( 1.0), -inf3), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.00000, (double)bksge::smoothstep(T1(  0.0), T2( 1.0), T3( -1.00)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.00000, (double)bksge::smoothstep(T1(  0.0), T2( 1.0), T3( -0.10)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.00000, (double)bksge::smoothstep(T1(  0.0), T2( 1.0), T3(  0.00)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.02800, (double)bksge::smoothstep(T1(  0.0), T2( 1.0), T3(  0.10)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.15625, (double)bksge::smoothstep(T1(  0.0), T2( 1.0), T3(  0.25)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.50000, (double)bksge::smoothstep(T1(  0.0), T2( 1.0), T3(  0.50)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.84375, (double)bksge::smoothstep(T1(  0.0), T2( 1.0), T3(  0.75)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(1.00000, (double)bksge::smoothstep(T1(  0.0), T2( 1.0), T3(  1.00)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(1.00000, (double)bksge::smoothstep(T1(  0.0), T2( 1.0), T3(  2.00)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.00000, (double)bksge::smoothstep(T1(  0.0), T2(10.0), T3(  0.00)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.00725, (double)bksge::smoothstep(T1(  0.0), T2(10.0), T3(  0.50)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.02800, (double)bksge::smoothstep(T1(  0.0), T2(10.0), T3(  1.00)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.50000, (double)bksge::smoothstep(T1(  0.0), T2(10.0), T3(  5.00)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.97200, (double)bksge::smoothstep(T1(  0.0), T2(10.0), T3(  9.00)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.99275, (double)bksge::smoothstep(T1(  0.0), T2(10.0), T3(  9.50)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(1.00000, (double)bksge::smoothstep(T1(  0.0), T2(10.0), T3( 10.00)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(1.00000, (double)bksge::smoothstep(T1(  0.0), T2(10.0), T3( 10.10)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(1.00000, (double)bksge::smoothstep(T1(  0.0), T2(10.0), inf3), error);

	BKSGE_CONSTEXPR_EXPECT_NEAR(0.000000, (double)bksge::smoothstep(T1( -5.0), T2( 0.0), T3(-6.0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.000000, (double)bksge::smoothstep(T1( -5.0), T2( 0.0), T3(-5.1)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.000000, (double)bksge::smoothstep(T1( -5.0), T2( 0.0), T3(-5.0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.001184, (double)bksge::smoothstep(T1( -5.0), T2( 0.0), T3(-4.9)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.104000, (double)bksge::smoothstep(T1( -5.0), T2( 0.0), T3(-4.0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.352000, (double)bksge::smoothstep(T1( -5.0), T2( 0.0), T3(-3.0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.500000, (double)bksge::smoothstep(T1( -5.0), T2( 0.0), T3(-2.5)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.648000, (double)bksge::smoothstep(T1( -5.0), T2( 0.0), T3(-2.0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.896000, (double)bksge::smoothstep(T1( -5.0), T2( 0.0), T3(-1.0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.998816, (double)bksge::smoothstep(T1( -5.0), T2( 0.0), T3(-0.1)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(1.000000, (double)bksge::smoothstep(T1( -5.0), T2( 0.0), T3( 0.0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(1.000000, (double)bksge::smoothstep(T1( -5.0), T2( 0.0), T3( 0.1)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(1.000000, (double)bksge::smoothstep(T1( -5.0), T2( 0.0), T3( 1.0)), error);

	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::smoothstep(T1( 1.0), T2( 1.0), T3(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::smoothstep(T1( 1.0), T2( 1.0), T3( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1.0, bksge::smoothstep(T1( 1.0), T2( 1.0), T3( 1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1.0, bksge::smoothstep(T1( 1.0), T2( 1.0), T3( 2.0)));

	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::smoothstep(T1( 10.0), T2( 10.0), T3(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::smoothstep(T1( 10.0), T2( 10.0), T3( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::smoothstep(T1( 10.0), T2( 10.0), T3( 9.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::smoothstep(T1( 10.0), T2( 10.0), T3( 9.9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1.0, bksge::smoothstep(T1( 10.0), T2( 10.0), T3(10.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1.0, bksge::smoothstep(T1( 10.0), T2( 10.0), T3(10.1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1.0, bksge::smoothstep(T1( 10.0), T2( 10.0), T3(11.0)));

	BKSGE_CONSTEXPR_EXPECT_EQ  (1.0,         bksge::smoothstep(-inf1, inf2,   inf3));
	BKSGE_CONSTEXPR_EXPECT_EQ  (0.0,         bksge::smoothstep(-inf1, inf2,  -inf3));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::smoothstep(-inf1, inf2,   T3(-1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::smoothstep(-inf1, inf2,   T3( 0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::smoothstep(-inf1, inf2,   T3( 1))));
	BKSGE_CONSTEXPR_EXPECT_EQ  (1.0,         bksge::smoothstep(inf1,  inf2,   inf3));
	BKSGE_CONSTEXPR_EXPECT_EQ  (0.0,         bksge::smoothstep(inf1,  inf2,  -inf3));
	BKSGE_CONSTEXPR_EXPECT_EQ  (0.0,         bksge::smoothstep(inf1,  inf2,   T3(-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ  (0.0,         bksge::smoothstep(inf1,  inf2,   T3( 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ  (0.0,         bksge::smoothstep(inf1,  inf2,   T3( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ  (1.0,         bksge::smoothstep(-inf1,-inf2,   inf3));
	BKSGE_CONSTEXPR_EXPECT_EQ  (1.0,         bksge::smoothstep(-inf1,-inf2,  -inf3));
	BKSGE_CONSTEXPR_EXPECT_EQ  (1.0,         bksge::smoothstep(-inf1,-inf2,   T3(-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ  (1.0,         bksge::smoothstep(-inf1,-inf2,   T3( 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ  (1.0,         bksge::smoothstep(-inf1,-inf2,   T3( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ  (1.0,         bksge::smoothstep(-inf1, T2(0),  inf3));
	BKSGE_CONSTEXPR_EXPECT_EQ  (0.0,         bksge::smoothstep(-inf1, T2(0), -inf3));
	BKSGE_CONSTEXPR_EXPECT_EQ  (1.0,         bksge::smoothstep(-inf1, T2(0),  T3(-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ  (1.0,         bksge::smoothstep(-inf1, T2(0),  T3( 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ  (1.0,         bksge::smoothstep(-inf1, T2(0),  T3( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ  (1.0,         bksge::smoothstep(T1(0), inf2,   inf3));
	BKSGE_CONSTEXPR_EXPECT_EQ  (0.0,         bksge::smoothstep(T1(0), inf2,  -inf3));
	BKSGE_CONSTEXPR_EXPECT_EQ  (0.0,         bksge::smoothstep(T1(0), inf2,   T3(-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ  (0.0,         bksge::smoothstep(T1(0), inf2,   T3( 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ  (0.0,         bksge::smoothstep(T1(0), inf2,   T3( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ  (1.0,         bksge::smoothstep(T1(0), T2(0),  inf3));
	BKSGE_CONSTEXPR_EXPECT_EQ  (0.0,         bksge::smoothstep(T1(0), T2(0), -inf3));
	BKSGE_CONSTEXPR_EXPECT_EQ  (0.0,         bksge::smoothstep(T1(0), T2(0),  T3(-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ  (1.0,         bksge::smoothstep(T1(0), T2(0),  T3( 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ  (1.0,         bksge::smoothstep(T1(0), T2(0),  T3( 1)));

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan(bksge::smoothstep(T1( 1.0), T2( 0.0), T3(0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan(bksge::smoothstep(T1(-1.0), T2(-2.0), T3(0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan(bksge::smoothstep(T1(10.0), T2( 9.0), T3(0.0))));

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan(bksge::smoothstep(nan1,  nan2,  nan3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan(bksge::smoothstep(nan1,  nan2,  T3(0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan(bksge::smoothstep(nan1,  T2(0), nan3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan(bksge::smoothstep(nan1,  T2(0), T3(0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan(bksge::smoothstep(T1(0), nan2,  nan3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan(bksge::smoothstep(T1(0), nan2,  T3(0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan(bksge::smoothstep(T1(0), T2(0), nan3)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(bksge::smoothstep(T1(0), T2(0), T3(0))));
}

template <typename T1, typename T2, typename T3>
void SmoothStepTestInteger(void)
{
	BKSGE_CONSTEXPR double error = 0.000000000000001;

	BKSGE_CONSTEXPR_EXPECT_NEAR(0.00000, (double)bksge::smoothstep(T1(-10), T2(10), T3(-99)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.00000, (double)bksge::smoothstep(T1(-10), T2(10), T3(-11)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.00000, (double)bksge::smoothstep(T1(-10), T2(10), T3(-10)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.00725, (double)bksge::smoothstep(T1(-10), T2(10), T3( -9)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.02800, (double)bksge::smoothstep(T1(-10), T2(10), T3( -8)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.06075, (double)bksge::smoothstep(T1(-10), T2(10), T3( -7)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.10400, (double)bksge::smoothstep(T1(-10), T2(10), T3( -6)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.15625, (double)bksge::smoothstep(T1(-10), T2(10), T3( -5)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.21600, (double)bksge::smoothstep(T1(-10), T2(10), T3( -4)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.28175, (double)bksge::smoothstep(T1(-10), T2(10), T3( -3)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.35200, (double)bksge::smoothstep(T1(-10), T2(10), T3( -2)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.42525, (double)bksge::smoothstep(T1(-10), T2(10), T3( -1)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.50000, (double)bksge::smoothstep(T1(-10), T2(10), T3(  0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.57475, (double)bksge::smoothstep(T1(-10), T2(10), T3(  1)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.64800, (double)bksge::smoothstep(T1(-10), T2(10), T3(  2)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.71825, (double)bksge::smoothstep(T1(-10), T2(10), T3(  3)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.78400, (double)bksge::smoothstep(T1(-10), T2(10), T3(  4)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.84375, (double)bksge::smoothstep(T1(-10), T2(10), T3(  5)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.89600, (double)bksge::smoothstep(T1(-10), T2(10), T3(  6)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.93925, (double)bksge::smoothstep(T1(-10), T2(10), T3(  7)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.97200, (double)bksge::smoothstep(T1(-10), T2(10), T3(  8)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.99275, (double)bksge::smoothstep(T1(-10), T2(10), T3(  9)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(1.00000, (double)bksge::smoothstep(T1(-10), T2(10), T3( 10)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(1.00000, (double)bksge::smoothstep(T1(-10), T2(10), T3( 11)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(1.00000, (double)bksge::smoothstep(T1(-10), T2(10), T3(100)), error);

	BKSGE_CONSTEXPR_EXPECT_NEAR(0.000000, (double)bksge::smoothstep(T1(50), T2(100), T3(-50)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.000000, (double)bksge::smoothstep(T1(50), T2(100), T3(  0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.000000, (double)bksge::smoothstep(T1(50), T2(100), T3( 49)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.000000, (double)bksge::smoothstep(T1(50), T2(100), T3( 50)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.001184, (double)bksge::smoothstep(T1(50), T2(100), T3( 51)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.004672, (double)bksge::smoothstep(T1(50), T2(100), T3( 52)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.470016, (double)bksge::smoothstep(T1(50), T2(100), T3( 74)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.500000, (double)bksge::smoothstep(T1(50), T2(100), T3( 75)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.529984, (double)bksge::smoothstep(T1(50), T2(100), T3( 76)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.995328, (double)bksge::smoothstep(T1(50), T2(100), T3( 98)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.998816, (double)bksge::smoothstep(T1(50), T2(100), T3( 99)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(1.000000, (double)bksge::smoothstep(T1(50), T2(100), T3(100)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(1.000000, (double)bksge::smoothstep(T1(50), T2(100), T3(101)), error);
}

GTEST_TEST(CMathTest, SmoothStepTest)
{
//	SmoothStepTestFloat<float, float,       float>      ();
	SmoothStepTestFloat<float, float,       double>     ();
//	SmoothStepTestFloat<float, float,       long double>();
	SmoothStepTestFloat<float, double,      float>      ();
//	SmoothStepTestFloat<float, double,      double>     ();
	SmoothStepTestFloat<float, double,      long double>();
//	SmoothStepTestFloat<float, long double, float>      ();
	SmoothStepTestFloat<float, long double, double>     ();
//	SmoothStepTestFloat<float, long double, long double>();

	SmoothStepTestFloat<double, float,       float>      ();
//	SmoothStepTestFloat<double, float,       double>     ();
	SmoothStepTestFloat<double, float,       long double>();
//	SmoothStepTestFloat<double, double,      float>      ();
	SmoothStepTestFloat<double, double,      double>     ();
//	SmoothStepTestFloat<double, double,      long double>();
	SmoothStepTestFloat<double, long double, float>      ();
//	SmoothStepTestFloat<double, long double, double>     ();
	SmoothStepTestFloat<double, long double, long double>();

//	SmoothStepTestFloat<long double, float,       float>      ();
	SmoothStepTestFloat<long double, float,       double>     ();
//	SmoothStepTestFloat<long double, float,       long double>();
	SmoothStepTestFloat<long double, double,      float>      ();
//	SmoothStepTestFloat<long double, double,      double>     ();
	SmoothStepTestFloat<long double, double,      long double>();
//	SmoothStepTestFloat<long double, long double, float>      ();
	SmoothStepTestFloat<long double, long double, double>     ();
//	SmoothStepTestFloat<long double, long double, long double>();

	SmoothStepTestInteger<int, int,         int>();
//	SmoothStepTestInteger<int, int,         float>();
	SmoothStepTestInteger<int, int,         double>();
//	SmoothStepTestInteger<int, int,         long double>();
	SmoothStepTestInteger<int, float,       int>();
//	SmoothStepTestInteger<int, double,      int>();
	SmoothStepTestInteger<int, long double, int>();

//	SmoothStepTestInteger<float, int,         int>();
	SmoothStepTestInteger<float, int,         float>();
//	SmoothStepTestInteger<float, int,         double>();
	SmoothStepTestInteger<float, int,         long double>();
//	SmoothStepTestInteger<float, float,       int>();
	SmoothStepTestInteger<float, double,      int>();
//	SmoothStepTestInteger<float, long double, int>();
}

}	// namespace smoothstep_test

}	// namespace bksge_cmath_test
