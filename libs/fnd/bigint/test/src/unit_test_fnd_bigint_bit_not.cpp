/**
 *	@file	unit_test_fnd_bigint_bit_not.cpp
 *
 *	@brief	bigint::operator~() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bigint.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_CLANG("-Wsign-compare");

namespace bksge_bigint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool BitNotTest()
{
	{
		auto x = ~BigInt{1};
		VERIFY(x == -2);
	}
	{
		auto x = ~BigInt{0xFFFF};
		VERIFY(x == -0x10000);
	}
	{
		auto x = ~BigInt{0xFFFFFFFF};
		VERIFY(x == -0x100000000);
	}
	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool BitNotLargeTest()
{
	{
		auto x = ~BigInt{0xFFFFFFFFFFFFFFFF};
		VERIFY(x == -BigInt{"0x10000000000000000"});
	}
	return true;
}

GTEST_TEST(BigIntTest, BitNotTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitNotTest<bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitNotTest<bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitNotTest<bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitNotTest<bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitNotTest<bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitNotTest<bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitNotTest<bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitNotTest<bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitNotTest<bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitNotTest<bksge::uint1024_t>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitNotLargeTest<bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitNotLargeTest<bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitNotLargeTest<bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitNotLargeTest<bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitNotLargeTest<bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitNotLargeTest<bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitNotLargeTest<bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitNotLargeTest<bksge::uint1024_t>()));
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
