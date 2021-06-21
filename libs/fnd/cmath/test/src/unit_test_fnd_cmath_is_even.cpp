/**
 *	@file	unit_test_fnd_cmath_is_even.cpp
 *
 *	@brief	is_even のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/is_even.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace is_even_test
{

static_assert(bksge::is_same<bool, decltype(bksge::is_even(0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::is_even(0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::is_even(0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::is_even(0   ))>::value, "");

template <typename T>
void IsEvenTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T(-4.1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_even(T(-4.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T(-3.9)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T(-3.1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T(-3.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T(-2.9)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T(-2.2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T(-2.1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_even(T(-2.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T(-1.9)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T(-1.1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T(-0.9)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T(-0.1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_even(T(-0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_even(T( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T( 0.1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T( 0.9)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T( 1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T( 1.1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T( 1.9)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_even(T( 2.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T( 2.1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T( 2.2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T( 2.9)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T( 3.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T( 3.1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T( 3.9)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_even(T( 4.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T( 4.1)));

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even( nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(-nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even( inf));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(-inf));
}

template <typename T>
void IsEvenTestSignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T(-3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_even(T(-2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_even(T( 0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T( 1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_even(T( 2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T( 3)));
}

template <typename T>
void IsEvenTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_even(T(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T(1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_even(T(2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_even(T(3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_even(T(4)));
}

GTEST_TEST(CMathTest, IsEvenTest)
{
	IsEvenTestFloat<float>();
	IsEvenTestFloat<double>();
	IsEvenTestFloat<long double>();

//	IsEvenTestSignedInt<int>();
	IsEvenTestSignedInt<signed char>();
//	IsEvenTestSignedInt<short>();
	IsEvenTestSignedInt<long>();
//	IsEvenTestSignedInt<long long>();

	IsEvenTestUnsignedInt<unsigned int>();
//	IsEvenTestUnsignedInt<unsigned char>();
	IsEvenTestUnsignedInt<unsigned short>();
//	IsEvenTestUnsignedInt<unsigned long>();
	IsEvenTestUnsignedInt<unsigned long long>();
}

}	// namespace is_even_test

}	// namespace bksge_cmath_test
