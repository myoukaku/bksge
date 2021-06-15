/**
 *	@file	unit_test_fnd_cmath_round.cpp
 *
 *	@brief	round のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/round.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace round_test
{

static_assert(bksge::is_same<float,       decltype(bksge::round(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::round(0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::round(0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::round(0   ))>::value, "");

template <typename T>
void RoundTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto eps = bksge::numeric_limits<T>::epsilon() * 2;

	BKSGE_CONSTEXPR_EXPECT_EQ((T)-2.0,  bksge::round(T(-1.5) - eps));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-2.0,  bksge::round(T(-1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-1.0,  bksge::round(T(-1.5) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-1.0,  bksge::round(T(-0.5) - eps));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-1.0,  bksge::round(T(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 0.0,  bksge::round(T(-0.5) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 0.0,  bksge::round(T( 0.0) - eps));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 0.0,  bksge::round(T( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 0.0,  bksge::round(T( 0.0) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 0.0,  bksge::round(T( 0.5) - eps));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 1.0,  bksge::round(T( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 1.0,  bksge::round(T( 0.5) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 1.0,  bksge::round(T( 1.5) - eps));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 2.0,  bksge::round(T( 1.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 2.0,  bksge::round(T( 1.5) + eps));

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::round(T(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::round(T(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::round(T(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::round(T(-0.0))));

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isinf  (bksge::round(+inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isinf  (bksge::round(-inf)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::round(+inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::signbit(bksge::round(-inf)));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::round(-nan)));
}

template <typename T>
void RoundTestSignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ((T)   0, bksge::round((T)   0));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)   1, bksge::round((T)   1));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  -1, bksge::round((T)  -1));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)   3, bksge::round((T)   3));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  -3, bksge::round((T)  -3));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 100, bksge::round((T) 100));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-100, bksge::round((T)-100));
}

template <typename T>
void RoundTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  0, bksge::round((T)  0));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  1, bksge::round((T)  1));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  3, bksge::round((T)  3));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)100, bksge::round((T)100));
}

GTEST_TEST(CMathTest, RoundTest)
{
	RoundTestFloat<float>();
	RoundTestFloat<double>();
	RoundTestFloat<long double>();

//	RoundTestSignedInt<int>();
	RoundTestSignedInt<signed char>();
//	RoundTestSignedInt<short>();
	RoundTestSignedInt<long>();
//	RoundTestSignedInt<long long>();

	RoundTestUnsignedInt<unsigned int>();
//	RoundTestUnsignedInt<unsigned char>();
	RoundTestUnsignedInt<unsigned short>();
//	RoundTestUnsignedInt<unsigned long>();
	RoundTestUnsignedInt<unsigned long long>();
}

}	// namespace round_test

}	// namespace bksge_cmath_test
