/**
 *	@file	unit_test_fnd_optional_nullopt.cpp
 *
 *	@brief	nullopt のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/optional/nullopt.hpp>
#include <bksge/fnd/optional/optional.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "constexpr_test.hpp"

GTEST_TEST(OptionalTest, NulloptTest)
{
	// [20.5.6] Disengaged state indicator
	static_assert( std::is_same<decltype(bksge::nullopt), const bksge::nullopt_t>::value, "");
	static_assert( std::is_empty<bksge::nullopt_t>::value, "");
	static_assert( std::is_literal_type<bksge::nullopt_t>::value, "");
	static_assert(!std::is_default_constructible<bksge::nullopt_t>::value, "");

	{
		// TODO constexprにする
		bksge::optional<int> o = bksge::nullopt;
		EXPECT_TRUE(!o);
	}

	{
		BKSGE_CONSTEXPR bksge::optional<int> o = { bksge::nullopt };
		BKSGE_CONSTEXPR_EXPECT_TRUE(!o);
	}

	{
		BKSGE_CONSTEXPR bksge::optional<int> o{ bksge::nullopt };
		BKSGE_CONSTEXPR_EXPECT_TRUE(!o);
	}
}
