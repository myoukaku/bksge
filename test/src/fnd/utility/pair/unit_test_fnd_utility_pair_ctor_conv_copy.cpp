/**
 *	@file	unit_test_fnd_utility_pair_ctor_conv_copy.cpp
 *
 *	@brief	pair::pair(pair<U1, U2> const&) のテスト
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

namespace ctor_conv_copy_test
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

static_assert( bksge::is_constructible<bksge::pair<short, float>, bksge::pair<int, double> const&>::value, "");
static_assert( bksge::is_constructible<bksge::pair<Explicit, Explicit>, bksge::pair<int, int> const&>::value, "");
static_assert( bksge::is_constructible<bksge::pair<Explicit, Implicit>, bksge::pair<int, int> const&>::value, "");
static_assert( bksge::is_constructible<bksge::pair<Implicit, Explicit>, bksge::pair<int, int> const&>::value, "");
static_assert( bksge::is_constructible<bksge::pair<Implicit, Implicit>, bksge::pair<int, int> const&>::value, "");

static_assert( bksge::is_implicitly_constructible<bksge::pair<short, float>, bksge::pair<int, double> const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::pair<Explicit, Explicit>, bksge::pair<int, int> const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::pair<Explicit, Implicit>, bksge::pair<int, int> const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::pair<Implicit, Explicit>, bksge::pair<int, int> const&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::pair<Implicit, Implicit>, bksge::pair<int, int> const&>::value, "");

static_assert( bksge::is_nothrow_constructible<bksge::pair<short, float>, bksge::pair<int, double> const&>::value, "");
static_assert( bksge::is_nothrow_constructible<bksge::pair<Explicit, Explicit>, bksge::pair<int, int> const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::pair<Explicit, Implicit>, bksge::pair<int, int> const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::pair<Implicit, Explicit>, bksge::pair<int, int> const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::pair<Implicit, Implicit>, bksge::pair<int, int> const&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	{
		bksge::pair<short, float> const p1(1, 2);
		bksge::pair<int, double>  const p2(p1);
		VERIFY(p2.first  == 1);
		VERIFY(p2.second == 2.0f);
	}
	{
		bksge::pair<int, int>           const p1(3, 4);
		bksge::pair<Explicit, Explicit> const p2(p1);
		VERIFY(p2.first.n  == 3);
		VERIFY(p2.second.n == 4);
	}
	{
		bksge::pair<int, int>           const p1(5, 6);
		bksge::pair<Explicit, Implicit> const p2(p1);
		VERIFY(p2.first.n  == 5);
		VERIFY(p2.second.n == 6);
	}
	{
		bksge::pair<int, int>           const p1(7, 8);
		bksge::pair<Implicit, Explicit> const p2 {p1};
		VERIFY(p2.first.n  == 7);
		VERIFY(p2.second.n == 8);
	}
	{
		bksge::pair<int, int>           const p1(9, 10);
		bksge::pair<Implicit, Implicit> const p2 = {p1};
		VERIFY(p2.first.n  == 9);
		VERIFY(p2.second.n == 10);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, CtorConvCopyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace ctor_conv_copy_test

}	// namespace bksge_pair_test
