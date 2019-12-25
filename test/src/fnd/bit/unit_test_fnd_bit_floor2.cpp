﻿/**
 *	@file	unit_test_fnd_bit_floor2.cpp
 *
 *	@brief	floor2 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bit/floor2.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include "constexpr_test.hpp"

namespace bksge_bit_test
{

namespace floor2_test
{

template <typename T>
void Floor2TestU8(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00), bksge::floor2(T(0x00)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x01), bksge::floor2(T(0x01)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x02), bksge::floor2(T(0x02)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x02), bksge::floor2(T(0x03)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x04), bksge::floor2(T(0x04)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x04), bksge::floor2(T(0x05)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x04), bksge::floor2(T(0x07)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x08), bksge::floor2(T(0x08)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x08), bksge::floor2(T(0x09)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x08), bksge::floor2(T(0x0f)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x10), bksge::floor2(T(0x10)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x10), bksge::floor2(T(0x11)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x10), bksge::floor2(T(0x1f)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x20), bksge::floor2(T(0x20)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x20), bksge::floor2(T(0x21)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x20), bksge::floor2(T(0x2f)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x20), bksge::floor2(T(0x30)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x20), bksge::floor2(T(0x31)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x20), bksge::floor2(T(0x3f)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x40), bksge::floor2(T(0x40)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x40), bksge::floor2(T(0x41)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x40), bksge::floor2(T(0x7f)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x80), bksge::floor2(T(0x80)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x80), bksge::floor2(T(0x81)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x80), bksge::floor2(T(0xff)));
}

template <typename T>
void Floor2TestU16(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0100), bksge::floor2(T(0x0100)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0100), bksge::floor2(T(0x0101)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0100), bksge::floor2(T(0x01ff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0200), bksge::floor2(T(0x0200)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0200), bksge::floor2(T(0x0201)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0200), bksge::floor2(T(0x03ff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0400), bksge::floor2(T(0x0400)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0400), bksge::floor2(T(0x0401)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0400), bksge::floor2(T(0x07ff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0800), bksge::floor2(T(0x0800)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0800), bksge::floor2(T(0x0801)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0800), bksge::floor2(T(0x0fff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x1000), bksge::floor2(T(0x1000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x1000), bksge::floor2(T(0x1001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x1000), bksge::floor2(T(0x1fff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x2000), bksge::floor2(T(0x2000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x2000), bksge::floor2(T(0x2001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x2000), bksge::floor2(T(0x3fff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x4000), bksge::floor2(T(0x4000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x4000), bksge::floor2(T(0x4001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x4000), bksge::floor2(T(0x7fff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x8000), bksge::floor2(T(0x8000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x8000), bksge::floor2(T(0x8001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x8000), bksge::floor2(T(0xffff)));
}

template <typename T>
void Floor2TestU32(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00010000), bksge::floor2(T(0x00010000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00010000), bksge::floor2(T(0x00010001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00010000), bksge::floor2(T(0x0001ffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00020000), bksge::floor2(T(0x00020000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00020000), bksge::floor2(T(0x00020001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00020000), bksge::floor2(T(0x0003ffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00040000), bksge::floor2(T(0x00040000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00040000), bksge::floor2(T(0x00040001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00040000), bksge::floor2(T(0x0007ffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00080000), bksge::floor2(T(0x00080000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00080000), bksge::floor2(T(0x00080001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00080000), bksge::floor2(T(0x000fffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00100000), bksge::floor2(T(0x00100000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00100000), bksge::floor2(T(0x00100001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00100000), bksge::floor2(T(0x001fffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00200000), bksge::floor2(T(0x00200000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00200000), bksge::floor2(T(0x00200001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00200000), bksge::floor2(T(0x003fffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00400000), bksge::floor2(T(0x00400000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00400000), bksge::floor2(T(0x00400001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00400000), bksge::floor2(T(0x007fffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00800000), bksge::floor2(T(0x00800000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00800000), bksge::floor2(T(0x00800001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x00800000), bksge::floor2(T(0x00ffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x01000000), bksge::floor2(T(0x01000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x01000000), bksge::floor2(T(0x01000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x01000000), bksge::floor2(T(0x01ffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x02000000), bksge::floor2(T(0x02000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x02000000), bksge::floor2(T(0x02000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x02000000), bksge::floor2(T(0x03ffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x04000000), bksge::floor2(T(0x04000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x04000000), bksge::floor2(T(0x04000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x04000000), bksge::floor2(T(0x07ffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x08000000), bksge::floor2(T(0x08000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x08000000), bksge::floor2(T(0x08000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x08000000), bksge::floor2(T(0x0fffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x10000000), bksge::floor2(T(0x10000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x10000000), bksge::floor2(T(0x10000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x10000000), bksge::floor2(T(0x1fffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x20000000), bksge::floor2(T(0x20000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x20000000), bksge::floor2(T(0x20000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x20000000), bksge::floor2(T(0x3fffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x40000000), bksge::floor2(T(0x40000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x40000000), bksge::floor2(T(0x40000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x40000000), bksge::floor2(T(0x7fffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x80000000), bksge::floor2(T(0x80000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x80000000), bksge::floor2(T(0x80000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x80000000), bksge::floor2(T(0xffffffff)));
}

template <typename T>
void Floor2TestU64(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000000100000000), bksge::floor2(T(0x0000000100000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000000100000000), bksge::floor2(T(0x0000000100000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000000100000000), bksge::floor2(T(0x00000001ffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000000200000000), bksge::floor2(T(0x0000000200000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000000200000000), bksge::floor2(T(0x0000000200000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000000200000000), bksge::floor2(T(0x00000003ffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000000400000000), bksge::floor2(T(0x0000000400000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000000400000000), bksge::floor2(T(0x0000000400000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000000400000000), bksge::floor2(T(0x00000007ffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000000800000000), bksge::floor2(T(0x0000000800000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000000800000000), bksge::floor2(T(0x0000000800000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000000800000000), bksge::floor2(T(0x0000000fffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000001000000000), bksge::floor2(T(0x0000001000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000001000000000), bksge::floor2(T(0x0000001000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000001000000000), bksge::floor2(T(0x0000001fffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000002000000000), bksge::floor2(T(0x0000002000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000002000000000), bksge::floor2(T(0x0000002000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000002000000000), bksge::floor2(T(0x0000003fffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000004000000000), bksge::floor2(T(0x0000004000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000004000000000), bksge::floor2(T(0x0000004000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000004000000000), bksge::floor2(T(0x0000007fffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000008000000000), bksge::floor2(T(0x0000008000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000008000000000), bksge::floor2(T(0x0000008000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000008000000000), bksge::floor2(T(0x000000ffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000010000000000), bksge::floor2(T(0x0000010000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000010000000000), bksge::floor2(T(0x0000010000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000010000000000), bksge::floor2(T(0x000001ffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000020000000000), bksge::floor2(T(0x0000020000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000020000000000), bksge::floor2(T(0x0000020000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000020000000000), bksge::floor2(T(0x000003ffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000040000000000), bksge::floor2(T(0x0000040000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000040000000000), bksge::floor2(T(0x0000040000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000040000000000), bksge::floor2(T(0x000007ffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000080000000000), bksge::floor2(T(0x0000080000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000080000000000), bksge::floor2(T(0x0000080000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000080000000000), bksge::floor2(T(0x00000fffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000100000000000), bksge::floor2(T(0x0000100000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000100000000000), bksge::floor2(T(0x0000100000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000100000000000), bksge::floor2(T(0x00001fffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000200000000000), bksge::floor2(T(0x0000200000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000200000000000), bksge::floor2(T(0x0000200000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000200000000000), bksge::floor2(T(0x00003fffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000400000000000), bksge::floor2(T(0x0000400000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000400000000000), bksge::floor2(T(0x0000400000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000400000000000), bksge::floor2(T(0x00007fffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000800000000000), bksge::floor2(T(0x0000800000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000800000000000), bksge::floor2(T(0x0000800000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0000800000000000), bksge::floor2(T(0x0000ffffffffffff)));

	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0001000000000000), bksge::floor2(T(0x0001000000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0001000000000000), bksge::floor2(T(0x0001000000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0001000000000000), bksge::floor2(T(0x0001ffffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0002000000000000), bksge::floor2(T(0x0002000000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0002000000000000), bksge::floor2(T(0x0002000000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0002000000000000), bksge::floor2(T(0x0003ffffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0004000000000000), bksge::floor2(T(0x0004000000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0004000000000000), bksge::floor2(T(0x0004000000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0004000000000000), bksge::floor2(T(0x0007ffffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0008000000000000), bksge::floor2(T(0x0008000000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0008000000000000), bksge::floor2(T(0x0008000000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0008000000000000), bksge::floor2(T(0x000fffffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0010000000000000), bksge::floor2(T(0x0010000000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0010000000000000), bksge::floor2(T(0x0010000000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0010000000000000), bksge::floor2(T(0x001fffffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0020000000000000), bksge::floor2(T(0x0020000000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0020000000000000), bksge::floor2(T(0x0020000000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0020000000000000), bksge::floor2(T(0x003fffffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0040000000000000), bksge::floor2(T(0x0040000000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0040000000000000), bksge::floor2(T(0x0040000000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0040000000000000), bksge::floor2(T(0x007fffffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0080000000000000), bksge::floor2(T(0x0080000000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0080000000000000), bksge::floor2(T(0x0080000000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0080000000000000), bksge::floor2(T(0x00ffffffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0100000000000000), bksge::floor2(T(0x0100000000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0100000000000000), bksge::floor2(T(0x0100000000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0100000000000000), bksge::floor2(T(0x01ffffffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0200000000000000), bksge::floor2(T(0x0200000000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0200000000000000), bksge::floor2(T(0x0200000000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0200000000000000), bksge::floor2(T(0x03ffffffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0400000000000000), bksge::floor2(T(0x0400000000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0400000000000000), bksge::floor2(T(0x0400000000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0400000000000000), bksge::floor2(T(0x07ffffffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0800000000000000), bksge::floor2(T(0x0800000000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0800000000000000), bksge::floor2(T(0x0800000000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x0800000000000000), bksge::floor2(T(0x0fffffffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x1000000000000000), bksge::floor2(T(0x1000000000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x1000000000000000), bksge::floor2(T(0x1000000000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x1000000000000000), bksge::floor2(T(0x1fffffffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x2000000000000000), bksge::floor2(T(0x2000000000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x2000000000000000), bksge::floor2(T(0x2000000000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x2000000000000000), bksge::floor2(T(0x3fffffffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x4000000000000000), bksge::floor2(T(0x4000000000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x4000000000000000), bksge::floor2(T(0x4000000000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x4000000000000000), bksge::floor2(T(0x7fffffffffffffff)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x8000000000000000), bksge::floor2(T(0x8000000000000000)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x8000000000000000), bksge::floor2(T(0x8000000000000001)));
	BKSGE_CONSTEXPR_EXPECT_EQ(T(0x8000000000000000), bksge::floor2(T(0xffffffffffffffff)));
}

GTEST_TEST(BitTest, Floor2Test)
{
	Floor2TestU8<std::uint8_t>();
	Floor2TestU8<std::uint16_t>();
	Floor2TestU8<std::uint32_t>();
	Floor2TestU8<std::uint64_t>();

	Floor2TestU16<std::uint16_t>();
	Floor2TestU16<std::uint32_t>();
	Floor2TestU16<std::uint64_t>();

	Floor2TestU32<std::uint32_t>();
	Floor2TestU32<std::uint64_t>();

	Floor2TestU64<std::uint64_t>();
}

}	// namespace floor2_test

}	// namespace bksge_bit_test
