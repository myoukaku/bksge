/**
 *	@file	unit_test_fnd_variant_ctor_in_place_type_args.cpp
 *
 *	@brief	variant::variant(in_place_type_t<Tp>, Args&&...) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/utility/in_place_type.hpp>
#include <gtest/gtest.h>
#include "fnd/variant/test_convertible.hpp"
#include "fnd/variant/test_macros.hpp"

namespace bksge_variant_test
{

namespace ctor_in_place_type_args_test
{

void test_ctor_sfinae()
{
	{
		using V = bksge::variant<int>;
		static_assert(bksge::is_constructible<V, bksge::in_place_type_t<int>, int>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_type_t<int>, int>(), "");
	}
	{
		using V = bksge::variant<int, long, long long>;
		static_assert(bksge::is_constructible<V, bksge::in_place_type_t<long>, int>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_type_t<long>, int>(), "");
	}
	{
		using V = bksge::variant<int, long, int*>;
		static_assert(bksge::is_constructible<V, bksge::in_place_type_t<int*>, int*>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_type_t<int*>, int*>(), "");
	}
	{
		// duplicate type
		using V = bksge::variant<int, long, int>;
		static_assert(!bksge::is_constructible<V, bksge::in_place_type_t<int>, int>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_type_t<int>, int>(), "");
	}
	{
		// args not convertible to type
		using V = bksge::variant<int, long, int*>;
		static_assert(!bksge::is_constructible<V, bksge::in_place_type_t<int>, int*>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_type_t<int>, int*>(), "");
	}
	{
		// type not in variant
		using V = bksge::variant<int, long, int*>;
		static_assert(!bksge::is_constructible<V, bksge::in_place_type_t<long long>, int>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_type_t<long long>, int>(), "");
	}
}

void test_ctor_basic()
{
	using std::get;
	{
		constexpr bksge::variant<int> v(bksge::in_place_type_t<int>{}, 42);
		static_assert(v.index() == 0, "");
		static_assert(get<0>(v) == 42, "");
	}
	{
		constexpr bksge::variant<int, long> v(bksge::in_place_type_t<long>{}, 42);
		static_assert(v.index() == 1, "");
		static_assert(get<1>(v) == 42, "");
	}
	{
		constexpr bksge::variant<int, const int, long> v(
			bksge::in_place_type_t<const int>{}, 42);
		static_assert(v.index() == 1, "");
		static_assert(get<1>(v) == 42, "");
	}
	{
		using V = bksge::variant<const int, volatile int, int>;
		int x = 42;
		V v(bksge::in_place_type_t<const int>{}, x);
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(get<0>(v), x);
	}
	{
		using V = bksge::variant<const int, volatile int, int>;
		int x = 42;
		V v(bksge::in_place_type_t<volatile int>{}, x);
		EXPECT_EQ(v.index(), 1u);
		EXPECT_EQ(get<1>(v), x);
	}
	{
		using V = bksge::variant<const int, volatile int, int>;
		int x = 42;
		V v(bksge::in_place_type_t<int>{}, x);
		EXPECT_EQ(v.index(), 2u);
		EXPECT_EQ(get<2>(v), x);
	}
}

GTEST_TEST(VariantTest, CtorInPlaceTypeArgsTest)
{
	test_ctor_basic();
	test_ctor_sfinae();
}

}	// namespace ctor_in_place_type_args_test

}	// namespace bksge_variant_test
