/**
 *	@file	unit_test_fnd_variant_index.cpp
 *
 *	@brief	variant::index() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/variant_npos.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "fnd/variant/archetypes.hpp"
#include "fnd/variant/test_macros.hpp"
#include "fnd/variant/variant_test_helpers.hpp"

namespace bksge_variant_test
{

namespace index_test
{

GTEST_TEST(VariantTest, IndexTest)
{
	{
		using V = bksge::variant<int, long>;
		constexpr V v;
		static_assert(v.index() == 0, "");
	}
	{
		using V = bksge::variant<int, long>;
		V v;
		EXPECT_EQ(v.index(), 0u);
	}
	{
		using V = bksge::variant<int, long>;
		constexpr V v(bksge::in_place_index_t<1>{});
		static_assert(v.index() == 1, "");
	}
	{
		using V = bksge::variant<int, bksge::string>;
		V v("abc");
		EXPECT_EQ(v.index(), 1u);
		v = 42;
		EXPECT_EQ(v.index(), 0u);
	}
#if !defined(BKSGE_NO_EXCEPTIONS)
	{
		using V = bksge::variant<int, MakeEmptyT>;
		V v;
		EXPECT_EQ(v.index(), 0u);
		makeEmpty(v);
		EXPECT_EQ(v.index(), bksge::variant_npos);
	}
#endif
}

}	// namespace index_test

}	// namespace bksge_variant_test
