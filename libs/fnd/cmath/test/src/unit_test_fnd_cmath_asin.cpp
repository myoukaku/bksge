/**
 *	@file	unit_test_fnd_cmath_asin.cpp
 *
 *	@brief	asin のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/asin.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace asin_test
{

static_assert(bksge::is_same<float,       decltype(bksge::asin(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::asinf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::asin(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::asin(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::asin(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::asinl(0.0l))>::value, "");

template <typename T>
void AsinTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto eps = bksge::numeric_limits<T>::epsilon();

	EXPECT_NEAR(-1.5707963267949, (double)bksge::asin(T(-1.00)), error);
	EXPECT_NEAR(-0.8480620789814, (double)bksge::asin(T(-0.75)), error);
	EXPECT_NEAR(-0.5235987755983, (double)bksge::asin(T(-0.50)), error);
	EXPECT_NEAR(-0.2526802551420, (double)bksge::asin(T(-0.25)), error);
	EXPECT_NEAR( 0.0000000000000, (double)bksge::asin(T( 0.00)), error);
	EXPECT_NEAR( 0.2526802551420, (double)bksge::asin(T( 0.25)), error);
	EXPECT_NEAR( 0.5235987755983, (double)bksge::asin(T( 0.50)), error);
	EXPECT_NEAR( 0.8480620789814, (double)bksge::asin(T( 0.75)), error);
	EXPECT_NEAR( 1.5707963267949, (double)bksge::asin(T( 1.00)), error);

	BKSGE_CONSTEXPR_EXPECT_EQ( 0.0, bksge::asin(T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0.0, bksge::asin(T(-0.0)));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::asin(T(+1.0) + eps)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::asin(T(-1.0) - eps)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::asin(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::asin(-nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::asin(+inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::asin(-inf)));
}

template <typename T>
void AsinTestSignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.000000000001;

	EXPECT_NEAR( 0.0000000000000, bksge::asin(T( 0)), error);
	EXPECT_NEAR( 1.5707963267949, bksge::asin(T( 1)), error);
	EXPECT_NEAR(-1.5707963267949, bksge::asin(T(-1)), error);

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::asin(T( 2))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::asin(T(-2))));
}

template <typename T>
void AsinTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.000000000001;

	EXPECT_NEAR(0.0000000000000, bksge::asin(T( 0)), error);
	EXPECT_NEAR(1.5707963267949, bksge::asin(T( 1)), error);

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::asin(T( 2))));
}

GTEST_TEST(CMathTest, AsinTest)
{
	AsinTestFloat<float>(0.000001);
	AsinTestFloat<double>(0.000000000001);
	AsinTestFloat<long double>(0.000000000001);

	AsinTestSignedInt<int>();
//	AsinTestSignedInt<signed char>();
	AsinTestSignedInt<short>();
//	AsinTestSignedInt<long>();
	AsinTestSignedInt<long long>();

	AsinTestUnsignedInt<unsigned int>();
	AsinTestUnsignedInt<unsigned char>();
//	AsinTestUnsignedInt<unsigned short>();
	AsinTestUnsignedInt<unsigned long>();
//	AsinTestUnsignedInt<unsigned long long>();
}

}	// namespace asin_test

}	// namespace bksge_cmath_test
