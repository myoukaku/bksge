/**
 *	@file	unit_test_fnd_cmath_radians_to_degrees.cpp
 *
 *	@brief	radians_to_degrees のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/radians_to_degrees.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/cmath/constants.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace radians_to_degrees_test
{

template <typename T>
void RadiansToDegreesTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto pi  = bksge::pi<T>();
	
	BKSGE_CONSTEXPR_EXPECT_EQ(T(   0.0), bksge::radians_to_degrees(pi * T( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(  90.0), bksge::radians_to_degrees(pi * T( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 180.0), bksge::radians_to_degrees(pi * T( 1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 270.0), bksge::radians_to_degrees(pi * T( 1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 360.0), bksge::radians_to_degrees(pi * T( 2.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 540.0), bksge::radians_to_degrees(pi * T( 3.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 720.0), bksge::radians_to_degrees(pi * T( 4.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( -90.0), bksge::radians_to_degrees(pi * T(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-180.0), bksge::radians_to_degrees(pi * T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-270.0), bksge::radians_to_degrees(pi * T(-1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-360.0), bksge::radians_to_degrees(pi * T(-2.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-540.0), bksge::radians_to_degrees(pi * T(-3.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-720.0), bksge::radians_to_degrees(pi * T(-4.0)));

	BKSGE_CONSTEXPR_EXPECT_EQ( inf, bksge::radians_to_degrees(+inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::radians_to_degrees(-inf));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isinf  (bksge::radians_to_degrees(+inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isinf  (bksge::radians_to_degrees(-inf)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::radians_to_degrees(+inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::signbit(bksge::radians_to_degrees(-inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan  (bksge::radians_to_degrees(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan  (bksge::radians_to_degrees(-nan)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::radians_to_degrees(+nan)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::radians_to_degrees(-nan)));
}

template <typename T>
void RadiansToDegreesTestSignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.00000000001;

	BKSGE_CONSTEXPR_EXPECT_NEAR(   0.000000000000, bksge::radians_to_degrees(T( 0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(  57.295779513082, bksge::radians_to_degrees(T( 1)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 114.591559026164, bksge::radians_to_degrees(T( 2)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 171.887338539246, bksge::radians_to_degrees(T( 3)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 229.183118052329, bksge::radians_to_degrees(T( 4)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 286.478897565411, bksge::radians_to_degrees(T( 5)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 343.774677078493, bksge::radians_to_degrees(T( 6)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 401.070456591576, bksge::radians_to_degrees(T( 7)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 458.366236104658, bksge::radians_to_degrees(T( 8)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 515.662015617740, bksge::radians_to_degrees(T( 9)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(- 57.295779513082, bksge::radians_to_degrees(T(-1)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(-114.591559026164, bksge::radians_to_degrees(T(-2)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(-171.887338539246, bksge::radians_to_degrees(T(-3)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(-229.183118052329, bksge::radians_to_degrees(T(-4)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(-286.478897565411, bksge::radians_to_degrees(T(-5)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(-343.774677078493, bksge::radians_to_degrees(T(-6)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(-401.070456591576, bksge::radians_to_degrees(T(-7)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(-458.366236104658, bksge::radians_to_degrees(T(-8)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(-515.662015617740, bksge::radians_to_degrees(T(-9)), error);
}

template <typename T>
void RadiansToDegreesTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.00000000001;

	BKSGE_CONSTEXPR_EXPECT_NEAR(  0.000000000000, bksge::radians_to_degrees(T( 0)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 57.295779513082, bksge::radians_to_degrees(T( 1)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(114.591559026164, bksge::radians_to_degrees(T( 2)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(171.887338539246, bksge::radians_to_degrees(T( 3)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(229.183118052329, bksge::radians_to_degrees(T( 4)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(286.478897565411, bksge::radians_to_degrees(T( 5)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(343.774677078493, bksge::radians_to_degrees(T( 6)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(401.070456591576, bksge::radians_to_degrees(T( 7)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(458.366236104658, bksge::radians_to_degrees(T( 8)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(515.662015617740, bksge::radians_to_degrees(T( 9)), error);
}

GTEST_TEST(CMathTest, RadiansToDegreesTest)
{
	RadiansToDegreesTestFloat<float>();
	RadiansToDegreesTestFloat<double>();
	RadiansToDegreesTestFloat<long double>();

//	RadiansToDegreesTestSignedInt<int>();
	RadiansToDegreesTestSignedInt<signed char>();
//	RadiansToDegreesTestSignedInt<short>();
	RadiansToDegreesTestSignedInt<long>();
//	RadiansToDegreesTestSignedInt<long long>();

	RadiansToDegreesTestUnsignedInt<unsigned int>();
//	RadiansToDegreesTestUnsignedInt<unsigned char>();
	RadiansToDegreesTestUnsignedInt<unsigned short>();
//	RadiansToDegreesTestUnsignedInt<unsigned long>();
	RadiansToDegreesTestUnsignedInt<unsigned long long>();
}

}	// namespace radians_to_degrees_test

}	// namespace bksge_cmath_test
