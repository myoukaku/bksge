/**
 *	@file	unit_test_fnd_bit_popcount.cpp
 *
 *	@brief	popcount のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bit/popcount.hpp>
#include <cstdint>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4307);	// 整数定数がオーバーフローしました。

namespace bksge_bit_test
{

namespace popcount_test
{

template <typename T>
void PopCountTestU8(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::popcount((T)0x00));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::popcount((T)0x01));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::popcount((T)0x02));
	BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::popcount((T)0x03));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::popcount((T)0x04));
	BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::popcount((T)0x05));
	BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::popcount((T)0x06));
	BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::popcount((T)0x07));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::popcount((T)0x08));
	BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::popcount((T)0x09));
	BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::popcount((T)0x0a));
	BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::popcount((T)0x0b));
	BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::popcount((T)0x0c));
	BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::popcount((T)0x0d));
	BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::popcount((T)0x0e));
	BKSGE_CONSTEXPR_EXPECT_EQ(4, bksge::popcount((T)0x0f));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::popcount((T)0x10));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::popcount((T)0x20));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::popcount((T)0x40));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::popcount((T)0x80));
	BKSGE_CONSTEXPR_EXPECT_EQ(4, bksge::popcount((T)0xf0));
	BKSGE_CONSTEXPR_EXPECT_EQ(5, bksge::popcount((T)0xf1));
	BKSGE_CONSTEXPR_EXPECT_EQ(6, bksge::popcount((T)0xf3));
	BKSGE_CONSTEXPR_EXPECT_EQ(7, bksge::popcount((T)0xf7));
	BKSGE_CONSTEXPR_EXPECT_EQ(8, bksge::popcount((T)0xff));
}

template <typename T>
void PopCountTestU16(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x0100));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x0200));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x0400));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x0800));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x1000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x2000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x4000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x8000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, bksge::popcount((T)0x01ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::popcount((T)0x03ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::popcount((T)0x07ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(12, bksge::popcount((T)0x0fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(13, bksge::popcount((T)0x1fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(14, bksge::popcount((T)0x3fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::popcount((T)0x7fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(16, bksge::popcount((T)0xffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::popcount((T)0xf100));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::popcount((T)0xf300));
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, bksge::popcount((T)0xf700));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::popcount((T)0xff00));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::popcount((T)0x1234));
}

template <typename T>
void PopCountTestU32(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x00010000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x00020000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x00040000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x00080000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x00100000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x00200000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x00400000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x00800000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x01000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x02000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x04000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x08000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x10000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x20000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x40000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x80000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(17, bksge::popcount((T)0x0001ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(18, bksge::popcount((T)0x0003ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(19, bksge::popcount((T)0x0007ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(20, bksge::popcount((T)0x000fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(21, bksge::popcount((T)0x001fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(22, bksge::popcount((T)0x003fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(23, bksge::popcount((T)0x007fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(24, bksge::popcount((T)0x00ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(25, bksge::popcount((T)0x01ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(26, bksge::popcount((T)0x03ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(27, bksge::popcount((T)0x07ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(28, bksge::popcount((T)0x0fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(29, bksge::popcount((T)0x1fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(30, bksge::popcount((T)0x3fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(31, bksge::popcount((T)0x7fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(32, bksge::popcount((T)0xffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::popcount((T)0xf1000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::popcount((T)0xf3000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, bksge::popcount((T)0xf7000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::popcount((T)0xff000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(13, bksge::popcount((T)0x12345678));
}

template <typename T>
void PopCountTestU64(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(64, bksge::popcount((T)0xffffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(63, bksge::popcount((T)0xfffffffffffffffe));
	BKSGE_CONSTEXPR_EXPECT_EQ(62, bksge::popcount((T)0xfffffffffffffffc));
	BKSGE_CONSTEXPR_EXPECT_EQ(61, bksge::popcount((T)0xfffffffffffffff8));
	BKSGE_CONSTEXPR_EXPECT_EQ(60, bksge::popcount((T)0xfffffffffffffff0));
	BKSGE_CONSTEXPR_EXPECT_EQ(59, bksge::popcount((T)0xffffffffffffffe0));
	BKSGE_CONSTEXPR_EXPECT_EQ(58, bksge::popcount((T)0xffffffffffffffc0));
	BKSGE_CONSTEXPR_EXPECT_EQ(57, bksge::popcount((T)0xffffffffffffff80));
	BKSGE_CONSTEXPR_EXPECT_EQ(56, bksge::popcount((T)0xffffffffffffff00));
	BKSGE_CONSTEXPR_EXPECT_EQ(55, bksge::popcount((T)0xfffffffffffffe00));
	BKSGE_CONSTEXPR_EXPECT_EQ(54, bksge::popcount((T)0xfffffffffffffc00));
	BKSGE_CONSTEXPR_EXPECT_EQ(53, bksge::popcount((T)0xfffffffffffff800));
	BKSGE_CONSTEXPR_EXPECT_EQ(52, bksge::popcount((T)0xfffffffffffff000));
	BKSGE_CONSTEXPR_EXPECT_EQ(51, bksge::popcount((T)0xffffffffffffe000));
	BKSGE_CONSTEXPR_EXPECT_EQ(50, bksge::popcount((T)0xffffffffffffc000));
	BKSGE_CONSTEXPR_EXPECT_EQ(49, bksge::popcount((T)0xffffffffffff8000));
	BKSGE_CONSTEXPR_EXPECT_EQ(48, bksge::popcount((T)0xffffffffffff0000));
	BKSGE_CONSTEXPR_EXPECT_EQ(47, bksge::popcount((T)0xfffffffffffe0000));
	BKSGE_CONSTEXPR_EXPECT_EQ(46, bksge::popcount((T)0xfffffffffffc0000));
	BKSGE_CONSTEXPR_EXPECT_EQ(45, bksge::popcount((T)0xfffffffffff80000));
	BKSGE_CONSTEXPR_EXPECT_EQ(44, bksge::popcount((T)0xfffffffffff00000));
	BKSGE_CONSTEXPR_EXPECT_EQ(43, bksge::popcount((T)0xffffffffffe00000));
	BKSGE_CONSTEXPR_EXPECT_EQ(42, bksge::popcount((T)0xffffffffffc00000));
	BKSGE_CONSTEXPR_EXPECT_EQ(41, bksge::popcount((T)0xffffffffff800000));
	BKSGE_CONSTEXPR_EXPECT_EQ(40, bksge::popcount((T)0xffffffffff000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(39, bksge::popcount((T)0xfffffffffe000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(38, bksge::popcount((T)0xfffffffffc000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(37, bksge::popcount((T)0xfffffffff8000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(36, bksge::popcount((T)0xfffffffff0000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(35, bksge::popcount((T)0xffffffffe0000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(34, bksge::popcount((T)0xffffffffc0000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(33, bksge::popcount((T)0xffffffff80000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(32, bksge::popcount((T)0xffffffff00000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(31, bksge::popcount((T)0xfffffffe00000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(30, bksge::popcount((T)0xfffffffc00000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(29, bksge::popcount((T)0xfffffff800000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(28, bksge::popcount((T)0xfffffff000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(27, bksge::popcount((T)0xffffffe000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(26, bksge::popcount((T)0xffffffc000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(25, bksge::popcount((T)0xffffff8000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(24, bksge::popcount((T)0xffffff0000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(23, bksge::popcount((T)0xfffffe0000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(22, bksge::popcount((T)0xfffffc0000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(21, bksge::popcount((T)0xfffff80000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(20, bksge::popcount((T)0xfffff00000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(19, bksge::popcount((T)0xffffe00000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(18, bksge::popcount((T)0xffffc00000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(17, bksge::popcount((T)0xffff800000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(16, bksge::popcount((T)0xffff000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::popcount((T)0xfffe000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(14, bksge::popcount((T)0xfffc000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(13, bksge::popcount((T)0xfff8000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(12, bksge::popcount((T)0xfff0000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::popcount((T)0xffe0000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::popcount((T)0xffc0000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, bksge::popcount((T)0xff80000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::popcount((T)0xff00000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, bksge::popcount((T)0xfe00000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::popcount((T)0xfc00000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::popcount((T)0xf800000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::popcount((T)0xf000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, bksge::popcount((T)0xe000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::popcount((T)0xc000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::popcount((T)0x8000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::popcount((T)0x0000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(32, bksge::popcount((T)0x123456789abcdef0));
}

GTEST_TEST(BitTest, PopCountTest)
{
	PopCountTestU8<std::uint8_t>();
	PopCountTestU8<std::uint16_t>();
	PopCountTestU8<std::uint32_t>();
	PopCountTestU8<std::uint64_t>();

	PopCountTestU16<std::uint16_t>();
	PopCountTestU16<std::uint32_t>();
	PopCountTestU16<std::uint64_t>();

	PopCountTestU32<std::uint32_t>();
	PopCountTestU32<std::uint64_t>();

	PopCountTestU64<std::uint64_t>();
}

}	// namespace popcount_test

}	// namespace bksge_bit_test

BKSGE_WARNING_POP();
