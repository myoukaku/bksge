/**
 *	@file	unit_test_fnd_cmath_nearbyint.cpp
 *
 *	@brief	nearbyint のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/nearbyint.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <gtest/gtest.h>
#include <cfenv>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace nearbyint_test
{

static_assert(bksge::is_same<float,       decltype(bksge::nearbyint(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::nearbyintf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::nearbyint(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::nearbyint(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::nearbyint(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::nearbyintl(0.0l))>::value, "");

template <typename T>
void NearbyIntTestFloat(void)
{
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();

	switch (std::fegetround())
	{
	case FE_DOWNWARD:
		EXPECT_EQ(T( 0.0), bksge::nearbyint(T( 0.0)));
		EXPECT_EQ(T( 2.0), bksge::nearbyint(T( 2.5)));
		EXPECT_EQ(T(-3.0), bksge::nearbyint(T(-2.5)));
		EXPECT_EQ(T( 3.0), bksge::nearbyint(T( 3.5)));
		EXPECT_EQ(T(-4.0), bksge::nearbyint(T(-3.5)));
		break;
	case FE_TONEAREST:
		EXPECT_EQ(T( 0.0), bksge::nearbyint(T( 0.0)));
		EXPECT_EQ(T( 2.0), bksge::nearbyint(T( 2.5)));
		EXPECT_EQ(T(-2.0), bksge::nearbyint(T(-2.5)));
		EXPECT_EQ(T( 4.0), bksge::nearbyint(T( 3.5)));
		EXPECT_EQ(T(-4.0), bksge::nearbyint(T(-3.5)));
		break;
	case FE_TOWARDZERO:
		EXPECT_EQ(T( 0.0), bksge::nearbyint(T( 0.0)));
		EXPECT_EQ(T( 2.0), bksge::nearbyint(T( 2.5)));
		EXPECT_EQ(T(-2.0), bksge::nearbyint(T(-2.5)));
		EXPECT_EQ(T( 3.0), bksge::nearbyint(T( 3.5)));
		EXPECT_EQ(T(-3.0), bksge::nearbyint(T(-3.5)));
		break;
	case FE_UPWARD:
		EXPECT_EQ(T( 0.0), bksge::nearbyint(T( 0.0)));
		EXPECT_EQ(T( 3.0), bksge::nearbyint(T( 2.5)));
		EXPECT_EQ(T(-2.0), bksge::nearbyint(T(-2.5)));
		EXPECT_EQ(T( 4.0), bksge::nearbyint(T( 3.5)));
		EXPECT_EQ(T(-3.0), bksge::nearbyint(T(-3.5)));
		break;
	}

	EXPECT_EQ(+inf, bksge::nearbyint(+inf));
	EXPECT_EQ(-inf, bksge::nearbyint(-inf));
	EXPECT_TRUE(bksge::isnan(bksge::nearbyint(nan)));
}

template <typename T>
void NearbyIntTestSignedInt(void)
{
	EXPECT_EQ( 0.0, bksge::nearbyint(T( 0)));
	EXPECT_EQ( 2.0, bksge::nearbyint(T( 2)));
	EXPECT_EQ(-2.0, bksge::nearbyint(T(-2)));
	EXPECT_EQ( 3.0, bksge::nearbyint(T( 3)));
	EXPECT_EQ(-3.0, bksge::nearbyint(T(-3)));
}

template <typename T>
void NearbyIntTestUnsignedInt(void)
{
	EXPECT_EQ( 0.0, bksge::nearbyint(T( 0)));
	EXPECT_EQ( 2.0, bksge::nearbyint(T( 2)));
	EXPECT_EQ( 3.0, bksge::nearbyint(T( 3)));
}

GTEST_TEST(CMathTest, NearbyIntTest)
{
	NearbyIntTestFloat<float>();
	NearbyIntTestFloat<double>();
	NearbyIntTestFloat<long double>();

	NearbyIntTestSignedInt<int>();
//	NearbyIntTestSignedInt<signed char>();
	NearbyIntTestSignedInt<short>();
//	NearbyIntTestSignedInt<long>();
	NearbyIntTestSignedInt<long long>();

//	NearbyIntTestUnsignedInt<unsigned int>();
	NearbyIntTestUnsignedInt<unsigned char>();
//	NearbyIntTestUnsignedInt<unsigned short>();
	NearbyIntTestUnsignedInt<unsigned long>();
//	NearbyIntTestUnsignedInt<unsigned long long>();
}

}	// namespace nearbyint_test

}	// namespace bksge_cmath_test
