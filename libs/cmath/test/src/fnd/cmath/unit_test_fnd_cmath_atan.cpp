/**
 *	@file	unit_test_fnd_cmath_atan.cpp
 *
 *	@brief	atan のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/atan.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/numbers.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace atan_test
{

static_assert(bksge::is_same<float,       decltype(bksge::atan(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::atanf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::atan(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::atan(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::atan(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::atanl(0.0l))>::value, "");

template <typename T>
void AtanTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	EXPECT_NEAR(-1.5507989928217, (double)bksge::atan(T(-50.00)), error);
	EXPECT_NEAR(-1.1902899496825, (double)bksge::atan(T( -2.50)), error);
	EXPECT_NEAR(-0.7853981633974, (double)bksge::atan(T( -1.00)), error);
	EXPECT_NEAR(-0.6435011087932, (double)bksge::atan(T( -0.75)), error);
	EXPECT_NEAR(-0.4636476090008, (double)bksge::atan(T( -0.50)), error);
	EXPECT_NEAR(-0.2449786631268, (double)bksge::atan(T( -0.25)), error);
	EXPECT_NEAR( 0.0000000000000, (double)bksge::atan(T(  0.00)), error);
	EXPECT_NEAR( 0.2449786631268, (double)bksge::atan(T(  0.25)), error);
	EXPECT_NEAR( 0.4636476090008, (double)bksge::atan(T(  0.50)), error);
	EXPECT_NEAR( 0.6435011087932, (double)bksge::atan(T(  0.75)), error);
	EXPECT_NEAR( 0.7853981633974, (double)bksge::atan(T(  1.00)), error);
	EXPECT_NEAR( 1.1902899496825, (double)bksge::atan(T(  2.50)), error);
	EXPECT_NEAR( 1.5507989928217, (double)bksge::atan(T( 50.00)), error);

	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::atan(T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::atan(T(-0.0)));

	BKSGE_CONSTEXPR_EXPECT_NEAR( bksge::pi_t<double>() / 2, (double)bksge::atan(+inf), 0.000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR(-bksge::pi_t<double>() / 2, (double)bksge::atan(-inf), 0.000001);

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atan(-nan)));
}

template <typename T>
void AtanTestSignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.000000000001;

	EXPECT_NEAR( 0.0000000000000, bksge::atan(T(   0)), error);
	EXPECT_NEAR( 0.7853981633974, bksge::atan(T(   1)), error);
	EXPECT_NEAR( 1.1071487177941, bksge::atan(T(   2)), error);
	EXPECT_NEAR( 1.4711276743037, bksge::atan(T(  10)), error);
	EXPECT_NEAR( 1.5607966601082, bksge::atan(T( 100)), error);
	EXPECT_NEAR(-0.7853981633974, bksge::atan(T(  -1)), error);
	EXPECT_NEAR(-1.1071487177941, bksge::atan(T(  -2)), error);
	EXPECT_NEAR(-1.4711276743037, bksge::atan(T( -10)), error);
	EXPECT_NEAR(-1.5607966601082, bksge::atan(T(-100)), error);
}

template <typename T>
void AtanTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.000000000001;

	EXPECT_NEAR(0.0000000000000, bksge::atan(T(  0)), error);
	EXPECT_NEAR(0.7853981633974, bksge::atan(T(  1)), error);
	EXPECT_NEAR(1.1071487177941, bksge::atan(T(  2)), error);
	EXPECT_NEAR(1.4711276743037, bksge::atan(T( 10)), error);
	EXPECT_NEAR(1.5607966601082, bksge::atan(T(100)), error);
}

GTEST_TEST(CMathTest, AtanTest)
{
	AtanTestFloat<float>(0.000001);
	AtanTestFloat<double>(0.000000000001);
	AtanTestFloat<long double>(0.000000000001);

	AtanTestSignedInt<int>();
//	AtanTestSignedInt<signed char>();
	AtanTestSignedInt<short>();
//	AtanTestSignedInt<long>();
	AtanTestSignedInt<long long>();

	AtanTestUnsignedInt<unsigned int>();
	AtanTestUnsignedInt<unsigned char>();
//	AtanTestUnsignedInt<unsigned short>();
	AtanTestUnsignedInt<unsigned long>();
//	AtanTestUnsignedInt<unsigned long long>();
}

}	// namespace atan_test

}	// namespace bksge_cmath_test
