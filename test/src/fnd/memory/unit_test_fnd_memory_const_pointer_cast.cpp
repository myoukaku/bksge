/**
 *	@file	unit_test_fnd_memory_const_pointer_cast.cpp
 *
 *	@brief	const_pointer_cast のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/memory/const_pointer_cast.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <gtest/gtest.h>

GTEST_TEST(MemoryTest, ConstPointerCastTest)
{
	{
		bksge::shared_ptr<const int> p1(new int(3));
		bksge::shared_ptr<int> p2 = bksge::const_pointer_cast<int>(p1);

		EXPECT_EQ(3, *p2);
	}
	{
		bksge::shared_ptr<const int> p1;
		bksge::shared_ptr<int> p2 = bksge::const_pointer_cast<int>(p1);

		EXPECT_TRUE(p2 == nullptr);
	}
}
