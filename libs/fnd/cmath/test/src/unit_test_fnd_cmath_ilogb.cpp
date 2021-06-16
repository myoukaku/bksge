/**
 *	@file	unit_test_fnd_cmath_ilogb.cpp
 *
 *	@brief	ilogb のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/ilogb.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace ilogb_test
{

static_assert(bksge::is_same<int, decltype(bksge::ilogb(0.0f))>::value, "");
static_assert(bksge::is_same<int, decltype(bksge::ilogbf(0.0f))>::value, "");
static_assert(bksge::is_same<int, decltype(bksge::ilogb(0.0 ))>::value, "");
static_assert(bksge::is_same<int, decltype(bksge::ilogb(0   ))>::value, "");
static_assert(bksge::is_same<int, decltype(bksge::ilogb(0.0l))>::value, "");
static_assert(bksge::is_same<int, decltype(bksge::ilogbl(0.0l))>::value, "");

template <typename T>
void ILogbTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	EXPECT_EQ( 4, bksge::ilogb(T(-17.0)));
	EXPECT_EQ( 4, bksge::ilogb(T(-16.0)));
	EXPECT_EQ( 3, bksge::ilogb(T(-15.0)));
	EXPECT_EQ( 3, bksge::ilogb(T( -9.0)));
	EXPECT_EQ( 3, bksge::ilogb(T( -8.0)));
	EXPECT_EQ( 2, bksge::ilogb(T( -7.0)));
	EXPECT_EQ( 2, bksge::ilogb(T( -5.0)));
	EXPECT_EQ( 2, bksge::ilogb(T( -4.0)));
	EXPECT_EQ( 1, bksge::ilogb(T( -3.0)));
	EXPECT_EQ( 1, bksge::ilogb(T( -2.0)));
	EXPECT_EQ( 0, bksge::ilogb(T( -1.0)));
	EXPECT_EQ(-1, bksge::ilogb(T( -0.5)));
	EXPECT_EQ(-2, bksge::ilogb(T( -0.25)));
	EXPECT_EQ(-3, bksge::ilogb(T( -0.125)));
	EXPECT_EQ(-3, bksge::ilogb(T(  0.125)));
	EXPECT_EQ(-2, bksge::ilogb(T(  0.25)));
	EXPECT_EQ(-1, bksge::ilogb(T(  0.5)));
	EXPECT_EQ( 0, bksge::ilogb(T(  1.0)));
	EXPECT_EQ( 0, bksge::ilogb(T(  1.5)));
	EXPECT_EQ( 1, bksge::ilogb(T(  2.0)));
	EXPECT_EQ( 1, bksge::ilogb(T(  2.5)));
	EXPECT_EQ( 1, bksge::ilogb(T(  3.0)));
	EXPECT_EQ( 1, bksge::ilogb(T(  3.5)));
	EXPECT_EQ( 2, bksge::ilogb(T(  4.0)));
	EXPECT_EQ( 2, bksge::ilogb(T(  4.5)));
	EXPECT_EQ( 2, bksge::ilogb(T(  5.0)));
	EXPECT_EQ( 2, bksge::ilogb(T(  7.0)));
	EXPECT_EQ( 3, bksge::ilogb(T(  8.0)));
	EXPECT_EQ( 3, bksge::ilogb(T(  9.0)));
	EXPECT_EQ( 3, bksge::ilogb(T( 15.0)));
	EXPECT_EQ( 4, bksge::ilogb(T( 16.0)));
	EXPECT_EQ( 4, bksge::ilogb(T( 17.0)));

	BKSGE_CONSTEXPR_EXPECT_EQ(FP_ILOGB0,   bksge::ilogb(T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(FP_ILOGB0,   bksge::ilogb(T(-0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(INT_MAX,     bksge::ilogb(+inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(INT_MAX,     bksge::ilogb(-inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(FP_ILOGBNAN, bksge::ilogb(+nan));
	BKSGE_CONSTEXPR_EXPECT_EQ(FP_ILOGBNAN, bksge::ilogb(-nan));
}

template <typename T>
void ILogbTestSignedInt(void)
{
	EXPECT_EQ( 4, bksge::ilogb(T(-17)));
	EXPECT_EQ( 4, bksge::ilogb(T(-16)));
	EXPECT_EQ( 3, bksge::ilogb(T(-15)));
	EXPECT_EQ( 3, bksge::ilogb(T( -9)));
	EXPECT_EQ( 3, bksge::ilogb(T( -8)));
	EXPECT_EQ( 2, bksge::ilogb(T( -7)));
	EXPECT_EQ( 2, bksge::ilogb(T( -5)));
	EXPECT_EQ( 2, bksge::ilogb(T( -4)));
	EXPECT_EQ( 1, bksge::ilogb(T( -3)));
	EXPECT_EQ( 1, bksge::ilogb(T( -2)));
	EXPECT_EQ( 0, bksge::ilogb(T( -1)));
	EXPECT_EQ( 0, bksge::ilogb(T(  1)));
	EXPECT_EQ( 1, bksge::ilogb(T(  2)));
	EXPECT_EQ( 1, bksge::ilogb(T(  3)));
	EXPECT_EQ( 2, bksge::ilogb(T(  4)));
	EXPECT_EQ( 2, bksge::ilogb(T(  5)));
	EXPECT_EQ( 2, bksge::ilogb(T(  7)));
	EXPECT_EQ( 3, bksge::ilogb(T(  8)));
	EXPECT_EQ( 3, bksge::ilogb(T(  9)));
	EXPECT_EQ( 3, bksge::ilogb(T( 15)));
	EXPECT_EQ( 4, bksge::ilogb(T( 16)));
	EXPECT_EQ( 4, bksge::ilogb(T( 17)));

	BKSGE_CONSTEXPR_EXPECT_EQ(FP_ILOGB0, bksge::ilogb(T(0)));
}

template <typename T>
void ILogbTestUnsignedInt(void)
{
	EXPECT_EQ( 0, bksge::ilogb(T(  1)));
	EXPECT_EQ( 1, bksge::ilogb(T(  2)));
	EXPECT_EQ( 1, bksge::ilogb(T(  3)));
	EXPECT_EQ( 2, bksge::ilogb(T(  4)));
	EXPECT_EQ( 2, bksge::ilogb(T(  5)));
	EXPECT_EQ( 2, bksge::ilogb(T(  7)));
	EXPECT_EQ( 3, bksge::ilogb(T(  8)));
	EXPECT_EQ( 3, bksge::ilogb(T(  9)));
	EXPECT_EQ( 3, bksge::ilogb(T( 15)));
	EXPECT_EQ( 4, bksge::ilogb(T( 16)));
	EXPECT_EQ( 4, bksge::ilogb(T( 17)));

	BKSGE_CONSTEXPR_EXPECT_EQ(FP_ILOGB0, bksge::ilogb(T(0)));
}

GTEST_TEST(CMathTest, ILogbTest)
{
	ILogbTestFloat<float>();
	ILogbTestFloat<double>();
	ILogbTestFloat<long double>();

	ILogbTestSignedInt<int>();
//	ILogbTestSignedInt<signed char>();
	ILogbTestSignedInt<short>();
//	ILogbTestSignedInt<long>();
	ILogbTestSignedInt<long long>();

//	ILogbTestUnsignedInt<unsigned int>();
	ILogbTestUnsignedInt<unsigned char>();
//	ILogbTestUnsignedInt<unsigned short>();
	ILogbTestUnsignedInt<unsigned long>();
//	ILogbTestUnsignedInt<unsigned long long>();
}

}	// namespace ilogb_test

}	// namespace bksge_cmath_test
