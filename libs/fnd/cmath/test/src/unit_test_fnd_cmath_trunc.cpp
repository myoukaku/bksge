/**
 *	@file	unit_test_fnd_cmath_trunc.cpp
 *
 *	@brief	trunc のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/trunc.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace trunc_test
{

static_assert(bksge::is_same<float,       decltype(bksge::trunc(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::truncf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::trunc(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::trunc(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::trunc(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::truncl(0.0l))>::value, "");

template <typename T>
void TruncTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto eps = std::numeric_limits<T>::epsilon() * 2;

	BKSGE_CONSTEXPR_EXPECT_EQ(T( 0.0), bksge::trunc(T( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 0.0), bksge::trunc(T( 0.1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 0.0), bksge::trunc(T( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 0.0), bksge::trunc(T( 0.9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 0.0), bksge::trunc(T( 1.0) - eps));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 1.0), bksge::trunc(T( 1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 1.0), bksge::trunc(T( 1.1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 1.0), bksge::trunc(T( 1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 1.0), bksge::trunc(T( 1.9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 1.0), bksge::trunc(T( 2.0) - eps));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 2.0), bksge::trunc(T( 2.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 2.0), bksge::trunc(T( 2.1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 2.0), bksge::trunc(T( 2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 2.0), bksge::trunc(T( 2.9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 2.0), bksge::trunc(T( 3.0) - eps));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 3.0), bksge::trunc(T( 3.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 0.0), bksge::trunc(T(-0.1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 0.0), bksge::trunc(T(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 0.0), bksge::trunc(T(-0.9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 0.0), bksge::trunc(T(-1.0) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-1.0), bksge::trunc(T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-1.0), bksge::trunc(T(-1.1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-1.0), bksge::trunc(T(-1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-1.0), bksge::trunc(T(-1.9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-1.0), bksge::trunc(T(-2.0) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-2.0), bksge::trunc(T(-2.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-2.0), bksge::trunc(T(-2.1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-2.0), bksge::trunc(T(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-2.0), bksge::trunc(T(-2.9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-2.0), bksge::trunc(T(-3.0) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-3.0), bksge::trunc(T(-3.0)));

	BKSGE_CONSTEXPR_EXPECT_EQ( inf, bksge::trunc(+inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::trunc(-inf));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isinf  (bksge::trunc(+inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isinf  (bksge::trunc(-inf)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::trunc(+inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::signbit(bksge::trunc(-inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::trunc(T(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::trunc(T(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::trunc(T(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::trunc(T(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan  (bksge::trunc(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan  (bksge::trunc(-nan)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::trunc(+nan)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::trunc(-nan)));
}

template <typename T>
void TruncTestSignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(T(   0), bksge::trunc(T(   0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(   1), bksge::trunc(T(   1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(  -1), bksge::trunc(T(  -1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(   3), bksge::trunc(T(   3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(  -3), bksge::trunc(T(  -3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 100), bksge::trunc(T( 100)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-100), bksge::trunc(T(-100)));
}

template <typename T>
void TruncTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(T(   0), bksge::trunc(T(   0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(   1), bksge::trunc(T(   1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(   3), bksge::trunc(T(   3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 100), bksge::trunc(T( 100)));
}

GTEST_TEST(CMathTest, TruncTest)
{
	TruncTestFloat<float>();
	TruncTestFloat<double>();
	TruncTestFloat<long double>();

	TruncTestSignedInt<int>();
//	TruncTestSignedInt<signed char>();
	TruncTestSignedInt<short>();
//	TruncTestSignedInt<long>();
	TruncTestSignedInt<long long>();

//	TruncTestUnsignedInt<unsigned int>();
	TruncTestUnsignedInt<unsigned char>();
//	TruncTestUnsignedInt<unsigned short>();
	TruncTestUnsignedInt<unsigned long>();
//	TruncTestUnsignedInt<unsigned long long>();
}

}	// namespace trunc_test

}	// namespace bksge_cmath_test
