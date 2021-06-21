/**
 *	@file	unit_test_fnd_cmath_llrint.cpp
 *
 *	@brief	llrint のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/llrint.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <cfenv>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace llrint_test
{

static_assert(bksge::is_same<long long, decltype(bksge::llrint(0.0f))>::value, "");
static_assert(bksge::is_same<long long, decltype(bksge::llrintf(0.0f))>::value, "");
static_assert(bksge::is_same<long long, decltype(bksge::llrint(0.0 ))>::value, "");
static_assert(bksge::is_same<long long, decltype(bksge::llrint(0   ))>::value, "");
static_assert(bksge::is_same<long long, decltype(bksge::llrint(0.0l))>::value, "");
static_assert(bksge::is_same<long long, decltype(bksge::llrintl(0.0l))>::value, "");

template <typename T>
inline long long llrint_helper(T x, int round_mode)
{
	auto current = std::fegetround();
	std::fesetround(round_mode);
	auto ret = bksge::llrint(x);
	std::fesetround(current);
	return ret;
}

template <typename T>
void LLRIntTestFloat(void)
{
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto llmax = std::numeric_limits<long long>::max();
	BKSGE_CONSTEXPR auto llmin = std::numeric_limits<long long>::min();

	EXPECT_EQ(T( 0.0), llrint_helper(T( 0.0), FE_DOWNWARD));
	EXPECT_EQ(T( 2.0), llrint_helper(T( 2.5), FE_DOWNWARD));
	EXPECT_EQ(T(-3.0), llrint_helper(T(-2.5), FE_DOWNWARD));
	EXPECT_EQ(T( 3.0), llrint_helper(T( 3.5), FE_DOWNWARD));
	EXPECT_EQ(T(-4.0), llrint_helper(T(-3.5), FE_DOWNWARD));
	EXPECT_EQ(llmax,   llrint_helper(+inf,    FE_DOWNWARD));
	EXPECT_EQ(llmin,   llrint_helper(-inf,    FE_DOWNWARD));
	EXPECT_EQ(T( 0.0), llrint_helper(nan,     FE_DOWNWARD));

	EXPECT_EQ(T( 0.0), llrint_helper(T( 0.0), FE_TONEAREST));
	EXPECT_EQ(T( 2.0), llrint_helper(T( 2.5), FE_TONEAREST));
	EXPECT_EQ(T(-2.0), llrint_helper(T(-2.5), FE_TONEAREST));
	EXPECT_EQ(T( 4.0), llrint_helper(T( 3.5), FE_TONEAREST));
	EXPECT_EQ(T(-4.0), llrint_helper(T(-3.5), FE_TONEAREST));
	EXPECT_EQ(llmax,   llrint_helper(+inf,    FE_TONEAREST));
	EXPECT_EQ(llmin,   llrint_helper(-inf,    FE_TONEAREST));
	EXPECT_EQ(T( 0.0), llrint_helper(nan,     FE_TONEAREST));

	EXPECT_EQ(T( 0.0), llrint_helper(T( 0.0), FE_TOWARDZERO));
	EXPECT_EQ(T( 2.0), llrint_helper(T( 2.5), FE_TOWARDZERO));
	EXPECT_EQ(T(-2.0), llrint_helper(T(-2.5), FE_TOWARDZERO));
	EXPECT_EQ(T( 3.0), llrint_helper(T( 3.5), FE_TOWARDZERO));
	EXPECT_EQ(T(-3.0), llrint_helper(T(-3.5), FE_TOWARDZERO));
	EXPECT_EQ(llmax,   llrint_helper(+inf,    FE_TOWARDZERO));
	EXPECT_EQ(llmin,   llrint_helper(-inf,    FE_TOWARDZERO));
	EXPECT_EQ(T( 0.0), llrint_helper(nan,     FE_TOWARDZERO));

	EXPECT_EQ(T( 0.0), llrint_helper(T( 0.0), FE_UPWARD));
	EXPECT_EQ(T( 3.0), llrint_helper(T( 2.5), FE_UPWARD));
	EXPECT_EQ(T(-2.0), llrint_helper(T(-2.5), FE_UPWARD));
	EXPECT_EQ(T( 4.0), llrint_helper(T( 3.5), FE_UPWARD));
	EXPECT_EQ(T(-3.0), llrint_helper(T(-3.5), FE_UPWARD));
	EXPECT_EQ(llmax,   llrint_helper(+inf,    FE_UPWARD));
	EXPECT_EQ(llmin,   llrint_helper(-inf,    FE_UPWARD));
	EXPECT_EQ(T( 0.0), llrint_helper(nan,     FE_UPWARD));
}

template <typename T>
void LLRIntTestSignedInt(void)
{
	EXPECT_EQ( 0.0, llrint_helper(T( 0), FE_DOWNWARD));
	EXPECT_EQ( 2.0, llrint_helper(T( 2), FE_DOWNWARD));
	EXPECT_EQ(-2.0, llrint_helper(T(-2), FE_DOWNWARD));
	EXPECT_EQ( 3.0, llrint_helper(T( 3), FE_DOWNWARD));
	EXPECT_EQ(-3.0, llrint_helper(T(-3), FE_DOWNWARD));

	EXPECT_EQ( 0.0, llrint_helper(T( 0), FE_TONEAREST));
	EXPECT_EQ( 2.0, llrint_helper(T( 2), FE_TONEAREST));
	EXPECT_EQ(-2.0, llrint_helper(T(-2), FE_TONEAREST));
	EXPECT_EQ( 3.0, llrint_helper(T( 3), FE_TONEAREST));
	EXPECT_EQ(-3.0, llrint_helper(T(-3), FE_TONEAREST));

	EXPECT_EQ( 0.0, llrint_helper(T( 0), FE_TOWARDZERO));
	EXPECT_EQ( 2.0, llrint_helper(T( 2), FE_TOWARDZERO));
	EXPECT_EQ(-2.0, llrint_helper(T(-2), FE_TOWARDZERO));
	EXPECT_EQ( 3.0, llrint_helper(T( 3), FE_TOWARDZERO));
	EXPECT_EQ(-3.0, llrint_helper(T(-3), FE_TOWARDZERO));

	EXPECT_EQ( 0.0, llrint_helper(T( 0), FE_UPWARD));
	EXPECT_EQ( 2.0, llrint_helper(T( 2), FE_UPWARD));
	EXPECT_EQ(-2.0, llrint_helper(T(-2), FE_UPWARD));
	EXPECT_EQ( 3.0, llrint_helper(T( 3), FE_UPWARD));
	EXPECT_EQ(-3.0, llrint_helper(T(-3), FE_UPWARD));
}

template <typename T>
void LLRIntTestUnsignedInt(void)
{
	EXPECT_EQ( 0.0, llrint_helper(T( 0), FE_DOWNWARD));
	EXPECT_EQ( 2.0, llrint_helper(T( 2), FE_DOWNWARD));
	EXPECT_EQ( 3.0, llrint_helper(T( 3), FE_DOWNWARD));

	EXPECT_EQ( 0.0, llrint_helper(T( 0), FE_TONEAREST));
	EXPECT_EQ( 2.0, llrint_helper(T( 2), FE_TONEAREST));
	EXPECT_EQ( 3.0, llrint_helper(T( 3), FE_TONEAREST));

	EXPECT_EQ( 0.0, llrint_helper(T( 0), FE_TOWARDZERO));
	EXPECT_EQ( 2.0, llrint_helper(T( 2), FE_TOWARDZERO));
	EXPECT_EQ( 3.0, llrint_helper(T( 3), FE_TOWARDZERO));

	EXPECT_EQ( 0.0, llrint_helper(T( 0), FE_UPWARD));
	EXPECT_EQ( 2.0, llrint_helper(T( 2), FE_UPWARD));
	EXPECT_EQ( 3.0, llrint_helper(T( 3), FE_UPWARD));
}

GTEST_TEST(CMathTest, LLRIntTest)
{
	LLRIntTestFloat<float>();
	LLRIntTestFloat<double>();
	LLRIntTestFloat<long double>();

	LLRIntTestSignedInt<int>();
//	LLRIntTestSignedInt<signed char>();
	LLRIntTestSignedInt<short>();
//	LLRIntTestSignedInt<long>();
	LLRIntTestSignedInt<long long>();

//	LLRIntTestUnsignedInt<unsigned int>();
	LLRIntTestUnsignedInt<unsigned char>();
//	LLRIntTestUnsignedInt<unsigned short>();
	LLRIntTestUnsignedInt<unsigned long>();
//	LLRIntTestUnsignedInt<unsigned long long>();
}

}	// namespace llrint_test

}	// namespace bksge_cmath_test
