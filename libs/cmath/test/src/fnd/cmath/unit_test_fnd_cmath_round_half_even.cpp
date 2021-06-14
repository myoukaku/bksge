/**
 *	@file	unit_test_fnd_cmath_round_half_even.cpp
 *
 *	@brief	round_half_even のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/round_half_even.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace round_half_even_test
{

static_assert(bksge::is_same<float,       decltype(bksge::round_half_even(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::round_half_even(0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::round_half_even(0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::round_half_even(0   ))>::value, "");

template <typename T>
void RoundHalfEvenTestUnsigned(void)
{
	using bksge::round_half_even;

	BKSGE_CONSTEXPR_EXPECT_EQ((T)  0, round_half_even((T)  0));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  1, round_half_even((T)  1));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)100, round_half_even((T)100));
}

template <typename T>
void RoundHalfEvenTestSigned(void)
{
	using bksge::round_half_even;

	RoundHalfEvenTestUnsigned<T>();

	BKSGE_CONSTEXPR_EXPECT_EQ((T)  -1, round_half_even((T)  -1));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  -3, round_half_even((T)  -3));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-100, round_half_even((T)-100));
}

template <typename T>
void RoundHalfEvenTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	using bksge::round_half_even;

	BKSGE_CONSTEXPR_EXPECT_EQ(T( 0.0), round_half_even(T( 0.0000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 0.0), round_half_even(T( 0.4999)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 0.0), round_half_even(T( 0.5000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 1.0), round_half_even(T( 0.5001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 1.0), round_half_even(T( 1.0000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 1.0), round_half_even(T( 1.4999)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 2.0), round_half_even(T( 1.5000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 2.0), round_half_even(T( 1.5001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 2.0), round_half_even(T( 2.0000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 2.0), round_half_even(T( 2.4999)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 2.0), round_half_even(T( 2.5000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 3.0), round_half_even(T( 2.5001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T( 0.0), round_half_even(T(-0.4999)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-0.0), round_half_even(T(-0.5000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-1.0), round_half_even(T(-0.5001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-1.0), round_half_even(T(-1.0000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-1.0), round_half_even(T(-1.4999)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-2.0), round_half_even(T(-1.5000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-2.0), round_half_even(T(-1.5001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-2.0), round_half_even(T(-2.0000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-2.0), round_half_even(T(-2.4999)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-2.0), round_half_even(T(-2.5000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-3.0), round_half_even(T(-2.5001)));

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isinf  (round_half_even(+inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isinf  (round_half_even(-inf)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(round_half_even(+inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::signbit(round_half_even(-inf)));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(round_half_even(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(round_half_even(-nan)));
}

GTEST_TEST(CMathTest, RoundHalfEvenTest)
{
//	RoundHalfEvenTestUnsigned<unsigned char>();
	RoundHalfEvenTestUnsigned<unsigned short>();
//	RoundHalfEvenTestUnsigned<unsigned int>();
	RoundHalfEvenTestUnsigned<unsigned long>();
//	RoundHalfEvenTestUnsigned<unsigned long long>();

	RoundHalfEvenTestSigned<signed char>();
//	RoundHalfEvenTestSigned<signed short>();
	RoundHalfEvenTestSigned<signed int>();
//	RoundHalfEvenTestSigned<signed long>();
	RoundHalfEvenTestSigned<signed long long>();

	RoundHalfEvenTestFloat<float>();
	RoundHalfEvenTestFloat<double>();
	RoundHalfEvenTestFloat<long double>();
}

}	// namespace round_half_even_test

}	// namespace bksge_cmath_test
