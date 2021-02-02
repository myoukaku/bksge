/**
 *	@file	unit_test_fnd_cmath_isless.cpp
 *
 *	@brief	isless のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/isless.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace isless_test
{

static_assert(bksge::is_same<bool, decltype(bksge::isless(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isless(0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isless(0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isless(0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isless(0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isless(0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isless(0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isless(0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isless(0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isless(0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isless(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isless(0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isless(0   , 0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isless(0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isless(0   , 0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isless(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void IsLessTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan1 = bksge::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2 = bksge::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf1 = bksge::numeric_limits<T1>::infinity();
	BKSGE_CONSTEXPR auto inf2 = bksge::numeric_limits<T2>::infinity();
	BKSGE_CONSTEXPR auto min1 = bksge::numeric_limits<T1>::min();
	BKSGE_CONSTEXPR auto min2 = bksge::numeric_limits<T2>::min();
	BKSGE_CONSTEXPR auto max1 = bksge::numeric_limits<T1>::max();
	BKSGE_CONSTEXPR auto max2 = bksge::numeric_limits<T2>::max();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(T1(0.0), T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(T1(1.0), T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isless(T1(0.0), T2(1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(T1(1.0), T2(1.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isless(T1(0.0), inf2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isless(T1(0.0), min2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isless(T1(0.0), max2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(T1(0.0), nan2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(inf1,    T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(inf1,    inf2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(inf1,    min2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(inf1,    max2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(inf1,    nan2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(min1,    T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isless(min1,    inf2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isless(min1,    max2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(min1,    nan2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(max1,    T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isless(max1,    inf2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(max1,    min2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(max1,    nan2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(nan1,    T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(nan1,    inf2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(nan1,    min2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(nan1,    max2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(nan1,    nan2));
}

template <typename T1, typename T2>
void IsLessTestInteger(void)
{
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(T1(0), T2(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(T1(1), T2(0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isless(T1(0), T2(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isless(T1(1), T2(1)));
}

GTEST_TEST(CMathTest, IsLessTest)
{
	IsLessTestFloat<float,       float>      ();
//	IsLessTestFloat<float,       double>     ();
	IsLessTestFloat<float,       long double>();
//	IsLessTestFloat<double,      float>      ();
	IsLessTestFloat<double,      double>     ();
//	IsLessTestFloat<double,      long double>();
	IsLessTestFloat<long double, float>      ();
//	IsLessTestFloat<long double, double>     ();
	IsLessTestFloat<long double, long double>();

//	IsLessTestInteger<int, int>();
	IsLessTestInteger<int, float>();
//	IsLessTestInteger<int, double>();
	IsLessTestInteger<int, long double>();
//	IsLessTestInteger<float, int>();
	IsLessTestInteger<double, int>();
//	IsLessTestInteger<long double, int>();
}

}	// namespace isless_test

}	// namespace bksge_cmath_test
