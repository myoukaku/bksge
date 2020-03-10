/**
 *	@file	unit_test_fnd_memory_reinterpret_pointer_cast.cpp
 *
 *	@brief	reinterpret_pointer_cast のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/memory/reinterpret_pointer_cast.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <gtest/gtest.h>

namespace bksge_memory_test
{

namespace reinterpret_pointer_cast_test
{

struct Foo
{
	int m_value;

	Foo(int x) : m_value(x) {}
};

GTEST_TEST(MemoryTest, ReinterpretPointerCastTest)
{
	{
		bksge::shared_ptr<Foo> p1(new Foo(4));
		bksge::shared_ptr<int> p2 = bksge::reinterpret_pointer_cast<int>(p1);

		EXPECT_EQ(4, *p2);
	}
}

}	// namespace reinterpret_pointer_cast_test

}	// namespace bksge_memory_test
