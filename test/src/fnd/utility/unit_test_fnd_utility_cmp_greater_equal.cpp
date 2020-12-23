/**
 *	@file	unit_test_fnd_utility_cmp_greater_equal.cpp
 *
 *	@brief	cmp_greater_equal のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/cmp_greater_equal.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(UtilityTest, CmpGreaterEqualTest)
{
	BKSGE_CONSTEXPR bksge::int8_t   s08  = -1;
	BKSGE_CONSTEXPR bksge::int16_t  s16  = -1;
	BKSGE_CONSTEXPR bksge::int32_t  s32  = -1;
	BKSGE_CONSTEXPR bksge::int64_t  s64  = -1;
	BKSGE_CONSTEXPR bksge::uint8_t  u08  = (bksge::uint8_t )-1;
	BKSGE_CONSTEXPR bksge::uint16_t u16  = (bksge::uint16_t)-1;
	BKSGE_CONSTEXPR bksge::uint32_t u32  = (bksge::uint32_t)-1;
	BKSGE_CONSTEXPR bksge::uint64_t u64  = (bksge::uint64_t)-1;

	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(s08, s08));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(s08, s16));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(s08, s32));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(s08, s64));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(s08, u08));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(s08, u16));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(s08, u32));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(s08, u64));

	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(s16, s08));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(s16, s16));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(s16, s32));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(s16, s64));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(s16, u08));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(s16, u16));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(s16, u32));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(s16, u64));

	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(s32, s08));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(s32, s16));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(s32, s32));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(s32, s64));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(s32, u08));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(s32, u16));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(s32, u32));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(s32, u64));

	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(s64, s08));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(s64, s16));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(s64, s32));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(s64, s64));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(s64, u08));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(s64, u16));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(s64, u32));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(s64, u64));

	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u08, s08));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u08, s16));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u08, s32));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u08, s64));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u08, u08));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(u08, u16));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(u08, u32));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(u08, u64));

	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u16, s08));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u16, s16));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u16, s32));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u16, s64));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u16, u08));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u16, u16));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(u16, u32));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(u16, u64));

	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u32, s08));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u32, s16));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u32, s32));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u32, s64));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u32, u08));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u32, u16));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u32, u32));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(u32, u64));

	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u64, s08));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u64, s16));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u64, s32));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u64, s64));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u64, u08));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u64, u16));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u64, u32));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(u64, u64));

	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(0, 0));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_greater_equal(0, 1));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(1, 0));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_greater_equal(1, 1));
}
