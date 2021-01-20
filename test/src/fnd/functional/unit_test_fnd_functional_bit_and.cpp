/**
 *	@file	unit_test_fnd_functional_bit_and.cpp
 *
 *	@brief	bit_and のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/bit_and.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(FunctionalTest, BitAndTest)
{
	{
		using type = bksge::bit_and<int>;
		//static_assert(bksge::is_same<type::result_type,          int>::value, "");
		//static_assert(bksge::is_same<type::first_argument_type,  int>::value, "");
		//static_assert(bksge::is_same<type::second_argument_type, int>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(0x05, type()(0x0F, 0x35));
		BKSGE_CONSTEXPR_EXPECT_EQ(0x30, type()(0x35, 0xf0));
	}
	{
		using type = bksge::bit_and<>;
		BKSGE_CONSTEXPR_EXPECT_EQ(bksge::uint16_t(0x02), type()(bksge::uint8_t (0x0F), bksge::uint16_t(0x12)));
		BKSGE_CONSTEXPR_EXPECT_EQ(bksge::uint32_t(0x20), type()(bksge::uint32_t(0x77), bksge::uint16_t(0x20)));
	}
}
