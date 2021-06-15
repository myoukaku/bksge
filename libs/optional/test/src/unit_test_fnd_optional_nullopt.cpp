/**
 *	@file	unit_test_fnd_optional_nullopt.cpp
 *
 *	@brief	nullopt のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/optional/nullopt.hpp>
#include <bksge/fnd/optional/optional.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_empty.hpp>
#include <bksge/fnd/type_traits/is_literal_type.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(OptionalTest, NulloptTest)
{
	// [20.5.6] Disengaged state indicator
	static_assert( bksge::is_same<decltype(bksge::nullopt), const bksge::nullopt_t>::value, "");
	static_assert( bksge::is_empty<bksge::nullopt_t>::value, "");
	static_assert( bksge::is_literal_type<bksge::nullopt_t>::value, "");
	static_assert(!bksge::is_default_constructible<bksge::nullopt_t>::value, "");

	{
		BKSGE_CONSTEXPR bksge::optional<int> o = bksge::nullopt;
		BKSGE_CONSTEXPR_EXPECT_TRUE(!o);
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
