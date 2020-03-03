/**
 *	@file	unit_test_fnd_pair_assign_const_pair.cpp
 *
 *	@brief	pairのoperator=のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair/pair.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
//#include <bksge/fnd/type_traits/is_nothrow_copy_assignable.hpp>
#include <gtest/gtest.h>

namespace bksge_pair_assign_const_pair
{

struct NonCopyable
{
	NonCopyable(NonCopyable const&) = delete;
	NonCopyable& operator=(NonCopyable const&) = delete;
};

struct ThrowAssign
{
	ThrowAssign& operator=(ThrowAssign const&) { return *this; }
};

struct NothrowAssign
{
	NothrowAssign& operator=(NothrowAssign const&) noexcept { return *this; }
};

GTEST_TEST(PairTest, AssignConstPairTest)
{
	{
		static_assert( bksge::is_copy_assignable<bksge::pair<int, float>>::value, "");
		static_assert(!bksge::is_copy_assignable<bksge::pair<NonCopyable, float>>::value, "");
		static_assert(!bksge::is_copy_assignable<bksge::pair<int, NonCopyable>>::value, "");
		static_assert( bksge::is_copy_assignable<bksge::pair<ThrowAssign, float>>::value, "");
		static_assert( bksge::is_copy_assignable<bksge::pair<int, ThrowAssign>>::value, "");
		static_assert( bksge::is_copy_assignable<bksge::pair<NothrowAssign, float>>::value, "");
		static_assert( bksge::is_copy_assignable<bksge::pair<int, NothrowAssign>>::value, "");

		//static_assert( bksge::is_nothrow_copy_assignable<bksge::pair<int, float>>::value, "");
		//static_assert(!bksge::is_nothrow_copy_assignable<bksge::pair<NonCopyable, float>>::value, "");
		//static_assert(!bksge::is_nothrow_copy_assignable<bksge::pair<int, NonCopyable>>::value, "");
		//static_assert(!bksge::is_nothrow_copy_assignable<bksge::pair<ThrowAssign, float>>::value, "");
		//static_assert(!bksge::is_nothrow_copy_assignable<bksge::pair<int, ThrowAssign>>::value, "");
		//static_assert( bksge::is_nothrow_copy_assignable<bksge::pair<NothrowAssign, float>>::value, "");
		//static_assert( bksge::is_nothrow_copy_assignable<bksge::pair<int, NothrowAssign>>::value, "");
	}
	{
		const bksge::pair<int, float> p1 { 3, 4.5f };
		bksge::pair<int, float> p2;
		p2 = p1;
		EXPECT_EQ(3,    p2.first);
		EXPECT_EQ(4.5f, p2.second);
	}
}

}	// namespace bksge_pair_assign_const_pair
