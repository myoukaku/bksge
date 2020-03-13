/**
 *	@file	unit_test_fnd_bit_countr_one.cpp
 *
 *	@brief	countr_one のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bit/countr_one.hpp>
#include <cstdint>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4307);	// 整数定数がオーバーフローしました。

namespace bksge_bit_test
{

namespace countr_one_test
{

template <typename T>
void CountrOneTestU8(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(8, bksge::countr_one((T)0xff));
	BKSGE_CONSTEXPR_EXPECT_EQ(7, bksge::countr_one((T)0x7f));
	BKSGE_CONSTEXPR_EXPECT_EQ(6, bksge::countr_one((T)0x3f));
	BKSGE_CONSTEXPR_EXPECT_EQ(5, bksge::countr_one((T)0x1f));
	BKSGE_CONSTEXPR_EXPECT_EQ(4, bksge::countr_one((T)0x0f));
	BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::countr_one((T)0x07));
	BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::countr_one((T)0x03));
	BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::countr_one((T)0x01));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::countr_one((T)0x00));

	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::countr_one((T)0x02));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::countr_one((T)0x04));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::countr_one((T)0x08));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::countr_one((T)0x10));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::countr_one((T)0x20));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::countr_one((T)0x40));
	BKSGE_CONSTEXPR_EXPECT_EQ(0, bksge::countr_one((T)0x80));

	BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::countr_one((T)0xf7));
	BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::countr_one((T)0xe7));
	BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::countr_one((T)0xc7));
	BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::countr_one((T)0x87));

	BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::countr_one((T)0xf3));
	BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::countr_one((T)0xe3));
	BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::countr_one((T)0xc3));
	BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::countr_one((T)0x83));
}

template <typename T>
void CountrOneTestU16(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(16, bksge::countr_one((T)0xffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::countr_one((T)0x7fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(14, bksge::countr_one((T)0x3fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(13, bksge::countr_one((T)0x1fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(12, bksge::countr_one((T)0x0fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::countr_one((T)0x07ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::countr_one((T)0x03ff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, bksge::countr_one((T)0x01ff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::countr_one((T)0x00ff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, bksge::countr_one((T)0x007f));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::countr_one((T)0x003f));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::countr_one((T)0x001f));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::countr_one((T)0x000f));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, bksge::countr_one((T)0x0007));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::countr_one((T)0x0003));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::countr_one((T)0x0001));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countr_one((T)0x0000));

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countr_one((T)0x0002));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countr_one((T)0x0004));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countr_one((T)0x0008));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countr_one((T)0x0010));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countr_one((T)0x0020));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countr_one((T)0x0040));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countr_one((T)0x0080));

	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::countr_one((T)0xf03f));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::countr_one((T)0xe03f));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::countr_one((T)0xc03f));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::countr_one((T)0x803f));

	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::countr_one((T)0xf7ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::countr_one((T)0xe7ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::countr_one((T)0xc7ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::countr_one((T)0x87ff));
}

template <typename T>
void CountrOneTestU32(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(32, bksge::countr_one((T)0xffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(31, bksge::countr_one((T)0x7fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(30, bksge::countr_one((T)0x3fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(29, bksge::countr_one((T)0x1fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(28, bksge::countr_one((T)0x0fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(27, bksge::countr_one((T)0x07ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(26, bksge::countr_one((T)0x03ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(25, bksge::countr_one((T)0x01ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(24, bksge::countr_one((T)0x00ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(23, bksge::countr_one((T)0x007fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(22, bksge::countr_one((T)0x003fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(21, bksge::countr_one((T)0x001fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(20, bksge::countr_one((T)0x000fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(19, bksge::countr_one((T)0x0007ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(18, bksge::countr_one((T)0x0003ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(17, bksge::countr_one((T)0x0001ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(16, bksge::countr_one((T)0x0000ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::countr_one((T)0x00007fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(14, bksge::countr_one((T)0x00003fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(13, bksge::countr_one((T)0x00001fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(12, bksge::countr_one((T)0x00000fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::countr_one((T)0x000007ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::countr_one((T)0x000003ff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, bksge::countr_one((T)0x000001ff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::countr_one((T)0x000000ff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, bksge::countr_one((T)0x0000007f));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::countr_one((T)0x0000003f));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::countr_one((T)0x0000001f));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::countr_one((T)0x0000000f));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, bksge::countr_one((T)0x00000007));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::countr_one((T)0x00000003));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::countr_one((T)0x00000001));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countr_one((T)0x00000000));

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countr_one((T)0x00000010));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countr_one((T)0x00000100));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countr_one((T)0x00001000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countr_one((T)0x00010000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countr_one((T)0x00100000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countr_one((T)0x01000000));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countr_one((T)0x10000000));

	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::countr_one((T)0xf000001f));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::countr_one((T)0xff00001f));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::countr_one((T)0xfff0001f));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::countr_one((T)0xffff001f));

	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::countr_one((T)0xffff7fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::countr_one((T)0xfffe7fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::countr_one((T)0xfffc7fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::countr_one((T)0xfff87fff));
}

template <typename T>
void CountrOneTestU64(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(64, bksge::countr_one((T)0xffffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(63, bksge::countr_one((T)0x7fffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(62, bksge::countr_one((T)0x3fffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(61, bksge::countr_one((T)0x1fffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(60, bksge::countr_one((T)0x0fffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(59, bksge::countr_one((T)0x07ffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(58, bksge::countr_one((T)0x03ffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(57, bksge::countr_one((T)0x01ffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(56, bksge::countr_one((T)0x00ffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(55, bksge::countr_one((T)0x007fffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(54, bksge::countr_one((T)0x003fffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(53, bksge::countr_one((T)0x001fffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(52, bksge::countr_one((T)0x000fffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(51, bksge::countr_one((T)0x0007ffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(50, bksge::countr_one((T)0x0003ffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(49, bksge::countr_one((T)0x0001ffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(48, bksge::countr_one((T)0x0000ffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(47, bksge::countr_one((T)0x00007fffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(46, bksge::countr_one((T)0x00003fffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(45, bksge::countr_one((T)0x00001fffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(44, bksge::countr_one((T)0x00000fffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(43, bksge::countr_one((T)0x000007ffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(42, bksge::countr_one((T)0x000003ffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(41, bksge::countr_one((T)0x000001ffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(40, bksge::countr_one((T)0x000000ffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(39, bksge::countr_one((T)0x0000007fffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(38, bksge::countr_one((T)0x0000003fffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(37, bksge::countr_one((T)0x0000001fffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(36, bksge::countr_one((T)0x0000000fffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(35, bksge::countr_one((T)0x00000007ffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(34, bksge::countr_one((T)0x00000003ffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(33, bksge::countr_one((T)0x00000001ffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(32, bksge::countr_one((T)0x00000000ffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(31, bksge::countr_one((T)0x000000007fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(30, bksge::countr_one((T)0x000000003fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(29, bksge::countr_one((T)0x000000001fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(28, bksge::countr_one((T)0x000000000fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(27, bksge::countr_one((T)0x0000000007ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(26, bksge::countr_one((T)0x0000000003ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(25, bksge::countr_one((T)0x0000000001ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(24, bksge::countr_one((T)0x0000000000ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(23, bksge::countr_one((T)0x00000000007fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(22, bksge::countr_one((T)0x00000000003fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(21, bksge::countr_one((T)0x00000000001fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(20, bksge::countr_one((T)0x00000000000fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(19, bksge::countr_one((T)0x000000000007ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(18, bksge::countr_one((T)0x000000000003ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(17, bksge::countr_one((T)0x000000000001ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(16, bksge::countr_one((T)0x000000000000ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ(15, bksge::countr_one((T)0x0000000000007fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(14, bksge::countr_one((T)0x0000000000003fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(13, bksge::countr_one((T)0x0000000000001fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(12, bksge::countr_one((T)0x0000000000000fff));
	BKSGE_CONSTEXPR_EXPECT_EQ(11, bksge::countr_one((T)0x00000000000007ff));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, bksge::countr_one((T)0x00000000000003ff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, bksge::countr_one((T)0x00000000000001ff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, bksge::countr_one((T)0x00000000000000ff));
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, bksge::countr_one((T)0x000000000000007f));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, bksge::countr_one((T)0x000000000000003f));
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, bksge::countr_one((T)0x000000000000001f));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, bksge::countr_one((T)0x000000000000000f));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, bksge::countr_one((T)0x0000000000000007));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, bksge::countr_one((T)0x0000000000000003));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, bksge::countr_one((T)0x0000000000000001));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, bksge::countr_one((T)0x0000000000000000));
}

GTEST_TEST(BitTest, CountrOneTest)
{
	CountrOneTestU8<std::uint8_t>();
	CountrOneTestU16<std::uint16_t>();
	CountrOneTestU32<std::uint32_t>();
	CountrOneTestU64<std::uint64_t>();
}

}	// namespace countr_one_test

}	// namespace bksge_bit_test

BKSGE_WARNING_POP();
