/**
 *	@file	unit_test_fnd_bigint_decrement.cpp
 *
 *	@brief	bigint::operator--() のテスト
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
inline BKSGE_CXX14_CONSTEXPR bool PreDecrementTest()
{
	{
		BigInt x1 = 2;
		VERIFY(x1 == 2);

		auto x2 = --x1;
		VERIFY(x1 == 1);
		VERIFY(x2 == 1);

		auto x3 = --x1;
		VERIFY(x1 == 0);
		VERIFY(x3 == 0);

		auto x4 = --x1;
		VERIFY(x1 == -1);
		VERIFY(x4 == -1);

		auto x5 = --x1;
		VERIFY(x1 == -2);
		VERIFY(x5 == -2);
	}
	{
		BigInt x = 100;
		VERIFY(x == 100);

		auto y = --x;
		VERIFY(x == 99);
		VERIFY(y == 99);

		auto z = --x;
		VERIFY(x == 98);
		VERIFY(z == 98);
	}
	{
		BigInt x = 0x100;
		VERIFY(x == 0x100);

		auto y = --x;
		VERIFY(x == 0xff);
		VERIFY(y == 0xff);

		auto z = --x;
		VERIFY(x == 0xfe);
		VERIFY(z == 0xfe);
	}
	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool PostDecrementTest()
{
	{
		BigInt x1 = 2;
		VERIFY(x1 == 2);

		auto x2 = x1--;
		VERIFY(x1 == 1);
		VERIFY(x2 == 2);

		auto x3 = x1--;
		VERIFY(x1 == 0);
		VERIFY(x3 == 1);

		auto x4 = x1--;
		VERIFY(x1 == -1);
		VERIFY(x4 == 0);

		auto x5 = x1--;
		VERIFY(x1 == -2);
		VERIFY(x5 == -1);
	}
	{
		BigInt x = 1000;
		VERIFY(x == 1000);

		auto y = x--;
		VERIFY(x ==  999);
		VERIFY(y == 1000);

		auto z = x--;
		VERIFY(x ==  998);
		VERIFY(z ==  999);
	}
	{
		BigInt x = 0x10000;
		VERIFY(x == 0x10000);

		auto y = x--;
		VERIFY(x == 0x0ffff);
		VERIFY(y == 0x10000);

		auto z = x--;
		VERIFY(x == 0x0fffe);
		VERIFY(z == 0x0ffff);
	}
	return true;
}

GTEST_TEST(BigIntTest, DecrementTest)
{
	EXPECT_TRUE(PreDecrementTest<bksge::bigint>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PreDecrementTest<bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PreDecrementTest<bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PreDecrementTest<bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PreDecrementTest<bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PreDecrementTest<bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PreDecrementTest<bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PreDecrementTest<bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PreDecrementTest<bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PreDecrementTest<bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PreDecrementTest<bksge::uint1024_t>()));

	EXPECT_TRUE(PostDecrementTest<bksge::bigint>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PostDecrementTest<bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PostDecrementTest<bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PostDecrementTest<bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PostDecrementTest<bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PostDecrementTest<bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PostDecrementTest<bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PostDecrementTest<bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PostDecrementTest<bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PostDecrementTest<bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PostDecrementTest<bksge::uint1024_t>()));
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
