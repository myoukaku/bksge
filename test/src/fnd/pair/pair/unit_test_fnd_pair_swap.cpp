/**
 *	@file	unit_test_fnd_pair_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair/pair.hpp>
#include <gtest/gtest.h>

namespace bksge_pair_swap_test
{

struct S
{
	int i;
	S() : i(0) {}
	S(int j) : i(j) {}
	S * operator& () { assert(false); return this; }
	S const * operator& () const { assert(false); return this; }
};

GTEST_TEST(PairTest, SwapTest)
{
	{
		using P1 = bksge::pair<int, short>;
		P1 p1(3, static_cast<short>(4));
		P1 p2(5, static_cast<short>(6));
		p1.swap(p2);
		EXPECT_EQ(5, p1.first);
		EXPECT_EQ(6, p1.second);
		EXPECT_EQ(3, p2.first);
		EXPECT_EQ(4, p2.second);
		swap(p1, p2);
		EXPECT_EQ(3, p1.first);
		EXPECT_EQ(4, p1.second);
		EXPECT_EQ(5, p2.first);
		EXPECT_EQ(6, p2.second);
	}
	{
		using P1 = bksge::pair<int, S>;
		P1 p1(3, S(4));
		P1 p2(5, S(6));
		p1.swap(p2);
		EXPECT_EQ(5, p1.first);
		EXPECT_EQ(6, p1.second.i);
		EXPECT_EQ(3, p2.first);
		EXPECT_EQ(4, p2.second.i);
		swap(p1, p2);
		EXPECT_EQ(3, p1.first);
		EXPECT_EQ(4, p1.second.i);
		EXPECT_EQ(5, p2.first);
		EXPECT_EQ(6, p2.second.i);
	}
}

}	// namespace bksge_pair_swap_test
