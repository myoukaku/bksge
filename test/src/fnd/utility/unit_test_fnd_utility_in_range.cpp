/**
 *	@file	unit_test_fnd_utility_in_range.cpp
 *
 *	@brief	in_range のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/in_range.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(UtilityTest, InRangeTest)
{
	{
		BKSGE_CONSTEXPR bksge::int8_t i = 0;
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::int8_t i = -1;
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::int8_t i = bksge::numeric_limits<bksge::int8_t>::min();
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::int8_t i = bksge::numeric_limits<bksge::int8_t>::max();
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::int16_t i = 0;
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::int16_t i = -1;
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::int16_t i = bksge::numeric_limits<bksge::int16_t>::min();
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::int16_t i = bksge::numeric_limits<bksge::int16_t>::max();
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::int32_t i = 0;
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::int32_t i = -1;
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::int32_t i = bksge::numeric_limits<bksge::int32_t>::min();
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::int32_t i = bksge::numeric_limits<bksge::int32_t>::max();
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::int64_t i = 0;
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::int64_t i = -1;
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::int64_t i = bksge::numeric_limits<bksge::int64_t>::min();
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::int64_t i = bksge::numeric_limits<bksge::int64_t>::max();
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::uint8_t i = bksge::numeric_limits<bksge::uint8_t>::min();
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::uint8_t i = bksge::numeric_limits<bksge::uint8_t>::max();
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::uint16_t i = bksge::numeric_limits<bksge::uint16_t>::min();
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::uint16_t i = bksge::numeric_limits<bksge::uint16_t>::max();
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::uint32_t i = bksge::numeric_limits<bksge::uint32_t>::min();
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::uint32_t i = bksge::numeric_limits<bksge::uint32_t>::max();
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::uint64_t i = bksge::numeric_limits<bksge::uint64_t>::min();
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR bksge::uint64_t i = bksge::numeric_limits<bksge::uint64_t>::max();
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<bksge::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<bksge::uint64_t>(i));
	}
}
