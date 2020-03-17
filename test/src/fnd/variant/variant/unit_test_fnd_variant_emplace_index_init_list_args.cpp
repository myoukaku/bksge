/**
 *	@file	unit_test_fnd_variant_emplace_index_init_list_args.cpp
 *
 *	@brief	variant::emplace(initializer_list<U> il,Args&&... args) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <initializer_list>
#include <gtest/gtest.h>
#include "fnd/variant/archetypes.hpp"
#include "fnd/variant/test_convertible.hpp"
#include "fnd/variant/test_macros.hpp"

namespace bksge_variant_test
{

namespace emplace_index_init_list_args_test
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

template <class Var, std::size_t I, class... Args>
constexpr auto test_emplace_exists_imp(int) -> decltype(
	bksge::declval<Var>().template emplace<I>(bksge::declval<Args>()...), true)
{
	return true;
}

template <class, std::size_t, class...>
constexpr auto test_emplace_exists_imp(long) -> bool
{
	return false;
}

template <class Var, std::size_t I, class... Args>
constexpr bool emplace_exists()
{
	return test_emplace_exists_imp<Var, I, Args...>(0);
}

void test_emplace_sfinae()
{
	using V = bksge::variant<int, TestTypes::NoCtors, InitList, InitListArg, long, long>;
	using IL = std::initializer_list<int>;
	static_assert(!emplace_exists<V, 1, IL>(), "no such constructor");
	static_assert( emplace_exists<V, 2, IL>(), "");
	static_assert(!emplace_exists<V, 2, int>(), "args don't match");
	static_assert(!emplace_exists<V, 2, IL, int>(), "too many args");
	static_assert( emplace_exists<V, 3, IL, int>(), "");
	static_assert(!emplace_exists<V, 3, int>(), "args don't match");
	static_assert(!emplace_exists<V, 3, IL>(), "too few args");
	static_assert(!emplace_exists<V, 3, IL, int, int>(), "too many args");
}

void test_basic()
{
	using V = bksge::variant<int, InitList, InitListArg, TestTypes::NoCtors>;
	V v;
	auto& ref1 = v.emplace<1>({1, 2, 3});
	static_assert(bksge::is_same<InitList&, decltype(ref1)>::value, "");
	EXPECT_EQ(bksge::get<1>(v).size, 3u);
	EXPECT_EQ(&ref1, &bksge::get<1>(v));
	auto& ref2 = v.emplace<2>({1, 2, 3, 4}, 42);
	static_assert(bksge::is_same<InitListArg&, decltype(ref2)>::value, "");
	EXPECT_EQ(bksge::get<2>(v).size, 4u);
	EXPECT_EQ(bksge::get<2>(v).value, 42);
	EXPECT_EQ(&ref2, &bksge::get<2>(v));
	auto& ref3 = v.emplace<1>({1});
	static_assert(bksge::is_same<InitList&, decltype(ref3)>::value, "");
	EXPECT_EQ(bksge::get<1>(v).size, 1u);
	EXPECT_EQ(&ref3, &bksge::get<1>(v));
}

GTEST_TEST(VariantTest, EmplaceIndexInitListArgsTest)
{
	test_basic();
	test_emplace_sfinae();
}

}	// namespace emplace_index_init_list_args_test

}	// namespace bksge_variant_test
