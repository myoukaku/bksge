﻿/**
 *	@file	unit_test_fnd_functional_greater_equal.cpp
 *
 *	@brief	greater_equal のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/greater_equal.hpp>
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

namespace greater_equal_test
{

template <typename T, typename = void>
struct has_is_transparent
	: public bksge::false_type {};

template <typename T>
struct has_is_transparent<T, bksge::void_t<typename T::is_transparent>>
	: public bksge::true_type {};

GTEST_TEST(FunctionalTest, GreaterEqualTest)
{
	{
		using type = bksge::greater_equal<int>;
		static_assert(bksge::is_same<type::result_type,          bool>::value, "");
		static_assert(bksge::is_same<type::first_argument_type,  int>::value, "");
		static_assert(bksge::is_same<type::second_argument_type, int>::value, "");
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(2, 2));
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(2, 3));
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(2, 1));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = bksge::greater_equal<float>;
		static_assert(bksge::is_same<type::result_type,          bool>::value, "");
		static_assert(bksge::is_same<type::first_argument_type,  float>::value, "");
		static_assert(bksge::is_same<type::second_argument_type, float>::value, "");
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(-1.5f, -1.5f));
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(-1.5f, -1.6f));
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(-1.6f, -1.5f));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = bksge::greater_equal<>;
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(3U, 3.0));
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(3U, 3.1));
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(3U, 2.9));
		EXPECT_TRUE (type()(std::string("A"), "A"));
		EXPECT_FALSE(type()(std::string("A"), "B"));
		EXPECT_TRUE (type()(std::string("B"), "A"));
		static_assert( has_is_transparent<type>::value, "");
	}
}

struct X { };
int operator==(X, X) { return 2; }
int operator!=(X, X) { return 0; }
int operator<(X, X) noexcept { return 0; }
int operator>(X, X) { return 0; }
int operator<=(X, X) { return 3; }
int operator>=(X, X) { return 4; }

GTEST_TEST(FunctionalTest, RangesGreaterEqualTest)
{
	using F = bksge::ranges::greater_equal;
	static_assert( bksge::is_default_constructible<F>::value, "");
	static_assert( bksge::is_copy_constructible<F>::value, "");
	static_assert( bksge::is_move_constructible<F>::value, "");
	static_assert( bksge::is_copy_assignable<F>::value, "");
	static_assert( bksge::is_move_assignable<F>::value, "");

	static_assert(!bksge::is_invocable<F>::value, "");
	static_assert(!bksge::is_invocable<F, int&>::value, "");
	static_assert(!bksge::is_invocable<F, int, void>::value, "");
	static_assert(!bksge::is_invocable<F, int, void*>::value, "");
	static_assert( bksge::is_nothrow_invocable_r<bool, F&, int&, int>::value, "");
	static_assert( bksge::is_nothrow_invocable_r<bool, F, const long&, char>::value, "");
	static_assert( bksge::is_nothrow_invocable_r<bool, const F&, short, int&>::value, "");
	static_assert( bksge::is_nothrow_invocable_r<bool, const F, const char, char>::value, "");

	static_assert( has_is_transparent<F>::value, "");

	static_assert( bksge::ranges::greater_equal{}(99, 99.0), "");
	static_assert( bksge::ranges::greater_equal{}(99.01, 99), "");
	static_assert(!bksge::ranges::greater_equal{}(99, 140L), "");

	{
		F f;
		int a[2]{};
		EXPECT_TRUE( f(&a, (void*)&a[0]));
		EXPECT_TRUE( f((void*)&a[1], &a));
		EXPECT_TRUE( f(&a + 1, (void*)(a + 1)));
		EXPECT_TRUE(!f(&a, (void*)(a + 1)));
	}

	static_assert(bksge::is_nothrow_invocable_r<bool, F&, X, X>::value, "");

	{
		X x;
		F f;
		EXPECT_TRUE(f(x, x));
	}
}

}	// namespace greater_equal_test

}	// namespace bksge_functional_test
