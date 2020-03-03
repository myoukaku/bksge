/**
 *	@file	unit_test_fnd_pair_assign_rv_pair_u_v.cpp
 *
 *	@brief	pairのoperator=のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair/pair.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/type_traits/is_assignable.hpp>
//#include <bksge/fnd/type_traits/is_nothrow_assignable.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>

namespace bksge_pair_assign_rv_pair_uv
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

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4244);	// '初期化中': '_Ty' から '_Ty1' への変換です。データが失われる可能性があります。 

GTEST_TEST(PairTest, AssignRVPairUVTest)
{
	{
		static_assert( bksge::is_assignable<bksge::pair<int, float>, bksge::pair<short, double>&&>::value, "");
		static_assert(!bksge::is_assignable<bksge::pair<int, float>, bksge::pair<NonMovable, float>&&>::value, "");
		static_assert(!bksge::is_assignable<bksge::pair<int, float>, bksge::pair<int, ThrowAssign>&&>::value, "");
		static_assert(!bksge::is_assignable<bksge::pair<NonMovable, float>, bksge::pair<NonMovable, int>&&>::value, "");
		static_assert( bksge::is_assignable<bksge::pair<ThrowAssign, float>, bksge::pair<ThrowAssign, int>&&>::value, "");
		static_assert( bksge::is_assignable<bksge::pair<NothrowAssign, float>, bksge::pair<NothrowAssign, int>&&>::value, "");

		//static_assert( bksge::is_nothrow_assignable<bksge::pair<int, float>, bksge::pair<short, double>&&>::value, "");
		//static_assert(!bksge::is_nothrow_assignable<bksge::pair<int, float>, bksge::pair<NonMovable, float>&&>::value, "");
		//static_assert(!bksge::is_nothrow_assignable<bksge::pair<int, float>, bksge::pair<int, ThrowAssign>&&>::value, "");
		//static_assert(!bksge::is_nothrow_assignable<bksge::pair<NonMovable, float>, bksge::pair<NonMovable, int>&&>::value, "");
		//static_assert(!bksge::is_nothrow_assignable<bksge::pair<ThrowAssign, float>, bksge::pair<ThrowAssign, int>&&>::value, "");
		//static_assert( bksge::is_nothrow_assignable<bksge::pair<NothrowAssign, float>, bksge::pair<NothrowAssign, int>&&>::value, "");
	}
	{
		bksge::pair<short, float> p1 { 3, 4.5f };
		bksge::pair<int, double> p2;
		p2 = bksge::move(p1);
		EXPECT_EQ(3,   p2.first);
		EXPECT_EQ(4.5, p2.second);
	}
}

BKSGE_WARNING_POP();

}	// namespace bksge_pair_assign_rv_pair_uv
