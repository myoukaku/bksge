/**
 *	@file	unit_test_fnd_bit_log2p1.cpp
 *
 *	@brief	log2p1 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bit/log2p1.hpp>
#include <cstdint>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4307);	// 整数定数がオーバーフローしました。

namespace bksge_bit_test
{

namespace log2p1_test
{

template <typename T>
void Log2p1TestU8(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ((T)0, bksge::log2p1((T)0));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)1, bksge::log2p1((T)1));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)2, bksge::log2p1((T)2));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)2, bksge::log2p1((T)3));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)3, bksge::log2p1((T)4));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)3, bksge::log2p1((T)5));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)3, bksge::log2p1((T)6));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)3, bksge::log2p1((T)7));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)4, bksge::log2p1((T)8));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)4, bksge::log2p1((T)15));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)5, bksge::log2p1((T)16));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)5, bksge::log2p1((T)31));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)6, bksge::log2p1((T)32));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)6, bksge::log2p1((T)63));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)7, bksge::log2p1((T)64));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)7, bksge::log2p1((T)127));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)8, bksge::log2p1((T)128));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)8, bksge::log2p1((T)255));
}

template <typename T>
void Log2p1TestU16(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 9, bksge::log2p1((T)0x0100));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 9, bksge::log2p1((T)0x01ff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)10, bksge::log2p1((T)0x0200));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)10, bksge::log2p1((T)0x03ff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)11, bksge::log2p1((T)0x0400));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)11, bksge::log2p1((T)0x07ff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)12, bksge::log2p1((T)0x0800));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)12, bksge::log2p1((T)0x0fff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)13, bksge::log2p1((T)0x1000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)13, bksge::log2p1((T)0x1fff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)14, bksge::log2p1((T)0x2000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)14, bksge::log2p1((T)0x3fff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)15, bksge::log2p1((T)0x4000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)15, bksge::log2p1((T)0x7fff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)16, bksge::log2p1((T)0x8000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)16, bksge::log2p1((T)0xffff));
}

template <typename T>
void Log2p1TestU32(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ((T)17, bksge::log2p1((T)0x00010000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)17, bksge::log2p1((T)0x0001ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)18, bksge::log2p1((T)0x00020000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)18, bksge::log2p1((T)0x0003ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)19, bksge::log2p1((T)0x00040000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)19, bksge::log2p1((T)0x0007ffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)20, bksge::log2p1((T)0x00080000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)20, bksge::log2p1((T)0x000fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)21, bksge::log2p1((T)0x00100000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)21, bksge::log2p1((T)0x001fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)22, bksge::log2p1((T)0x00200000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)22, bksge::log2p1((T)0x003fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)23, bksge::log2p1((T)0x00400000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)23, bksge::log2p1((T)0x007fffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)24, bksge::log2p1((T)0x00800000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)24, bksge::log2p1((T)0x00ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)25, bksge::log2p1((T)0x01000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)25, bksge::log2p1((T)0x01ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)26, bksge::log2p1((T)0x02000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)26, bksge::log2p1((T)0x03ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)27, bksge::log2p1((T)0x04000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)27, bksge::log2p1((T)0x07ffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)28, bksge::log2p1((T)0x08000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)28, bksge::log2p1((T)0x0fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)29, bksge::log2p1((T)0x10000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)29, bksge::log2p1((T)0x1fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)30, bksge::log2p1((T)0x20000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)30, bksge::log2p1((T)0x3fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)31, bksge::log2p1((T)0x40000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)31, bksge::log2p1((T)0x7fffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)32, bksge::log2p1((T)0x80000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)32, bksge::log2p1((T)0xffffffff));
}

template <typename T>
void Log2p1TestU64(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ((T)33, bksge::log2p1((T)0x0000000100000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)33, bksge::log2p1((T)0x00000001ffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)34, bksge::log2p1((T)0x0000000200000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)34, bksge::log2p1((T)0x00000003ffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)35, bksge::log2p1((T)0x0000000400000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)35, bksge::log2p1((T)0x00000007ffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)36, bksge::log2p1((T)0x0000000800000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)36, bksge::log2p1((T)0x0000000fffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)37, bksge::log2p1((T)0x0000001000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)37, bksge::log2p1((T)0x0000001fffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)38, bksge::log2p1((T)0x0000002000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)38, bksge::log2p1((T)0x0000003fffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)39, bksge::log2p1((T)0x0000004000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)39, bksge::log2p1((T)0x0000007fffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)40, bksge::log2p1((T)0x0000008000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)40, bksge::log2p1((T)0x000000ffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)41, bksge::log2p1((T)0x0000010000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)41, bksge::log2p1((T)0x000001ffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)42, bksge::log2p1((T)0x0000020000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)42, bksge::log2p1((T)0x000003ffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)43, bksge::log2p1((T)0x0000040000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)43, bksge::log2p1((T)0x000007ffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)44, bksge::log2p1((T)0x0000080000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)44, bksge::log2p1((T)0x00000fffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)45, bksge::log2p1((T)0x0000100000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)45, bksge::log2p1((T)0x00001fffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)46, bksge::log2p1((T)0x0000200000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)46, bksge::log2p1((T)0x00003fffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)47, bksge::log2p1((T)0x0000400000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)47, bksge::log2p1((T)0x00007fffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)48, bksge::log2p1((T)0x0000800000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)48, bksge::log2p1((T)0x0000ffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)49, bksge::log2p1((T)0x0001000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)49, bksge::log2p1((T)0x0001ffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)50, bksge::log2p1((T)0x0002000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)50, bksge::log2p1((T)0x0003ffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)51, bksge::log2p1((T)0x0004000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)51, bksge::log2p1((T)0x0007ffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)52, bksge::log2p1((T)0x0008000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)52, bksge::log2p1((T)0x000fffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)53, bksge::log2p1((T)0x0010000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)53, bksge::log2p1((T)0x001fffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)54, bksge::log2p1((T)0x0020000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)54, bksge::log2p1((T)0x003fffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)55, bksge::log2p1((T)0x0040000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)55, bksge::log2p1((T)0x007fffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)56, bksge::log2p1((T)0x0080000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)56, bksge::log2p1((T)0x00ffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)57, bksge::log2p1((T)0x0100000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)57, bksge::log2p1((T)0x01ffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)58, bksge::log2p1((T)0x0200000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)58, bksge::log2p1((T)0x03ffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)59, bksge::log2p1((T)0x0400000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)59, bksge::log2p1((T)0x07ffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)60, bksge::log2p1((T)0x0800000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)60, bksge::log2p1((T)0x0fffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)61, bksge::log2p1((T)0x1000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)61, bksge::log2p1((T)0x1fffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)62, bksge::log2p1((T)0x2000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)62, bksge::log2p1((T)0x3fffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)63, bksge::log2p1((T)0x4000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)63, bksge::log2p1((T)0x7fffffffffffffff));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)64, bksge::log2p1((T)0x8000000000000000));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)64, bksge::log2p1((T)0xffffffffffffffff));
}

GTEST_TEST(BitTest, Log2p1Test)
{
	Log2p1TestU8<std::uint8_t>();
	Log2p1TestU8<std::uint16_t>();
	Log2p1TestU8<std::uint32_t>();
	Log2p1TestU8<std::uint64_t>();

	Log2p1TestU16<std::uint16_t>();
	Log2p1TestU16<std::uint32_t>();
	Log2p1TestU16<std::uint64_t>();

	Log2p1TestU32<std::uint32_t>();
	Log2p1TestU32<std::uint64_t>();

	Log2p1TestU64<std::uint64_t>();
}

}	// namespace log2p1_test

}	// namespace bksge_bit_test

BKSGE_WARNING_POP();
