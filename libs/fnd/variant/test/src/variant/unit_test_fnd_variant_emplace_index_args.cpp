/**
 *	@file	unit_test_fnd_variant_emplace_index_args.cpp
 *
 *	@brief	variant::emplace(Args&&... args) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "archetypes.hpp"
#include "test_convertible.hpp"
#include "test_macros.hpp"
#include "variant_test_helpers.hpp"

namespace bksge_variant_test
{

namespace emplace_index_args_test
{

template <typename Var, std::size_t I, typename... Args>
constexpr auto test_emplace_exists_imp(int) -> decltype(
	bksge::declval<Var>().template emplace<I>(bksge::declval<Args>()...), true)
{
	return true;
}

template <typename, std::size_t, typename...>
constexpr auto test_emplace_exists_imp(long) -> bool
{
	return false;
}

template <typename Var, std::size_t I, typename... Args>
constexpr bool emplace_exists()
{
	return test_emplace_exists_imp<Var, I, Args...>(0);
}

void test_emplace_sfinae()
{
	{
		using V = bksge::variant<int, void*, const void*, TestTypes::NoCtors>;
		static_assert( emplace_exists<V, 0>(), "");
		static_assert( emplace_exists<V, 0, int>(), "");
		static_assert(!emplace_exists<V, 0, decltype(nullptr)>(), "cannot construct");
		static_assert( emplace_exists<V, 1, decltype(nullptr)>(), "");
		static_assert( emplace_exists<V, 1, int*>(), "");
		static_assert(!emplace_exists<V, 1, const int*>(), "");
		static_assert(!emplace_exists<V, 1, int>(), "cannot construct");
		static_assert( emplace_exists<V, 2, const int*>(), "");
		static_assert( emplace_exists<V, 2, int*>(), "");
		static_assert(!emplace_exists<V, 3>(), "cannot construct");
	}
#if !defined(TEST_VARIANT_HAS_NO_REFERENCES)
	{
		using V = bksge::variant<int, int&, const int&, int&&, TestTypes::NoCtors>;
		static_assert( emplace_exists<V, 0>(), "");
		static_assert( emplace_exists<V, 0, int>(), "");
		static_assert( emplace_exists<V, 0, long long>(), "");
		static_assert(!emplace_exists<V, 0, int, int>(), "too many args");
		static_assert( emplace_exists<V, 1, int&>(), "");
		static_assert(!emplace_exists<V, 1>(), "cannot default construct ref");
		static_assert(!emplace_exists<V, 1, const int&>(), "cannot bind ref");
		static_assert(!emplace_exists<V, 1, int&&>(), "cannot bind ref");
		static_assert( emplace_exists<V, 2, int&>(), "");
		static_assert( emplace_exists<V, 2, const int&>(), "");
		static_assert( emplace_exists<V, 2, int&&>(), "");
		static_assert(!emplace_exists<V, 2, void*>(), "not constructible from void*");
		static_assert( emplace_exists<V, 3, int>(), "");
		static_assert(!emplace_exists<V, 3, int&>(), "cannot bind ref");
		static_assert(!emplace_exists<V, 3, const int&>(), "cannot bind ref");
		static_assert(!emplace_exists<V, 3, const int&&>(), "cannot bind ref");
		static_assert(!emplace_exists<V, 4>(), "no ctors");
	}
#endif
}

void test_basic()
{
	using std::get;
	{
		using V = bksge::variant<int>;
		V v(42);
		auto& ref1 = v.emplace<0>();
		static_assert(bksge::is_same<int&, decltype(ref1)>::value, "");
		EXPECT_EQ(get<0>(v), 0);
		EXPECT_EQ(&ref1, &get<0>(v));
		auto& ref2 = v.emplace<0>(42);
		static_assert(bksge::is_same<int&, decltype(ref2)>::value, "");
		EXPECT_EQ(get<0>(v), 42);
		EXPECT_EQ(&ref2, &get<0>(v));
	}
	{
		using V = bksge::variant<int, long, const void*, TestTypes::NoCtors, bksge::string>;
		const int x = 100;
		V v(bksge::in_place_index_t<0>{}, -1);
		// default emplace a value
		auto& ref1 = v.emplace<1>();
		static_assert(bksge::is_same<long&, decltype(ref1)>::value, "");
		EXPECT_EQ(get<1>(v), 0);
		EXPECT_EQ(&ref1, &get<1>(v));
		auto& ref2 = v.emplace<2>(&x);
		static_assert(bksge::is_same<const void*&, decltype(ref2)>::value, "");
		EXPECT_EQ(get<2>(v), &x);
		EXPECT_EQ(&ref2, &get<2>(v));
		// emplace with multiple args
		auto& ref3 = v.emplace<4>(3u, 'a');
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
		auto& ref1 = v.emplace<1>();
		static_assert(bksge::is_same<long&, decltype(ref1)>::value, "");
		EXPECT_EQ(get<1>(v), 0);
		EXPECT_EQ(&ref1, &get<1>(v));
		// emplace a reference
		auto& ref2 = v.emplace<2>(x);
		static_assert(bksge::is_same<const int&, decltype(ref2)>::value, "");
		EXPECT_EQ(&get<2>(v), &x);
		EXPECT_EQ(&ref2, &get<2>(v));
		// emplace an rvalue reference
		auto& ref3 = v.emplace<3>(bksge::move(y));
		static_assert(bksge::is_same<int&, decltype(ref3)>::value, "");
		EXPECT_EQ(&get<3>(v), &y);
		EXPECT_EQ(&ref3, &get<3>(v));
		// re-emplace a new reference over the active member
		auto& ref4 = v.emplace<3>(bksge::move(z));
		static_assert(bksge::is_same<int&, decltype(ref4)>::value, "");
		EXPECT_EQ(&get<3>(v), &z);
		EXPECT_EQ(&ref4, &get<3>(v));
		// emplace with multiple args
		auto& ref5 = v.emplace<5>(3u, 'a');
		static_assert(bksge::is_same<bksge::string&, decltype(ref5)>::value, "");
		EXPECT_EQ(get<5>(v), "aaa");
		EXPECT_EQ(&ref5, &get<5>(v));
	}
#endif
}

GTEST_TEST(VariantTest, EmplaceIndexArgsTest)
{
	test_basic();
	test_emplace_sfinae();
}

}	// namespace emplace_index_args_test

}	// namespace bksge_variant_test
