/**
 *	@file	unit_test_fnd_cmath_fmax.cpp
 *
 *	@brief	fmax のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/fmax.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace fmax_test
{

static_assert(bksge::is_same<float,       decltype(bksge::fmax(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::fmaxf(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmax(0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmax(0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmax(0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmax(0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmax(0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmax(0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmax(0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmax(0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmax(0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmax(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmaxl(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmax(0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmax(0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmax(0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmax(0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmax(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void FMaxTestFloat(void)
{
	using R = bksge::float_promote_t<T1, T2>;

	BKSGE_CONSTEXPR auto nan1    = bksge::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2    = bksge::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf1    = bksge::numeric_limits<T1>::infinity();
	BKSGE_CONSTEXPR auto inf2    = bksge::numeric_limits<T2>::infinity();
	BKSGE_CONSTEXPR auto inf3    = bksge::numeric_limits<R>::infinity();

	BKSGE_CONSTEXPR_EXPECT_EQ( 0.5, bksge::fmax(T1( 0.5), T2( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1.5, bksge::fmax(T1( 0.5), T2( 1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1.5, bksge::fmax(T1( 1.5), T2( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2.5, bksge::fmax(T1( 2.5), T2( 1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2.5, bksge::fmax(T1( 1.5), T2( 2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0.5, bksge::fmax(T1(-0.5), T2( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0.5, bksge::fmax(T1( 0.5), T2(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-0.5, bksge::fmax(T1(-0.5), T2(-1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-0.5, bksge::fmax(T1(-1.5), T2(-0.5)));

	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::fmax( inf1,     T2( 2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::fmax( T1(3.5),  inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4.5,  bksge::fmax(-inf1,     T2( 4.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5.5,  bksge::fmax( T1(5.5), -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::fmax( inf1,     inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::fmax(-inf1,     inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::fmax( inf1,    -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::fmax(-inf1,    -inf2));

	BKSGE_CONSTEXPR_EXPECT_EQ( 0.5, bksge::fmax(nan1,    T2(0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0.5, bksge::fmax(T1(0.5), nan2));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmax(nan1, nan2)));
}

template <typename T1, typename T2>
void FMaxTestSignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fmax(T1( 0), T2( 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::fmax(T1( 0), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::fmax(T1( 1), T2( 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::fmax(T1( 2), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::fmax(T1( 1), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::fmax(T1(-1), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::fmax(T1( 1), T2(-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-2, bksge::fmax(T1(-2), T2(-3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-3, bksge::fmax(T1(-4), T2(-3)));
}

template <typename T1, typename T2>
void FMaxTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fmax(T1( 0), T2( 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::fmax(T1( 1), T2(10)));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::fmax(T1(11), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(20, bksge::fmax(T1(20), T2(10)));
	BKSGE_CONSTEXPR_EXPECT_EQ(21, bksge::fmax(T1(11), T2(21)));
}

GTEST_TEST(CMathTest, FMaxTest)
{
//	FMaxTestFloat<float,       float>();
	FMaxTestFloat<float,       double>();
//	FMaxTestFloat<float,       long double>();
	FMaxTestFloat<double,      float>();
//	FMaxTestFloat<double,      double>();
	FMaxTestFloat<double,      long double>();
//	FMaxTestFloat<long double, float>();
	FMaxTestFloat<long double, double>();
//	FMaxTestFloat<long double, long double>();

	FMaxTestSignedInt<int,         int>();
//	FMaxTestSignedInt<int,         float>();
	FMaxTestSignedInt<int,         double>();
//	FMaxTestSignedInt<int,         long double>();
	FMaxTestSignedInt<float,       int>();
//	FMaxTestSignedInt<double,      int>();
	FMaxTestSignedInt<long double, int>();

	FMaxTestUnsignedInt<unsigned int, unsigned int>();
//	FMaxTestUnsignedInt<unsigned int, float>();
	FMaxTestUnsignedInt<unsigned int, double>();
	FMaxTestUnsignedInt<unsigned int, long double>();
	FMaxTestUnsignedInt<float,        unsigned int>();
//	FMaxTestUnsignedInt<double,       unsigned int>();
	FMaxTestUnsignedInt<long double,  unsigned int>();
}

}	// namespace fmax_test

}	// namespace bksge_cmath_test
