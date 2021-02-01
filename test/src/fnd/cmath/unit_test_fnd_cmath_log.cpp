/**
 *	@file	unit_test_fnd_cmath_log.cpp
 *
 *	@brief	log のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/log.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/numbers.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace log_test
{

static_assert(bksge::is_same<float,       decltype(bksge::log(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::logf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::log(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::log(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::log(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::logl(0.0l))>::value, "");

template <typename T>
void LogTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto eps = bksge::numeric_limits<T>::epsilon();

	EXPECT_NEAR(-1.38629436111989, (double)bksge::log(T(0.25)), error);
	EXPECT_NEAR(-0.69314718055995, (double)bksge::log(T(0.50)), error);
	EXPECT_NEAR(-0.28768207245178, (double)bksge::log(T(0.75)), error);
	EXPECT_NEAR( 0.00000000000000, (double)bksge::log(T(1.00)), error);
	EXPECT_NEAR( 0.22314355131421, (double)bksge::log(T(1.25)), error);
	EXPECT_NEAR( 0.40546510810816, (double)bksge::log(T(1.50)), error);
	EXPECT_NEAR( 0.69314718055994, (double)bksge::log(T(2.00)), error);
	EXPECT_NEAR( 1.00000000000000, (double)bksge::log(bksge::e_t<T>()),  error);
	EXPECT_NEAR( 1.09861228866810, (double)bksge::log(T(3.00)), error);
	EXPECT_NEAR( 1.38629436111989, (double)bksge::log(T(4.00)), error);

	//If the argument is ±0, -∞ is returned and FE_DIVBYZERO is raised.
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::log(T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::log(T(-0.0)));

	//If the argument is 1, +0 is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::log(T(+1.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::log(T(+1.0))));

	//If the argument is negative, NaN is returned and FE_INVALID is raised.
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log(T(-1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log(T(-2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log(T( 0.0) - eps)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log(-inf)));

	//If the argument is +∞, +∞ is returned
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::log(inf));

	//If the argument is NaN, NaN is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log( nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log(-nan)));
}

template <typename T>
void LogTestSignedInt(void)
{
	using R = bksge::float_promote_t<T>;
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<R>::infinity();

	BKSGE_CONSTEXPR double error = 0.000000000001;

	EXPECT_NEAR(0.69314718055994, bksge::log(T(2)), error);
	EXPECT_NEAR(1.09861228866810, bksge::log(T(3)), error);
	
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::log(T(0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0,  bksge::log(T(1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log(-T(1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log(-T(2))));
}

template <typename T>
void LogTestUnsignedInt(void)
{
	using R = bksge::float_promote_t<T>;
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<R>::infinity();

	BKSGE_CONSTEXPR double error = 0.000000000001;

	EXPECT_NEAR(0.69314718055994, bksge::log(T(2)), error);
	EXPECT_NEAR(1.09861228866810, bksge::log(T(3)), error);
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::log(T(0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0,  bksge::log(T(1)));
}

GTEST_TEST(CMathTest, LogTest)
{
	LogTestFloat<float>(0.000001);
	LogTestFloat<double>(0.000000000001);
	LogTestFloat<long double>(0.000000000001);

//	LogTestSignedInt<int>();
	LogTestSignedInt<signed char>();
//	LogTestSignedInt<short>();
	LogTestSignedInt<long>();
//	LogTestSignedInt<long long>();

	LogTestUnsignedInt<unsigned int>();
//	LogTestUnsignedInt<unsigned char>();
	LogTestUnsignedInt<unsigned short>();
//	LogTestUnsignedInt<unsigned long>();
	LogTestUnsignedInt<unsigned long long>();
}

}	// namespace log_test

}	// namespace bksge_cmath_test
