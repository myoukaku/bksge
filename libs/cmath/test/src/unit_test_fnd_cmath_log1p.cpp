/**
 *	@file	unit_test_fnd_cmath_log1p.cpp
 *
 *	@brief	log1p のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/log1p.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace log1p_test
{

static_assert(bksge::is_same<float,       decltype(bksge::log1p(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::log1pf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::log1p(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::log1p(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::log1p(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::log1pl(0.0l))>::value, "");

template <typename T>
void Log1pTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto eps = bksge::numeric_limits<T>::epsilon();
	BKSGE_CONSTEXPR auto min = bksge::numeric_limits<T>::lowest();

	EXPECT_NEAR(-2.30258509299404568, (double)bksge::log1p(T(-0.9)), error);
	EXPECT_NEAR(-0.69314718055994530, (double)bksge::log1p(T(-0.5)), error);
	EXPECT_NEAR( 0.40546510810816438, (double)bksge::log1p(T( 0.5)), error);
	EXPECT_NEAR( 0.69314718055994530, (double)bksge::log1p(T( 1.0)), error);
	EXPECT_NEAR( 0.91629073187415506, (double)bksge::log1p(T( 1.5)), error);
	EXPECT_NEAR( 1.09861228866810969, (double)bksge::log1p(T( 2.0)), error);
	EXPECT_NEAR( 1.60943791243410037, (double)bksge::log1p(T( 4.0)), error);
	EXPECT_NEAR( 2.19722457733621938, (double)bksge::log1p(T( 8.0)), error);

	//If the argument is ±0, it is returned unmodified
	BKSGE_CONSTEXPR_EXPECT_EQ(T(+0.0), bksge::log1p(T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-0.0), bksge::log1p(T(-0.0)));

	//If the argument is -1, -∞ is returned.
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::log1p(T(-1.0)));

	//If the argument is less than -1, NaN is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log1p(T(-1.0) - eps)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log1p(T(-1.5))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log1p(T(-2.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log1p(T(-2.5))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log1p(T(-3.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log1p(min)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log1p(-inf)));

	//If the argument is +∞, +∞ is returned
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::log1p(+inf));

	//If the argument is NaN, NaN is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log1p(-nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log1p(+nan)));
}

template <typename T>
void Log1pTestSignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.000000000001;

	EXPECT_NEAR( 0.69314718055994530, bksge::log1p(T( 1)), error);
	EXPECT_NEAR( 1.09861228866810969, bksge::log1p(T( 2)), error);
	EXPECT_NEAR( 1.60943791243410037, bksge::log1p(T( 4)), error);
	EXPECT_NEAR( 2.19722457733621938, bksge::log1p(T( 8)), error);

	BKSGE_CONSTEXPR_EXPECT_EQ(T(0), bksge::log1p(T(0)));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isinf  (bksge::log1p(T(-1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::signbit(bksge::log1p(T(-1))));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log1p(T(-2))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::log1p(T(-3))));
}

template <typename T>
void Log1pTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.000000000001;

	EXPECT_NEAR( 0.69314718055994530, bksge::log1p(T( 1)), error);
	EXPECT_NEAR( 1.09861228866810969, bksge::log1p(T( 2)), error);
	EXPECT_NEAR( 1.60943791243410037, bksge::log1p(T( 4)), error);
	EXPECT_NEAR( 2.19722457733621938, bksge::log1p(T( 8)), error);

	BKSGE_CONSTEXPR_EXPECT_EQ(T(0), bksge::log1p(T(0)));
}

GTEST_TEST(CMathTest, Log1pTest)
{
	Log1pTestFloat<float>(0.000001);
	Log1pTestFloat<double>(0.000000000001);
	Log1pTestFloat<long double>(0.000000000001);

	Log1pTestSignedInt<int>();
//	Log1pTestSignedInt<signed char>();
	Log1pTestSignedInt<short>();
//	Log1pTestSignedInt<long>();
	Log1pTestSignedInt<long long>();

//	Log1pTestUnsignedInt<unsigned int>();
	Log1pTestUnsignedInt<unsigned char>();
//	Log1pTestUnsignedInt<unsigned short>();
	Log1pTestUnsignedInt<unsigned long>();
//	Log1pTestUnsignedInt<unsigned long long>();
}

}	// namespace log1p_test

}	// namespace bksge_cmath_test
