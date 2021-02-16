/**
 *	@file	unit_test_fnd_bigint_bit_shift_right.cpp
 *
 *	@brief	bigint::operator>>=(), operator>>(bigint, bigint) のテスト
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
inline BKSGE_CXX14_CONSTEXPR bool BitShiftRightTest()
{
	{
		auto x = BigInt1{12345678};
		VERIFY(x == 12345678);

		x >>= BigInt2(1);
		VERIFY(x == 6172839);

		x >>= BigInt2(2);
		VERIFY(x == 1543209);

		x >>= BigInt2(3);
		VERIFY(x == 192901);

		x >>= BigInt2(10);
		VERIFY(x == 188);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool BitShiftRightLargeTest()
{
	{
		auto x = BigInt1{"0x1234567890123456789012345678901234567890"};

		x >>= BigInt2{4};
		VERIFY(x == BigInt1{"0x123456789012345678901234567890123456789"});

		x >>= BigInt2{"0x100000000000000000000000000000000000000"};
		VERIFY(x == 0);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool BitShiftRight2Test()
{
	{
		auto x = BigInt1{0x1234} >> BigInt2{1};
		VERIFY(x == 0x91a);
	}
	{
		auto x = BigInt1{0xffff} >> BigInt2{1};
		VERIFY(x == 0x7fff);
	}
	{
		auto x = BigInt1{0xffffff} >> BigInt2{2};
		VERIFY(x == 0x3fffff);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool BitShiftRight2LargeTest()
{
	{
		auto x = BigInt1{"0x123400000000000000000000000000000000"} >> BigInt2{128};
		VERIFY(x == 0x1234);
	}
	{
		auto x = BigInt1{"0x123400000000000000000000000000000000"} >> BigInt2{129};
		VERIFY(x == 0x91a);
	}
	{
		auto x = BigInt1{"0x12340000000000000000000000000000000000000000000000000000000000000000"} >> BigInt2{255};
		VERIFY(x == 0x2468);
	}
	{
		auto x = BigInt1{"0x12340000000000000000000000000000000000000000000000000000000000000000"} >> BigInt2{256};
		VERIFY(x == 0x1234);
	}
	return true;
}

GTEST_TEST(BigIntTest, BitShiftRightTest)
{
	EXPECT_TRUE((BitShiftRightTest<bksge::bigint, bksge::bigint>()));
	EXPECT_TRUE((BitShiftRightTest<bksge::bigint, bksge::int32_t>()));
	EXPECT_TRUE((BitShiftRightTest<bksge::bigint, bksge::int64_t>()));
	EXPECT_TRUE((BitShiftRightTest<bksge::bigint, bksge::int128_t>()));
	EXPECT_TRUE((BitShiftRightTest<bksge::bigint, bksge::int256_t>()));
	EXPECT_TRUE((BitShiftRightTest<bksge::bigint, bksge::int512_t>()));
	EXPECT_TRUE((BitShiftRightTest<bksge::bigint, bksge::int1024_t>()));
	EXPECT_TRUE((BitShiftRightTest<bksge::bigint, bksge::uint32_t>()));
	EXPECT_TRUE((BitShiftRightTest<bksge::bigint, bksge::uint64_t>()));
	EXPECT_TRUE((BitShiftRightTest<bksge::bigint, bksge::uint128_t>()));
	EXPECT_TRUE((BitShiftRightTest<bksge::bigint, bksge::uint256_t>()));
	EXPECT_TRUE((BitShiftRightTest<bksge::bigint, bksge::uint512_t>()));
	EXPECT_TRUE((BitShiftRightTest<bksge::bigint, bksge::uint1024_t>()));
//	EXPECT_TRUE((BitShiftRightTest<bksge::int32_t,    bksge::bigint>()));
//	EXPECT_TRUE((BitShiftRightTest<bksge::int64_t,    bksge::bigint>()));
	EXPECT_TRUE((BitShiftRightTest<bksge::int128_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftRightTest<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftRightTest<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftRightTest<bksge::int1024_t,  bksge::bigint>()));
//	EXPECT_TRUE((BitShiftRightTest<bksge::uint32_t,   bksge::bigint>()));
//	EXPECT_TRUE((BitShiftRightTest<bksge::uint64_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftRightTest<bksge::uint128_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftRightTest<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftRightTest<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftRightTest<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int32_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int32_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int32_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int32_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int32_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int32_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int32_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int32_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int64_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int64_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int64_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int64_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int64_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int64_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int64_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int64_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int256_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint32_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint32_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint32_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint32_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint32_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint32_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint32_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint32_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint64_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint64_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint64_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint64_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint64_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint64_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint64_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint64_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint256_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightTest<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((BitShiftRightLargeTest<bksge::bigint, bksge::bigint>()));
	EXPECT_TRUE((BitShiftRightLargeTest<bksge::bigint, bksge::int256_t>()));
	EXPECT_TRUE((BitShiftRightLargeTest<bksge::bigint, bksge::int512_t>()));
	EXPECT_TRUE((BitShiftRightLargeTest<bksge::bigint, bksge::int1024_t>()));
	EXPECT_TRUE((BitShiftRightLargeTest<bksge::bigint, bksge::uint256_t>()));
	EXPECT_TRUE((BitShiftRightLargeTest<bksge::bigint, bksge::uint512_t>()));
	EXPECT_TRUE((BitShiftRightLargeTest<bksge::bigint, bksge::uint1024_t>()));
	EXPECT_TRUE((BitShiftRightLargeTest<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftRightLargeTest<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftRightLargeTest<bksge::int1024_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRightLargeTest<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((BitShiftRight2Test<bksge::bigint, bksge::bigint>()));
	EXPECT_TRUE((BitShiftRight2Test<bksge::bigint, bksge::int32_t>()));
	EXPECT_TRUE((BitShiftRight2Test<bksge::bigint, bksge::int64_t>()));
	EXPECT_TRUE((BitShiftRight2Test<bksge::bigint, bksge::int128_t>()));
	EXPECT_TRUE((BitShiftRight2Test<bksge::bigint, bksge::int256_t>()));
	EXPECT_TRUE((BitShiftRight2Test<bksge::bigint, bksge::int512_t>()));
	EXPECT_TRUE((BitShiftRight2Test<bksge::bigint, bksge::int1024_t>()));
	EXPECT_TRUE((BitShiftRight2Test<bksge::bigint, bksge::uint32_t>()));
	EXPECT_TRUE((BitShiftRight2Test<bksge::bigint, bksge::uint64_t>()));
	EXPECT_TRUE((BitShiftRight2Test<bksge::bigint, bksge::uint128_t>()));
	EXPECT_TRUE((BitShiftRight2Test<bksge::bigint, bksge::uint256_t>()));
	EXPECT_TRUE((BitShiftRight2Test<bksge::bigint, bksge::uint512_t>()));
	EXPECT_TRUE((BitShiftRight2Test<bksge::bigint, bksge::uint1024_t>()));
//	EXPECT_TRUE((BitShiftRight2Test<bksge::int32_t,    bksge::bigint>()));
//	EXPECT_TRUE((BitShiftRight2Test<bksge::int64_t,    bksge::bigint>()));
	EXPECT_TRUE((BitShiftRight2Test<bksge::int128_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftRight2Test<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftRight2Test<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftRight2Test<bksge::int1024_t,  bksge::bigint>()));
//	EXPECT_TRUE((BitShiftRight2Test<bksge::uint32_t,   bksge::bigint>()));
//	EXPECT_TRUE((BitShiftRight2Test<bksge::uint64_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftRight2Test<bksge::uint128_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftRight2Test<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftRight2Test<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftRight2Test<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int32_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int32_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int32_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int32_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int32_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int32_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int32_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int32_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int64_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int64_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int256_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint32_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint32_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint32_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint32_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint32_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint32_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint32_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint32_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint64_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint64_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint256_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2Test<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((BitShiftRight2LargeTest<bksge::bigint, bksge::bigint>()));
	EXPECT_TRUE((BitShiftRight2LargeTest<bksge::bigint, bksge::int128_t>()));
	EXPECT_TRUE((BitShiftRight2LargeTest<bksge::bigint, bksge::int256_t>()));
	EXPECT_TRUE((BitShiftRight2LargeTest<bksge::bigint, bksge::int512_t>()));
	EXPECT_TRUE((BitShiftRight2LargeTest<bksge::bigint, bksge::int1024_t>()));
	EXPECT_TRUE((BitShiftRight2LargeTest<bksge::bigint, bksge::uint128_t>()));
	EXPECT_TRUE((BitShiftRight2LargeTest<bksge::bigint, bksge::uint256_t>()));
	EXPECT_TRUE((BitShiftRight2LargeTest<bksge::bigint, bksge::uint512_t>()));
	EXPECT_TRUE((BitShiftRight2LargeTest<bksge::bigint, bksge::uint1024_t>()));
//	EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int128_t,   bksge::bigint>()));
//	EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int1024_t,  bksge::bigint>()));
//	EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint128_t,  bksge::bigint>()));
//	EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftRight2LargeTest<bksge::uint1024_t, bksge::uint1024_t>()));
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
