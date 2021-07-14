/**
 *	@file	unit_test_fnd_cmath_tgamma.cpp
 *
 *	@brief	tgamma のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/tgamma.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace tgamma_test
{

static_assert(bksge::is_same<float,       decltype(bksge::tgamma(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::tgammaf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::tgamma(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::tgamma(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::tgamma(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::tgammal(0.0l))>::value, "");

template <typename T>
void TgammaTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR( 1.77245385090551602729, (double)bksge::tgamma(T( 0.5)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR( 1.00000000000000000000, (double)bksge::tgamma(T( 1.0)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR( 0.88622692545275801365, (double)bksge::tgamma(T( 1.5)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR( 1.00000000000000000000, (double)bksge::tgamma(T( 2.0)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR( 1.32934038817913702047, (double)bksge::tgamma(T( 2.5)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR( 2.00000000000000000000, (double)bksge::tgamma(T( 3.0)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR( 3.32335097044784255118, (double)bksge::tgamma(T( 3.5)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR( 6.00000000000000000000, (double)bksge::tgamma(T( 4.0)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(11.63172839656744892914, (double)bksge::tgamma(T( 4.5)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(24.00000000000000000000, (double)bksge::tgamma(T( 5.0)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(-3.54490770181103205459, (double)bksge::tgamma(T(-0.5)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR( 2.36327180120735470306, (double)bksge::tgamma(T(-1.5)), error);
	/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(-0.94530872048294188123, (double)bksge::tgamma(T(-2.5)), error);

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isinf(bksge::tgamma(T(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isinf(bksge::tgamma(T(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::tgamma(T(-1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::tgamma(T(-2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::tgamma(T(-3.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::tgamma(T(-4.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::tgamma(T(-5.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isinf(bksge::tgamma(+inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::tgamma(-inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::tgamma(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::tgamma(-nan)));
}

template <typename T>
void TgammaTestSignedInt(void)
{
	/*BKSGE_CONSTEXPR_*/EXPECT_EQ( 1, bksge::tgamma(T( 1)));
	/*BKSGE_CONSTEXPR_*/EXPECT_EQ( 1, bksge::tgamma(T( 2)));
	/*BKSGE_CONSTEXPR_*/EXPECT_EQ( 2, bksge::tgamma(T( 3)));
	/*BKSGE_CONSTEXPR_*/EXPECT_EQ( 6, bksge::tgamma(T( 4)));
	/*BKSGE_CONSTEXPR_*/EXPECT_EQ(24, bksge::tgamma(T( 5)));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isinf(bksge::tgamma(T( 0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isinf(bksge::tgamma(T( 0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::tgamma(T(-1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::tgamma(T(-2))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::tgamma(T(-3))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::tgamma(T(-4))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::tgamma(T(-5))));
}

template <typename T>
void TgammaTestUnsignedInt(void)
{
	/*BKSGE_CONSTEXPR_*/EXPECT_EQ(  1, bksge::tgamma(T( 1)));
	/*BKSGE_CONSTEXPR_*/EXPECT_EQ(  1, bksge::tgamma(T( 2)));
	/*BKSGE_CONSTEXPR_*/EXPECT_EQ(  2, bksge::tgamma(T( 3)));
	/*BKSGE_CONSTEXPR_*/EXPECT_EQ(  6, bksge::tgamma(T( 4)));
	/*BKSGE_CONSTEXPR_*/EXPECT_EQ( 24, bksge::tgamma(T( 5)));
	/*BKSGE_CONSTEXPR_*/EXPECT_EQ(120, bksge::tgamma(T( 6)));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isinf(bksge::tgamma(T( 0))));
}

GTEST_TEST(CMathTest, TgammaTest)
{
	TgammaTestFloat<float>(0.00001);
	TgammaTestFloat<double>(0.000000000001);
	TgammaTestFloat<long double>(0.000000000001);

//	TgammaTestSignedInt<int>();
	TgammaTestSignedInt<signed char>();
//	TgammaTestSignedInt<short>();
	TgammaTestSignedInt<long>();
//	TgammaTestSignedInt<long long>();

	TgammaTestUnsignedInt<unsigned int>();
//	TgammaTestUnsignedInt<unsigned char>();
	TgammaTestUnsignedInt<unsigned short>();
//	TgammaTestUnsignedInt<unsigned long>();
	TgammaTestUnsignedInt<unsigned long long>();
}

}	// namespace tgamma_test

}	// namespace bksge_cmath_test
