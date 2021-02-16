/**
 *	@file	unit_test_fnd_bigint_mod.cpp
 *
 *	@brief	bigint::operator%=(), operator%(bigint, bigint) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bigint.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded");
BKSGE_WARNING_DISABLE_CLANG("-Wsign-compare");
BKSGE_WARNING_DISABLE_MSVC(4127);	// conditional expression is constant

namespace bksge_bigint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool ModTest()
{
	{
		auto x = BigInt1{12345};
		VERIFY(x == 12345);

		x %= BigInt2(678);
		VERIFY(x == 141);

		x %= BigInt2{13};
		VERIFY(x == 11);

		x %= BigInt2(20);
		VERIFY(x == 11);

		x %= BigInt2{11};
		VERIFY(x == 0);

		x %= BigInt2(1);
		VERIFY(x == 0);
	}
	if (bksge::numeric_limits<BigInt1>::is_signed &&
		bksge::numeric_limits<BigInt2>::is_signed)
	{
		auto x = BigInt1(-51);
		VERIFY(x == -51);

		x %= BigInt2{13};
		VERIFY(x == -12);

		x %= -7;
		VERIFY(x == -5);

		x %= BigInt2{5};
		VERIFY(x == 0);
	}
	{
		BigInt1 x{0xffff};
		VERIFY(x == 0xffff);

		x %= x;
		VERIFY(x == 0);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool Mod2Test()
{
	{
		auto x = BigInt1( 6) % BigInt2( 3);
		VERIFY(x == 0);
	}
	{
		auto x = BigInt1(-6) % BigInt2( 3);
		VERIFY(x == 0);
	}
	{
		auto x = BigInt1( 6) % BigInt2(-3);
		VERIFY(x == 0);
	}
	{
		auto x = BigInt1(-6) % BigInt2(-3);
		VERIFY(x == 0);
	}
	{
		auto x = BigInt1( 7) % BigInt2( 3);
		VERIFY(x == 1);
	}
	{
		auto x = BigInt1(-7) % BigInt2( 3);
		VERIFY(x == -1);
	}
	{
		auto x = BigInt1( 7) % BigInt2(-3);
		VERIFY(x == 1);
	}
	{
		auto x = BigInt1(-7) % BigInt2(-3);
		VERIFY(x == -1);
	}
	{
		auto x = BigInt1{123} % BigInt2{4};
		VERIFY(x == 3);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool Mod2UnsignedTest()
{
	{
		auto x = BigInt1( 7) % BigInt2( 2);
		VERIFY(x == 1);
	}
	{
		auto x = BigInt1( 7) % BigInt2( 3);
		VERIFY(x == 1);
	}
	{
		auto x = BigInt1( 7) % BigInt2( 4);
		VERIFY(x == 3);
	}
	{
		auto x = BigInt1( 7) % BigInt2( 5);
		VERIFY(x == 2);
	}
	{
		auto x = BigInt1( 8) % BigInt2( 2);
		VERIFY(x == 0);
	}
	{
		auto x = BigInt1( 8) % BigInt2( 3);
		VERIFY(x == 2);
	}
	{
		auto x = BigInt1( 8) % BigInt2( 4);
		VERIFY(x == 0);
	}
	{
		auto x = BigInt1( 8) % BigInt2( 5);
		VERIFY(x == 3);
	}
	{
		auto x = BigInt1(0xfffffff) % BigInt2(2);
		VERIFY(x == 1);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool Mod2LargeTest()
{
	{
		auto x = BigInt1{"517232794887556900325139264240"} %
			     BigInt2{"97854840192602714242"};
		VERIFY(x == BigInt1{"20300968082335090596"});
	}
	{
		auto x = BigInt1{"8480533256755492072837759593696251541964"} %
			     BigInt2{"80317560221046790777589885826979837"};
		VERIFY(x == BigInt1{"43025695824575004376318882931492645"});
	}
	return true;
}

GTEST_TEST(BigIntTest, ModTest)
{
	EXPECT_TRUE((ModTest<bksge::bigint,     bksge::bigint>()));
	EXPECT_TRUE((ModTest<bksge::bigint,     bksge::int32_t>()));
	EXPECT_TRUE((ModTest<bksge::bigint,     bksge::int64_t>()));
	EXPECT_TRUE((ModTest<bksge::bigint,     bksge::int128_t>()));
	EXPECT_TRUE((ModTest<bksge::bigint,     bksge::int256_t>()));
	EXPECT_TRUE((ModTest<bksge::bigint,     bksge::int512_t>()));
	EXPECT_TRUE((ModTest<bksge::bigint,     bksge::int1024_t>()));
	EXPECT_TRUE((ModTest<bksge::bigint,     bksge::uint32_t>()));
	EXPECT_TRUE((ModTest<bksge::bigint,     bksge::uint64_t>()));
	EXPECT_TRUE((ModTest<bksge::bigint,     bksge::uint128_t>()));
	EXPECT_TRUE((ModTest<bksge::bigint,     bksge::uint256_t>()));
	EXPECT_TRUE((ModTest<bksge::bigint,     bksge::uint512_t>()));
	EXPECT_TRUE((ModTest<bksge::bigint,     bksge::uint1024_t>()));
//	EXPECT_TRUE((ModTest<bksge::int32_t,    bksge::bigint>()));
//	EXPECT_TRUE((ModTest<bksge::int64_t,    bksge::bigint>()));
	EXPECT_TRUE((ModTest<bksge::int128_t,   bksge::bigint>()));
	EXPECT_TRUE((ModTest<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((ModTest<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((ModTest<bksge::int1024_t,  bksge::bigint>()));
//	EXPECT_TRUE((ModTest<bksge::uint32_t,   bksge::bigint>()));
//	EXPECT_TRUE((ModTest<bksge::uint64_t,   bksge::bigint>()));
	EXPECT_TRUE((ModTest<bksge::uint128_t,  bksge::bigint>()));
	EXPECT_TRUE((ModTest<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((ModTest<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((ModTest<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int32_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int32_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int32_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int32_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int32_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int32_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int32_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int32_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int64_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int64_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int64_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int64_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int64_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int64_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int64_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int64_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int256_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ModTest<bksge::int1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((Mod2Test<bksge::bigint, bksge::bigint>()));
	EXPECT_TRUE((Mod2Test<bksge::bigint, bksge::int32_t>()));
	EXPECT_TRUE((Mod2Test<bksge::bigint, bksge::int64_t>()));
	EXPECT_TRUE((Mod2Test<bksge::bigint, bksge::int128_t>()));
	EXPECT_TRUE((Mod2Test<bksge::bigint, bksge::int256_t>()));
	EXPECT_TRUE((Mod2Test<bksge::bigint, bksge::int512_t>()));
	EXPECT_TRUE((Mod2Test<bksge::bigint, bksge::int1024_t>()));
	EXPECT_TRUE((Mod2UnsignedTest<bksge::bigint, bksge::uint32_t>()));
	EXPECT_TRUE((Mod2UnsignedTest<bksge::bigint, bksge::uint64_t>()));
	EXPECT_TRUE((Mod2UnsignedTest<bksge::bigint, bksge::uint128_t>()));
	EXPECT_TRUE((Mod2UnsignedTest<bksge::bigint, bksge::uint256_t>()));
	EXPECT_TRUE((Mod2UnsignedTest<bksge::bigint, bksge::uint512_t>()));
	EXPECT_TRUE((Mod2UnsignedTest<bksge::bigint, bksge::uint1024_t>()));
	EXPECT_TRUE((Mod2Test<bksge::int32_t, bksge::bigint>()));
	EXPECT_TRUE((Mod2Test<bksge::int64_t, bksge::bigint>()));
	EXPECT_TRUE((Mod2Test<bksge::int128_t, bksge::bigint>()));
	EXPECT_TRUE((Mod2Test<bksge::int256_t, bksge::bigint>()));
	EXPECT_TRUE((Mod2Test<bksge::int512_t, bksge::bigint>()));
	EXPECT_TRUE((Mod2Test<bksge::int1024_t, bksge::bigint>()));
	EXPECT_TRUE((Mod2UnsignedTest<bksge::uint32_t, bksge::bigint>()));
	EXPECT_TRUE((Mod2UnsignedTest<bksge::uint64_t, bksge::bigint>()));
	EXPECT_TRUE((Mod2UnsignedTest<bksge::uint128_t, bksge::bigint>()));
	EXPECT_TRUE((Mod2UnsignedTest<bksge::uint256_t, bksge::bigint>()));
	EXPECT_TRUE((Mod2UnsignedTest<bksge::uint512_t, bksge::bigint>()));
	EXPECT_TRUE((Mod2UnsignedTest<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int32_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int32_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int32_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int32_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int32_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int32_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int32_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int32_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int64_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int64_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int256_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2Test<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint32_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint32_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint32_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint32_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint32_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint32_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint32_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint32_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint64_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint64_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint256_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mod2UnsignedTest<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((Mod2LargeTest<bksge::bigint, bksge::bigint>()));
	EXPECT_TRUE((Mod2LargeTest<bksge::bigint, bksge::int256_t>()));
	EXPECT_TRUE((Mod2LargeTest<bksge::bigint, bksge::int512_t>()));
	EXPECT_TRUE((Mod2LargeTest<bksge::bigint, bksge::int1024_t>()));
	EXPECT_TRUE((Mod2LargeTest<bksge::bigint, bksge::uint256_t>()));
	EXPECT_TRUE((Mod2LargeTest<bksge::bigint, bksge::uint512_t>()));
	EXPECT_TRUE((Mod2LargeTest<bksge::bigint, bksge::uint1024_t>()));
	EXPECT_TRUE((Mod2LargeTest<bksge::int256_t, bksge::bigint>()));
	EXPECT_TRUE((Mod2LargeTest<bksge::int512_t, bksge::bigint>()));
	EXPECT_TRUE((Mod2LargeTest<bksge::int1024_t, bksge::bigint>()));
	EXPECT_TRUE((Mod2LargeTest<bksge::uint256_t, bksge::bigint>()));
	EXPECT_TRUE((Mod2LargeTest<bksge::uint512_t, bksge::bigint>()));
	EXPECT_TRUE((Mod2LargeTest<bksge::uint1024_t, bksge::bigint>()));

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::int256_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::int256_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::int256_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::int256_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::int256_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::int256_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::int512_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::int512_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::int512_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::int512_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::int512_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::int512_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::int1024_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::int1024_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::int1024_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::int1024_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::int1024_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::int1024_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::uint256_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::uint256_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::uint256_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::uint256_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::uint256_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::uint256_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::uint512_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::uint512_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::uint512_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::uint512_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::uint512_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::uint512_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::uint1024_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::uint1024_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::uint1024_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::uint1024_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::uint1024_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mod2LargeTest<bksge::uint1024_t, bksge::uint1024_t>()));
}

GTEST_TEST(BigIntTest, ModByZeroTest)
{
	{
		bksge::bigint x{0xFFFFFFFF};
		EXPECT_THROW(x %= 0, bksge::overflow_error);
		EXPECT_THROW(x %= bksge::bigint(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int128_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int256_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int512_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int1024_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint128_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint256_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint512_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint1024_t(0), bksge::overflow_error);
		EXPECT_EQ(x, 0xFFFFFFFF);
	}
	{
		bksge::int128_t x{1};
		EXPECT_THROW(x %= 0, bksge::overflow_error);
		EXPECT_THROW(x %= bksge::bigint(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int128_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int256_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int512_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int1024_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint128_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint256_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint512_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint1024_t(0), bksge::overflow_error);
		EXPECT_EQ(x, 1);
	}
	{
		bksge::int256_t x{2};
		EXPECT_THROW(x %= 0, bksge::overflow_error);
		EXPECT_THROW(x %= bksge::bigint(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int128_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int256_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int512_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int1024_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint128_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint256_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint512_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint1024_t(0), bksge::overflow_error);
		EXPECT_EQ(x, 2);
	}
	{
		bksge::int512_t x{3};
		EXPECT_THROW(x %= 0, bksge::overflow_error);
		EXPECT_THROW(x %= bksge::bigint(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int128_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int256_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int512_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int1024_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint128_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint256_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint512_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint1024_t(0), bksge::overflow_error);
		EXPECT_EQ(x, 3);
	}
	{
		bksge::int1024_t x{4};
		EXPECT_THROW(x %= 0, bksge::overflow_error);
		EXPECT_THROW(x %= bksge::bigint(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int128_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int256_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int512_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int1024_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint128_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint256_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint512_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint1024_t(0), bksge::overflow_error);
		EXPECT_EQ(x, 4);
	}
	{
		bksge::uint128_t x{1};
		EXPECT_THROW(x %= 0, bksge::overflow_error);
		EXPECT_THROW(x %= bksge::bigint(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int128_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int256_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int512_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int1024_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint128_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint256_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint512_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint1024_t(0), bksge::overflow_error);
		EXPECT_EQ(x, 1);
	}
	{
		bksge::uint256_t x{2};
		EXPECT_THROW(x %= 0, bksge::overflow_error);
		EXPECT_THROW(x %= bksge::bigint(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int128_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int256_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int512_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int1024_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint128_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint256_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint512_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint1024_t(0), bksge::overflow_error);
		EXPECT_EQ(x, 2);
	}
	{
		bksge::uint512_t x{3};
		EXPECT_THROW(x %= 0, bksge::overflow_error);
		EXPECT_THROW(x %= bksge::bigint(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int128_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int256_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int512_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int1024_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint128_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint256_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint512_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint1024_t(0), bksge::overflow_error);
		EXPECT_EQ(x, 3);
	}
	{
		bksge::uint1024_t x{4};
		EXPECT_THROW(x %= 0, bksge::overflow_error);
		EXPECT_THROW(x %= bksge::bigint(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int128_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int256_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int512_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::int1024_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint128_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint256_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint512_t(0), bksge::overflow_error);
		EXPECT_THROW(x %= bksge::uint1024_t(0), bksge::overflow_error);
		EXPECT_EQ(x, 4);
	}

	EXPECT_THROW(bksge::bigint(0) % 0, bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(0) % bksge::bigint(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(0) % bksge::int128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(0) % bksge::int256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(0) % bksge::int512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(0) % bksge::int1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(0) % bksge::uint128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(0) % bksge::uint256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(0) % bksge::uint512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(0) % bksge::uint1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(-1) % 0, bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(-1) % bksge::bigint(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(-1) % bksge::int128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(-1) % bksge::int256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(-1) % bksge::int512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(-1) % bksge::int1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(-1) % bksge::uint128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(-1) % bksge::uint256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(-1) % bksge::uint512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(-1) % bksge::uint1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int128_t(-2) % 0, bksge::overflow_error);
	EXPECT_THROW(bksge::int128_t(-2) % bksge::bigint(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int128_t(-2) % bksge::int128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int128_t(-2) % bksge::int256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int128_t(-2) % bksge::int512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int128_t(-2) % bksge::int1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int128_t(-2) % bksge::uint128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int128_t(-2) % bksge::uint256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int128_t(-2) % bksge::uint512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int128_t(-2) % bksge::uint1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int256_t(3) % 0, bksge::overflow_error);
	EXPECT_THROW(bksge::int256_t(3) % bksge::bigint(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int256_t(3) % bksge::int128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int256_t(3) % bksge::int256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int256_t(3) % bksge::int512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int256_t(3) % bksge::int1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int256_t(3) % bksge::uint128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int256_t(3) % bksge::uint256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int256_t(3) % bksge::uint512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int256_t(3) % bksge::uint1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int512_t(-4) % 0, bksge::overflow_error);
	EXPECT_THROW(bksge::int512_t(-4) % bksge::bigint(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int512_t(-4) % bksge::int128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int512_t(-4) % bksge::int256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int512_t(-4) % bksge::int512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int512_t(-4) % bksge::int1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int512_t(-4) % bksge::uint128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int512_t(-4) % bksge::uint256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int512_t(-4) % bksge::uint512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int512_t(-4) % bksge::uint1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int1024_t(5) % 0, bksge::overflow_error);
	EXPECT_THROW(bksge::int1024_t(5) % bksge::bigint(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int1024_t(5) % bksge::int128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int1024_t(5) % bksge::int256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int1024_t(5) % bksge::int512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int1024_t(5) % bksge::int1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int1024_t(5) % bksge::uint128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int1024_t(5) % bksge::uint256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int1024_t(5) % bksge::uint512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int1024_t(5) % bksge::uint1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint128_t(2) % 0, bksge::overflow_error);
	EXPECT_THROW(bksge::uint128_t(2) % bksge::bigint(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint128_t(2) % bksge::int128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint128_t(2) % bksge::int256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint128_t(2) % bksge::int512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint128_t(2) % bksge::int1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint128_t(2) % bksge::uint128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint128_t(2) % bksge::uint256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint128_t(2) % bksge::uint512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint128_t(2) % bksge::uint1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint256_t(3) % 0, bksge::overflow_error);
	EXPECT_THROW(bksge::uint256_t(3) % bksge::bigint(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint256_t(3) % bksge::int128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint256_t(3) % bksge::int256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint256_t(3) % bksge::int512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint256_t(3) % bksge::int1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint256_t(3) % bksge::uint128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint256_t(3) % bksge::uint256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint256_t(3) % bksge::uint512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint256_t(3) % bksge::uint1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint512_t(4) % 0, bksge::overflow_error);
	EXPECT_THROW(bksge::uint512_t(4) % bksge::bigint(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint512_t(4) % bksge::int128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint512_t(4) % bksge::int256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint512_t(4) % bksge::int512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint512_t(4) % bksge::int1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint512_t(4) % bksge::uint128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint512_t(4) % bksge::uint256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint512_t(4) % bksge::uint512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint512_t(4) % bksge::uint1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint1024_t(5) % 0, bksge::overflow_error);
	EXPECT_THROW(bksge::uint1024_t(5) % bksge::bigint(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint1024_t(5) % bksge::int128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint1024_t(5) % bksge::int256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint1024_t(5) % bksge::int512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint1024_t(5) % bksge::int1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint1024_t(5) % bksge::uint128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint1024_t(5) % bksge::uint256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint1024_t(5) % bksge::uint512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint1024_t(5) % bksge::uint1024_t(0), bksge::overflow_error);
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
