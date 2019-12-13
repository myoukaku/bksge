/**
 *	@file	unit_test_cmath_clamp.cpp
 *
 *	@brief	clamp のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/cmath/clamp.hpp>
#include <bksge/cmath/iszero.hpp>
#include <bksge/cmath/isnan.hpp>
#include <bksge/cmath/signbit.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace clamp_test
{

template <typename T>
void ClampTestFloat(void)
{
	BKSGE_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_EQ(T(  0), bksge::clamp(T(  0), T(  0), T(  0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(  0), bksge::clamp(T( -1), T(  0), T(  0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(  0), bksge::clamp(T(  1), T(  0), T(  0)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T(-10), bksge::clamp(T(-11), T(-10), T( 20)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-10), bksge::clamp(T(-10), T(-10), T( 20)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( -9), bksge::clamp(T( -9), T(-10), T( 20)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 19), bksge::clamp(T( 19), T(-10), T( 20)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 20), bksge::clamp(T( 20), T(-10), T( 20)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 20), bksge::clamp(T( 21), T(-10), T( 20)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T(0.5), bksge::clamp(T(0.4), T(0.5), T(1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0.5), bksge::clamp(T(0.5), T(0.5), T(1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0.6), bksge::clamp(T(0.6), T(0.5), T(1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(1.4), bksge::clamp(T(1.4), T(0.5), T(1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(1.5), bksge::clamp(T(1.5), T(0.5), T(1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(1.5), bksge::clamp(T(1.6), T(0.5), T(1.5)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T( 10), bksge::clamp(T( 10), -inf, inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-10), bksge::clamp(T(-10), -inf, inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 10), bksge::clamp(T( 10), T(0.0), inf));

	BKSGE_CONSTEXPR_EXPECT_EQ(T(3.0), bksge::clamp( inf, T(2.0), T(3.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(2.0), bksge::clamp(-inf, T(2.0), T(3.0)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T(  0), bksge::clamp(T(  0), lowest, max));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 20), bksge::clamp(T( 20), lowest, max));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-20), bksge::clamp(T(-20), lowest, max));

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::clamp(T(+0.0), T(-1.0), T(1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::clamp(T(-0.0), T(-1.0), T(1.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::clamp(T(+0.0), T(-1.0), T(1.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::clamp(T(-0.0), T(-1.0), T(1.0))));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::clamp(T(0.0), T(10),   T(5))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::clamp(T(0.0), T(1.0),  T(-1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::clamp(nan,    T(-1.0), T(1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::clamp(T(0.0), nan,     T(1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::clamp(T(0.0), T(-1.0), nan)));
}

template <typename T>
void ClampTestSignedInt(void)
{
	BKSGE_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_EQ(T(  0), bksge::clamp(T(  0), T(  0), T(  0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(  0), bksge::clamp(T( -1), T(  0), T(  0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(  0), bksge::clamp(T(  1), T(  0), T(  0)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T(-10), bksge::clamp(T(-11), T(-10), T( 20)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-10), bksge::clamp(T(-10), T(-10), T( 20)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( -9), bksge::clamp(T( -9), T(-10), T( 20)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 19), bksge::clamp(T( 19), T(-10), T( 20)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 20), bksge::clamp(T( 20), T(-10), T( 20)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 20), bksge::clamp(T( 21), T(-10), T( 20)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T(  0), bksge::clamp(T(  0), lowest, max));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 20), bksge::clamp(T( 20), lowest, max));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-20), bksge::clamp(T(-20), lowest, max));
}

template <typename T>
void ClampTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_EQ(T( 0), bksge::clamp(T( 0), T( 0), T( 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 0), bksge::clamp(T( 1), T( 0), T( 0)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T(10), bksge::clamp(T( 9), T(10), T(20)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(10), bksge::clamp(T(10), T(10), T(20)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(11), bksge::clamp(T(11), T(10), T(20)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(15), bksge::clamp(T(15), T(10), T(20)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(19), bksge::clamp(T(19), T(10), T(20)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(20), bksge::clamp(T(20), T(10), T(20)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(20), bksge::clamp(T(21), T(10), T(20)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T( 0), bksge::clamp(T( 0), lowest, max));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(20), bksge::clamp(T(20), lowest, max));
}

GTEST_TEST(CMathTest, ClampTest)
{
	ClampTestFloat<float>();
	ClampTestFloat<double>();
	ClampTestFloat<long double>();

	ClampTestSignedInt<int>();
	ClampTestSignedInt<signed char>();
//	ClampTestSignedInt<short>();
	ClampTestSignedInt<long>();
//	ClampTestSignedInt<long long>();

	ClampTestUnsignedInt<unsigned int>();
//	ClampTestUnsignedInt<unsigned char>();
	ClampTestUnsignedInt<unsigned short>();
//	ClampTestUnsignedInt<unsigned long>();
	ClampTestUnsignedInt<unsigned long long>();
}

}	// namespace clamp_test

}	// namespace bksge_cmath_test
