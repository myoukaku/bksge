/**
 *	@file	unit_test_fnd_cmath_log2.cpp
 *
 *	@brief	log2 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/log2.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace log2_test
{

static_assert(bksge::is_same<float,       decltype(bksge::log2(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::log2f(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::log2(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::log2(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::log2(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::log2l(0.0l))>::value, "");

template <typename T>
void Log2TestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto eps = bksge::numeric_limits<T>::epsilon();

	EXPECT_NEAR(-3.0, (double)bksge::log2(T(0.125)), error);
	EXPECT_NEAR(-2.0, (double)bksge::log2(T(0.25)), error);
	EXPECT_NEAR(-1.0, (double)bksge::log2(T(0.5)), error);
	EXPECT_NEAR( 0.0, (double)bksge::log2(T(1.0)), error);
	EXPECT_NEAR( 1.0, (double)bksge::log2(T(2.0)), error);
	EXPECT_NEAR( 2.0, (double)bksge::log2(T(4.0)), error);
	EXPECT_NEAR( 3.0, (double)bksge::log2(T(8.0)), error);

	//If the argument is ±0, -∞ is returned and FE_DIVBYZERO is raised.
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::log2(T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::log2(T(-0.0)));

	//If the argument is 1, +0 is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::log2(T(+1.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::log2(T(+1.0))));

	//If the argument is negative, NaN is returned and FE_INVALID is raised.
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log2(T(-1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log2(T(-2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log2(T( 0.0) - eps)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log2(-inf)));

	//If the argument is +∞, +∞ is returned
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::log2(inf));

	//If the argument is NaN, NaN is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log2( nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log2(-nan)));
}

template <typename T>
void Log2TestSignedInt(void)
{
	using R = bksge::float_promote_t<T>;
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<R>::infinity();

	BKSGE_CONSTEXPR double error = 0.000000000001;

	BKSGE_CONSTEXPR_EXPECT_EQ(-inf,         bksge::log2(T( 0)));
	EXPECT_NEAR(0.0,                (double)bksge::log2(T( 1)), error);
	EXPECT_NEAR(1.0,                (double)bksge::log2(T( 2)), error);
	EXPECT_NEAR(1.5849625007211561, (double)bksge::log2(T( 3)), error);
	EXPECT_NEAR(2.0,                (double)bksge::log2(T( 4)), error);
	EXPECT_NEAR(2.3219280948873622, (double)bksge::log2(T( 5)), error);
	EXPECT_NEAR(3.0,                (double)bksge::log2(T( 8)), error);

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log2(T(-1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log2(T(-2))));
}

template <typename T>
void Log2TestUnsignedInt(void)
{
	using R = bksge::float_promote_t<T>;
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<R>::infinity();

	BKSGE_CONSTEXPR double error = 0.000000000001;

	BKSGE_CONSTEXPR_EXPECT_EQ(-inf,         bksge::log2(T( 0)));
	EXPECT_NEAR(0.0,                (double)bksge::log2(T( 1)), error);
	EXPECT_NEAR(1.0,                (double)bksge::log2(T( 2)), error);
	EXPECT_NEAR(1.5849625007211561, (double)bksge::log2(T( 3)), error);
	EXPECT_NEAR(2.0,                (double)bksge::log2(T( 4)), error);
	EXPECT_NEAR(2.3219280948873622, (double)bksge::log2(T( 5)), error);
	EXPECT_NEAR(3.0,                (double)bksge::log2(T( 8)), error);
}

GTEST_TEST(CMathTest, Log2Test)
{
	Log2TestFloat<float>(0.000001);
	Log2TestFloat<double>(0.000000000001);
	Log2TestFloat<long double>(0.000000000001);

//	Log2TestSignedInt<int>();
	Log2TestSignedInt<signed char>();
//	Log2TestSignedInt<short>();
	Log2TestSignedInt<long>();
//	Log2TestSignedInt<long long>();

	Log2TestUnsignedInt<unsigned int>();
//	Log2TestUnsignedInt<unsigned char>();
	Log2TestUnsignedInt<unsigned short>();
//	Log2TestUnsignedInt<unsigned long>();
	Log2TestUnsignedInt<unsigned long long>();
}

}	// namespace log2_test

}	// namespace bksge_cmath_test
