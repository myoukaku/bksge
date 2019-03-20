/**
 *	@file	unit_test_cmath_round_up.cpp
 *
 *	@brief	round_up のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/cmath/round_up.hpp>
#include <bksge/cmath/isnan.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace round_up_test
{

template <typename T1, typename T2>
void RoundUpTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_up(T1( 0), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_up(T1( 0), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_up(T1( 0), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_up(T1( 0), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_up(T1( 0), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_up(T1( 0), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_up(T1( 0), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_up(T1( 0), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_up(T1( 0), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_up(T1( 0), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_up(T1( 0), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  0), bksge::round_up(T1( 0), T2(32)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  1), bksge::round_up(T1( 1), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  2), bksge::round_up(T1( 1), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  3), bksge::round_up(T1( 1), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  4), bksge::round_up(T1( 1), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  5), bksge::round_up(T1( 1), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  7), bksge::round_up(T1( 1), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  8), bksge::round_up(T1( 1), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  9), bksge::round_up(T1( 1), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 15), bksge::round_up(T1( 1), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 16), bksge::round_up(T1( 1), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 17), bksge::round_up(T1( 1), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 32), bksge::round_up(T1( 1), T2(32)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  2), bksge::round_up(T1( 2), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  2), bksge::round_up(T1( 2), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  3), bksge::round_up(T1( 2), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  4), bksge::round_up(T1( 2), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  5), bksge::round_up(T1( 2), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  7), bksge::round_up(T1( 2), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  8), bksge::round_up(T1( 2), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  9), bksge::round_up(T1( 2), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 15), bksge::round_up(T1( 2), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 16), bksge::round_up(T1( 2), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 17), bksge::round_up(T1( 2), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 32), bksge::round_up(T1( 2), T2(32)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  3), bksge::round_up(T1( 3), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  4), bksge::round_up(T1( 3), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  3), bksge::round_up(T1( 3), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  4), bksge::round_up(T1( 3), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  5), bksge::round_up(T1( 3), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  7), bksge::round_up(T1( 3), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  8), bksge::round_up(T1( 3), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  9), bksge::round_up(T1( 3), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 15), bksge::round_up(T1( 3), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 16), bksge::round_up(T1( 3), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 17), bksge::round_up(T1( 3), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 32), bksge::round_up(T1( 3), T2(32)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  9), bksge::round_up(T1( 9), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 10), bksge::round_up(T1( 9), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  9), bksge::round_up(T1( 9), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 12), bksge::round_up(T1( 9), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 10), bksge::round_up(T1( 9), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 14), bksge::round_up(T1( 9), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 16), bksge::round_up(T1( 9), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1(  9), bksge::round_up(T1( 9), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 15), bksge::round_up(T1( 9), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 16), bksge::round_up(T1( 9), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 17), bksge::round_up(T1( 9), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 32), bksge::round_up(T1( 9), T2(32)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 17), bksge::round_up(T1(17), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 18), bksge::round_up(T1(17), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 18), bksge::round_up(T1(17), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 20), bksge::round_up(T1(17), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 20), bksge::round_up(T1(17), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 21), bksge::round_up(T1(17), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 24), bksge::round_up(T1(17), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 18), bksge::round_up(T1(17), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 30), bksge::round_up(T1(17), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 32), bksge::round_up(T1(17), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 17), bksge::round_up(T1(17), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T1( 32), bksge::round_up(T1(17), T2(32)));
}

template <typename T1, typename T2>
void RoundUpTestSignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ( -1, bksge::round_up(T1(-1), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-1), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-1), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-1), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-1), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-1), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-1), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-1), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-1), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-1), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-1), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-1), T2(32)));

	BKSGE_CONSTEXPR_EXPECT_EQ( -2, bksge::round_up(T1(-2), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -2, bksge::round_up(T1(-2), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-2), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-2), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-2), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-2), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-2), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-2), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-2), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-2), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-2), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-2), T2(32)));

	BKSGE_CONSTEXPR_EXPECT_EQ( -3, bksge::round_up(T1(-3), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -2, bksge::round_up(T1(-3), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -3, bksge::round_up(T1(-3), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-3), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-3), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-3), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-3), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-3), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-3), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-3), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-3), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-3), T2(32)));

	BKSGE_CONSTEXPR_EXPECT_EQ( -9, bksge::round_up(T1(-9), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -8, bksge::round_up(T1(-9), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -9, bksge::round_up(T1(-9), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -8, bksge::round_up(T1(-9), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -5, bksge::round_up(T1(-9), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -7, bksge::round_up(T1(-9), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -8, bksge::round_up(T1(-9), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -9, bksge::round_up(T1(-9), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-9), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-9), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-9), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-9), T2(32)));

	BKSGE_CONSTEXPR_EXPECT_EQ(-17, bksge::round_up(T1(-17), T2( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-16, bksge::round_up(T1(-17), T2( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-15, bksge::round_up(T1(-17), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-16, bksge::round_up(T1(-17), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-15, bksge::round_up(T1(-17), T2( 5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-14, bksge::round_up(T1(-17), T2( 7)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-16, bksge::round_up(T1(-17), T2( 8)));
	BKSGE_CONSTEXPR_EXPECT_EQ( -9, bksge::round_up(T1(-17), T2( 9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-15, bksge::round_up(T1(-17), T2(15)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-16, bksge::round_up(T1(-17), T2(16)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-17, bksge::round_up(T1(-17), T2(17)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  0, bksge::round_up(T1(-17), T2(32)));

	RoundUpTestUnsignedInt<T1, T2>();
}

template <typename T1, typename T2>
void RoundUpTestFloat(void)
{
	using R = bksge::float_promote_t<T1, T2>;

	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2.5), bksge::round_up(T1(-2.6), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2.5), bksge::round_up(T1(-2.5), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::round_up(T1(-2.4), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::round_up(T1(-0.1), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::round_up(T1( 0.0), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2.5), bksge::round_up(T1( 0.1), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2.5), bksge::round_up(T1( 2.4), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2.5), bksge::round_up(T1( 2.5), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 5.0), bksge::round_up(T1( 2.6), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 5.0), bksge::round_up(T1( 4.9), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 5.0), bksge::round_up(T1( 5.0), T2(2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 7.5), bksge::round_up(T1( 5.1), T2(2.5)));

	BKSGE_CONSTEXPR_EXPECT_EQ(R(-3.5), bksge::round_up(T1(-3.6), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-3.5), bksge::round_up(T1(-3.5), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::round_up(T1(-3.4), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::round_up(T1(-0.1), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::round_up(T1( 0.0), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 3.5), bksge::round_up(T1( 0.1), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 3.5), bksge::round_up(T1( 3.4), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 3.5), bksge::round_up(T1( 3.5), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 7.0), bksge::round_up(T1( 3.6), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 7.0), bksge::round_up(T1( 6.9), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 7.0), bksge::round_up(T1( 7.0), T2(3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(10.5), bksge::round_up(T1( 7.1), T2(3.5)));

	BKSGE_CONSTEXPR_EXPECT_EQ(R(-5.0), bksge::round_up(T1(-2.6), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2.5), bksge::round_up(T1(-2.5), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2.5), bksge::round_up(T1(-2.4), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2.5), bksge::round_up(T1(-0.1), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::round_up(T1( 0.0), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::round_up(T1( 0.1), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::round_up(T1( 2.4), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2.5), bksge::round_up(T1( 2.5), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2.5), bksge::round_up(T1( 2.6), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2.5), bksge::round_up(T1( 4.9), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 5.0), bksge::round_up(T1( 5.0), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 5.0), bksge::round_up(T1( 5.1), T2(-2.5)));

	BKSGE_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf1 = std::numeric_limits<T1>::infinity();
	BKSGE_CONSTEXPR auto inf2 = std::numeric_limits<T2>::infinity();
	BKSGE_CONSTEXPR auto inf3 = std::numeric_limits<R>::infinity();

	// base が NaN  の場合、NaN  を返す。
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_up(T1( 1.0), nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_up(T1( 0.0), nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_up(T1(-1.0), nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_up( inf1, nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_up(-inf1, nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_up( nan1, nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_up(-nan1, nan2)));

	// x が NaN     の場合、NaN  を返す。
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_up( nan1, T2(2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_up(-nan1, T2(3.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_up( nan1, T2(0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_up(-nan1, T2(0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_up( nan1, inf2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_up(-nan1, inf2)));

	// base が ±∞ の場合、±∞ を返す。
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::round_up(T1( 1.0),  inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::round_up(T1( 0.0),  inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::round_up(T1(-1.0),  inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::round_up( inf1,     inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::round_up(-inf1,     inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::round_up(T1( 1.0), -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::round_up(T1( 0.0), -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::round_up(T1(-1.0), -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::round_up( inf1,    -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::round_up(-inf1,    -inf2));

	// x が ±∞    の場合、±∞ を返す。
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::round_up( inf1, T2(2.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::round_up(-inf1, T2(3.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::round_up( inf1, T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::round_up(-inf1, T2(0.0)));

	// base == 0　  の場合、x    を返す。
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 1.0), bksge::round_up(T1( 1.0), T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::round_up(T1( 0.0), T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-1.0), bksge::round_up(T1(-1.0), T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2.0), bksge::round_up(T1( 2.0), T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-3.0), bksge::round_up(T1(-3.0), T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( inf3, bksge::round_up( inf1, T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf3, bksge::round_up(-inf1, T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_up( nan1, T2(0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round_up(-nan1, T2(0.0))));

	RoundUpTestSignedInt<T1, T2>();
}

GTEST_TEST(CMathTest, RoundUpTest)
{
	RoundUpTestSignedInt<int, signed char>();
//	RoundUpTestSignedInt<int, short>();
	RoundUpTestSignedInt<int, int>();
//	RoundUpTestSignedInt<int, long>();
	RoundUpTestSignedInt<int, long long>();
//	RoundUpTestSignedInt<signed char, signed char>();
	RoundUpTestSignedInt<signed char, short>();
//	RoundUpTestSignedInt<signed char, int>();
	RoundUpTestSignedInt<signed char, long>();
//	RoundUpTestSignedInt<signed char, long long>();
	RoundUpTestSignedInt<long long, signed char>();
//	RoundUpTestSignedInt<long long, short>();
	RoundUpTestSignedInt<long long, int>();
//	RoundUpTestSignedInt<long long, long>();
	RoundUpTestSignedInt<long long, long long>();

//	RoundUpTestUnsignedInt<unsigned int, unsigned char>();
	RoundUpTestUnsignedInt<unsigned int, unsigned short>();
//	RoundUpTestUnsignedInt<unsigned int, unsigned int>();
	RoundUpTestUnsignedInt<unsigned int, unsigned long>();
//	RoundUpTestUnsignedInt<unsigned int, unsigned long long>();
	RoundUpTestUnsignedInt<unsigned char, unsigned char>();
//	RoundUpTestUnsignedInt<unsigned char, unsigned short>();
	RoundUpTestUnsignedInt<unsigned char, unsigned int>();
//	RoundUpTestUnsignedInt<unsigned char, unsigned long>();
	RoundUpTestUnsignedInt<unsigned char, unsigned long long>();
//	RoundUpTestUnsignedInt<unsigned long long, unsigned char>();
	RoundUpTestUnsignedInt<unsigned long long, unsigned short>();
//	RoundUpTestUnsignedInt<unsigned long long, unsigned int>();
	RoundUpTestUnsignedInt<unsigned long long, unsigned long>();
//	RoundUpTestUnsignedInt<unsigned long long, unsigned long long>();

	RoundUpTestFloat<float, float>();
//	RoundUpTestFloat<float, double>();
	RoundUpTestFloat<float, long double>();
//	RoundUpTestFloat<double, float>();
	RoundUpTestFloat<double, double>();
//	RoundUpTestFloat<double, long double>();
	RoundUpTestFloat<long double, float>();
//	RoundUpTestFloat<long double, double>();
	RoundUpTestFloat<long double, long double>();
}

}	// namespace round_up_test

}	// namespace bksge_cmath_test
