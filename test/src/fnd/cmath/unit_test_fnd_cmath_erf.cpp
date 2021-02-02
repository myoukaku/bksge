/**
 *	@file	unit_test_fnd_cmath_erf.cpp
 *
 *	@brief	erf のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/erf.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace erf_test
{

static_assert(bksge::is_same<float,       decltype(bksge::erf(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::erff(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::erf(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::erf(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::erf(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::erfl(0.0l))>::value, "");

template <typename T>
void ErfTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	BKSGE_CONSTEXPR_EXPECT_EQ(T( 1.0), bksge::erf(+inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-1.0), bksge::erf(-inf));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::erf(nan)));

	EXPECT_NEAR(-0.9953222650189527341621, (double)bksge::erf(T(-2.0)), error);
	EXPECT_NEAR(-0.8427007929497148693412, (double)bksge::erf(T(-1.0)), error);
	EXPECT_NEAR( 0.0,                      (double)bksge::erf(T( 0.0)), error);
	EXPECT_NEAR( 0.8427007929497148693412, (double)bksge::erf(T( 1.0)), error);
	EXPECT_NEAR( 0.9953222650189527341621, (double)bksge::erf(T( 2.0)), error);
}

template <typename T>
void ErfTestSignedInt(void)
{
	double const error = 0.000000000000001;

	EXPECT_NEAR(-0.9953222650189527341621, bksge::erf(T(-2)), error);
	EXPECT_NEAR(-0.8427007929497148693412, bksge::erf(T(-1)), error);
	EXPECT_NEAR( 0.0,                      bksge::erf(T( 0)), error);
	EXPECT_NEAR( 0.8427007929497148693412, bksge::erf(T( 1)), error);
	EXPECT_NEAR( 0.9953222650189527341621, bksge::erf(T( 2)), error);
}

template <typename T>
void ErfTestUnsignedInt(void)
{
	double const error = 0.000000000000001;

	EXPECT_NEAR( 0.0,                      bksge::erf(T( 0)), error);
	EXPECT_NEAR( 0.8427007929497148693412, bksge::erf(T( 1)), error);
	EXPECT_NEAR( 0.9953222650189527341621, bksge::erf(T( 2)), error);
	EXPECT_NEAR( 0.9999779095030014145586, bksge::erf(T( 3)), error);
	EXPECT_NEAR( 0.99999998458274209972,   bksge::erf(T( 4)), error);
}

GTEST_TEST(CMathTest, ErfTest)
{
	ErfTestFloat<float>      (0.0000001);
	ErfTestFloat<double>     (0.000000000000001);
	ErfTestFloat<long double>(0.000000000000001);

	ErfTestSignedInt<int>();
//	ErfTestSignedInt<signed char>();
	ErfTestSignedInt<short>();
//	ErfTestSignedInt<long>();
	ErfTestSignedInt<long long>();

//	ErfTestUnsignedInt<unsigned int>();
	ErfTestUnsignedInt<unsigned char>();
//	ErfTestUnsignedInt<unsigned short>();
	ErfTestUnsignedInt<unsigned long>();
//	ErfTestUnsignedInt<unsigned long long>();
}

}	// namespace erf_test

}	// namespace bksge_cmath_test
