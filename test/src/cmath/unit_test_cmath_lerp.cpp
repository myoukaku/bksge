/**
 *	@file	unit_test_cmath_lerp.cpp
 *
 *	@brief	lerp のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/cmath/lerp.hpp>
#include <bksge/cmath/isnan.hpp>
#include <bksge/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace lerp_test
{

template <typename T1, typename T2, typename T3>
void LerpTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan3 = std::numeric_limits<T3>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf1 = std::numeric_limits<T1>::infinity();
	BKSGE_CONSTEXPR auto inf2 = std::numeric_limits<T2>::infinity();
	BKSGE_CONSTEXPR auto inf3 = std::numeric_limits<T3>::infinity();

	BKSGE_CONSTEXPR_EXPECT_EQ( 0.0,   bksge::lerp(T1(0.0), T2(0.5), T3( 0.00)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0.125, bksge::lerp(T1(0.0), T2(0.5), T3( 0.25)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0.25,  bksge::lerp(T1(0.0), T2(0.5), T3( 0.50)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0.375, bksge::lerp(T1(0.0), T2(0.5), T3( 0.75)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0.5,   bksge::lerp(T1(0.0), T2(0.5), T3( 1.00)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1.0,   bksge::lerp(T1(0.0), T2(0.5), T3( 2.00)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1.5,   bksge::lerp(T1(0.0), T2(0.5), T3( 3.00)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-0.5,   bksge::lerp(T1(0.0), T2(0.5), T3(-1.00)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1.0,   bksge::lerp(T1(0.0), T2(0.5), T3(-2.00)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1.5,   bksge::lerp(T1(0.0), T2(0.5), T3(-3.00)));
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3,  bksge::lerp(T1(0.0), T2(0.5),  inf3));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3,  bksge::lerp(T1(0.0), T2(0.5), -inf3));

	BKSGE_CONSTEXPR_EXPECT_EQ(10.0,   bksge::lerp(T1(10.0), T2(5.0), T3( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8.75,  bksge::lerp(T1(10.0), T2(5.0), T3( 0.25)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 7.5,   bksge::lerp(T1(10.0), T2(5.0), T3( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6.25,  bksge::lerp(T1(10.0), T2(5.0), T3( 0.75)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5.0,   bksge::lerp(T1(10.0), T2(5.0), T3( 1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0.0,   bksge::lerp(T1(10.0), T2(5.0), T3( 2.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(15.0,   bksge::lerp(T1(10.0), T2(5.0), T3(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(20.0,   bksge::lerp(T1(10.0), T2(5.0), T3(-2.0)));

	// from, to, t のうちどれか1つでもNaNの場合、NaNを返す。
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::lerp( nan1,     T2(2.0),  T3(0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::lerp(-nan1,     T2(2.0),  T3(0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::lerp( T1(1.0),  nan2,     T3(0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::lerp( T1(1.0), -nan2,     T3(0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::lerp( T1(1.0),  T2(2.0),  nan3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::lerp( T1(1.0),  T2(2.0), -nan3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::lerp( nan1,     nan2,     nan3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::lerp(-nan1,    -nan2,    -nan3)));

	// from か to が ±∞ の場合、NaNを返す。
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::lerp( inf1,     T2(2.0),  T3(0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::lerp(-inf1,     T2(2.0),  T3(0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::lerp( T1(1.0),  inf2,     T3(0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::lerp( T1(1.0), -inf2,     T3(0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::lerp( inf1,     inf2,     T3(0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::lerp( inf1,     inf2,     inf3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::lerp(-inf1,    -inf2,     T3(0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::lerp(-inf1,    -inf2,    -inf3)));

	// t が ±∞ の場合、±∞を返す。
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3,         bksge::lerp( T1(1.0),  T2(2.0),  inf3));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3,         bksge::lerp( T1(1.0),  T2(2.0), -inf3));

	// from == to の場合、fromを返す。
	BKSGE_CONSTEXPR_EXPECT_EQ( 2.0,          bksge::lerp(T1(2.0), T2(2.0), T3(0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2.0,          bksge::lerp(T1(2.0), T2(2.0), T3(1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3,         bksge::lerp(T1(2.0), T2(2.0),  inf3));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3,         bksge::lerp(T1(2.0), T2(2.0), -inf3));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::lerp(T1(2.0), T2(2.0),  nan3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::lerp(T1(2.0), T2(2.0), -nan3)));
}
  
template <typename T1, typename T2>
void LerpTestInteger(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(  0.0f, bksge::lerp(T1( 0), T1(10), T2( 0.00)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  2.5f, bksge::lerp(T1( 0), T1(10), T2( 0.25)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  5.0f, bksge::lerp(T1( 0), T1(10), T2( 0.50)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  7.5f, bksge::lerp(T1( 0), T1(10), T2( 0.75)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 10.0f, bksge::lerp(T1( 0), T1(10), T2( 1.00)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 20.0f, bksge::lerp(T1( 0), T1(10), T2( 2.00)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -5.0f, bksge::lerp(T1( 0), T1(10), T2(-0.50)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-10.0f, bksge::lerp(T1( 0), T1(10), T2(-1.00)));

	BKSGE_CONSTEXPR_EXPECT_EQ( 20.0f, bksge::lerp(T1(20), T1(-10), T2( 0.00)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 12.5f, bksge::lerp(T1(20), T1(-10), T2( 0.25)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  5.0f, bksge::lerp(T1(20), T1(-10), T2( 0.50)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -2.5f, bksge::lerp(T1(20), T1(-10), T2( 0.75)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-10.0f, bksge::lerp(T1(20), T1(-10), T2( 1.00)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-40.0f, bksge::lerp(T1(20), T1(-10), T2( 2.00)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 50.0f, bksge::lerp(T1(20), T1(-10), T2(-1.00)));
}

GTEST_TEST(CMathTest, LerpTest)
{
//	LerpTestFloat<float, float,       float>();
	LerpTestFloat<float, float,       double>();
//	LerpTestFloat<float, float,       long double>();
	LerpTestFloat<float, double,      float>();
//	LerpTestFloat<float, double,      double>();
	LerpTestFloat<float, double,      long double>();
//	LerpTestFloat<float, long double, float>();
	LerpTestFloat<float, long double, double>();
//	LerpTestFloat<float, long double, long double>();
	LerpTestFloat<double, float,       float>();
//	LerpTestFloat<double, float,       double>();
	LerpTestFloat<double, float,       long double>();
//	LerpTestFloat<double, double,      float>();
	LerpTestFloat<double, double,      double>();
//	LerpTestFloat<double, double,      long double>();
	LerpTestFloat<double, long double, float>();
//	LerpTestFloat<double, long double, double>();
	LerpTestFloat<double, long double, long double>();
//	LerpTestFloat<long double, float,       float>();
	LerpTestFloat<long double, float,       double>();
//	LerpTestFloat<long double, float,       long double>();
	LerpTestFloat<long double, double,      float>();
//	LerpTestFloat<long double, double,      double>();
	LerpTestFloat<long double, double,      long double>();
//	LerpTestFloat<long double, long double, float>();
	LerpTestFloat<long double, long double, double>();
//	LerpTestFloat<long double, long double, long double>();

	LerpTestInteger<int,   float>();
//	LerpTestInteger<int,   double>();
	LerpTestInteger<int,   long double>();
//	LerpTestInteger<short, float>();
	LerpTestInteger<short, double>();
//	LerpTestInteger<short, long double>();
	LerpTestInteger<long,  float>();
//	LerpTestInteger<long,  double>();
	LerpTestInteger<long,  long double>();
}

}	// namespace lerp_test

}	// namespace bksge_cmath_test
