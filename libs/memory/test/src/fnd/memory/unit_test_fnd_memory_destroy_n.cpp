/**
 *	@file	unit_test_fnd_memory_destroy_n.cpp
 *
 *	@brief	destroy_n のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/memory/destroy_n.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_memory_test
{

namespace destroy_n_test
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

GTEST_TEST(MemoryTest, DestroyNTest)
{
	EXPECT_EQ(0, X::destruct_count);
	{
		X x[3] = {};
		auto ret = bksge::destroy_n(x, 3);
		EXPECT_TRUE(ret == x+3);
		EXPECT_EQ(3, X::destruct_count);
	}
	EXPECT_EQ(6, X::destruct_count);

	{
		int x[8] = {};
		auto ret = bksge::destroy_n(x, 8);
		EXPECT_TRUE(ret == x+8);
	}
}

}	// namespace destroy_n_test

}	// namespace bksge_memory_test
