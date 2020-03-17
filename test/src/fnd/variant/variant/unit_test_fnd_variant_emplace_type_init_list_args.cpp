﻿/**
 *	@file	unit_test_fnd_variant_emplace_type_init_list_args.cpp
 *
 *	@brief	variant::emplace(initializer_list<U> il,Args&&... args) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <initializer_list>
#include <utility>
#include <gtest/gtest.h>
#include "fnd/variant/archetypes.hpp"
#include "fnd/variant/test_convertible.hpp"
#include "fnd/variant/test_macros.hpp"

namespace bksge_variant_test
{

namespace emplace_type_init_list_args_test
{

struct InitList
{
	std::size_t size;

	BKSGE_CXX14_CONSTEXPR
	InitList(std::initializer_list<int> il)
		: size(il.size()) {}
};

struct InitListArg
{
	std::size_t size;
	int value;

	BKSGE_CXX14_CONSTEXPR
	InitListArg(std::initializer_list<int> il, int v)
		: size(il.size()), value(v) {}
};

template <class Var, class T, class... Args>
constexpr auto test_emplace_exists_imp(int) -> decltype(
	bksge::declval<Var>().template emplace<T>(bksge::declval<Args>()...), true)
{
	return true;
}

template <class, class, class...>
constexpr auto test_emplace_exists_imp(long) -> bool
{
	return false;
}

template <class... Args>
constexpr bool emplace_exists()
{
	return test_emplace_exists_imp<Args...>(0);
}

void test_emplace_sfinae()
{
	using V = bksge::variant<int, TestTypes::NoCtors, InitList, InitListArg, long, long>;
	using IL = std::initializer_list<int>;
	static_assert( emplace_exists<V, InitList, IL>(), "");
	static_assert(!emplace_exists<V, InitList, int>(), "args don't match");
	static_assert(!emplace_exists<V, InitList, IL, int>(), "too many args");
	static_assert( emplace_exists<V, InitListArg, IL, int>(), "");
	static_assert(!emplace_exists<V, InitListArg, int>(), "args don't match");
	static_assert(!emplace_exists<V, InitListArg, IL>(), "too few args");
	static_assert(!emplace_exists<V, InitListArg, IL, int, int>(), "too many args");
}

void test_basic()
{
	using V = bksge::variant<int, InitList, InitListArg, TestTypes::NoCtors>;
	V v;
	auto& ref1 = v.emplace<InitList>({1, 2, 3});
	static_assert(bksge::is_same<InitList&, decltype(ref1)>::value, "");
	EXPECT_EQ(bksge::get<InitList>(v).size, 3u);
	EXPECT_EQ(&ref1, &bksge::get<InitList>(v));
	auto& ref2 = v.emplace<InitListArg>({1, 2, 3, 4}, 42);
	static_assert(bksge::is_same<InitListArg&, decltype(ref2)>::value, "");
	EXPECT_EQ(bksge::get<InitListArg>(v).size, 4u);
	EXPECT_EQ(bksge::get<InitListArg>(v).value, 42);
	EXPECT_EQ(&ref2, &bksge::get<InitListArg>(v));
	auto& ref3 = v.emplace<InitList>({1});
	static_assert(bksge::is_same<InitList&, decltype(ref3)>::value, "");
	EXPECT_EQ(bksge::get<InitList>(v).size, 1u);
	EXPECT_EQ(&ref3, &bksge::get<InitList>(v));
}

GTEST_TEST(VariantTest, EmplaceTypeInitListArgsTest)
{
	test_basic();
	test_emplace_sfinae();
}

}	// namespace emplace_type_init_list_args_test

}	// namespace bksge_variant_test
