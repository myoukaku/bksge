/**
 *	@file	unit_test_fnd_bigint_bit_shift_left.cpp
 *
 *	@brief	bigint::operator<<=(), operator<<(bigint, bigint) のテスト
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
inline BKSGE_CXX14_CONSTEXPR bool BitShiftLeftTest()
{
	{
		auto x = BigInt1{1};
		VERIFY(x == 0x01);

		x <<= BigInt2(1);
		VERIFY(x == 0x02);

		x <<= BigInt2(1);
		VERIFY(x == 0x04);

		x <<= BigInt2(2);
		VERIFY(x == 0x10);

		x <<= BigInt2(4);
		VERIFY(x == 0x100);
	}
	{
		auto x = BigInt1{0xff};
		VERIFY(x == 0xff);

		x <<= BigInt2(4);
		VERIFY(x == 0xff0);

		x <<= BigInt2(8);
		VERIFY(x == 0xff000);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool BitShiftLeft2Test()
{
	{
		auto x = BigInt1{0x1234} << BigInt2{1};
		VERIFY(x == 0x2468ULL);
	}
	{
		auto x = BigInt1{0x1234} << BigInt2{31};
		VERIFY(x == 0x91a00000000ULL);
	}
	{
		auto x = BigInt1{0x1234} << BigInt2{32};
		VERIFY(x == 0x123400000000ULL);
	}
	{
		auto x = BigInt1{0x1234} << BigInt2{33};
		VERIFY(x == 0x246800000000ULL);
	}
	{
		auto x = BigInt1{0x1234} << BigInt2{34};
		VERIFY(x == 0x48d000000000ULL);
	}
	{
		auto x = BigInt1{0x1234} << BigInt2{40};
		VERIFY(x == 0x12340000000000ULL);
	}
	{
		auto x = BigInt1{0x1234} << BigInt2{41};
		VERIFY(x == 0x24680000000000ULL);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool BitShiftLeft2LargeTest()
{
	{
		auto x = BigInt1{0x1234} << BigInt2{64};
		using result_type = decltype(x);
		VERIFY(x == result_type{"0x12340000000000000000"});
	}
	{
		auto x = BigInt1{0x1234} << BigInt2{65};
		using result_type = decltype(x);
		VERIFY(x == result_type{"0x24680000000000000000"});
	}
	{
		auto x = BigInt1{0x1234} << BigInt2{128};
		using result_type = decltype(x);
		VERIFY(x == result_type{"0x123400000000000000000000000000000000"});
	}
	{
		auto x = BigInt1{0x1234} << BigInt2{256};
		using result_type = decltype(x);
		VERIFY(x == result_type{"0x12340000000000000000000000000000000000000000000000000000000000000000"});
	}
	return true;
}

GTEST_TEST(BigIntTest, BitShiftLeftTest)
{
	EXPECT_TRUE((BitShiftLeftTest<bksge::bigint, bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeftTest<bksge::bigint, bksge::int32_t>()));
	EXPECT_TRUE((BitShiftLeftTest<bksge::bigint, bksge::int64_t>()));
	EXPECT_TRUE((BitShiftLeftTest<bksge::bigint, bksge::int128_t>()));
	EXPECT_TRUE((BitShiftLeftTest<bksge::bigint, bksge::int256_t>()));
	EXPECT_TRUE((BitShiftLeftTest<bksge::bigint, bksge::int512_t>()));
	EXPECT_TRUE((BitShiftLeftTest<bksge::bigint, bksge::int1024_t>()));
	EXPECT_TRUE((BitShiftLeftTest<bksge::bigint, bksge::uint32_t>()));
	EXPECT_TRUE((BitShiftLeftTest<bksge::bigint, bksge::uint64_t>()));
	EXPECT_TRUE((BitShiftLeftTest<bksge::bigint, bksge::uint128_t>()));
	EXPECT_TRUE((BitShiftLeftTest<bksge::bigint, bksge::uint256_t>()));
	EXPECT_TRUE((BitShiftLeftTest<bksge::bigint, bksge::uint512_t>()));
	EXPECT_TRUE((BitShiftLeftTest<bksge::bigint, bksge::uint1024_t>()));
//	EXPECT_TRUE((BitShiftLeftTest<bksge::int32_t,    bksge::bigint>()));
//	EXPECT_TRUE((BitShiftLeftTest<bksge::int64_t,    bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeftTest<bksge::int128_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeftTest<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeftTest<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeftTest<bksge::int1024_t,  bksge::bigint>()));
//	EXPECT_TRUE((BitShiftLeftTest<bksge::uint32_t,   bksge::bigint>()));
//	EXPECT_TRUE((BitShiftLeftTest<bksge::uint64_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeftTest<bksge::uint128_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeftTest<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeftTest<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeftTest<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int32_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int32_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int32_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int32_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int32_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int32_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int32_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int32_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int64_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int64_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int64_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int64_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int64_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int64_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int64_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int64_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int256_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint32_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint32_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint32_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint32_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint32_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint32_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint32_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint32_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint64_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint64_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint64_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint64_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint64_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint64_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint64_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint64_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint256_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeftTest<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((BitShiftLeft2Test<bksge::bigint, bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::bigint, bksge::int32_t>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::bigint, bksge::int64_t>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::bigint, bksge::int128_t>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::bigint, bksge::int256_t>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::bigint, bksge::int512_t>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::bigint, bksge::int1024_t>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::bigint, bksge::uint32_t>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::bigint, bksge::uint64_t>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::bigint, bksge::uint128_t>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::bigint, bksge::uint256_t>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::bigint, bksge::uint512_t>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::bigint, bksge::uint1024_t>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::int32_t,    bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::int64_t,    bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::int128_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::int1024_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::uint32_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::uint64_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::uint128_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeft2Test<bksge::uint1024_t, bksge::bigint>()));

	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int32_t, bksge::int32_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int32_t, bksge::int64_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int32_t, bksge::int128_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int32_t, bksge::int256_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int32_t, bksge::int512_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int32_t, bksge::int1024_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int32_t, bksge::uint32_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int32_t, bksge::uint64_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int32_t, bksge::uint128_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int32_t, bksge::uint256_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int32_t, bksge::uint512_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int64_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int64_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int256_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::int1024_t, bksge::uint1024_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint32_t, bksge::int32_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint32_t, bksge::int64_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint32_t, bksge::int128_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint32_t, bksge::int256_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint32_t, bksge::int512_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint32_t, bksge::int1024_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint32_t, bksge::uint32_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint32_t, bksge::uint64_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint32_t, bksge::uint128_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint32_t, bksge::uint256_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint32_t, bksge::uint512_t>()));
	//BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint64_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint64_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint256_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2Test<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::bigint, bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::bigint, bksge::int32_t>()));
	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::bigint, bksge::int64_t>()));
	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::bigint, bksge::int128_t>()));
	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::bigint, bksge::int256_t>()));
	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::bigint, bksge::int512_t>()));
	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::bigint, bksge::int1024_t>()));
	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::bigint, bksge::uint32_t>()));
	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::bigint, bksge::uint64_t>()));
	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::bigint, bksge::uint128_t>()));
	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::bigint, bksge::uint256_t>()));
	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::bigint, bksge::uint512_t>()));
	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::bigint, bksge::uint1024_t>()));
	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int128_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int1024_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint128_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((BitShiftLeft2LargeTest<bksge::uint1024_t, bksge::uint1024_t>()));
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
