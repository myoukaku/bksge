/**
 *	@file	unit_test_fnd_type_traits_endian.cpp
 *
 *	@brief	endian のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/endian.hpp>
#include <bksge/fnd/type_traits/is_enum.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <bksge/fnd/cstring/memcpy.hpp>
#include <cstdint>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4127)

GTEST_TEST(TypeTraitsTest, EndianTest)
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
		std::uint32_t i = 0x01020304;
		std::uint8_t c[4];
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

BKSGE_WARNING_POP()
