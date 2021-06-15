/**
 *	@file	unit_test_fnd_tuple_tuple_assign_move.cpp
 *
 *	@brief	operator=(tuple<UTypes...> &&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/type_traits/is_assignable.hpp>
#include <bksge/fnd/type_traits/is_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_assignable.hpp>
#include <bksge/fnd/utility/pair.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4244);

namespace bksge_tuple_test
{

namespace assign_move_test
{

struct ThrowOnMove
{
	BKSGE_CONSTEXPR ThrowOnMove(int)                           noexcept(true)  {}
	BKSGE_CONSTEXPR ThrowOnMove(ThrowOnMove const&)            noexcept(true)  {}
	BKSGE_CONSTEXPR ThrowOnMove(ThrowOnMove&&)                 noexcept(false) {}
	BKSGE_CONSTEXPR ThrowOnMove& operator=(ThrowOnMove const&) noexcept(true)  { return *this; }
	BKSGE_CONSTEXPR ThrowOnMove& operator=(ThrowOnMove&&)      noexcept(false) { return *this; }
	int n = 0;
};

struct NothrowOnMove
{
	BKSGE_CONSTEXPR NothrowOnMove(int)                             noexcept(true) {}
	BKSGE_CONSTEXPR NothrowOnMove(NothrowOnMove const&)            noexcept(true) {}
	BKSGE_CONSTEXPR NothrowOnMove(NothrowOnMove&&)                 noexcept(true) {}
	BKSGE_CONSTEXPR NothrowOnMove& operator=(NothrowOnMove const&) noexcept(true) { return *this; }
	BKSGE_CONSTEXPR NothrowOnMove& operator=(NothrowOnMove&&)      noexcept(true) { return *this; }
	int n = 0;
};

struct NonMovable
{
	BKSGE_CONSTEXPR NonMovable(int)                          noexcept(true) {}
	BKSGE_CONSTEXPR NonMovable(NonMovable const&)            noexcept(true) = delete;
	BKSGE_CONSTEXPR NonMovable(NonMovable&&)                 noexcept(true) = delete;
	BKSGE_CONSTEXPR NonMovable& operator=(NonMovable const&) noexcept(true) = delete;
	BKSGE_CONSTEXPR NonMovable& operator=(NonMovable&&)      noexcept(true) = delete;
	int n = 0;
};

struct Empty {};

static_assert( bksge::is_move_assignable<bksge::tuple<>>::value, "");
static_assert( bksge::is_move_assignable<bksge::tuple<int>>::value, "");
static_assert( bksge::is_move_assignable<bksge::tuple<int, int>>::value, "");
static_assert( bksge::is_move_assignable<bksge::tuple<int, int, int>>::value, "");
static_assert( bksge::is_move_assignable<bksge::tuple<ThrowOnMove>>::value, "");
static_assert( bksge::is_move_assignable<bksge::tuple<NothrowOnMove>>::value, "");
static_assert(!bksge::is_move_assignable<bksge::tuple<NonMovable>>::value, "");
static_assert( bksge::is_move_assignable<bksge::tuple<ThrowOnMove, ThrowOnMove>>::value, "");
static_assert( bksge::is_move_assignable<bksge::tuple<ThrowOnMove, NothrowOnMove>>::value, "");
static_assert(!bksge::is_move_assignable<bksge::tuple<ThrowOnMove, NonMovable>>::value, "");
static_assert( bksge::is_move_assignable<bksge::tuple<NothrowOnMove, ThrowOnMove>>::value, "");
static_assert( bksge::is_move_assignable<bksge::tuple<NothrowOnMove, NothrowOnMove>>::value, "");
static_assert(!bksge::is_move_assignable<bksge::tuple<NothrowOnMove, NonMovable>>::value, "");
static_assert(!bksge::is_move_assignable<bksge::tuple<NonMovable, ThrowOnMove>>::value, "");
static_assert(!bksge::is_move_assignable<bksge::tuple<NonMovable, NothrowOnMove>>::value, "");
static_assert(!bksge::is_move_assignable<bksge::tuple<NonMovable, NonMovable>>::value, "");
static_assert( bksge::is_move_assignable<bksge::tuple<NothrowOnMove, NothrowOnMove, NothrowOnMove>>::value, "");
static_assert( bksge::is_move_assignable<bksge::tuple<ThrowOnMove,   NothrowOnMove, NothrowOnMove>>::value, "");
static_assert( bksge::is_move_assignable<bksge::tuple<NothrowOnMove, ThrowOnMove,   NothrowOnMove>>::value, "");
static_assert( bksge::is_move_assignable<bksge::tuple<NothrowOnMove, NothrowOnMove, ThrowOnMove>>::value, "");
static_assert(!bksge::is_move_assignable<bksge::tuple<NonMovable,   NothrowOnMove, NothrowOnMove>>::value, "");
static_assert(!bksge::is_move_assignable<bksge::tuple<NothrowOnMove, NonMovable,   NothrowOnMove>>::value, "");
static_assert(!bksge::is_move_assignable<bksge::tuple<NothrowOnMove, NothrowOnMove, NonMovable>>::value, "");
static_assert( bksge::is_assignable<bksge::tuple<ThrowOnMove>,   bksge::tuple<int>&&>::value, "");
static_assert( bksge::is_assignable<bksge::tuple<NothrowOnMove>, bksge::tuple<int>&&>::value, "");
static_assert(!bksge::is_assignable<bksge::tuple<NonMovable>,    bksge::tuple<int>&&>::value, "");
static_assert(!bksge::is_assignable<bksge::tuple<ThrowOnMove>,   bksge::tuple<NothrowOnMove>&&>::value, "");
static_assert( bksge::is_assignable<bksge::tuple<int, int>, bksge::pair<int, int>&&>::value, "");
static_assert( bksge::is_assignable<bksge::tuple<ThrowOnMove, ThrowOnMove>,   bksge::pair<ThrowOnMove, ThrowOnMove>&&>::value, "");
static_assert( bksge::is_assignable<bksge::tuple<ThrowOnMove, NothrowOnMove>, bksge::pair<ThrowOnMove, NothrowOnMove>&&>::value, "");
static_assert(!bksge::is_assignable<bksge::tuple<ThrowOnMove, NonMovable>,   bksge::pair<ThrowOnMove, NonMovable>&&>::value, "");
static_assert( bksge::is_assignable<bksge::tuple<NothrowOnMove, ThrowOnMove>,   bksge::pair<NothrowOnMove, ThrowOnMove>&&>::value, "");
static_assert( bksge::is_assignable<bksge::tuple<NothrowOnMove, NothrowOnMove>, bksge::pair<NothrowOnMove, NothrowOnMove>&&>::value, "");
static_assert(!bksge::is_assignable<bksge::tuple<NothrowOnMove, NonMovable>,   bksge::pair<NothrowOnMove, NonMovable>&&>::value, "");

static_assert( bksge::is_nothrow_move_assignable<bksge::tuple<>>::value, "");
static_assert( bksge::is_nothrow_move_assignable<bksge::tuple<int>>::value, "");
static_assert( bksge::is_nothrow_move_assignable<bksge::tuple<int, int>>::value, "");
static_assert( bksge::is_nothrow_move_assignable<bksge::tuple<int, int, int>>::value, "");
static_assert(!bksge::is_nothrow_move_assignable<bksge::tuple<ThrowOnMove>>::value, "");
static_assert( bksge::is_nothrow_move_assignable<bksge::tuple<NothrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_move_assignable<bksge::tuple<NonMovable>>::value, "");
static_assert(!bksge::is_nothrow_move_assignable<bksge::tuple<ThrowOnMove, ThrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_move_assignable<bksge::tuple<ThrowOnMove, NothrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_move_assignable<bksge::tuple<ThrowOnMove, NonMovable>>::value, "");
static_assert(!bksge::is_nothrow_move_assignable<bksge::tuple<NothrowOnMove, ThrowOnMove>>::value, "");
static_assert( bksge::is_nothrow_move_assignable<bksge::tuple<NothrowOnMove, NothrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_move_assignable<bksge::tuple<NothrowOnMove, NonMovable>>::value, "");
static_assert(!bksge::is_nothrow_move_assignable<bksge::tuple<NonMovable, ThrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_move_assignable<bksge::tuple<NonMovable, NothrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_move_assignable<bksge::tuple<NonMovable, NonMovable>>::value, "");
static_assert( bksge::is_nothrow_move_assignable<bksge::tuple<NothrowOnMove, NothrowOnMove, NothrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_move_assignable<bksge::tuple<ThrowOnMove,   NothrowOnMove, NothrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_move_assignable<bksge::tuple<NothrowOnMove, ThrowOnMove,   NothrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_move_assignable<bksge::tuple<NothrowOnMove, NothrowOnMove, ThrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_move_assignable<bksge::tuple<NonMovable,    NothrowOnMove, NothrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_move_assignable<bksge::tuple<NothrowOnMove, NonMovable,    NothrowOnMove>>::value, "");
static_assert(!bksge::is_nothrow_move_assignable<bksge::tuple<NothrowOnMove, NothrowOnMove, NonMovable>>::value, "");
static_assert(!bksge::is_nothrow_assignable<bksge::tuple<ThrowOnMove>,   bksge::tuple<int>&&>::value, "");
static_assert( bksge::is_nothrow_assignable<bksge::tuple<NothrowOnMove>, bksge::tuple<int>&&>::value, "");
static_assert(!bksge::is_nothrow_assignable<bksge::tuple<NonMovable>,    bksge::tuple<int>&&>::value, "");
static_assert(!bksge::is_nothrow_assignable<bksge::tuple<ThrowOnMove>,   bksge::tuple<NothrowOnMove>&&>::value, "");
static_assert( bksge::is_nothrow_assignable<bksge::tuple<int, int>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_assignable<bksge::tuple<ThrowOnMove, ThrowOnMove>,   bksge::pair<ThrowOnMove, ThrowOnMove>&&>::value, "");
static_assert(!bksge::is_nothrow_assignable<bksge::tuple<ThrowOnMove, NothrowOnMove>, bksge::pair<ThrowOnMove, NothrowOnMove>&&>::value, "");
static_assert(!bksge::is_nothrow_assignable<bksge::tuple<ThrowOnMove, NonMovable>,    bksge::pair<ThrowOnMove, NonMovable>&&>::value, "");
static_assert(!bksge::is_nothrow_assignable<bksge::tuple<NothrowOnMove, ThrowOnMove>,   bksge::pair<NothrowOnMove, ThrowOnMove>&&>::value, "");
static_assert( bksge::is_nothrow_assignable<bksge::tuple<NothrowOnMove, NothrowOnMove>, bksge::pair<NothrowOnMove, NothrowOnMove>&&>::value, "");
static_assert(!bksge::is_nothrow_assignable<bksge::tuple<NothrowOnMove, NonMovable>,    bksge::pair<NothrowOnMove, NonMovable>&&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	using std::get;
	{
		bksge::tuple<Empty> t1;
		bksge::tuple<Empty> t2;
		t2 = bksge::move(t1);
	}
	{
		bksge::tuple<Empty, Empty> t1;
		bksge::tuple<Empty, Empty> t2;
		t2 = bksge::move(t1);
	}
	{
		bksge::tuple<Empty, Empty, Empty> t1;
		bksge::tuple<Empty, Empty, Empty> t2;
		t2 = bksge::move(t1);
	}
	{
		bksge::tuple<int> t1(1);
		bksge::tuple<int> t2(2);
		VERIFY(get<0>(t2) == 2);
		t2 = bksge::move(t1);
		VERIFY(get<0>(t2) == 1);
	}
	{
		bksge::tuple<float>  t1(1);
		bksge::tuple<double> t2(2);
		VERIFY(get<0>(t2) == 2);
		t2 = bksge::move(t1);
		VERIFY(get<0>(t2) == 1);
	}
	{
		bksge::tuple<int, float> t1(2, 0.5f);
		bksge::tuple<int, float> t2(3, 4.5f);
		VERIFY(get<0>(t2) == 3);
		VERIFY(get<1>(t2) == 4.5f);
		t2 = bksge::move(t1);
		VERIFY(get<0>(t2) == 2);
		VERIFY(get<1>(t2) == 0.5f);
	}
	{
		bksge::tuple<int, float>   t1(2, 0.5f);
		bksge::tuple<long, double> t2(3, 4.5f);
		VERIFY(get<0>(t2) == 3);
		VERIFY(get<1>(t2) == 4.5f);
		t2 = bksge::move(t1);
		VERIFY(get<0>(t2) == 2);
		VERIFY(get<1>(t2) == 0.5f);
	}
	{
		bksge::pair<int, float>  t1(2, 0.5f);
		bksge::tuple<int, float> t2(3, 4.5f);
		VERIFY(get<0>(t2) == 3);
		VERIFY(get<1>(t2) == 4.5f);
		t2 = bksge::move(t1);
		VERIFY(get<0>(t2) == 2);
		VERIFY(get<1>(t2) == 0.5f);
	}
	{
		bksge::pair<int, float>    t1(2, 0.5f);
		bksge::tuple<long, double> t2(3, 4.5f);
		VERIFY(get<0>(t2) == 3);
		VERIFY(get<1>(t2) == 4.5f);
		t2 = bksge::move(t1);
		VERIFY(get<0>(t2) == 2);
		VERIFY(get<1>(t2) == 0.5f);
	}
	{
		bksge::tuple<int, float, char> t1(2, 0.5f, 'a');
		bksge::tuple<int, float, char> t2(3, 4.5f, 'b');
		VERIFY(get<0>(t2) == 3);
		VERIFY(get<1>(t2) == 4.5f);
		VERIFY(get<2>(t2) == 'b');
		t2 = bksge::move(t1);
		VERIFY(get<0>(t2) == 2);
		VERIFY(get<1>(t2) == 0.5f);
		VERIFY(get<2>(t2) == 'a');
	}
	{
		bksge::tuple<int, float, char>   t1(2, 0.5f, 'a');
		bksge::tuple<long, double, char> t2(3, 4.5f, 'b');
		VERIFY(get<0>(t2) == 3);
		VERIFY(get<1>(t2) == 4.5f);
		VERIFY(get<2>(t2) == 'b');
		t2 = bksge::move(t1);
		VERIFY(get<0>(t2) == 2);
		VERIFY(get<1>(t2) == 0.5f);
		VERIFY(get<2>(t2) == 'a');
	}
	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, AssignMoveTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_move_test

}	// namespace bksge_tuple_test

BKSGE_WARNING_POP();
