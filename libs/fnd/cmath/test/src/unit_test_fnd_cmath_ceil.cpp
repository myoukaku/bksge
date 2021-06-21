/**
 *	@file	unit_test_fnd_cmath_ceil.cpp
 *
 *	@brief	ceil のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/ceil.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace ceil_test
{

static_assert(bksge::is_same<float,       decltype(bksge::ceil(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::ceilf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::ceil(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::ceil(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::ceil(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::ceill(0.0l))>::value, "");

template <typename T>
void CeilTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto eps = std::numeric_limits<T>::epsilon() * 2;

	BKSGE_CONSTEXPR_EXPECT_EQ((T)  0.0,  bksge::ceil(T(0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  1.0,  bksge::ceil(T(0.0) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  0.0,  bksge::ceil(T(0.0) - eps));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::ceil(T(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::ceil(T(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::ceil(T(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::ceil(T(-0.0))));

	BKSGE_CONSTEXPR_EXPECT_EQ((T)  1.0,  bksge::ceil(T(1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  2.0,  bksge::ceil(T(1.0) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  1.0,  bksge::ceil(T(1.0) - eps));

	BKSGE_CONSTEXPR_EXPECT_EQ((T) -1.0,  bksge::ceil(T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  0.0,  bksge::ceil(T(-1.0) + eps));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) -1.0,  bksge::ceil(T(-1.0) - eps));

	BKSGE_CONSTEXPR_EXPECT_EQ((T) 10.0,  bksge::ceil(T(10.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 11.0,  bksge::ceil(T(10.0) + (eps*10)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 10.0,  bksge::ceil(T(10.0) - (eps*10)));

	BKSGE_CONSTEXPR_EXPECT_EQ((T)-10.0,  bksge::ceil(T(-10.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) -9.0,  bksge::ceil(T(-10.0) + (eps*10)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-10.0,  bksge::ceil(T(-10.0) - (eps*10)));

	BKSGE_CONSTEXPR_EXPECT_EQ((T) 1000.0,  bksge::ceil(T(1000.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 1001.0,  bksge::ceil(T(1000.0) + (eps*1000)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 1000.0,  bksge::ceil(T(1000.0) - (eps*1000)));

	BKSGE_CONSTEXPR_EXPECT_EQ((T)-1000.0,  bksge::ceil(T(-1000.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) -999.0,  bksge::ceil(T(-1000.0) + (eps*1000)));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-1000.0,  bksge::ceil(T(-1000.0) - (eps*1000)));

	BKSGE_CONSTEXPR_EXPECT_EQ( inf,  bksge::ceil(+inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf,  bksge::ceil(-inf));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::ceil(+inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::signbit(bksge::ceil(-inf)));

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan  (bksge::ceil(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan  (bksge::ceil(-nan)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::ceil(+nan)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::ceil(-nan)));
}

template <typename T>
void CeilTestSignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ((T)   0, bksge::ceil((T)   0));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)   1, bksge::ceil((T)   1));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  -1, bksge::ceil((T)  -1));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)   3, bksge::ceil((T)   3));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  -3, bksge::ceil((T)  -3));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 100, bksge::ceil((T) 100));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-100, bksge::ceil((T)-100));
}

template <typename T>
void CeilTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  0, bksge::ceil((T)  0));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  1, bksge::ceil((T)  1));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)100, bksge::ceil((T)100));
}

GTEST_TEST(CMathTest, CeilTest)
{
	CeilTestFloat<float>();
	CeilTestFloat<double>();
	CeilTestFloat<long double>();

	CeilTestSignedInt<int>();
//	CeilTestSignedInt<signed char>();
	CeilTestSignedInt<short>();
//	CeilTestSignedInt<long>();
	CeilTestSignedInt<long long>();

	CeilTestUnsignedInt<unsigned int>();
	CeilTestUnsignedInt<unsigned char>();
//	CeilTestUnsignedInt<unsigned short>();
	CeilTestUnsignedInt<unsigned long>();
//	CeilTestUnsignedInt<unsigned long long>();
}

}	// namespace ceil_test

}	// namespace bksge_cmath_test
