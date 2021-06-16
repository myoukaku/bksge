/**
 *	@file	unit_test_fnd_optional_requirements.cpp
 *
 *	@brief	optional のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/optional/optional.hpp>
#include <bksge/fnd/optional/nullopt.hpp>
#include <bksge/fnd/optional/bad_optional_access.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_destructible.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_optional_test
{

namespace requirements_test
{

struct trivially_destructible
{
	trivially_destructible() = delete;
	trivially_destructible(trivially_destructible const&) = delete;
	trivially_destructible& operator=(trivially_destructible const&) = delete;
	trivially_destructible(trivially_destructible&&) = delete;
	trivially_destructible& operator=(trivially_destructible&&) = delete;
	~trivially_destructible() BKSGE_NOEXCEPT = default;
};

struct no_default_constructor
{
	no_default_constructor() = delete;
};

struct no_copy_constructor
{
	no_copy_constructor() = default;
	no_copy_constructor(no_copy_constructor const&) = delete;
	no_copy_constructor& operator=(no_copy_constructor const&) = default;
	no_copy_constructor(no_copy_constructor&&) {}
	no_copy_constructor& operator=(no_copy_constructor&&) {return *this; }
};

struct no_copy_assignment
{
	no_copy_assignment() = default;
	no_copy_assignment(no_copy_assignment const&) = default;
	no_copy_assignment(no_copy_assignment&&) {}
	no_copy_assignment& operator=(no_copy_assignment&&) {return *this; }
};

struct no_move_constructor
{
	no_move_constructor() = default;
	no_move_constructor(no_move_constructor const&) = default;
	no_move_constructor& operator=(no_move_constructor const&) = default;
	no_move_constructor(no_move_constructor&&) = delete;
	no_move_constructor& operator=(no_move_constructor&&) {return *this; }
};

struct no_move_assignment
{
	no_move_assignment() = default;
	no_move_assignment(no_move_assignment const&) = default;
	no_move_assignment& operator=(no_move_assignment const&) = default;
	no_move_assignment(no_move_assignment&&) {}
	no_move_assignment& operator=(no_move_assignment&&) = delete;
};

struct no_copy : no_copy_constructor, no_copy_assignment {};
struct no_move : no_move_constructor, no_move_assignment {};

// Laxest possible model of a value type for optional
struct only_destructible
{
	only_destructible(only_destructible&&) = delete;
};

/*
 * Should not complain about 'invalid' specializations as long as
 * they're not instantiated.
 */
using A  = bksge::optional<int&>;
using B  = bksge::optional<int&&>;
using C1 = bksge::optional<bksge::in_place_t>;
using C2 = bksge::optional<bksge::in_place_t const>;
using C3 = bksge::optional<bksge::in_place_t volatile>;
using C4 = bksge::optional<bksge::in_place_t const volatile>;
using D1 = bksge::optional<bksge::nullopt_t>;
using D2 = bksge::optional<bksge::nullopt_t const>;
using D3 = bksge::optional<bksge::nullopt_t volatile>;
using D4 = bksge::optional<bksge::nullopt_t const volatile>;
using X  = bksge::tuple<A, B, C1, C2, C3, C4, D1, D2, D3, D4>;

