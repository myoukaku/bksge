/**
 *	@file	unit_test_fnd_cmath_remquo.cpp
 *
 *	@brief	remquo のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/remquo.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace remquo_test
{

static_assert(bksge::is_same<float,       decltype(bksge::remquo(0.0f, 0.0f, nullptr))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::remquof(0.0f, 0.0f, nullptr))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::remquo(0.0f, 0.0, nullptr))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::remquo(0.0f, 0.0l, nullptr))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::remquo(0.0f, 0, nullptr))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::remquo(0.0 , 0.0f, nullptr))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::remquo(0.0 , 0.0, nullptr))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::remquo(0.0 , 0.0l, nullptr))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::remquo(0.0 , 0, nullptr))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::remquo(0.0l, 0.0f, nullptr))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::remquo(0.0l, 0.0, nullptr))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::remquo(0.0l, 0.0l, nullptr))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::remquol(0.0l, 0.0l, nullptr))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::remquo(0.0l, 0, nullptr))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::remquo(0   , 0.0f, nullptr))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::remquo(0   , 0.0, nullptr))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::remquo(0   , 0.0l, nullptr))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::remquo(0   , 0, nullptr))>::value, "");

template <typename T1, typename T2, typename R>
inline bool RemquoTestImpl(R re_expect, int quo_expect, T1 x, T2 y)
{
	int quo;
	auto re = bksge::remquo(x, y, &quo);
	return re == re_expect && quo == quo_expect;
}

template <typename T1, typename T2>
void RemquoTestFloat(void)
{
	using R = bksge::float_promote_t<T1, T2>;

	BKSGE_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf1 = std::numeric_limits<T1>::infinity();
	BKSGE_CONSTEXPR auto inf2 = std::numeric_limits<T2>::infinity();

	EXPECT_TRUE(RemquoTestImpl(R( 1.0), 2, T1( 7.0), T2(3)));
	EXPECT_TRUE(RemquoTestImpl(R( 1.5), 2, T1( 7.5), T2(3)));
	EXPECT_TRUE(RemquoTestImpl(R(-1.0), 3, T1( 8.0), T2(3)));
	EXPECT_TRUE(RemquoTestImpl(R(-0.5), 3, T1( 8.5), T2(3)));
	EXPECT_TRUE(RemquoTestImpl(R( 0.0), 3, T1( 9.0), T2(3)));
	EXPECT_TRUE(RemquoTestImpl(R( 0.5), 3, T1( 9.5), T2(3)));
	EXPECT_TRUE(RemquoTestImpl(R( 1.0), 3, T1(10.0), T2(3)));
	EXPECT_TRUE(RemquoTestImpl(R(-1.5), 4, T1(10.5), T2(3)));

	EXPECT_TRUE(RemquoTestImpl(R( 1.0), -2, T1( 7.0), T2(-3)));
	EXPECT_TRUE(RemquoTestImpl(R( 1.5), -2, T1( 7.5), T2(-3)));
	EXPECT_TRUE(RemquoTestImpl(R(-1.0), -3, T1( 8.0), T2(-3)));
	EXPECT_TRUE(RemquoTestImpl(R(-0.5), -3, T1( 8.5), T2(-3)));
	EXPECT_TRUE(RemquoTestImpl(R( 0.0), -3, T1( 9.0), T2(-3)));
	EXPECT_TRUE(RemquoTestImpl(R( 0.5), -3, T1( 9.5), T2(-3)));
	EXPECT_TRUE(RemquoTestImpl(R( 1.0), -3, T1(10.0), T2(-3)));
	EXPECT_TRUE(RemquoTestImpl(R(-1.5), -4, T1(10.5), T2(-3)));

	EXPECT_TRUE(RemquoTestImpl(R( 0.5), -3, T1(- 7.0), T2(2.5)));
	EXPECT_TRUE(RemquoTestImpl(R( 0.0), -3, T1(- 7.5), T2(2.5)));
	EXPECT_TRUE(RemquoTestImpl(R(-0.5), -3, T1(- 8.0), T2(2.5)));
	EXPECT_TRUE(RemquoTestImpl(R(-1.0), -3, T1(- 8.5), T2(2.5)));
	EXPECT_TRUE(RemquoTestImpl(R( 1.0), -4, T1(- 9.0), T2(2.5)));
	EXPECT_TRUE(RemquoTestImpl(R( 0.5), -4, T1(- 9.5), T2(2.5)));
	EXPECT_TRUE(RemquoTestImpl(R( 0.0), -4, T1(-10.0), T2(2.5)));
	EXPECT_TRUE(RemquoTestImpl(R(-0.5), -4, T1(-10.5), T2(2.5)));

	EXPECT_TRUE(RemquoTestImpl(R( 0.5), 3, T1(- 7.0), T2(-2.5)));
	EXPECT_TRUE(RemquoTestImpl(R( 0.0), 3, T1(- 7.5), T2(-2.5)));
	EXPECT_TRUE(RemquoTestImpl(R(-0.5), 3, T1(- 8.0), T2(-2.5)));
	EXPECT_TRUE(RemquoTestImpl(R(-1.0), 3, T1(- 8.5), T2(-2.5)));
	EXPECT_TRUE(RemquoTestImpl(R( 1.0), 4, T1(- 9.0), T2(-2.5)));
	EXPECT_TRUE(RemquoTestImpl(R( 0.5), 4, T1(- 9.5), T2(-2.5)));
	EXPECT_TRUE(RemquoTestImpl(R( 0.0), 4, T1(-10.0), T2(-2.5)));
	EXPECT_TRUE(RemquoTestImpl(R(-0.5), 4, T1(-10.5), T2(-2.5)));

	int quo;

	//If x is ±∞ and y is not NaN, NaN is returned and FE_INVALID is raised
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo( inf1, T2( 1.0), &quo)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo(-inf1, T2( 1.0), &quo)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo( inf1, T2(-2.0), &quo)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo(-inf1, T2(-2.0), &quo)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo( inf1, T2( 0.0), &quo)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo(-inf1, T2( 0.0), &quo)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo( inf1, inf2, &quo)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo(-inf1, inf2, &quo)));

	//If y is ±0 and x is not NaN, NaN is returned and FE_INVALID is raised
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo(T1( 1.0), T2(+0.0), &quo)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo(T1( 1.0), T2(-0.0), &quo)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo(T1(-2.0), T2(+0.0), &quo)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo(T1(-2.0), T2(-0.0), &quo)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo(T1( 0.0), T2(+0.0), &quo)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo(T1( 0.0), T2(-0.0), &quo)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo(inf1,     T2(+0.0), &quo)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo(inf1,     T2(-0.0), &quo)));

	//If either argument is NaN, NaN is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo(nan1, T2(1.0), &quo)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo(nan1, T2(0.0), &quo)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo(T1(1.0), nan2, &quo)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo(inf1, nan2, &quo)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::remquo(nan1, nan2, &quo)));
}

template <typename T1, typename T2>
void RemquoTestInteger(void)
{
	using R = bksge::float_promote_t<T1, T2>;

	EXPECT_TRUE(RemquoTestImpl(R(-1), 2, T1( 5), T2( 3)));
	EXPECT_TRUE(RemquoTestImpl(R( 1),-2, T1(-5), T2( 3)));
	EXPECT_TRUE(RemquoTestImpl(R(-1),-2, T1( 5), T2(-3)));
	EXPECT_TRUE(RemquoTestImpl(R( 1), 2, T1(-5), T2(-3)));

	EXPECT_TRUE(RemquoTestImpl(R( 1), 2, T1( 5), T2( 2)));
	EXPECT_TRUE(RemquoTestImpl(R(-1),-2, T1(-5), T2( 2)));
	EXPECT_TRUE(RemquoTestImpl(R( 1),-2, T1( 5), T2(-2)));
	EXPECT_TRUE(RemquoTestImpl(R(-1), 2, T1(-5), T2(-2)));
}

GTEST_TEST(CMathTest, RemquoTest)
{
	RemquoTestFloat<float, float>();
	RemquoTestFloat<float, double>();
	RemquoTestFloat<double, double>();
	RemquoTestFloat<double, long double>();
	RemquoTestFloat<long double, long double>();
	RemquoTestFloat<long double, float>();

	RemquoTestInteger<int, int>();
	RemquoTestInteger<int, float>();
	RemquoTestInteger<int, double>();
	RemquoTestInteger<int, long long>();
	RemquoTestInteger<double, long long>();
	RemquoTestInteger<long double, long long>();
}

}	// namespace remquo_test

}	// namespace bksge_cmath_test
