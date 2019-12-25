/**
 *	@file	unit_test_fnd_bit_countl_zero.cpp
 *
 *	@brief	countl_zero のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bit/countl_zero.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4307);	// 整数定数がオーバーフローしました。

namespace bksge_bit_test
{

namespace countl_zero_test
{

template <typename T>
void CountlZeroTestU8(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::countl_zero((T)0xff));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::countl_zero((T)0x80));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::countl_zero((T)0x7f));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::countl_zero((T)0x40));
	BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::countl_zero((T)0x3f));
	BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::countl_zero((T)0x20));
	BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::countl_zero((T)0x1f));
	BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::countl_zero((T)0x10));
	BKSGE_CONSTEXPR_EXPECT_EQ(4, bksge::countl_zero((T)0x0f));
	BKSGE_CONSTEXPR_EXPECT_EQ(4, bksge::countl_zero((T)0x08));
	BKSGE_CONSTEXPR_EXPECT_EQ(5, bksge::countl_zero((T)0x07));
	BKSGE_CONSTEXPR_EXPECT_EQ(5, bksge::countl_zero((T)0x04));
	BKSGE_CONSTEXPR_EXPECT_EQ(6, bksge::countl_zero((T)0x03));
	BKSGE_CONSTEXPR_EXPECT_EQ(6, bksge::countl_zero((T)0x02));
	BKSGE_CONSTEXPR_EXPECT_EQ(7, bksge::countl_zero((T)0x01));
	BKSGE_CONSTEXPR_EXPECT_EQ(8, bksge::countl_zero((T)0x00));
}

template <typename T>
void CountlZeroTestU16(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countl_zero((T)0xffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countl_zero((T)0x8000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::countl_zero((T)0x7fff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::countl_zero((T)0x4000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::countl_zero((T)0x3fff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::countl_zero((T)0x2000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, bksge::countl_zero((T)0x1fff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, bksge::countl_zero((T)0x1000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::countl_zero((T)0x0fff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::countl_zero((T)0x0800));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::countl_zero((T)0x07ff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::countl_zero((T)0x0400));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::countl_zero((T)0x03ff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::countl_zero((T)0x0200));
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, bksge::countl_zero((T)0x01ff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, bksge::countl_zero((T)0x0100));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::countl_zero((T)0x00ff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::countl_zero((T)0x0080));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, bksge::countl_zero((T)0x007f));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, bksge::countl_zero((T)0x0040));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::countl_zero((T)0x003f));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::countl_zero((T)0x0020));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::countl_zero((T)0x001f));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::countl_zero((T)0x0010));
	BKSGE_CONSTEXPR_EXPECT_EQ(12, bksge::countl_zero((T)0x000f));
	BKSGE_CONSTEXPR_EXPECT_EQ(12, bksge::countl_zero((T)0x0008));
	BKSGE_CONSTEXPR_EXPECT_EQ(13, bksge::countl_zero((T)0x0007));
	BKSGE_CONSTEXPR_EXPECT_EQ(13, bksge::countl_zero((T)0x0004));
	BKSGE_CONSTEXPR_EXPECT_EQ(14, bksge::countl_zero((T)0x0003));
	BKSGE_CONSTEXPR_EXPECT_EQ(14, bksge::countl_zero((T)0x0002));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::countl_zero((T)0x0001));
	BKSGE_CONSTEXPR_EXPECT_EQ(16, bksge::countl_zero((T)0x0000));
}

template <typename T>
void CountlZeroTestU32(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countl_zero((T)0xffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countl_zero((T)0x80000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::countl_zero((T)0x7fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::countl_zero((T)0x40000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::countl_zero((T)0x3fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::countl_zero((T)0x20000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, bksge::countl_zero((T)0x1fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, bksge::countl_zero((T)0x10000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::countl_zero((T)0x0fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::countl_zero((T)0x08000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::countl_zero((T)0x07ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::countl_zero((T)0x04000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::countl_zero((T)0x03ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::countl_zero((T)0x02000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, bksge::countl_zero((T)0x01ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, bksge::countl_zero((T)0x01000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::countl_zero((T)0x00ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::countl_zero((T)0x00800000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, bksge::countl_zero((T)0x007fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, bksge::countl_zero((T)0x00400000));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::countl_zero((T)0x003fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::countl_zero((T)0x00200000));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::countl_zero((T)0x001fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::countl_zero((T)0x00100000));
	BKSGE_CONSTEXPR_EXPECT_EQ(12, bksge::countl_zero((T)0x000fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(12, bksge::countl_zero((T)0x00080000));
	BKSGE_CONSTEXPR_EXPECT_EQ(13, bksge::countl_zero((T)0x0007ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(13, bksge::countl_zero((T)0x00040000));
	BKSGE_CONSTEXPR_EXPECT_EQ(14, bksge::countl_zero((T)0x0003ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(14, bksge::countl_zero((T)0x00020000));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::countl_zero((T)0x0001ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::countl_zero((T)0x00010000));
	BKSGE_CONSTEXPR_EXPECT_EQ(16, bksge::countl_zero((T)0x0000ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(16, bksge::countl_zero((T)0x00008000));
	BKSGE_CONSTEXPR_EXPECT_EQ(17, bksge::countl_zero((T)0x00007fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(17, bksge::countl_zero((T)0x00004000));
	BKSGE_CONSTEXPR_EXPECT_EQ(18, bksge::countl_zero((T)0x00003fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(18, bksge::countl_zero((T)0x00002000));
	BKSGE_CONSTEXPR_EXPECT_EQ(19, bksge::countl_zero((T)0x00001fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(19, bksge::countl_zero((T)0x00001000));
	BKSGE_CONSTEXPR_EXPECT_EQ(20, bksge::countl_zero((T)0x00000fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(20, bksge::countl_zero((T)0x00000800));
	BKSGE_CONSTEXPR_EXPECT_EQ(21, bksge::countl_zero((T)0x000007ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(21, bksge::countl_zero((T)0x00000400));
	BKSGE_CONSTEXPR_EXPECT_EQ(22, bksge::countl_zero((T)0x000003ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(22, bksge::countl_zero((T)0x00000200));
	BKSGE_CONSTEXPR_EXPECT_EQ(23, bksge::countl_zero((T)0x000001ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(23, bksge::countl_zero((T)0x00000100));
	BKSGE_CONSTEXPR_EXPECT_EQ(24, bksge::countl_zero((T)0x000000ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(24, bksge::countl_zero((T)0x00000080));
	BKSGE_CONSTEXPR_EXPECT_EQ(25, bksge::countl_zero((T)0x0000007f));
	BKSGE_CONSTEXPR_EXPECT_EQ(25, bksge::countl_zero((T)0x00000040));
	BKSGE_CONSTEXPR_EXPECT_EQ(26, bksge::countl_zero((T)0x0000003f));
	BKSGE_CONSTEXPR_EXPECT_EQ(26, bksge::countl_zero((T)0x00000020));
	BKSGE_CONSTEXPR_EXPECT_EQ(27, bksge::countl_zero((T)0x0000001f));
	BKSGE_CONSTEXPR_EXPECT_EQ(27, bksge::countl_zero((T)0x00000010));
	BKSGE_CONSTEXPR_EXPECT_EQ(28, bksge::countl_zero((T)0x0000000f));
	BKSGE_CONSTEXPR_EXPECT_EQ(28, bksge::countl_zero((T)0x00000008));
	BKSGE_CONSTEXPR_EXPECT_EQ(29, bksge::countl_zero((T)0x00000007));
	BKSGE_CONSTEXPR_EXPECT_EQ(29, bksge::countl_zero((T)0x00000004));
	BKSGE_CONSTEXPR_EXPECT_EQ(30, bksge::countl_zero((T)0x00000003));
	BKSGE_CONSTEXPR_EXPECT_EQ(30, bksge::countl_zero((T)0x00000002));
	BKSGE_CONSTEXPR_EXPECT_EQ(31, bksge::countl_zero((T)0x00000001));
	BKSGE_CONSTEXPR_EXPECT_EQ(32, bksge::countl_zero((T)0x00000000));
}

template <typename T>
void CountlZeroTestU64(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countl_zero((T)0xffffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countl_zero((T)0x8000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::countl_zero((T)0x7fffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::countl_zero((T)0x4000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::countl_zero((T)0x3fffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::countl_zero((T)0x2000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, bksge::countl_zero((T)0x1fffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, bksge::countl_zero((T)0x1000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::countl_zero((T)0x0fffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::countl_zero((T)0x0800000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::countl_zero((T)0x07ffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::countl_zero((T)0x0400000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::countl_zero((T)0x03ffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::countl_zero((T)0x0200000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, bksge::countl_zero((T)0x01ffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, bksge::countl_zero((T)0x0100000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::countl_zero((T)0x00ffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::countl_zero((T)0x0080000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, bksge::countl_zero((T)0x007fffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, bksge::countl_zero((T)0x0040000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::countl_zero((T)0x003fffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::countl_zero((T)0x0020000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::countl_zero((T)0x001fffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::countl_zero((T)0x0010000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(12, bksge::countl_zero((T)0x000fffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(12, bksge::countl_zero((T)0x0008000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(13, bksge::countl_zero((T)0x0007ffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(13, bksge::countl_zero((T)0x0004000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(14, bksge::countl_zero((T)0x0003ffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(14, bksge::countl_zero((T)0x0002000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::countl_zero((T)0x0001ffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::countl_zero((T)0x0001000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(16, bksge::countl_zero((T)0x0000ffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(16, bksge::countl_zero((T)0x0000800000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(17, bksge::countl_zero((T)0x00007fffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(17, bksge::countl_zero((T)0x0000400000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(18, bksge::countl_zero((T)0x00003fffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(18, bksge::countl_zero((T)0x0000200000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(19, bksge::countl_zero((T)0x00001fffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(19, bksge::countl_zero((T)0x0000100000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(20, bksge::countl_zero((T)0x00000fffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(20, bksge::countl_zero((T)0x0000080000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(21, bksge::countl_zero((T)0x000007ffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(21, bksge::countl_zero((T)0x0000040000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(22, bksge::countl_zero((T)0x000003ffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(22, bksge::countl_zero((T)0x0000020000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(23, bksge::countl_zero((T)0x000001ffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(23, bksge::countl_zero((T)0x0000010000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(24, bksge::countl_zero((T)0x000000ffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(24, bksge::countl_zero((T)0x0000008000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(25, bksge::countl_zero((T)0x0000007fffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(25, bksge::countl_zero((T)0x0000004000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(26, bksge::countl_zero((T)0x0000003fffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(26, bksge::countl_zero((T)0x0000002000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(27, bksge::countl_zero((T)0x0000001fffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(27, bksge::countl_zero((T)0x0000001000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(28, bksge::countl_zero((T)0x0000000fffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(28, bksge::countl_zero((T)0x0000000800000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(29, bksge::countl_zero((T)0x00000007ffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(29, bksge::countl_zero((T)0x0000000400000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(30, bksge::countl_zero((T)0x00000003ffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(30, bksge::countl_zero((T)0x0000000200000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(31, bksge::countl_zero((T)0x00000001ffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(31, bksge::countl_zero((T)0x0000000100000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(32, bksge::countl_zero((T)0x00000000ffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(32, bksge::countl_zero((T)0x0000000080000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(33, bksge::countl_zero((T)0x000000007fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(33, bksge::countl_zero((T)0x0000000040000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(34, bksge::countl_zero((T)0x000000003fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(34, bksge::countl_zero((T)0x0000000020000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(35, bksge::countl_zero((T)0x000000001fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(35, bksge::countl_zero((T)0x0000000010000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(36, bksge::countl_zero((T)0x000000000fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(36, bksge::countl_zero((T)0x0000000008000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(37, bksge::countl_zero((T)0x0000000007ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(37, bksge::countl_zero((T)0x0000000004000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(38, bksge::countl_zero((T)0x0000000003ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(38, bksge::countl_zero((T)0x0000000002000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(39, bksge::countl_zero((T)0x0000000001ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(39, bksge::countl_zero((T)0x0000000001000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(40, bksge::countl_zero((T)0x0000000000ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(40, bksge::countl_zero((T)0x0000000000800000));
	BKSGE_CONSTEXPR_EXPECT_EQ(41, bksge::countl_zero((T)0x00000000007fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(41, bksge::countl_zero((T)0x0000000000400000));
	BKSGE_CONSTEXPR_EXPECT_EQ(42, bksge::countl_zero((T)0x00000000003fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(42, bksge::countl_zero((T)0x0000000000200000));
	BKSGE_CONSTEXPR_EXPECT_EQ(43, bksge::countl_zero((T)0x00000000001fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(43, bksge::countl_zero((T)0x0000000000100000));
	BKSGE_CONSTEXPR_EXPECT_EQ(44, bksge::countl_zero((T)0x00000000000fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(44, bksge::countl_zero((T)0x0000000000080000));
	BKSGE_CONSTEXPR_EXPECT_EQ(45, bksge::countl_zero((T)0x000000000007ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(45, bksge::countl_zero((T)0x0000000000040000));
	BKSGE_CONSTEXPR_EXPECT_EQ(46, bksge::countl_zero((T)0x000000000003ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(46, bksge::countl_zero((T)0x0000000000020000));
	BKSGE_CONSTEXPR_EXPECT_EQ(47, bksge::countl_zero((T)0x000000000001ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(47, bksge::countl_zero((T)0x0000000000010000));
	BKSGE_CONSTEXPR_EXPECT_EQ(48, bksge::countl_zero((T)0x000000000000ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(48, bksge::countl_zero((T)0x0000000000008000));
	BKSGE_CONSTEXPR_EXPECT_EQ(49, bksge::countl_zero((T)0x0000000000007fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(49, bksge::countl_zero((T)0x0000000000004000));
	BKSGE_CONSTEXPR_EXPECT_EQ(50, bksge::countl_zero((T)0x0000000000003fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(50, bksge::countl_zero((T)0x0000000000002000));
	BKSGE_CONSTEXPR_EXPECT_EQ(51, bksge::countl_zero((T)0x0000000000001fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(51, bksge::countl_zero((T)0x0000000000001000));
	BKSGE_CONSTEXPR_EXPECT_EQ(52, bksge::countl_zero((T)0x0000000000000fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(52, bksge::countl_zero((T)0x0000000000000800));
	BKSGE_CONSTEXPR_EXPECT_EQ(53, bksge::countl_zero((T)0x00000000000007ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(53, bksge::countl_zero((T)0x0000000000000400));
	BKSGE_CONSTEXPR_EXPECT_EQ(54, bksge::countl_zero((T)0x00000000000003ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(54, bksge::countl_zero((T)0x0000000000000200));
	BKSGE_CONSTEXPR_EXPECT_EQ(55, bksge::countl_zero((T)0x00000000000001ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(55, bksge::countl_zero((T)0x0000000000000100));
	BKSGE_CONSTEXPR_EXPECT_EQ(56, bksge::countl_zero((T)0x00000000000000ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(56, bksge::countl_zero((T)0x0000000000000080));
	BKSGE_CONSTEXPR_EXPECT_EQ(57, bksge::countl_zero((T)0x000000000000007f));
	BKSGE_CONSTEXPR_EXPECT_EQ(57, bksge::countl_zero((T)0x0000000000000040));
	BKSGE_CONSTEXPR_EXPECT_EQ(58, bksge::countl_zero((T)0x000000000000003f));
	BKSGE_CONSTEXPR_EXPECT_EQ(58, bksge::countl_zero((T)0x0000000000000020));
	BKSGE_CONSTEXPR_EXPECT_EQ(59, bksge::countl_zero((T)0x000000000000001f));
	BKSGE_CONSTEXPR_EXPECT_EQ(59, bksge::countl_zero((T)0x0000000000000010));
	BKSGE_CONSTEXPR_EXPECT_EQ(60, bksge::countl_zero((T)0x000000000000000f));
	BKSGE_CONSTEXPR_EXPECT_EQ(60, bksge::countl_zero((T)0x0000000000000008));
	BKSGE_CONSTEXPR_EXPECT_EQ(61, bksge::countl_zero((T)0x0000000000000007));
	BKSGE_CONSTEXPR_EXPECT_EQ(61, bksge::countl_zero((T)0x0000000000000004));
	BKSGE_CONSTEXPR_EXPECT_EQ(62, bksge::countl_zero((T)0x0000000000000003));
	BKSGE_CONSTEXPR_EXPECT_EQ(62, bksge::countl_zero((T)0x0000000000000002));
	BKSGE_CONSTEXPR_EXPECT_EQ(63, bksge::countl_zero((T)0x0000000000000001));
	BKSGE_CONSTEXPR_EXPECT_EQ(64, bksge::countl_zero((T)0x0000000000000000));
}

GTEST_TEST(BitTest, CountlZeroTest)
{
	CountlZeroTestU8<std::uint8_t>();
	CountlZeroTestU16<std::uint16_t>();
	CountlZeroTestU32<std::uint32_t>();
	CountlZeroTestU64<std::uint64_t>();
}

}	// namespace countl_zero_test

}	// namespace bksge_bit_test

BKSGE_WARNING_POP();
