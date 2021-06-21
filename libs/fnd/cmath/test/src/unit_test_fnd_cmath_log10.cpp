/**
 *	@file	unit_test_fnd_cmath_log10.cpp
 *
 *	@brief	log10 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/log10.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace log10_test
{

static_assert(bksge::is_same<float,       decltype(bksge::log10(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::log10f(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::log10(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::log10(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::log10(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::log10l(0.0l))>::value, "");

template <typename T>
void Log10TestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto eps = std::numeric_limits<T>::epsilon();

	EXPECT_NEAR(-3.0,                  (double)bksge::log10(T(   0.001)), error);
	EXPECT_NEAR(-2.0,                  (double)bksge::log10(T(   0.01)), error);
	EXPECT_NEAR(-1.0,                  (double)bksge::log10(T(   0.1)), error);
	EXPECT_NEAR(-0.301029995663981195, (double)bksge::log10(T(   0.5)), error);
	EXPECT_NEAR( 0.0,                  (double)bksge::log10(T(   1.0)), error);
	EXPECT_NEAR( 0.301029995663981195, (double)bksge::log10(T(   2.0)), error);
	EXPECT_NEAR( 0.477121254719662437, (double)bksge::log10(T(   3.0)), error);
	EXPECT_NEAR( 0.954242509439324875, (double)bksge::log10(T(   9.0)), error);
	EXPECT_NEAR( 1.0,                  (double)bksge::log10(T(  10.0)), error);
	EXPECT_NEAR( 2.0,                  (double)bksge::log10(T( 100.0)), error);
	EXPECT_NEAR( 3.0,                  (double)bksge::log10(T(1000.0)), error);

	//If the argument is ±0, -∞ is returned and FE_DIVBYZERO is raised.
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::log10(T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::log10(T(-0.0)));

	//If the argument is 1, +0 is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::log10(T(+1.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::log10(T(+1.0))));

	//If the argument is negative, NaN is returned and FE_INVALID is raised.
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log10(T(-1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log10(T(-2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log10(T( 0.0) - eps)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log10(-inf)));

	//If the argument is +∞, +∞ is returned
	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::log10(inf));

	//If the argument is NaN, NaN is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log10( nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log10(-nan)));
}

template <typename T>
void Log10TestSignedInt(void)
{
	using R = bksge::float_promote_t<T>;
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<R>::infinity();

	BKSGE_CONSTEXPR double error = 0.000000000001;

	BKSGE_CONSTEXPR_EXPECT_EQ  (-inf,         bksge::log10(T(   0)));
	EXPECT_NEAR(0.0,                  (double)bksge::log10(T(   1)), error);
	EXPECT_NEAR(0.301029995663981195, (double)bksge::log10(T(   2)), error);
	EXPECT_NEAR(0.477121254719662437, (double)bksge::log10(T(   3)), error);
	EXPECT_NEAR(0.954242509439324875, (double)bksge::log10(T(   9)), error);
	EXPECT_NEAR(1.0,                  (double)bksge::log10(T(  10)), error);
	EXPECT_NEAR(2.0,                  (double)bksge::log10(T( 100)), error);

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log10(T(-1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log10(T(-2))));
}

template <typename T>
void Log10TestUnsignedInt(void)
{
	using R = bksge::float_promote_t<T>;
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<R>::infinity();

	BKSGE_CONSTEXPR double error = 0.000000000001;

	BKSGE_CONSTEXPR_EXPECT_EQ  (-inf,         bksge::log10(T(   0)));
	EXPECT_NEAR(0.0,                  (double)bksge::log10(T(   1)), error);
	EXPECT_NEAR(0.301029995663981195, (double)bksge::log10(T(   2)), error);
	EXPECT_NEAR(0.477121254719662437, (double)bksge::log10(T(   3)), error);
	EXPECT_NEAR(0.954242509439324875, (double)bksge::log10(T(   9)), error);
	EXPECT_NEAR(1.0,                  (double)bksge::log10(T(  10)), error);
	EXPECT_NEAR(2.0,                  (double)bksge::log10(T( 100)), error);
}

GTEST_TEST(CMathTest, Log10Test)
{
	Log10TestFloat<float>(0.000001);
	Log10TestFloat<double>(0.000000000001);
	Log10TestFloat<long double>(0.000000000001);

	Log10TestSignedInt<int>();
//	Log10TestSignedInt<signed char>();
	Log10TestSignedInt<short>();
//	Log10TestSignedInt<long>();
	Log10TestSignedInt<long long>();

//	Log10TestUnsignedInt<unsigned int>();
	Log10TestUnsignedInt<unsigned char>();
//	Log10TestUnsignedInt<unsigned short>();
	Log10TestUnsignedInt<unsigned long>();
//	Log10TestUnsignedInt<unsigned long long>();
}

}	// namespace log10_test

}	// namespace bksge_cmath_test
