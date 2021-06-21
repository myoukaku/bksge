/**
 *	@file	unit_test_fnd_cmath_exp.cpp
 *
 *	@brief	exp のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/exp.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace exp_test
{

static_assert(bksge::is_same<float,       decltype(bksge::exp(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::expf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::exp(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::exp(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::exp(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::expl(0.0l))>::value, "");

template <typename T>
void ExpTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	EXPECT_NEAR( 1.0000000000000, (double)bksge::exp(T(+0.00)), error);
	EXPECT_NEAR( 1.0000000000000, (double)bksge::exp(T(-0.00)), error);
	EXPECT_NEAR( 1.2840254166877, (double)bksge::exp(T( 0.25)), error);
	EXPECT_NEAR( 1.6487212707001, (double)bksge::exp(T( 0.50)), error);
	EXPECT_NEAR( 2.1170000166127, (double)bksge::exp(T( 0.75)), error);
	EXPECT_NEAR( 2.7182818284590, (double)bksge::exp(T( 1.00)), error);
	EXPECT_NEAR( 7.3890560989306, (double)bksge::exp(T( 2.00)), error);
	EXPECT_NEAR(20.0855369231876, (double)bksge::exp(T( 3.00)), error);
	EXPECT_NEAR( 0.7788007830714, (double)bksge::exp(T(-0.25)), error);
	EXPECT_NEAR( 0.6065306597126, (double)bksge::exp(T(-0.50)), error);
	EXPECT_NEAR( 0.4723665527410, (double)bksge::exp(T(-0.75)), error);
	EXPECT_NEAR( 0.3678794411714, (double)bksge::exp(T(-1.00)), error);
	EXPECT_NEAR( 0.1353352832366, (double)bksge::exp(T(-2.00)), error);
	EXPECT_NEAR( 0.0497870683678, (double)bksge::exp(T(-3.00)), error);

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::exp(-inf)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::exp(-inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isinf  (bksge::exp(+inf)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::exp(+inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan  (bksge::exp(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isnan  (bksge::exp(-nan)));
}

template <typename T>
void ExpTestSignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.000000000001;
	EXPECT_NEAR(0.1353352832366, bksge::exp(T(-2)), error);
	EXPECT_NEAR(0.3678794411714, bksge::exp(T(-1)), error);
	EXPECT_NEAR(1.0000000000000, bksge::exp(T( 0)), error);
	EXPECT_NEAR(2.7182818284590, bksge::exp(T( 1)), error);
	EXPECT_NEAR(7.3890560989306, bksge::exp(T( 2)), error);
}

template <typename T>
void ExpTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.000000000001;
	EXPECT_NEAR(1.0000000000000, bksge::exp(T( 0)), error);
	EXPECT_NEAR(2.7182818284590, bksge::exp(T( 1)), error);
	EXPECT_NEAR(7.3890560989306, bksge::exp(T( 2)), error);
}

GTEST_TEST(CMathTest, ExpTest)
{
	ExpTestFloat<float>(0.000001);
	ExpTestFloat<double>(0.000000000001);
	ExpTestFloat<long double>(0.000000000001);

	ExpTestSignedInt<int>();
//	ExpTestSignedInt<signed char>();
	ExpTestSignedInt<short>();
//	ExpTestSignedInt<long>();
	ExpTestSignedInt<long long>();

	ExpTestUnsignedInt<unsigned int>();
	ExpTestUnsignedInt<unsigned char>();
//	ExpTestUnsignedInt<unsigned short>();
	ExpTestUnsignedInt<unsigned long>();
//	ExpTestUnsignedInt<unsigned long long>();
}

}	// namespace exp_test

}	// namespace bksge_cmath_test
