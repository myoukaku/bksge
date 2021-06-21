/**
 *	@file	unit_test_fnd_cmath_is_integer.cpp
 *
 *	@brief	is_integer のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/is_integer.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace is_integer_test
{

static_assert(bksge::is_same<bool, decltype(bksge::is_integer(0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::is_integer(0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::is_integer(0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::is_integer(0   ))>::value, "");

template <typename T>
void IsIntegerTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(T(-4.1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_integer(T(-4.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(T(-3.9)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(T(-3.1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_integer(T(-3.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(T(-2.9)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(T(-2.2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(T(-2.1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_integer(T(-2.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(T(-1.9)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(T(-1.1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_integer(T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(T(-0.9)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(T(-0.1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_integer(T(-0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_integer(T( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(T( 0.1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(T( 0.9)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_integer(T( 1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(T( 1.1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(T( 1.9)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_integer(T( 2.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(T( 2.1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(T( 2.2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(T( 2.9)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_integer(T( 3.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(T( 3.1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(T( 3.9)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_integer(T( 4.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(T( 4.1)));

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer( nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(-nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer( inf));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_integer(-inf));
}

template <typename T>
void IsIntegerTestSignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::is_integer(T(-3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::is_integer(T(-2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::is_integer(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::is_integer(T( 0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::is_integer(T( 1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::is_integer(T( 2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::is_integer(T( 3)));
}

template <typename T>
void IsIntegerTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::is_integer(T(0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::is_integer(T(1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::is_integer(T(2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::is_integer(T(3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::is_integer(T(4)));
}

GTEST_TEST(CMathTest, IsIntegerTest)
{
	IsIntegerTestFloat<float>();
	IsIntegerTestFloat<double>();
	IsIntegerTestFloat<long double>();

	IsIntegerTestSignedInt<int>();
//	IsIntegerTestSignedInt<signed char>();
	IsIntegerTestSignedInt<short>();
//	IsIntegerTestSignedInt<long>();
	IsIntegerTestSignedInt<long long>();

//	IsIntegerTestUnsignedInt<unsigned int>();
	IsIntegerTestUnsignedInt<unsigned char>();
//	IsIntegerTestUnsignedInt<unsigned short>();
	IsIntegerTestUnsignedInt<unsigned long>();
//	IsIntegerTestUnsignedInt<unsigned long long>();
}

}	// namespace is_integer_test

}	// namespace bksge_cmath_test
