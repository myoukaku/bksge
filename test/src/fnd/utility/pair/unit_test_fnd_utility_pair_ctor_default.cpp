/**
 *	@file	unit_test_fnd_utility_pair_ctor_default.cpp
 *
 *	@brief	pair::pair() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/pair.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_pair_test
{

namespace ctor_default_test
{

struct Explicit
{
	explicit BKSGE_CONSTEXPR Explicit() noexcept : n(1) {}
	int n;
};

struct Implicit
{
	BKSGE_CONSTEXPR Implicit() : n(2) {}
	int n;
};

static_assert( bksge::is_default_constructible<bksge::pair<Explicit, Explicit>>::value, "");
static_assert( bksge::is_default_constructible<bksge::pair<Explicit, Implicit>>::value, "");
static_assert( bksge::is_default_constructible<bksge::pair<Implicit, Explicit>>::value, "");
static_assert( bksge::is_default_constructible<bksge::pair<Implicit, Implicit>>::value, "");

static_assert(!bksge::is_implicitly_default_constructible<bksge::pair<Explicit, Explicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::pair<Explicit, Implicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::pair<Implicit, Explicit>>::value, "");
static_assert( bksge::is_implicitly_default_constructible<bksge::pair<Implicit, Implicit>>::value, "");

static_assert(!bksge::is_implicitly_default_constructible<bksge::pair<Explicit, int>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::pair<int, Explicit>>::value, "");
static_assert( bksge::is_implicitly_default_constructible<bksge::pair<Implicit, int>>::value, "");
static_assert( bksge::is_implicitly_default_constructible<bksge::pair<int, Implicit>>::value, "");
static_assert( bksge::is_implicitly_default_constructible<bksge::pair<int, int>>::value, "");

static_assert( bksge::is_nothrow_default_constructible<bksge::pair<Explicit, Explicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::pair<Explicit, Implicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::pair<Implicit, Explicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::pair<Implicit, Implicit>>::value, "");

static_assert( bksge::is_nothrow_default_constructible<bksge::pair<Explicit, int>>::value, "");
static_assert( bksge::is_nothrow_default_constructible<bksge::pair<int, Explicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::pair<Implicit, int>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::pair<int, Implicit>>::value, "");
static_assert( bksge::is_nothrow_default_constructible<bksge::pair<int, int>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	{
		bksge::pair<int, int> p;
		VERIFY(p.first  == 0);
		VERIFY(p.second == 0);
	}
	{
		bksge::pair<int, int> p{};
		VERIFY(p.first  == 0);
		VERIFY(p.second == 0);
	}
	{
		bksge::pair<int, int> p = {};
		VERIFY(p.first  == 0);
		VERIFY(p.second == 0);
	}
	{
		bksge::pair<Explicit, Explicit> p;
		VERIFY(p.first.n  == 1);
		VERIFY(p.second.n == 1);
	}
	{
		bksge::pair<Explicit, Implicit> p{};
		VERIFY(p.first.n  == 1);
		VERIFY(p.second.n == 2);
	}
	{
		bksge::pair<Implicit, Explicit> p;
		VERIFY(p.first.n  == 2);
		VERIFY(p.second.n == 1);
	}
	{
		bksge::pair<Implicit, Implicit> p = {};
		VERIFY(p.first.n  == 2);
		VERIFY(p.second.n == 2);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, CtorDefaultTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace ctor_default_test

}	// namespace bksge_pair_test
