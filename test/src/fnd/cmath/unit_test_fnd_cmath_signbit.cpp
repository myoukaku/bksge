/**
 *	@file	unit_test_fnd_cmath_signbit.cpp
 *
 *	@brief	signbit のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace signbit_test
{

template <typename T>
void SignbitTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan    = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf    = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto max    = bksge::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min    = bksge::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto lowest = bksge::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(T( 1.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::signbit(T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(T( 0.5)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::signbit(T(-0.5)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit( inf));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::signbit(-inf));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(min));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::signbit(lowest));

	// BKSGEでは、+0と-0は区別されない
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(T( 0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(T(-0.0)));

	// BKSGEでは、+NaNと-NaNは区別されない
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit( nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(-nan));
}

template <typename T>
void SignbitTestSignedInt(void)
{
	BKSGE_CONSTEXPR auto max    = bksge::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min    = bksge::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto lowest = bksge::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(T( 0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(T( 1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::signbit(T(-1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(T( 2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::signbit(T(-2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(max));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::signbit(min));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::signbit(lowest));
}

template <typename T>
void SignbitTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR auto max    = bksge::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min    = bksge::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto lowest = bksge::numeric_limits<T>::lowest();

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(T( 0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(T( 1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(T( 2)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(lowest));
}

GTEST_TEST(CMathTest, SignBitTest)
{
	SignbitTestFloat<float>();
	SignbitTestFloat<double>();
	SignbitTestFloat<long double>();

//	SignbitTestSignedInt<int>();
	SignbitTestSignedInt<signed char>();
//	SignbitTestSignedInt<short>();
	SignbitTestSignedInt<long>();
//	SignbitTestSignedInt<long long>();

	SignbitTestUnsignedInt<unsigned int>();
//	SignbitTestUnsignedInt<unsigned char>();
	SignbitTestUnsignedInt<unsigned short>();
//	SignbitTestUnsignedInt<unsigned long>();
	SignbitTestUnsignedInt<unsigned long long>();
}

}	// namespace signbit_test

}	// namespace bksge_cmath_test
