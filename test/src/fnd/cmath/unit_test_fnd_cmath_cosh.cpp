/**
 *	@file	unit_test_fnd_cmath_cosh.cpp
 *
 *	@brief	cosh のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/cosh.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace cosh_test
{

static_assert(bksge::is_same<float,       decltype(bksge::cosh(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::coshf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cosh(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cosh(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cosh(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::coshl(0.0l))>::value, "");

template <typename T>
void CoshTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	EXPECT_NEAR(10.06766199577, (double)bksge::cosh(T(-3.0)), error);
	EXPECT_NEAR( 6.13228947966, (double)bksge::cosh(T(-2.5)), error);
	EXPECT_NEAR( 3.76219569108, (double)bksge::cosh(T(-2.0)), error);
	EXPECT_NEAR( 2.35240961524, (double)bksge::cosh(T(-1.5)), error);
	EXPECT_NEAR( 1.54308063482, (double)bksge::cosh(T(-1.0)), error);
	EXPECT_NEAR( 1.12762596521, (double)bksge::cosh(T(-0.5)), error);
	EXPECT_NEAR( 1.00000000000, (double)bksge::cosh(T(-0.0)), error);
	EXPECT_NEAR( 1.00000000000, (double)bksge::cosh(T( 0.0)), error);
	EXPECT_NEAR( 1.12762596521, (double)bksge::cosh(T( 0.5)), error);
	EXPECT_NEAR( 1.54308063482, (double)bksge::cosh(T( 1.0)), error);
	EXPECT_NEAR( 2.35240961524, (double)bksge::cosh(T( 1.5)), error);
	EXPECT_NEAR( 3.76219569108, (double)bksge::cosh(T( 2.0)), error);
	EXPECT_NEAR( 6.13228947966, (double)bksge::cosh(T( 2.5)), error);
	EXPECT_NEAR(10.06766199577, (double)bksge::cosh(T( 3.0)), error);

	BKSGE_CONSTEXPR_EXPECT_EQ( 1.0, bksge::cosh(T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1.0, bksge::cosh(T(-0.0)));

	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::cosh(+inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::cosh(-inf));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cosh(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cosh(-nan)));
}

template <typename T>
void CoshTestSignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.00000000001;

	EXPECT_NEAR(10.06766199577, (double)bksge::cosh(T(-3)), error);
	EXPECT_NEAR( 3.76219569108, (double)bksge::cosh(T(-2)), error);
	EXPECT_NEAR( 1.54308063482, (double)bksge::cosh(T(-1)), error);
	EXPECT_NEAR( 1.00000000000, (double)bksge::cosh(T( 0)), error);
	EXPECT_NEAR( 1.54308063482, (double)bksge::cosh(T( 1)), error);
	EXPECT_NEAR( 3.76219569108, (double)bksge::cosh(T( 2)), error);
	EXPECT_NEAR(10.06766199577, (double)bksge::cosh(T( 3)), error);
}

template <typename T>
void CoshTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.00000000001;

	EXPECT_NEAR( 1.00000000000, (double)bksge::cosh(T( 0)), error);
	EXPECT_NEAR( 1.54308063482, (double)bksge::cosh(T( 1)), error);
	EXPECT_NEAR( 3.76219569108, (double)bksge::cosh(T( 2)), error);
	EXPECT_NEAR(10.06766199577, (double)bksge::cosh(T( 3)), error);
}

GTEST_TEST(CMathTest, CoshTest)
{
	CoshTestFloat<float>(0.000001);
	CoshTestFloat<double>(0.00000000001);
	CoshTestFloat<long double>(0.00000000001);

	CoshTestSignedInt<int>();
//	CoshTestSignedInt<signed char>();
	CoshTestSignedInt<short>();
//	CoshTestSignedInt<long>();
	CoshTestSignedInt<long long>();

	CoshTestUnsignedInt<unsigned int>();
	CoshTestUnsignedInt<unsigned char>();
//	CoshTestUnsignedInt<unsigned short>();
	CoshTestUnsignedInt<unsigned long>();
//	CoshTestUnsignedInt<unsigned long long>();
}

}	// namespace cosh_test

}	// namespace bksge_cmath_test
