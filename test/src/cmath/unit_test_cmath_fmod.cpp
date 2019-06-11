/**
 *	@file	unit_test_cmath_fmod.cpp
 *
 *	@brief	fmod のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/cmath/fmod.hpp>
#include <bksge/cmath/isnan.hpp>
#include <bksge/cmath/iszero.hpp>
#include <bksge/cmath/signbit.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_fmod_test
{

template <typename T1, typename T2>
void FmodTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf1 = std::numeric_limits<T1>::infinity();
	BKSGE_CONSTEXPR auto inf2 = std::numeric_limits<T2>::infinity();

	using R = bksge::float_promote_t<T1, T2>;

	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2.5), bksge::fmod(T1( 5.5), T2( 3.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2.5), bksge::fmod(T1(-5.5), T2( 3.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2.5), bksge::fmod(T1( 5.5), T2(-3.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2.5), bksge::fmod(T1(-5.5), T2(-3.0)));

	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.5), bksge::fmod(T1( 5.5), T2( 2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-0.5), bksge::fmod(T1(-5.5), T2( 2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.5), bksge::fmod(T1( 5.5), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-0.5), bksge::fmod(T1(-5.5), T2(-2.5)));

	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::fmod(T1( 7.5), T2( 2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-0.0), bksge::fmod(T1(-7.5), T2( 2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 0.0), bksge::fmod(T1( 7.5), T2(-2.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-0.0), bksge::fmod(T1(-7.5), T2(-2.5)));

	//If x is ±0 and y is not zero, ±0 is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::fmod(T1(+0.0), T2( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::fmod(T1(-0.0), T2( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::fmod(T1(+0.0), T2( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::fmod(T1(-0.0), T2( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::fmod(T1(+0.0), T2(-2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::fmod(T1(-0.0), T2(-2.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::fmod(T1(+0.0), T2(-2.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::fmod(T1(-0.0), T2(-2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::fmod(T1(+0.0), inf2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::fmod(T1(-0.0), inf2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::fmod(T1(+0.0), inf2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::fmod(T1(-0.0), inf2)));

	//If x is ±∞ and y is not NaN, NaN is returned and FE_INVALID is raised
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod( inf1, T2( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(-inf1, T2( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod( inf1, T2(-2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(-inf1, T2(-2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod( inf1, T2( 0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(-inf1, T2( 0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod( inf1, inf2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(-inf1, inf2)));

	//If y is ±0 and x is not NaN, NaN is returned and FE_INVALID is raised
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(T1( 1.0), T2(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(T1( 1.0), T2(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(T1(-2.0), T2(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(T1(-2.0), T2(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(T1( 0.0), T2(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(T1( 0.0), T2(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(inf1,     T2(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(inf1,     T2(-0.0))));

	//If y is ±∞ and x is finite, x is returned.
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 1.0), bksge::fmod(T1( 1.0), +inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 1.0), bksge::fmod(T1( 1.0), -inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2.0), bksge::fmod(T1(-2.0), +inf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2.0), bksge::fmod(T1(-2.0), -inf2));

	//If either argument is NaN, NaN is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(nan1, T2(1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(T1(1.0), nan2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::fmod(nan1, nan2)));
}

template <typename T1, typename T2>
void FmodTestInteger(void)
{
	using R = bksge::float_promote_t<T1, T2>;

	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2), bksge::fmod(T1( 5), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2), bksge::fmod(T1(-5), T2( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 2), bksge::fmod(T1( 5), T2(-3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-2), bksge::fmod(T1(-5), T2(-3)));

	BKSGE_CONSTEXPR_EXPECT_EQ(R( 3), bksge::fmod(T1( 7), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-3), bksge::fmod(T1(-7), T2( 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R( 3), bksge::fmod(T1( 7), T2(-4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(R(-3), bksge::fmod(T1(-7), T2(-4)));
}

GTEST_TEST(CMathTest, FmodTest)
{
//	FmodTestFloat<float,       float>      ();
	FmodTestFloat<float,       double>     ();
//	FmodTestFloat<float,       long double>();
	FmodTestFloat<double,      float>      ();
//	FmodTestFloat<double,      double>     ();
	FmodTestFloat<double,      long double>();
//	FmodTestFloat<long double, float>      ();
	FmodTestFloat<long double, double>     ();
//	FmodTestFloat<long double, long double>();

	FmodTestInteger<int,         int>();
//	FmodTestInteger<int,         float>();
	FmodTestInteger<int,         double>();
//	FmodTestInteger<int,         long double>();
	FmodTestInteger<float,       int>();
//	FmodTestInteger<double,      int>();
	FmodTestInteger<long double, int>();
}

}	// namespace bksge_cmath_fmod_test
