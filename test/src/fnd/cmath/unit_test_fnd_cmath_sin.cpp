/**
 *	@file	unit_test_fnd_cmath_sin.cpp
 *
 *	@brief	sin のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/sin.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/constants.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace sin_test
{

template <typename T>
void SinTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	EXPECT_NEAR( 0.35078322768961985, (double)bksge::sin(T(-3.5)), error);
	EXPECT_NEAR(-0.14112000805986722, (double)bksge::sin(T(-3.0)), error);
	EXPECT_NEAR(-0.59847214410395649, (double)bksge::sin(T(-2.5)), error);
	EXPECT_NEAR(-0.90929742682568169, (double)bksge::sin(T(-2.0)), error);
	EXPECT_NEAR(-0.99749498660405443, (double)bksge::sin(T(-1.5)), error);
	EXPECT_NEAR(-0.84147098480789650, (double)bksge::sin(T(-1.0)), error);
	EXPECT_NEAR(-0.47942553860420300, (double)bksge::sin(T(-0.5)), error);
	EXPECT_NEAR( 0.00000000000000000, (double)bksge::sin(T( 0.0)), error);
	EXPECT_NEAR( 0.47942553860420300, (double)bksge::sin(T( 0.5)), error);
	EXPECT_NEAR( 0.84147098480789650, (double)bksge::sin(T( 1.0)), error);
	EXPECT_NEAR( 0.99749498660405443, (double)bksge::sin(T( 1.5)), error);
	EXPECT_NEAR( 0.90929742682568169, (double)bksge::sin(T( 2.0)), error);
	EXPECT_NEAR( 0.59847214410395649, (double)bksge::sin(T( 2.5)), error);
	EXPECT_NEAR( 0.14112000805986722, (double)bksge::sin(T( 3.0)), error);
	EXPECT_NEAR(-0.35078322768961985, (double)bksge::sin(T( 3.5)), error);

	EXPECT_NEAR(0.0, (double)bksge::sin( bksge::pi<T>()), error);
	EXPECT_NEAR(0.0, (double)bksge::sin(-bksge::pi<T>()), error);

	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::sin(T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::sin(T(-0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::sin(+inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::sin(-inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::sin(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::sin(-nan)));
}

template <typename T>
void SinTestSignedInt(void)
{
	const double error = 0.00000000001;

	EXPECT_NEAR( 0.00000000000000000, bksge::sin(T( 0)), error);
	EXPECT_NEAR( 0.84147098480789650, bksge::sin(T( 1)), error);
	EXPECT_NEAR(-0.84147098480789650, bksge::sin(T(-1)), error);
	EXPECT_NEAR( 0.90929742682568169, bksge::sin(T( 2)), error);
	EXPECT_NEAR(-0.90929742682568169, bksge::sin(T(-2)), error);
	EXPECT_NEAR( 0.14112000805986722, bksge::sin(T( 3)), error);
	EXPECT_NEAR(-0.14112000805986722, bksge::sin(T(-3)), error);
}

template <typename T>
void SinTestUnsignedInt(void)
{
	const double error = 0.00000000001;

	EXPECT_NEAR(0.00000000000000000, bksge::sin(T( 0)), error);
	EXPECT_NEAR(0.84147098480789650, bksge::sin(T( 1)), error);
	EXPECT_NEAR(0.90929742682568169, bksge::sin(T( 2)), error);
	EXPECT_NEAR(0.14112000805986722, bksge::sin(T( 3)), error);
}

GTEST_TEST(CMathTest, SinTest)
{
	SinTestFloat<float>(0.0000001);
	SinTestFloat<double>(0.00000000001);
	SinTestFloat<long double>(0.00000000001);

	SinTestSignedInt<int>();
//	SinTestSignedInt<signed char>();
	SinTestSignedInt<short>();
//	SinTestSignedInt<long>();
	SinTestSignedInt<long long>();

//	SinTestUnsignedInt<unsigned int>();
	SinTestUnsignedInt<unsigned char>();
//	SinTestUnsignedInt<unsigned short>();
	SinTestUnsignedInt<unsigned long>();
//	SinTestUnsignedInt<unsigned long long>();
}

}	// namespace sin_test

}	// namespace bksge_cmath_test
