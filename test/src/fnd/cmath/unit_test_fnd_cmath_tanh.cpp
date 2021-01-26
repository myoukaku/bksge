/**
 *	@file	unit_test_fnd_cmath_tanh.cpp
 *
 *	@brief	tanh のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/tanh.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace tanh_test
{

template <typename T>
void TanhTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	EXPECT_NEAR(-0.99505475368, (double)bksge::tanh(T(-3.0)), error);
	EXPECT_NEAR(-0.98661429815, (double)bksge::tanh(T(-2.5)), error);
	EXPECT_NEAR(-0.96402758007, (double)bksge::tanh(T(-2.0)), error);
	EXPECT_NEAR(-0.90514825364, (double)bksge::tanh(T(-1.5)), error);
	EXPECT_NEAR(-0.76159415595, (double)bksge::tanh(T(-1.0)), error);
	EXPECT_NEAR(-0.46211715726, (double)bksge::tanh(T(-0.5)), error);
	EXPECT_NEAR( 0.00000000000, (double)bksge::tanh(T( 0.0)), error);
	EXPECT_NEAR( 0.46211715726, (double)bksge::tanh(T( 0.5)), error);
	EXPECT_NEAR( 0.76159415595, (double)bksge::tanh(T( 1.0)), error);
	EXPECT_NEAR( 0.90514825364, (double)bksge::tanh(T( 1.5)), error);
	EXPECT_NEAR( 0.96402758007, (double)bksge::tanh(T( 2.0)), error);
	EXPECT_NEAR( 0.98661429815, (double)bksge::tanh(T( 2.5)), error);
	EXPECT_NEAR( 0.99505475368, (double)bksge::tanh(T( 3.0)), error);

	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::tanh(T(+0.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::tanh(T(-0.0)));

	BKSGE_CONSTEXPR_EXPECT_EQ(+1.0, bksge::tanh(+inf));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1.0, bksge::tanh(-inf));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::tanh(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::tanh(-nan)));
}

template <typename T>
void TanhTestSignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.00000000001;

	EXPECT_NEAR(-0.99505475368, (double)bksge::tanh(T(-3)), error);
	EXPECT_NEAR(-0.96402758007, (double)bksge::tanh(T(-2)), error);
	EXPECT_NEAR(-0.76159415595, (double)bksge::tanh(T(-1)), error);
	EXPECT_NEAR( 0.00000000000, (double)bksge::tanh(T( 0)), error);
	EXPECT_NEAR( 0.76159415595, (double)bksge::tanh(T( 1)), error);
	EXPECT_NEAR( 0.96402758007, (double)bksge::tanh(T( 2)), error);
	EXPECT_NEAR( 0.99505475368, (double)bksge::tanh(T( 3)), error);
}

template <typename T>
void TanhTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.00000000001;

	EXPECT_NEAR( 0.00000000000, (double)bksge::tanh(T( 0)), error);
	EXPECT_NEAR( 0.76159415595, (double)bksge::tanh(T( 1)), error);
	EXPECT_NEAR( 0.96402758007, (double)bksge::tanh(T( 2)), error);
	EXPECT_NEAR( 0.99505475368, (double)bksge::tanh(T( 3)), error);
}

GTEST_TEST(CMathTest, TanhTest)
{
	TanhTestFloat<float>(0.0001);
	TanhTestFloat<double>(0.0000000001);
	TanhTestFloat<long double>(0.0000000001);

	TanhTestSignedInt<int>();
//	TanhTestSignedInt<signed char>();
	TanhTestSignedInt<short>();
//	TanhTestSignedInt<long>();
	TanhTestSignedInt<long long>();

//	TanhTestUnsignedInt<unsigned int>();
	TanhTestUnsignedInt<unsigned char>();
//	TanhTestUnsignedInt<unsigned short>();
	TanhTestUnsignedInt<unsigned long>();
//	TanhTestUnsignedInt<unsigned long long>();
}

}	// namespace tanh_test

}	// namespace bksge_cmath_test
