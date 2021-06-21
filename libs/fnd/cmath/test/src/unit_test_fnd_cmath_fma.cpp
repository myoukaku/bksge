/**
 *	@file	unit_test_fnd_cmath_fma.cpp
 *
 *	@brief	fma のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/fma.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace fma_test
{

static_assert(bksge::is_same<float,       decltype(bksge::fma(0.0f, 0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0.0f, 0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0f, 0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0.0f, 0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0.0f, 0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0.0f, 0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0f, 0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0.0f, 0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0f, 0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0f, 0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0f, 0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0f, 0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0.0f, 0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0.0f, 0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0f, 0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0.0f, 0   , 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0.0 , 0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0.0 , 0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0 , 0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0.0 , 0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0.0 , 0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0.0 , 0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0 , 0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0.0 , 0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0 , 0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0 , 0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0 , 0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0 , 0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0.0 , 0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0.0 , 0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0 , 0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0.0 , 0   , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0l, 0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0l, 0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0l, 0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0l, 0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0l, 0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0l, 0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0l, 0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0l, 0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0l, 0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0l, 0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0l, 0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0l, 0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0l, 0   , 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0l, 0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0l, 0   , 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0.0l, 0   , 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0   , 0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0   , 0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0   , 0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0   , 0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0   , 0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0   , 0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0   , 0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0   , 0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0   , 0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0   , 0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0   , 0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0   , 0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0   , 0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0   , 0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fma(0   , 0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fma(0   , 0   , 0   ))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::fmaf(0.0f, 0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmal(0.0l, 0.0l, 0.0l))>::value, "");

template <typename T1, typename T2, typename T3>
void FmaTestFloat(void)
{
	using R = bksge::float_promote_t<T1, T2, T3>;

	BKSGE_CONSTEXPR auto inf1 = std::numeric_limits<T1>::infinity();
	BKSGE_CONSTEXPR auto inf2 = std::numeric_limits<T2>::infinity();
	BKSGE_CONSTEXPR auto inf3 = std::numeric_limits<T3>::infinity();
	BKSGE_CONSTEXPR auto inf4 = std::numeric_limits<R>::infinity();
	BKSGE_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan3 = std::numeric_limits<T3>::quiet_NaN();

	BKSGE_CONSTEXPR_EXPECT_EQ( 0.0, bksge::fma(T1( 0.0), T2( 0.0), T3( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0.5, bksge::fma(T1( 0.0), T2( 0.0), T3( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-0.5, bksge::fma(T1( 0.0), T2( 0.0), T3(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0.5, bksge::fma(T1( 0.0), T2( 2.5), T3( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-0.5, bksge::fma(T1( 0.0), T2( 2.5), T3(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0.5, bksge::fma(T1( 0.0), T2(-2.5), T3( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-0.5, bksge::fma(T1( 0.0), T2(-2.5), T3(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3.0, bksge::fma(T1( 1.0), T2( 2.5), T3( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2.0, bksge::fma(T1( 1.0), T2( 2.5), T3(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-2.0, bksge::fma(T1( 1.0), T2(-2.5), T3( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-3.0, bksge::fma(T1( 1.0), T2(-2.5), T3(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-6.0, bksge::fma(T1(-3.0), T2( 2.5), T3( 1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-9.0, bksge::fma(T1(-3.0), T2( 2.5), T3(-1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9.0, bksge::fma(T1(-3.0), T2(-2.5), T3( 1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6.0, bksge::fma(T1(-3.0), T2(-2.5), T3(-1.5)));

	//If x is zero and y is infinite or if x is infinite and y is zero, and z is not a NaN, then NaN is returned and FE_INVALID is raised
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(T1(+0.0), +inf2, T3( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(T1(-0.0), +inf2, T3( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(T1(+0.0), -inf2, T3( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(T1(-0.0), -inf2, T3( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(+inf1, T2(+0.0), T3( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(+inf1, T2(-0.0), T3( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(-inf1, T2(+0.0), T3( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(-inf1, T2(-0.0), T3( 1.0))));

	//If x is zero and y is infinite or if x is infinite and y is zero, and z is a NaN, then NaN is returned and FE_INVALID may be raised
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(T1(+0.0), +inf2, nan3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(T1(-0.0), +inf2, nan3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(T1(+0.0), -inf2, nan3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(T1(-0.0), -inf2, nan3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(+inf1, T2(+0.0), nan3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(+inf1, T2(-0.0), nan3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(-inf1, T2(+0.0), nan3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(-inf1, T2(-0.0), nan3)));

	//If x*y is an exact infinity and z is an infinity with the opposite sign, NaN is returned and FE_INVALID is raised
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(T1(+1.0), +inf2, -inf3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(T1(-1.0), +inf2, +inf3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(T1(+1.0), -inf2, +inf3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(T1(-1.0), -inf2, -inf3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(+inf1, T2(+1.0), -inf3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(+inf1, T2(-1.0), +inf3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(-inf1, T2(+1.0), +inf3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(-inf1, T2(-1.0), -inf3)));

	// x*yがinfかつzがinfでも符号が同じならNaNにならない
	// (計算途中でinfが発生するのでconstexprにはできない)
	EXPECT_FALSE(bksge::isnan(bksge::fma(T1(+1.0), +inf2, +inf3)));
	EXPECT_FALSE(bksge::isnan(bksge::fma(T1(-1.0), +inf2, -inf3)));
	EXPECT_FALSE(bksge::isnan(bksge::fma(T1(+1.0), -inf2, -inf3)));
	EXPECT_FALSE(bksge::isnan(bksge::fma(T1(-1.0), -inf2, +inf3)));
	EXPECT_FALSE(bksge::isnan(bksge::fma(+inf1, T2(+1.0), +inf3)));
	EXPECT_FALSE(bksge::isnan(bksge::fma(+inf1, T2(-1.0), -inf3)));
	EXPECT_FALSE(bksge::isnan(bksge::fma(-inf1, T2(+1.0), -inf3)));
	EXPECT_FALSE(bksge::isnan(bksge::fma(-inf1, T2(-1.0), +inf3)));
	EXPECT_EQ(+inf4, bksge::fma(T1(+1.0), +inf2, +inf3));
	EXPECT_EQ(-inf4, bksge::fma(T1(-1.0), +inf2, -inf3));
	EXPECT_EQ(-inf4, bksge::fma(T1(+1.0), -inf2, -inf3));
	EXPECT_EQ(+inf4, bksge::fma(T1(-1.0), -inf2, +inf3));
	EXPECT_EQ(+inf4, bksge::fma(+inf1, T2(+1.0), +inf3));
	EXPECT_EQ(-inf4, bksge::fma(+inf1, T2(-1.0), -inf3));
	EXPECT_EQ(-inf4, bksge::fma(-inf1, T2(+1.0), -inf3));
	EXPECT_EQ(+inf4, bksge::fma(-inf1, T2(-1.0), +inf3));

	//If x or y are NaN, NaN is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(nan1,    T2(1.0), T3(1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(T1(1.0), nan2,    T3(1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(nan1,    nan2,    T3(1.0))));

	//If z is NaN, and x*y aren't 0*Inf or Inf*0, then NaN is returned (without FE_INVALID)
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fma(T1(1.0), T2(1.0), nan3)));
}

template <typename T1, typename T2, typename T3>
void FmaTestInteger(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(  0.0, bksge::fma(T1( 0), T2( 0), T3(  0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  1.0, bksge::fma(T1( 0), T2( 0), T3(  1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -2.0, bksge::fma(T1( 0), T2( 0), T3( -2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  3.0, bksge::fma(T1( 0), T2( 3), T3(  3)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -4.0, bksge::fma(T1( 0), T2( 3), T3( -4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  5.0, bksge::fma(T1( 0), T2(-3), T3(  5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -6.0, bksge::fma(T1( 0), T2(-3), T3( -6)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 10.0, bksge::fma(T1( 1), T2( 3), T3(  7)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -5.0, bksge::fma(T1( 1), T2( 3), T3( -8)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  6.0, bksge::fma(T1( 1), T2(-3), T3(  9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-13.0, bksge::fma(T1( 1), T2(-3), T3(-10)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -1.0, bksge::fma(T1(-4), T2( 3), T3( 11)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-24.0, bksge::fma(T1(-4), T2( 3), T3(-12)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 25.0, bksge::fma(T1(-4), T2(-3), T3( 13)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -2.0, bksge::fma(T1(-4), T2(-3), T3(-14)));
}

GTEST_TEST(CMathTest, FmaTest)
{
	FmaTestFloat<float,       float,       float>      ();
//	FmaTestFloat<float,       float,       double>     ();
	FmaTestFloat<float,       float,       long double>();
//	FmaTestFloat<float,       double,      float>      ();
	FmaTestFloat<float,       double,      double>     ();
//	FmaTestFloat<float,       double,      long double>();
	FmaTestFloat<float,       long double, float>      ();
//	FmaTestFloat<float,       long double, double>     ();
	FmaTestFloat<float,       long double, long double>();
//	FmaTestFloat<double,      float,       float>      ();
	FmaTestFloat<double,      float,       double>     ();
//	FmaTestFloat<double,      float,       long double>();
	FmaTestFloat<double,      double,      float>      ();
//	FmaTestFloat<double,      double,      double>     ();
	FmaTestFloat<double,      double,      long double>();
//	FmaTestFloat<double,      long double, float>      ();
	FmaTestFloat<double,      long double, double>     ();
//	FmaTestFloat<double,      long double, long double>();
	FmaTestFloat<long double, float,       float>      ();
//	FmaTestFloat<long double, float,       double>     ();
	FmaTestFloat<long double, float,       long double>();
//	FmaTestFloat<long double, double,      float>      ();
	FmaTestFloat<long double, double,      double>     ();
//	FmaTestFloat<long double, double,      long double>();
	FmaTestFloat<long double, long double, float>      ();
//	FmaTestFloat<long double, long double, double>     ();
	FmaTestFloat<long double, long double, long double>();

	FmaTestInteger<int,         int,         int>();
//	FmaTestInteger<int,         int,         float>();
	FmaTestInteger<int,         int,         double>();
//	FmaTestInteger<int,         int,         long double>();
	FmaTestInteger<int,         float,       int>();
//	FmaTestInteger<int,         float,       float>();
	FmaTestInteger<int,         float,       double>();
//	FmaTestInteger<int,         float,       long double>();
	FmaTestInteger<int,         double,      int>();
//	FmaTestInteger<int,         double,      float>();
	FmaTestInteger<int,         double,      double>();
//	FmaTestInteger<int,         double,      long double>();
	FmaTestInteger<int,         long double, int>();
//	FmaTestInteger<int,         long double, float>();
	FmaTestInteger<int,         long double, double>();
//	FmaTestInteger<int,         long double, long double>();
	FmaTestInteger<float,       int,         int>();
//	FmaTestInteger<float,       int,         float>();
	FmaTestInteger<float,       int,         double>();
//	FmaTestInteger<float,       int,         long double>();
	FmaTestInteger<float,       float,       int>();
//	FmaTestInteger<float,       double,      int>();
	FmaTestInteger<float,       long double, int>();
//	FmaTestInteger<double,      int,         int>();
	FmaTestInteger<double,      int,         float>();
//	FmaTestInteger<double,      int,         double>();
	FmaTestInteger<double,      int,         long double>();
//	FmaTestInteger<double,      float,       int>();
	FmaTestInteger<double,      double,      int>();
//	FmaTestInteger<double,      long double, int>();
	FmaTestInteger<long double, int,         int>();
//	FmaTestInteger<long double, int,         float>();
	FmaTestInteger<long double, int,         double>();
//	FmaTestInteger<long double, int,         long double>();
	FmaTestInteger<long double, float,       int>();
//	FmaTestInteger<long double, double,      int>();
	FmaTestInteger<long double, long double, int>();
}

}	// namespace fma_test

}	// namespace bksge_cmath_test
