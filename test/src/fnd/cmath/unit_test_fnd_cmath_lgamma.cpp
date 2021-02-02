/**
 *	@file	unit_test_fnd_cmath_lgamma.cpp
 *
 *	@brief	lgamma のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/lgamma.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace lgamma_test
{

static_assert(bksge::is_same<float,       decltype(bksge::lgamma(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::lgammaf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::lgamma(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::lgamma(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::lgamma(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::lgammal(0.0l))>::value, "");

template <typename T>
void LgammaTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR( 0.57236494292470008707, (double)bksge::lgamma(T( 0.5)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(-0.12078223763524522235, (double)bksge::lgamma(T( 1.5)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR( 0.28468287047291915963, (double)bksge::lgamma(T( 2.5)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR( 0.69314718055994530942, (double)bksge::lgamma(T( 3.0)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR( 1.79175946922805500081, (double)bksge::lgamma(T( 4.0)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR( 3.17805383034794561965, (double)bksge::lgamma(T( 5.0)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR( 1.26551212348464539649, (double)bksge::lgamma(T(-0.5)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR( 0.86004701537648101451, (double)bksge::lgamma(T(-1.5)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(-0.05624371649767405067, (double)bksge::lgamma(T(-2.5)), error);

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::iszero(bksge::lgamma(T( 1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::iszero(bksge::lgamma(T( 2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isinf (bksge::lgamma(T(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isinf (bksge::lgamma(T(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isinf (bksge::lgamma(T(-1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isinf (bksge::lgamma(T(-2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isinf (bksge::lgamma(inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan (bksge::lgamma(nan)));
}

template <typename T>
void LgammaTestSignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.0000001;

	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(0.69314718055994530942, (double)bksge::lgamma(T( 3)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(1.79175946922805500081, (double)bksge::lgamma(T( 4)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(3.17805383034794561965, (double)bksge::lgamma(T( 5)), error);

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isinf (bksge::lgamma(T( 0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::iszero(bksge::lgamma(T( 1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::iszero(bksge::lgamma(T( 2))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isinf (bksge::lgamma(T(-1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isinf (bksge::lgamma(T(-2))));
}

template <typename T>
void LgammaTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.0000001;

	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(0.69314718055994530942, (double)bksge::lgamma(T( 3)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(1.79175946922805500081, (double)bksge::lgamma(T( 4)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(3.17805383034794561965, (double)bksge::lgamma(T( 5)), error);

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isinf (bksge::lgamma(T( 0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::iszero(bksge::lgamma(T( 1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::iszero(bksge::lgamma(T( 2))));
}

GTEST_TEST(CMathTest, LgammaTest)
{
	LgammaTestFloat<float>(0.00001);
	LgammaTestFloat<double>(0.000000000001);
	LgammaTestFloat<long double>(0.000000000001);

	LgammaTestSignedInt<int>();
//	LgammaTestSignedInt<signed char>();
	LgammaTestSignedInt<short>();
//	LgammaTestSignedInt<long>();
	LgammaTestSignedInt<long long>();

//	LgammaTestUnsignedInt<unsigned int>();
	LgammaTestUnsignedInt<unsigned char>();
//	LgammaTestUnsignedInt<unsigned short>();
	LgammaTestUnsignedInt<unsigned long>();
//	LgammaTestUnsignedInt<unsigned long long>();
}

}	// namespace lgamma_test

}	// namespace bksge_cmath_test
