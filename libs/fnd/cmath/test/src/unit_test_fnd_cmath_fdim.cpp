/**
 *	@file	unit_test_fnd_cmath_fdim.cpp
 *
 *	@brief	fdim のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/fdim.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace fdim_test
{

static_assert(bksge::is_same<float,       decltype(bksge::fdim(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::fdimf(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fdim(0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fdim(0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fdim(0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fdim(0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fdim(0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fdim(0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fdim(0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fdim(0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fdim(0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fdim(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fdiml(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fdim(0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fdim(0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fdim(0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fdim(0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fdim(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void FdimTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan1    = std::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2    = std::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf1    = std::numeric_limits<T1>::infinity();
	BKSGE_CONSTEXPR auto inf2    = std::numeric_limits<T2>::infinity();

	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1( 0.0), T2( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.5, bksge::fdim(T1( 0.5), T2( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-0.5), T2( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1.0, bksge::fdim(T1( 1.0), T2( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-1.0), T2( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(2.5, bksge::fdim(T1( 2.5), T2( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-2.5), T2( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(4.0, bksge::fdim(T1( 4.0), T2( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-4.0), T2( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1( 0.0), T2( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1( 0.5), T2( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-0.5), T2( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.5, bksge::fdim(T1( 1.0), T2( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-1.0), T2( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(2.0, bksge::fdim(T1( 2.5), T2( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-2.5), T2( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(3.5, bksge::fdim(T1( 4.0), T2( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-4.0), T2( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.5, bksge::fdim(T1( 0.0), T2(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1.0, bksge::fdim(T1( 0.5), T2(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-0.5), T2(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1.5, bksge::fdim(T1( 1.0), T2(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-1.0), T2(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(3.0, bksge::fdim(T1( 2.5), T2(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-2.5), T2(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(4.5, bksge::fdim(T1( 4.0), T2(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-4.0), T2(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1( 0.0), T2( 1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1( 0.5), T2( 1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-0.5), T2( 1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1( 1.0), T2( 1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-1.0), T2( 1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1.0, bksge::fdim(T1( 2.5), T2( 1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-2.5), T2( 1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(2.5, bksge::fdim(T1( 4.0), T2( 1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-4.0), T2( 1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1.5, bksge::fdim(T1( 0.0), T2(-1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(2.0, bksge::fdim(T1( 0.5), T2(-1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1.0, bksge::fdim(T1(-0.5), T2(-1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(2.5, bksge::fdim(T1( 1.0), T2(-1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.5, bksge::fdim(T1(-1.0), T2(-1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(4.0, bksge::fdim(T1( 2.5), T2(-1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-2.5), T2(-1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(5.5, bksge::fdim(T1( 4.0), T2(-1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-4.0), T2(-1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1( 0.0), T2( 3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1( 0.5), T2( 3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-0.5), T2( 3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1( 1.0), T2( 3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-1.0), T2( 3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1( 2.5), T2( 3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-2.5), T2( 3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.5, bksge::fdim(T1( 4.0), T2( 3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-4.0), T2( 3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(3.5, bksge::fdim(T1( 0.0), T2(-3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(4.0, bksge::fdim(T1( 0.5), T2(-3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(3.0, bksge::fdim(T1(-0.5), T2(-3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(4.5, bksge::fdim(T1( 1.0), T2(-3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(2.5, bksge::fdim(T1(-1.0), T2(-3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(6.0, bksge::fdim(T1( 2.5), T2(-3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1.0, bksge::fdim(T1(-2.5), T2(-3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(7.5, bksge::fdim(T1( 4.0), T2(-3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::fdim(T1(-4.0), T2(-3.5)));

	BKSGE_CONSTEXPR_EXPECT_EQ(inf1, bksge::fdim( inf1, T2(10.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0,  bksge::fdim(-inf1, T2(10.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0,  bksge::fdim(T1(20.0),  inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf2, bksge::fdim(T1(20.0), -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0,  bksge::fdim( inf1,  inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf1, bksge::fdim( inf1, -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0,  bksge::fdim(-inf1,  inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0,  bksge::fdim(-inf1, -inf2));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fdim( nan1,    T2(2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fdim(-nan1,    T2(3.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fdim( nan1,    inf2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fdim(-nan1,    inf2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fdim( nan1,   -inf2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fdim(-nan1,   -inf2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fdim(T1(4.0),  nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fdim(T1(5.0), -nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fdim( inf1,    nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fdim( inf1,   -nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fdim(-inf1,    nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fdim(-inf1,   -nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fdim( nan1,    nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fdim(-nan1,    nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fdim( nan1,   -nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fdim(-nan1,   -nan2)));
}

template <typename T1, typename T2>
void FdimTestInteger(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1(  0), T2(  0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::fdim(T1(  1), T2(  0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::fdim(T1(  2), T2(  0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::fdim(T1( 10), T2(  0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1( -1), T2(  0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1( -2), T2(  0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1(-10), T2(  0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1(  0), T2(  1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1(  1), T2(  1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::fdim(T1(  2), T2(  1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, bksge::fdim(T1( 10), T2(  1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1( -1), T2(  1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1( -2), T2(  1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1(-10), T2(  1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::fdim(T1(  0), T2( -1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::fdim(T1(  1), T2( -1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, bksge::fdim(T1(  2), T2( -1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::fdim(T1( 10), T2( -1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1( -1), T2( -1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1( -2), T2( -1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1(-10), T2( -1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1(  0), T2(  2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1(  1), T2(  2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1(  2), T2(  2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::fdim(T1( 10), T2(  2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1( -1), T2(  2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1( -2), T2(  2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1(-10), T2(  2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::fdim(T1(  0), T2( -2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, bksge::fdim(T1(  1), T2( -2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::fdim(T1(  2), T2( -2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(12, bksge::fdim(T1( 10), T2( -2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::fdim(T1( -1), T2( -2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1( -2), T2( -2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1(-10), T2( -2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1(  0), T2( 10)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1(  1), T2( 10)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1(  2), T2( 10)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1( 10), T2( 10)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1( -1), T2( 10)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1( -2), T2( 10)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1(-10), T2( 10)));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::fdim(T1(  0), T2(-10)));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::fdim(T1(  1), T2(-10)));
	BKSGE_CONSTEXPR_EXPECT_EQ(12, bksge::fdim(T1(  2), T2(-10)));
	BKSGE_CONSTEXPR_EXPECT_EQ(20, bksge::fdim(T1( 10), T2(-10)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, bksge::fdim(T1( -1), T2(-10)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::fdim(T1( -2), T2(-10)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fdim(T1(-10), T2(-10)));
}

GTEST_TEST(CMathTest, FdimTest)
{
	FdimTestFloat<float,       float>      ();
//	FdimTestFloat<float,       double>     ();
	FdimTestFloat<float,       long double>();
//	FdimTestFloat<double,      float>      ();
	FdimTestFloat<double,      double>     ();
//	FdimTestFloat<double,      long double>();
	FdimTestFloat<long double, float>      ();
//	FdimTestFloat<long double, double>     ();
	FdimTestFloat<long double, long double>();

	FdimTestInteger<int,         int>();
	FdimTestInteger<int,         float>();
//	FdimTestInteger<int,         double>();
	FdimTestInteger<int,         long double>();
//	FdimTestInteger<float,       int>();
	FdimTestInteger<double,      int>();
	FdimTestInteger<long double, int>();
}

}	// namespace fdim_test

}	// namespace bksge_cmath_test
