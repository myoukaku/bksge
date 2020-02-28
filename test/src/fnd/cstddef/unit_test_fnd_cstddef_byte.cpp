/**
 *	@file	unit_test_fnd_cstddef_byte.cpp
 *
 *	@brief	byte のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cstddef/byte.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(CStddefTest, ByteTest)
{
	bksge::byte b = static_cast<bksge::byte>(42);
	EXPECT_EQ(42, bksge::to_integer<int>(b));

	b <<= 1;
	EXPECT_EQ(84, bksge::to_integer<int>(b));

	b >>= 2;
	EXPECT_EQ(21, bksge::to_integer<int>(b));

	EXPECT_EQ(42, bksge::to_integer<int>(b << 1));
	EXPECT_EQ(10, bksge::to_integer<int>(b >> 1));

	b |= static_cast<bksge::byte>(15);
	EXPECT_EQ(31, bksge::to_integer<int>(b));

	b &= static_cast<bksge::byte>(7);
	EXPECT_EQ(7, bksge::to_integer<int>(b));

	b ^= static_cast<bksge::byte>(31);
	EXPECT_EQ(24, bksge::to_integer<int>(b));

	EXPECT_EQ(127, bksge::to_integer<int>(b | static_cast<bksge::byte>(127)));
	EXPECT_EQ( 24, bksge::to_integer<int>(b & static_cast<bksge::byte>(127)));
	EXPECT_EQ(103, bksge::to_integer<int>(b ^ static_cast<bksge::byte>(127)));
	EXPECT_EQ(231, bksge::to_integer<int>(~b));

	BKSGE_CONSTEXPR_EXPECT_EQ( 64, bksge::to_integer<int>(static_cast<bksge::byte>(64)));
	BKSGE_CONSTEXPR_EXPECT_EQ(128, bksge::to_integer<int>(static_cast<bksge::byte>(64) << 1));
	BKSGE_CONSTEXPR_EXPECT_EQ( 32, bksge::to_integer<int>(static_cast<bksge::byte>(64) >> 1));
	BKSGE_CONSTEXPR_EXPECT_EQ(240, bksge::to_integer<int>(static_cast<bksge::byte>(64) | static_cast<bksge::byte>(240)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 64, bksge::to_integer<int>(static_cast<bksge::byte>(64) & static_cast<bksge::byte>(240)));
	BKSGE_CONSTEXPR_EXPECT_EQ(176, bksge::to_integer<int>(static_cast<bksge::byte>(64) ^ static_cast<bksge::byte>(240)));
	BKSGE_CONSTEXPR_EXPECT_EQ(191, bksge::to_integer<int>(~static_cast<bksge::byte>(64)));
}
