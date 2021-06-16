/**
 *	@file	unit_test_fnd_utility_move_if_noexcept.cpp
 *
 *	@brief	move_if_noexcept のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/move_if_noexcept.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_utility_test
{

namespace move_if_noexcept_test
{

static bool copied;
static bool moved;

struct A
{
	A() {}

	A(const A&)
	{
		copied = true;
	}

	A(A&&) BKSGE_NOEXCEPT_OR_NOTHROW
	{
		moved = true;
	}
};

struct B
{
	B() {}

	B(const B&)
	{
		copied = true;
	}

	B(B&&)
	{
		moved = true;
	}
};

GTEST_TEST(UtilityTest, MoveIfNoexceptTest)
{
	copied = false;
	moved = false;

	{
		// Aのムーブコンストラクタが例外を投げないのでムーブされる
		A a1;
		A a2 = bksge::move_if_noexcept(a1);
		(void)a2;
		EXPECT_FALSE(copied);
		EXPECT_TRUE(moved);
	}

	copied = false;
	moved = false;

	{
		// Bのムーブコンストラクタが例外を投げる可能性があるのでコピーされる
		B b1;
		B b2 = bksge::move_if_noexcept(b1);
		(void)b2;
		EXPECT_TRUE(copied);
		EXPECT_FALSE(moved);
	}
}

}	// namespace move_if_noexcept_test

}	// namespace bksge_utility_test
