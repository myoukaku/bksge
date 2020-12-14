/**
 *	@file	unit_test_fnd_tuple_tuple_ctor_default.cpp
 *
 *	@brief	tuple::tuple() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_tuple_test
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

struct NoDefault
{
	BKSGE_CONSTEXPR NoDefault(int x) : n(x) {}
	int n;
};

static_assert( bksge::is_default_constructible<bksge::tuple<>>::value, "");
static_assert( bksge::is_default_constructible<bksge::tuple<Explicit>>::value, "");
static_assert( bksge::is_default_constructible<bksge::tuple<Implicit>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<NoDefault>>::value, "");
static_assert( bksge::is_default_constructible<bksge::tuple<Explicit, Explicit>>::value, "");
static_assert( bksge::is_default_constructible<bksge::tuple<Explicit, Implicit>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<Explicit, NoDefault>>::value, "");
static_assert( bksge::is_default_constructible<bksge::tuple<Implicit, Explicit>>::value, "");
static_assert( bksge::is_default_constructible<bksge::tuple<Implicit, Implicit>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<Implicit, NoDefault>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<NoDefault, Explicit>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<NoDefault, Implicit>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<NoDefault, NoDefault>>::value, "");
static_assert( bksge::is_default_constructible<bksge::tuple<Explicit, Explicit, Explicit>>::value, "");
static_assert( bksge::is_default_constructible<bksge::tuple<Explicit, Explicit, Implicit>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<Explicit, Explicit, NoDefault>>::value, "");
static_assert( bksge::is_default_constructible<bksge::tuple<Explicit, Implicit, Explicit>>::value, "");
static_assert( bksge::is_default_constructible<bksge::tuple<Explicit, Implicit, Implicit>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<Explicit, Implicit, NoDefault>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<Explicit, NoDefault, Explicit>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<Explicit, NoDefault, Implicit>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<Explicit, NoDefault, NoDefault>>::value, "");
static_assert( bksge::is_default_constructible<bksge::tuple<Implicit, Explicit, Explicit>>::value, "");
static_assert( bksge::is_default_constructible<bksge::tuple<Implicit, Explicit, Implicit>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<Implicit, Explicit, NoDefault>>::value, "");
static_assert( bksge::is_default_constructible<bksge::tuple<Implicit, Implicit, Explicit>>::value, "");
static_assert( bksge::is_default_constructible<bksge::tuple<Implicit, Implicit, Implicit>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<Implicit, Implicit, NoDefault>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<Implicit, NoDefault, Explicit>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<Implicit, NoDefault, Implicit>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<Implicit, NoDefault, NoDefault>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<NoDefault, Explicit, Explicit>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<NoDefault, Explicit, Implicit>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<NoDefault, Explicit, NoDefault>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<NoDefault, Implicit, Explicit>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<NoDefault, Implicit, Implicit>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<NoDefault, Implicit, NoDefault>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<NoDefault, NoDefault, Explicit>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<NoDefault, NoDefault, Implicit>>::value, "");
static_assert(!bksge::is_default_constructible<bksge::tuple<NoDefault, NoDefault, NoDefault>>::value, "");

static_assert( bksge::is_implicitly_default_constructible<bksge::tuple<>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Explicit>>::value, "");
static_assert( bksge::is_implicitly_default_constructible<bksge::tuple<Implicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<NoDefault>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Explicit, Explicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Explicit, Implicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Explicit, NoDefault>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Implicit, Explicit>>::value, "");
static_assert( bksge::is_implicitly_default_constructible<bksge::tuple<Implicit, Implicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Implicit, NoDefault>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<NoDefault, Explicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<NoDefault, Implicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<NoDefault, NoDefault>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Explicit, Explicit, Explicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Explicit, Explicit, Implicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Explicit, Explicit, NoDefault>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Explicit, Implicit, Explicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Explicit, Implicit, Implicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Explicit, Implicit, NoDefault>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Explicit, NoDefault, Explicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Explicit, NoDefault, Implicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Explicit, NoDefault, NoDefault>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Implicit, Explicit, Explicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Implicit, Explicit, Implicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Implicit, Explicit, NoDefault>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Implicit, Implicit, Explicit>>::value, "");
static_assert( bksge::is_implicitly_default_constructible<bksge::tuple<Implicit, Implicit, Implicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Implicit, Implicit, NoDefault>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Implicit, NoDefault, Explicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Implicit, NoDefault, Implicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<Implicit, NoDefault, NoDefault>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<NoDefault, Explicit, Explicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<NoDefault, Explicit, Implicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<NoDefault, Explicit, NoDefault>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<NoDefault, Implicit, Explicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<NoDefault, Implicit, Implicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<NoDefault, Implicit, NoDefault>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<NoDefault, NoDefault, Explicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<NoDefault, NoDefault, Implicit>>::value, "");
static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<NoDefault, NoDefault, NoDefault>>::value, "");

static_assert( bksge::is_nothrow_default_constructible<bksge::tuple<>>::value, "");
static_assert( bksge::is_nothrow_default_constructible<bksge::tuple<Explicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Implicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<NoDefault>>::value, "");
static_assert( bksge::is_nothrow_default_constructible<bksge::tuple<Explicit, Explicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Explicit, Implicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Explicit, NoDefault>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Implicit, Explicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Implicit, Implicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Implicit, NoDefault>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<NoDefault, Explicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<NoDefault, Implicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<NoDefault, NoDefault>>::value, "");
static_assert( bksge::is_nothrow_default_constructible<bksge::tuple<Explicit, Explicit, Explicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Explicit, Explicit, Implicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Explicit, Explicit, NoDefault>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Explicit, Implicit, Explicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Explicit, Implicit, Implicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Explicit, Implicit, NoDefault>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Explicit, NoDefault, Explicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Explicit, NoDefault, Implicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Explicit, NoDefault, NoDefault>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Implicit, Explicit, Explicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Implicit, Explicit, Implicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Implicit, Explicit, NoDefault>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Implicit, Implicit, Explicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Implicit, Implicit, Implicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Implicit, Implicit, NoDefault>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Implicit, NoDefault, Explicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Implicit, NoDefault, Implicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<Implicit, NoDefault, NoDefault>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<NoDefault, Explicit, Explicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<NoDefault, Explicit, Implicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<NoDefault, Explicit, NoDefault>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<NoDefault, Implicit, Explicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<NoDefault, Implicit, Implicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<NoDefault, Implicit, NoDefault>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<NoDefault, NoDefault, Explicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<NoDefault, NoDefault, Implicit>>::value, "");
static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<NoDefault, NoDefault, NoDefault>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	using std::get;
	{
		bksge::tuple<> t;
		(void)t;
	}
	{
		bksge::tuple<int> t{};
		VERIFY(get<0>(t) == 0);
	}
	{
		bksge::tuple<float, int> t = {};
		VERIFY(get<0>(t) == 0.0f);
		VERIFY(get<1>(t) == 0);
	}
	{
		bksge::tuple<float, char, int> t{};
		VERIFY(get<0>(t) == 0.0f);
		VERIFY(get<1>(t) == 0);
		VERIFY(get<2>(t) == 0);
	}
	{
		bksge::tuple<Explicit, Explicit, Explicit> t;
		VERIFY(get<0>(t).n == 1);
		VERIFY(get<1>(t).n == 1);
		VERIFY(get<2>(t).n == 1);
	}
	{
		bksge::tuple<Implicit, Explicit, Implicit> t{};
		VERIFY(get<0>(t).n == 2);
		VERIFY(get<1>(t).n == 1);
		VERIFY(get<2>(t).n == 2);
	}
	{
		bksge::tuple<Implicit, Implicit, Implicit> t = {};
		VERIFY(get<0>(t).n == 2);
		VERIFY(get<1>(t).n == 2);
		VERIFY(get<2>(t).n == 2);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, CtorDefaultTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace ctor_default_test

}	// namespace bksge_tuple_test
