/**
 *	@file	unit_test_fnd_cmath_isgreater.cpp
 *
 *	@brief	isgreater のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/isgreater.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace isgreater_test
{

static_assert(bksge::is_same<bool, decltype(bksge::isgreater(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isgreater(0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isgreater(0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isgreater(0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isgreater(0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isgreater(0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isgreater(0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isgreater(0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isgreater(0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isgreater(0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isgreater(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isgreater(0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isgreater(0   , 0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isgreater(0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isgreater(0   , 0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isgreater(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void IsGreaterTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf1 = std::numeric_limits<T1>::infinity();
	BKSGE_CONSTEXPR auto inf2 = std::numeric_limits<T2>::infinity();
	BKSGE_CONSTEXPR auto min1 = std::numeric_limits<T1>::min();
	BKSGE_CONSTEXPR auto min2 = std::numeric_limits<T2>::min();
	BKSGE_CONSTEXPR auto max1 = std::numeric_limits<T1>::max();
	BKSGE_CONSTEXPR auto max2 = std::numeric_limits<T2>::max();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(T1(0.0), T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isgreater(T1(1.0), T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(T1(0.0), T2(1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(T1(1.0), T2(1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(T1(0.0), inf2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(T1(0.0), min2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(T1(0.0), max2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(T1(0.0), nan2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isgreater(inf1,    T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(inf1,    inf2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isgreater(inf1,    min2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isgreater(inf1,    max2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(inf1,    nan2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isgreater(min1,    T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(min1,    inf2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(min1,    max2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(min1,    nan2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isgreater(max1,    T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(max1,    inf2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isgreater(max1,    min2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(max1,    nan2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(nan1,    T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(nan1,    inf2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(nan1,    min2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(nan1,    max2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(nan1,    nan2));
}

template <typename T1, typename T2>
void IsGreaterTestInteger(void)
{
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(T1(0), T2(0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isgreater(T1(1), T2(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(T1(0), T2(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isgreater(T1(1), T2(1)));
}

GTEST_TEST(CMathTest, IsGreaterTest)
{
//	IsGreaterTestFloat<float,       float>      ();
	IsGreaterTestFloat<float,       double>     ();
//	IsGreaterTestFloat<float,       long double>();
	IsGreaterTestFloat<double,      float>      ();
//	IsGreaterTestFloat<double,      double>     ();
	IsGreaterTestFloat<double,      long double>();
//	IsGreaterTestFloat<long double, float>      ();
	IsGreaterTestFloat<long double, double>     ();
//	IsGreaterTestFloat<long double, long double>();

	IsGreaterTestInteger<int, int>();
//	IsGreaterTestInteger<int, float>();
	IsGreaterTestInteger<int, double>();
//	IsGreaterTestInteger<int, long double>();
	IsGreaterTestInteger<float, int>();
//	IsGreaterTestInteger<double, int>();
	IsGreaterTestInteger<long double, int>();
}

}	// namespace isgreater_test

}	// namespace bksge_cmath_test
