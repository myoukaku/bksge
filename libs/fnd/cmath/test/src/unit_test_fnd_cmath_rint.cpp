/**
 *	@file	unit_test_fnd_cmath_rint.cpp
 *
 *	@brief	rint のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/rint.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <gtest/gtest.h>
#include <cfenv>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace rint_test
{

static_assert(bksge::is_same<float,       decltype(bksge::rint(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::rintf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::rint(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::rint(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::rint(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::rintl(0.0l))>::value, "");

template <typename T>
void RIntTestFloat(void)
{
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();

	switch (std::fegetround())
	{
	case FE_DOWNWARD:
		EXPECT_EQ(T( 0.0), bksge::rint(T( 0.0)));
		EXPECT_EQ(T( 2.0), bksge::rint(T( 2.5)));
		EXPECT_EQ(T(-3.0), bksge::rint(T(-2.5)));
		EXPECT_EQ(T( 3.0), bksge::rint(T( 3.5)));
		EXPECT_EQ(T(-4.0), bksge::rint(T(-3.5)));
		break;
	case FE_TONEAREST:
		EXPECT_EQ(T( 0.0), bksge::rint(T( 0.0)));
		EXPECT_EQ(T( 2.0), bksge::rint(T( 2.5)));
		EXPECT_EQ(T(-2.0), bksge::rint(T(-2.5)));
		EXPECT_EQ(T( 4.0), bksge::rint(T( 3.5)));
		EXPECT_EQ(T(-4.0), bksge::rint(T(-3.5)));
		break;
	case FE_TOWARDZERO:
		EXPECT_EQ(T( 0.0), bksge::rint(T( 0.0)));
		EXPECT_EQ(T( 2.0), bksge::rint(T( 2.5)));
		EXPECT_EQ(T(-2.0), bksge::rint(T(-2.5)));
		EXPECT_EQ(T( 3.0), bksge::rint(T( 3.5)));
		EXPECT_EQ(T(-3.0), bksge::rint(T(-3.5)));
		break;
	case FE_UPWARD:
		EXPECT_EQ(T( 0.0), bksge::rint(T( 0.0)));
		EXPECT_EQ(T( 3.0), bksge::rint(T( 2.5)));
		EXPECT_EQ(T(-2.0), bksge::rint(T(-2.5)));
		EXPECT_EQ(T( 4.0), bksge::rint(T( 3.5)));
		EXPECT_EQ(T(-3.0), bksge::rint(T(-3.5)));
		break;
	}

	EXPECT_EQ(+inf, bksge::rint(+inf));
	EXPECT_EQ(-inf, bksge::rint(-inf));
	EXPECT_TRUE(bksge::isnan(bksge::rint(nan)));
}

template <typename T>
void RIntTestSignedInt(void)
{
	EXPECT_EQ( 0.0, bksge::rint(T( 0)));
	EXPECT_EQ( 2.0, bksge::rint(T( 2)));
	EXPECT_EQ(-2.0, bksge::rint(T(-2)));
	EXPECT_EQ( 3.0, bksge::rint(T( 3)));
	EXPECT_EQ(-3.0, bksge::rint(T(-3)));
}

template <typename T>
void RIntTestUnsignedInt(void)
{
	EXPECT_EQ( 0.0, bksge::rint(T( 0)));
	EXPECT_EQ( 2.0, bksge::rint(T( 2)));
	EXPECT_EQ( 3.0, bksge::rint(T( 3)));
}

GTEST_TEST(CMathTest, RIntTest)
{
	RIntTestFloat<float>();
	RIntTestFloat<double>();
	RIntTestFloat<long double>();

	RIntTestSignedInt<int>();
//	RIntTestSignedInt<signed char>();
	RIntTestSignedInt<short>();
//	RIntTestSignedInt<long>();
	RIntTestSignedInt<long long>();

//	RIntTestUnsignedInt<unsigned int>();
	RIntTestUnsignedInt<unsigned char>();
//	RIntTestUnsignedInt<unsigned short>();
	RIntTestUnsignedInt<unsigned long>();
//	RIntTestUnsignedInt<unsigned long long>();
}

}	// namespace rint_test

}	// namespace bksge_cmath_test
