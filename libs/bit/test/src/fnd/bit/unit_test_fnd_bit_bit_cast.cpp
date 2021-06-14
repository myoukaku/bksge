/**
 *	@file	unit_test_fnd_bit_bit_cast.cpp
 *
 *	@brief	bit_cast のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bit/bit_cast.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BitTest, BitCastTest)
{
	{
		const float	x = 1.0f;
		const auto  y = bksge::bit_cast<bksge::uint32_t>(x);
		EXPECT_EQ(bksge::uint32_t(0x3f800000), y);
	}
	{
		const float	x = 3.14159265358979f;
		const auto  y = bksge::bit_cast<bksge::int32_t>(x);
		EXPECT_EQ(bksge::int32_t(0x40490fdb), y);
	}
	{
		const double x = 1.0;
		const auto	 y = bksge::bit_cast<bksge::uint64_t>(x);
		EXPECT_EQ(bksge::uint64_t(0x3FF0000000000000), y);
	}
}
