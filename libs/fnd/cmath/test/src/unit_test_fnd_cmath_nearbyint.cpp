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
inline bksge::float_promote_t<T>
nearbyint_helper(T x, int round_mode)
{
	auto current = std::fegetround();
	std::fesetround(round_mode);
	auto ret = bksge::nearbyint(x);
	std::fesetround(current);
	return ret;
}

template <typename T>
void NearbyIntTestFloat(void)
{
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();

	EXPECT_EQ(T( 0.0), nearbyint_helper(T( 0.0), FE_DOWNWARD));
	EXPECT_EQ(T( 2.0), nearbyint_helper(T( 2.5), FE_DOWNWARD));
	EXPECT_EQ(T(-3.0), nearbyint_helper(T(-2.5), FE_DOWNWARD));
	EXPECT_EQ(T( 3.0), nearbyint_helper(T( 3.5), FE_DOWNWARD));
	EXPECT_EQ(T(-4.0), nearbyint_helper(T(-3.5), FE_DOWNWARD));
	EXPECT_EQ(+inf,    nearbyint_helper(+inf,    FE_DOWNWARD));
	EXPECT_EQ(-inf,    nearbyint_helper(-inf,    FE_DOWNWARD));
	EXPECT_TRUE(bksge::isnan(nearbyint_helper(nan, FE_DOWNWARD)));

	EXPECT_EQ(T( 0.0), nearbyint_helper(T( 0.0), FE_TONEAREST));
	EXPECT_EQ(T( 2.0), nearbyint_helper(T( 2.5), FE_TONEAREST));
	EXPECT_EQ(T(-2.0), nearbyint_helper(T(-2.5), FE_TONEAREST));
	EXPECT_EQ(T( 4.0), nearbyint_helper(T( 3.5), FE_TONEAREST));
	EXPECT_EQ(T(-4.0), nearbyint_helper(T(-3.5), FE_TONEAREST));
	EXPECT_EQ(+inf,    nearbyint_helper(+inf,    FE_TONEAREST));
	EXPECT_EQ(-inf,    nearbyint_helper(-inf,    FE_TONEAREST));
	EXPECT_TRUE(bksge::isnan(nearbyint_helper(nan, FE_TONEAREST)));

	EXPECT_EQ(T( 0.0), nearbyint_helper(T( 0.0), FE_TOWARDZERO));
	EXPECT_EQ(T( 2.0), nearbyint_helper(T( 2.5), FE_TOWARDZERO));
	EXPECT_EQ(T(-2.0), nearbyint_helper(T(-2.5), FE_TOWARDZERO));
	EXPECT_EQ(T( 3.0), nearbyint_helper(T( 3.5), FE_TOWARDZERO));
	EXPECT_EQ(T(-3.0), nearbyint_helper(T(-3.5), FE_TOWARDZERO));
	EXPECT_EQ(+inf,    nearbyint_helper(+inf,    FE_TOWARDZERO));
	EXPECT_EQ(-inf,    nearbyint_helper(-inf,    FE_TOWARDZERO));
	EXPECT_TRUE(bksge::isnan(nearbyint_helper(nan, FE_TOWARDZERO)));

	EXPECT_EQ(T( 0.0), nearbyint_helper(T( 0.0), FE_UPWARD));
	EXPECT_EQ(T( 3.0), nearbyint_helper(T( 2.5), FE_UPWARD));
	EXPECT_EQ(T(-2.0), nearbyint_helper(T(-2.5), FE_UPWARD));
	EXPECT_EQ(T( 4.0), nearbyint_helper(T( 3.5), FE_UPWARD));
	EXPECT_EQ(T(-3.0), nearbyint_helper(T(-3.5), FE_UPWARD));
	EXPECT_EQ(+inf,    nearbyint_helper(+inf,    FE_UPWARD));
	EXPECT_EQ(-inf,    nearbyint_helper(-inf,    FE_UPWARD));
	EXPECT_TRUE(bksge::isnan(nearbyint_helper(nan, FE_UPWARD)));
}

template <typename T>
void NearbyIntTestSignedInt(void)
{
	EXPECT_EQ( 0.0, nearbyint_helper(T( 0), FE_DOWNWARD));
	EXPECT_EQ( 2.0, nearbyint_helper(T( 2), FE_DOWNWARD));
	EXPECT_EQ(-2.0, nearbyint_helper(T(-2), FE_DOWNWARD));
	EXPECT_EQ( 3.0, nearbyint_helper(T( 3), FE_DOWNWARD));
	EXPECT_EQ(-3.0, nearbyint_helper(T(-3), FE_DOWNWARD));

	EXPECT_EQ( 0.0, nearbyint_helper(T( 0), FE_TONEAREST));
	EXPECT_EQ( 2.0, nearbyint_helper(T( 2), FE_TONEAREST));
	EXPECT_EQ(-2.0, nearbyint_helper(T(-2), FE_TONEAREST));
	EXPECT_EQ( 3.0, nearbyint_helper(T( 3), FE_TONEAREST));
	EXPECT_EQ(-3.0, nearbyint_helper(T(-3), FE_TONEAREST));

	EXPECT_EQ( 0.0, nearbyint_helper(T( 0), FE_TOWARDZERO));
	EXPECT_EQ( 2.0, nearbyint_helper(T( 2), FE_TOWARDZERO));
	EXPECT_EQ(-2.0, nearbyint_helper(T(-2), FE_TOWARDZERO));
	EXPECT_EQ( 3.0, nearbyint_helper(T( 3), FE_TOWARDZERO));
	EXPECT_EQ(-3.0, nearbyint_helper(T(-3), FE_TOWARDZERO));

	EXPECT_EQ( 0.0, nearbyint_helper(T( 0), FE_UPWARD));
	EXPECT_EQ( 2.0, nearbyint_helper(T( 2), FE_UPWARD));
	EXPECT_EQ(-2.0, nearbyint_helper(T(-2), FE_UPWARD));
	EXPECT_EQ( 3.0, nearbyint_helper(T( 3), FE_UPWARD));
	EXPECT_EQ(-3.0, nearbyint_helper(T(-3), FE_UPWARD));
}

template <typename T>
void NearbyIntTestUnsignedInt(void)
{
	EXPECT_EQ( 0.0, nearbyint_helper(T( 0), FE_DOWNWARD));
	EXPECT_EQ( 2.0, nearbyint_helper(T( 2), FE_DOWNWARD));
	EXPECT_EQ( 3.0, nearbyint_helper(T( 3), FE_DOWNWARD));

	EXPECT_EQ( 0.0, nearbyint_helper(T( 0), FE_TONEAREST));
	EXPECT_EQ( 2.0, nearbyint_helper(T( 2), FE_TONEAREST));
	EXPECT_EQ( 3.0, nearbyint_helper(T( 3), FE_TONEAREST));

	EXPECT_EQ( 0.0, nearbyint_helper(T( 0), FE_TOWARDZERO));
	EXPECT_EQ( 2.0, nearbyint_helper(T( 2), FE_TOWARDZERO));
	EXPECT_EQ( 3.0, nearbyint_helper(T( 3), FE_TOWARDZERO));

	EXPECT_EQ( 0.0, nearbyint_helper(T( 0), FE_UPWARD));
	EXPECT_EQ( 2.0, nearbyint_helper(T( 2), FE_UPWARD));
	EXPECT_EQ( 3.0, nearbyint_helper(T( 3), FE_UPWARD));
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
