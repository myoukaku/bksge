/**
 *	@file	unit_test_fnd_cmath_tan.cpp
 *
 *	@brief	tan のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/tan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace tan_test
{

template <typename T>
void TanTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	EXPECT_NEAR( 0.00000000000, (double)bksge::tan(T( 0.0)), error);
	EXPECT_NEAR( 0.10033467208, (double)bksge::tan(T( 0.1)), error);
	EXPECT_NEAR( 0.20271003550, (double)bksge::tan(T( 0.2)), error);
	EXPECT_NEAR( 0.30933624961, (double)bksge::tan(T( 0.3)), error);
	EXPECT_NEAR( 0.54630248984, (double)bksge::tan(T( 0.5)), error);
	EXPECT_NEAR( 1.02963855705, (double)bksge::tan(T( 0.8)), error);
	EXPECT_NEAR( 1.55740772465, (double)bksge::tan(T( 1.0)), error);
	EXPECT_NEAR( 14.1014199472, (double)bksge::tan(T( 1.5)), error);
	EXPECT_NEAR(-34.2325327356, (double)bksge::tan(T( 1.6)), error);
	EXPECT_NEAR(-7.69660213946, (double)bksge::tan(T( 1.7)), error);
	EXPECT_NEAR(-4.28626167463, (double)bksge::tan(T( 1.8)), error);
	EXPECT_NEAR(-2.92709751468, (double)bksge::tan(T( 1.9)), error);
	EXPECT_NEAR(-2.18503986326, (double)bksge::tan(T( 2.0)), error);
	EXPECT_NEAR(-0.74702229723, (double)bksge::tan(T( 2.5)), error);
	EXPECT_NEAR(-0.14254654307, (double)bksge::tan(T( 3.0)), error);
	EXPECT_NEAR( 0.37458564015, (double)bksge::tan(T( 3.5)), error);
	EXPECT_NEAR(-0.10033467208, (double)bksge::tan(T(-0.1)), error);
	EXPECT_NEAR(-0.20271003550, (double)bksge::tan(T(-0.2)), error);
	EXPECT_NEAR(-0.30933624961, (double)bksge::tan(T(-0.3)), error);
	EXPECT_NEAR(-0.54630248984, (double)bksge::tan(T(-0.5)), error);
	EXPECT_NEAR(-1.02963855705, (double)bksge::tan(T(-0.8)), error);
	EXPECT_NEAR(-1.55740772465, (double)bksge::tan(T(-1.0)), error);
	EXPECT_NEAR(-14.1014199472, (double)bksge::tan(T(-1.5)), error);
	EXPECT_NEAR( 34.2325327356, (double)bksge::tan(T(-1.6)), error);
	EXPECT_NEAR( 7.69660213946, (double)bksge::tan(T(-1.7)), error);
	EXPECT_NEAR( 4.28626167463, (double)bksge::tan(T(-1.8)), error);
	EXPECT_NEAR( 2.92709751468, (double)bksge::tan(T(-1.9)), error);
	EXPECT_NEAR( 2.18503986326, (double)bksge::tan(T(-2.0)), error);
	EXPECT_NEAR( 0.74702229723, (double)bksge::tan(T(-2.5)), error);
	EXPECT_NEAR( 0.14254654307, (double)bksge::tan(T(-3.0)), error);
	EXPECT_NEAR(-0.37458564015, (double)bksge::tan(T(-3.5)), error);

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::tan(T(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::tan(T(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::tan(T(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::tan(T(-0.0))));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::tan(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::tan(-nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::tan(+inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::tan(-inf)));
}

template <typename T>
void TanTestSignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.00000000001;

	EXPECT_NEAR( 0.00000000000, bksge::tan(T( 0)), error);
	EXPECT_NEAR( 1.55740772465, bksge::tan(T( 1)), error);
	EXPECT_NEAR(-1.55740772465, bksge::tan(T(-1)), error);
	EXPECT_NEAR(-2.18503986326, bksge::tan(T( 2)), error);
	EXPECT_NEAR( 2.18503986326, bksge::tan(T(-2)), error);
	EXPECT_NEAR(-0.14254654307, bksge::tan(T( 3)), error);
	EXPECT_NEAR( 0.14254654307, bksge::tan(T(-3)), error);
}

template <typename T>
void TanTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.00000000001;

	EXPECT_NEAR( 0.00000000000, bksge::tan(T(0)), error);
	EXPECT_NEAR( 1.55740772465, bksge::tan(T(1)), error);
	EXPECT_NEAR(-2.18503986326, bksge::tan(T(2)), error);
	EXPECT_NEAR(-0.14254654307, bksge::tan(T(3)), error);
}

GTEST_TEST(CMathTest, TanTest)
{
	TanTestFloat<float>(0.0001);
	TanTestFloat<double>(0.0000000001);
	TanTestFloat<long double>(0.0000000001);

//	TanTestSignedInt<int>();
	TanTestSignedInt<signed char>();
//	TanTestSignedInt<short>();
	TanTestSignedInt<long>();
//	TanTestSignedInt<long long>();

	TanTestUnsignedInt<unsigned int>();
//	TanTestUnsignedInt<unsigned char>();
	TanTestUnsignedInt<unsigned short>();
//	TanTestUnsignedInt<unsigned long>();
	TanTestUnsignedInt<unsigned long long>();
}

}	// namespace tan_test

}	// namespace bksge_cmath_test
