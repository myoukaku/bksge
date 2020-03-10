/**
 *	@file	unit_test_fnd_memory_allocator.cpp
 *
 *	@brief	allocator のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/memory/allocator.hpp>
#include <gtest/gtest.h>

GTEST_TEST(MemoryTest, AllocatorTest)
{
	bksge::allocator<int> alloc;
	auto p = alloc.allocate(10);
	alloc.deallocate(p, 10);
}
