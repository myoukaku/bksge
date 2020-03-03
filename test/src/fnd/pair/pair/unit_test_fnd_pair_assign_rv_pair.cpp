/**
 *	@file	unit_test_fnd_pair_assign_rv_pair.cpp
 *
 *	@brief	pairのoperator=のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair/pair.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/type_traits/is_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_assignable.hpp>
#include <gtest/gtest.h>

namespace bksge_pair_assign_rv_pair
{

struct NonMovable
{
	NonMovable(NonMovable&&) = delete;
	NonMovable& operator=(NonMovable&&) = delete;
};

struct ThrowAssign
{
	ThrowAssign& operator=(ThrowAssign&&) { return *this; }
};

struct NothrowAssign
{
	NothrowAssign& operator=(NothrowAssign&&) noexcept { return *this; }
};

GTEST_TEST(PairTest, AssignRVPairTest)
{
	{
		static_assert( bksge::is_move_assignable<bksge::pair<int, float>>::value, "");
		static_assert(!bksge::is_move_assignable<bksge::pair<NonMovable, float>>::value, "");
		static_assert(!bksge::is_move_assignable<bksge::pair<int, NonMovable>>::value, "");
		static_assert( bksge::is_move_assignable<bksge::pair<ThrowAssign, float>>::value, "");
		static_assert( bksge::is_move_assignable<bksge::pair<int, ThrowAssign>>::value, "");
		static_assert( bksge::is_move_assignable<bksge::pair<NothrowAssign, float>>::value, "");
		static_assert( bksge::is_move_assignable<bksge::pair<int, NothrowAssign>>::value, "");

		static_assert( bksge::is_nothrow_move_assignable<bksge::pair<int, float>>::value, "");
		static_assert(!bksge::is_nothrow_move_assignable<bksge::pair<NonMovable, float>>::value, "");
		static_assert(!bksge::is_nothrow_move_assignable<bksge::pair<int, NonMovable>>::value, "");
		static_assert(!bksge::is_nothrow_move_assignable<bksge::pair<ThrowAssign, float>>::value, "");
		static_assert(!bksge::is_nothrow_move_assignable<bksge::pair<int, ThrowAssign>>::value, "");
		static_assert( bksge::is_nothrow_move_assignable<bksge::pair<NothrowAssign, float>>::value, "");
		static_assert( bksge::is_nothrow_move_assignable<bksge::pair<int, NothrowAssign>>::value, "");
	}
	{
		bksge::pair<int, float> p1 { 3, 4.5f };
		bksge::pair<int, float> p2;
		p2 = bksge::move(p1);
		EXPECT_EQ(3,    p2.first);
		EXPECT_EQ(4.5f, p2.second);
	}
}

}	// namespace bksge_pair_assign_rv_pair
