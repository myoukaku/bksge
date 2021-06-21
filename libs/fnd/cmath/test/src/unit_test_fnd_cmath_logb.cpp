/**
 *	@file	unit_test_fnd_cmath_logb.cpp
 *
 *	@brief	logb のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/logb.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace frexp_test
{

static_assert(bksge::is_same<float,       decltype(bksge::logb(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::logbf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::logb(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::logb(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::logb(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::logbl(0.0l))>::value, "");

template <typename T>
void LogbTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	EXPECT_EQ( 4, bksge::logb(T(-17.0)));
	EXPECT_EQ( 4, bksge::logb(T(-16.0)));
	EXPECT_EQ( 3, bksge::logb(T(-15.0)));
	EXPECT_EQ( 3, bksge::logb(T( -9.0)));
	EXPECT_EQ( 3, bksge::logb(T( -8.0)));
	EXPECT_EQ( 2, bksge::logb(T( -7.0)));
	EXPECT_EQ( 2, bksge::logb(T( -5.0)));
	EXPECT_EQ( 2, bksge::logb(T( -4.0)));
	EXPECT_EQ( 1, bksge::logb(T( -3.0)));
	EXPECT_EQ( 1, bksge::logb(T( -2.0)));
	EXPECT_EQ( 0, bksge::logb(T( -1.0)));
	EXPECT_EQ(-1, bksge::logb(T( -0.5)));
	EXPECT_EQ(-2, bksge::logb(T( -0.25)));
	EXPECT_EQ(-3, bksge::logb(T( -0.125)));
	EXPECT_EQ(-3, bksge::logb(T(  0.125)));
	EXPECT_EQ(-2, bksge::logb(T(  0.25)));
	EXPECT_EQ(-1, bksge::logb(T(  0.5)));
	EXPECT_EQ( 0, bksge::logb(T(  1.0)));
	EXPECT_EQ( 0, bksge::logb(T(  1.5)));
	EXPECT_EQ( 1, bksge::logb(T(  2.0)));
	EXPECT_EQ( 1, bksge::logb(T(  2.5)));
	EXPECT_EQ( 1, bksge::logb(T(  3.0)));
	EXPECT_EQ( 1, bksge::logb(T(  3.5)));
	EXPECT_EQ( 2, bksge::logb(T(  4.0)));
	EXPECT_EQ( 2, bksge::logb(T(  4.5)));
	EXPECT_EQ( 2, bksge::logb(T(  5.0)));
	EXPECT_EQ( 2, bksge::logb(T(  7.0)));
	EXPECT_EQ( 3, bksge::logb(T(  8.0)));
	EXPECT_EQ( 3, bksge::logb(T(  9.0)));
	EXPECT_EQ( 3, bksge::logb(T( 15.0)));
	EXPECT_EQ( 4, bksge::logb(T( 16.0)));
	EXPECT_EQ( 4, bksge::logb(T( 17.0)));

	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::logb(T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::logb(T(-0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::logb(+inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::logb(-inf));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::logb(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::logb(-nan)));
}

template <typename T>
void LogbTestSignedInt(void)
{
	using R = bksge::float_promote_t<T>;
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<R>::infinity();

	EXPECT_EQ( 4, bksge::logb(T(-17)));
	EXPECT_EQ( 4, bksge::logb(T(-16)));
	EXPECT_EQ( 3, bksge::logb(T(-15)));
	EXPECT_EQ( 3, bksge::logb(T( -9)));
	EXPECT_EQ( 3, bksge::logb(T( -8)));
	EXPECT_EQ( 2, bksge::logb(T( -7)));
	EXPECT_EQ( 2, bksge::logb(T( -5)));
	EXPECT_EQ( 2, bksge::logb(T( -4)));
	EXPECT_EQ( 1, bksge::logb(T( -3)));
	EXPECT_EQ( 1, bksge::logb(T( -2)));
	EXPECT_EQ( 0, bksge::logb(T( -1)));
	EXPECT_EQ( 0, bksge::logb(T(  1)));
	EXPECT_EQ( 1, bksge::logb(T(  2)));
	EXPECT_EQ( 1, bksge::logb(T(  3)));
	EXPECT_EQ( 2, bksge::logb(T(  4)));
	EXPECT_EQ( 2, bksge::logb(T(  5)));
	EXPECT_EQ( 2, bksge::logb(T(  7)));
	EXPECT_EQ( 3, bksge::logb(T(  8)));
	EXPECT_EQ( 3, bksge::logb(T(  9)));
	EXPECT_EQ( 3, bksge::logb(T( 15)));
	EXPECT_EQ( 4, bksge::logb(T( 16)));
	EXPECT_EQ( 4, bksge::logb(T( 17)));

	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::logb(T(0)));
}

template <typename T>
void LogbTestUnsignedInt(void)
{
	using R = bksge::float_promote_t<T>;
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<R>::infinity();

	EXPECT_EQ( 0, bksge::logb(T(  1)));
	EXPECT_EQ( 1, bksge::logb(T(  2)));
	EXPECT_EQ( 1, bksge::logb(T(  3)));
	EXPECT_EQ( 2, bksge::logb(T(  4)));
	EXPECT_EQ( 2, bksge::logb(T(  5)));
	EXPECT_EQ( 2, bksge::logb(T(  7)));
	EXPECT_EQ( 3, bksge::logb(T(  8)));
	EXPECT_EQ( 3, bksge::logb(T(  9)));
	EXPECT_EQ( 3, bksge::logb(T( 15)));
	EXPECT_EQ( 4, bksge::logb(T( 16)));
	EXPECT_EQ( 4, bksge::logb(T( 17)));

	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::logb(T(0)));
}

GTEST_TEST(CMathTest, LogbTest)
{
	LogbTestFloat<float>();
	LogbTestFloat<double>();
	LogbTestFloat<long double>();

//	LogbTestSignedInt<int>();
	LogbTestSignedInt<signed char>();
//	LogbTestSignedInt<short>();
	LogbTestSignedInt<long>();
//	LogbTestSignedInt<long long>();

	LogbTestUnsignedInt<unsigned int>();
//	LogbTestUnsignedInt<unsigned char>();
	LogbTestUnsignedInt<unsigned short>();
//	LogbTestUnsignedInt<unsigned long>();
	LogbTestUnsignedInt<unsigned long long>();
}

}	// namespace frexp_test

}	// namespace bksge_cmath_test
