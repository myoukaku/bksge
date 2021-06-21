/**
 *	@file	unit_test_fnd_cmath_iszero.cpp
 *
 *	@brief	iszero のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace iszero_test
{

static_assert(bksge::is_same<bool, decltype(bksge::iszero(0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::iszero(0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::iszero(0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::iszero(0   ))>::value, "");

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4056)	// 浮動小数点数の定数演算でオーバーフローしました。
BKSGE_WARNING_DISABLE_MSVC(4723)	// 除算の 2 番目のオペランドは、コンパイル時に 0 と評価され、不定の結果を返します。

template <typename T>
void IsZeroTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();
	T zero = 0;	// MSVCでのエラーを避けるために変数にする

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::iszero(inf));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::iszero(-inf));
	EXPECT_FALSE(bksge::iszero(T(1) / zero));
	EXPECT_FALSE(bksge::iszero(max * T(2)));
	EXPECT_FALSE(bksge::iszero(lowest * T(2)));
	EXPECT_FALSE(bksge::iszero(nan));
	EXPECT_FALSE(bksge::iszero(-nan));
//	EXPECT_FALSE(bksge::iszero(inf - inf));
	EXPECT_FALSE(bksge::iszero(zero / zero));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::iszero(T( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::iszero(T(-0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::iszero(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::iszero(T(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::iszero(min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::iszero(max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::iszero(lowest));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::iszero(min * T(2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::iszero(T(1) / min));
}

BKSGE_WARNING_POP()

template <typename T>
void IsZeroTestSignedInt(void)
{
	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero(T(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::iszero(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::iszero(T(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::iszero(min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::iszero(max));
}

template <typename T>
void IsZeroTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero(T(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::iszero(T(1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero(min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::iszero(max));
}

GTEST_TEST(CMathTest, IsZeroTest)
{
	IsZeroTestFloat<float>();
	IsZeroTestFloat<double>();
	IsZeroTestFloat<long double>();

//	IsZeroTestSignedInt<int>();
	IsZeroTestSignedInt<signed char>();
//	IsZeroTestSignedInt<short>();
	IsZeroTestSignedInt<long>();
//	IsZeroTestSignedInt<long long>();

	IsZeroTestUnsignedInt<unsigned int>();
//	IsZeroTestUnsignedInt<unsigned char>();
	IsZeroTestUnsignedInt<unsigned short>();
//	IsZeroTestUnsignedInt<unsigned long>();
	IsZeroTestUnsignedInt<unsigned long long>();
}

}	// namespace iszero_test

}	// namespace bksge_cmath_test
