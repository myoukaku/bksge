/**
 *	@file	unit_test_fnd_cmath_asinh.cpp
 *
 *	@brief	asinh のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/asinh.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace asinh_test
{

static_assert(bksge::is_same<float,       decltype(bksge::asinh(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::asinhf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::asinh(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::asinh(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::asinh(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::asinhl(0.0l))>::value, "");

template <typename T>
void AsinhTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	EXPECT_NEAR(-1.8184464592320, (double)bksge::asinh(T(-3.0)), error);
	EXPECT_NEAR(-1.6472311463710, (double)bksge::asinh(T(-2.5)), error);
	EXPECT_NEAR(-1.4436354751788, (double)bksge::asinh(T(-2.0)), error);
	EXPECT_NEAR(-1.1947632172871, (double)bksge::asinh(T(-1.5)), error);
	EXPECT_NEAR(-0.8813735870195, (double)bksge::asinh(T(-1.0)), error);
	EXPECT_NEAR(-0.4812118250596, (double)bksge::asinh(T(-0.5)), error);
	EXPECT_NEAR( 0.0000000000000, (double)bksge::asinh(T( 0.0)), error);
	EXPECT_NEAR( 0.4812118250596, (double)bksge::asinh(T( 0.5)), error);
	EXPECT_NEAR( 0.8813735870195, (double)bksge::asinh(T( 1.0)), error);
	EXPECT_NEAR( 1.1947632172871, (double)bksge::asinh(T( 1.5)), error);
	EXPECT_NEAR( 1.4436354751788, (double)bksge::asinh(T( 2.0)), error);
	EXPECT_NEAR( 1.6472311463710, (double)bksge::asinh(T( 2.5)), error);
	EXPECT_NEAR( 1.8184464592320, (double)bksge::asinh(T( 3.0)), error);

	BKSGE_CONSTEXPR_EXPECT_EQ( 0.0, bksge::asinh(T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0.0, bksge::asinh(T(-0.0)));

	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::asinh(+inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::asinh(-inf));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::asinh(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::asinh(-nan)));
}

template <typename T>
void AsinhTestSignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.000000000001;

	EXPECT_NEAR(-1.8184464592320, (double)bksge::asinh(T(-3)), error);
	EXPECT_NEAR(-1.4436354751788, (double)bksge::asinh(T(-2)), error);
	EXPECT_NEAR(-0.8813735870195, (double)bksge::asinh(T(-1)), error);
	EXPECT_NEAR( 0.0000000000000, (double)bksge::asinh(T( 0)), error);
	EXPECT_NEAR( 0.8813735870195, (double)bksge::asinh(T( 1)), error);
	EXPECT_NEAR( 1.4436354751788, (double)bksge::asinh(T( 2)), error);
	EXPECT_NEAR( 1.8184464592320, (double)bksge::asinh(T( 3)), error);
}

template <typename T>
void AsinhTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.000000000001;

	EXPECT_NEAR( 0.0000000000000, (double)bksge::asinh(T( 0)), error);
	EXPECT_NEAR( 0.8813735870195, (double)bksge::asinh(T( 1)), error);
	EXPECT_NEAR( 1.4436354751788, (double)bksge::asinh(T( 2)), error);
	EXPECT_NEAR( 1.8184464592320, (double)bksge::asinh(T( 3)), error);
}

GTEST_TEST(CMathTest, AsinhTest)
{
	AsinhTestFloat<float>(0.000001);
	AsinhTestFloat<double>(0.000000000001);
	AsinhTestFloat<long double>(0.000000000001);

	AsinhTestSignedInt<int>();
	AsinhTestSignedInt<signed char>();
//	AsinhTestSignedInt<short>();
	AsinhTestSignedInt<long>();
//	AsinhTestSignedInt<long long>();

	AsinhTestUnsignedInt<unsigned int>();
//	AsinhTestUnsignedInt<unsigned char>();
	AsinhTestUnsignedInt<unsigned short>();
//	AsinhTestUnsignedInt<unsigned long>();
	AsinhTestUnsignedInt<unsigned long long>();
}

}	// namespace asinh_test

}	// namespace bksge_cmath_test
