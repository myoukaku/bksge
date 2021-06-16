/**
 *	@file	unit_test_fnd_variant_holds_alternative.cpp
 *
 *	@brief	holds_alternative のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/holds_alternative.hpp>
#include <bksge/fnd/variant/variant.hpp>
#include <gtest/gtest.h>
#include "test_macros.hpp"

GTEST_TEST(VariantTest, HoldsAlternativeTest)
{
	{
		using V = bksge::variant<int>;
		constexpr V v;
		static_assert(bksge::holds_alternative<int>(v), "");
	}
	{
		using V = bksge::variant<int, long>;
		constexpr V v;
		static_assert(bksge::holds_alternative<int>(v), "");
		static_assert(!bksge::holds_alternative<long>(v), "");
	}
	{
		// noexcept test
		using V = bksge::variant<int>;
		const V v;
		ASSERT_NOEXCEPT(bksge::holds_alternative<int>(v));
	}
}
