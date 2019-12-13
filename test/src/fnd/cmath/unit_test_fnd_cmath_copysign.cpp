/**
 *	@file	unit_test_fnd_cmath_copysign.cpp
 *
 *	@brief	copysign のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/copysign.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace copysign_test
{

template <typename T>
void CopysignTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_EQ(T( 1.0), bksge::copysign(T( 1.0), T(+2.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-1.0), bksge::copysign(T( 1.0), T(-2.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 5.0), bksge::copysign(T(-5.0), T(+2.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-5.0), bksge::copysign(T(-5.0), T(-2.0)));
	
	// BKSGEでは、yが±0のときはxの符号は変更されない
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 2.0), bksge::copysign(T( 2.0), T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 2.0), bksge::copysign(T( 2.0), T(-0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-3.0), bksge::copysign(T(-3.0), T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-3.0), bksge::copysign(T(-3.0), T(-0.0)));
	
	// BKSGEでは、yが±NaNのときはxの符号は変更されない
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 4.0), bksge::copysign(T( 4.0), +nan));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 4.0), bksge::copysign(T( 4.0), -nan));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-5.0), bksge::copysign(T(-5.0), +nan));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-5.0), bksge::copysign(T(-5.0), -nan));

	BKSGE_CONSTEXPR_EXPECT_EQ(T( 6.0), bksge::copysign(T( 6.0), +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-6.0), bksge::copysign(T( 6.0), -inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 7.0), bksge::copysign(T(-7.0), +inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-7.0), bksge::copysign(T(-7.0), -inf));
	BKSGE_CONSTEXPR_EXPECT_EQ( max, bksge::copysign(max, T(+1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-max, bksge::copysign(max, T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( min, bksge::copysign(min, T(+1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-min, bksge::copysign(min, T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( max, bksge::copysign(lowest, T(+1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-max, bksge::copysign(lowest, T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( inf, bksge::copysign(inf, T(+3.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::copysign(inf, T(-3.0)));

	// BKSGEでは、+NaNと-NaNは区別されない
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan  (bksge::copysign(nan, T(+1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan  (bksge::copysign(nan, T(-1.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::copysign(nan, T(+1.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::copysign(nan, T(-1.0))));

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan  (bksge::copysign(nan, T(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan  (bksge::copysign(nan, T(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::copysign(nan, T(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::copysign(nan, T(-0.0))));

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan  (bksge::copysign(nan,  nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan  (bksge::copysign(nan, -nan)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::copysign(nan,  nan)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::copysign(nan, -nan)));

	// BKSGEでは、+0と-0は区別されない
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::copysign(T(0), T(+1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::copysign(T(0), T(-1.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::copysign(T(0), T(+1.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::copysign(T(0), T(-1.0))));

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::copysign(T(0), T(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::copysign(T(0), T(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::copysign(T(0), T(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::copysign(T(0), T(-0.0))));

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::copysign(T(0),  nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::copysign(T(0), -nan)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::copysign(T(0),  nan)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::copysign(T(0), -nan)));
}

template <typename T>
void CopysignTestSignedInt(void)
{
	BKSGE_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_EQ(T( 1), bksge::copysign(T(1), T(+2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-1), bksge::copysign(T(1), T(-2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 5), bksge::copysign(T(-5), +2.0f));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-5), bksge::copysign(T(-5), -2.0f));
	BKSGE_CONSTEXPR_EXPECT_EQ( max, bksge::copysign(max, +1.0f));
	BKSGE_CONSTEXPR_EXPECT_EQ(-max, bksge::copysign(max, -1.0f));
	BKSGE_CONSTEXPR_EXPECT_EQ(-double(min), bksge::copysign(min, T(+1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( double(min), bksge::copysign(min, T(-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-double(min), bksge::copysign(lowest, T(+1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( double(min), bksge::copysign(lowest, T(-1)));
}

template <typename T>
void CopysignTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_EQ( 1.0, bksge::copysign(T(1), T(+2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1.0, bksge::copysign(T(1), -2.0));
	BKSGE_CONSTEXPR_EXPECT_EQ( double(max), bksge::copysign(max, +1.0f));
	BKSGE_CONSTEXPR_EXPECT_EQ(-double(max), bksge::copysign(max, -1.0f));
	BKSGE_CONSTEXPR_EXPECT_EQ( min, bksge::copysign(min, +1));
	BKSGE_CONSTEXPR_EXPECT_EQ( min, bksge::copysign(min, -1));
	BKSGE_CONSTEXPR_EXPECT_EQ( lowest, bksge::copysign(lowest, +1));
	BKSGE_CONSTEXPR_EXPECT_EQ( lowest, bksge::copysign(lowest, -1));
}

GTEST_TEST(CMathTest, CopySignTest)
{
	CopysignTestFloat<float>();
	CopysignTestFloat<double>();
	CopysignTestFloat<long double>();

	CopysignTestSignedInt<int>();
//	CopysignTestSignedInt<signed char>();
	CopysignTestSignedInt<short>();
//	CopysignTestSignedInt<long>();
	CopysignTestSignedInt<long long>();

	CopysignTestUnsignedInt<unsigned int>();
	CopysignTestUnsignedInt<unsigned char>();
//	CopysignTestUnsignedInt<unsigned short>();
	CopysignTestUnsignedInt<unsigned long>();
//	CopysignTestUnsignedInt<unsigned long long>();
}

}	// namespace copysign_test

}	// namespace bksge_cmath_test
