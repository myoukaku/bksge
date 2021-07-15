/**
 *	@file	unit_test_fnd_bigint_increment.cpp
 *
 *	@brief	bigint::operator++() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bigint.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_CLANG("-Wsign-compare");
BKSGE_WARNING_DISABLE_MSVC(4245);	// conversion from '...' to '...', signed/unsigned mismatch
BKSGE_WARNING_DISABLE_MSVC(4307);	// integral constant overflow

namespace bksge_bigint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool PreIncrementTest()
{
	{
		BigInt x1 = -2;
		VERIFY(x1 == -2);

		auto x2 = ++x1;
		VERIFY(x1 == -1);
		VERIFY(x2 == -1);

		auto x3 = ++x1;
		VERIFY(x1 == 0);
		VERIFY(x3 == 0);

		auto x4 = ++x1;
		VERIFY(x1 == 1);
		VERIFY(x4 == 1);

		auto x5 = ++x1;
		VERIFY(x1 == 2);
		VERIFY(x5 == 2);
	}
	{
		BigInt x = 0xff;
		VERIFY(x == 0xff);

		auto y = ++x;
		VERIFY(x == 0x100);
		VERIFY(y == 0x100);

		auto z = ++x;
		VERIFY(x == 0x101);
		VERIFY(z == 0x101);
	}
	{
		BigInt x = 0xffff;
		VERIFY(x == 0xffff);

		auto y = ++x;
		VERIFY(x == 0x10000);
		VERIFY(y == 0x10000);

		auto z = ++x;
		VERIFY(x == 0x10001);
		VERIFY(z == 0x10001);
	}
	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool PostIncrementTest()
{
	{
		BigInt x1 = -2;
		VERIFY(x1 == -2);

		auto x2 = x1++;
		VERIFY(x1 == -1);
		VERIFY(x2 == -2);

		auto x3 = x1++;
		VERIFY(x1 == 0);
		VERIFY(x3 == -1);

		auto x4 = x1++;
		VERIFY(x1 == 1);
		VERIFY(x4 == 0);

		auto x5 = x1++;
		VERIFY(x1 == 2);
		VERIFY(x5 == 1);
	}
	{
		BigInt x = 99;
		VERIFY(x == 99);

		auto y = x++;
		VERIFY(x == 100);
		VERIFY(y == 99);

		auto z = x++;
		VERIFY(x == 101);
		VERIFY(z == 100);
	}
	{
		BigInt x = 0xff;
		VERIFY(x == 0xff);

		auto y = x++;
		VERIFY(x == 0x100);
		VERIFY(y == 0xff);

		auto z = x++;
		VERIFY(x == 0x101);
		VERIFY(z == 0x100);
	}
	{
		BigInt x = 0xffff;
		VERIFY(x == 0xffff);

		auto y = x++;
		VERIFY(x == 0x10000);
		VERIFY(y == 0xffff);

		auto z = x++;
		VERIFY(x == 0x10001);
		VERIFY(z == 0x10000);
	}
	return true;
}

GTEST_TEST(BigIntTest, IncrementTest)
{
	EXPECT_TRUE(PreIncrementTest<bksge::bigint>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PreIncrementTest<std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PreIncrementTest<bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PreIncrementTest<bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PreIncrementTest<bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PreIncrementTest<bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PreIncrementTest<std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PreIncrementTest<bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PreIncrementTest<bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PreIncrementTest<bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PreIncrementTest<bksge::uint1024_t>()));

	EXPECT_TRUE(PostIncrementTest<bksge::bigint>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PostIncrementTest<std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PostIncrementTest<bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PostIncrementTest<bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PostIncrementTest<bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PostIncrementTest<bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PostIncrementTest<std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PostIncrementTest<bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PostIncrementTest<bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PostIncrementTest<bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((PostIncrementTest<bksge::uint1024_t>()));
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
