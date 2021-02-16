/**
 *	@file	unit_test_fnd_bigint_bit_or.cpp
 *
 *	@brief	bigint::operator|=(), operator|(bigint, bigint) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bigint.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();

namespace bksge_bigint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool BitOrTest()
{
	{
		auto x = BigInt1{0};
		VERIFY(x == 0);

		x |= BigInt2(1);
		VERIFY(x == 0x0001);

		x |= BigInt2(0x8000);
		VERIFY(x == 0x8001);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool BitOrLargeTest()
{
	{
		auto x = BigInt1{0x8001};
		VERIFY(x == 0x8001);

		x |= BigInt2{"0xFEDCBA9876543210000000000000000"};
		VERIFY(x == BigInt1{"0xFEDCBA9876543210000000000008001"});
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool BitOr2Test()
{
	{
		auto x = BigInt1{0x0F} | BigInt2{0x35};
		VERIFY(x == 0x3F);
	}
	{
		auto x = BigInt1{0x35} | BigInt2{0xf0};
		VERIFY(x == 0xF5);
	}
	{
		auto x = BigInt1{0x0F} | BigInt2{0x12};
		VERIFY(x == 0x1F);
	}
	{
		auto x = BigInt1{0x77} | BigInt2{0x20};
		VERIFY(x == 0x77);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool BitOr2LargeTest()
{
	{
		auto x = BigInt1{0x01} | BigInt2{"0x8000000000000000000000000000000"};
		VERIFY(x == BigInt2{"0x8000000000000000000000000000001"});
	}
	{
		auto x = BigInt1{"0x1234000000000000000000000000000"} | BigInt2{0x123};
		VERIFY(x == BigInt2{"0x1234000000000000000000000000123"});
	}
	return true;
}

GTEST_TEST(BigIntTest, BitOrTest)
{
	EXPECT_TRUE((BitOrTest<bksge::bigint, bksge::bigint>()));
	EXPECT_TRUE((BitOrTest<bksge::bigint, bksge::int64_t>()));
	EXPECT_TRUE((BitOrTest<bksge::bigint, bksge::int128_t>()));
	EXPECT_TRUE((BitOrTest<bksge::bigint, bksge::int256_t>()));
	EXPECT_TRUE((BitOrTest<bksge::bigint, bksge::int512_t>()));
	EXPECT_TRUE((BitOrTest<bksge::bigint, bksge::int1024_t>()));
	EXPECT_TRUE((BitOrTest<bksge::bigint, bksge::uint64_t>()));
	EXPECT_TRUE((BitOrTest<bksge::bigint, bksge::uint128_t>()));
	EXPECT_TRUE((BitOrTest<bksge::bigint, bksge::uint256_t>()));
	EXPECT_TRUE((BitOrTest<bksge::bigint, bksge::uint512_t>()));
	EXPECT_TRUE((BitOrTest<bksge::bigint, bksge::uint1024_t>()));
//	EXPECT_TRUE((BitOrTest<bksge::int64_t, bksge::bigint>()));
	EXPECT_TRUE((BitOrTest<bksge::int128_t, bksge::bigint>()));
	EXPECT_TRUE((BitOrTest<bksge::int256_t, bksge::bigint>()));
	EXPECT_TRUE((BitOrTest<bksge::int512_t, bksge::bigint>()));
	EXPECT_TRUE((BitOrTest<bksge::int1024_t, bksge::bigint>()));
//	EXPECT_TRUE((BitOrTest<bksge::uint64_t, bksge::bigint>()));
	EXPECT_TRUE((BitOrTest<bksge::uint128_t, bksge::bigint>()));
	EXPECT_TRUE((BitOrTest<bksge::uint256_t, bksge::bigint>()));
	EXPECT_TRUE((BitOrTest<bksge::uint512_t, bksge::bigint>()));
	EXPECT_TRUE((BitOrTest<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrTest<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((BitOrLargeTest<bksge::bigint, bksge::bigint>()));
	EXPECT_TRUE((BitOrLargeTest<bksge::bigint, bksge::int128_t>()));
	EXPECT_TRUE((BitOrLargeTest<bksge::bigint, bksge::int256_t>()));
	EXPECT_TRUE((BitOrLargeTest<bksge::bigint, bksge::int512_t>()));
	EXPECT_TRUE((BitOrLargeTest<bksge::bigint, bksge::int1024_t>()));
	EXPECT_TRUE((BitOrLargeTest<bksge::bigint, bksge::uint128_t>()));
	EXPECT_TRUE((BitOrLargeTest<bksge::bigint, bksge::uint256_t>()));
	EXPECT_TRUE((BitOrLargeTest<bksge::bigint, bksge::uint512_t>()));
	EXPECT_TRUE((BitOrLargeTest<bksge::bigint, bksge::uint1024_t>()));
	EXPECT_TRUE((BitOrLargeTest<bksge::int128_t, bksge::bigint>()));
	EXPECT_TRUE((BitOrLargeTest<bksge::int256_t, bksge::bigint>()));
	EXPECT_TRUE((BitOrLargeTest<bksge::int512_t, bksge::bigint>()));
	EXPECT_TRUE((BitOrLargeTest<bksge::int1024_t, bksge::bigint>()));
	EXPECT_TRUE((BitOrLargeTest<bksge::uint128_t, bksge::bigint>()));
	EXPECT_TRUE((BitOrLargeTest<bksge::uint256_t, bksge::bigint>()));
	EXPECT_TRUE((BitOrLargeTest<bksge::uint512_t, bksge::bigint>()));
	EXPECT_TRUE((BitOrLargeTest<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOrLargeTest<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((BitOr2Test<bksge::bigint, bksge::bigint>()));
	EXPECT_TRUE((BitOr2Test<bksge::bigint, bksge::int64_t>()));
	EXPECT_TRUE((BitOr2Test<bksge::bigint, bksge::int128_t>()));
	EXPECT_TRUE((BitOr2Test<bksge::bigint, bksge::int256_t>()));
	EXPECT_TRUE((BitOr2Test<bksge::bigint, bksge::int512_t>()));
	EXPECT_TRUE((BitOr2Test<bksge::bigint, bksge::int1024_t>()));
	EXPECT_TRUE((BitOr2Test<bksge::bigint, bksge::uint64_t>()));
	EXPECT_TRUE((BitOr2Test<bksge::bigint, bksge::uint128_t>()));
	EXPECT_TRUE((BitOr2Test<bksge::bigint, bksge::uint256_t>()));
	EXPECT_TRUE((BitOr2Test<bksge::bigint, bksge::uint512_t>()));
	EXPECT_TRUE((BitOr2Test<bksge::bigint, bksge::uint1024_t>()));
	EXPECT_TRUE((BitOr2Test<bksge::int64_t, bksge::bigint>()));
	EXPECT_TRUE((BitOr2Test<bksge::int128_t, bksge::bigint>()));
	EXPECT_TRUE((BitOr2Test<bksge::int256_t, bksge::bigint>()));
	EXPECT_TRUE((BitOr2Test<bksge::int512_t, bksge::bigint>()));
	EXPECT_TRUE((BitOr2Test<bksge::int1024_t, bksge::bigint>()));
	EXPECT_TRUE((BitOr2Test<bksge::uint64_t, bksge::bigint>()));
	EXPECT_TRUE((BitOr2Test<bksge::uint128_t, bksge::bigint>()));
	EXPECT_TRUE((BitOr2Test<bksge::uint256_t, bksge::bigint>()));
	EXPECT_TRUE((BitOr2Test<bksge::uint512_t, bksge::bigint>()));
	EXPECT_TRUE((BitOr2Test<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int64_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int64_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint64_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint64_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2Test<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((BitOr2LargeTest<bksge::bigint, bksge::bigint>()));
	EXPECT_TRUE((BitOr2LargeTest<bksge::bigint, bksge::int128_t>()));
	EXPECT_TRUE((BitOr2LargeTest<bksge::bigint, bksge::int256_t>()));
	EXPECT_TRUE((BitOr2LargeTest<bksge::bigint, bksge::int512_t>()));
	EXPECT_TRUE((BitOr2LargeTest<bksge::bigint, bksge::int1024_t>()));
	EXPECT_TRUE((BitOr2LargeTest<bksge::bigint, bksge::uint128_t>()));
	EXPECT_TRUE((BitOr2LargeTest<bksge::bigint, bksge::uint256_t>()));
	EXPECT_TRUE((BitOr2LargeTest<bksge::bigint, bksge::uint512_t>()));
	EXPECT_TRUE((BitOr2LargeTest<bksge::bigint, bksge::uint1024_t>()));
	EXPECT_TRUE((BitOr2LargeTest<bksge::int128_t, bksge::bigint>()));
	EXPECT_TRUE((BitOr2LargeTest<bksge::int256_t, bksge::bigint>()));
	EXPECT_TRUE((BitOr2LargeTest<bksge::int512_t, bksge::bigint>()));
	EXPECT_TRUE((BitOr2LargeTest<bksge::int1024_t, bksge::bigint>()));
	EXPECT_TRUE((BitOr2LargeTest<bksge::uint128_t, bksge::bigint>()));
	EXPECT_TRUE((BitOr2LargeTest<bksge::uint256_t, bksge::bigint>()));
	EXPECT_TRUE((BitOr2LargeTest<bksge::uint512_t, bksge::bigint>()));
	EXPECT_TRUE((BitOr2LargeTest<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitOr2LargeTest<bksge::uint1024_t, bksge::uint1024_t>()));
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
