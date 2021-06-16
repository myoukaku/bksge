/**
 *	@file	unit_test_fnd_utility_pair_ctor_move.cpp
 *
 *	@brief	pair::pair(pair&&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/pair.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_pair_test
{

namespace ctor_move_test
{

struct NoexceptMove
{
	NoexceptMove(NoexceptMove&&) noexcept(true);
	NoexceptMove& operator=(NoexceptMove&&) = default;
};

struct ExceptMove
{
	ExceptMove(ExceptMove&&) noexcept(false);
};

typedef bksge::pair<int, int>                   tt1;
typedef bksge::pair<int, double>                tt2;
typedef bksge::pair<NoexceptMove, NoexceptMove> tt3;
typedef bksge::pair<ExceptMove, ExceptMove>     tt4;
typedef bksge::pair<ExceptMove, double>         tt5;
typedef bksge::pair<NoexceptMove, ExceptMove>   tt6;

static_assert( bksge::is_nothrow_move_constructible<tt1>::value, "");
static_assert( bksge::is_nothrow_move_constructible<tt2>::value, "");
static_assert( bksge::is_nothrow_move_constructible<tt3>::value, "");
static_assert(!bksge::is_nothrow_move_constructible<tt4>::value, "");
static_assert(!bksge::is_nothrow_move_constructible<tt5>::value, "");
static_assert(!bksge::is_nothrow_move_constructible<tt6>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	{
		bksge::pair<int, double> p1(1, 2);
		bksge::pair<int, double> p2(bksge::move(p1));
		VERIFY(p2.first  == 1);
		VERIFY(p2.second == 2.0f);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, CtorMoveTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace ctor_move_test

}	// namespace bksge_pair_test