GTEST_TEST(OptionalTest, RequirememtsTest)
{
	{
		static_assert(bksge::is_default_constructible<bksge::bad_optional_access>::value, "");
	}
	{
		static_assert(bksge::is_trivially_destructible<trivially_destructible>::value, "");
		static_assert(bksge::is_trivially_destructible<bksge::optional<trivially_destructible>>::value, "");
	}
	{
		using T = no_default_constructor;
		using O = bksge::optional<T>;
		static_assert(bksge::is_same<O::value_type, T>::value, "");
		static_assert(bksge::is_default_constructible<O>::value, "");
		{ O o; (void)o; }
		static_assert(bksge::is_copy_constructible<O>::value, "");
		{ O o; auto copy = o; (void)copy; }
		static_assert(bksge::is_copy_assignable<O>::value, "");
		{ O o, p; p = o; }
		static_assert(bksge::is_move_constructible<O>::value, "");
		{ O o; auto moved_to = bksge::move(o); (void)moved_to; }
		static_assert(bksge::is_move_assignable<O>::value, "");
		{ O o, p; p = bksge::move(o); }
	}
#if !(defined(_MSC_VER) && _MSC_VER <= 1900)
	{
		using T = no_copy_constructor;
		using O = bksge::optional<T>;
		static_assert(bksge::is_same<O::value_type, T>::value, "");
		static_assert(bksge::is_default_constructible<O>::value, "");
		{ O o; (void)o; }
		static_assert(!bksge::is_copy_constructible<O>::value, "");
		static_assert(!bksge::is_copy_assignable<O>::value, "");
		static_assert(bksge::is_move_constructible<O>::value, "");
		{ O o; auto moved_to = bksge::move(o); (void)moved_to; }
		static_assert(bksge::is_move_assignable<O>::value, "");
		{ O o, p; p = bksge::move(o); }
	}
	{
		using T = no_copy_assignment;
		using O = bksge::optional<T>;
		static_assert(bksge::is_default_constructible<O>::value, "");
		{ O o; (void)o; }
		static_assert(bksge::is_copy_constructible<O>::value, "");
		{ O o; auto copy = o; (void)copy; }
		static_assert(!bksge::is_copy_assignable<O>::value, "");
		static_assert(bksge::is_move_constructible<O>::value, "");
		{ O o; auto moved_to = bksge::move(o); (void)moved_to; }
		static_assert(bksge::is_move_assignable<O>::value, "");
		{ O o, p; p = bksge::move(o); }
	}
	{
		using T = no_copy;
		using O = bksge::optional<T>;
		static_assert(bksge::is_same<O::value_type, T>::value, "");
		static_assert(bksge::is_default_constructible<O>::value, "");
		{ O o; (void)o; }
		static_assert(!bksge::is_copy_constructible<O>::value, "");
		static_assert(!bksge::is_copy_assignable<O>::value, "");
		static_assert(bksge::is_move_constructible<O>::value, "");
		{ O o; auto moved_to = bksge::move(o); (void)moved_to; }
		static_assert(bksge::is_move_assignable<O>::value, "");
		{ O o, p; p = bksge::move(o); }
	}
	{
		using T = no_move_constructor;
		using O = bksge::optional<T>;
		static_assert(bksge::is_same<O::value_type, T>::value, "");
		static_assert(bksge::is_default_constructible<O>::value, "");
		{ O o; (void)o; }
		static_assert(bksge::is_copy_constructible<O>::value, "");
		{ O o; auto copy = o; (void)copy; }
		static_assert(bksge::is_copy_assignable<O>::value, "");
		/*
		 * T should be move constructible due to [12.8/11], which is a new rule in C++1y
		 * not yet implemented by GCC. Because there is already a special exception in C++11
		 * for the generation of the special members that GCC implements (at least some of the
		 * time), this does not affect the bksge::optional implementation however. So the assertion
		 * for T should be changed (or removed altogether) when the time comes, but the rest
		 * should however remain correct and unchanged.
		 */
		static_assert(!bksge::is_move_constructible<T>::value, "");
		static_assert(bksge::is_move_constructible<O>::value, "");
		{ O o; auto moved_to = bksge::move(o); (void)moved_to; }
		static_assert(bksge::is_move_assignable<O>::value, "");
		{ O o, p; p = bksge::move(o); }
	}
	{
		using T = no_move_assignment;
		using O = bksge::optional<T>;
		static_assert(bksge::is_same<O::value_type, T>::value, "");
		static_assert(bksge::is_default_constructible<O>::value, "");
		{ O o; (void)o; }
		static_assert(bksge::is_copy_constructible<O>::value, "");
		{ O o; auto copy = o; (void)copy; }
		static_assert(bksge::is_copy_assignable<O>::value, "");
		{ O o, p; p = o; }
		static_assert(bksge::is_move_constructible<O>::value, "");
		{ O o; auto moved_to = bksge::move(o); (void)moved_to; }
		/*
		 * Paragraph 23 of same leads to a similar situation but with respect to move
		 * assignment.
		 */
		static_assert(!bksge::is_move_assignable<T>::value, "");
		static_assert(bksge::is_move_assignable<O>::value, "");
		{ O o, p; p = bksge::move(o); }
	}
	{
		using T = no_move;
		using O = bksge::optional<T>;
		static_assert(bksge::is_same<O::value_type, T>::value, "");
		static_assert(bksge::is_default_constructible<O>::value, "");
		{ O o; (void)o; }
		static_assert(bksge::is_copy_constructible<O>::value, "");
		{ O o; auto copy = o; (void)copy; }
		static_assert(bksge::is_copy_assignable<O>::value, "");
		{ O o, p; p = o; }
		static_assert(bksge::is_move_constructible<O>::value, "");
// TODO g++9 でエラーになる
//		{ O o; auto moved_to = bksge::move(o); (void)moved_to; }
		static_assert(bksge::is_move_assignable<O>::value, "");
		{ O o, p; p = bksge::move(o); }
	}
	{
		using T = only_destructible;
		using O = bksge::optional<T>;
		static_assert(bksge::is_same<O::value_type, T>::value, "");
		static_assert(bksge::is_default_constructible<O>::value, "");
		{ O o; (void)o; }
		static_assert(!bksge::is_copy_constructible<O>::value, "");
		static_assert(!bksge::is_copy_assignable<O>::value, "");
		static_assert(!bksge::is_move_constructible<O>::value, "");
		static_assert(!bksge::is_move_assignable<O>::value, "");
	}

	{
		bksge::optional<const int> o{ 42 };
		static_assert(bksge::is_same<decltype(o)::value_type, const int>::value, "");
		EXPECT_TRUE((bool)o);
		EXPECT_TRUE(*o == 42);
	}
	{
		BKSGE_CONSTEXPR bksge::optional<const int> o{ 33 };
		static_assert(bksge::is_same<decltype(o)::value_type, const int>::value, "");
		BKSGE_CONSTEXPR_EXPECT_TRUE((bool)o);
		BKSGE_CONSTEXPR_EXPECT_TRUE(*o == 33);
	}
#endif
}

}	// namespace requirements_test

}	// namespace bksge_optional_test
