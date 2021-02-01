/**
 *	@file	unit_test_fnd_cmath_exp2.cpp
 *
 *	@brief	exp2 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/exp2.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace exp2_test
{

static_assert(bksge::is_same<float,       decltype(bksge::exp2(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::exp2f(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::exp2(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::exp2(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::exp2(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::exp2l(0.0l))>::value, "");

template <typename T>
void Exp2TestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	EXPECT_NEAR( 1.00000000000, (double)bksge::exp2(T(+0.0)), error);
	EXPECT_NEAR( 1.00000000000, (double)bksge::exp2(T(-0.0)), error);
	EXPECT_NEAR( 1.09050773266, (double)bksge::exp2(T( 0.125)), error);
	EXPECT_NEAR( 1.18920711500, (double)bksge::exp2(T( 0.25)), error);
	EXPECT_NEAR( 1.41421356237, (double)bksge::exp2(T( 0.5)), error);
	EXPECT_NEAR( 1.68179283051, (double)bksge::exp2(T( 0.75)), error);
	EXPECT_NEAR( 2.00000000000, (double)bksge::exp2(T( 1.0)), error);
	EXPECT_NEAR( 2.37841423000, (double)bksge::exp2(T( 1.25)), error);
	EXPECT_NEAR( 2.82842712474, (double)bksge::exp2(T( 1.5)), error);
	EXPECT_NEAR( 4.00000000000, (double)bksge::exp2(T( 2.0)), error);
	EXPECT_NEAR( 5.65685424949, (double)bksge::exp2(T( 2.5)), error);
	EXPECT_NEAR( 8.00000000000, (double)bksge::exp2(T( 3.0)), error);
	EXPECT_NEAR(11.31370849898, (double)bksge::exp2(T( 3.5)), error);
	EXPECT_NEAR(16.00000000000, (double)bksge::exp2(T( 4.0)), error);
	EXPECT_NEAR(22.62741699796, (double)bksge::exp2(T( 4.5)), error);
	EXPECT_NEAR(32.00000000000, (double)bksge::exp2(T( 5.0)), error);
	EXPECT_NEAR( 0.91700404320, (double)bksge::exp2(T(-0.125)), error);
	EXPECT_NEAR( 0.84089641525, (double)bksge::exp2(T(-0.25)), error);
	EXPECT_NEAR( 0.70710678118, (double)bksge::exp2(T(-0.5)), error);
	EXPECT_NEAR( 0.59460355750, (double)bksge::exp2(T(-0.75)), error);
	EXPECT_NEAR( 0.50000000000, (double)bksge::exp2(T(-1.0)), error);
	EXPECT_NEAR( 0.25000000000, (double)bksge::exp2(T(-2.0)), error);
	EXPECT_NEAR( 0.17677669529, (double)bksge::exp2(T(-2.5)), error);
	EXPECT_NEAR( 0.12500000000, (double)bksge::exp2(T(-3.0)), error);
	EXPECT_NEAR( 0.08838834764, (double)bksge::exp2(T(-3.5)), error);
	EXPECT_NEAR( 0.06250000000, (double)bksge::exp2(T(-4.0)), error);
	EXPECT_NEAR( 0.04419417382, (double)bksge::exp2(T(-4.5)), error);
	EXPECT_NEAR( 0.03125000000, (double)bksge::exp2(T(-5.0)), error);
	
	BKSGE_CONSTEXPR_EXPECT_EQ(0,   bksge::exp2(-inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::exp2(+inf));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::exp2(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::exp2(-nan)));
}

template <typename T>
void Exp2TestSignedInt(void)
{
	EXPECT_EQ( 0.03125, bksge::exp2(T(-5)));
	EXPECT_EQ( 0.0625,  bksge::exp2(T(-4)));
	EXPECT_EQ( 0.125,   bksge::exp2(T(-3)));
	EXPECT_EQ( 0.25,    bksge::exp2(T(-2)));
	EXPECT_EQ( 0.5,     bksge::exp2(T(-1)));
	EXPECT_EQ( 1.0,     bksge::exp2(T( 0)));
	EXPECT_EQ( 2.0,     bksge::exp2(T( 1)));
	EXPECT_EQ( 4.0,     bksge::exp2(T( 2)));
	EXPECT_EQ( 8.0,     bksge::exp2(T( 3)));
}

template <typename T>
void Exp2TestUnsignedInt(void)
{
	EXPECT_EQ( 1.0, bksge::exp2(T( 0)));
	EXPECT_EQ( 2.0, bksge::exp2(T( 1)));
	EXPECT_EQ( 4.0, bksge::exp2(T( 2)));
	EXPECT_EQ( 8.0, bksge::exp2(T( 3)));
	EXPECT_EQ(16.0, bksge::exp2(T( 4)));
	EXPECT_EQ(32.0, bksge::exp2(T( 5)));
}

GTEST_TEST(CMathTest, Exp2Test)
{
	Exp2TestFloat<float>(0.000001);
	Exp2TestFloat<double>(0.00000000001);
	Exp2TestFloat<long double>(0.00000000001);

	Exp2TestSignedInt<int>();
	Exp2TestSignedInt<signed char>();
//	Exp2TestSignedInt<short>();
	Exp2TestSignedInt<long>();
//	Exp2TestSignedInt<long long>();

	Exp2TestUnsignedInt<unsigned int>();
//	Exp2TestUnsignedInt<unsigned char>();
	Exp2TestUnsignedInt<unsigned short>();
//	Exp2TestUnsignedInt<unsigned long>();
	Exp2TestUnsignedInt<unsigned long long>();
}

}	// namespace exp2_test

}	// namespace bksge_cmath_test
