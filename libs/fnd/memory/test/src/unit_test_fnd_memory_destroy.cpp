/**
 *	@file	unit_test_fnd_memory_destroy.cpp
 *
 *	@brief	destroy のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/memory/destroy.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_memory_test
{

namespace destroy_test
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

GTEST_TEST(MemoryTest, DestroyTest)
{
	EXPECT_EQ(0, X::destruct_count);
	{
		X x[3] = {};
		bksge::destroy(x, x+3);
		EXPECT_EQ(3, X::destruct_count);
	}
	EXPECT_EQ(6, X::destruct_count);

	{
		int x[8] = {};
		bksge::destroy(x, x+8);
	}
}

}	// namespace destroy_test

}	// namespace bksge_memory_test
