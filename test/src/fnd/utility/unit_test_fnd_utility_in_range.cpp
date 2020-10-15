/**
 *	@file	unit_test_fnd_utility_in_range.cpp
 *
 *	@brief	in_range のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/in_range.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include "constexpr_test.hpp"

GTEST_TEST(UtilityTest, InRangeTest)
{
	{
		BKSGE_CONSTEXPR std::int8_t i = 0;
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::int8_t i = -1;
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::int8_t i = std::numeric_limits<std::int8_t>::min();
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::int8_t i = std::numeric_limits<std::int8_t>::max();
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::int16_t i = 0;
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::int16_t i = -1;
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::int16_t i = std::numeric_limits<std::int16_t>::min();
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::int16_t i = std::numeric_limits<std::int16_t>::max();
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::int32_t i = 0;
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::int32_t i = -1;
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::int32_t i = std::numeric_limits<std::int32_t>::min();
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::int32_t i = std::numeric_limits<std::int32_t>::max();
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::int64_t i = 0;
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::int64_t i = -1;
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::int64_t i = std::numeric_limits<std::int64_t>::min();
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::int64_t i = std::numeric_limits<std::int64_t>::max();
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::uint8_t i = std::numeric_limits<std::uint8_t>::min();
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::uint8_t i = std::numeric_limits<std::uint8_t>::max();
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::uint16_t i = std::numeric_limits<std::uint16_t>::min();
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::uint16_t i = std::numeric_limits<std::uint16_t>::max();
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::uint32_t i = std::numeric_limits<std::uint32_t>::min();
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::uint32_t i = std::numeric_limits<std::uint32_t>::max();
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::uint64_t i = std::numeric_limits<std::uint64_t>::min();
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint64_t>(i));
	}
	{
		BKSGE_CONSTEXPR std::uint64_t i = std::numeric_limits<std::uint64_t>::max();
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::int64_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint8_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint16_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::in_range<std::uint32_t>(i));
		BKSGE_CONSTEXPR_EXPECT_TRUE( bksge::in_range<std::uint64_t>(i));
	}
}
