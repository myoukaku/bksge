/**
 *	@file	unit_test_fnd_cstring_memset.cpp
 *
 *	@brief	memsetのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cstring/memset.hpp>
#include <gtest/gtest.h>

GTEST_TEST(CStringTest, MemSetTest)
{
	{
		char a[3];
		auto p = bksge::memset(a, 0, sizeof(a));

		EXPECT_EQ(0, a[0]);
		EXPECT_EQ(0, a[1]);
		EXPECT_EQ(0, a[2]);
		EXPECT_EQ(p, a);
	}
	{
		int a[4];
		auto p = bksge::memset(a, 0, sizeof(a));

		EXPECT_EQ(0, a[0]);
		EXPECT_EQ(0, a[1]);
		EXPECT_EQ(0, a[2]);
		EXPECT_EQ(0, a[3]);
		EXPECT_EQ(p, a);
	}
	{
		char a[5] = {};
		auto p = bksge::memset(a, 42, sizeof(char) * 3);

		EXPECT_EQ(42, a[0]);
		EXPECT_EQ(42, a[1]);
		EXPECT_EQ(42, a[2]);
		EXPECT_EQ( 0, a[3]);
		EXPECT_EQ( 0, a[4]);
		EXPECT_EQ(p, a);
	}
}
