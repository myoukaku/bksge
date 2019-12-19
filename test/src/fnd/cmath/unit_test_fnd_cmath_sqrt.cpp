/**
 *	@file	unit_test_fnd_cmath_sqrt.cpp
 *
 *	@brief	sqrt のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/sqrt.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace sqrt_test
{

template <typename T>
void SqrtTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto eps = std::numeric_limits<T>::epsilon();

	BKSGE_CONSTEXPR double error = 0.0000001;

	EXPECT_NEAR( 0.00000000000, (double)bksge::sqrt(T(  0.00)), error);
	EXPECT_NEAR( 0.50000000000, (double)bksge::sqrt(T(  0.25)), error);
	EXPECT_NEAR( 1.00000000000, (double)bksge::sqrt(T(  1.00)), error);
	EXPECT_NEAR( 1.50000000000, (double)bksge::sqrt(T(  2.25)), error);
	EXPECT_NEAR( 1.41421356237, (double)bksge::sqrt(T(  2.00)), error);
	EXPECT_NEAR( 1.73205080757, (double)bksge::sqrt(T(  3.00)), error);
	EXPECT_NEAR(10.00000000000, (double)bksge::sqrt(T(100.00)), error);

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::sqrt(T(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::sqrt(T(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::sqrt(T(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::sqrt(T(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::sqrt(+inf));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::sqrt(-eps)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::sqrt(T(-1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::sqrt(-inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::sqrt(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::sqrt(-nan)));
}

template <typename T>
void SqrtTestSignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.0000001;

	EXPECT_NEAR( 0.00000000000, bksge::sqrt(T(  0)), error);
	EXPECT_NEAR( 1.00000000000, bksge::sqrt(T(  1)), error);
	EXPECT_NEAR( 1.41421356237, bksge::sqrt(T(  2)), error);
	EXPECT_NEAR( 1.73205080757, bksge::sqrt(T(  3)), error);
	EXPECT_NEAR(10.00000000000, bksge::sqrt(T(100)), error);

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::sqrt(T(-1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::sqrt(T(-2))));
}

template <typename T>
void SqrtTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.0000001;

	EXPECT_NEAR( 0.00000000000, bksge::sqrt(T(  0)), error);
	EXPECT_NEAR( 1.00000000000, bksge::sqrt(T(  1)), error);
	EXPECT_NEAR( 1.41421356237, bksge::sqrt(T(  2)), error);
	EXPECT_NEAR( 1.73205080757, bksge::sqrt(T(  3)), error);
	EXPECT_NEAR(10.00000000000, bksge::sqrt(T(100)), error);
}

GTEST_TEST(CMathTest, SqrtTest)
{
	SqrtTestFloat<float>();
	SqrtTestFloat<double>();
	SqrtTestFloat<long double>();

//	SqrtTestSignedInt<int>();
	SqrtTestSignedInt<signed char>();
//	SqrtTestSignedInt<short>();
	SqrtTestSignedInt<long>();
//	SqrtTestSignedInt<long long>();

	SqrtTestUnsignedInt<unsigned int>();
//	SqrtTestUnsignedInt<unsigned char>();
	SqrtTestUnsignedInt<unsigned short>();
//	SqrtTestUnsignedInt<unsigned long>();
	SqrtTestUnsignedInt<unsigned long long>();
}

}	// namespace sqrt_test

}	// namespace bksge_cmath_test
