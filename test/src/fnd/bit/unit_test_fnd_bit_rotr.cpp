﻿/**
 *	@file	unit_test_fnd_bit_rotr.cpp
 *
 *	@brief	rotr のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bit/rotr.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include "constexpr_test.hpp"

GTEST_TEST(BitTest, RotrTest)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint8_t(0x01), bksge::rotr(std::uint8_t(0x01),  0));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint8_t(0x80), bksge::rotr(std::uint8_t(0x01),  1));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint8_t(0x40), bksge::rotr(std::uint8_t(0x01),  2));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint8_t(0x20), bksge::rotr(std::uint8_t(0x01),  3));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint8_t(0x10), bksge::rotr(std::uint8_t(0x01),  4));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint8_t(0x08), bksge::rotr(std::uint8_t(0x01),  5));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint8_t(0x04), bksge::rotr(std::uint8_t(0x01),  6));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint8_t(0x02), bksge::rotr(std::uint8_t(0x01),  7));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint8_t(0x01), bksge::rotr(std::uint8_t(0x01),  8));

	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x0001), bksge::rotr(std::uint16_t(0x0001),  0));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x8000), bksge::rotr(std::uint16_t(0x0001),  1));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x4000), bksge::rotr(std::uint16_t(0x0001),  2));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x2000), bksge::rotr(std::uint16_t(0x0001),  3));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x1000), bksge::rotr(std::uint16_t(0x0001),  4));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x0800), bksge::rotr(std::uint16_t(0x0001),  5));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x0400), bksge::rotr(std::uint16_t(0x0001),  6));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x0200), bksge::rotr(std::uint16_t(0x0001),  7));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x0100), bksge::rotr(std::uint16_t(0x0001),  8));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x0080), bksge::rotr(std::uint16_t(0x0001),  9));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x0040), bksge::rotr(std::uint16_t(0x0001), 10));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x0020), bksge::rotr(std::uint16_t(0x0001), 11));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x0010), bksge::rotr(std::uint16_t(0x0001), 12));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x0008), bksge::rotr(std::uint16_t(0x0001), 13));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x0004), bksge::rotr(std::uint16_t(0x0001), 14));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x0002), bksge::rotr(std::uint16_t(0x0001), 15));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x0001), bksge::rotr(std::uint16_t(0x0001), 16));

	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x1234), bksge::rotr(std::uint16_t(0x1234),  0));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x091A), bksge::rotr(std::uint16_t(0x1234),  1));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x048D), bksge::rotr(std::uint16_t(0x1234),  2));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x8246), bksge::rotr(std::uint16_t(0x1234),  3));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x4123), bksge::rotr(std::uint16_t(0x1234),  4));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0xA091), bksge::rotr(std::uint16_t(0x1234),  5));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0xD048), bksge::rotr(std::uint16_t(0x1234),  6));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x6824), bksge::rotr(std::uint16_t(0x1234),  7));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x3412), bksge::rotr(std::uint16_t(0x1234),  8));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x1A09), bksge::rotr(std::uint16_t(0x1234),  9));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x8D04), bksge::rotr(std::uint16_t(0x1234), 10));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x4682), bksge::rotr(std::uint16_t(0x1234), 11));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x2341), bksge::rotr(std::uint16_t(0x1234), 12));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x91A0), bksge::rotr(std::uint16_t(0x1234), 13));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x48D0), bksge::rotr(std::uint16_t(0x1234), 14));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x2468), bksge::rotr(std::uint16_t(0x1234), 15));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x1234), bksge::rotr(std::uint16_t(0x1234), 16));

	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00000001), bksge::rotr(std::uint32_t(0x00000001),  0));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x80000000), bksge::rotr(std::uint32_t(0x00000001),  1));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x40000000), bksge::rotr(std::uint32_t(0x00000001),  2));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x20000000), bksge::rotr(std::uint32_t(0x00000001),  3));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x10000000), bksge::rotr(std::uint32_t(0x00000001),  4));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x08000000), bksge::rotr(std::uint32_t(0x00000001),  5));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x04000000), bksge::rotr(std::uint32_t(0x00000001),  6));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x02000000), bksge::rotr(std::uint32_t(0x00000001),  7));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x01000000), bksge::rotr(std::uint32_t(0x00000001),  8));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00800000), bksge::rotr(std::uint32_t(0x00000001),  9));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00400000), bksge::rotr(std::uint32_t(0x00000001), 10));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00200000), bksge::rotr(std::uint32_t(0x00000001), 11));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00100000), bksge::rotr(std::uint32_t(0x00000001), 12));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00080000), bksge::rotr(std::uint32_t(0x00000001), 13));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00040000), bksge::rotr(std::uint32_t(0x00000001), 14));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00020000), bksge::rotr(std::uint32_t(0x00000001), 15));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00010000), bksge::rotr(std::uint32_t(0x00000001), 16));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00008000), bksge::rotr(std::uint32_t(0x00000001), 17));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00004000), bksge::rotr(std::uint32_t(0x00000001), 18));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00002000), bksge::rotr(std::uint32_t(0x00000001), 19));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00001000), bksge::rotr(std::uint32_t(0x00000001), 20));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00000800), bksge::rotr(std::uint32_t(0x00000001), 21));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00000400), bksge::rotr(std::uint32_t(0x00000001), 22));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00000200), bksge::rotr(std::uint32_t(0x00000001), 23));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00000100), bksge::rotr(std::uint32_t(0x00000001), 24));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00000080), bksge::rotr(std::uint32_t(0x00000001), 25));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00000040), bksge::rotr(std::uint32_t(0x00000001), 26));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00000020), bksge::rotr(std::uint32_t(0x00000001), 27));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00000010), bksge::rotr(std::uint32_t(0x00000001), 28));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00000008), bksge::rotr(std::uint32_t(0x00000001), 29));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00000004), bksge::rotr(std::uint32_t(0x00000001), 30));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00000002), bksge::rotr(std::uint32_t(0x00000001), 31));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x00000001), bksge::rotr(std::uint32_t(0x00000001), 32));

	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x12345678), bksge::rotr(std::uint32_t(0x12345678),  0));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x091A2B3C), bksge::rotr(std::uint32_t(0x12345678),  1));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x048D159E), bksge::rotr(std::uint32_t(0x12345678),  2));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x02468ACF), bksge::rotr(std::uint32_t(0x12345678),  3));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x81234567), bksge::rotr(std::uint32_t(0x12345678),  4));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0xC091A2B3), bksge::rotr(std::uint32_t(0x12345678),  5));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0xE048D159), bksge::rotr(std::uint32_t(0x12345678),  6));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0xF02468AC), bksge::rotr(std::uint32_t(0x12345678),  7));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x78123456), bksge::rotr(std::uint32_t(0x12345678),  8));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x3C091A2B), bksge::rotr(std::uint32_t(0x12345678),  9));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x9E048D15), bksge::rotr(std::uint32_t(0x12345678), 10));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0xCF02468A), bksge::rotr(std::uint32_t(0x12345678), 11));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x67812345), bksge::rotr(std::uint32_t(0x12345678), 12));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0xB3C091A2), bksge::rotr(std::uint32_t(0x12345678), 13));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x59E048D1), bksge::rotr(std::uint32_t(0x12345678), 14));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0xACF02468), bksge::rotr(std::uint32_t(0x12345678), 15));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x56781234), bksge::rotr(std::uint32_t(0x12345678), 16));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x2B3C091A), bksge::rotr(std::uint32_t(0x12345678), 17));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x159E048D), bksge::rotr(std::uint32_t(0x12345678), 18));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x8ACF0246), bksge::rotr(std::uint32_t(0x12345678), 19));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x45678123), bksge::rotr(std::uint32_t(0x12345678), 20));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0xA2B3C091), bksge::rotr(std::uint32_t(0x12345678), 21));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0xD159E048), bksge::rotr(std::uint32_t(0x12345678), 22));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x68ACF024), bksge::rotr(std::uint32_t(0x12345678), 23));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x34567812), bksge::rotr(std::uint32_t(0x12345678), 24));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x1A2B3C09), bksge::rotr(std::uint32_t(0x12345678), 25));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x8D159E04), bksge::rotr(std::uint32_t(0x12345678), 26));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x468ACF02), bksge::rotr(std::uint32_t(0x12345678), 27));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x23456781), bksge::rotr(std::uint32_t(0x12345678), 28));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x91A2B3C0), bksge::rotr(std::uint32_t(0x12345678), 29));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x48D159E0), bksge::rotr(std::uint32_t(0x12345678), 30));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x2468ACF0), bksge::rotr(std::uint32_t(0x12345678), 31));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x12345678), bksge::rotr(std::uint32_t(0x12345678), 32));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x12345678), bksge::rotr(std::uint32_t(0x12345678), 64));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x12345678), bksge::rotr(std::uint32_t(0x12345678), 96));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x091A2B3C), bksge::rotr(std::uint32_t(0x12345678), 33));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x091A2B3C), bksge::rotr(std::uint32_t(0x12345678), 65));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x091A2B3C), bksge::rotr(std::uint32_t(0x12345678), 97));

	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000000001), bksge::rotr(std::uint64_t(0x0000000000000001),  0));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x8000000000000000), bksge::rotr(std::uint64_t(0x0000000000000001),  1));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x4000000000000000), bksge::rotr(std::uint64_t(0x0000000000000001),  2));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x2000000000000000), bksge::rotr(std::uint64_t(0x0000000000000001),  3));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x1000000000000000), bksge::rotr(std::uint64_t(0x0000000000000001),  4));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0800000000000000), bksge::rotr(std::uint64_t(0x0000000000000001),  5));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0400000000000000), bksge::rotr(std::uint64_t(0x0000000000000001),  6));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0200000000000000), bksge::rotr(std::uint64_t(0x0000000000000001),  7));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0100000000000000), bksge::rotr(std::uint64_t(0x0000000000000001),  8));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0080000000000000), bksge::rotr(std::uint64_t(0x0000000000000001),  9));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0040000000000000), bksge::rotr(std::uint64_t(0x0000000000000001), 10));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0020000000000000), bksge::rotr(std::uint64_t(0x0000000000000001), 11));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0010000000000000), bksge::rotr(std::uint64_t(0x0000000000000001), 12));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0008000000000000), bksge::rotr(std::uint64_t(0x0000000000000001), 13));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0004000000000000), bksge::rotr(std::uint64_t(0x0000000000000001), 14));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0002000000000000), bksge::rotr(std::uint64_t(0x0000000000000001), 15));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0001000000000000), bksge::rotr(std::uint64_t(0x0000000000000001), 16));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000800000000000), bksge::rotr(std::uint64_t(0x0000000000000001), 17));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000400000000000), bksge::rotr(std::uint64_t(0x0000000000000001), 18));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000200000000000), bksge::rotr(std::uint64_t(0x0000000000000001), 19));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000100000000000), bksge::rotr(std::uint64_t(0x0000000000000001), 20));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000080000000000), bksge::rotr(std::uint64_t(0x0000000000000001), 21));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000040000000000), bksge::rotr(std::uint64_t(0x0000000000000001), 22));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000020000000000), bksge::rotr(std::uint64_t(0x0000000000000001), 23));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000010000000000), bksge::rotr(std::uint64_t(0x0000000000000001), 24));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000008000000000), bksge::rotr(std::uint64_t(0x0000000000000001), 25));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000004000000000), bksge::rotr(std::uint64_t(0x0000000000000001), 26));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000002000000000), bksge::rotr(std::uint64_t(0x0000000000000001), 27));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000001000000000), bksge::rotr(std::uint64_t(0x0000000000000001), 28));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000800000000), bksge::rotr(std::uint64_t(0x0000000000000001), 29));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000400000000), bksge::rotr(std::uint64_t(0x0000000000000001), 30));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000200000000), bksge::rotr(std::uint64_t(0x0000000000000001), 31));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000100000000), bksge::rotr(std::uint64_t(0x0000000000000001), 32));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000080000000), bksge::rotr(std::uint64_t(0x0000000000000001), 33));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000040000000), bksge::rotr(std::uint64_t(0x0000000000000001), 34));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000020000000), bksge::rotr(std::uint64_t(0x0000000000000001), 35));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000010000000), bksge::rotr(std::uint64_t(0x0000000000000001), 36));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000008000000), bksge::rotr(std::uint64_t(0x0000000000000001), 37));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000004000000), bksge::rotr(std::uint64_t(0x0000000000000001), 38));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000002000000), bksge::rotr(std::uint64_t(0x0000000000000001), 39));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000001000000), bksge::rotr(std::uint64_t(0x0000000000000001), 40));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000800000), bksge::rotr(std::uint64_t(0x0000000000000001), 41));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000400000), bksge::rotr(std::uint64_t(0x0000000000000001), 42));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000200000), bksge::rotr(std::uint64_t(0x0000000000000001), 43));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000100000), bksge::rotr(std::uint64_t(0x0000000000000001), 44));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000080000), bksge::rotr(std::uint64_t(0x0000000000000001), 45));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000040000), bksge::rotr(std::uint64_t(0x0000000000000001), 46));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000020000), bksge::rotr(std::uint64_t(0x0000000000000001), 47));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000010000), bksge::rotr(std::uint64_t(0x0000000000000001), 48));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000008000), bksge::rotr(std::uint64_t(0x0000000000000001), 49));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000004000), bksge::rotr(std::uint64_t(0x0000000000000001), 50));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000002000), bksge::rotr(std::uint64_t(0x0000000000000001), 51));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000001000), bksge::rotr(std::uint64_t(0x0000000000000001), 52));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000000800), bksge::rotr(std::uint64_t(0x0000000000000001), 53));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000000400), bksge::rotr(std::uint64_t(0x0000000000000001), 54));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000000200), bksge::rotr(std::uint64_t(0x0000000000000001), 55));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000000100), bksge::rotr(std::uint64_t(0x0000000000000001), 56));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000000080), bksge::rotr(std::uint64_t(0x0000000000000001), 57));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000000040), bksge::rotr(std::uint64_t(0x0000000000000001), 58));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000000020), bksge::rotr(std::uint64_t(0x0000000000000001), 59));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000000010), bksge::rotr(std::uint64_t(0x0000000000000001), 60));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000000008), bksge::rotr(std::uint64_t(0x0000000000000001), 61));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000000004), bksge::rotr(std::uint64_t(0x0000000000000001), 62));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000000002), bksge::rotr(std::uint64_t(0x0000000000000001), 63));
	BKSGE_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x0000000000000001), bksge::rotr(std::uint64_t(0x0000000000000001), 64));
}