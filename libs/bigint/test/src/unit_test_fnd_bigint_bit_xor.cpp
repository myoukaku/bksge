/**
 *	@file	unit_test_fnd_bigint_bit_xor.cpp
 *
 *	@brief	bigint::operator^=(), operator^(bigint, bigint) のテスト
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
inline BKSGE_CXX14_CONSTEXPR bool BitXorTest()
{
	{
		auto x = BigInt1{0};
		VERIFY(x == 0);

		x ^= BigInt2(1);
		VERIFY(x == 0x0001);

		x ^= BigInt2(1);
		VERIFY(x == 0x0000);

		x ^= BigInt2(0x1234);
		VERIFY(x == 0x1234);

		x ^= BigInt2(0xff00);
		VERIFY(x == 0xed34);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool BitXor2Test()
{
	{
		auto x = BigInt1{0xFA} ^ BigInt2{0x47};
		VERIFY(x == 0xBD);
	}
	{
		auto x = BigInt1{0x35} ^ BigInt2{0xf0};
		VERIFY(x == 0xC5);
	}
	{
		auto x = BigInt1{0x73} ^ BigInt2{0x20};
		VERIFY(x == 0x53);
	}
	return true;
}

GTEST_TEST(BigIntTest, BitXorTest)
{
	EXPECT_TRUE((BitXorTest<bksge::bigint, bksge::bigint>()));
	EXPECT_TRUE((BitXorTest<bksge::bigint, bksge::int32_t>()));
	EXPECT_TRUE((BitXorTest<bksge::bigint, bksge::int64_t>()));
	EXPECT_TRUE((BitXorTest<bksge::bigint, bksge::int128_t>()));
	EXPECT_TRUE((BitXorTest<bksge::bigint, bksge::int256_t>()));
	EXPECT_TRUE((BitXorTest<bksge::bigint, bksge::int512_t>()));
	EXPECT_TRUE((BitXorTest<bksge::bigint, bksge::int1024_t>()));
	EXPECT_TRUE((BitXorTest<bksge::bigint, bksge::uint32_t>()));
	EXPECT_TRUE((BitXorTest<bksge::bigint, bksge::uint64_t>()));
	EXPECT_TRUE((BitXorTest<bksge::bigint, bksge::uint128_t>()));
	EXPECT_TRUE((BitXorTest<bksge::bigint, bksge::uint256_t>()));
	EXPECT_TRUE((BitXorTest<bksge::bigint, bksge::uint512_t>()));
	EXPECT_TRUE((BitXorTest<bksge::bigint, bksge::uint1024_t>()));
//	EXPECT_TRUE((BitXorTest<bksge::int32_t,    bksge::bigint>()));
//	EXPECT_TRUE((BitXorTest<bksge::int64_t,    bksge::bigint>()));
	EXPECT_TRUE((BitXorTest<bksge::int128_t,   bksge::bigint>()));
	EXPECT_TRUE((BitXorTest<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((BitXorTest<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((BitXorTest<bksge::int1024_t,  bksge::bigint>()));
//	EXPECT_TRUE((BitXorTest<bksge::uint32_t,   bksge::bigint>()));
//	EXPECT_TRUE((BitXorTest<bksge::uint64_t,   bksge::bigint>()));
	EXPECT_TRUE((BitXorTest<bksge::uint128_t,  bksge::bigint>()));
	EXPECT_TRUE((BitXorTest<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((BitXorTest<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((BitXorTest<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int32_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int32_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int32_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int32_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int32_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int32_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int32_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int32_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int64_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int64_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int64_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int64_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int64_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int64_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int64_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int64_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int256_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint32_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint32_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint32_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint32_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint32_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint32_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint32_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint32_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint64_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint64_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint64_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint64_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint64_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint64_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint64_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint64_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint256_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXorTest<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((BitXor2Test<bksge::bigint, bksge::bigint>()));
	EXPECT_TRUE((BitXor2Test<bksge::bigint, bksge::int32_t>()));
	EXPECT_TRUE((BitXor2Test<bksge::bigint, bksge::int64_t>()));
	EXPECT_TRUE((BitXor2Test<bksge::bigint, bksge::int128_t>()));
	EXPECT_TRUE((BitXor2Test<bksge::bigint, bksge::int256_t>()));
	EXPECT_TRUE((BitXor2Test<bksge::bigint, bksge::int512_t>()));
	EXPECT_TRUE((BitXor2Test<bksge::bigint, bksge::int1024_t>()));
	EXPECT_TRUE((BitXor2Test<bksge::bigint, bksge::uint32_t>()));
	EXPECT_TRUE((BitXor2Test<bksge::bigint, bksge::uint64_t>()));
	EXPECT_TRUE((BitXor2Test<bksge::bigint, bksge::uint128_t>()));
	EXPECT_TRUE((BitXor2Test<bksge::bigint, bksge::uint256_t>()));
	EXPECT_TRUE((BitXor2Test<bksge::bigint, bksge::uint512_t>()));
	EXPECT_TRUE((BitXor2Test<bksge::bigint, bksge::uint1024_t>()));
	EXPECT_TRUE((BitXor2Test<bksge::int32_t,    bksge::bigint>()));
	EXPECT_TRUE((BitXor2Test<bksge::int64_t,    bksge::bigint>()));
	EXPECT_TRUE((BitXor2Test<bksge::int128_t,   bksge::bigint>()));
	EXPECT_TRUE((BitXor2Test<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((BitXor2Test<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((BitXor2Test<bksge::int1024_t,  bksge::bigint>()));
	EXPECT_TRUE((BitXor2Test<bksge::uint32_t,   bksge::bigint>()));
	EXPECT_TRUE((BitXor2Test<bksge::uint64_t,   bksge::bigint>()));
	EXPECT_TRUE((BitXor2Test<bksge::uint128_t,  bksge::bigint>()));
	EXPECT_TRUE((BitXor2Test<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((BitXor2Test<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((BitXor2Test<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int32_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int32_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int32_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int32_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int32_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int32_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int32_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int32_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int64_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int64_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int256_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint32_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint32_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint32_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint32_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint32_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint32_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint32_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint32_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint64_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint64_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint256_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitXor2Test<bksge::uint1024_t, bksge::uint1024_t>()));
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
