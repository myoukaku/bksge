/**
 *	@file	unit_test_fnd_variant_ctor_in_place_index_args.cpp
 *
 *	@brief	variant::variant(in_place_index_t<I>, Args&&...) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <gtest/gtest.h>
#include "fnd/variant/test_convertible.hpp"
#include "fnd/variant/test_macros.hpp"

namespace bksge_variant_test
{

namespace ctor_in_place_index_args_test
{

void test_ctor_sfinae()
{
	{
		using V = bksge::variant<int>;
		static_assert(bksge::is_constructible<V, bksge::in_place_index_t<0>, int>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_index_t<0>, int>(), "");
	}
	{
		using V = bksge::variant<int, long, long long>;
		static_assert(bksge::is_constructible<V, bksge::in_place_index_t<1>, int>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_index_t<1>, int>(), "");
	}
	{
		using V = bksge::variant<int, long, int*>;
		static_assert(bksge::is_constructible<V, bksge::in_place_index_t<2>, int*>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_index_t<2>, int*>(), "");
	}
	{
		// args not convertible to type
		using V = bksge::variant<int, long, int*>;
		static_assert(!bksge::is_constructible<V, bksge::in_place_index_t<0>, int*>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_index_t<0>, int*>(), "");
	}
	{
		// index not in variant
		using V = bksge::variant<int, long, int*>;
		static_assert(!bksge::is_constructible<V, bksge::in_place_index_t<3>, int>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_index_t<3>, int>(), "");
	}
}

void test_ctor_basic()
{
	{
		constexpr bksge::variant<int> v(bksge::in_place_index_t<0>{}, 42);
		static_assert(v.index() == 0, "");
		static_assert(bksge::get<0>(v) == 42, "");
	}
	{
		constexpr bksge::variant<int, long, long> v(bksge::in_place_index_t<1>{}, 42);
		static_assert(v.index() == 1, "");
		static_assert(bksge::get<1>(v) == 42, "");
	}
	{
		constexpr bksge::variant<int, const int, long> v(bksge::in_place_index_t<1>{}, 42);
		static_assert(v.index() == 1, "");
		static_assert(bksge::get<1>(v) == 42, "");
	}
	{
		using V = bksge::variant<const int, volatile int, int>;
		int x = 42;
		V v(bksge::in_place_index_t<0>{}, x);
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(bksge::get<0>(v), x);
	}
	{
		using V = bksge::variant<const int, volatile int, int>;
		int x = 42;
		V v(bksge::in_place_index_t<1>{}, x);
		EXPECT_EQ(v.index(), 1u);
		EXPECT_EQ(bksge::get<1>(v), x);
	}
	{
		using V = bksge::variant<const int, volatile int, int>;
		int x = 42;
		V v(bksge::in_place_index_t<2>{}, x);
		EXPECT_EQ(v.index(), 2u);
		EXPECT_EQ(bksge::get<2>(v), x);
	}
}

GTEST_TEST(VariantTest, CtorInPlaceIndexArgsTest)
{
	test_ctor_basic();
	test_ctor_sfinae();
}

}	// namespace ctor_in_place_index_args_test

}	// namespace bksge_variant_test
