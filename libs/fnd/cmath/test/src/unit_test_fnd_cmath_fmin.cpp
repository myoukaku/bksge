/**
 *	@file	unit_test_fnd_cmath_fmin.cpp
 *
 *	@brief	fmin のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/fmin.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace fmin_test
{

static_assert(bksge::is_same<float,       decltype(bksge::fmin(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::fminf(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmin(0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmin(0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmin(0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmin(0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmin(0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmin(0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmin(0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmin(0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmin(0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmin(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fminl(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmin(0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmin(0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmin(0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::fmin(0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::fmin(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void FMinTestFloat(void)
{
	using R = bksge::float_promote_t<T1, T2>;

	BKSGE_CONSTEXPR auto nan1    = std::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2    = std::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf1    = std::numeric_limits<T1>::infinity();
	BKSGE_CONSTEXPR auto inf2    = std::numeric_limits<T2>::infinity();
	BKSGE_CONSTEXPR auto inf3    = std::numeric_limits<R>::infinity();

	BKSGE_CONSTEXPR_EXPECT_EQ( 0.5, bksge::fmin(T1( 0.5), T2( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0.5, bksge::fmin(T1( 0.5), T2( 1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0.5, bksge::fmin(T1( 1.5), T2( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1.5, bksge::fmin(T1( 2.5), T2( 1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1.5, bksge::fmin(T1( 1.5), T2( 2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-0.5, bksge::fmin(T1(-0.5), T2( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-0.5, bksge::fmin(T1( 0.5), T2(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1.5, bksge::fmin(T1(-0.5), T2(-1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1.5, bksge::fmin(T1(-1.5), T2(-0.5)));

	BKSGE_CONSTEXPR_EXPECT_EQ( 2.5,  bksge::fmin( inf1,     T2( 2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3.5,  bksge::fmin( T1(3.5),  inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::fmin(-inf1,     T2( 4.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::fmin( T1(5.5), -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::fmin( inf1,     inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::fmin(-inf1,     inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::fmin( inf1,    -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::fmin(-inf1,    -inf2));

	BKSGE_CONSTEXPR_EXPECT_EQ( 0.5, bksge::fmin(nan1,    T2(0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0.5, bksge::fmin(T1(0.5), nan2));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmin(nan1, nan2)));
}

template <typename T1, typename T2>
void FMinTestSignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fmin(T1( 0), T2( 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fmin(T1( 0), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fmin(T1( 1), T2( 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::fmin(T1( 2), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::fmin(T1( 1), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1, bksge::fmin(T1(-1), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1, bksge::fmin(T1( 1), T2(-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-3, bksge::fmin(T1(-2), T2(-3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-4, bksge::fmin(T1(-4), T2(-3)));
}

template <typename T1, typename T2>
void FMinTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::fmin(T1( 0), T2( 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::fmin(T1( 1), T2(10)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::fmin(T1(10), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::fmin(T1(20), T2(10)));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::fmin(T1(11), T2(20)));
}

GTEST_TEST(CMathTest, FMinTest)
{
	FMinTestFloat<float,       float>();
//	FMinTestFloat<float,       double>();
	FMinTestFloat<float,       long double>();
//	FMinTestFloat<double,      float>();
	FMinTestFloat<double,      double>();
//	FMinTestFloat<double,      long double>();
	FMinTestFloat<long double, float>();
//	FMinTestFloat<long double, double>();
	FMinTestFloat<long double, long double>();

//	FMinTestSignedInt<int,         int>();
	FMinTestSignedInt<int,         float>();
//	FMinTestSignedInt<int,         double>();
	FMinTestSignedInt<int,         long double>();
//	FMinTestSignedInt<float,       int>();
	FMinTestSignedInt<double,      int>();
//	FMinTestSignedInt<long double, int>();

	FMinTestUnsignedInt<unsigned int, unsigned int>();
//	FMinTestUnsignedInt<unsigned int, float>();
	FMinTestUnsignedInt<unsigned int, double>();
//	FMinTestUnsignedInt<unsigned int, long double>();
	FMinTestUnsignedInt<float,        unsigned int>();
//	FMinTestUnsignedInt<double,       unsigned int>();
	FMinTestUnsignedInt<long double,  unsigned int>();
}

}	// namespace fmin_test

}	// namespace bksge_cmath_test
