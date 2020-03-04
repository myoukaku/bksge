/**
 *	@file	unit_test_fnd_pair_move_ctor.cpp
 *
 *	@brief	pairのムーブコンストラクタのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair/pair.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/type_traits/is_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_pair_move_ctor_test
{

struct NonMovable
{
	NonMovable(NonMovable&&) = delete;
};

struct ImplicitMove
{
	ImplicitMove(ImplicitMove&&) {}
};

struct ExplicitMove
{
	explicit ExplicitMove(ExplicitMove&&) {}
};

struct NothrowMove
{
	NothrowMove(NothrowMove&&) noexcept {}
};

GTEST_TEST(PairTest, MoveCtorTest)
{
	{
        static_assert( bksge::is_move_constructible<bksge::pair<int, float>>::value, "");
        static_assert(!bksge::is_move_constructible<bksge::pair<int, NonMovable>>::value, "");
        static_assert(!bksge::is_move_constructible<bksge::pair<NonMovable, float>>::value, "");
        static_assert( bksge::is_move_constructible<bksge::pair<int, ImplicitMove>>::value, "");
        static_assert( bksge::is_move_constructible<bksge::pair<ImplicitMove, int>>::value, "");
        static_assert( bksge::is_move_constructible<bksge::pair<int, ExplicitMove>>::value, "");
        static_assert( bksge::is_move_constructible<bksge::pair<ExplicitMove, int>>::value, "");
        static_assert( bksge::is_move_constructible<bksge::pair<int, NothrowMove>>::value, "");
        static_assert( bksge::is_move_constructible<bksge::pair<NothrowMove, int>>::value, "");

        static_assert( bksge::is_implicitly_move_constructible<bksge::pair<int, float>>::value, "");
        static_assert(!bksge::is_implicitly_move_constructible<bksge::pair<int, NonMovable>>::value, "");
        static_assert(!bksge::is_implicitly_move_constructible<bksge::pair<NonMovable, float>>::value, "");
        static_assert( bksge::is_implicitly_move_constructible<bksge::pair<int, ImplicitMove>>::value, "");
        static_assert( bksge::is_implicitly_move_constructible<bksge::pair<ImplicitMove, int>>::value, "");
        static_assert( bksge::is_implicitly_move_constructible<bksge::pair<int, ExplicitMove>>::value, "");	// TODO
        static_assert( bksge::is_implicitly_move_constructible<bksge::pair<ExplicitMove, int>>::value, "");	// TODO
        static_assert( bksge::is_implicitly_move_constructible<bksge::pair<int, NothrowMove>>::value, "");
        static_assert( bksge::is_implicitly_move_constructible<bksge::pair<NothrowMove, int>>::value, "");

        static_assert( bksge::is_nothrow_move_constructible<bksge::pair<int, float>>::value, "");
        static_assert(!bksge::is_nothrow_move_constructible<bksge::pair<int, NonMovable>>::value, "");
        static_assert(!bksge::is_nothrow_move_constructible<bksge::pair<NonMovable, float>>::value, "");
        static_assert(!bksge::is_nothrow_move_constructible<bksge::pair<int, ImplicitMove>>::value, "");
        static_assert(!bksge::is_nothrow_move_constructible<bksge::pair<ImplicitMove, int>>::value, "");
        static_assert(!bksge::is_nothrow_move_constructible<bksge::pair<int, ExplicitMove>>::value, "");
        static_assert(!bksge::is_nothrow_move_constructible<bksge::pair<ExplicitMove, int>>::value, "");
        static_assert( bksge::is_nothrow_move_constructible<bksge::pair<int, NothrowMove>>::value, "");
        static_assert( bksge::is_nothrow_move_constructible<bksge::pair<NothrowMove, int>>::value, "");
	}
	{
		bksge::pair<int, float> p1 { 3, 4.5f };
		bksge::pair<int, float> p2 { bksge::move(p1) };
		EXPECT_EQ(3,    p2.first);
		EXPECT_EQ(4.5f, p2.second);
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::pair<int, float> p1 { 3, 4.5f };
		BKSGE_CXX14_CONSTEXPR bksge::pair<int, float> p2 { bksge::move(p1) };
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3,    p2.first);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(4.5f, p2.second);
	}
}

}	// namespace bksge_pair_move_ctor_test
