/**
 *	@file	unit_test_fnd_functional_bit_and.cpp
 *
 *	@brief	bit_and のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/bit_and.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include <type_traits>
#include "constexpr_test.hpp"

GTEST_TEST(FunctionalTest, BitAndTest)
{
	{
		using type = bksge::bit_and<int>;
		static_assert(std::is_same<type::result_type,          int>::value, "");
		static_assert(std::is_same<type::first_argument_type,  int>::value, "");
		static_assert(std::is_same<type::second_argument_type, int>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(0x05, type()(0x0F, 0x35));
		BKSGE_CONSTEXPR_EXPECT_EQ(0x30, type()(0x35, 0xf0));
	}
	{
		using type = bksge::bit_and<>;
		BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x02), type()(std::uint8_t (0x0F), std::uint16_t(0x12)));
		BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x20), type()(std::uint32_t(0x77), std::uint16_t(0x20)));
	}
}
