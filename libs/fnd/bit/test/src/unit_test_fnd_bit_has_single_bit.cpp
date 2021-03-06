﻿/**
 *	@file	unit_test_fnd_bit_has_single_bit.cpp
 *
 *	@brief	has_single_bit のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bit/has_single_bit.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_bit_test
{

namespace has_single_bit_test
{

template <typename T>
void HasSingleBitTestU8(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T) 0));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T) 1));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T) 2));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T) 3));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T) 4));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T) 5));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T) 6));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T) 7));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T) 8));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T) 9));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x0f));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x10));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x11));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x1f));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x20));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x21));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x3f));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x40));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x41));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x7f));
	BKSGE_CONSTEXPR_EXPECT_EQ(true,  bksge::has_single_bit((T)0x80));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x81));
}

template <typename T>
void HasSingleBitTestU16(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x00ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x0100));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x0101));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x01ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x0200));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x0201));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x03ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x0400));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x0401));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x07ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x0800));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x0801));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x0fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x1000));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x1001));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x1fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x2000));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x2001));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x3fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x4000));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x4001));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x7fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x8000));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x8001));
}

template <typename T>
void HasSingleBitTestU32(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x00ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x01000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x01000001));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x01ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x02000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x02000001));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x03ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x04000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x04000001));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x07ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x08000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x08000001));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x0fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x10000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x10000001));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x1fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x20000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x20000001));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x3fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x40000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x40000001));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x7fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x80000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x80000001));
}

template <typename T>
void HasSingleBitTestU64(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x00ffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x0100000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x0100000000000001));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x01ffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x0200000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x0200000000000001));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x03ffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x0400000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x0400000000000001));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x07ffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x0800000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x0800000000000001));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x0fffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x1000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x1000000000000001));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x1fffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x2000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x2000000000000001));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x3fffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x4000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x4000000000000001));

	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x7fffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(true , bksge::has_single_bit((T)0x8000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::has_single_bit((T)0x8000000000000001));
}

GTEST_TEST(BitTest, HasSingleBitTest)
{
	HasSingleBitTestU8<bksge::uint8_t>();
	HasSingleBitTestU8<bksge::uint16_t>();
	HasSingleBitTestU8<bksge::uint32_t>();
	HasSingleBitTestU8<bksge::uint64_t>();

	HasSingleBitTestU16<bksge::uint16_t>();
	HasSingleBitTestU16<bksge::uint32_t>();
	HasSingleBitTestU16<bksge::uint64_t>();

	HasSingleBitTestU32<bksge::uint32_t>();
	HasSingleBitTestU32<bksge::uint64_t>();

	HasSingleBitTestU64<bksge::uint64_t>();
}

}	// namespace has_single_bit_test

}	// namespace bksge_bit_test
