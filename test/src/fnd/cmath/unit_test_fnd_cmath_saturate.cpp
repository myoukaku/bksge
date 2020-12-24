/**
 *	@file	unit_test_fnd_cmath_saturate.cpp
 *
 *	@brief	saturate のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/saturate.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace saturate_test
{

template <typename T>
void SaturateTestFloat(void)
{
	BKSGE_CONSTEXPR auto inf    = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto nan    = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto max    = bksge::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto lowest = bksge::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_EQ(T(0.0), bksge::saturate(T(lowest)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0.0), bksge::saturate(T(-0.2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0.0), bksge::saturate(T(-0.1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0.0), bksge::saturate(T( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0.1), bksge::saturate(T( 0.1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0.2), bksge::saturate(T( 0.2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0.9), bksge::saturate(T( 0.9)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(1.0), bksge::saturate(T( 1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(1.0), bksge::saturate(T( 1.1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(1.0), bksge::saturate(T(max)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(1.0), bksge::saturate(T(inf)));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::saturate(nan)));
}

template <typename T>
void SaturateTestSignedInt(void)
{
	BKSGE_CONSTEXPR auto max    = bksge::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto lowest = bksge::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_EQ(T(0), bksge::saturate(T(lowest)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0), bksge::saturate(T(-2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0), bksge::saturate(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0), bksge::saturate(T( 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(1), bksge::saturate(T( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(1), bksge::saturate(T( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(1), bksge::saturate(T(max)));
}

template <typename T>
void SaturateTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR auto max = bksge::numeric_limits<T>::max();

	BKSGE_CONSTEXPR_EXPECT_EQ(T(0), bksge::saturate(T(0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(1), bksge::saturate(T(1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(1), bksge::saturate(T(2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(1), bksge::saturate(T(max)));
}

GTEST_TEST(CMathTest, SaturateTest)
{
	SaturateTestFloat<float>();
	SaturateTestFloat<double>();
	SaturateTestFloat<long double>();

	SaturateTestSignedInt<int>();
	SaturateTestSignedInt<signed char>();
//	SaturateTestSignedInt<short>();
	SaturateTestSignedInt<long>();
//	SaturateTestSignedInt<long long>();

	SaturateTestUnsignedInt<unsigned int>();
//	SaturateTestUnsignedInt<unsigned char>();
	SaturateTestUnsignedInt<unsigned short>();
//	SaturateTestUnsignedInt<unsigned long>();
	SaturateTestUnsignedInt<unsigned long long>();
}

}	// namespace saturate_test

}	// namespace bksge_cmath_test
