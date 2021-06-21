/**
 *	@file	unit_test_fnd_cmath_is_positive.cpp
 *
 *	@brief	is_positive のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/is_positive.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace is_positive_test
{

static_assert(bksge::is_same<bool, decltype(bksge::is_positive(0.0f))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::is_positive(0.0 ))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::is_positive(0.0l))>::value, "");
static_assert(bksge::is_same<bool, decltype(bksge::is_positive(0   ))>::value, "");

template <typename T>
void IsPositiveTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_positive(T( 1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_positive(T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_positive(T( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_positive(T(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_positive( inf));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_positive(-inf));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_positive(max));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_positive(min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_positive(lowest));

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_positive(T( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_positive(T(-0.0)));

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_positive( nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_positive(-nan));
}

template <typename T>
void IsPositiveTestSignedInt(void)
{
	BKSGE_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_positive(T( 0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_positive(T( 1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_positive(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_positive(T( 2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_positive(T(-2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_positive(max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_positive(min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_positive(lowest));
}

template <typename T>
void IsPositiveTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_positive(T( 0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_positive(T( 1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_positive(T( 2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::is_positive(max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_positive(min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::is_positive(lowest));
}

GTEST_TEST(CMathTest, IsPositiveTest)
{
	IsPositiveTestFloat<float>();
	IsPositiveTestFloat<double>();
	IsPositiveTestFloat<long double>();

//	IsPositiveTestSignedInt<int>();
	IsPositiveTestSignedInt<signed char>();
//	IsPositiveTestSignedInt<short>();
	IsPositiveTestSignedInt<long>();
//	IsPositiveTestSignedInt<long long>();

	IsPositiveTestUnsignedInt<unsigned int>();
//	IsPositiveTestUnsignedInt<unsigned char>();
	IsPositiveTestUnsignedInt<unsigned short>();
//	IsPositiveTestUnsignedInt<unsigned long>();
	IsPositiveTestUnsignedInt<unsigned long long>();
}

}	// namespace is_positive_test

}	// namespace bksge_cmath_test
