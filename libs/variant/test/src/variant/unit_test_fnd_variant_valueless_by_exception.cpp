/**
 *	@file	unit_test_fnd_variant_valueless_by_exception.cpp
 *
 *	@brief	variant::valueless_by_exception() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "archetypes.hpp"
#include "test_macros.hpp"
#include "variant_test_helpers.hpp"

namespace bksge_variant_test
{

namespace valueless_by_exception_test
{

GTEST_TEST(VariantTest, ValuelessByExceptionTest)
{
	{
		using V = bksge::variant<int, long>;
		constexpr V v;
		static_assert(!v.valueless_by_exception(), "");
	}
	{
		using V = bksge::variant<int, long>;
		V v;
		EXPECT_FALSE(v.valueless_by_exception());
	}
	{
		using V = bksge::variant<int, long, bksge::string>;
		const V v("abc");
		EXPECT_FALSE(v.valueless_by_exception());
	}
#if !defined(BKSGE_NO_EXCEPTIONS)
	{
		using V = bksge::variant<int, MakeEmptyT>;
		V v;
		EXPECT_FALSE(v.valueless_by_exception());
		makeEmpty(v);
		EXPECT_TRUE(v.valueless_by_exception());
	}
#endif
}

}	// namespace valueless_by_exception_test

}	// namespace bksge_variant_test
