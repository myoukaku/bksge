/**
 *	@file	unit_test_fnd_cmath_is_even.cpp
 *
 *	@brief	is_even のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/is_even.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace is_even_test
{

template <typename T>
void IsEvenTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

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
