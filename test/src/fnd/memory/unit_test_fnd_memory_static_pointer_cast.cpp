/**
 *	@file	unit_test_fnd_memory_static_pointer_cast.cpp
 *
 *	@brief	static_pointer_cast のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/memory/static_pointer_cast.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <gtest/gtest.h>

namespace bksge_memory_test
{

namespace static_pointer_cast_test
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

GTEST_TEST(MemoryTest, StaticPointerCastTest)
{
	{
		bksge::shared_ptr<Derived> p1(new Derived);
		bksge::shared_ptr<Base> p2 = bksge::static_pointer_cast<Base>(p1);

		EXPECT_EQ(20, p1->func());
		EXPECT_EQ(20, p2->func());
		EXPECT_TRUE(p1 == p2);
	}
	{
		bksge::shared_ptr<Derived> p1;
		bksge::shared_ptr<Base> p2 = bksge::static_pointer_cast<Base>(p1);

		EXPECT_TRUE(p2 == nullptr);
	}
}

}	// namespace static_pointer_cast_test

}	// namespace bksge_memory_test
