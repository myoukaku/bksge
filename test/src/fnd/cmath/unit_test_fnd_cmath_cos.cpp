/**
 *	@file	unit_test_fnd_cmath_cos.cpp
 *
 *	@brief	cos のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/cos.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/numbers.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace cos_test
{

static_assert(bksge::is_same<float,       decltype(bksge::cos(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::cosf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cos(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cos(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cos(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cosl(0.0l))>::value, "");

template <typename T>
void CosTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	EXPECT_NEAR(-0.93645668729, (double)bksge::cos(T(-3.5)), error);
	EXPECT_NEAR(-0.98999249660, (double)bksge::cos(T(-3.0)), error);
	EXPECT_NEAR(-0.80114361554, (double)bksge::cos(T(-2.5)), error);
	EXPECT_NEAR(-0.41614683654, (double)bksge::cos(T(-2.0)), error);
	EXPECT_NEAR( 0.07073720166, (double)bksge::cos(T(-1.5)), error);
	EXPECT_NEAR( 0.54030230586, (double)bksge::cos(T(-1.0)), error);
	EXPECT_NEAR( 0.87758256189, (double)bksge::cos(T(-0.5)), error);
	EXPECT_NEAR( 1.00000000000, (double)bksge::cos(T(-0.0)), error);
	EXPECT_NEAR( 1.00000000000, (double)bksge::cos(T( 0.0)), error);
	EXPECT_NEAR( 0.87758256189, (double)bksge::cos(T( 0.5)), error);
	EXPECT_NEAR( 0.54030230586, (double)bksge::cos(T( 1.0)), error);
	EXPECT_NEAR( 0.07073720166, (double)bksge::cos(T( 1.5)), error);
	EXPECT_NEAR(-0.41614683654, (double)bksge::cos(T( 2.0)), error);
	EXPECT_NEAR(-0.80114361554, (double)bksge::cos(T( 2.5)), error);
	EXPECT_NEAR(-0.98999249660, (double)bksge::cos(T( 3.0)), error);
	EXPECT_NEAR(-0.93645668729, (double)bksge::cos(T( 3.5)), error);

	EXPECT_NEAR(-1.0, (double)bksge::cos( bksge::pi_t<T>()), error);
	EXPECT_NEAR(-1.0, (double)bksge::cos(-bksge::pi_t<T>()), error);

	BKSGE_CONSTEXPR_EXPECT_EQ(1.0, bksge::cos(T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(1.0, bksge::cos(T(-0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cos( nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cos(-nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cos( inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cos(-inf)));
}

template <typename T>
void CosTestSignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.00000000001;

	EXPECT_NEAR( 1.00000000000, bksge::cos(T( 0)), error);
	EXPECT_NEAR( 0.54030230586, bksge::cos(T( 1)), error);
	EXPECT_NEAR( 0.54030230586, bksge::cos(T(-1)), error);
	EXPECT_NEAR(-0.41614683654, bksge::cos(T( 2)), error);
	EXPECT_NEAR(-0.41614683654, bksge::cos(T(-2)), error);
	EXPECT_NEAR(-0.98999249660, bksge::cos(T( 3)), error);
	EXPECT_NEAR(-0.98999249660, bksge::cos(T(-3)), error);
}

template <typename T>
void CosTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.00000000001;

	EXPECT_NEAR( 1.00000000000, bksge::cos(T( 0)), error);
	EXPECT_NEAR( 0.54030230586, bksge::cos(T( 1)), error);
	EXPECT_NEAR(-0.41614683654, bksge::cos(T( 2)), error);
	EXPECT_NEAR(-0.98999249660, bksge::cos(T( 3)), error);
}

GTEST_TEST(CMathTest, CosTest)
{
	CosTestFloat<float>(0.0000001);
	CosTestFloat<double>(0.00000000001);
	CosTestFloat<long double>(0.00000000001);

	CosTestSignedInt<int>();
	CosTestSignedInt<signed char>();
//	CosTestSignedInt<short>();
	CosTestSignedInt<long>();
//	CosTestSignedInt<long long>();

	CosTestUnsignedInt<unsigned int>();
//	CosTestUnsignedInt<unsigned char>();
	CosTestUnsignedInt<unsigned short>();
//	CosTestUnsignedInt<unsigned long>();
	CosTestUnsignedInt<unsigned long long>();
}

}	// namespace cos_test

}	// namespace bksge_cmath_test
