/**
 *	@file	unit_test_fnd_cmath_scalbln.cpp
 *
 *	@brief	scalbln のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/scalbln.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace scalbln_test
{

static_assert(bksge::is_same<float,       decltype(bksge::scalbln(0.0f, 0L))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::scalblnf(0.0f, 0L))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::scalbln(0.0, 0L))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::scalbln(0, 0L))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::scalbln(0.0l, 0L))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::scalblnl(0.0l, 0L))>::value, "");

template <typename T>
void ScalblnTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	EXPECT_EQ( 0.125, bksge::scalbln(T( 1.0), -3));
	EXPECT_EQ( 0.25,  bksge::scalbln(T( 1.0), -2));
	EXPECT_EQ( 0.5,   bksge::scalbln(T( 1.0), -1));
	EXPECT_EQ( 1.0,   bksge::scalbln(T( 1.0),  0));
	EXPECT_EQ( 2.0,   bksge::scalbln(T( 1.0),  1));
	EXPECT_EQ( 4.0,   bksge::scalbln(T( 1.0),  2));
	EXPECT_EQ( 8.0,   bksge::scalbln(T( 1.0),  3));

	EXPECT_EQ(-0.125, bksge::scalbln(T(-1.0), -3));
	EXPECT_EQ(-0.25,  bksge::scalbln(T(-1.0), -2));
	EXPECT_EQ(-0.5,   bksge::scalbln(T(-1.0), -1));
	EXPECT_EQ(-1.0,   bksge::scalbln(T(-1.0),  0));
	EXPECT_EQ(-2.0,   bksge::scalbln(T(-1.0),  1));
	EXPECT_EQ(-4.0,   bksge::scalbln(T(-1.0),  2));
	EXPECT_EQ(-8.0,   bksge::scalbln(T(-1.0),  3));

	EXPECT_EQ(  0.25, bksge::scalbln(T( 2.0), -3));
	EXPECT_EQ(  0.5,  bksge::scalbln(T( 2.0), -2));
	EXPECT_EQ(  1.0,  bksge::scalbln(T( 2.0), -1));
	EXPECT_EQ(  2.0,  bksge::scalbln(T( 2.0),  0));
	EXPECT_EQ(  4.0,  bksge::scalbln(T( 2.0),  1));
	EXPECT_EQ(  8.0,  bksge::scalbln(T( 2.0),  2));
	EXPECT_EQ( 16.0,  bksge::scalbln(T( 2.0),  3));

	EXPECT_EQ( -0.25, bksge::scalbln(T(-2.0), -3));
	EXPECT_EQ( -0.5,  bksge::scalbln(T(-2.0), -2));
	EXPECT_EQ( -1.0,  bksge::scalbln(T(-2.0), -1));
	EXPECT_EQ( -2.0,  bksge::scalbln(T(-2.0),  0));
	EXPECT_EQ( -4.0,  bksge::scalbln(T(-2.0),  1));
	EXPECT_EQ( -8.0,  bksge::scalbln(T(-2.0),  2));
	EXPECT_EQ(-16.0,  bksge::scalbln(T(-2.0),  3));

	EXPECT_EQ( 0.0625, bksge::scalbln(T( 0.5), -3));
	EXPECT_EQ( 0.125,  bksge::scalbln(T( 0.5), -2));
	EXPECT_EQ( 0.25,   bksge::scalbln(T( 0.5), -1));
	EXPECT_EQ( 0.5,    bksge::scalbln(T( 0.5),  0));
	EXPECT_EQ( 1.0,    bksge::scalbln(T( 0.5),  1));
	EXPECT_EQ( 2.0,    bksge::scalbln(T( 0.5),  2));
	EXPECT_EQ( 4.0,    bksge::scalbln(T( 0.5),  3));

	EXPECT_EQ(-0.0625, bksge::scalbln(T(-0.5), -3));
	EXPECT_EQ(-0.125,  bksge::scalbln(T(-0.5), -2));
	EXPECT_EQ(-0.25,   bksge::scalbln(T(-0.5), -1));
	EXPECT_EQ(-0.5,    bksge::scalbln(T(-0.5),  0));
	EXPECT_EQ(-1.0,    bksge::scalbln(T(-0.5),  1));
	EXPECT_EQ(-2.0,    bksge::scalbln(T(-0.5),  2));
	EXPECT_EQ(-4.0,    bksge::scalbln(T(-0.5),  3));

	BKSGE_CONSTEXPR_EXPECT_EQ(T(+0.0), bksge::scalbln(T(+0.0), 1));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-0.0), bksge::scalbln(T(-0.0), 1));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,    bksge::scalbln(+inf, 1));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf,    bksge::scalbln(-inf, 1));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(2.0),  bksge::scalbln(T(2.0), 0));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(3.0),  bksge::scalbln(T(3.0), 0));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::scalbln(+nan, 1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::scalbln(-nan, 1)));
}

template <typename T>
void ScalblnTestSignedInt(void)
{
	EXPECT_EQ( 0.0,   bksge::scalbln(T( 0), -3));
	EXPECT_EQ( 0.0,   bksge::scalbln(T( 0), -2));
	EXPECT_EQ( 0.0,   bksge::scalbln(T( 0), -1));
	EXPECT_EQ( 0.0,   bksge::scalbln(T( 0),  0));
	EXPECT_EQ( 0.0,   bksge::scalbln(T( 0),  1));
	EXPECT_EQ( 0.0,   bksge::scalbln(T( 0),  2));
	EXPECT_EQ( 0.0,   bksge::scalbln(T( 0),  3));

	EXPECT_EQ( 0.125, bksge::scalbln(T( 1), -3));
	EXPECT_EQ( 0.25,  bksge::scalbln(T( 1), -2));
	EXPECT_EQ( 0.5,   bksge::scalbln(T( 1), -1));
	EXPECT_EQ( 1.0,   bksge::scalbln(T( 1),  0));
	EXPECT_EQ( 2.0,   bksge::scalbln(T( 1),  1));
	EXPECT_EQ( 4.0,   bksge::scalbln(T( 1),  2));
	EXPECT_EQ( 8.0,   bksge::scalbln(T( 1),  3));

	EXPECT_EQ(-0.125, bksge::scalbln(T(-1), -3));
	EXPECT_EQ(-0.25,  bksge::scalbln(T(-1), -2));
	EXPECT_EQ(-0.5,   bksge::scalbln(T(-1), -1));
	EXPECT_EQ(-1.0,   bksge::scalbln(T(-1),  0));
	EXPECT_EQ(-2.0,   bksge::scalbln(T(-1),  1));
	EXPECT_EQ(-4.0,   bksge::scalbln(T(-1),  2));
	EXPECT_EQ(-8.0,   bksge::scalbln(T(-1),  3));

	EXPECT_EQ(  0.25, bksge::scalbln(T( 2), -3));
	EXPECT_EQ(  0.5,  bksge::scalbln(T( 2), -2));
	EXPECT_EQ(  1.0,  bksge::scalbln(T( 2), -1));
	EXPECT_EQ(  2.0,  bksge::scalbln(T( 2),  0));
	EXPECT_EQ(  4.0,  bksge::scalbln(T( 2),  1));
	EXPECT_EQ(  8.0,  bksge::scalbln(T( 2),  2));
	EXPECT_EQ( 16.0,  bksge::scalbln(T( 2),  3));

	EXPECT_EQ( -0.25, bksge::scalbln(T(-2), -3));
	EXPECT_EQ( -0.5,  bksge::scalbln(T(-2), -2));
	EXPECT_EQ( -1.0,  bksge::scalbln(T(-2), -1));
	EXPECT_EQ( -2.0,  bksge::scalbln(T(-2),  0));
	EXPECT_EQ( -4.0,  bksge::scalbln(T(-2),  1));
	EXPECT_EQ( -8.0,  bksge::scalbln(T(-2),  2));
	EXPECT_EQ(-16.0,  bksge::scalbln(T(-2),  3));
}

template <typename T>
void ScalblnTestUnsignedInt(void)
{
	EXPECT_EQ( 0.0,   bksge::scalbln(T( 0), -3));
	EXPECT_EQ( 0.0,   bksge::scalbln(T( 0), -2));
	EXPECT_EQ( 0.0,   bksge::scalbln(T( 0), -1));
	EXPECT_EQ( 0.0,   bksge::scalbln(T( 0),  0));
	EXPECT_EQ( 0.0,   bksge::scalbln(T( 0),  1));
	EXPECT_EQ( 0.0,   bksge::scalbln(T( 0),  2));
	EXPECT_EQ( 0.0,   bksge::scalbln(T( 0),  3));

	EXPECT_EQ( 0.125, bksge::scalbln(T( 1), -3));
	EXPECT_EQ( 0.25,  bksge::scalbln(T( 1), -2));
	EXPECT_EQ( 0.5,   bksge::scalbln(T( 1), -1));
	EXPECT_EQ( 1.0,   bksge::scalbln(T( 1),  0));
	EXPECT_EQ( 2.0,   bksge::scalbln(T( 1),  1));
	EXPECT_EQ( 4.0,   bksge::scalbln(T( 1),  2));
	EXPECT_EQ( 8.0,   bksge::scalbln(T( 1),  3));

	EXPECT_EQ(  0.25, bksge::scalbln(T( 2), -3));
	EXPECT_EQ(  0.5,  bksge::scalbln(T( 2), -2));
	EXPECT_EQ(  1.0,  bksge::scalbln(T( 2), -1));
	EXPECT_EQ(  2.0,  bksge::scalbln(T( 2),  0));
	EXPECT_EQ(  4.0,  bksge::scalbln(T( 2),  1));
	EXPECT_EQ(  8.0,  bksge::scalbln(T( 2),  2));
	EXPECT_EQ( 16.0,  bksge::scalbln(T( 2),  3));
}

GTEST_TEST(CMathTest, ScalblnTest)
{
	ScalblnTestFloat<float>();
	ScalblnTestFloat<double>();
	ScalblnTestFloat<long double>();

//	ScalblnTestSignedInt<int>();
	ScalblnTestSignedInt<signed char>();
//	ScalblnTestSignedInt<short>();
	ScalblnTestSignedInt<long>();
//	ScalblnTestSignedInt<long long>();

	ScalblnTestUnsignedInt<unsigned int>();
//	ScalblnTestUnsignedInt<unsigned char>();
	ScalblnTestUnsignedInt<unsigned short>();
//	ScalblnTestUnsignedInt<unsigned long>();
	ScalblnTestUnsignedInt<unsigned long long>();
}

}	// namespace scalbln_test

}	// namespace bksge_cmath_test
