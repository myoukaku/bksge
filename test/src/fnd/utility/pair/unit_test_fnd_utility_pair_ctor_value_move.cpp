/**
 *	@file	unit_test_fnd_utility_pair_ctor_value_move.cpp
 *
 *	@brief	pair::pair(U1&&, U2&&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/pair.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_pair_test
{

namespace ctor_value_move_test
{

struct Explicit
{
	explicit BKSGE_CONSTEXPR Explicit(int x) noexcept : n(x) {}
	int n;
};

struct Implicit
{
	BKSGE_CONSTEXPR Implicit(int x) : n(x) {}
	int n;
};

static_assert( bksge::is_constructible<bksge::pair<Explicit, Explicit>, int, int>::value, "");
static_assert( bksge::is_constructible<bksge::pair<Explicit, Implicit>, int, int>::value, "");
static_assert( bksge::is_constructible<bksge::pair<Implicit, Explicit>, int, int>::value, "");
static_assert( bksge::is_constructible<bksge::pair<Implicit, Implicit>, int, int>::value, "");
static_assert( bksge::is_constructible<bksge::pair<int, int>, int, int>::value, "");

static_assert(!bksge::is_implicitly_constructible<bksge::pair<Explicit, Explicit>, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::pair<Explicit, Implicit>, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::pair<Implicit, Explicit>, int, int>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::pair<Implicit, Implicit>, int, int>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::pair<int, int>, int, int>::value, "");

static_assert( bksge::is_nothrow_constructible<bksge::pair<Explicit, Explicit>, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::pair<Explicit, Implicit>, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::pair<Implicit, Explicit>, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::pair<Implicit, Implicit>, int, int>::value, "");
static_assert( bksge::is_nothrow_constructible<bksge::pair<int, int>, int, int>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	{
		bksge::pair<int, int> p(1, 2);
		VERIFY(p.first  == 1);
		VERIFY(p.second == 2);
	}
	{
		bksge::pair<int, int> p{3, 4};
		VERIFY(p.first  == 3);
		VERIFY(p.second == 4);
	}
	{
		bksge::pair<int, int> p = {5, 6};
		VERIFY(p.first  == 5);
		VERIFY(p.second == 6);
	}
	{
		bksge::pair<Explicit, Explicit> p(1, 2);
		VERIFY(p.first.n  == 1);
		VERIFY(p.second.n == 2);
	}
	{
		bksge::pair<Explicit, Implicit> p(3, 4);
		VERIFY(p.first.n  == 3);
		VERIFY(p.second.n == 4);
	}
	{
		bksge::pair<Implicit, Explicit> p{5, 6};
		VERIFY(p.first.n  == 5);
		VERIFY(p.second.n == 6);
	}
	{
		bksge::pair<Implicit, Implicit> p = {7, 8};
		VERIFY(p.first.n  == 7);
		VERIFY(p.second.n == 8);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, CtorValueMoveTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace ctor_value_move_test

}	// namespace bksge_pair_test
