/**
 *	@file	unit_test_cmath_isinf.cpp
 *
 *	@brief	isinf のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/cmath/isinf.hpp>
#include <bksge/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace isinf_test
{

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4056)	// 浮動小数点数の定数演算でオーバーフローしました。
BKSGE_WARNING_DISABLE_MSVC(4723)	// 除算の 2 番目のオペランドは、コンパイル時に 0 と評価され、不定の結果を返します。

template <typename T>
void IsInfTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();
	T zero = 0;	// MSVCでのエラーを避けるために変数にする

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isinf(inf));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isinf(-inf));
	EXPECT_TRUE(bksge::isinf(T(1) / zero));
	EXPECT_TRUE(bksge::isinf(max * T(2)));

	EXPECT_FALSE(bksge::isinf(nan));
	EXPECT_FALSE(bksge::isinf(-nan));
	EXPECT_FALSE(bksge::isinf(inf - inf));
	EXPECT_FALSE(bksge::isinf(zero / zero));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isinf(T( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isinf(T(-0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isinf(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isinf(T(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isinf(min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isinf(max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isinf(lowest));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isinf(min * T(2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isinf(min / T(2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isinf(T(1) / min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isinf(T(1) / max));
}

BKSGE_WARNING_POP()

template <typename T>
void IsInfTestSignedInt(void)
{
	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isinf(T(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isinf(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isinf(T(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isinf(min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isinf(max));
}

template <typename T>
void IsInfTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isinf(T(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isinf(T(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isinf(min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isinf(max));
}

GTEST_TEST(CMathTest, IsInfTest)
{
	IsInfTestFloat<float>();
	IsInfTestFloat<double>();
	IsInfTestFloat<long double>();

	IsInfTestSignedInt<int>();
//	IsInfTestSignedInt<signed char>();
	IsInfTestSignedInt<short>();
//	IsInfTestSignedInt<long>();
	IsInfTestSignedInt<long long>();

//	IsInfTestUnsignedInt<unsigned int>();
	IsInfTestUnsignedInt<unsigned char>();
//	IsInfTestUnsignedInt<unsigned short>();
	IsInfTestUnsignedInt<unsigned long>();
//	IsInfTestUnsignedInt<unsigned long long>();
}

}	// namespace isinf_test

}	// namespace bksge_cmath_test
