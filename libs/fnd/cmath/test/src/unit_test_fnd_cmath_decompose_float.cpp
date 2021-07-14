/**
 *	@file	unit_test_fnd_cmath_decompose_float.cpp
 *
 *	@brief	decompose_float のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/decompose_float.hpp>
#include <bksge/fnd/cmath/pow.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace decompose_float_test
{

template <typename T>
bool DecomposeFloatTestImpl(T x)
{
	auto result = bksge::decompose_float(x);
	return x == T(result.fraction) * bksge::pow(T(2), result.exponent) * bksge::pow(T(-1), result.sign);
}

template <typename T>
void DecomposeFloatTest(void)
{
	EXPECT_TRUE(DecomposeFloatTestImpl(T( 0.0L)));
	EXPECT_TRUE(DecomposeFloatTestImpl(T(-0.0L)));
	EXPECT_TRUE(DecomposeFloatTestImpl(T( 0.5L)));
	EXPECT_TRUE(DecomposeFloatTestImpl(T(-0.5L)));
	EXPECT_TRUE(DecomposeFloatTestImpl(T( 1.5L)));
	EXPECT_TRUE(DecomposeFloatTestImpl(T(-1.5L)));
	EXPECT_TRUE(DecomposeFloatTestImpl(T( 1.125L)));
	EXPECT_TRUE(DecomposeFloatTestImpl(T(-1.125L)));
	EXPECT_TRUE(DecomposeFloatTestImpl(T(123.0L)));
	EXPECT_TRUE(DecomposeFloatTestImpl(T(12.3L)));
	EXPECT_TRUE(DecomposeFloatTestImpl(T(1.23L)));
	EXPECT_TRUE(DecomposeFloatTestImpl(T(0.123L)));
	EXPECT_TRUE(DecomposeFloatTestImpl(T(0.1L)));
	EXPECT_TRUE(DecomposeFloatTestImpl(T(0.2L)));
	EXPECT_TRUE(DecomposeFloatTestImpl(T(1.0L / 3.0L)));
	EXPECT_TRUE(DecomposeFloatTestImpl(std::numeric_limits<T>::max()));
	EXPECT_TRUE(DecomposeFloatTestImpl(std::numeric_limits<T>::min()));
	EXPECT_TRUE(DecomposeFloatTestImpl(std::numeric_limits<T>::lowest()));
	EXPECT_TRUE(DecomposeFloatTestImpl(std::numeric_limits<T>::denorm_min()));

	{
		// 0.0 == -1^0 * 0 * 2^0
		auto result = bksge::decompose_float(T(0.0L));
		EXPECT_EQ(0u, result.sign);
		EXPECT_EQ(0u, result.fraction);
		EXPECT_EQ(0,  result.exponent);
	}
	{
		// -0.0 == -1^1 * 0 * 2^0
		auto result = bksge::decompose_float(T(-0.0L));
		EXPECT_EQ(1u, result.sign);
		EXPECT_EQ(0u, result.fraction);
		EXPECT_EQ(0,  result.exponent);
	}
	{
		// 0.5 == -1^0 * 1 * 2^-1
		auto result = bksge::decompose_float(T(0.5L));
		EXPECT_EQ(0u, result.sign);
		EXPECT_EQ(1u, result.fraction);
		EXPECT_EQ(-1, result.exponent);
	}
	{
		// -0.5 == -1^1 * 1 * 2^-1
		auto result = bksge::decompose_float(T(-0.5L));
		EXPECT_EQ(1u, result.sign);
		EXPECT_EQ(1u, result.fraction);
		EXPECT_EQ(-1, result.exponent);
	}
	{
		// 1.5 == -1^0 * 3 * 2^-1
		auto result = bksge::decompose_float(T(1.5L));
		EXPECT_EQ(0u, result.sign);
		EXPECT_EQ(3u, result.fraction);
		EXPECT_EQ(-1, result.exponent);
	}
	{
		// -1.5 == -1^1 * 3 * 2^-1
		auto result = bksge::decompose_float(T(-1.5L));
		EXPECT_EQ(1u, result.sign);
		EXPECT_EQ(3u, result.fraction);
		EXPECT_EQ(-1, result.exponent);
	}
	{
		// 1.125 == -1^0 * 9 * 2^-3
		auto result = bksge::decompose_float(T(1.125L));
		EXPECT_EQ(0u, result.sign);
		EXPECT_EQ(9u, result.fraction);
		EXPECT_EQ(-3, result.exponent);
	}
	{
		// -1.125 == -1^1 * 9 * 2^-3
		auto result = bksge::decompose_float(T(-1.125L));
		EXPECT_EQ(1u, result.sign);
		EXPECT_EQ(9u, result.fraction);
		EXPECT_EQ(-3, result.exponent);
	}
	{
		// 123.0 == -1^0 * 123 * 2^0
		auto result = bksge::decompose_float(T(123.0L));
		EXPECT_EQ(0u,   result.sign);
		EXPECT_EQ(123u, result.fraction);
		EXPECT_EQ(0,    result.exponent);
	}
	{
		// infinity
		auto result = bksge::decompose_float(std::numeric_limits<T>::infinity());
		EXPECT_EQ(0u, result.sign);
		EXPECT_EQ(0u, result.fraction);
		EXPECT_EQ(0,  result.exponent);
	}
	{
		// -infinity
		auto result = bksge::decompose_float(-std::numeric_limits<T>::infinity());
		EXPECT_EQ(1u, result.sign);
		EXPECT_EQ(0u, result.fraction);
		EXPECT_EQ(0,  result.exponent);
	}
	{
		// NaN
		auto result = bksge::decompose_float(std::numeric_limits<T>::quiet_NaN());
		EXPECT_EQ(0u, result.sign);
		EXPECT_EQ(0u, result.fraction);
		EXPECT_EQ(0,  result.exponent);
	}
	{
		// -NaN
		auto result = bksge::decompose_float(-std::numeric_limits<T>::quiet_NaN());
		EXPECT_EQ(1u, result.sign);
		EXPECT_EQ(0u, result.fraction);
		EXPECT_EQ(0,  result.exponent);
	}
}

GTEST_TEST(CMathTest, DecomposeFloatTest)
{
	DecomposeFloatTest<float>();
	DecomposeFloatTest<double>();
	DecomposeFloatTest<long double>();

	// float
	{
		// 0.1f == -1^0 * 13421773 * 2^-27
		auto result = bksge::decompose_float(0.1f);
		EXPECT_EQ(0u, result.sign);
		EXPECT_EQ(13421773u, result.fraction);
		EXPECT_EQ(-27, result.exponent);
	}

	// double
	{
		// 0.1 == -1^0 * 3602879701896397 * 2^-55
		auto result = bksge::decompose_float(0.1);
		EXPECT_EQ(0u, result.sign);
		EXPECT_EQ(3602879701896397u, result.fraction);
		EXPECT_EQ(-55, result.exponent);
	}

	// long double
#if LDBL_MANT_DIG == 53
	// binary64
	{
		// 0.1L == -1^0 * 3602879701896397 * 2^-55
		auto result = bksge::decompose_float(0.1L);
		EXPECT_EQ(0u, result.sign);
		EXPECT_EQ(3602879701896397u, result.fraction);
		EXPECT_EQ(-55, result.exponent);
	}
#elif LDBL_MANT_DIG == 64
	// binary80
	{
		// 0.1L == -1^0 * 14757395258967641293 * 2^-55
		auto result = bksge::decompose_float(0.1L);
		EXPECT_EQ(0u, result.sign);
		EXPECT_EQ(14757395258967641293u, result.fraction);
		EXPECT_EQ(-67, result.exponent);
	}
#else
	// binary128
	// TODO
	#error "not implemented yet"
#endif
}

}	// namespace decompose_float_test

}	// namespace bksge_cmath_test
