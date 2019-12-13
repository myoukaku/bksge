/**
 *	@file	unit_test_fnd_cmath_degrees_to_radians.cpp
 *
 *	@brief	degrees_to_radians のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/degrees_to_radians.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace degrees_to_radians_test
{

template <typename T>
void DegreesToRadiansTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR double error = 0.000001;

	BKSGE_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, (double)bksge::degrees_to_radians(T(   0.0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 0.0087266462599, (double)bksge::degrees_to_radians(T(   0.5)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 0.0174532925199, (double)bksge::degrees_to_radians(T(   1.0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 0.0261799387799, (double)bksge::degrees_to_radians(T(   1.5)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 0.7853981633974, (double)bksge::degrees_to_radians(T(  45.0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 1.5707963267949, (double)bksge::degrees_to_radians(T(  90.0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 3.1415926535898, (double)bksge::degrees_to_radians(T( 180.0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 6.2831853071796, (double)bksge::degrees_to_radians(T( 360.0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(12.5663706143591, (double)bksge::degrees_to_radians(T( 720.0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(-0.7853981633974, (double)bksge::degrees_to_radians(T( -45.0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(-1.5707963267949, (double)bksge::degrees_to_radians(T( -90.0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(-3.1415926535898, (double)bksge::degrees_to_radians(T(-180.0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(-6.2831853071796, (double)bksge::degrees_to_radians(T(-360.0)), error);

	BKSGE_CONSTEXPR_EXPECT_EQ( inf, bksge::degrees_to_radians(+inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::degrees_to_radians(-inf));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isinf  (bksge::degrees_to_radians(+inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isinf  (bksge::degrees_to_radians(-inf)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::degrees_to_radians(+inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::signbit(bksge::degrees_to_radians(-inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan  (bksge::degrees_to_radians(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan  (bksge::degrees_to_radians(-nan)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::degrees_to_radians(+nan)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::degrees_to_radians(-nan)));
}

template <typename T>
void DegreesToRadiansTestSignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.00000000001;

	BKSGE_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, bksge::degrees_to_radians(T(   0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 0.0174532925199, bksge::degrees_to_radians(T(   1)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 0.0349065850398, bksge::degrees_to_radians(T(   2)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 0.0523598775598, bksge::degrees_to_radians(T(   3)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 0.7853981633974, bksge::degrees_to_radians(T(  45)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 1.5707963267949, bksge::degrees_to_radians(T(  90)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(-0.0174532925199, bksge::degrees_to_radians(T(  -1)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(-0.0349065850398, bksge::degrees_to_radians(T(  -2)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(-0.0523598775598, bksge::degrees_to_radians(T(  -3)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(-0.7853981633974, bksge::degrees_to_radians(T( -45)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(-1.5707963267949, bksge::degrees_to_radians(T( -90)), error);
}

template <typename T>
void DegreesToRadiansTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.00000000001;

	BKSGE_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, bksge::degrees_to_radians(T(   0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 0.0174532925199, bksge::degrees_to_radians(T(   1)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 0.0349065850398, bksge::degrees_to_radians(T(   2)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 0.0523598775598, bksge::degrees_to_radians(T(   3)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 0.7853981633974, bksge::degrees_to_radians(T(  45)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 1.5707963267949, bksge::degrees_to_radians(T(  90)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 3.1415926535898, bksge::degrees_to_radians(T( 180)), error);
}

GTEST_TEST(CMathTest, DegreesToRadiansTest)
{
	DegreesToRadiansTestFloat<float>();
	DegreesToRadiansTestFloat<double>();
	DegreesToRadiansTestFloat<long double>();

	DegreesToRadiansTestSignedInt<int>();
	DegreesToRadiansTestSignedInt<signed char>();
//	DegreesToRadiansTestSignedInt<short>();
	DegreesToRadiansTestSignedInt<long>();
//	DegreesToRadiansTestSignedInt<long long>();

	DegreesToRadiansTestUnsignedInt<unsigned int>();
//	DegreesToRadiansTestUnsignedInt<unsigned char>();
	DegreesToRadiansTestUnsignedInt<unsigned short>();
//	DegreesToRadiansTestUnsignedInt<unsigned long>();
	DegreesToRadiansTestUnsignedInt<unsigned long long>();
}

}	// namespace degrees_to_radians_test

}	// namespace bksge_cmath_test
