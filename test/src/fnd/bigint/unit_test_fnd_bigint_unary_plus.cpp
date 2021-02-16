/**
 *	@file	unit_test_fnd_bigint_unary_plus.cpp
 *
 *	@brief	bigint::operator+() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bigint.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4127);	// conditional expression is constant

namespace bksge_bigint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool UnaryPlusTest()
{
	VERIFY(+BigInt{0} == 0);
	VERIFY(+BigInt{1} == 1);
	VERIFY(+BigInt{2} == 2);
	VERIFY(+BigInt(-1) == -1);
	VERIFY(+BigInt(-2) == -2);
	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool UnaryPlusLargeTest()
{
	VERIFY(+BigInt{"12345678901234567890"} == BigInt{"12345678901234567890"});
	VERIFY(+BigInt{"-12345678901234567890"} == BigInt{"-12345678901234567890"});
	return true;
}

GTEST_TEST(BigIntTest, UnaryPlusTest)
{
	EXPECT_TRUE(UnaryPlusTest<bksge::bigint>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<bksge::int64_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<bksge::int128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<bksge::int256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<bksge::int512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<bksge::int1024_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<bksge::uint64_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<bksge::uint128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<bksge::uint256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<bksge::uint512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<bksge::uint1024_t>());

	EXPECT_TRUE(UnaryPlusLargeTest<bksge::bigint>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusLargeTest<bksge::int128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusLargeTest<bksge::int256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusLargeTest<bksge::int512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusLargeTest<bksge::int1024_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusLargeTest<bksge::uint128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusLargeTest<bksge::uint256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusLargeTest<bksge::uint512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusLargeTest<bksge::uint1024_t>());
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
