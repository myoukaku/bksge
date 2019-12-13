/**
 *	@file	unit_test_fnd_functional_bit_xor.cpp
 *
 *	@brief	bit_xor のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/bit_xor.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include <type_traits>
#include "constexpr_test.hpp"

GTEST_TEST(FunctionalTest, BitXorTest)
{
	{
		using type = bksge::bit_xor<int>;
		static_assert(std::is_same<type::result_type,          int>::value, "");
		static_assert(std::is_same<type::first_argument_type,  int>::value, "");
		static_assert(std::is_same<type::second_argument_type, int>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(0xBD, type()(0xFA, 0x47));
		BKSGE_CONSTEXPR_EXPECT_EQ(0xC5, type()(0x35, 0xf0));
	}
	{
		using type = bksge::bit_xor<>;
		BKSGE_CONSTEXPR_EXPECT_EQ(std::uint16_t(0xBD), type()(std::uint8_t (0xFA), std::uint16_t(0x47)));
		BKSGE_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x53), type()(std::uint32_t(0x73), std::uint16_t(0x20)));
	}
}
