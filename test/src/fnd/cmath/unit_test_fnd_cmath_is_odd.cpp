/**
 *	@file	unit_test_fnd_cmath_is_odd.cpp
 *
 *	@brief	is_odd のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/is_odd.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace is_odd_test
{

template <typename T>
void IsOddTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T(-4.1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T(-4.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T(-3.9)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T(-3.1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_odd(T(-3.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T(-2.9)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T(-2.2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T(-2.1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T(-2.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T(-1.9)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T(-1.1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_odd(T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T(-0.9)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T(-0.1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T(-0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T( 0.1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T( 0.9)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_odd(T( 1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T( 1.1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T( 1.9)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T( 2.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T( 2.1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T( 2.2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T( 2.9)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_odd(T( 3.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T( 3.1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T( 3.9)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T( 4.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T( 4.1)));

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd( nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(-nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd( inf));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(-inf));
}

template <typename T>
void IsOddTestSignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_odd(T(-3)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T(-2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_odd(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T( 0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_odd(T( 1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T( 2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_odd(T( 3)));
}

template <typename T>
void IsOddTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T(0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_odd(T(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T(2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_odd(T(3)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_odd(T(4)));
}

GTEST_TEST(CMathTest, IsOddTest)
{
	IsOddTestFloat<float>();
	IsOddTestFloat<double>();
	IsOddTestFloat<long double>();

	IsOddTestSignedInt<int>();
//	IsOddTestSignedInt<signed char>();
	IsOddTestSignedInt<short>();
//	IsOddTestSignedInt<long>();
	IsOddTestSignedInt<long long>();

//	IsOddTestUnsignedInt<unsigned int>();
	IsOddTestUnsignedInt<unsigned char>();
//	IsOddTestUnsignedInt<unsigned short>();
	IsOddTestUnsignedInt<unsigned long>();
//	IsOddTestUnsignedInt<unsigned long long>();
}

}	// namespace is_odd_test

}	// namespace bksge_cmath_test
