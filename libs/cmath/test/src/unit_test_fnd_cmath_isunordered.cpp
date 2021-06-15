/**
 *	@file	unit_test_fnd_cmath_isunordered.cpp
 *
 *	@brief	isunordered のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/isunordered.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace isunordered_test
{

static_assert(bksge::is_same<bool, decltype(bksge::isunordered(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isunordered(0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isunordered(0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isunordered(0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isunordered(0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isunordered(0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isunordered(0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isunordered(0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isunordered(0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isunordered(0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isunordered(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isunordered(0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isunordered(0   , 0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isunordered(0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isunordered(0   , 0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isunordered(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void IsUnorderedTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan1    = bksge::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2    = bksge::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf1    = bksge::numeric_limits<T1>::infinity();
	BKSGE_CONSTEXPR auto inf2    = bksge::numeric_limits<T2>::infinity();
	BKSGE_CONSTEXPR auto min1    = bksge::numeric_limits<T1>::min();
	BKSGE_CONSTEXPR auto min2    = bksge::numeric_limits<T2>::min();
	BKSGE_CONSTEXPR auto max1    = bksge::numeric_limits<T1>::max();
	BKSGE_CONSTEXPR auto max2    = bksge::numeric_limits<T2>::max();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(T1(0.0), T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(T1(0.0), inf2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(T1(0.0), min2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(T1(0.0), max2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isunordered(T1(0.0), nan2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(inf1,    T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(inf1,    inf2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(inf1,    min2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(inf1,    max2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isunordered(inf1,    nan2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(min1,    T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(min1,    inf2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(min1,    min2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(min1,    max2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isunordered(min1,    nan2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(max1,    T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(max1,    inf2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(max1,    min2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(max1,    max2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isunordered(max1,    nan2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isunordered(nan1,    T2(0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isunordered(nan1,    inf2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isunordered(nan1,    min2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isunordered(nan1,    max2));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isunordered(nan1,    nan2));
}

template <typename T1, typename T2>
void IsUnorderedTestInteger(void)
{
	BKSGE_CONSTEXPR auto min1    = bksge::numeric_limits<T1>::min();
	BKSGE_CONSTEXPR auto min2    = bksge::numeric_limits<T2>::min();
	BKSGE_CONSTEXPR auto max1    = bksge::numeric_limits<T1>::max();
	BKSGE_CONSTEXPR auto max2    = bksge::numeric_limits<T2>::max();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(T1(0),   T2(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(T1(0),   min2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(T1(0),   max2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(min1,    T2(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(min1,    min2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(min1,    max2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(max1,    T2(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(max1,    min2));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isunordered(max1,    max2));
}

GTEST_TEST(CMathTest, IsUnorderedTest)
{
	IsUnorderedTestFloat<float,       float>      ();
//	IsUnorderedTestFloat<float,       double>     ();
	IsUnorderedTestFloat<float,       long double>();
//	IsUnorderedTestFloat<double,      float>      ();
	IsUnorderedTestFloat<double,      double>     ();
//	IsUnorderedTestFloat<double,      long double>();
	IsUnorderedTestFloat<long double, float>      ();
//	IsUnorderedTestFloat<long double, double>     ();
	IsUnorderedTestFloat<long double, long double>();

//	IsUnorderedTestInteger<int, int>();
	IsUnorderedTestInteger<int, float>();
//	IsUnorderedTestInteger<int, double>();
	IsUnorderedTestInteger<int, long double>();
//	IsUnorderedTestInteger<float, int>();
	IsUnorderedTestInteger<double, int>();
//	IsUnorderedTestInteger<long double, int>();
}

}	// namespace isunordered_test

}	// namespace bksge_cmath_test
