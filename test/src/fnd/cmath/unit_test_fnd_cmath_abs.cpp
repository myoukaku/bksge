/**
 *	@file	unit_test_fnd_cmath_abs.cpp
 *
 *	@brief	abs のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace abs_test
{

template <typename T>
void AbsTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_EQ(T(1.0), bksge::abs(T( 1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(1.0), bksge::abs(T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(3.5), bksge::abs(T( 3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(3.5), bksge::abs(T(-3.5)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(max), bksge::abs(T( max)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(max), bksge::abs(T(-max)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(min), bksge::abs(T( min)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(min), bksge::abs(T(-min)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(max), bksge::abs(T( lowest)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(max), bksge::abs(T(-lowest)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(inf), bksge::abs(T( inf)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(inf), bksge::abs(T(-inf)));

	{
		BKSGE_CONSTEXPR auto t = bksge::abs(T(+0.0));
		BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::iszero(t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(t));
	}
	{
		BKSGE_CONSTEXPR auto t = bksge::abs(T(-0.0));
		BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::iszero(t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(t));
	}
	{
		BKSGE_CONSTEXPR auto t = bksge::abs(nan);
		BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(t));
	}
	{
		BKSGE_CONSTEXPR auto t = bksge::abs(-nan);
		BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(t));
	}
}

template <typename T>
void AbsTestSignedInt(void)
{
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	BKSGE_CONSTEXPR_EXPECT_EQ(T(0),   bksge::abs(T( 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(1),   bksge::abs(T( 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(1),   bksge::abs(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(3),   bksge::abs(T( 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(3),   bksge::abs(T(-3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(max,    bksge::abs(T( max)));
	BKSGE_CONSTEXPR_EXPECT_EQ(max,    bksge::abs(T(-max)));
}

template <typename T>
void AbsTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_EQ(T(0),      bksge::abs(T(0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(1),      bksge::abs(T(1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(3),      bksge::abs(T(3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(max),    bksge::abs(T(max)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(min),    bksge::abs(T(min)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(lowest), bksge::abs(T(lowest)));
}

GTEST_TEST(CMathTest, AbsTest)
{
	AbsTestFloat<float>();
	AbsTestFloat<double>();
	AbsTestFloat<long double>();

	AbsTestSignedInt<int>();
//	AbsTestSignedInt<signed char>();
	AbsTestSignedInt<short>();
//	AbsTestSignedInt<long>();
	AbsTestSignedInt<long long>();

	AbsTestUnsignedInt<unsigned int>();
	AbsTestUnsignedInt<unsigned char>();
//	AbsTestUnsignedInt<unsigned short>();
	AbsTestUnsignedInt<unsigned long>();
//	AbsTestUnsignedInt<unsigned long long>();
}

}	// namespace abs_test

}	// namespace bksge_cmath_test
