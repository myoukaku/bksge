/**
 *	@file	unit_test_fnd_cmath_erfc.cpp
 *
 *	@brief	erfc のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/erfc.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace erfc_test
{

static_assert(bksge::is_same<float,       decltype(bksge::erfc(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::erfcf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::erfc(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::erfc(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::erfc(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::erfcl(0.0l))>::value, "");

template <typename T>
void ErfcTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	BKSGE_CONSTEXPR_EXPECT_EQ(T(0.0), bksge::erfc(+inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(2.0), bksge::erfc(-inf));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::erfc(nan)));

	EXPECT_NEAR(1.995322265018952734162,  (double)bksge::erfc(T(-2.0)), error);
	EXPECT_NEAR(1.842700792949714869341,  (double)bksge::erfc(T(-1.0)), error);
	EXPECT_NEAR(1.0,                      (double)bksge::erfc(T( 0.0)), error);
	EXPECT_NEAR(0.1572992070502851306588, (double)bksge::erfc(T( 1.0)), error);
	EXPECT_NEAR(0.0046777349810472658379, (double)bksge::erfc(T( 2.0)), error);
}

template <typename T>
void ErfcTestSignedInt(void)
{
	double const error = 0.000000000000001;

	EXPECT_NEAR(1.995322265018952734162,  bksge::erfc(T(-2)), error);
	EXPECT_NEAR(1.842700792949714869341,  bksge::erfc(T(-1)), error);
	EXPECT_NEAR(1.0,                      bksge::erfc(T( 0)), error);
	EXPECT_NEAR(0.1572992070502851306588, bksge::erfc(T( 1)), error);
	EXPECT_NEAR(0.0046777349810472658379, bksge::erfc(T( 2)), error);
}

template <typename T>
void ErfcTestUnsignedInt(void)
{
	double const error = 0.000000000000001;

	EXPECT_NEAR(1.0,                      bksge::erfc(T( 0)), error);
	EXPECT_NEAR(0.1572992070502851306588, bksge::erfc(T( 1)), error);
	EXPECT_NEAR(0.0046777349810472658379, bksge::erfc(T( 2)), error);
	EXPECT_NEAR(2.209049699858544137278E-5, bksge::erfc(T( 3)), error);
	EXPECT_NEAR(1.541725790028001885216E-8, bksge::erfc(T( 4)), error);
}

GTEST_TEST(CMathTest, ErfcTest)
{
	ErfcTestFloat<float>      (0.0000001);
	ErfcTestFloat<double>     (0.000000000000001);
	ErfcTestFloat<long double>(0.000000000000001);

	ErfcTestSignedInt<int>();
//	ErfcTestSignedInt<signed char>();
	ErfcTestSignedInt<short>();
//	ErfcTestSignedInt<long>();
	ErfcTestSignedInt<long long>();

//	ErfcTestUnsignedInt<unsigned int>();
	ErfcTestUnsignedInt<unsigned char>();
//	ErfcTestUnsignedInt<unsigned short>();
	ErfcTestUnsignedInt<unsigned long>();
//	ErfcTestUnsignedInt<unsigned long long>();
}

}	// namespace erfc_test

}	// namespace bksge_cmath_test
