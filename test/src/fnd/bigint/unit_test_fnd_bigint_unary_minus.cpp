/**
 *	@file	unit_test_fnd_bigint_unary_minus.cpp
 *
 *	@brief	bigint::operator-() のテスト
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
BKSGE_WARNING_DISABLE_MSVC(4146);	// unary minus operator applied to unsigned type, result still unsigned

namespace bksge_bigint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool UnaryMinusTest()
{
	VERIFY(-BigInt{0} == 0);
	VERIFY(-BigInt{1} == -1);
	VERIFY(-BigInt{2} == -2);
	VERIFY(-BigInt(-1) == 1);
	VERIFY(-BigInt(-2) == 2);
	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool UnaryMinusLargeTest()
{
	VERIFY(-BigInt{"12345678901234567890"} == BigInt{"-12345678901234567890"});
	VERIFY(-BigInt{"-12345678901234567890"} == BigInt{"12345678901234567890"});
	return true;
}

GTEST_TEST(BigIntTest, UnaryMinusTest)
{
	EXPECT_TRUE(UnaryMinusTest<bksge::bigint>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest<bksge::int64_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest<bksge::int128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest<bksge::int256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest<bksge::int512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest<bksge::int1024_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest<bksge::uint64_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest<bksge::uint128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest<bksge::uint256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest<bksge::uint512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest<bksge::uint1024_t>());

	EXPECT_TRUE(UnaryMinusLargeTest<bksge::bigint>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusLargeTest<bksge::int128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusLargeTest<bksge::int256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusLargeTest<bksge::int512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusLargeTest<bksge::int1024_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusLargeTest<bksge::uint128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusLargeTest<bksge::uint256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusLargeTest<bksge::uint512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusLargeTest<bksge::uint1024_t>());
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
