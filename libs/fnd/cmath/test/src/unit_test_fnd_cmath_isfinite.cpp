/**
 *	@file	unit_test_fnd_cmath_isfinite.cpp
 *
 *	@brief	isfinite のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/isfinite.hpp>
#include <bksge/fnd/cmath/exp.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4756 4723 4056)

namespace bksge_cmath_test
{

namespace isfinite_test
{

static_assert(bksge::is_same<bool, decltype(bksge::isfinite(0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isfinite(0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isfinite(0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::isfinite(0   ))>::value, "");

template <typename T>
void IsFiniteTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();
	T zero = 0;	// MSVCでのエラーを避けるために変数にする

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isfinite(inf));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isfinite(-inf));
	EXPECT_FALSE(bksge::isfinite(bksge::exp(T(80000))));
	EXPECT_FALSE(bksge::isfinite(T(1) / zero));
	EXPECT_FALSE(bksge::isfinite(max * T(2)));
	EXPECT_FALSE(bksge::isfinite(lowest * T(2)));
	EXPECT_FALSE(bksge::isfinite(nan));
	EXPECT_FALSE(bksge::isfinite(-nan));
//	EXPECT_FALSE(bksge::isfinite(inf - inf));
	EXPECT_FALSE(bksge::isfinite(zero / zero));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(T( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(T(-0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(T(1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(min));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(max));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(lowest));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(min * T(2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(min / T(2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(T(1) / min));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(T(1) / max));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(T(1) / lowest));
}

template <typename T>
void IsFiniteTestSignedInt(void)
{
	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(T(0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(T(1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(min));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(max));
}

template <typename T>
void IsFiniteTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(T(0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(T(1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(min));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isfinite(max));
}

GTEST_TEST(CMathTest, IsFiniteTest)
{
	IsFiniteTestFloat<float>();
	IsFiniteTestFloat<double>();
	IsFiniteTestFloat<long double>();

	IsFiniteTestSignedInt<int>();
//	IsFiniteTestSignedInt<signed char>();
	IsFiniteTestSignedInt<short>();
//	IsFiniteTestSignedInt<long>();
	IsFiniteTestSignedInt<long long>();

//	IsFiniteTestUnsignedInt<unsigned int>();
	IsFiniteTestUnsignedInt<unsigned char>();
//	IsFiniteTestUnsignedInt<unsigned short>();
	IsFiniteTestUnsignedInt<unsigned long>();
//	IsFiniteTestUnsignedInt<unsigned long long>();
}

}	// namespace isfinite_test

}	// namespace bksge_cmath_test

BKSGE_WARNING_POP()
