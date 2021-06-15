/**
 *	@file	unit_test_fnd_memory_destroy_at.cpp
 *
 *	@brief	destroy_at のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/memory/destroy_at.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_memory_test
{

namespace destroy_at_test
{

struct X
{
	int value;
	static int destruct_count;
	~X()
	{
		++destruct_count;
	}
};

int X::destruct_count = 0;

GTEST_TEST(MemoryTest, DestroyAtTest)
{
	EXPECT_EQ(0, X::destruct_count);
	{
		X x = {};
		bksge::destroy_at(&x);
		EXPECT_EQ(1, X::destruct_count);
	}
	EXPECT_EQ(2, X::destruct_count);

	X::destruct_count = 0;
	{
		X x[4] = {};
		bksge::destroy_at(&x);
		EXPECT_EQ(4, X::destruct_count);
	}
	EXPECT_EQ(8, X::destruct_count);

	{
		int x = {};
		bksge::destroy_at(&x);
	}
}

}	// namespace destroy_at_test

}	// namespace bksge_memory_test
