/**
 *	@file	unit_test_fnd_cmath_cbrt.cpp
 *
 *	@brief	cbrt のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/cbrt.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace cbrt_test
{

static_assert(bksge::is_same<float,       decltype(bksge::cbrt(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::cbrtf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cbrt(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cbrt(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cbrt(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cbrtl(0.0l))>::value, "");

template <typename T>
void CbrtTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	EXPECT_EQ( 0.0, bksge::cbrt(T(   0.0)));
	EXPECT_EQ( 0.5, bksge::cbrt(T(   0.125)));
	EXPECT_EQ( 1.0, bksge::cbrt(T(   1.0)));
	EXPECT_EQ( 1.5, bksge::cbrt(T(   3.375)));
	EXPECT_EQ( 2.0, bksge::cbrt(T(   8.0)));
	EXPECT_EQ( 3.0, bksge::cbrt(T(  27.0)));
	EXPECT_EQ( 4.0, bksge::cbrt(T(  64.0)));
	EXPECT_EQ( 5.0, bksge::cbrt(T( 125.0)));
	EXPECT_EQ( 6.0, bksge::cbrt(T( 216.0)));
	EXPECT_EQ( 7.0, bksge::cbrt(T( 343.0)));
	EXPECT_EQ( 8.0, bksge::cbrt(T( 512.0)));
	EXPECT_EQ( 9.0, bksge::cbrt(T( 729.0)));
	EXPECT_EQ(-0.5, bksge::cbrt(T(  -0.125)));
	EXPECT_EQ(-1.0, bksge::cbrt(T(  -1.0)));
	EXPECT_EQ(-1.5, bksge::cbrt(T(  -3.375)));
	EXPECT_EQ(-2.0, bksge::cbrt(T(  -8.0)));
	EXPECT_EQ(-3.0, bksge::cbrt(T( -27.0)));
	EXPECT_EQ(-4.0, bksge::cbrt(T( -64.0)));
	EXPECT_EQ(-5.0, bksge::cbrt(T(-125.0)));
	EXPECT_EQ(-6.0, bksge::cbrt(T(-216.0)));
	EXPECT_EQ(-7.0, bksge::cbrt(T(-343.0)));
	EXPECT_EQ(-8.0, bksge::cbrt(T(-512.0)));
	EXPECT_EQ(-9.0, bksge::cbrt(T(-729.0)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T(+0.0), bksge::cbrt(T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-0.0), bksge::cbrt(T(-0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,    bksge::cbrt(+inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf,    bksge::cbrt(-inf));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cbrt(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cbrt(-nan)));
}

template <typename T>
void CbrtTestSignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.000000000000001;

	EXPECT_NEAR( 0.0000000000000000000000000000000, bksge::cbrt(T( 0)), error);
	EXPECT_NEAR( 1.0000000000000000000000000000000, bksge::cbrt(T( 1)), error);
	EXPECT_NEAR( 1.2599210498948731647672106072782, bksge::cbrt(T( 2)), error);
	EXPECT_NEAR( 1.4422495703074083823216383107801, bksge::cbrt(T( 3)), error);
	EXPECT_NEAR( 1.5874010519681994747517056392723, bksge::cbrt(T( 4)), error);
	EXPECT_NEAR( 1.7099759466766969893531088725439, bksge::cbrt(T( 5)), error);
	EXPECT_NEAR( 1.8171205928321396588912117563273, bksge::cbrt(T( 6)), error);
	EXPECT_NEAR( 1.9129311827723891011991168395488, bksge::cbrt(T( 7)), error);
	EXPECT_NEAR( 2.0000000000000000000000000000000, bksge::cbrt(T( 8)), error);

	EXPECT_NEAR(-1.0000000000000000000000000000000, bksge::cbrt(T(-1)), error);
	EXPECT_NEAR(-1.2599210498948731647672106072782, bksge::cbrt(T(-2)), error);
	EXPECT_NEAR(-1.4422495703074083823216383107801, bksge::cbrt(T(-3)), error);
	EXPECT_NEAR(-1.5874010519681994747517056392723, bksge::cbrt(T(-4)), error);
	EXPECT_NEAR(-1.7099759466766969893531088725439, bksge::cbrt(T(-5)), error);
	EXPECT_NEAR(-1.8171205928321396588912117563273, bksge::cbrt(T(-6)), error);
	EXPECT_NEAR(-1.9129311827723891011991168395488, bksge::cbrt(T(-7)), error);
	EXPECT_NEAR(-2.0000000000000000000000000000000, bksge::cbrt(T(-8)), error);

	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::cbrt(T(0)));
}

template <typename T>
void CbrtTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.000000000000001;

	EXPECT_NEAR( 0.0000000000000000000000000000000, bksge::cbrt(T( 0)), error);
	EXPECT_NEAR( 1.0000000000000000000000000000000, bksge::cbrt(T( 1)), error);
	EXPECT_NEAR( 1.2599210498948731647672106072782, bksge::cbrt(T( 2)), error);
	EXPECT_NEAR( 1.4422495703074083823216383107801, bksge::cbrt(T( 3)), error);
	EXPECT_NEAR( 1.5874010519681994747517056392723, bksge::cbrt(T( 4)), error);
	EXPECT_NEAR( 1.7099759466766969893531088725439, bksge::cbrt(T( 5)), error);
	EXPECT_NEAR( 1.8171205928321396588912117563273, bksge::cbrt(T( 6)), error);
	EXPECT_NEAR( 1.9129311827723891011991168395488, bksge::cbrt(T( 7)), error);
	EXPECT_NEAR( 2.0000000000000000000000000000000, bksge::cbrt(T( 8)), error);

	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::cbrt(T(0)));
}

GTEST_TEST(CMathTest, CbrtTest)
{
	CbrtTestFloat<float>();
	CbrtTestFloat<double>();
	CbrtTestFloat<long double>();

	CbrtTestSignedInt<int>();
	CbrtTestSignedInt<signed char>();
//	CbrtTestSignedInt<short>();
	CbrtTestSignedInt<long>();
//	CbrtTestSignedInt<long long>();

	CbrtTestUnsignedInt<unsigned int>();
//	CbrtTestUnsignedInt<unsigned char>();
	CbrtTestUnsignedInt<unsigned short>();
//	CbrtTestUnsignedInt<unsigned long>();
	CbrtTestUnsignedInt<unsigned long long>();
}

}	// namespace cbrt_test

}	// namespace bksge_cmath_test
