/**
 *	@file	unit_test_fnd_memory_make_shared.cpp
 *
 *	@brief	make_shared のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/memory/make_shared.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <gtest/gtest.h>

GTEST_TEST(MemoryTest, MakeSharedTest)
{
	bksge::shared_ptr<int> sp = bksge::make_shared<int>(42);

	EXPECT_TRUE(!!sp);
	EXPECT_EQ(42, *sp);
}
