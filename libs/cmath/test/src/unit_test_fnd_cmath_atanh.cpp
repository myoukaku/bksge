/**
 *	@file	unit_test_fnd_cmath_atanh.cpp
 *
 *	@brief	atanh のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/atanh.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace atanh_test
{

static_assert(bksge::is_same<float,       decltype(bksge::atanh(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::atanhf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::atanh(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::atanh(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::atanh(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::atanhl(0.0l))>::value, "");

template <typename T>
void AtanhTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto eps = bksge::numeric_limits<T>::epsilon();

	EXPECT_NEAR( 0.0000000000000, (double)bksge::atanh(T( 0.0)), error);
	EXPECT_NEAR( 0.1003353477310, (double)bksge::atanh(T( 0.1)), error);
	EXPECT_NEAR( 0.2027325540540, (double)bksge::atanh(T( 0.2)), error);
	EXPECT_NEAR( 0.3095196042031, (double)bksge::atanh(T( 0.3)), error);
	EXPECT_NEAR( 0.5493061443340, (double)bksge::atanh(T( 0.5)), error);
	EXPECT_NEAR( 1.4722194895832, (double)bksge::atanh(T( 0.9)), error);
	EXPECT_NEAR( 2.6466524123622, (double)bksge::atanh(T( 0.99)), error);
	EXPECT_NEAR(-0.1003353477310, (double)bksge::atanh(T(-0.1)), error);
	EXPECT_NEAR(-0.2027325540540, (double)bksge::atanh(T(-0.2)), error);
	EXPECT_NEAR(-0.3095196042031, (double)bksge::atanh(T(-0.3)), error);
	EXPECT_NEAR(-0.5493061443340, (double)bksge::atanh(T(-0.5)), error);
	EXPECT_NEAR(-1.4722194895832, (double)bksge::atanh(T(-0.9)), error);
	EXPECT_NEAR(-2.6466524123622, (double)bksge::atanh(T(-0.99)), error);

	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::atanh(T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::atanh(T(-0.0)));

	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::atanh(T(+1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::atanh(T(-1.0)));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atanh(T(+1.0) + eps)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atanh(T(-1.0) - eps)));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atanh(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atanh(-nan)));
}

template <typename T>
void AtanhTestSignedInt(void)
{
	using R = bksge::float_promote_t<T>;
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<R>::infinity();

	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::atanh(T(0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::atanh(T(+1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::atanh(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atanh(T(+2))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atanh(T(-2))));
}

template <typename T>
void AtanhTestUnsignedInt(void)
{
	using R = bksge::float_promote_t<T>;
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<R>::infinity();

	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::atanh(T(0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::atanh(T(1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::atanh(T(2))));
}

GTEST_TEST(CMathTest, AtanhTest)
{
	AtanhTestFloat<float>(0.000001);
	AtanhTestFloat<double>(0.000000000001);
	AtanhTestFloat<long double>(0.000000000001);

	AtanhTestSignedInt<int>();
//	AtanhTestSignedInt<signed char>();
	AtanhTestSignedInt<short>();
//	AtanhTestSignedInt<long>();
	AtanhTestSignedInt<long long>();

	AtanhTestUnsignedInt<unsigned int>();
	AtanhTestUnsignedInt<unsigned char>();
//	AtanhTestUnsignedInt<unsigned short>();
	AtanhTestUnsignedInt<unsigned long>();
//	AtanhTestUnsignedInt<unsigned long long>();
}

}	// namespace atanh_test

}	// namespace bksge_cmath_test
