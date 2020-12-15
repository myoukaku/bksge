/**
 *	@file	unit_test_fnd_utility_pair_ctor_value_copy.cpp
 *
 *	@brief	pair::pair(T1 const&, T2 const&) のテスト
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

namespace ctor_value_copy_test
{

struct Explicit
{
	BKSGE_CONSTEXPR Explicit(int x) : n(x) {}
	explicit BKSGE_CONSTEXPR Explicit(Explicit const& rhs) noexcept : n(rhs.n) {}
	int n;
};

struct Implicit
{
	BKSGE_CONSTEXPR Implicit(int x) : n(x) {}
	BKSGE_CONSTEXPR Implicit(Implicit const& rhs) : n(rhs.n) {}
	int n;
};

static_assert( bksge::is_constructible<bksge::pair<Explicit, Explicit>, Explicit const&, Explicit const&>::value, "");
static_assert( bksge::is_constructible<bksge::pair<Explicit, Implicit>, Explicit const&, Implicit const&>::value, "");
static_assert( bksge::is_constructible<bksge::pair<Implicit, Explicit>, Implicit const&, Explicit const&>::value, "");
static_assert( bksge::is_constructible<bksge::pair<Implicit, Implicit>, Implicit const&, Implicit const&>::value, "");

static_assert(!bksge::is_implicitly_constructible<bksge::pair<Explicit, Explicit>, Explicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::pair<Explicit, Implicit>, Explicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::pair<Implicit, Explicit>, Implicit const&, Explicit const&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::pair<Implicit, Implicit>, Implicit const&, Implicit const&>::value, "");

static_assert(!bksge::is_implicitly_constructible<bksge::pair<Explicit, int>,      Explicit const&, int      const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::pair<int,      Explicit>, int      const&, Explicit const&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::pair<Implicit, int>,      Implicit const&, int      const&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::pair<int,      Implicit>, int      const&, Implicit const&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::pair<int,      int>,      int      const&, int      const&>::value, "");

static_assert( bksge::is_nothrow_constructible<bksge::pair<Explicit, Explicit>, Explicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::pair<Explicit, Implicit>, Explicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::pair<Implicit, Explicit>, Implicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::pair<Implicit, Implicit>, Implicit const&, Implicit const&>::value, "");

static_assert( bksge::is_nothrow_constructible<bksge::pair<Explicit, int>,      Explicit const&, int      const&>::value, "");
static_assert( bksge::is_nothrow_constructible<bksge::pair<int,      Explicit>, int      const&, Explicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::pair<Implicit, int>,      Implicit const&, int      const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::pair<int,      Implicit>, int      const&, Implicit const&>::value, "");
static_assert( bksge::is_nothrow_constructible<bksge::pair<int,      int>,      int      const&, int      const&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	{
		int const x1 = 1;
		int const x2 = 2;
		bksge::pair<int, int> p(x1, x2);
		VERIFY(p.first  == 1);
		VERIFY(p.second == 2);
	}
	{
		int const x1 = 3;
		int const x2 = 4;
		bksge::pair<int, int> p{x1, x2};
		VERIFY(p.first  == 3);
		VERIFY(p.second == 4);
	}
	{
		int const x1 = 5;
		int const x2 = 6;
		bksge::pair<int, int> p = {x1, x2};
		VERIFY(p.first  == 5);
		VERIFY(p.second == 6);
	}
	{
		Explicit const x1(1);
		Explicit const x2(2);
		bksge::pair<Explicit, Explicit> p(x1, x2);
		VERIFY(p.first.n  == 1);
		VERIFY(p.second.n == 2);
	}
	{
		Explicit const x1(3);
		Implicit const x2(4);
		bksge::pair<Explicit, Implicit> p{x1, x2};
		VERIFY(p.first.n  == 3);
		VERIFY(p.second.n == 4);
	}
	{
		Implicit const x1(5);
		Explicit const x2(6);
		bksge::pair<Implicit, Explicit> p{x1, x2};
		VERIFY(p.first.n  == 5);
		VERIFY(p.second.n == 6);
	}
	{
		Implicit const x1(7);
		Implicit const x2(8);
		bksge::pair<Implicit, Implicit> p = {x1, x2};
		VERIFY(p.first.n  == 7);
		VERIFY(p.second.n == 8);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, CtorValueCopyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace ctor_value_copy_test

}	// namespace bksge_pair_test
