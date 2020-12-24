/**
 *	@file	unit_test_fnd_cmath_fabs.cpp
 *
 *	@brief	fabs のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/fabs.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace fabs_test
{

template <typename T>
void FabsTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan    = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf    = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto max    = bksge::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min    = bksge::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto lowest = bksge::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_EQ(T(1.0), bksge::fabs(T( 1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(1.0), bksge::fabs(T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(3.5), bksge::fabs(T( 3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(3.5), bksge::fabs(T(-3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(max), bksge::fabs(T( max)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(max), bksge::fabs(T(-max)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(min), bksge::fabs(T( min)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(min), bksge::fabs(T(-min)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(max), bksge::fabs(T( lowest)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(max), bksge::fabs(T(-lowest)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(inf), bksge::fabs(T( inf)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(inf), bksge::fabs(T(-inf)));

	{
		BKSGE_CONSTEXPR auto t = bksge::fabs(T(+0.0));
		BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::iszero(t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(t));
	}
	{
		BKSGE_CONSTEXPR auto t = bksge::fabs(T(-0.0));
		BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::iszero(t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(t));
	}
	{
		BKSGE_CONSTEXPR auto t = bksge::fabs(nan);
		BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(t));
	}
	{
		BKSGE_CONSTEXPR auto t = bksge::fabs(-nan);
		BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(t));
	}
}

template <typename T>
void FabsTestSignedInt(void)
{
	BKSGE_CONSTEXPR auto max    = bksge::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min    = bksge::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto lowest = bksge::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_EQ(double(0),     bksge::fabs(T( 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(double(1),     bksge::fabs(T( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(double(1),     bksge::fabs(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(double(3),     bksge::fabs(T( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(double(3),     bksge::fabs(T(-3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(double(max),   bksge::fabs(T( max)));
	BKSGE_CONSTEXPR_EXPECT_EQ(double(max),   bksge::fabs(T(-max)));
	BKSGE_CONSTEXPR_EXPECT_EQ(double(max)+1, bksge::fabs(T( min)));
	BKSGE_CONSTEXPR_EXPECT_EQ(double(max)+1, bksge::fabs(T( lowest)));
}

template <typename T>
void FabsTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR auto max    = bksge::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min    = bksge::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto lowest = bksge::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_EQ(double(0),      bksge::fabs(T(0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(double(1),      bksge::fabs(T(1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(double(3),      bksge::fabs(T(3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(double(max),    bksge::fabs(T(max)));
	BKSGE_CONSTEXPR_EXPECT_EQ(double(min),    bksge::fabs(T(min)));
	BKSGE_CONSTEXPR_EXPECT_EQ(double(lowest), bksge::fabs(T(lowest)));
}

GTEST_TEST(CMathTest, FAbsTest)
{
	FabsTestFloat<float>();
	FabsTestFloat<double>();
	FabsTestFloat<long double>();

	FabsTestSignedInt<int>();
	FabsTestSignedInt<signed char>();
//	FabsTestSignedInt<short>();
	FabsTestSignedInt<long>();
//	FabsTestSignedInt<long long>();

	FabsTestUnsignedInt<unsigned int>();
//	FabsTestUnsignedInt<unsigned char>();
	FabsTestUnsignedInt<unsigned short>();
//	FabsTestUnsignedInt<unsigned long>();
	FabsTestUnsignedInt<unsigned long long>();
}

}	// namespace fabs_test

}	// namespace bksge_cmath_test
