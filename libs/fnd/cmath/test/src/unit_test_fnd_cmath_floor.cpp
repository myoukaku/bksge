﻿/**
 *	@file	unit_test_fnd_cmath_floor.cpp
 *
 *	@brief	floor のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/floor.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace floor_test
{

static_assert(bksge::is_same<float,       decltype(bksge::floor(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::floorf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::floor(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::floor(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::floor(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::floorl(0.0l))>::value, "");

template <typename T>
void FloorTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto eps = std::numeric_limits<T>::epsilon() * 2;

	BKSGE_CONSTEXPR_EXPECT_EQ((T)  0.0,  bksge::floor(T(0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  0.0,  bksge::floor(T(0.0) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) -1.0,  bksge::floor(T(0.0) - eps));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::floor(T(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::floor(T(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::floor(T(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::floor(T(-0.0))));

	BKSGE_CONSTEXPR_EXPECT_EQ((T)  1.0,  bksge::floor(T(1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  1.0,  bksge::floor(T(1.0) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  0.0,  bksge::floor(T(1.0) - eps));

	BKSGE_CONSTEXPR_EXPECT_EQ((T) -1.0,  bksge::floor(T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) -1.0,  bksge::floor(T(-1.0) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) -2.0,  bksge::floor(T(-1.0) - eps));

	BKSGE_CONSTEXPR_EXPECT_EQ((T) 10.0,  bksge::floor(T(10.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 10.0,  bksge::floor(T(10.0) + (eps*10)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  9.0,  bksge::floor(T(10.0) - (eps*10)));

	BKSGE_CONSTEXPR_EXPECT_EQ((T)-10.0,  bksge::floor(T(-10.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-10.0,  bksge::floor(T(-10.0) + (eps*10)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-11.0,  bksge::floor(T(-10.0) - (eps*10)));

	BKSGE_CONSTEXPR_EXPECT_EQ((T) 1000.0,  bksge::floor(T(1000.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 1000.0,  bksge::floor(T(1000.0) + (eps*1000)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  999.0,  bksge::floor(T(1000.0) - (eps*1000)));

	BKSGE_CONSTEXPR_EXPECT_EQ((T)-1000.0,  bksge::floor(T(-1000.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-1000.0,  bksge::floor(T(-1000.0) + (eps*1000)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-1001.0,  bksge::floor(T(-1000.0) - (eps*1000)));

	BKSGE_CONSTEXPR_EXPECT_EQ( inf,  bksge::floor(+inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf,  bksge::floor(-inf));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::floor(+inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::signbit(bksge::floor(-inf)));

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan  (bksge::floor(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan  (bksge::floor(-nan)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::floor(+nan)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::floor(-nan)));
}

template <typename T>
void FloorTestSignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ((T)   0, bksge::floor((T)   0));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)   1, bksge::floor((T)   1));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  -1, bksge::floor((T)  -1));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)   3, bksge::floor((T)   3));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  -3, bksge::floor((T)  -3));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 100, bksge::floor((T) 100));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-100, bksge::floor((T)-100));
}

template <typename T>
void FloorTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  0, bksge::floor((T)  0));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  1, bksge::floor((T)  1));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)100, bksge::floor((T)100));
}

GTEST_TEST(CMathTest, FloorTest)
{
	FloorTestFloat<float>();
	FloorTestFloat<double>();
	FloorTestFloat<long double>();

	FloorTestSignedInt<int>();
//	FloorTestSignedInt<signed char>();
	FloorTestSignedInt<short>();
//	FloorTestSignedInt<long>();
	FloorTestSignedInt<long long>();

	FloorTestUnsignedInt<unsigned int>();
	FloorTestUnsignedInt<unsigned char>();
//	FloorTestUnsignedInt<unsigned short>();
	FloorTestUnsignedInt<unsigned long>();
//	FloorTestUnsignedInt<unsigned long long>();
}

}	// namespace floor_test

}	// namespace bksge_cmath_test
