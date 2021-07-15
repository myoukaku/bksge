/**
 *	@file	unit_test_fnd_bigint_bit_and.cpp
 *
 *	@brief	bigint::operator&=(), operator&(bigint, bigint) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bigint.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();

namespace bksge_bigint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool BitAndTest()
{
	{
		auto x = BigInt1{0xffffffff};
		VERIFY(x == 0xffffffff);

		x &= BigInt2(0x80ff000f);
		VERIFY(x == 0x80ff000f);

		x &= BigInt2{0x0000ffff};
		VERIFY(x == 0x0000000f);

		x &= BigInt2(1);
		VERIFY(x == 0x00000001);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool BitAndLargeTest()
{
	{
		auto x = BigInt1{0xffffffff};
		VERIFY(x == 0xffffffff);

		x &= BigInt2("0xFEDCBA9876543210000000000000000");
		VERIFY(x == 0);
	}
	{
		auto x = BigInt1{0x12345678};
		VERIFY(x == 0x12345678);

		x &= BigInt2("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
		VERIFY(x == 0x12345678);

		x &= BigInt2("0x000000000000000000000000000FFFF");
		VERIFY(x == 0x5678);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool BitAnd2Test()
{
	{
		auto x = BigInt1{0x35} & BigInt2{0xf0};
		VERIFY(x == 0x30);
	}
	{
		auto x = BigInt1{0x35} & BigInt2{0x0f};
		VERIFY(x == 0x05);
	}
	{
		auto x = BigInt1{0x0F} & BigInt2{0x12};
		VERIFY(x == 0x02);
	}
	{
		auto x = BigInt1{0x77} & BigInt2{0x20};
		VERIFY(x == 0x20);
	}
	{
		auto x = BigInt1{0x123456} & BigInt2{0xf00000};
		VERIFY(x == 0x100000);
	}
	{
		auto x = BigInt1{0x123456} & BigInt2{0x0f0000};
		VERIFY(x == 0x020000);
	}
	{
		auto x = BigInt1{0x123456} & BigInt2{0x00000f};
		VERIFY(x == 0x000006);
	}
	{
		auto x = BigInt1{0x123456} & BigInt2{0xf0f0f0};
		VERIFY(x == 0x103050);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool BitAnd2LargeTest()
{
	{
		auto x = BigInt1{0x01} & BigInt2{"0x8000000000000000000000000000000"};
		VERIFY(x == 0);
	}
	{
		auto x = BigInt1{"0x1234000000000000000000000000000"} & BigInt2{0x123};
		VERIFY(x == 0);
	}
	return true;
}

GTEST_TEST(BigIntTest, BitAndTest)
{
	EXPECT_TRUE((BitAndTest<bksge::bigint, bksge::bigint>()));
	EXPECT_TRUE((BitAndTest<bksge::bigint, std::int64_t>()));
	EXPECT_TRUE((BitAndTest<bksge::bigint, bksge::int128_t>()));
	EXPECT_TRUE((BitAndTest<bksge::bigint, bksge::int256_t>()));
	EXPECT_TRUE((BitAndTest<bksge::bigint, bksge::int512_t>()));
	EXPECT_TRUE((BitAndTest<bksge::bigint, bksge::int1024_t>()));
	EXPECT_TRUE((BitAndTest<bksge::bigint, std::uint64_t>()));
	EXPECT_TRUE((BitAndTest<bksge::bigint, bksge::uint128_t>()));
	EXPECT_TRUE((BitAndTest<bksge::bigint, bksge::uint256_t>()));
	EXPECT_TRUE((BitAndTest<bksge::bigint, bksge::uint512_t>()));
	EXPECT_TRUE((BitAndTest<bksge::bigint, bksge::uint1024_t>()));
//	EXPECT_TRUE((BitAndTest<std::int64_t, bksge::bigint>()));
	EXPECT_TRUE((BitAndTest<bksge::int128_t, bksge::bigint>()));
	EXPECT_TRUE((BitAndTest<bksge::int256_t, bksge::bigint>()));
	EXPECT_TRUE((BitAndTest<bksge::int512_t, bksge::bigint>()));
	EXPECT_TRUE((BitAndTest<bksge::int1024_t, bksge::bigint>()));
//	EXPECT_TRUE((BitAndTest<std::uint64_t, bksge::bigint>()));
	EXPECT_TRUE((BitAndTest<bksge::uint128_t, bksge::bigint>()));
	EXPECT_TRUE((BitAndTest<bksge::uint256_t, bksge::bigint>()));
	EXPECT_TRUE((BitAndTest<bksge::uint512_t, bksge::bigint>()));
	EXPECT_TRUE((BitAndTest<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int128_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int128_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int256_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int256_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int512_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int512_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int1024_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int1024_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint128_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint128_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint256_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint256_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint512_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint512_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint1024_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint1024_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndTest<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((BitAndLargeTest<bksge::bigint, bksge::bigint>()));
	EXPECT_TRUE((BitAndLargeTest<bksge::bigint, bksge::int128_t>()));
	EXPECT_TRUE((BitAndLargeTest<bksge::bigint, bksge::int256_t>()));
	EXPECT_TRUE((BitAndLargeTest<bksge::bigint, bksge::int512_t>()));
	EXPECT_TRUE((BitAndLargeTest<bksge::bigint, bksge::int1024_t>()));
	EXPECT_TRUE((BitAndLargeTest<bksge::bigint, bksge::uint128_t>()));
	EXPECT_TRUE((BitAndLargeTest<bksge::bigint, bksge::uint256_t>()));
	EXPECT_TRUE((BitAndLargeTest<bksge::bigint, bksge::uint512_t>()));
	EXPECT_TRUE((BitAndLargeTest<bksge::bigint, bksge::uint1024_t>()));
	EXPECT_TRUE((BitAndLargeTest<bksge::int128_t, bksge::bigint>()));
	EXPECT_TRUE((BitAndLargeTest<bksge::int256_t, bksge::bigint>()));
	EXPECT_TRUE((BitAndLargeTest<bksge::int512_t, bksge::bigint>()));
	EXPECT_TRUE((BitAndLargeTest<bksge::int1024_t, bksge::bigint>()));
	EXPECT_TRUE((BitAndLargeTest<bksge::uint128_t, bksge::bigint>()));
	EXPECT_TRUE((BitAndLargeTest<bksge::uint256_t, bksge::bigint>()));
	EXPECT_TRUE((BitAndLargeTest<bksge::uint512_t, bksge::bigint>()));
	EXPECT_TRUE((BitAndLargeTest<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAndLargeTest<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((BitAnd2Test<bksge::bigint, bksge::bigint>()));
	EXPECT_TRUE((BitAnd2Test<bksge::bigint, std::int64_t>()));
	EXPECT_TRUE((BitAnd2Test<bksge::bigint, bksge::int128_t>()));
	EXPECT_TRUE((BitAnd2Test<bksge::bigint, bksge::int256_t>()));
	EXPECT_TRUE((BitAnd2Test<bksge::bigint, bksge::int512_t>()));
	EXPECT_TRUE((BitAnd2Test<bksge::bigint, bksge::int1024_t>()));
	EXPECT_TRUE((BitAnd2Test<bksge::bigint, std::uint64_t>()));
	EXPECT_TRUE((BitAnd2Test<bksge::bigint, bksge::uint128_t>()));
	EXPECT_TRUE((BitAnd2Test<bksge::bigint, bksge::uint256_t>()));
	EXPECT_TRUE((BitAnd2Test<bksge::bigint, bksge::uint512_t>()));
	EXPECT_TRUE((BitAnd2Test<bksge::bigint, bksge::uint1024_t>()));
	EXPECT_TRUE((BitAnd2Test<std::int64_t, bksge::bigint>()));
	EXPECT_TRUE((BitAnd2Test<bksge::int128_t, bksge::bigint>()));
	EXPECT_TRUE((BitAnd2Test<bksge::int256_t, bksge::bigint>()));
	EXPECT_TRUE((BitAnd2Test<bksge::int512_t, bksge::bigint>()));
	EXPECT_TRUE((BitAnd2Test<bksge::int1024_t, bksge::bigint>()));
	EXPECT_TRUE((BitAnd2Test<std::uint64_t, bksge::bigint>()));
	EXPECT_TRUE((BitAnd2Test<bksge::uint128_t, bksge::bigint>()));
	EXPECT_TRUE((BitAnd2Test<bksge::uint256_t, bksge::bigint>()));
	EXPECT_TRUE((BitAnd2Test<bksge::uint512_t, bksge::bigint>()));
	EXPECT_TRUE((BitAnd2Test<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<std::int64_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<std::int64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<std::int64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<std::int64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<std::int64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<std::int64_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<std::int64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<std::int64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<std::int64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<std::int64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int128_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int128_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int256_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int256_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int512_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int512_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int1024_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int1024_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<std::uint64_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<std::uint64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<std::uint64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<std::uint64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<std::uint64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<std::uint64_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<std::uint64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<std::uint64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<std::uint64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<std::uint64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint128_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint128_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint256_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint256_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint512_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint512_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint1024_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint1024_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2Test<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((BitAnd2LargeTest<bksge::bigint, bksge::bigint>()));
	EXPECT_TRUE((BitAnd2LargeTest<bksge::bigint, bksge::int128_t>()));
	EXPECT_TRUE((BitAnd2LargeTest<bksge::bigint, bksge::int256_t>()));
	EXPECT_TRUE((BitAnd2LargeTest<bksge::bigint, bksge::int512_t>()));
	EXPECT_TRUE((BitAnd2LargeTest<bksge::bigint, bksge::int1024_t>()));
	EXPECT_TRUE((BitAnd2LargeTest<bksge::bigint, bksge::uint128_t>()));
	EXPECT_TRUE((BitAnd2LargeTest<bksge::bigint, bksge::uint256_t>()));
	EXPECT_TRUE((BitAnd2LargeTest<bksge::bigint, bksge::uint512_t>()));
	EXPECT_TRUE((BitAnd2LargeTest<bksge::bigint, bksge::uint1024_t>()));
	EXPECT_TRUE((BitAnd2LargeTest<bksge::int128_t, bksge::bigint>()));
	EXPECT_TRUE((BitAnd2LargeTest<bksge::int256_t, bksge::bigint>()));
	EXPECT_TRUE((BitAnd2LargeTest<bksge::int512_t, bksge::bigint>()));
	EXPECT_TRUE((BitAnd2LargeTest<bksge::int1024_t, bksge::bigint>()));
	EXPECT_TRUE((BitAnd2LargeTest<bksge::uint128_t, bksge::bigint>()));
	EXPECT_TRUE((BitAnd2LargeTest<bksge::uint256_t, bksge::bigint>()));
	EXPECT_TRUE((BitAnd2LargeTest<bksge::uint512_t, bksge::bigint>()));
	EXPECT_TRUE((BitAnd2LargeTest<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitAnd2LargeTest<bksge::uint1024_t, bksge::uint1024_t>()));
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
