/**
 *	@file	unit_test_fnd_functional_bit_or.cpp
 *
 *	@brief	bit_or のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/bit_or.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <gtest/gtest.h>
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
		BKSGE_CONSTEXPR_EXPECT_EQ(bksge::uint16_t(0x1F), type()(bksge::uint8_t (0x0F), bksge::uint16_t(0x12)));
		BKSGE_CONSTEXPR_EXPECT_EQ(bksge::uint32_t(0x77), type()(bksge::uint32_t(0x77), bksge::uint16_t(0x20)));
	}
}
