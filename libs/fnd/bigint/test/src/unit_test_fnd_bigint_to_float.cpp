/**
 *	@file	unit_test_fnd_bigint_to_float.cpp
 *
 *	@brief	operator Arithmetic() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bigint.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4127);	// conditional expression is constant

namespace bksge_bigint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool ToFloatTest()
{
	{
		BigInt const x = 0;
		float       f(x);
		double      d(x);
		long double l(x);
		VERIFY(f == 0);
		VERIFY(d == 0);
		VERIFY(l == 0);
	}
	{
		BigInt const x = 1;
		float       f(x);
		double      d(x);
		long double l(x);
		VERIFY(f == 1);
		VERIFY(d == 1);
		VERIFY(l == 1);
	}
	{
		BigInt const x = -1;
		float       f(x);
		double      d(x);
		long double l(x);
		if (std::numeric_limits<BigInt>::is_signed)
		{
			VERIFY(f == -1);
			VERIFY(d == -1);
			VERIFY(l == -1);
		}
		else
		{
			VERIFY(f > 0);
			VERIFY(d > 0);
			VERIFY(l > 0);
		}
	}
	{
		BigInt const x = 123;
		float       f(x);
		double      d(x);
		long double l(x);
		VERIFY(f == 123);
		VERIFY(d == 123);
		VERIFY(l == 123);
	}
	if (std::numeric_limits<BigInt>::digits10 >= 40)
	{
		BigInt const x = std::numeric_limits<float>::max();
		float       f(x);
		double      d(x);
		long double l(x);
		VERIFY(f == std::numeric_limits<float>::max());
		VERIFY(d == std::numeric_limits<float>::max());
		VERIFY(l == std::numeric_limits<float>::max());
	}
	if (std::numeric_limits<BigInt>::digits10 >= 40)
	{
		BigInt const x = std::numeric_limits<float>::lowest();
		float       f(x);
		double      d(x);
		long double l(x);
		if (std::numeric_limits<BigInt>::is_signed)
		{
			VERIFY(f == std::numeric_limits<float>::lowest());
			VERIFY(d == std::numeric_limits<float>::lowest());
			VERIFY(l == std::numeric_limits<float>::lowest());
		}
		else
		{
			VERIFY(f > 0);
			VERIFY(d > 0);
			VERIFY(l > 0);
		}
	}
	return true;
}

GTEST_TEST(BigIntTest, ToFloatTest)
{
	EXPECT_TRUE((ToFloatTest<bksge::bigint>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((ToFloatTest<bksge::int128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((ToFloatTest<bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((ToFloatTest<bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((ToFloatTest<bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((ToFloatTest<bksge::uint128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((ToFloatTest<bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((ToFloatTest<bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((ToFloatTest<bksge::uint1024_t>()));
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
