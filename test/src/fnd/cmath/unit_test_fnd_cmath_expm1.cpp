/**
 *	@file	unit_test_fnd_cmath_expm1.cpp
 *
 *	@brief	expm1 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/expm1.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace expm1_test
{

static_assert(bksge::is_same<float,       decltype(bksge::expm1(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::expm1f(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::expm1(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::expm1(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::expm1(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::expm1l(0.0l))>::value, "");

template <typename T>
void Expm1TestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	EXPECT_NEAR( 0.0000000000000, (double)bksge::expm1(T(+0.00)), error);
	EXPECT_NEAR( 0.0000000000000, (double)bksge::expm1(T(-0.00)), error);
	EXPECT_NEAR( 0.2840254166877, (double)bksge::expm1(T( 0.25)), error);
	EXPECT_NEAR( 0.6487212707001, (double)bksge::expm1(T( 0.50)), error);
	EXPECT_NEAR( 1.1170000166127, (double)bksge::expm1(T( 0.75)), error);
	EXPECT_NEAR( 1.7182818284590, (double)bksge::expm1(T( 1.00)), error);
	EXPECT_NEAR( 6.3890560989306, (double)bksge::expm1(T( 2.00)), error);
	EXPECT_NEAR(19.0855369231876, (double)bksge::expm1(T( 3.00)), error);
	EXPECT_NEAR(-0.2211992169285, (double)bksge::expm1(T(-0.25)), error);
	EXPECT_NEAR(-0.3934693402873, (double)bksge::expm1(T(-0.50)), error);
	EXPECT_NEAR(-0.5276334472589, (double)bksge::expm1(T(-0.75)), error);
	EXPECT_NEAR(-0.6321205588285, (double)bksge::expm1(T(-1.00)), error);
	EXPECT_NEAR(-0.8646647167633, (double)bksge::expm1(T(-2.00)), error);
	EXPECT_NEAR(-0.9502129316321, (double)bksge::expm1(T(-3.00)), error);

	BKSGE_CONSTEXPR_EXPECT_EQ   (-1.0,          bksge::expm1(-inf));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isinf  (bksge::expm1(+inf)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::expm1(+inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan  (bksge::expm1(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan  (bksge::expm1(-nan)));
}

template <typename T>
void Expm1TestSignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.000000000001;
	EXPECT_NEAR(-0.8646647167633, bksge::expm1(T(-2)), error);
	EXPECT_NEAR(-0.6321205588285, bksge::expm1(T(-1)), error);
	EXPECT_NEAR( 0.0000000000000, bksge::expm1(T( 0)), error);
	EXPECT_NEAR( 1.7182818284590, bksge::expm1(T( 1)), error);
	EXPECT_NEAR( 6.3890560989306, bksge::expm1(T( 2)), error);
}

template <typename T>
void Expm1TestUnsignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.000000000001;
	EXPECT_NEAR( 0.0000000000000, bksge::expm1(T( 0)), error);
	EXPECT_NEAR( 1.7182818284590, bksge::expm1(T( 1)), error);
	EXPECT_NEAR( 6.3890560989306, bksge::expm1(T( 2)), error);
}

GTEST_TEST(CMathTest, Expm1Test)
{
	Expm1TestFloat<float>(0.000001);
	Expm1TestFloat<double>(0.000000000001);
	Expm1TestFloat<long double>(0.000000000001);

	Expm1TestSignedInt<int>();
//	Expm1TestSignedInt<signed char>();
	Expm1TestSignedInt<short>();
//	Expm1TestSignedInt<long>();
	Expm1TestSignedInt<long long>();

	Expm1TestUnsignedInt<unsigned int>();
	Expm1TestUnsignedInt<unsigned char>();
//	Expm1TestUnsignedInt<unsigned short>();
	Expm1TestUnsignedInt<unsigned long>();
//	Expm1TestUnsignedInt<unsigned long long>();
}

}	// namespace expm1_test

}	// namespace bksge_cmath_test
