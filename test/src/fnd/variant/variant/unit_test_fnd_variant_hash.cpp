/**
 *	@file	unit_test_fnd_variant_hash.cpp
 *
 *	@brief	hash のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/monostate.hpp>
//#include <bksge/fnd/type_traits/invoke_result.hpp>
//#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
//#include <bksge/fnd/type_traits/is_default_constructible.hpp>
//#include <bksge/fnd/type_traits/is_destructible.hpp>
//#include <bksge/fnd/type_traits/is_function.hpp>
//#include <bksge/fnd/type_traits/is_move_assignable.hpp>
//#include <bksge/fnd/type_traits/is_move_constructible.hpp>
//#include <bksge/fnd/type_traits/is_same.hpp>
//#include <bksge/fnd/type_traits/is_swappable.hpp>
//#include <bksge/fnd/type_traits/remove_pointer.hpp>
//#include <bksge/fnd/type_traits/remove_reference.hpp>
//#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>
#include <functional>
//#include <type_traits>
#include <gtest/gtest.h>
#include "fnd/variant/test_macros.hpp"
#include "fnd/variant/variant_test_helpers.hpp"
#include "fnd/variant/poisoned_hash_helper.hpp"

#if !defined(BKSGE_NO_EXCEPTIONS)

namespace std
{

template <>
struct hash<bksge_variant_test::MakeEmptyT>
{
	size_t operator()(const bksge_variant_test::MakeEmptyT&) const
	{
		assert(false);
		return 0;
	}
};

}	// namespace std

#endif

namespace bksge_variant_test
{

namespace hash_test
{

void test_hash_variant()
{
	{
		using V = bksge::variant<int, long, int>;
		using H = std::hash<V>;
		const V v(bksge::in_place_index_t<0>{}, 42);
		const V v_copy = v;
		V v2(bksge::in_place_index_t<0>{}, 100);
		const H h{};
		EXPECT_TRUE(h(v) == h(v));
		EXPECT_TRUE(h(v) != h(v2));
		EXPECT_TRUE(h(v) == h(v_copy));
		{
			ASSERT_SAME_TYPE(decltype(h(v)), bksge::size_t);
			static_assert(bksge::is_copy_constructible<H>::value, "");
		}
	}
	{
		using V = bksge::variant<bksge::monostate, int, long, const char*>;
		using H = std::hash<V>;
		const char* str = "hello";
		const V v0;
		const V v0_other;
		const V v1(42);
		const V v1_other(100);
		V v2(100l);
		V v2_other(999l);
		V v3(str);
		V v3_other("not hello");
		const H h{};
		EXPECT_TRUE(h(v0) == h(v0));
		EXPECT_TRUE(h(v0) == h(v0_other));
		EXPECT_TRUE(h(v1) == h(v1));
		EXPECT_TRUE(h(v1) != h(v1_other));
		EXPECT_TRUE(h(v2) == h(v2));
		EXPECT_TRUE(h(v2) != h(v2_other));
		EXPECT_TRUE(h(v3) == h(v3));
		EXPECT_TRUE(h(v3) != h(v3_other));
		EXPECT_TRUE(h(v0) != h(v1));
		EXPECT_TRUE(h(v0) != h(v2));
		EXPECT_TRUE(h(v0) != h(v3));
		EXPECT_TRUE(h(v1) != h(v2));
		EXPECT_TRUE(h(v1) != h(v3));
		EXPECT_TRUE(h(v2) != h(v3));
	}
#if !defined(BKSGE_NO_EXCEPTIONS)
	{
		using V = bksge::variant<int, MakeEmptyT>;
		using H = std::hash<V>;
		V v;
		makeEmpty(v);
		V v2;
		makeEmpty(v2);
		const H h{};
		EXPECT_TRUE(h(v) == h(v2));
	}
#endif
}

void test_hash_monostate()
{
	using H = std::hash<bksge::monostate>;
	const H h{};
	bksge::monostate m1{};
	const bksge::monostate m2{};
	EXPECT_TRUE(h(m1) == h(m1));
	EXPECT_TRUE(h(m2) == h(m2));
	EXPECT_TRUE(h(m1) == h(m2));
	{
		ASSERT_SAME_TYPE(decltype(h(m1)), bksge::size_t);
		ASSERT_NOEXCEPT(h(m1));
		static_assert(bksge::is_copy_constructible<H>::value, "");
	}
	{
		test_hash_enabled_for_type<bksge::monostate>();
	}
}

void test_hash_variant_duplicate_elements()
{
	// Test that the index of the alternative participates in the hash value.
	using V = bksge::variant<bksge::monostate, bksge::monostate>;
	using H = std::hash<V>;
	H h{};
	const V v1(bksge::in_place_index_t<0>{});
	const V v2(bksge::in_place_index_t<1>{});
	assert(h(v1) == h(v1));
	assert(h(v2) == h(v2));
	LIBCPP_ASSERT(h(v1) != h(v2));
}

struct A {};
struct B {};

}	// namespace hash_test

}	// namespace bksge_variant_test

namespace std
{

template <>
struct hash<bksge_variant_test::hash_test::B>
{
	size_t operator()(bksge_variant_test::hash_test::B const&) const
	{
		return 0;
	}
};

}	// namespace std

namespace bksge_variant_test
{

namespace hash_test
{

void test_hash_variant_enabled()
{
	{
		test_hash_enabled_for_type<bksge::variant<int> >();
		test_hash_enabled_for_type<bksge::variant<int*, long, double, const int> >();
	}
#if !(defined(BKSGE_MSVC) && (BKSGE_MSVC <= 1916)) && \
	!(defined(BKSGE_APPLE_CLANG) && (BKSGE_CXX_STANDARD <= 11))
	{
		test_hash_disabled_for_type<bksge::variant<int, A>>();
		test_hash_disabled_for_type<bksge::variant<const A, void*>>();
	}
#endif
	{
		test_hash_enabled_for_type<bksge::variant<int, B>>();
		test_hash_enabled_for_type<bksge::variant<const B, int>>();
	}
}

GTEST_TEST(VariantTest, HashTest)
{
	test_hash_variant();
	test_hash_variant_duplicate_elements();
	test_hash_monostate();
	test_hash_variant_enabled();
}

}	// namespace hash_test

}	// namespace bksge_variant_test
