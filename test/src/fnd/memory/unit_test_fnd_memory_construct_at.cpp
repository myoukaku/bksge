/**
 *	@file	unit_test_fnd_memory_construct_at.cpp
 *
 *	@brief	construct_at のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/memory/construct_at.hpp>
#include <bksge/fnd/memory/destroy_at.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_memory_test
{

namespace construct_at_test
{

struct X
{
	int value;
	static int construct_count;
	static int destruct_count;

	X() : value(0)
	{
		++construct_count;
	}

	X(int v) : value(v)
	{
		++construct_count;
	}

	~X()
	{
		++destruct_count;
	}
};

int X::construct_count = 0;
int X::destruct_count = 0;

GTEST_TEST(MemoryTest, ConstructAtTest)
{
	EXPECT_EQ(0, X::construct_count);
	EXPECT_EQ(0, X::destruct_count);
	{
		X x;
		EXPECT_EQ(1, X::construct_count);
		EXPECT_EQ(0, X::destruct_count);
		bksge::destroy_at(&x);
		bksge::construct_at(&x);
		EXPECT_EQ(2, X::construct_count);
		EXPECT_EQ(1, X::destruct_count);
	}
	EXPECT_EQ(2, X::construct_count);
	EXPECT_EQ(2, X::destruct_count);

	X::construct_count = 0;
	X::destruct_count = 0;

	{
		X x;
		EXPECT_EQ(1, X::construct_count);
		EXPECT_EQ(0, X::destruct_count);
		EXPECT_EQ(0, x.value);
		bksge::destroy_at(&x);
		bksge::construct_at(&x, 42);
		EXPECT_EQ(2, X::construct_count);
		EXPECT_EQ(1, X::destruct_count);
		EXPECT_EQ(42, x.value);
	}
	EXPECT_EQ(2, X::construct_count);
	EXPECT_EQ(2, X::destruct_count);

	{
		int x = {};
		bksge::destroy_at(&x);
		bksge::construct_at(&x, 17);
		EXPECT_EQ(x, 17);
	}
}

}	// namespace construct_at_test

}	// namespace bksge_memory_test
