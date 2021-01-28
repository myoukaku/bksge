/**
 *	@file	unit_test_fnd_cmath_hypot.cpp
 *
 *	@brief	hypot のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/hypot.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/sqrt.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace hypot_test
{

static_assert(bksge::is_same<float,       decltype(bksge::hypot(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::hypotf(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypotl(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0   , 0   ))>::value, "");

static_assert(bksge::is_same<float,       decltype(bksge::hypot(0.0f, 0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0f, 0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0f, 0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0f, 0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0f, 0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0f, 0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0f, 0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0f, 0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0f, 0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0f, 0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0f, 0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0f, 0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0f, 0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0f, 0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0f, 0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0f, 0   , 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0 , 0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0 , 0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0 , 0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0 , 0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0 , 0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0 , 0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0 , 0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0 , 0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0 , 0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0 , 0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0 , 0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0 , 0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0 , 0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0 , 0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0 , 0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0.0 , 0   , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0l, 0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0l, 0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0l, 0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0l, 0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0l, 0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0l, 0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0l, 0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0l, 0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0l, 0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0l, 0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0l, 0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0l, 0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0l, 0   , 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0l, 0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0l, 0   , 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0.0l, 0   , 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0   , 0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0   , 0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0   , 0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0   , 0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0   , 0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0   , 0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0   , 0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0   , 0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0   , 0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0   , 0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0   , 0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0   , 0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0   , 0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0   , 0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::hypot(0   , 0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::hypot(0   , 0   , 0   ))>::value, "");

template <typename T>
void HypotTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan    = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf    = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto max    = bksge::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto lowest = bksge::numeric_limits<T>::lowest();

	EXPECT_NEAR(0.0000000000000000000000000000000, (double)bksge::hypot(T( 0.0), T( 0.0)), error);
	EXPECT_NEAR(0.5000000000000000000000000000000, (double)bksge::hypot(T( 0.0), T( 0.5)), error);
	EXPECT_NEAR(0.5000000000000000000000000000000, (double)bksge::hypot(T( 0.0), T(-0.5)), error);
	EXPECT_NEAR(1.5000000000000000000000000000000, (double)bksge::hypot(T( 0.0), T( 1.5)), error);
	EXPECT_NEAR(1.5000000000000000000000000000000, (double)bksge::hypot(T( 0.0), T(-1.5)), error);
	EXPECT_NEAR(0.5000000000000000000000000000000, (double)bksge::hypot(T( 0.5), T( 0.0)), error);
	EXPECT_NEAR(0.7071067811865475244008443621048, (double)bksge::hypot(T( 0.5), T( 0.5)), error);
	EXPECT_NEAR(0.7071067811865475244008443621048, (double)bksge::hypot(T( 0.5), T(-0.5)), error);
	EXPECT_NEAR(1.5811388300841896659994467722164, (double)bksge::hypot(T( 0.5), T( 1.5)), error);
	EXPECT_NEAR(1.5811388300841896659994467722164, (double)bksge::hypot(T( 0.5), T(-1.5)), error);
	EXPECT_NEAR(0.5000000000000000000000000000000, (double)bksge::hypot(T(-0.5), T( 0.0)), error);
	EXPECT_NEAR(0.7071067811865475244008443621048, (double)bksge::hypot(T(-0.5), T( 0.5)), error);
	EXPECT_NEAR(0.7071067811865475244008443621048, (double)bksge::hypot(T(-0.5), T(-0.5)), error);
	EXPECT_NEAR(1.5811388300841896659994467722164, (double)bksge::hypot(T(-0.5), T( 1.5)), error);
	EXPECT_NEAR(1.5811388300841896659994467722164, (double)bksge::hypot(T(-0.5), T(-1.5)), error);
	EXPECT_NEAR(2.5000000000000000000000000000000, (double)bksge::hypot(T( 2.5), T( 0.0)), error);
	EXPECT_NEAR(2.5495097567963924150141120545114, (double)bksge::hypot(T( 2.5), T( 0.5)), error);
	EXPECT_NEAR(2.5495097567963924150141120545114, (double)bksge::hypot(T( 2.5), T(-0.5)), error);
	EXPECT_NEAR(2.9154759474226502354370764387728, (double)bksge::hypot(T( 2.5), T( 1.5)), error);
	EXPECT_NEAR(2.9154759474226502354370764387728, (double)bksge::hypot(T( 2.5), T(-1.5)), error);
	EXPECT_NEAR(2.5000000000000000000000000000000, (double)bksge::hypot(T(-2.5), T( 0.0)), error);
	EXPECT_NEAR(2.5495097567963924150141120545114, (double)bksge::hypot(T(-2.5), T( 0.5)), error);
	EXPECT_NEAR(2.5495097567963924150141120545114, (double)bksge::hypot(T(-2.5), T(-0.5)), error);
	EXPECT_NEAR(2.9154759474226502354370764387728, (double)bksge::hypot(T(-2.5), T( 1.5)), error);
	EXPECT_NEAR(2.9154759474226502354370764387728, (double)bksge::hypot(T(-2.5), T(-1.5)), error);

	// if one of the arguments is ±0, hypot(x,y) is equivalent to fabs called with the non-zero argument
	BKSGE_CONSTEXPR_EXPECT_EQ(2.0, bksge::hypot(T(+0.0), T( 2.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(3.0, bksge::hypot(T(-0.0), T( 3.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(4.0, bksge::hypot(T(+0.0), T(-4.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(5.0, bksge::hypot(T(-0.0), T(-5.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(max, bksge::hypot(T(+0.0), max));
	BKSGE_CONSTEXPR_EXPECT_EQ(max, bksge::hypot(T(-0.0), max));
	BKSGE_CONSTEXPR_EXPECT_EQ(max, bksge::hypot(T(+0.0), lowest));
	BKSGE_CONSTEXPR_EXPECT_EQ(max, bksge::hypot(T(-0.0), lowest));
	BKSGE_CONSTEXPR_EXPECT_EQ(2.0, bksge::hypot(T( 2.0), T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(3.0, bksge::hypot(T( 3.0), T(-0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(4.0, bksge::hypot(T(-4.0), T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(5.0, bksge::hypot(T(-5.0), T(-0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(max, bksge::hypot(max,     T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(max, bksge::hypot(max,     T(-0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(max, bksge::hypot(lowest,  T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(max, bksge::hypot(lowest,  T(-0.0)));

	// if one of the arguments is ±∞, hypot(x,y) returns +∞ even if the other argument is NaN
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::hypot(+inf,    T(1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::hypot(-inf,    T(1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::hypot(+inf,    max));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::hypot(-inf,    max));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::hypot(+inf,    lowest));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::hypot(-inf,    lowest));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::hypot(+inf,    +nan));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::hypot(-inf,    +nan));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::hypot(+inf,    -nan));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::hypot(-inf,    -nan));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::hypot(T(1.0),  +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::hypot(T(1.0),  -inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::hypot(+nan,    +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::hypot(+nan,    -inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::hypot(-nan,    +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::hypot(-nan,    -inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::hypot(max,     +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::hypot(max,     -inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::hypot(lowest,  +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::hypot(lowest,  -inf));

	// otherwise, if any of the arguments is NaN, NaN is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::hypot(+nan,   T(2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::hypot(-nan,   T(3.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::hypot(T(4.0), +nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::hypot(T(5.0), -nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::hypot(+nan,   +nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::hypot(-nan,   +nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::hypot(+nan,   -nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::hypot(-nan,   -nan)));
}

template <typename T>
void HypotTestInteger(void)
{
	BKSGE_CONSTEXPR double error = 0.0000000000001;

	EXPECT_NEAR(  0.00000000000000000000000000000, bksge::hypot(T(  0), T(  0)), error);
	EXPECT_NEAR(  1.00000000000000000000000000000, bksge::hypot(T(  0), T(  1)), error);
	EXPECT_NEAR(  1.00000000000000000000000000000, bksge::hypot(T(  0), T( -1)), error);
	EXPECT_NEAR(  2.00000000000000000000000000000, bksge::hypot(T(  0), T(  2)), error);
	EXPECT_NEAR(  2.00000000000000000000000000000, bksge::hypot(T(  0), T( -2)), error);
	EXPECT_NEAR( 99.00000000000000000000000000000, bksge::hypot(T(  0), T( 99)), error);
	EXPECT_NEAR( 99.00000000000000000000000000000, bksge::hypot(T(  0), T(-99)), error);
	EXPECT_NEAR(  1.00000000000000000000000000000, bksge::hypot(T(  1), T(  0)), error);
	EXPECT_NEAR(  1.41421356237309504880168872420, bksge::hypot(T(  1), T(  1)), error);
	EXPECT_NEAR(  1.41421356237309504880168872420, bksge::hypot(T(  1), T( -1)), error);
	EXPECT_NEAR(  2.23606797749978969640917366873, bksge::hypot(T(  1), T(  2)), error);
	EXPECT_NEAR(  2.23606797749978969640917366873, bksge::hypot(T(  1), T( -2)), error);
	EXPECT_NEAR( 99.00505037623080771359834335305, bksge::hypot(T(  1), T( 99)), error);
	EXPECT_NEAR( 99.00505037623080771359834335305, bksge::hypot(T(  1), T(-99)), error);
	EXPECT_NEAR(  1.00000000000000000000000000000, bksge::hypot(T( -1), T(  0)), error);
	EXPECT_NEAR(  1.41421356237309504880168872420, bksge::hypot(T( -1), T(  1)), error);
	EXPECT_NEAR(  1.41421356237309504880168872420, bksge::hypot(T( -1), T( -1)), error);
	EXPECT_NEAR(  2.23606797749978969640917366873, bksge::hypot(T( -1), T(  2)), error);
	EXPECT_NEAR(  2.23606797749978969640917366873, bksge::hypot(T( -1), T( -2)), error);
	EXPECT_NEAR( 99.00505037623080771359834335305, bksge::hypot(T( -1), T( 99)), error);
	EXPECT_NEAR( 99.00505037623080771359834335305, bksge::hypot(T( -1), T(-99)), error);
	EXPECT_NEAR(  2.00000000000000000000000000000, bksge::hypot(T(  2), T(  0)), error);
	EXPECT_NEAR(  2.23606797749978969640917366873, bksge::hypot(T(  2), T(  1)), error);
	EXPECT_NEAR(  2.23606797749978969640917366873, bksge::hypot(T(  2), T( -1)), error);
	EXPECT_NEAR(  2.82842712474619009760337744841, bksge::hypot(T(  2), T(  2)), error);
	EXPECT_NEAR(  2.82842712474619009760337744841, bksge::hypot(T(  2), T( -2)), error);
	EXPECT_NEAR( 99.02019995940222297244309999586, bksge::hypot(T(  2), T( 99)), error);
	EXPECT_NEAR( 99.02019995940222297244309999586, bksge::hypot(T(  2), T(-99)), error);
	EXPECT_NEAR(  2.00000000000000000000000000000, bksge::hypot(T( -2), T(  0)), error);
	EXPECT_NEAR(  2.23606797749978969640917366873, bksge::hypot(T( -2), T(  1)), error);
	EXPECT_NEAR(  2.23606797749978969640917366873, bksge::hypot(T( -2), T( -1)), error);
	EXPECT_NEAR(  2.82842712474619009760337744841, bksge::hypot(T( -2), T(  2)), error);
	EXPECT_NEAR(  2.82842712474619009760337744841, bksge::hypot(T( -2), T( -2)), error);
	EXPECT_NEAR( 99.02019995940222297244309999586, bksge::hypot(T( -2), T( 99)), error);
	EXPECT_NEAR( 99.02019995940222297244309999586, bksge::hypot(T( -2), T(-99)), error);
	EXPECT_NEAR( 99.00000000000000000000000000000, bksge::hypot(T( 99), T(  0)), error);
	EXPECT_NEAR( 99.00505037623080771359834335305, bksge::hypot(T( 99), T(  1)), error);
	EXPECT_NEAR( 99.00505037623080771359834335305, bksge::hypot(T( 99), T( -1)), error);
	EXPECT_NEAR( 99.02019995940222297244309999586, bksge::hypot(T( 99), T(  2)), error);
	EXPECT_NEAR( 99.02019995940222297244309999586, bksge::hypot(T( 99), T( -2)), error);
	EXPECT_NEAR(140.00714267493640983136718369676, bksge::hypot(T( 99), T( 99)), error);
	EXPECT_NEAR(140.00714267493640983136718369676, bksge::hypot(T( 99), T(-99)), error);
	EXPECT_NEAR( 99.00000000000000000000000000000, bksge::hypot(T(-99), T(  0)), error);
	EXPECT_NEAR( 99.00505037623080771359834335305, bksge::hypot(T(-99), T(  1)), error);
	EXPECT_NEAR( 99.00505037623080771359834335305, bksge::hypot(T(-99), T( -1)), error);
	EXPECT_NEAR( 99.02019995940222297244309999586, bksge::hypot(T(-99), T(  2)), error);
	EXPECT_NEAR( 99.02019995940222297244309999586, bksge::hypot(T(-99), T( -2)), error);
	EXPECT_NEAR(140.00714267493640983136718369676, bksge::hypot(T(-99), T( 99)), error);
	EXPECT_NEAR(140.00714267493640983136718369676, bksge::hypot(T(-99), T(-99)), error);
}

template <typename T>
void Hypot3TestFloat(double error)
{
	EXPECT_NEAR(0.0,                         (double)bksge::hypot(T( 0.0), T( 0.0), T( 0.0)), error);
	EXPECT_NEAR((double)bksge::sqrt(T(2.0)), (double)bksge::hypot(T( 0.0), T( 1.0), T( 1.0)), error);
	EXPECT_NEAR((double)bksge::sqrt(T(2.0)), (double)bksge::hypot(T( 0.0), T( 1.0), T(-1.0)), error);
	EXPECT_NEAR((double)bksge::sqrt(T(3.0)), (double)bksge::hypot(T( 1.0), T( 1.0), T( 1.0)), error);
	EXPECT_NEAR((double)bksge::sqrt(T(3.0)), (double)bksge::hypot(T(-1.0), T(-1.0), T( 1.0)), error);
	EXPECT_NEAR(3.0,                         (double)bksge::hypot(T( 1.0), T( 2.0), T( 2.0)), error);
	EXPECT_NEAR(7.0,                         (double)bksge::hypot(T( 2.0), T( 3.0), T( 6.0)), error);
	EXPECT_NEAR(9.0,                         (double)bksge::hypot(T( 1.0), T( 4.0), T( 8.0)), error);
	EXPECT_NEAR(9.0,                         (double)bksge::hypot(T( 4.0), T( 4.0), T( 7.0)), error);
	EXPECT_NEAR(9.0,                         (double)bksge::hypot(T(-4.0), T(-4.0), T(-7.0)), error);
	EXPECT_NEAR(29.0,                        (double)bksge::hypot(T(12.0), T(16.0), T(21.0)), error*1e1);
	EXPECT_NEAR(1e8,                         (double)bksge::hypot(T(1e8),  T( 1.0), T(1e-8)), error);
	EXPECT_NEAR(0.01000099995,               (double)bksge::hypot(T(1e-2), T(1e-4), T(1e-4)), error);
	EXPECT_NEAR(371955077.2902952,           (double)bksge::hypot(T(214748364), T(214748364), T(214748364)), error*1e7);

	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(+inf, +inf, +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(+inf, +inf, -inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(+inf, +inf, T(1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(+inf, +inf, nan));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(+inf, -inf, +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(+inf, -inf, -inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(+inf, -inf, T(1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(+inf, -inf, nan));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(+inf, T(1), +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(+inf, T(1), -inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(+inf, T(1), T(1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(+inf, T(1), nan));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(+inf, nan,  +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(+inf, nan,  -inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(+inf, nan,  T(1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(+inf, nan,  nan));

	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(-inf, +inf, +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(-inf, +inf, -inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(-inf, +inf, T(1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(-inf, +inf, nan));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(-inf, -inf, +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(-inf, -inf, -inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(-inf, -inf, T(1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(-inf, -inf, nan));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(-inf, T(1), +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(-inf, T(1), -inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(-inf, T(1), T(1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(-inf, T(1), nan));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(-inf, nan,  +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(-inf, nan,  -inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(-inf, nan,  T(1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::hypot(-inf, nan,  nan));

	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(T(1), +inf, +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(T(1), +inf, -inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(T(1), +inf, T(1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(T(1), +inf, nan));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(T(1), -inf, +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(T(1), -inf, -inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(T(1), -inf, T(1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(T(1), -inf, nan));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(T(1), T(1), +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(T(1), T(1), -inf));
//	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(T(1), T(1), T(1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::hypot(T(1), T(1), nan)));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(T(1), nan,  +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(T(1), nan,  -inf));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::hypot(T(1), nan,  T(1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::hypot(T(1), nan,  nan)));

	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(nan, +inf, +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(nan, +inf, -inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(nan, +inf, T(1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(nan, +inf, nan));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(nan, -inf, +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(nan, -inf, -inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(nan, -inf, T(1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(nan, -inf, nan));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(nan, T(1), +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(nan, T(1), -inf));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::hypot(nan, T(1), T(1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::hypot(nan, T(1), nan)));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(nan, nan,  +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf,          bksge::hypot(nan, nan,  -inf));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::hypot(nan, nan,  T(1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::hypot(nan, nan,  nan)));
}

template <typename T>
void Hypot3TestInteger(void)
{
	BKSGE_CONSTEXPR double error = 1e-12;

	BKSGE_CONSTEXPR auto max = bksge::numeric_limits<T>::max();

	EXPECT_NEAR(0.0,              bksge::hypot(T( 0), T( 0), T( 0)), error);
	EXPECT_NEAR(bksge::sqrt(2.0), bksge::hypot(T( 1), T( 0), T( 1)), error);
	EXPECT_NEAR(bksge::sqrt(3.0), bksge::hypot(T(-1), T(-1), T(-1)), error);
	EXPECT_NEAR(7.0,              bksge::hypot(T( 2), T( 3), T( 6)), error);
	EXPECT_NEAR((double)max,      bksge::hypot(T( 0), T( 0), max),   error);
	EXPECT_NEAR((double)max,      bksge::hypot(T( 0), max,   T( 0)), error);
	EXPECT_NEAR((double)max,      bksge::hypot(max,   T( 0), T( 0)), error);
}

GTEST_TEST(CMathTest, HypotTest)
{
	HypotTestFloat<float>      (1e-6);
	HypotTestFloat<double>     (1e-12);
	HypotTestFloat<long double>(1e-12);

	HypotTestInteger<short>();
	HypotTestInteger<int>();
	HypotTestInteger<long>();
	HypotTestInteger<long long>();

	Hypot3TestFloat<float>      (1e-6);
	Hypot3TestFloat<double>     (1e-12);
	Hypot3TestFloat<long double>(1e-12);

	Hypot3TestInteger<short>();
	Hypot3TestInteger<int>();
	Hypot3TestInteger<long>();
	Hypot3TestInteger<long long>();
}

}	// namespace hypot_test

}	// namespace bksge_cmath_test
