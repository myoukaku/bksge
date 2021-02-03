/**
 *	@file	unit_test_fnd_cmath_isnormal.cpp
 *
 *	@brief	isnormal のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/isnormal.hpp>
#include <bksge/fnd/cmath/exp.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4756 4723 4056)

namespace bksge_cmath_test
{

namespace isnormal_test
{

static_assert(bksge::is_same<bool, decltype(bksge::isnormal(0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isnormal(0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isnormal(0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isnormal(0   ))>::value, "");

template <typename T>
void IsNormalTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan    = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf    = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto min    = bksge::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max    = bksge::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto lowest = bksge::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto denorm_min = bksge::numeric_limits<T>::denorm_min();
	T zero = 0;	// MSVCでのエラーを避けるために変数にする

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnormal(inf));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnormal(-inf));
	EXPECT_FALSE(bksge::isnormal(bksge::exp(T(80000))));
	EXPECT_FALSE(bksge::isnormal(T(1) / zero));
	EXPECT_FALSE(bksge::isnormal(max * T(2)));
	EXPECT_FALSE(bksge::isnormal(lowest * T(2)));
	EXPECT_FALSE(bksge::isnormal(nan));
	EXPECT_FALSE(bksge::isnormal(-nan));
	EXPECT_FALSE(bksge::isnormal(inf - inf));
	EXPECT_FALSE(bksge::isnormal(zero / zero));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnormal(T( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnormal(T(-0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnormal(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnormal(T(1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnormal(min));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnormal(max));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnormal(lowest));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnormal(min * T(2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnormal(min / T(2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnormal(T(1) / min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnormal(T(1) / max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnormal(T(1) / lowest));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnormal(denorm_min));
}

template <typename T>
void IsNormalTestSignedInt(void)
{
	BKSGE_CONSTEXPR auto min = bksge::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max = bksge::numeric_limits<T>::max();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnormal(T(0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnormal(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnormal(T(1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnormal(min));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnormal(max));
}

template <typename T>
void IsNormalTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR auto min = bksge::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max = bksge::numeric_limits<T>::max();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnormal(T(0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnormal(T(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnormal(min));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnormal(max));
}

GTEST_TEST(CMathTest, IsNormalTest)
{
	IsNormalTestFloat<float>();
	IsNormalTestFloat<double>();
	IsNormalTestFloat<long double>();

	IsNormalTestSignedInt<int>();
//	IsNormalTestSignedInt<signed char>();
	IsNormalTestSignedInt<short>();
//	IsNormalTestSignedInt<long>();
	IsNormalTestSignedInt<long long>();

//	IsNormalTestUnsignedInt<unsigned int>();
	IsNormalTestUnsignedInt<unsigned char>();
//	IsNormalTestUnsignedInt<unsigned short>();
	IsNormalTestUnsignedInt<unsigned long>();
//	IsNormalTestUnsignedInt<unsigned long long>();
}

}	// namespace isnormal_test

}	// namespace bksge_cmath_test

BKSGE_WARNING_POP()
