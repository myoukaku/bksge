/**
 *	@file	unit_test_fnd_functional_bit_xor.cpp
 *
 *	@brief	bit_xor のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/bit_xor.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(FunctionalTest, BitXorTest)
{
	{
		using type = bksge::bit_xor<int>;
		static_assert(bksge::is_same<type::result_type,          int>::value, "");
		static_assert(bksge::is_same<type::first_argument_type,  int>::value, "");
		static_assert(bksge::is_same<type::second_argument_type, int>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(0xBD, type()(0xFA, 0x47));
		BKSGE_CONSTEXPR_EXPECT_EQ(0xC5, type()(0x35, 0xf0));
	}
	{
		using type = bksge::bit_xor<>;
		BKSGE_CONSTEXPR_EXPECT_EQ(bksge::uint16_t(0xBD), type()(bksge::uint8_t (0xFA), bksge::uint16_t(0x47)));
		BKSGE_CONSTEXPR_EXPECT_EQ(bksge::uint32_t(0x53), type()(bksge::uint32_t(0x73), bksge::uint16_t(0x20)));
	}
}
