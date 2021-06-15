/**
 *	@file	unit_test_fnd_bit_endian.cpp
 *
 *	@brief	endian のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bit/endian.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/is_enum.hpp>
#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <bksge/fnd/cstring/memcpy.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <gtest/gtest.h>

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4127);	// conditional expression is constant

GTEST_TEST(BitTest, EndianTest)
{
	static_assert(bksge::is_enum<bksge::endian>::value, "");

	using UT = bksge::underlying_type_t<bksge::endian>;
	static_assert(!bksge::is_convertible<bksge::endian, UT>::value, "");

	// test that the enumeration values exist
	static_assert(bksge::endian::little == bksge::endian::little, "");
	static_assert(bksge::endian::big    == bksge::endian::big, "");
	static_assert(bksge::endian::native == bksge::endian::native, "");
	static_assert(bksge::endian::little != bksge::endian::big, "");

	//  Technically not required, but true on all existing machines
	static_assert(
		bksge::endian::native == bksge::endian::little ||
		bksge::endian::native == bksge::endian::big, "");

	//  Try to check at runtime
	{
		bksge::uint32_t i = 0x01020304;
		bksge::uint8_t c[4];
		bksge::memcpy(c, &i, sizeof(c));

		if (bksge::endian::native == bksge::endian::big)
		{
			EXPECT_EQ(1, c[0]);
			EXPECT_EQ(2, c[1]);
			EXPECT_EQ(3, c[2]);
			EXPECT_EQ(4, c[3]);
		}
		else
		{
			EXPECT_EQ(4, c[0]);
			EXPECT_EQ(3, c[1]);
			EXPECT_EQ(2, c[2]);
			EXPECT_EQ(1, c[3]);
		}
	}
}

BKSGE_WARNING_POP();
