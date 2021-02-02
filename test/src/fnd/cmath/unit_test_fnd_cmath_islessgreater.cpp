/**
 *	@file	unit_test_fnd_cmath_islessgreater.cpp
 *
 *	@brief	islessgreater のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/islessgreater.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace islessgreater_test
{

static_assert(bksge::is_same<bool, decltype(bksge::islessgreater(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::islessgreater(0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::islessgreater(0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::islessgreater(0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::islessgreater(0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::islessgreater(0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::islessgreater(0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::islessgreater(0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::islessgreater(0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::islessgreater(0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::islessgreater(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::islessgreater(0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::islessgreater(0   , 0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::islessgreater(0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::islessgreater(0   , 0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::islessgreater(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void IsLessGreaterTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan1 = bksge::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2 = bksge::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf1 = bksge::numeric_limits<T1>::infinity();
	BKSGE_CONSTEXPR auto inf2 = bksge::numeric_limits<T2>::infinity();
	BKSGE_CONSTEXPR auto min1 = bksge::numeric_limits<T1>::min();
	BKSGE_CONSTEXPR auto min2 = bksge::numeric_limits<T2>::min();
	BKSGE_CONSTEXPR auto max1 = bksge::numeric_limits<T1>::max();
	BKSGE_CONSTEXPR auto max2 = bksge::numeric_limits<T2>::max();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::islessgreater(T1(0.0), T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::islessgreater(T1(1.0), T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::islessgreater(T1(0.0), T2(1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::islessgreater(T1(1.0), T2(1.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::islessgreater(T1(0.0), inf2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::islessgreater(T1(0.0), min2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::islessgreater(T1(0.0), max2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::islessgreater(T1(0.0), nan2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::islessgreater(inf1,    T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::islessgreater(inf1,    inf2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::islessgreater(inf1,    min2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::islessgreater(inf1,    max2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::islessgreater(inf1,    nan2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::islessgreater(min1,    T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::islessgreater(min1,    inf2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::islessgreater(min1,    max2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::islessgreater(min1,    nan2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::islessgreater(max1,    T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::islessgreater(max1,    inf2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::islessgreater(max1,    min2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::islessgreater(max1,    nan2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::islessgreater(nan1,    T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::islessgreater(nan1,    inf2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::islessgreater(nan1,    min2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::islessgreater(nan1,    max2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::islessgreater(nan1,    nan2));
}

template <typename T1, typename T2>
void IsLessGreaterTestInteger(void)
{
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::islessgreater(T1(0), T2(0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::islessgreater(T1(1), T2(0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::islessgreater(T1(0), T2(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::islessgreater(T1(1), T2(1)));
}

GTEST_TEST(CMathTest, IsLessGreaterTest)
{
	IsLessGreaterTestFloat<float,       float>      ();
//	IsLessGreaterTestFloat<float,       double>     ();
	IsLessGreaterTestFloat<float,       long double>();
//	IsLessGreaterTestFloat<double,      float>      ();
	IsLessGreaterTestFloat<double,      double>     ();
//	IsLessGreaterTestFloat<double,      long double>();
	IsLessGreaterTestFloat<long double, float>      ();
//	IsLessGreaterTestFloat<long double, double>     ();
	IsLessGreaterTestFloat<long double, long double>();

//	IsLessGreaterTestInteger<int, int>();
	IsLessGreaterTestInteger<int, float>();
//	IsLessGreaterTestInteger<int, double>();
	IsLessGreaterTestInteger<int, long double>();
//	IsLessGreaterTestInteger<float, int>();
	IsLessGreaterTestInteger<double, int>();
//	IsLessGreaterTestInteger<long double, int>();
}

}	// namespace islessgreater_test

}	// namespace bksge_cmath_test
