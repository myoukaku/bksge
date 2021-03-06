﻿/**
 *	@file	unit_test_fnd_cmath_step.cpp
 *
 *	@brief	step のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/step.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace step_test
{

static_assert(bksge::is_same<float,       decltype(bksge::step(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::step(0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::step(0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::step(0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::step(0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::step(0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::step(0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::step(0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::step(0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::step(0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::step(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::step(0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::step(0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::step(0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::step(0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::step(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void StepTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf1 = std::numeric_limits<T1>::infinity();
	BKSGE_CONSTEXPR auto inf2 = std::numeric_limits<T2>::infinity();
	BKSGE_CONSTEXPR auto eps2 = std::numeric_limits<T2>::epsilon();

	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::step(T1(0.0), T2( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::step(T1(0.0), T2(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::step(T1(0.0), T2( 1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::step(T1(0.0), T2(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::step(T1(0.0), T2( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::step(T1(0.0), -eps2));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::step(T1(0.0),  eps2));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::step(T1(0.0), -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::step(T1(0.0),  inf2));

	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::step(T1(10.0), T2( 9.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::step(T1(10.0), T2(10.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::step(T1(10.0), T2(11.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::step(T1(10.0), -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::step(T1(10.0),  inf2));

	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::step( inf1,  inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::step( inf1, -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::step(-inf1,  inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::step(-inf1, -inf2));

	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::step(nan1,    T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::step(T1(0.0), nan2));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::step(nan1,    nan2));
}

template <typename T1, typename T2>
void StepTestInteger(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::step(T1(0), T2(-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::step(T1(0), T2( 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::step(T1(0), T2( 1)));

	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::step(T1(20), T2(19)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::step(T1(20), T2(20)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::step(T1(20), T2(21)));

	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::step(T1(-30), T2(-29)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::step(T1(-30), T2(-30)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::step(T1(-30), T2(-31)));
}

GTEST_TEST(CMathTest, StepTest)
{
	StepTestFloat<float,       float>      ();
//	StepTestFloat<float,       double>     ();
	StepTestFloat<float,       long double>();
//	StepTestFloat<double,      float>      ();
	StepTestFloat<double,      double>     ();
//	StepTestFloat<double,      long double>();
	StepTestFloat<long double, float>      ();
//	StepTestFloat<long double, double>     ();
	StepTestFloat<long double, long double>();

//	StepTestInteger<int,         int>();
	StepTestInteger<int,         float>();
//	StepTestInteger<int,         double>();
	StepTestInteger<int,         long double>();
//	StepTestInteger<float,       int>();
	StepTestInteger<double,      int>();
//	StepTestInteger<long double, int>();
}

}	// namespace step_test

}	// namespace bksge_cmath_test
