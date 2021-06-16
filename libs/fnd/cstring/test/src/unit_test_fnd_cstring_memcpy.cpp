/**
 *	@file	unit_test_fnd_cstring_memcpy.cpp
 *
 *	@brief	memcpyのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cstring/memcpy.hpp>
#include <gtest/gtest.h>

GTEST_TEST(CStringTest, MemCpyTest)
{
	const int a1[] = { 2, 1, 0, 3 };
	int a2[4];

	auto p = bksge::memcpy(a2, a1, sizeof(a1));

	EXPECT_EQ(2, a2[0]);
	EXPECT_EQ(1, a2[1]);
	EXPECT_EQ(0, a2[2]);
	EXPECT_EQ(3, a2[3]);

	EXPECT_EQ(p, a2);
}
