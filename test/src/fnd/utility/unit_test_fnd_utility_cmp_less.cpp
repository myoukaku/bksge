﻿/**
 *	@file	unit_test_fnd_utility_cmp_less.cpp
 *
 *	@brief	cmp_less のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/cmp_less.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include "constexpr_test.hpp"

GTEST_TEST(UtilityTest, CmpLessTest)
{
	BKSGE_CONSTEXPR std::int8_t   s08  = -1;
	BKSGE_CONSTEXPR std::int16_t  s16  = -1;
	BKSGE_CONSTEXPR std::int32_t  s32  = -1;
	BKSGE_CONSTEXPR std::int64_t  s64  = -1;
	BKSGE_CONSTEXPR std::uint8_t  u08  = (std::uint8_t )-1;
	BKSGE_CONSTEXPR std::uint16_t u16  = (std::uint16_t)-1;
	BKSGE_CONSTEXPR std::uint32_t u32  = (std::uint32_t)-1;
	BKSGE_CONSTEXPR std::uint64_t u64  = (std::uint64_t)-1;

	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(s08, s08));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(s08, s16));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(s08, s32));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(s08, s64));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(s08, u08));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(s08, u16));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(s08, u32));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(s08, u64));

	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(s16, s08));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(s16, s16));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(s16, s32));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(s16, s64));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(s16, u08));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(s16, u16));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(s16, u32));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(s16, u64));

	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(s32, s08));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(s32, s16));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(s32, s32));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(s32, s64));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(s32, u08));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(s32, u16));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(s32, u32));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(s32, u64));

	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(s64, s08));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(s64, s16));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(s64, s32));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(s64, s64));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(s64, u08));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(s64, u16));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(s64, u32));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(s64, u64));

	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u08, s08));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u08, s16));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u08, s32));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u08, s64));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u08, u08));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(u08, u16));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(u08, u32));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(u08, u64));

	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u16, s08));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u16, s16));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u16, s32));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u16, s64));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u16, u08));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u16, u16));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(u16, u32));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(u16, u64));

	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u32, s08));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u32, s16));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u32, s32));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u32, s64));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u32, u08));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u32, u16));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u32, u32));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(u32, u64));

	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u64, s08));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u64, s16));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u64, s32));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u64, s64));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u64, u08));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u64, u16));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u64, u32));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(u64, u64));

	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(0, 0));
	BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::cmp_less(0, 1));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(1, 0));
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::cmp_less(1, 1));
}