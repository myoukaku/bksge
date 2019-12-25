/**
 *	@file	unit_test_fnd_bit_countr_zero.cpp
 *
 *	@brief	countr_zero のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bit/countr_zero.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4307);	// 整数定数がオーバーフローしました。

namespace bksge_bit_test
{

namespace countr_zero_test
{

template <typename T>
void CountrZeroTestU8(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::countr_zero((T)0xff));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::countr_zero((T)0xfe));
	BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::countr_zero((T)0xfc));
	BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::countr_zero((T)0xf8));
	BKSGE_CONSTEXPR_EXPECT_EQ(4, bksge::countr_zero((T)0xf0));
	BKSGE_CONSTEXPR_EXPECT_EQ(5, bksge::countr_zero((T)0xe0));
	BKSGE_CONSTEXPR_EXPECT_EQ(6, bksge::countr_zero((T)0xc0));
	BKSGE_CONSTEXPR_EXPECT_EQ(7, bksge::countr_zero((T)0x80));
	BKSGE_CONSTEXPR_EXPECT_EQ(8, bksge::countr_zero((T)0x00));

	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::countr_zero((T)0x01));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::countr_zero((T)0x02));
	BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::countr_zero((T)0x04));
	BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::countr_zero((T)0x08));
	BKSGE_CONSTEXPR_EXPECT_EQ(4, bksge::countr_zero((T)0x10));
	BKSGE_CONSTEXPR_EXPECT_EQ(5, bksge::countr_zero((T)0x20));
	BKSGE_CONSTEXPR_EXPECT_EQ(6, bksge::countr_zero((T)0x40));
	BKSGE_CONSTEXPR_EXPECT_EQ(7, bksge::countr_zero((T)0x80));
}

template <typename T>
void CountrZeroTestU16(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countr_zero((T)0xffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::countr_zero((T)0xfffe));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::countr_zero((T)0xfffc));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, bksge::countr_zero((T)0xfff8));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::countr_zero((T)0xfff0));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::countr_zero((T)0xffe0));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::countr_zero((T)0xffc0));
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, bksge::countr_zero((T)0xff80));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::countr_zero((T)0xff00));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, bksge::countr_zero((T)0xfe00));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::countr_zero((T)0xfc00));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::countr_zero((T)0xf800));
	BKSGE_CONSTEXPR_EXPECT_EQ(12, bksge::countr_zero((T)0xf000));
	BKSGE_CONSTEXPR_EXPECT_EQ(13, bksge::countr_zero((T)0xe000));
	BKSGE_CONSTEXPR_EXPECT_EQ(14, bksge::countr_zero((T)0xc000));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::countr_zero((T)0x8000));
	BKSGE_CONSTEXPR_EXPECT_EQ(16, bksge::countr_zero((T)0x0000));

	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::countr_zero((T)0x0100));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, bksge::countr_zero((T)0x0200));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::countr_zero((T)0x0400));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::countr_zero((T)0x0800));
	BKSGE_CONSTEXPR_EXPECT_EQ(12, bksge::countr_zero((T)0x1000));
	BKSGE_CONSTEXPR_EXPECT_EQ(13, bksge::countr_zero((T)0x2000));
	BKSGE_CONSTEXPR_EXPECT_EQ(14, bksge::countr_zero((T)0x4000));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::countr_zero((T)0x8000));
}

template <typename T>
void CountrZeroTestU32(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countr_zero((T)0xffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::countr_zero((T)0xfffffffe));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::countr_zero((T)0xfffffffc));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, bksge::countr_zero((T)0xfffffff8));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::countr_zero((T)0xfffffff0));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::countr_zero((T)0xffffffe0));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::countr_zero((T)0xffffffc0));
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, bksge::countr_zero((T)0xffffff80));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::countr_zero((T)0xffffff00));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, bksge::countr_zero((T)0xfffffe00));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::countr_zero((T)0xfffffc00));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::countr_zero((T)0xfffff800));
	BKSGE_CONSTEXPR_EXPECT_EQ(12, bksge::countr_zero((T)0xfffff000));
	BKSGE_CONSTEXPR_EXPECT_EQ(13, bksge::countr_zero((T)0xffffe000));
	BKSGE_CONSTEXPR_EXPECT_EQ(14, bksge::countr_zero((T)0xffffc000));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::countr_zero((T)0xffff8000));
	BKSGE_CONSTEXPR_EXPECT_EQ(16, bksge::countr_zero((T)0xffff0000));
	BKSGE_CONSTEXPR_EXPECT_EQ(17, bksge::countr_zero((T)0xfffe0000));
	BKSGE_CONSTEXPR_EXPECT_EQ(18, bksge::countr_zero((T)0xfffc0000));
	BKSGE_CONSTEXPR_EXPECT_EQ(19, bksge::countr_zero((T)0xfff80000));
	BKSGE_CONSTEXPR_EXPECT_EQ(20, bksge::countr_zero((T)0xfff00000));
	BKSGE_CONSTEXPR_EXPECT_EQ(21, bksge::countr_zero((T)0xffe00000));
	BKSGE_CONSTEXPR_EXPECT_EQ(22, bksge::countr_zero((T)0xffc00000));
	BKSGE_CONSTEXPR_EXPECT_EQ(23, bksge::countr_zero((T)0xff800000));
	BKSGE_CONSTEXPR_EXPECT_EQ(24, bksge::countr_zero((T)0xff000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(25, bksge::countr_zero((T)0xfe000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(26, bksge::countr_zero((T)0xfc000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(27, bksge::countr_zero((T)0xf8000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(28, bksge::countr_zero((T)0xf0000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(29, bksge::countr_zero((T)0xe0000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(30, bksge::countr_zero((T)0xc0000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(31, bksge::countr_zero((T)0x80000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(32, bksge::countr_zero((T)0x00000000));

	BKSGE_CONSTEXPR_EXPECT_EQ(16, bksge::countr_zero((T)0x00010000));
	BKSGE_CONSTEXPR_EXPECT_EQ(17, bksge::countr_zero((T)0x00020000));
	BKSGE_CONSTEXPR_EXPECT_EQ(18, bksge::countr_zero((T)0x00040000));
	BKSGE_CONSTEXPR_EXPECT_EQ(19, bksge::countr_zero((T)0x00080000));
	BKSGE_CONSTEXPR_EXPECT_EQ(20, bksge::countr_zero((T)0x00100000));
	BKSGE_CONSTEXPR_EXPECT_EQ(21, bksge::countr_zero((T)0x00200000));
	BKSGE_CONSTEXPR_EXPECT_EQ(22, bksge::countr_zero((T)0x00400000));
	BKSGE_CONSTEXPR_EXPECT_EQ(23, bksge::countr_zero((T)0x00800000));
	BKSGE_CONSTEXPR_EXPECT_EQ(24, bksge::countr_zero((T)0x01000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(25, bksge::countr_zero((T)0x02000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(26, bksge::countr_zero((T)0x04000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(27, bksge::countr_zero((T)0x08000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(28, bksge::countr_zero((T)0x10000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(29, bksge::countr_zero((T)0x20000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(30, bksge::countr_zero((T)0x40000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(31, bksge::countr_zero((T)0x80000000));
}

template <typename T>
void CountrZeroTestU64(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countr_zero((T)0xffffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::countr_zero((T)0xfffffffffffffffe));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::countr_zero((T)0xfffffffffffffffc));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, bksge::countr_zero((T)0xfffffffffffffff8));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::countr_zero((T)0xfffffffffffffff0));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::countr_zero((T)0xffffffffffffffe0));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::countr_zero((T)0xffffffffffffffc0));
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, bksge::countr_zero((T)0xffffffffffffff80));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::countr_zero((T)0xffffffffffffff00));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, bksge::countr_zero((T)0xfffffffffffffe00));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::countr_zero((T)0xfffffffffffffc00));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::countr_zero((T)0xfffffffffffff800));
	BKSGE_CONSTEXPR_EXPECT_EQ(12, bksge::countr_zero((T)0xfffffffffffff000));
	BKSGE_CONSTEXPR_EXPECT_EQ(13, bksge::countr_zero((T)0xffffffffffffe000));
	BKSGE_CONSTEXPR_EXPECT_EQ(14, bksge::countr_zero((T)0xffffffffffffc000));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::countr_zero((T)0xffffffffffff8000));
	BKSGE_CONSTEXPR_EXPECT_EQ(16, bksge::countr_zero((T)0xffffffffffff0000));
	BKSGE_CONSTEXPR_EXPECT_EQ(17, bksge::countr_zero((T)0xfffffffffffe0000));
	BKSGE_CONSTEXPR_EXPECT_EQ(18, bksge::countr_zero((T)0xfffffffffffc0000));
	BKSGE_CONSTEXPR_EXPECT_EQ(19, bksge::countr_zero((T)0xfffffffffff80000));
	BKSGE_CONSTEXPR_EXPECT_EQ(20, bksge::countr_zero((T)0xfffffffffff00000));
	BKSGE_CONSTEXPR_EXPECT_EQ(21, bksge::countr_zero((T)0xffffffffffe00000));
	BKSGE_CONSTEXPR_EXPECT_EQ(22, bksge::countr_zero((T)0xffffffffffc00000));
	BKSGE_CONSTEXPR_EXPECT_EQ(23, bksge::countr_zero((T)0xffffffffff800000));
	BKSGE_CONSTEXPR_EXPECT_EQ(24, bksge::countr_zero((T)0xffffffffff000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(25, bksge::countr_zero((T)0xfffffffffe000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(26, bksge::countr_zero((T)0xfffffffffc000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(27, bksge::countr_zero((T)0xfffffffff8000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(28, bksge::countr_zero((T)0xfffffffff0000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(29, bksge::countr_zero((T)0xffffffffe0000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(30, bksge::countr_zero((T)0xffffffffc0000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(31, bksge::countr_zero((T)0xffffffff80000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(32, bksge::countr_zero((T)0xffffffff00000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(33, bksge::countr_zero((T)0xfffffffe00000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(34, bksge::countr_zero((T)0xfffffffc00000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(35, bksge::countr_zero((T)0xfffffff800000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(36, bksge::countr_zero((T)0xfffffff000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(37, bksge::countr_zero((T)0xffffffe000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(38, bksge::countr_zero((T)0xffffffc000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(39, bksge::countr_zero((T)0xffffff8000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(40, bksge::countr_zero((T)0xffffff0000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(41, bksge::countr_zero((T)0xfffffe0000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(42, bksge::countr_zero((T)0xfffffc0000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(43, bksge::countr_zero((T)0xfffff80000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(44, bksge::countr_zero((T)0xfffff00000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(45, bksge::countr_zero((T)0xffffe00000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(46, bksge::countr_zero((T)0xffffc00000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(47, bksge::countr_zero((T)0xffff800000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(48, bksge::countr_zero((T)0xffff000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(49, bksge::countr_zero((T)0xfffe000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(50, bksge::countr_zero((T)0xfffc000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(51, bksge::countr_zero((T)0xfff8000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(52, bksge::countr_zero((T)0xfff0000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(53, bksge::countr_zero((T)0xffe0000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(54, bksge::countr_zero((T)0xffc0000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(55, bksge::countr_zero((T)0xff80000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(56, bksge::countr_zero((T)0xff00000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(57, bksge::countr_zero((T)0xfe00000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(58, bksge::countr_zero((T)0xfc00000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(59, bksge::countr_zero((T)0xf800000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(60, bksge::countr_zero((T)0xf000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(61, bksge::countr_zero((T)0xe000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(62, bksge::countr_zero((T)0xc000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(63, bksge::countr_zero((T)0x8000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(64, bksge::countr_zero((T)0x0000000000000000));

	BKSGE_CONSTEXPR_EXPECT_EQ(32, bksge::countr_zero((T)0x0000000100000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(33, bksge::countr_zero((T)0x0000000200000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(34, bksge::countr_zero((T)0x0000000400000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(35, bksge::countr_zero((T)0x0000000800000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(36, bksge::countr_zero((T)0x0000001000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(37, bksge::countr_zero((T)0x0000002000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(38, bksge::countr_zero((T)0x0000004000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(39, bksge::countr_zero((T)0x0000008000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(40, bksge::countr_zero((T)0x0000010000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(41, bksge::countr_zero((T)0x0000020000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(42, bksge::countr_zero((T)0x0000040000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(43, bksge::countr_zero((T)0x0000080000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(44, bksge::countr_zero((T)0x0000100000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(45, bksge::countr_zero((T)0x0000200000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(46, bksge::countr_zero((T)0x0000400000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(47, bksge::countr_zero((T)0x0000800000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(48, bksge::countr_zero((T)0x0001000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(49, bksge::countr_zero((T)0x0002000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(50, bksge::countr_zero((T)0x0004000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(51, bksge::countr_zero((T)0x0008000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(52, bksge::countr_zero((T)0x0010000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(53, bksge::countr_zero((T)0x0020000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(54, bksge::countr_zero((T)0x0040000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(55, bksge::countr_zero((T)0x0080000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(56, bksge::countr_zero((T)0x0100000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(57, bksge::countr_zero((T)0x0200000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(58, bksge::countr_zero((T)0x0400000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(59, bksge::countr_zero((T)0x0800000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(60, bksge::countr_zero((T)0x1000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(61, bksge::countr_zero((T)0x2000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(62, bksge::countr_zero((T)0x4000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(63, bksge::countr_zero((T)0x8000000000000000));
}

GTEST_TEST(BitTest, CountrZeroTest)
{
	CountrZeroTestU8<std::uint8_t>();
	CountrZeroTestU16<std::uint16_t>();
	CountrZeroTestU32<std::uint32_t>();
	CountrZeroTestU64<std::uint64_t>();
}

}	// namespace countr_zero_test

}	// namespace bksge_bit_test

BKSGE_WARNING_POP();
