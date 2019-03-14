/**
 *	@file	unit_test_cmath_isnan.cpp
 *
 *	@brief	isnan のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/cmath/isnan.hpp>
#include <bksge/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace isnan_test
{

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4056)	// 浮動小数点数の定数演算でオーバーフローしました。
BKSGE_WARNING_DISABLE_MSVC(4723)	// 除算の 2 番目のオペランドは、コンパイル時に 0 と評価され、不定の結果を返します。

template <typename T>
void IsNaNTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();
	T zero = 0;	// MSVCでのエラーを避けるために変数にする

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(+nan));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(-nan));
//	EXPECT_TRUE(bksge::isnan(inf - inf));
	EXPECT_TRUE(bksge::isnan(zero / zero));

	EXPECT_FALSE(bksge::isnan(T(1) / zero));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(inf));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(-inf));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(T( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(T(-0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(T(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(lowest));
	EXPECT_FALSE(bksge::isnan(max * T(2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(min * T(2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(min / T(2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(T(1) / min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(T(1) / max));
}

BKSGE_WARNING_POP()

template <typename T>
void IsNaNTestSignedInt(void)
{
	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(T(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(T(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(max));
}

template <typename T>
void IsNaNTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(T(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(T(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(max));
}

GTEST_TEST(CMathTest, IsNaNTest)
{
	IsNaNTestFloat<float>();
	IsNaNTestFloat<double>();
	IsNaNTestFloat<long double>();

//	IsNaNTestSignedInt<int>();
	IsNaNTestSignedInt<signed char>();
//	IsNaNTestSignedInt<short>();
	IsNaNTestSignedInt<long>();
//	IsNaNTestSignedInt<long long>();

	IsNaNTestUnsignedInt<unsigned int>();
//	IsNaNTestUnsignedInt<unsigned char>();
	IsNaNTestUnsignedInt<unsigned short>();
//	IsNaNTestUnsignedInt<unsigned long>();
	IsNaNTestUnsignedInt<unsigned long long>();
}

}	// namespace isnan_test

}	// namespace bksge_cmath_test
