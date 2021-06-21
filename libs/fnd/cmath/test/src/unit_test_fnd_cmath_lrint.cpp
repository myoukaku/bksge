/**
 *	@file	unit_test_fnd_cmath_lrint.cpp
 *
 *	@brief	lrint のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/lrint.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <cfenv>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace lrint_test
{

static_assert(bksge::is_same<long, decltype(bksge::lrint(0.0f))>::value, "");
static_assert(bksge::is_same<long, decltype(bksge::lrintf(0.0f))>::value, "");
static_assert(bksge::is_same<long, decltype(bksge::lrint(0.0 ))>::value, "");
static_assert(bksge::is_same<long, decltype(bksge::lrint(0   ))>::value, "");
static_assert(bksge::is_same<long, decltype(bksge::lrint(0.0l))>::value, "");
static_assert(bksge::is_same<long, decltype(bksge::lrintl(0.0l))>::value, "");

template <typename T>
inline long lrint_helper(T x, int round_mode)
{
	auto current = std::fegetround();
	std::fesetround(round_mode);
	auto ret = bksge::lrint(x);
	std::fesetround(current);
	return ret;
}

template <typename T>
void LRIntTestFloat(void)
{
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto lmax = std::numeric_limits<long>::max();
	BKSGE_CONSTEXPR auto lmin = std::numeric_limits<long>::min();

	EXPECT_EQ(T( 0.0), lrint_helper(T( 0.0), FE_DOWNWARD));
	EXPECT_EQ(T( 2.0), lrint_helper(T( 2.5), FE_DOWNWARD));
	EXPECT_EQ(T(-3.0), lrint_helper(T(-2.5), FE_DOWNWARD));
	EXPECT_EQ(T( 3.0), lrint_helper(T( 3.5), FE_DOWNWARD));
	EXPECT_EQ(T(-4.0), lrint_helper(T(-3.5), FE_DOWNWARD));
	EXPECT_EQ(lmax,    lrint_helper(+inf,    FE_DOWNWARD));
	EXPECT_EQ(lmin,    lrint_helper(-inf,    FE_DOWNWARD));
	EXPECT_EQ(T( 0.0), lrint_helper(nan,     FE_DOWNWARD));

	EXPECT_EQ(T( 0.0), lrint_helper(T( 0.0), FE_TONEAREST));
	EXPECT_EQ(T( 2.0), lrint_helper(T( 2.5), FE_TONEAREST));
	EXPECT_EQ(T(-2.0), lrint_helper(T(-2.5), FE_TONEAREST));
	EXPECT_EQ(T( 4.0), lrint_helper(T( 3.5), FE_TONEAREST));
	EXPECT_EQ(T(-4.0), lrint_helper(T(-3.5), FE_TONEAREST));
	EXPECT_EQ(lmax,    lrint_helper(+inf,    FE_TONEAREST));
	EXPECT_EQ(lmin,    lrint_helper(-inf,    FE_TONEAREST));
	EXPECT_EQ(T( 0.0), lrint_helper(nan,     FE_TONEAREST));

	EXPECT_EQ(T( 0.0), lrint_helper(T( 0.0), FE_TOWARDZERO));
	EXPECT_EQ(T( 2.0), lrint_helper(T( 2.5), FE_TOWARDZERO));
	EXPECT_EQ(T(-2.0), lrint_helper(T(-2.5), FE_TOWARDZERO));
	EXPECT_EQ(T( 3.0), lrint_helper(T( 3.5), FE_TOWARDZERO));
	EXPECT_EQ(T(-3.0), lrint_helper(T(-3.5), FE_TOWARDZERO));
	EXPECT_EQ(lmax,    lrint_helper(+inf,    FE_TOWARDZERO));
	EXPECT_EQ(lmin,    lrint_helper(-inf,    FE_TOWARDZERO));
	EXPECT_EQ(T( 0.0), lrint_helper(nan,     FE_TOWARDZERO));

	EXPECT_EQ(T( 0.0), lrint_helper(T( 0.0), FE_UPWARD));
	EXPECT_EQ(T( 3.0), lrint_helper(T( 2.5), FE_UPWARD));
	EXPECT_EQ(T(-2.0), lrint_helper(T(-2.5), FE_UPWARD));
	EXPECT_EQ(T( 4.0), lrint_helper(T( 3.5), FE_UPWARD));
	EXPECT_EQ(T(-3.0), lrint_helper(T(-3.5), FE_UPWARD));
	EXPECT_EQ(lmax,    lrint_helper(+inf,    FE_UPWARD));
	EXPECT_EQ(lmin,    lrint_helper(-inf,    FE_UPWARD));
	EXPECT_EQ(T( 0.0), lrint_helper(nan,     FE_UPWARD));
}

template <typename T>
void LRIntTestSignedInt(void)
{
	EXPECT_EQ( 0.0, lrint_helper(T( 0), FE_DOWNWARD));
	EXPECT_EQ( 2.0, lrint_helper(T( 2), FE_DOWNWARD));
	EXPECT_EQ(-2.0, lrint_helper(T(-2), FE_DOWNWARD));
	EXPECT_EQ( 3.0, lrint_helper(T( 3), FE_DOWNWARD));
	EXPECT_EQ(-3.0, lrint_helper(T(-3), FE_DOWNWARD));

	EXPECT_EQ( 0.0, lrint_helper(T( 0), FE_TONEAREST));
	EXPECT_EQ( 2.0, lrint_helper(T( 2), FE_TONEAREST));
	EXPECT_EQ(-2.0, lrint_helper(T(-2), FE_TONEAREST));
	EXPECT_EQ( 3.0, lrint_helper(T( 3), FE_TONEAREST));
	EXPECT_EQ(-3.0, lrint_helper(T(-3), FE_TONEAREST));

	EXPECT_EQ( 0.0, lrint_helper(T( 0), FE_TOWARDZERO));
	EXPECT_EQ( 2.0, lrint_helper(T( 2), FE_TOWARDZERO));
	EXPECT_EQ(-2.0, lrint_helper(T(-2), FE_TOWARDZERO));
	EXPECT_EQ( 3.0, lrint_helper(T( 3), FE_TOWARDZERO));
	EXPECT_EQ(-3.0, lrint_helper(T(-3), FE_TOWARDZERO));

	EXPECT_EQ( 0.0, lrint_helper(T( 0), FE_UPWARD));
	EXPECT_EQ( 2.0, lrint_helper(T( 2), FE_UPWARD));
	EXPECT_EQ(-2.0, lrint_helper(T(-2), FE_UPWARD));
	EXPECT_EQ( 3.0, lrint_helper(T( 3), FE_UPWARD));
	EXPECT_EQ(-3.0, lrint_helper(T(-3), FE_UPWARD));
}

template <typename T>
void LRIntTestUnsignedInt(void)
{
	EXPECT_EQ( 0.0, lrint_helper(T( 0), FE_DOWNWARD));
	EXPECT_EQ( 2.0, lrint_helper(T( 2), FE_DOWNWARD));
	EXPECT_EQ( 3.0, lrint_helper(T( 3), FE_DOWNWARD));

	EXPECT_EQ( 0.0, lrint_helper(T( 0), FE_TONEAREST));
	EXPECT_EQ( 2.0, lrint_helper(T( 2), FE_TONEAREST));
	EXPECT_EQ( 3.0, lrint_helper(T( 3), FE_TONEAREST));

	EXPECT_EQ( 0.0, lrint_helper(T( 0), FE_TOWARDZERO));
	EXPECT_EQ( 2.0, lrint_helper(T( 2), FE_TOWARDZERO));
	EXPECT_EQ( 3.0, lrint_helper(T( 3), FE_TOWARDZERO));

	EXPECT_EQ( 0.0, lrint_helper(T( 0), FE_UPWARD));
	EXPECT_EQ( 2.0, lrint_helper(T( 2), FE_UPWARD));
	EXPECT_EQ( 3.0, lrint_helper(T( 3), FE_UPWARD));
}

GTEST_TEST(CMathTest, LRIntTest)
{
	LRIntTestFloat<float>();
	LRIntTestFloat<double>();
	LRIntTestFloat<long double>();

	LRIntTestSignedInt<int>();
//	LRIntTestSignedInt<signed char>();
	LRIntTestSignedInt<short>();
//	LRIntTestSignedInt<long>();
	LRIntTestSignedInt<long long>();

//	LRIntTestUnsignedInt<unsigned int>();
	LRIntTestUnsignedInt<unsigned char>();
//	LRIntTestUnsignedInt<unsigned short>();
	LRIntTestUnsignedInt<unsigned long>();
//	LRIntTestUnsignedInt<unsigned long long>();
}

}	// namespace lrint_test

}	// namespace bksge_cmath_test
