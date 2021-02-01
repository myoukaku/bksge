/**
 *	@file	unit_test_fnd_cmath_ldexp.cpp
 *
 *	@brief	ldexp のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/ldexp.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace ldexp_test
{

static_assert(bksge::is_same<float,       decltype(bksge::ldexp(0.0f, 0))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::ldexpf(0.0f, 0))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::ldexp(0.0 , 0))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::ldexp(0   , 0))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::ldexp(0.0l, 0))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::ldexpl(0.0l, 0))>::value, "");

template <typename T>
void LdexpTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	EXPECT_EQ( 0.125, bksge::ldexp(T( 1.0), -3));
	EXPECT_EQ( 0.25,  bksge::ldexp(T( 1.0), -2));
	EXPECT_EQ( 0.5,   bksge::ldexp(T( 1.0), -1));
	EXPECT_EQ( 1.0,   bksge::ldexp(T( 1.0),  0));
	EXPECT_EQ( 2.0,   bksge::ldexp(T( 1.0),  1));
	EXPECT_EQ( 4.0,   bksge::ldexp(T( 1.0),  2));
	EXPECT_EQ( 8.0,   bksge::ldexp(T( 1.0),  3));

	EXPECT_EQ(-0.125, bksge::ldexp(T(-1.0), -3));
	EXPECT_EQ(-0.25,  bksge::ldexp(T(-1.0), -2));
	EXPECT_EQ(-0.5,   bksge::ldexp(T(-1.0), -1));
	EXPECT_EQ(-1.0,   bksge::ldexp(T(-1.0),  0));
	EXPECT_EQ(-2.0,   bksge::ldexp(T(-1.0),  1));
	EXPECT_EQ(-4.0,   bksge::ldexp(T(-1.0),  2));
	EXPECT_EQ(-8.0,   bksge::ldexp(T(-1.0),  3));

	EXPECT_EQ(  0.25, bksge::ldexp(T( 2.0), -3));
	EXPECT_EQ(  0.5,  bksge::ldexp(T( 2.0), -2));
	EXPECT_EQ(  1.0,  bksge::ldexp(T( 2.0), -1));
	EXPECT_EQ(  2.0,  bksge::ldexp(T( 2.0),  0));
	EXPECT_EQ(  4.0,  bksge::ldexp(T( 2.0),  1));
	EXPECT_EQ(  8.0,  bksge::ldexp(T( 2.0),  2));
	EXPECT_EQ( 16.0,  bksge::ldexp(T( 2.0),  3));

	EXPECT_EQ( -0.25, bksge::ldexp(T(-2.0), -3));
	EXPECT_EQ( -0.5,  bksge::ldexp(T(-2.0), -2));
	EXPECT_EQ( -1.0,  bksge::ldexp(T(-2.0), -1));
	EXPECT_EQ( -2.0,  bksge::ldexp(T(-2.0),  0));
	EXPECT_EQ( -4.0,  bksge::ldexp(T(-2.0),  1));
	EXPECT_EQ( -8.0,  bksge::ldexp(T(-2.0),  2));
	EXPECT_EQ(-16.0,  bksge::ldexp(T(-2.0),  3));

	EXPECT_EQ( 0.0625, bksge::ldexp(T( 0.5), -3));
	EXPECT_EQ( 0.125,  bksge::ldexp(T( 0.5), -2));
	EXPECT_EQ( 0.25,   bksge::ldexp(T( 0.5), -1));
	EXPECT_EQ( 0.5,    bksge::ldexp(T( 0.5),  0));
	EXPECT_EQ( 1.0,    bksge::ldexp(T( 0.5),  1));
	EXPECT_EQ( 2.0,    bksge::ldexp(T( 0.5),  2));
	EXPECT_EQ( 4.0,    bksge::ldexp(T( 0.5),  3));

	EXPECT_EQ(-0.0625, bksge::ldexp(T(-0.5), -3));
	EXPECT_EQ(-0.125,  bksge::ldexp(T(-0.5), -2));
	EXPECT_EQ(-0.25,   bksge::ldexp(T(-0.5), -1));
	EXPECT_EQ(-0.5,    bksge::ldexp(T(-0.5),  0));
	EXPECT_EQ(-1.0,    bksge::ldexp(T(-0.5),  1));
	EXPECT_EQ(-2.0,    bksge::ldexp(T(-0.5),  2));
	EXPECT_EQ(-4.0,    bksge::ldexp(T(-0.5),  3));

	BKSGE_CONSTEXPR_EXPECT_EQ(T(+0.0), bksge::ldexp(T(+0.0), 1));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-0.0), bksge::ldexp(T(-0.0), 1));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,    bksge::ldexp(+inf, 1));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf,    bksge::ldexp(-inf, 1));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(2.0),  bksge::ldexp(T(2.0), 0));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(3.0),  bksge::ldexp(T(3.0), 0));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ldexp(+nan, 1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ldexp(-nan, 1)));
}

template <typename T>
void LdexpTestSignedInt(void)
{
	EXPECT_EQ( 0.0,   bksge::ldexp(T( 0), -3));
	EXPECT_EQ( 0.0,   bksge::ldexp(T( 0), -2));
	EXPECT_EQ( 0.0,   bksge::ldexp(T( 0), -1));
	EXPECT_EQ( 0.0,   bksge::ldexp(T( 0),  0));
	EXPECT_EQ( 0.0,   bksge::ldexp(T( 0),  1));
	EXPECT_EQ( 0.0,   bksge::ldexp(T( 0),  2));
	EXPECT_EQ( 0.0,   bksge::ldexp(T( 0),  3));

	EXPECT_EQ( 0.125, bksge::ldexp(T( 1), -3));
	EXPECT_EQ( 0.25,  bksge::ldexp(T( 1), -2));
	EXPECT_EQ( 0.5,   bksge::ldexp(T( 1), -1));
	EXPECT_EQ( 1.0,   bksge::ldexp(T( 1),  0));
	EXPECT_EQ( 2.0,   bksge::ldexp(T( 1),  1));
	EXPECT_EQ( 4.0,   bksge::ldexp(T( 1),  2));
	EXPECT_EQ( 8.0,   bksge::ldexp(T( 1),  3));

	EXPECT_EQ(-0.125, bksge::ldexp(T(-1), -3));
	EXPECT_EQ(-0.25,  bksge::ldexp(T(-1), -2));
	EXPECT_EQ(-0.5,   bksge::ldexp(T(-1), -1));
	EXPECT_EQ(-1.0,   bksge::ldexp(T(-1),  0));
	EXPECT_EQ(-2.0,   bksge::ldexp(T(-1),  1));
	EXPECT_EQ(-4.0,   bksge::ldexp(T(-1),  2));
	EXPECT_EQ(-8.0,   bksge::ldexp(T(-1),  3));

	EXPECT_EQ(  0.25, bksge::ldexp(T( 2), -3));
	EXPECT_EQ(  0.5,  bksge::ldexp(T( 2), -2));
	EXPECT_EQ(  1.0,  bksge::ldexp(T( 2), -1));
	EXPECT_EQ(  2.0,  bksge::ldexp(T( 2),  0));
	EXPECT_EQ(  4.0,  bksge::ldexp(T( 2),  1));
	EXPECT_EQ(  8.0,  bksge::ldexp(T( 2),  2));
	EXPECT_EQ( 16.0,  bksge::ldexp(T( 2),  3));

	EXPECT_EQ( -0.25, bksge::ldexp(T(-2), -3));
	EXPECT_EQ( -0.5,  bksge::ldexp(T(-2), -2));
	EXPECT_EQ( -1.0,  bksge::ldexp(T(-2), -1));
	EXPECT_EQ( -2.0,  bksge::ldexp(T(-2),  0));
	EXPECT_EQ( -4.0,  bksge::ldexp(T(-2),  1));
	EXPECT_EQ( -8.0,  bksge::ldexp(T(-2),  2));
	EXPECT_EQ(-16.0,  bksge::ldexp(T(-2),  3));
}

template <typename T>
void LdexpTestUnsignedInt(void)
{
	EXPECT_EQ( 0.0,   bksge::ldexp(T( 0), -3));
	EXPECT_EQ( 0.0,   bksge::ldexp(T( 0), -2));
	EXPECT_EQ( 0.0,   bksge::ldexp(T( 0), -1));
	EXPECT_EQ( 0.0,   bksge::ldexp(T( 0),  0));
	EXPECT_EQ( 0.0,   bksge::ldexp(T( 0),  1));
	EXPECT_EQ( 0.0,   bksge::ldexp(T( 0),  2));
	EXPECT_EQ( 0.0,   bksge::ldexp(T( 0),  3));

	EXPECT_EQ( 0.125, bksge::ldexp(T( 1), -3));
	EXPECT_EQ( 0.25,  bksge::ldexp(T( 1), -2));
	EXPECT_EQ( 0.5,   bksge::ldexp(T( 1), -1));
	EXPECT_EQ( 1.0,   bksge::ldexp(T( 1),  0));
	EXPECT_EQ( 2.0,   bksge::ldexp(T( 1),  1));
	EXPECT_EQ( 4.0,   bksge::ldexp(T( 1),  2));
	EXPECT_EQ( 8.0,   bksge::ldexp(T( 1),  3));

	EXPECT_EQ(  0.25, bksge::ldexp(T( 2), -3));
	EXPECT_EQ(  0.5,  bksge::ldexp(T( 2), -2));
	EXPECT_EQ(  1.0,  bksge::ldexp(T( 2), -1));
	EXPECT_EQ(  2.0,  bksge::ldexp(T( 2),  0));
	EXPECT_EQ(  4.0,  bksge::ldexp(T( 2),  1));
	EXPECT_EQ(  8.0,  bksge::ldexp(T( 2),  2));
	EXPECT_EQ( 16.0,  bksge::ldexp(T( 2),  3));
}

GTEST_TEST(CMathTest, LdexpTest)
{
	LdexpTestFloat<float>();
	LdexpTestFloat<double>();
	LdexpTestFloat<long double>();

	LdexpTestSignedInt<int>();
//	LdexpTestSignedInt<signed char>();
	LdexpTestSignedInt<short>();
//	LdexpTestSignedInt<long>();
	LdexpTestSignedInt<long long>();

//	LdexpTestUnsignedInt<unsigned int>();
	LdexpTestUnsignedInt<unsigned char>();
//	LdexpTestUnsignedInt<unsigned short>();
	LdexpTestUnsignedInt<unsigned long>();
//	LdexpTestUnsignedInt<unsigned long long>();
}

}	// namespace ldexp_test

}	// namespace bksge_cmath_test
