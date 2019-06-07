/**
 *	@file	unit_test_functional_bit_or.cpp
 *
 *	@brief	bit_or のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/functional/bit_or.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include <type_traits>
#include "constexpr_test.hpp"

GTEST_TEST(FunctionalTest, BitOrTest)
{
	{
		using type = bksge::bit_or<int>;
		static_assert(std::is_same<type::result_type,          int>::value, "");
		static_assert(std::is_same<type::first_argument_type,  int>::value, "");
		static_assert(std::is_same<type::second_argument_type, int>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(0x3F, type()(0x0F, 0x35));
		BKSGE_CONSTEXPR_EXPECT_EQ(0xF5, type()(0x35, 0xf0));
	}
	{
		using type = bksge::bit_or<>;
		BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x1F), type()(std::uint8_t (0x0F), std::uint16_t(0x12)));
		BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x77), type()(std::uint32_t(0x77), std::uint16_t(0x20)));
	}
}
