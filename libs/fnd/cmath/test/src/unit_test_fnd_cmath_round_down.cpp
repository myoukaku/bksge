/**
 *	@file	unit_test_fnd_cmath_round_down.cpp
 *
 *	@brief	round_down のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/round_down.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace round_down_test
{

static_assert(bksge::is_same<float,       decltype(bksge::round_down(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::round_down(0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::round_down(0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::round_down(0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::round_down(0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::round_down(0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::round_down(0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::round_down(0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::round_down(0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::round_down(0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::round_down(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::round_down(0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<int,         decltype(bksge::round_down(0   , 0.0f))>::value, "");
static_assert(bksge::is_same<int,         decltype(bksge::round_down(0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<int,         decltype(bksge::round_down(0   , 0.0l))>::value, "");
static_assert(bksge::is_same<int,         decltype(bksge::round_down(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void RoundDownTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 0), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 0), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 0), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 0), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 0), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 0), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 0), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 0), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 0), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 0), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 0), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 0), T2(32)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  1), bksge::round_down(T1( 1), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 1), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 1), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 1), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 1), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 1), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 1), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 1), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 1), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 1), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 1), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 1), T2(32)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  2), bksge::round_down(T1( 2), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  2), bksge::round_down(T1( 2), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 2), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 2), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 2), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 2), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 2), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 2), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 2), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 2), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 2), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 2), T2(32)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  3), bksge::round_down(T1( 3), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  2), bksge::round_down(T1( 3), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  3), bksge::round_down(T1( 3), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 3), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 3), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 3), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 3), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 3), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 3), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 3), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 3), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 3), T2(32)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  9), bksge::round_down(T1( 9), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  8), bksge::round_down(T1( 9), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  9), bksge::round_down(T1( 9), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  8), bksge::round_down(T1( 9), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  5), bksge::round_down(T1( 9), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  7), bksge::round_down(T1( 9), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  8), bksge::round_down(T1( 9), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  9), bksge::round_down(T1( 9), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 9), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 9), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 9), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1( 9), T2(32)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 13), bksge::round_down(T1(13), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 12), bksge::round_down(T1(13), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 12), bksge::round_down(T1(13), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 12), bksge::round_down(T1(13), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 10), bksge::round_down(T1(13), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  7), bksge::round_down(T1(13), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  8), bksge::round_down(T1(13), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  9), bksge::round_down(T1(13), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1(13), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1(13), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1(13), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1(13), T2(32)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 17), bksge::round_down(T1(17), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 16), bksge::round_down(T1(17), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 15), bksge::round_down(T1(17), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 16), bksge::round_down(T1(17), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 15), bksge::round_down(T1(17), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 14), bksge::round_down(T1(17), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 16), bksge::round_down(T1(17), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  9), bksge::round_down(T1(17), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 15), bksge::round_down(T1(17), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 16), bksge::round_down(T1(17), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 17), bksge::round_down(T1(17), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_down(T1(17), T2(32)));
}

template <typename T1, typename T2>
void RoundDownTestSignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ( -1, bksge::round_down(T1(-1), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -2, bksge::round_down(T1(-1), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -3, bksge::round_down(T1(-1), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -4, bksge::round_down(T1(-1), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -5, bksge::round_down(T1(-1), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -7, bksge::round_down(T1(-1), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -8, bksge::round_down(T1(-1), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -9, bksge::round_down(T1(-1), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-15, bksge::round_down(T1(-1), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-16, bksge::round_down(T1(-1), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-17, bksge::round_down(T1(-1), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-32, bksge::round_down(T1(-1), T2(32)));

	BKSGE_CONSTEXPR_EXPECT_EQ( -2, bksge::round_down(T1(-2), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -2, bksge::round_down(T1(-2), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -3, bksge::round_down(T1(-2), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -4, bksge::round_down(T1(-2), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -5, bksge::round_down(T1(-2), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -7, bksge::round_down(T1(-2), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -8, bksge::round_down(T1(-2), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -9, bksge::round_down(T1(-2), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-15, bksge::round_down(T1(-2), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-16, bksge::round_down(T1(-2), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-17, bksge::round_down(T1(-2), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-32, bksge::round_down(T1(-2), T2(32)));

	BKSGE_CONSTEXPR_EXPECT_EQ( -3, bksge::round_down(T1(-3), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -4, bksge::round_down(T1(-3), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -3, bksge::round_down(T1(-3), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -4, bksge::round_down(T1(-3), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -5, bksge::round_down(T1(-3), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -7, bksge::round_down(T1(-3), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -8, bksge::round_down(T1(-3), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -9, bksge::round_down(T1(-3), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-15, bksge::round_down(T1(-3), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-16, bksge::round_down(T1(-3), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-17, bksge::round_down(T1(-3), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-32, bksge::round_down(T1(-3), T2(32)));

	BKSGE_CONSTEXPR_EXPECT_EQ( -9, bksge::round_down(T1(-9), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-10, bksge::round_down(T1(-9), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -9, bksge::round_down(T1(-9), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-12, bksge::round_down(T1(-9), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-10, bksge::round_down(T1(-9), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-14, bksge::round_down(T1(-9), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-16, bksge::round_down(T1(-9), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -9, bksge::round_down(T1(-9), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-15, bksge::round_down(T1(-9), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-16, bksge::round_down(T1(-9), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-17, bksge::round_down(T1(-9), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-32, bksge::round_down(T1(-9), T2(32)));

	BKSGE_CONSTEXPR_EXPECT_EQ(-17, bksge::round_down(T1(-17), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-18, bksge::round_down(T1(-17), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-18, bksge::round_down(T1(-17), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-20, bksge::round_down(T1(-17), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-20, bksge::round_down(T1(-17), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-21, bksge::round_down(T1(-17), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-24, bksge::round_down(T1(-17), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-18, bksge::round_down(T1(-17), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-30, bksge::round_down(T1(-17), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-32, bksge::round_down(T1(-17), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-17, bksge::round_down(T1(-17), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-32, bksge::round_down(T1(-17), T2(32)));

	RoundDownTestUnsignedInt<T1, T2>();
}

template <typename T1, typename T2>
void RoundDownTestFloat(void)
{
	using R = bksge::float_promote_t<T1, T2>;

	BKSGE_CONSTEXPR_EXPECT_EQ(R(-5.0), bksge::round_down(T1(-2.6), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2.5), bksge::round_down(T1(-2.5), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2.5), bksge::round_down(T1(-2.4), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2.5), bksge::round_down(T1(-0.1), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::round_down(T1( 0.0), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::round_down(T1( 0.1), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::round_down(T1( 2.4), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2.5), bksge::round_down(T1( 2.5), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2.5), bksge::round_down(T1( 2.6), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2.5), bksge::round_down(T1( 4.9), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 5.0), bksge::round_down(T1( 5.0), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 5.0), bksge::round_down(T1( 5.1), T2(2.5)));

	BKSGE_CONSTEXPR_EXPECT_EQ(R(-7.0), bksge::round_down(T1(-3.6), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-3.5), bksge::round_down(T1(-3.5), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-3.5), bksge::round_down(T1(-3.4), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-3.5), bksge::round_down(T1(-0.1), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::round_down(T1( 0.0), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::round_down(T1( 0.1), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::round_down(T1( 3.4), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 3.5), bksge::round_down(T1( 3.5), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 3.5), bksge::round_down(T1( 3.6), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 3.5), bksge::round_down(T1( 6.9), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 7.0), bksge::round_down(T1( 7.0), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 7.0), bksge::round_down(T1( 7.1), T2(3.5)));

	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2.5), bksge::round_down(T1(-2.6), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2.5), bksge::round_down(T1(-2.5), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::round_down(T1(-2.4), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::round_down(T1(-0.1), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::round_down(T1( 0.0), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2.5), bksge::round_down(T1( 0.1), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2.5), bksge::round_down(T1( 2.4), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2.5), bksge::round_down(T1( 2.5), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 5.0), bksge::round_down(T1( 2.6), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 5.0), bksge::round_down(T1( 4.9), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 5.0), bksge::round_down(T1( 5.0), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 7.5), bksge::round_down(T1( 5.1), T2(-2.5)));

	BKSGE_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf1 = std::numeric_limits<T1>::infinity();
	BKSGE_CONSTEXPR auto inf2 = std::numeric_limits<T2>::infinity();
	BKSGE_CONSTEXPR auto inf3 = std::numeric_limits<R>::infinity();

	// base が NaN  の場合、NaN  を返す。
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_down(T1( 1.0), nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_down(T1( 0.0), nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_down(T1(-1.0), nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_down( inf1, nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_down(-inf1, nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_down( nan1, nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_down(-nan1, nan2)));

	// x が NaN     の場合、NaN  を返す。
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_down( nan1, T2(2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_down(-nan1, T2(3.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_down( nan1, T2(0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_down(-nan1, T2(0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_down( nan1, inf2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_down(-nan1, inf2)));

	// base が ±∞ の場合、±∞ を返す。
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::round_down(T1( 1.0),  inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::round_down(T1( 0.0),  inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::round_down(T1(-1.0),  inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::round_down( inf1,     inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::round_down(-inf1,     inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::round_down(T1( 1.0), -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::round_down(T1( 0.0), -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::round_down(T1(-1.0), -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::round_down( inf1,    -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::round_down(-inf1,    -inf2));

	// x が ±∞    の場合、±∞ を返す。
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::round_down( inf1, T2(2.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::round_down(-inf1, T2(3.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::round_down( inf1, T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::round_down(-inf1, T2(0.0)));

	// base == 0　  の場合、x    を返す。
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 1.0), bksge::round_down(T1( 1.0), T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::round_down(T1( 0.0), T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-1.0), bksge::round_down(T1(-1.0), T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2.0), bksge::round_down(T1( 2.0), T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-3.0), bksge::round_down(T1(-3.0), T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::round_down( inf1, T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::round_down(-inf1, T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_down( nan1, T2(0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_down(-nan1, T2(0.0))));

	RoundDownTestSignedInt<T1, T2>();
}


GTEST_TEST(CMathTest, RoundDownTest)
{
	RoundDownTestSignedInt<int, signed char>();
//	RoundDownTestSignedInt<int, short>();
	RoundDownTestSignedInt<int, int>();
//	RoundDownTestSignedInt<int, long>();
	RoundDownTestSignedInt<int, long long>();
//	RoundDownTestSignedInt<signed char, signed char>();
	RoundDownTestSignedInt<signed char, short>();
//	RoundDownTestSignedInt<signed char, int>();
	RoundDownTestSignedInt<signed char, long>();
//	RoundDownTestSignedInt<signed char, long long>();
	RoundDownTestSignedInt<long long, signed char>();
//	RoundDownTestSignedInt<long long, short>();
	RoundDownTestSignedInt<long long, int>();
//	RoundDownTestSignedInt<long long, long>();
	RoundDownTestSignedInt<long long, long long>();

//	RoundDownTestUnsignedInt<unsigned int, unsigned char>();
	RoundDownTestUnsignedInt<unsigned int, unsigned short>();
//	RoundDownTestUnsignedInt<unsigned int, unsigned int>();
	RoundDownTestUnsignedInt<unsigned int, unsigned long>();
//	RoundDownTestUnsignedInt<unsigned int, unsigned long long>();
	RoundDownTestUnsignedInt<unsigned char, unsigned char>();
//	RoundDownTestUnsignedInt<unsigned char, unsigned short>();
	RoundDownTestUnsignedInt<unsigned char, unsigned int>();
//	RoundDownTestUnsignedInt<unsigned char, unsigned long>();
	RoundDownTestUnsignedInt<unsigned char, unsigned long long>();
//	RoundDownTestUnsignedInt<unsigned long long, unsigned char>();
	RoundDownTestUnsignedInt<unsigned long long, unsigned short>();
//	RoundDownTestUnsignedInt<unsigned long long, unsigned int>();
	RoundDownTestUnsignedInt<unsigned long long, unsigned long>();
//	RoundDownTestUnsignedInt<unsigned long long, unsigned long long>();

	RoundDownTestFloat<float, float>();
//	RoundDownTestFloat<float, double>();
	RoundDownTestFloat<float, long double>();
//	RoundDownTestFloat<double, float>();
	RoundDownTestFloat<double, double>();
//	RoundDownTestFloat<double, long double>();
	RoundDownTestFloat<long double, float>();
//	RoundDownTestFloat<long double, double>();
	RoundDownTestFloat<long double, long double>();
}

}	// namespace round_down_test

}	// namespace bksge_cmath_test
