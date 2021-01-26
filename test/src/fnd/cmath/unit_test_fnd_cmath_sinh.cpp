/**
 *	@file	unit_test_fnd_cmath_sinh.cpp
 *
 *	@brief	sinh のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/sinh.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace sinh_test
{

template <typename T>
void SinhTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	EXPECT_NEAR(-10.01787492740, (double)bksge::sinh(T(-3.0)), error);
	EXPECT_NEAR( -3.62686040785, (double)bksge::sinh(T(-2.0)), error);
	EXPECT_NEAR( -1.17520119364, (double)bksge::sinh(T(-1.0)), error);
	EXPECT_NEAR( -0.52109530549, (double)bksge::sinh(T(-0.5)), error);
	EXPECT_NEAR(  0.52109530549, (double)bksge::sinh(T( 0.5)), error);
	EXPECT_NEAR(  1.17520119364, (double)bksge::sinh(T( 1.0)), error);
	EXPECT_NEAR(  2.12927945509, (double)bksge::sinh(T( 1.5)), error);
	EXPECT_NEAR(  3.62686040785, (double)bksge::sinh(T( 2.0)), error);
	EXPECT_NEAR( 10.01787492740, (double)bksge::sinh(T( 3.0)), error);

	BKSGE_CONSTEXPR_EXPECT_EQ(T(+0.0), bksge::sinh(T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(-0.0), bksge::sinh(T(-0.0)));

	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::sinh(+inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::sinh(-inf));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::sinh(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::sinh(-nan)));
}

template <typename T>
void SinhTestSignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.00000000001;

	EXPECT_NEAR(-10.01787492740, (double)bksge::sinh(T(-3)), error);
	EXPECT_NEAR( -3.62686040785, (double)bksge::sinh(T(-2)), error);
	EXPECT_NEAR( -1.17520119364, (double)bksge::sinh(T(-1)), error);
	EXPECT_NEAR(  0.00000000000, (double)bksge::sinh(T( 0)), error);
	EXPECT_NEAR(  1.17520119364, (double)bksge::sinh(T( 1)), error);
	EXPECT_NEAR(  3.62686040785, (double)bksge::sinh(T( 2)), error);
	EXPECT_NEAR( 10.01787492740, (double)bksge::sinh(T( 3)), error);
}

template <typename T>
void SinhTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.00000000001;

	EXPECT_NEAR(  0.00000000000, (double)bksge::sinh(T( 0)), error);
	EXPECT_NEAR(  1.17520119364, (double)bksge::sinh(T( 1)), error);
	EXPECT_NEAR(  3.62686040785, (double)bksge::sinh(T( 2)), error);
	EXPECT_NEAR( 10.01787492740, (double)bksge::sinh(T( 3)), error);
}

GTEST_TEST(CMathTest, SinhTest)
{
	SinhTestFloat<float>(0.000001);
	SinhTestFloat<double>(0.00000000001);
	SinhTestFloat<long double>(0.00000000001);

	SinhTestSignedInt<int>();
//	SinhTestSignedInt<signed char>();
	SinhTestSignedInt<short>();
//	SinhTestSignedInt<long>();
	SinhTestSignedInt<long long>();

//	SinhTestUnsignedInt<unsigned int>();
	SinhTestUnsignedInt<unsigned char>();
//	SinhTestUnsignedInt<unsigned short>();
	SinhTestUnsignedInt<unsigned long>();
//	SinhTestUnsignedInt<unsigned long long>();
}

}	// namespace sinh_test

}	// namespace bksge_cmath_test
