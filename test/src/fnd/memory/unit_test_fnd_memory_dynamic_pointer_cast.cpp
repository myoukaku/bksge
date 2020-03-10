/**
 *	@file	unit_test_fnd_memory_dynamic_pointer_cast.cpp
 *
 *	@brief	dynamic_pointer_cast のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/memory/dynamic_pointer_cast.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <gtest/gtest.h>

namespace bksge_memory_test
{

namespace dynamic_pointer_cast_test
{

struct Base
{
	virtual ~Base(){}

	virtual int func() const { return 10; }
};

struct Derived : public Base
{
	virtual ~Derived(){}

	virtual int func() const { return 20; }
};

GTEST_TEST(MemoryTest, DynamicPointerCastTest)
{
#if !defined(BKSGE_NO_RTTI)
	{
		bksge::shared_ptr<Derived> p1(new Derived);
		bksge::shared_ptr<Base> p2 = p1;
		bksge::shared_ptr<Derived> p3 = bksge::dynamic_pointer_cast<Derived>(p2);

		EXPECT_EQ(20, p3->func());
	}
	{
		bksge::shared_ptr<Derived> p1;
		bksge::shared_ptr<Base> p2 = p1;
		bksge::shared_ptr<Derived> p3 = bksge::dynamic_pointer_cast<Derived>(p2);

		EXPECT_TRUE(p3 == nullptr);
	}
#endif
}

}	// namespace dynamic_pointer_cast_test

}	// namespace bksge_memory_test
