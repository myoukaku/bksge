/**
 *	@file	unit_test_fnd_cmath_issubnormal.cpp
 *
 *	@brief	issubnormal のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/issubnormal.hpp>
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

namespace issubnormal_test
{

static_assert(bksge::is_same<bool, decltype(bksge::issubnormal(0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::issubnormal(0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::issubnormal(0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::issubnormal(0   ))>::value, "");

template <typename T>
void IsSubnormalTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto denorm_min = std::numeric_limits<T>::denorm_min();
	T zero = 0;	// MSVCでのエラーを避けるために変数にする

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::issubnormal(inf));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::issubnormal(-inf));
	EXPECT_FALSE(bksge::issubnormal(bksge::exp(T(80000))));
	EXPECT_FALSE(bksge::issubnormal(T(1) / zero));
	EXPECT_FALSE(bksge::issubnormal(max * T(2)));
	EXPECT_FALSE(bksge::issubnormal(lowest * T(2)));
	EXPECT_FALSE(bksge::issubnormal(nan));
	EXPECT_FALSE(bksge::issubnormal(-nan));
	EXPECT_FALSE(bksge::issubnormal(inf - inf));
	EXPECT_FALSE(bksge::issubnormal(zero / zero));

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::issubnormal(T( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::issubnormal(T(-0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::issubnormal(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::issubnormal(T(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::issubnormal(min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::issubnormal(max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::issubnormal(lowest));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::issubnormal(min * T(2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::issubnormal(T(1) / min));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::issubnormal(min / T(2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::issubnormal(T(1) / max));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::issubnormal(T(1) / lowest));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::issubnormal(denorm_min));
}

template <typename T>
void IsSubnormalTestSignedInt(void)
{
	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::issubnormal(T(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::issubnormal(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::issubnormal(T(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::issubnormal(min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::issubnormal(max));
}

template <typename T>
void IsSubnormalTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::issubnormal(T(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::issubnormal(T(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::issubnormal(min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::issubnormal(max));
}

GTEST_TEST(CMathTest, IsSubnormalTest)
{
	IsSubnormalTestFloat<float>();
	IsSubnormalTestFloat<double>();
	IsSubnormalTestFloat<long double>();

//	IsSubnormalTestSignedInt<int>();
	IsSubnormalTestSignedInt<signed char>();
//	IsSubnormalTestSignedInt<short>();
	IsSubnormalTestSignedInt<long>();
//	IsSubnormalTestSignedInt<long long>();

	IsSubnormalTestUnsignedInt<unsigned int>();
//	IsSubnormalTestUnsignedInt<unsigned char>();
	IsSubnormalTestUnsignedInt<unsigned short>();
//	IsSubnormalTestUnsignedInt<unsigned long>();
	IsSubnormalTestUnsignedInt<unsigned long long>();
}

}	// namespace issubnormal_test

}	// namespace bksge_cmath_test

BKSGE_WARNING_POP()
