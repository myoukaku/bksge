/**
 *	@file	unit_test_fnd_cmath_acos.cpp
 *
 *	@brief	acos のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/acos.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace acos_test
{

template <typename T>
void AcosTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto eps = bksge::numeric_limits<T>::epsilon();

	EXPECT_NEAR(3.141592653590, (double)bksge::acos(T(-1.00)), error);
	EXPECT_NEAR(2.418858405776, (double)bksge::acos(T(-0.75)), error);
	EXPECT_NEAR(2.094395102393, (double)bksge::acos(T(-0.50)), error);
	EXPECT_NEAR(1.823476581937, (double)bksge::acos(T(-0.25)), error);
	EXPECT_NEAR(1.570796326795, (double)bksge::acos(T( 0.00)), error);
	EXPECT_NEAR(1.318116071653, (double)bksge::acos(T( 0.25)), error);
	EXPECT_NEAR(1.047197551197, (double)bksge::acos(T( 0.50)), error);
	EXPECT_NEAR(0.722734247813, (double)bksge::acos(T( 0.75)), error);
	EXPECT_NEAR(0.000000000000, (double)bksge::acos(T( 1.00)), error);

	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::acos(T(+1.0)));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::acos(T(+1.0) + eps)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::acos(T(-1.0) - eps)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::acos(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::acos(-nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::acos(+inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::acos(-inf)));
}

template <typename T>
void AcosTestSignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.000000000001;

	EXPECT_NEAR(3.141592653590, bksge::acos(T(-1)), error);
	EXPECT_NEAR(1.570796326795, bksge::acos(T( 0)), error);
	EXPECT_NEAR(0.000000000000, bksge::acos(T( 1)), error);
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::acos(T( 2))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::acos(T(-2))));
}

template <typename T>
void AcosTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.000000000001;

	EXPECT_NEAR(1.570796326795, bksge::acos(T( 0)), error);
	EXPECT_NEAR(0.000000000000, bksge::acos(T( 1)), error);
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::acos(T( 2))));
}

GTEST_TEST(CMathTest, AcosTest)
{
	AcosTestFloat<float>(0.000001);
	AcosTestFloat<double>(0.000000000001);
	AcosTestFloat<long double>(0.000000000001);

	AcosTestSignedInt<int>();
	AcosTestSignedInt<signed char>();
//	AcosTestSignedInt<short>();
	AcosTestSignedInt<long>();
//	AcosTestSignedInt<long long>();

	AcosTestUnsignedInt<unsigned int>();
//	AcosTestUnsignedInt<unsigned char>();
	AcosTestUnsignedInt<unsigned short>();
//	AcosTestUnsignedInt<unsigned long>();
	AcosTestUnsignedInt<unsigned long long>();
}

}	// namespace acos_test

}	// namespace bksge_cmath_test
