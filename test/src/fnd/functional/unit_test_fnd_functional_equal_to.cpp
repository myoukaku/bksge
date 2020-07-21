/**
 *	@file	unit_test_fnd_functional_equal_to.cpp
 *
 *	@brief	equal_to のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/equal_to.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_invocable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_invocable_r.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"

namespace bksge_functional_test
{

namespace equal_to_test
{

template <typename T, typename = void>
struct has_is_transparent
	: public bksge::false_type {};

template <typename T>
struct has_is_transparent<T, bksge::void_t<typename T::is_transparent>>
	: public bksge::true_type {};

GTEST_TEST(FunctionalTest, EqualToTest)
{
	{
		using type = bksge::equal_to<int>;
		static_assert(bksge::is_same<type::result_type,          bool>::value, "");
		static_assert(bksge::is_same<type::first_argument_type,  int>::value, "");
		static_assert(bksge::is_same<type::second_argument_type, int>::value, "");
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(0, 0));
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(2, 3));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = bksge::equal_to<float>;
		static_assert(bksge::is_same<type::result_type,          bool>::value, "");
		static_assert(bksge::is_same<type::first_argument_type,  float>::value, "");
		static_assert(bksge::is_same<type::second_argument_type, float>::value, "");
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(0.5,  0.5));
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(0.5, -0.5));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = bksge::equal_to<>;
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(1, 1.0));
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(1.5, 2U));
		EXPECT_TRUE (type()(std::string("Hello"), "Hello"));
		EXPECT_FALSE(type()(std::string("Hello"), "hello"));
		static_assert( has_is_transparent<type>::value, "");
	}
}

struct X { };
int operator==(X, X) noexcept { return 2; }
int operator!=(X, X) { return 0; }

struct Y
{
	operator void*() const;
	operator int() const;
};
static_assert(!bksge::is_invocable<bksge::ranges::equal_to&, Y, Y>::value, "");

struct A
{
	operator void*() const;
};
static_assert( bksge::is_invocable<bksge::ranges::equal_to&, A, A>::value, "");

struct B
{
	operator void*() const;
	bool operator==(B const&) const;
	bool operator!=(B const&) const = delete;
};
static_assert(!bksge::is_invocable<bksge::ranges::equal_to&, B, B>::value, "");

GTEST_TEST(FunctionalTest, RangesEqualToTest)
{
	using F = bksge::ranges::equal_to;
	static_assert( bksge::is_default_constructible<F>::value, "");
	static_assert( bksge::is_copy_constructible<F>::value, "");
	static_assert( bksge::is_move_constructible<F>::value, "");
	static_assert( bksge::is_copy_assignable<F>::value, "");
	static_assert( bksge::is_move_assignable<F>::value, "");

	static_assert(!bksge::is_invocable<F>::value, "");
	static_assert(!bksge::is_invocable<F, int&>::value, "");
	static_assert(!bksge::is_invocable<F, int, void>::value, "");
	static_assert(!bksge::is_invocable<F, int, void*>::value, "");
	static_assert( bksge::is_invocable<F, int*, void*>::value, "");
	static_assert( bksge::is_nothrow_invocable_r<bool, F&, int&, int>::value, "");
	static_assert( bksge::is_nothrow_invocable_r<bool, F, const long&, char>::value, "");
	static_assert( bksge::is_nothrow_invocable_r<bool, const F&, short, int&>::value, "");
	static_assert( bksge::is_nothrow_invocable_r<bool, const F, const char, char>::value, "");

	static_assert( has_is_transparent<F>::value, "");

	static_assert( bksge::ranges::equal_to{}(99, 99.0), "");
	static_assert(!bksge::ranges::equal_to{}(99, 99.01), "");
	static_assert(!bksge::ranges::equal_to{}(99, 140L), "");

	{
		F f;
		int a[2]{};
		EXPECT_TRUE( f(&a, (void*)&a[0]));
		EXPECT_TRUE(!f(&a, (void*)&a[1]));
		EXPECT_TRUE( f(&a + 1, (void*)(a + 2)));
	}

	static_assert(bksge::is_nothrow_invocable_r<bool, F&, X, X>::value, "");

	{
		X x;
		F f;
		EXPECT_TRUE(f(x, x));
	}
}

}	// namespace equal_to_test

}	// namespace bksge_functional_test
