/**
 *	@file	unit_test_fnd_cmath_llround.cpp
 *
 *	@brief	llround のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/llround.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace llround_test
{

static_assert(bksge::is_same<long long, decltype(bksge::llround(0.0f))>::value, "");
static_assert(bksge::is_same<long long, decltype(bksge::llroundf(0.0f))>::value, "");
static_assert(bksge::is_same<long long, decltype(bksge::llround(0.0 ))>::value, "");
static_assert(bksge::is_same<long long, decltype(bksge::llround(0.0l))>::value, "");
static_assert(bksge::is_same<long long, decltype(bksge::llroundl(0.0l))>::value, "");
static_assert(bksge::is_same<long long, decltype(bksge::llround(0   ))>::value, "");

template <typename T>
void LLRoundTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto eps = std::numeric_limits<T>::epsilon() * 2;

	BKSGE_CONSTEXPR auto llmin = std::numeric_limits<long long>::lowest();
	BKSGE_CONSTEXPR auto llmax = std::numeric_limits<long long>::max();

	BKSGE_CONSTEXPR_EXPECT_EQ(-2L,  bksge::llround(T(-1.5) - eps));
	BKSGE_CONSTEXPR_EXPECT_EQ(-2L,  bksge::llround(T(-1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1L,  bksge::llround(T(-1.5) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1L,  bksge::llround(T(-0.5) - eps));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1L,  bksge::llround(T(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0L,  bksge::llround(T(-0.5) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0L,  bksge::llround(T( 0.0) - eps));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0L,  bksge::llround(T( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0L,  bksge::llround(T( 0.0) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0L,  bksge::llround(T( 0.5) - eps));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1L,  bksge::llround(T( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1L,  bksge::llround(T( 0.5) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1L,  bksge::llround(T( 1.5) - eps));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2L,  bksge::llround(T( 1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2L,  bksge::llround(T( 1.5) + eps));

	BKSGE_CONSTEXPR_EXPECT_EQ(llmin, bksge::llround(min));
	BKSGE_CONSTEXPR_EXPECT_EQ(llmax, bksge::llround(max));
	BKSGE_CONSTEXPR_EXPECT_EQ(llmin, bksge::llround(-inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(llmax, bksge::llround(+inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(llmin, bksge::llround(nan));
}

template <typename T>
void LLRoundTestSignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(   0L, bksge::llround((T)   0));
	BKSGE_CONSTEXPR_EXPECT_EQ(   1L, bksge::llround((T)   1));
	BKSGE_CONSTEXPR_EXPECT_EQ(  -1L, bksge::llround((T)  -1));
	BKSGE_CONSTEXPR_EXPECT_EQ(   3L, bksge::llround((T)   3));
	BKSGE_CONSTEXPR_EXPECT_EQ(  -3L, bksge::llround((T)  -3));
	BKSGE_CONSTEXPR_EXPECT_EQ( 100L, bksge::llround((T) 100));
	BKSGE_CONSTEXPR_EXPECT_EQ(-100L, bksge::llround((T)-100));
}

template <typename T>
void LLRoundTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(  0L, bksge::llround((T)  0));
	BKSGE_CONSTEXPR_EXPECT_EQ(  1L, bksge::llround((T)  1));
	BKSGE_CONSTEXPR_EXPECT_EQ(  3L, bksge::llround((T)  3));
	BKSGE_CONSTEXPR_EXPECT_EQ(100L, bksge::llround((T)100));
}

GTEST_TEST(CMathTest, LLRoundTest)
{
	LLRoundTestFloat<float>();
	LLRoundTestFloat<double>();
	LLRoundTestFloat<long double>();

//	LLRoundTestSignedInt<int>();
	LLRoundTestSignedInt<signed char>();
//	LLRoundTestSignedInt<short>();
	LLRoundTestSignedInt<long>();
//	LLRoundTestSignedInt<long long>();

	LLRoundTestUnsignedInt<unsigned int>();
//	LLRoundTestUnsignedInt<unsigned char>();
	LLRoundTestUnsignedInt<unsigned short>();
//	LLRoundTestUnsignedInt<unsigned long>();
	LLRoundTestUnsignedInt<unsigned long long>();
}

}	// namespace llround_test

}	// namespace bksge_cmath_test
