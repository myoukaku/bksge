/**
 *	@file	unit_test_fnd_cmath_is_negative.cpp
 *
 *	@brief	is_negative のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/is_negative.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace is_negative_test
{

static_assert(bksge::is_same<bool, decltype(bksge::is_negative(0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::is_negative(0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::is_negative(0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::is_negative(0   ))>::value, "");

template <typename T>
void IsNegativeTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_negative(T( 1.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_negative(T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_negative(T( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_negative(T(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_negative( inf));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_negative(-inf));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_negative(max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_negative(min));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_negative(lowest));

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_negative(T( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_negative(T(-0.0)));

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_negative( nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_negative(-nan));
}

template <typename T>
void IsNegativeTestSignedInt(void)
{
	BKSGE_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_negative(T( 0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_negative(T( 1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_negative(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_negative(T( 2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_negative(T(-2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_negative(max));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_negative(min));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_negative(lowest));
}

template <typename T>
void IsNegativeTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_negative(T( 0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_negative(T( 1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_negative(T( 2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_negative(max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_negative(min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_negative(lowest));
}

GTEST_TEST(CMathTest, IsNegativeTest)
{
	IsNegativeTestFloat<float>();
	IsNegativeTestFloat<double>();
	IsNegativeTestFloat<long double>();

//	IsNegativeTestSignedInt<int>();
	IsNegativeTestSignedInt<signed char>();
//	IsNegativeTestSignedInt<short>();
	IsNegativeTestSignedInt<long>();
//	IsNegativeTestSignedInt<long long>();

	IsNegativeTestUnsignedInt<unsigned int>();
//	IsNegativeTestUnsignedInt<unsigned char>();
	IsNegativeTestUnsignedInt<unsigned short>();
//	IsNegativeTestUnsignedInt<unsigned long>();
	IsNegativeTestUnsignedInt<unsigned long long>();
}

}	// namespace is_negative_test

}	// namespace bksge_cmath_test
