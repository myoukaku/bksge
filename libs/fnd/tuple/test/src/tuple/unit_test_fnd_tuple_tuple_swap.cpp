/**
 *	@file	unit_test_fnd_tuple_tuple_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/type_traits/is_swappable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_swappable.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_tuple_test
{

namespace swap_test
{

struct ThrowOnMove
{
	BKSGE_CONSTEXPR ThrowOnMove(int)                           noexcept(true)  : n() {}
	BKSGE_CONSTEXPR ThrowOnMove(ThrowOnMove const&)            noexcept(true)  : n() {}
	BKSGE_CONSTEXPR ThrowOnMove(ThrowOnMove&&)                 noexcept(false) : n() {}
	BKSGE_CONSTEXPR ThrowOnMove& operator=(ThrowOnMove const&) noexcept(true)  {return *this;}
	BKSGE_CONSTEXPR ThrowOnMove& operator=(ThrowOnMove&&)      noexcept(false) {return *this;}
	int n;
};

struct NothrowOnMove
{
	BKSGE_CONSTEXPR NothrowOnMove(int x)                           noexcept(true) : n(x) {}
	BKSGE_CONSTEXPR NothrowOnMove(NothrowOnMove const&)            noexcept(true) = default;
	BKSGE_CONSTEXPR NothrowOnMove(NothrowOnMove&&)                 noexcept(true) = default;
	BKSGE_CONSTEXPR NothrowOnMove& operator=(NothrowOnMove const&) noexcept(true) = default;
	BKSGE_CONSTEXPR NothrowOnMove& operator=(NothrowOnMove&&)      noexcept(true) = default;
	int n;
};

struct NonMovable
{
	BKSGE_CONSTEXPR NonMovable(int x)                        noexcept(true) : n(x) {}
	BKSGE_CONSTEXPR NonMovable(NonMovable const&)            noexcept(true) = delete;
	BKSGE_CONSTEXPR NonMovable(NonMovable&&)                 noexcept(true) = delete;
	BKSGE_CONSTEXPR NonMovable& operator=(NonMovable const&) noexcept(true) = delete;
	BKSGE_CONSTEXPR NonMovable& operator=(NonMovable&&)      noexcept(true) = delete;
	int n;
};

static_assert( bksge::is_swappable<bksge::tuple<>>::value, "");
static_assert( bksge::is_swappable<bksge::tuple<int>>::value, "");
static_assert( bksge::is_swappable<bksge::tuple<int, int>>::value, "");
static_assert( bksge::is_swappable<bksge::tuple<int, int, int>>::value, "");
static_assert( bksge::is_swappable<bksge::tuple<ThrowOnMove>>::value, "");
static_assert( bksge::is_swappable<bksge::tuple<NothrowOnMove>>::value, "");
static_assert(!bksge::is_swappable<bksge::tuple<NonMovable>>::value, "");
static_assert( bksge::is_swappable<bksge::tuple<ThrowOnMove, ThrowOnMove>>::value, "");
static_assert( bksge::is_swappable<bksge::tuple<ThrowOnMove, NothrowOnMove>>::value, "");
static_assert(!bksge::is_swappable<bksge::tuple<ThrowOnMove, NonMovable>>::value, "");
static_assert( bksge::is_swappable<bksge::tuple<NothrowOnMove, ThrowOnMove>>::value, "");
static_assert( bksge::is_swappable<bksge::tuple<NothrowOnMove, NothrowOnMove>>::value, "");
static_assert(!bksge::is_swappable<bksge::tuple<NothrowOnMove, NonMovable>>::value, "");
static_assert(!bksge::is_swappable<bksge::tuple<NonMovable, ThrowOnMove>>::value, "");
static_assert(!bksge::is_swappable<bksge::tuple<NonMovable, NothrowOnMove>>::value, "");
static_assert(!bksge::is_swappable<bksge::tuple<NonMovable, NonMovable>>::value, "");
static_assert( bksge::is_swappable<bksge::tuple<NothrowOnMove, NothrowOnMove, NothrowOnMove>>::value, "");
static_assert( bksge::is_swappable<bksge::tuple<ThrowOnMove,   NothrowOnMove, NothrowOnMove>>::value, "");
static_assert( bksge::is_swappable<bksge::tuple<NothrowOnMove, ThrowOnMove,   NothrowOnMove>>::value, "");
static_assert( bksge::is_swappable<bksge::tuple<NothrowOnMove, NothrowOnMove, ThrowOnMove>>::value, "");
static_assert(!bksge::is_swappable<bksge::tuple<NonMovable,   NothrowOnMove, NothrowOnMove>>::value, "");
static_assert(!bksge::is_swappable<bksge::tuple<NothrowOnMove, NonMovable,   NothrowOnMove>>::value, "");
static_assert(!bksge::is_swappable<bksge::tuple<NothrowOnMove, NothrowOnMove, NonMovable>>::value, "");

static_assert( bksge::is_nothrow_swappable<bksge::tuple<>>::value, "");
static_assert( bksge::is_nothrow_swappable<bksge::tuple<int>>::value, "");
static_assert( bksge::is_nothrow_swappable<bksge::tuple<int, int>>::value, "");
static_assert( bksge::is_nothrow_swappable<bksge::tuple<int, int, int>>::value, "");
static_assert(!bksge::is_nothrow_swappable<bksge::tuple<ThrowOnMove>>::value, "");
static_assert( bksge::is_nothrow_swappable<bksge::tuple<NothrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_swappable<bksge::tuple<NonMovable>>::value, "");
static_assert(!bksge::is_nothrow_swappable<bksge::tuple<ThrowOnMove, ThrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_swappable<bksge::tuple<ThrowOnMove, NothrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_swappable<bksge::tuple<ThrowOnMove, NonMovable>>::value, "");
static_assert(!bksge::is_nothrow_swappable<bksge::tuple<NothrowOnMove, ThrowOnMove>>::value, "");
static_assert( bksge::is_nothrow_swappable<bksge::tuple<NothrowOnMove, NothrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_swappable<bksge::tuple<NothrowOnMove, NonMovable>>::value, "");
static_assert(!bksge::is_nothrow_swappable<bksge::tuple<NonMovable, ThrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_swappable<bksge::tuple<NonMovable, NothrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_swappable<bksge::tuple<NonMovable, NonMovable>>::value, "");
static_assert( bksge::is_nothrow_swappable<bksge::tuple<NothrowOnMove, NothrowOnMove, NothrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_swappable<bksge::tuple<ThrowOnMove,   NothrowOnMove, NothrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_swappable<bksge::tuple<NothrowOnMove, ThrowOnMove,   NothrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_swappable<bksge::tuple<NothrowOnMove, NothrowOnMove, ThrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_swappable<bksge::tuple<NonMovable,    NothrowOnMove, NothrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_swappable<bksge::tuple<NothrowOnMove, NonMovable,    NothrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_swappable<bksge::tuple<NothrowOnMove, NothrowOnMove, NonMovable>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	using std::get;
	{
		bksge::tuple<int> t1(1);
		bksge::tuple<int> t2(2);
		VERIFY(get<0>(t1) == 1);
		VERIFY(get<0>(t2) == 2);
		t1.swap(t2);
		VERIFY(get<0>(t1) == 2);
		VERIFY(get<0>(t2) == 1);
		swap(t1, t2);
		VERIFY(get<0>(t1) == 1);
		VERIFY(get<0>(t2) == 2);
	}
	{
		bksge::tuple<int, int> t1(2, 3);
		bksge::tuple<int, int> t2(4, 5);
		VERIFY(get<0>(t1) == 2);
		VERIFY(get<1>(t1) == 3);
		VERIFY(get<0>(t2) == 4);
		VERIFY(get<1>(t2) == 5);
		t1.swap(t2);
		VERIFY(get<0>(t1) == 4);
		VERIFY(get<1>(t1) == 5);
		VERIFY(get<0>(t2) == 2);
		VERIFY(get<1>(t2) == 3);
		swap(t1, t2);
		VERIFY(get<0>(t1) == 2);
		VERIFY(get<1>(t1) == 3);
		VERIFY(get<0>(t2) == 4);
		VERIFY(get<1>(t2) == 5);
	}
	{
		bksge::tuple<int, float, char> t1(3, 0.5f, 'A');
		bksge::tuple<int, float, char> t2(4, 2.5f, 'B');
		VERIFY(get<0>(t1) == 3);
		VERIFY(get<1>(t1) == 0.5f);
		VERIFY(get<2>(t1) == 'A');
		VERIFY(get<0>(t2) == 4);
		VERIFY(get<1>(t2) == 2.5f);
		VERIFY(get<2>(t2) == 'B');
		t1.swap(t2);
		VERIFY(get<0>(t1) == 4);
		VERIFY(get<1>(t1) == 2.5f);
		VERIFY(get<2>(t1) == 'B');
		VERIFY(get<0>(t2) == 3);
		VERIFY(get<1>(t2) == 0.5f);
		VERIFY(get<2>(t2) == 'A');
		swap(t1, t2);
		VERIFY(get<0>(t1) == 3);
		VERIFY(get<1>(t1) == 0.5f);
		VERIFY(get<2>(t1) == 'A');
		VERIFY(get<0>(t2) == 4);
		VERIFY(get<1>(t2) == 2.5f);
		VERIFY(get<2>(t2) == 'B');
	}
	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, SwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace swap_test

}	// namespace bksge_tuple_test
