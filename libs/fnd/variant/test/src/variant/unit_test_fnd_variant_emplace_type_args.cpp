﻿/**
 *	@file	unit_test_fnd_variant_emplace_type_args.cpp
 *
 *	@brief	variant::emplace(Args&&... args) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/utility/in_place_type.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <gtest/gtest.h>
#include <utility>
#include "archetypes.hpp"
#include "test_convertible.hpp"
#include "test_macros.hpp"
#include "variant_test_helpers.hpp"

namespace bksge_variant_test
{

namespace emplace_type_args_test
{

template <typename Var, typename T, typename... Args>
constexpr auto test_emplace_exists_imp(int) -> decltype(
	std::declval<Var>().template emplace<T>(std::declval<Args>()...), true)
{
	return true;
}

template <typename, typename, typename...>
constexpr auto test_emplace_exists_imp(long) -> bool
{
	return false;
}

template <typename... Args>
constexpr bool emplace_exists()
{
	return test_emplace_exists_imp<Args...>(0);
}

void test_emplace_sfinae()
{
	{
		using V = bksge::variant<int, void*, const void*, TestTypes::NoCtors>;
		static_assert( emplace_exists<V, int>(), "");
		static_assert( emplace_exists<V, int, int>(), "");
		static_assert(!emplace_exists<V, int, decltype(nullptr)>(), "cannot construct");
		static_assert( emplace_exists<V, void*, decltype(nullptr)>(), "");
		static_assert(!emplace_exists<V, void*, int>(), "cannot construct");
		static_assert( emplace_exists<V, void*, int*>(), "");
		static_assert(!emplace_exists<V, void*, const int*>(), "");
		static_assert( emplace_exists<V, const void*, const int*>(), "");
		static_assert( emplace_exists<V, const void*, int*>(), "");
		static_assert(!emplace_exists<V, TestTypes::NoCtors>(), "cannot construct");
	}

#if !defined(TEST_VARIANT_HAS_NO_REFERENCES)
	using V = bksge::variant<int, int&, const int&, int&&, long, long, TestTypes::NoCtors>;
	static_assert( emplace_exists<V, int>(), "");
	static_assert( emplace_exists<V, int, int>(), "");
	static_assert( emplace_exists<V, int, long long>(), "");
	static_assert(!emplace_exists<V, int, int, int>(), "too many args");
	static_assert( emplace_exists<V, int&, int&>(), "");
	static_assert(!emplace_exists<V, int&>(), "cannot default construct ref");
	static_assert(!emplace_exists<V, int&, const int&>(), "cannot bind ref");
	static_assert(!emplace_exists<V, int&, int&&>(), "cannot bind ref");
	static_assert( emplace_exists<V, const int&, int&>(), "");
	static_assert( emplace_exists<V, const int&, const int&>(), "");
	static_assert( emplace_exists<V, const int&, int&&>(), "");
	static_assert(!emplace_exists<V, const int&, void*>(), "not constructible from void*");
	static_assert( emplace_exists<V, int&&, int>(), "");
	static_assert(!emplace_exists<V, int&&, int&>(), "cannot bind ref");
	static_assert(!emplace_exists<V, int&&, const int&>(), "cannot bind ref");
	static_assert(!emplace_exists<V, int&&, const int&&>(), "cannot bind ref");
	static_assert(!emplace_exists<V, long, long>(), "ambiguous");
	static_assert(!emplace_exists<V, TestTypes::NoCtors>(), "cannot construct void");
#endif
}

void test_basic()
{
	using std::get;
	{
		using V = bksge::variant<int>;
		V v(42);
		auto& ref1 = v.emplace<int>();
		static_assert(bksge::is_same<int&, decltype(ref1)>::value, "");
		EXPECT_EQ(get<0>(v), 0);
		EXPECT_EQ(&ref1, &get<0>(v));
		auto& ref2 = v.emplace<int>(42);
		static_assert(bksge::is_same<int&, decltype(ref2)>::value, "");
		EXPECT_EQ(get<0>(v), 42);
		EXPECT_EQ(&ref2, &get<0>(v));
	}
	{
		using V = bksge::variant<int, long, const void*, TestTypes::NoCtors, bksge::string>;
		const int x = 100;
		V v(bksge::in_place_type_t<int>{}, -1);
		// default emplace a value
		auto& ref1 = v.emplace<long>();
		static_assert(bksge::is_same<long&, decltype(ref1)>::value, "");
		EXPECT_EQ(get<1>(v), 0);
		EXPECT_EQ(&ref1, &get<1>(v));
		auto& ref2 = v.emplace<const void*>(&x);
		static_assert(bksge::is_same<const void*&, decltype(ref2)>::value, "");
		EXPECT_EQ(get<2>(v), &x);
		EXPECT_EQ(&ref2, &get<2>(v));
		// emplace with multiple args
		auto& ref3 = v.emplace<bksge::string>(3u, 'a');
		static_assert(bksge::is_same<bksge::string&, decltype(ref3)>::value, "");
		EXPECT_EQ(get<4>(v), "aaa");
		EXPECT_EQ(&ref3, &get<4>(v));
	}
#if !defined(TEST_VARIANT_HAS_NO_REFERENCES)
	{
		using V = bksge::variant<int, long, const int&, int&&, TestTypes::NoCtors, bksge::string>;
		const int x = 100;
		int y = 42;
		int z = 43;
		V v(bksge::in_place_index_t<0>{}, -1);
		// default emplace a value
		auto& ref1 = v.emplace<long>();
		static_assert(bksge::is_same<long&, decltype(ref1)>::value, "");
		EXPECT_EQ(get<long>(v), 0);
		EXPECT_EQ(&ref1, &get<long>(v));
		// emplace a reference
		auto& ref2 = v.emplace<const int&>(x);
		static_assert(bksge::is_same<const int&, decltype(ref2)>::value, "");
		EXPECT_EQ(&get<const int&>(v), &x);
		EXPECT_EQ(&ref2, &get<const int&>(v));
		// emplace an rvalue reference
		auto& ref3 = v.emplace<int&&>(std::move(y));
		static_assert(bksge::is_same<int&&, decltype(ref3)>::value, "");
		EXPECT_EQ(&get<int&&>(v), &y);
		EXPECT_EQ(&ref3, &get<int&&>(v));
		// re-emplace a new reference over the active member
		auto& ref4 = v.emplace<int&&>(std::move(z));
		static_assert(bksge::is_same<int&, decltype(ref4)>::value, "");
		EXPECT_EQ(&get<int&&>(v), &z);
		EXPECT_EQ(&ref4, &get<int&&>(v));
		// emplace with multiple args
		auto& ref5 = v.emplace<bksge::string>(3u, 'a');
		static_assert(bksge::is_same<bksge::string&, decltype(ref5)>::value, "");
		EXPECT_EQ(get<bksge::string>(v), "aaa");
		EXPECT_EQ(&ref5, &get<bksge::string>(v));
	}
#endif
}

GTEST_TEST(VariantTest, EmplaceTypeArgsTest)
{
	test_basic();
	test_emplace_sfinae();
}

}	// namespace emplace_type_args_test

}	// namespace bksge_variant_test
