/**
 *	@file	unit_test_functional_bit_not.cpp
 *
 *	@brief	bit_not のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/functional/bit_not.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include <type_traits>
#include "constexpr_test.hpp"

GTEST_TEST(FunctionalTest, BitNotTest)
{
	{
		using type = bksge::bit_not<std::uint8_t>;
		static_assert(std::is_same<type::result_type,   std::uint8_t>::value, "");
		static_assert(std::is_same<type::argument_type, std::uint8_t>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(0x05, type()(0xFA));
	}
	{
		using type = bksge::bit_not<std::uint16_t>;
		static_assert(std::is_same<type::result_type,   std::uint16_t>::value, "");
		static_assert(std::is_same<type::argument_type, std::uint16_t>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(0xFF05, type()(0xFA));
	}
	{
		using type = bksge::bit_not<>;
		BKSGE_CONSTEXPR_EXPECT_EQ(0xF0, static_cast<std::uint8_t>(type()(static_cast<std::uint8_t>(0x0F))));
		BKSGE_CONSTEXPR_EXPECT_EQ(0xFFFFFF88, type()(static_cast<std::uint32_t>(0x77)));
	}
}
