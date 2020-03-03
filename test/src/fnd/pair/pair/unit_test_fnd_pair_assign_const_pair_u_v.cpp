/**
 *	@file	unit_test_fnd_pair_assign_const_pair_u_v.cpp
 *
 *	@brief	pairのoperator=のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair/pair.hpp>
#include <bksge/fnd/type_traits/is_assignable.hpp>
//#include <bksge/fnd/type_traits/is_nothrow_assignable.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>

namespace bksge_pair_assign_const_pair_uv
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

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4244);	// '初期化中': '_Ty' から '_Ty1' への変換です。データが失われる可能性があります。 

GTEST_TEST(PairTest, AssignConstPairUVTest)
{
	{
		static_assert( bksge::is_assignable<bksge::pair<int, float>, bksge::pair<short, double> const&>::value, "");
		static_assert(!bksge::is_assignable<bksge::pair<int, float>, bksge::pair<NonCopyable, float> const&>::value, "");
		static_assert(!bksge::is_assignable<bksge::pair<int, float>, bksge::pair<int, ThrowAssign> const&>::value, "");
		static_assert(!bksge::is_assignable<bksge::pair<NonCopyable, float>, bksge::pair<NonCopyable, int> const&>::value, "");
		static_assert( bksge::is_assignable<bksge::pair<ThrowAssign, float>, bksge::pair<ThrowAssign, int> const&>::value, "");
		static_assert( bksge::is_assignable<bksge::pair<NothrowAssign, float>, bksge::pair<NothrowAssign, int> const&>::value, "");

		//static_assert( bksge::is_nothrow_assignable<bksge::pair<int, float>, bksge::pair<short, double> const&>::value, "");
		//static_assert(!bksge::is_nothrow_assignable<bksge::pair<int, float>, bksge::pair<NonCopyable, float> const&>::value, "");
		//static_assert(!bksge::is_nothrow_assignable<bksge::pair<int, float>, bksge::pair<int, ThrowAssign> const&>::value, "");
		//static_assert(!bksge::is_nothrow_assignable<bksge::pair<NonCopyable, float>, bksge::pair<NonCopyable, int> const&>::value, "");
		//static_assert(!bksge::is_nothrow_assignable<bksge::pair<ThrowAssign, float>, bksge::pair<ThrowAssign, int> const&>::value, "");
		//static_assert( bksge::is_nothrow_assignable<bksge::pair<NothrowAssign, float>, bksge::pair<NothrowAssign, int> const&>::value, "");
	}
	{
		const bksge::pair<short, float> p1 { 3, 4.5f };
		bksge::pair<int, double> p2;
		p2 = p1;
		EXPECT_EQ(3,   p2.first);
		EXPECT_EQ(4.5, p2.second);
	}
}

BKSGE_WARNING_POP();

}	// namespace bksge_pair_assign_const_pair_uv
