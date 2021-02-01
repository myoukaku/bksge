/**
 *	@file	unit_test_fnd_cmath_lround.cpp
 *
 *	@brief	lround のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/lround.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace lround_test
{

static_assert(bksge::is_same<long, decltype(bksge::lround(0.0f))>::value, "");
static_assert(bksge::is_same<long, decltype(bksge::lroundf(0.0f))>::value, "");
static_assert(bksge::is_same<long, decltype(bksge::lround(0.0 ))>::value, "");
static_assert(bksge::is_same<long, decltype(bksge::lround(0.0l))>::value, "");
static_assert(bksge::is_same<long, decltype(bksge::lroundl(0.0l))>::value, "");
static_assert(bksge::is_same<long, decltype(bksge::lround(0   ))>::value, "");

template <typename T>
void LRoundTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto min = bksge::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max = bksge::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto eps = bksge::numeric_limits<T>::epsilon() * 2;

	BKSGE_CONSTEXPR auto lmin = bksge::numeric_limits<long>::lowest();
	BKSGE_CONSTEXPR auto lmax = bksge::numeric_limits<long>::max();

	BKSGE_CONSTEXPR_EXPECT_EQ(-2L,  bksge::lround(T(-1.5) - eps));
	BKSGE_CONSTEXPR_EXPECT_EQ(-2L,  bksge::lround(T(-1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1L,  bksge::lround(T(-1.5) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1L,  bksge::lround(T(-0.5) - eps));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1L,  bksge::lround(T(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0L,  bksge::lround(T(-0.5) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0L,  bksge::lround(T( 0.0) - eps));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0L,  bksge::lround(T( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0L,  bksge::lround(T( 0.0) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0L,  bksge::lround(T( 0.5) - eps));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1L,  bksge::lround(T( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1L,  bksge::lround(T( 0.5) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1L,  bksge::lround(T( 1.5) - eps));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2L,  bksge::lround(T( 1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2L,  bksge::lround(T( 1.5) + eps));

	BKSGE_CONSTEXPR_EXPECT_EQ(lmin, bksge::lround(min));
	BKSGE_CONSTEXPR_EXPECT_EQ(lmax, bksge::lround(max));
	BKSGE_CONSTEXPR_EXPECT_EQ(lmin, bksge::lround(-inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(lmax, bksge::lround(+inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(lmin, bksge::lround(nan));
}

template <typename T>
void LRoundTestSignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(   0L, bksge::lround((T)   0));
	BKSGE_CONSTEXPR_EXPECT_EQ(   1L, bksge::lround((T)   1));
	BKSGE_CONSTEXPR_EXPECT_EQ(  -1L, bksge::lround((T)  -1));
	BKSGE_CONSTEXPR_EXPECT_EQ(   3L, bksge::lround((T)   3));
	BKSGE_CONSTEXPR_EXPECT_EQ(  -3L, bksge::lround((T)  -3));
	BKSGE_CONSTEXPR_EXPECT_EQ( 100L, bksge::lround((T) 100));
	BKSGE_CONSTEXPR_EXPECT_EQ(-100L, bksge::lround((T)-100));
}

template <typename T>
void LRoundTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(  0L, bksge::lround((T)  0));
	BKSGE_CONSTEXPR_EXPECT_EQ(  1L, bksge::lround((T)  1));
	BKSGE_CONSTEXPR_EXPECT_EQ(  3L, bksge::lround((T)  3));
	BKSGE_CONSTEXPR_EXPECT_EQ(100L, bksge::lround((T)100));
}

GTEST_TEST(CMathTest, LRoundTest)
{
	LRoundTestFloat<float>();
	LRoundTestFloat<double>();
	LRoundTestFloat<long double>();

//	LRoundTestSignedInt<int>();
	LRoundTestSignedInt<signed char>();
//	LRoundTestSignedInt<short>();
	LRoundTestSignedInt<long>();
//	LRoundTestSignedInt<long long>();

	LRoundTestUnsignedInt<unsigned int>();
//	LRoundTestUnsignedInt<unsigned char>();
	LRoundTestUnsignedInt<unsigned short>();
//	LRoundTestUnsignedInt<unsigned long>();
	LRoundTestUnsignedInt<unsigned long long>();
}

}	// namespace lround_test

}	// namespace bksge_cmath_test
