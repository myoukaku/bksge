/**
 *	@file	unit_test_fnd_bit_countl_one.cpp
 *
 *	@brief	countl_one のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bit/countl_one.hpp>
#include <cstdint>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4307);	// 整数定数がオーバーフローしました。

namespace bksge_bit_test
{

namespace countl_one_test
{

template <typename T>
void CountlOneTestU8(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(8, bksge::countl_one((T)0xff));
	BKSGE_CONSTEXPR_EXPECT_EQ(7, bksge::countl_one((T)0xfe));
	BKSGE_CONSTEXPR_EXPECT_EQ(6, bksge::countl_one((T)0xfc));
	BKSGE_CONSTEXPR_EXPECT_EQ(5, bksge::countl_one((T)0xf8));
	BKSGE_CONSTEXPR_EXPECT_EQ(4, bksge::countl_one((T)0xf0));
	BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::countl_one((T)0xe0));
	BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::countl_one((T)0xc0));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::countl_one((T)0x80));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::countl_one((T)0x00));

	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::countl_one((T)0x01));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::countl_one((T)0x02));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::countl_one((T)0x03));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::countl_one((T)0x04));
	BKSGE_CONSTEXPR_EXPECT_EQ(4, bksge::countl_one((T)0xf1));
	BKSGE_CONSTEXPR_EXPECT_EQ(4, bksge::countl_one((T)0xf2));
	BKSGE_CONSTEXPR_EXPECT_EQ(4, bksge::countl_one((T)0xf3));
	BKSGE_CONSTEXPR_EXPECT_EQ(4, bksge::countl_one((T)0xf4));
	BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::countl_one((T)0xe1));
	BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::countl_one((T)0xe2));
	BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::countl_one((T)0xe3));
	BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::countl_one((T)0xe4));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::countl_one((T)0x81));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::countl_one((T)0x82));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::countl_one((T)0x83));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::countl_one((T)0x84));
}

template <typename T>
void CountlOneTestU16(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(16, bksge::countl_one((T)0xffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::countl_one((T)0xfffe));
	BKSGE_CONSTEXPR_EXPECT_EQ(14, bksge::countl_one((T)0xfffc));
	BKSGE_CONSTEXPR_EXPECT_EQ(13, bksge::countl_one((T)0xfff8));
	BKSGE_CONSTEXPR_EXPECT_EQ(12, bksge::countl_one((T)0xfff0));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::countl_one((T)0xffe0));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::countl_one((T)0xffc0));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, bksge::countl_one((T)0xff80));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::countl_one((T)0xff00));
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, bksge::countl_one((T)0xfe00));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::countl_one((T)0xfc00));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::countl_one((T)0xf800));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::countl_one((T)0xf000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, bksge::countl_one((T)0xe000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::countl_one((T)0xc000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::countl_one((T)0x8000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countl_one((T)0x0000));

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countl_one((T)0x0001));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countl_one((T)0x0002));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countl_one((T)0x0003));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countl_one((T)0x0004));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::countl_one((T)0xf001));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::countl_one((T)0xf082));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::countl_one((T)0xf0c3));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::countl_one((T)0xf0f4));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::countl_one((T)0xff01));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::countl_one((T)0xff02));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::countl_one((T)0xff03));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::countl_one((T)0xff04));
}

template <typename T>
void CountlOneTestU32(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(32, bksge::countl_one((T)0xffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(31, bksge::countl_one((T)0xfffffffe));
	BKSGE_CONSTEXPR_EXPECT_EQ(30, bksge::countl_one((T)0xfffffffc));
	BKSGE_CONSTEXPR_EXPECT_EQ(29, bksge::countl_one((T)0xfffffff8));
	BKSGE_CONSTEXPR_EXPECT_EQ(28, bksge::countl_one((T)0xfffffff0));
	BKSGE_CONSTEXPR_EXPECT_EQ(27, bksge::countl_one((T)0xffffffe0));
	BKSGE_CONSTEXPR_EXPECT_EQ(26, bksge::countl_one((T)0xffffffc0));
	BKSGE_CONSTEXPR_EXPECT_EQ(25, bksge::countl_one((T)0xffffff80));
	BKSGE_CONSTEXPR_EXPECT_EQ(24, bksge::countl_one((T)0xffffff00));
	BKSGE_CONSTEXPR_EXPECT_EQ(23, bksge::countl_one((T)0xfffffe00));
	BKSGE_CONSTEXPR_EXPECT_EQ(22, bksge::countl_one((T)0xfffffc00));
	BKSGE_CONSTEXPR_EXPECT_EQ(21, bksge::countl_one((T)0xfffff800));
	BKSGE_CONSTEXPR_EXPECT_EQ(20, bksge::countl_one((T)0xfffff000));
	BKSGE_CONSTEXPR_EXPECT_EQ(19, bksge::countl_one((T)0xffffe000));
	BKSGE_CONSTEXPR_EXPECT_EQ(18, bksge::countl_one((T)0xffffc000));
	BKSGE_CONSTEXPR_EXPECT_EQ(17, bksge::countl_one((T)0xffff8000));
	BKSGE_CONSTEXPR_EXPECT_EQ(16, bksge::countl_one((T)0xffff0000));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::countl_one((T)0xfffe0000));
	BKSGE_CONSTEXPR_EXPECT_EQ(14, bksge::countl_one((T)0xfffc0000));
	BKSGE_CONSTEXPR_EXPECT_EQ(13, bksge::countl_one((T)0xfff80000));
	BKSGE_CONSTEXPR_EXPECT_EQ(12, bksge::countl_one((T)0xfff00000));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::countl_one((T)0xffe00000));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::countl_one((T)0xffc00000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, bksge::countl_one((T)0xff800000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::countl_one((T)0xff000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, bksge::countl_one((T)0xfe000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::countl_one((T)0xfc000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::countl_one((T)0xf8000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::countl_one((T)0xf0000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, bksge::countl_one((T)0xe0000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::countl_one((T)0xc0000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::countl_one((T)0x80000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countl_one((T)0x00000000));
}

template <typename T>
void CountlOneTestU64(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(64, bksge::countl_one((T)0xffffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(63, bksge::countl_one((T)0xfffffffffffffffe));
	BKSGE_CONSTEXPR_EXPECT_EQ(62, bksge::countl_one((T)0xfffffffffffffffc));
	BKSGE_CONSTEXPR_EXPECT_EQ(61, bksge::countl_one((T)0xfffffffffffffff8));
	BKSGE_CONSTEXPR_EXPECT_EQ(60, bksge::countl_one((T)0xfffffffffffffff0));
	BKSGE_CONSTEXPR_EXPECT_EQ(59, bksge::countl_one((T)0xffffffffffffffe0));
	BKSGE_CONSTEXPR_EXPECT_EQ(58, bksge::countl_one((T)0xffffffffffffffc0));
	BKSGE_CONSTEXPR_EXPECT_EQ(57, bksge::countl_one((T)0xffffffffffffff80));
	BKSGE_CONSTEXPR_EXPECT_EQ(56, bksge::countl_one((T)0xffffffffffffff00));
	BKSGE_CONSTEXPR_EXPECT_EQ(55, bksge::countl_one((T)0xfffffffffffffe00));
	BKSGE_CONSTEXPR_EXPECT_EQ(54, bksge::countl_one((T)0xfffffffffffffc00));
	BKSGE_CONSTEXPR_EXPECT_EQ(53, bksge::countl_one((T)0xfffffffffffff800));
	BKSGE_CONSTEXPR_EXPECT_EQ(52, bksge::countl_one((T)0xfffffffffffff000));
	BKSGE_CONSTEXPR_EXPECT_EQ(51, bksge::countl_one((T)0xffffffffffffe000));
	BKSGE_CONSTEXPR_EXPECT_EQ(50, bksge::countl_one((T)0xffffffffffffc000));
	BKSGE_CONSTEXPR_EXPECT_EQ(49, bksge::countl_one((T)0xffffffffffff8000));
	BKSGE_CONSTEXPR_EXPECT_EQ(48, bksge::countl_one((T)0xffffffffffff0000));
	BKSGE_CONSTEXPR_EXPECT_EQ(47, bksge::countl_one((T)0xfffffffffffe0000));
	BKSGE_CONSTEXPR_EXPECT_EQ(46, bksge::countl_one((T)0xfffffffffffc0000));
	BKSGE_CONSTEXPR_EXPECT_EQ(45, bksge::countl_one((T)0xfffffffffff80000));
	BKSGE_CONSTEXPR_EXPECT_EQ(44, bksge::countl_one((T)0xfffffffffff00000));
	BKSGE_CONSTEXPR_EXPECT_EQ(43, bksge::countl_one((T)0xffffffffffe00000));
	BKSGE_CONSTEXPR_EXPECT_EQ(42, bksge::countl_one((T)0xffffffffffc00000));
	BKSGE_CONSTEXPR_EXPECT_EQ(41, bksge::countl_one((T)0xffffffffff800000));
	BKSGE_CONSTEXPR_EXPECT_EQ(40, bksge::countl_one((T)0xffffffffff000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(39, bksge::countl_one((T)0xfffffffffe000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(38, bksge::countl_one((T)0xfffffffffc000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(37, bksge::countl_one((T)0xfffffffff8000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(36, bksge::countl_one((T)0xfffffffff0000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(35, bksge::countl_one((T)0xffffffffe0000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(34, bksge::countl_one((T)0xffffffffc0000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(33, bksge::countl_one((T)0xffffffff80000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(32, bksge::countl_one((T)0xffffffff00000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(31, bksge::countl_one((T)0xfffffffe00000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(30, bksge::countl_one((T)0xfffffffc00000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(29, bksge::countl_one((T)0xfffffff800000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(28, bksge::countl_one((T)0xfffffff000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(27, bksge::countl_one((T)0xffffffe000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(26, bksge::countl_one((T)0xffffffc000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(25, bksge::countl_one((T)0xffffff8000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(24, bksge::countl_one((T)0xffffff0000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(23, bksge::countl_one((T)0xfffffe0000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(22, bksge::countl_one((T)0xfffffc0000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(21, bksge::countl_one((T)0xfffff80000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(20, bksge::countl_one((T)0xfffff00000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(19, bksge::countl_one((T)0xffffe00000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(18, bksge::countl_one((T)0xffffc00000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(17, bksge::countl_one((T)0xffff800000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(16, bksge::countl_one((T)0xffff000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::countl_one((T)0xfffe000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(14, bksge::countl_one((T)0xfffc000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(13, bksge::countl_one((T)0xfff8000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(12, bksge::countl_one((T)0xfff0000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::countl_one((T)0xffe0000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::countl_one((T)0xffc0000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, bksge::countl_one((T)0xff80000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::countl_one((T)0xff00000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, bksge::countl_one((T)0xfe00000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::countl_one((T)0xfc00000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::countl_one((T)0xf800000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::countl_one((T)0xf000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, bksge::countl_one((T)0xe000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::countl_one((T)0xc000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::countl_one((T)0x8000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countl_one((T)0x0000000000000000));
}

GTEST_TEST(BitTest, CountlOneTest)
{
	CountlOneTestU8<std::uint8_t>();
	CountlOneTestU16<std::uint16_t>();
	CountlOneTestU32<std::uint32_t>();
	CountlOneTestU64<std::uint64_t>();
}

}	// namespace countl_one_test

}	// namespace bksge_bit_test

BKSGE_WARNING_POP();
