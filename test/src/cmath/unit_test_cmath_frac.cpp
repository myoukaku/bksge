/**
 *	@file	unit_test_cmath_frac.cpp
 *
 *	@brief	frac のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/cmath/frac.hpp>
#include <bksge/cmath/isnan.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace frac_test
{

template <typename T>
void FracTestFloat(void)
{
	BKSGE_CONSTEXPR double error = 0.0000001;

	BKSGE_CONSTEXPR_EXPECT_NEAR(0.8,    (double)bksge::frac(T(-1.2)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.9,    (double)bksge::frac(T(-1.1)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.0,    (double)bksge::frac(T(-1.0)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.1,    (double)bksge::frac(T(-0.9)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.2,    (double)bksge::frac(T(-0.8)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.5,    (double)bksge::frac(T(-0.5)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.8,    (double)bksge::frac(T(-0.2)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.9,    (double)bksge::frac(T(-0.1)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.0,    (double)bksge::frac(T( 0.0)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.1,    (double)bksge::frac(T( 0.1)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.123,  (double)bksge::frac(T( 0.123)),  error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.2,    (double)bksge::frac(T( 0.2)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.5,    (double)bksge::frac(T( 0.5)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.8,    (double)bksge::frac(T( 0.8)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.9,    (double)bksge::frac(T( 0.9)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.99,   (double)bksge::frac(T( 0.99)),   error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.999,  (double)bksge::frac(T( 0.999)),  error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.0,    (double)bksge::frac(T( 1.0)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.1,    (double)bksge::frac(T( 1.1)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.2,    (double)bksge::frac(T( 1.2)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.2525, (double)bksge::frac(T( 1.2525)), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.8,    (double)bksge::frac(T( 1.8)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.9,    (double)bksge::frac(T( 1.9)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.0,    (double)bksge::frac(T( 2.0)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.1,    (double)bksge::frac(T( 2.1)),    error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.2,    (double)bksge::frac(T( 2.2)),    error);

	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0.0), bksge::frac(T( inf)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0.0), bksge::frac(T(-inf)));

	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::frac(T( nan))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::frac(T(-nan))));
}

template <typename T>
void FracTestSignedInt(void)
{
	BKSGE_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_EQ(T(0), bksge::frac(T(lowest)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0), bksge::frac(T(-2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0), bksge::frac(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0), bksge::frac(T( 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0), bksge::frac(T( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0), bksge::frac(T( 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0), bksge::frac(T(max)));
}

template <typename T>
void FracTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	BKSGE_CONSTEXPR_EXPECT_EQ(T(0), bksge::frac(T(0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0), bksge::frac(T(1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0), bksge::frac(T(2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0), bksge::frac(T(max)));
}

GTEST_TEST(CMathTest, FracTest)
{
	FracTestFloat<float>();
	FracTestFloat<double>();
	FracTestFloat<long double>();

	FracTestSignedInt<int>();
	FracTestSignedInt<signed char>();
//	FracTestSignedInt<short>();
	FracTestSignedInt<long>();
//	FracTestSignedInt<long long>();

	FracTestUnsignedInt<unsigned int>();
//	FracTestUnsignedInt<unsigned char>();
	FracTestUnsignedInt<unsigned short>();
//	FracTestUnsignedInt<unsigned long>();
	FracTestUnsignedInt<unsigned long long>();
}

}	// namespace frac_test

}	// namespace bksge_cmath_test
