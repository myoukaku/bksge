/**
 *	@file	unit_test_render_class_id.cpp
 *
 *	@brief	ClassIdのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/detail/class_id.hpp>
#include <gtest/gtest.h>

namespace bksge_render_test
{

namespace class_id_test
{

class Base
{
public:
	static const bksge::render::ClassId& StaticClassId(void)
	{
		static const auto id = bksge::render::make_class_id<Base>();
		return id;
	}

	virtual ~Base()
	{
	}

	virtual const bksge::render::ClassId& class_id(void) const
	{
		return StaticClassId();
	}
};

class Derived1 : public Base
{
public:
	virtual ~Derived1()
	{
	}

	static const bksge::render::ClassId& StaticClassId(void)
	{
		static const auto id = bksge::render::make_class_id<Derived1>();
		return id;
	}

	virtual const bksge::render::ClassId& class_id(void) const
	{
		return StaticClassId();
	}
};

template <typename T>
class Derived2 : public Base
{
public:
	virtual ~Derived2()
	{
	}

	static const bksge::render::ClassId& StaticClassId(void)
	{
		static const auto id = bksge::render::make_class_id<Derived2<T>>();
		return id;
	}

	virtual const bksge::render::ClassId& class_id(void) const
	{
		return StaticClassId();
	}
};

GTEST_TEST(Render_ClassId, BasicTest)
{
	Base b1;
	Base b2;
	Derived1 d1;
	Derived1 d2;
	Derived2<int> d3;
	Derived2<int> d4;
	Derived2<float> d5;
	Derived2<float> d6;
	EXPECT_EQ(Base::StaticClassId(), b1.class_id());
	EXPECT_NE(Derived1::StaticClassId(), b1.class_id());
	EXPECT_NE(Derived2<int>::StaticClassId(), b1.class_id());
	EXPECT_NE(Derived2<float>::StaticClassId(), b1.class_id());

	EXPECT_NE(Base::StaticClassId(), d1.class_id());
	EXPECT_EQ(Derived1::StaticClassId(), d1.class_id());
	EXPECT_NE(Derived2<int>::StaticClassId(), d1.class_id());
	EXPECT_NE(Derived2<float>::StaticClassId(), d1.class_id());

	EXPECT_NE(Base::StaticClassId(), d3.class_id());
	EXPECT_NE(Derived1::StaticClassId(), d3.class_id());
	EXPECT_EQ(Derived2<int>::StaticClassId(), d3.class_id());
	EXPECT_NE(Derived2<float>::StaticClassId(), d3.class_id());

	EXPECT_NE(Base::StaticClassId(), d5.class_id());
	EXPECT_NE(Derived1::StaticClassId(), d5.class_id());
	EXPECT_NE(Derived2<int>::StaticClassId(), d5.class_id());
	EXPECT_EQ(Derived2<float>::StaticClassId(), d5.class_id());

	EXPECT_EQ(b1.class_id(), b2.class_id());
	EXPECT_EQ(d1.class_id(), d2.class_id());
	EXPECT_EQ(d3.class_id(), d4.class_id());
	EXPECT_EQ(d5.class_id(), d6.class_id());
	EXPECT_NE(b1.class_id(), d1.class_id());
	EXPECT_NE(b1.class_id(), d3.class_id());
	EXPECT_NE(b1.class_id(), d5.class_id());
	EXPECT_NE(d1.class_id(), d3.class_id());
	EXPECT_NE(d1.class_id(), d5.class_id());
	EXPECT_NE(d3.class_id(), d5.class_id());
}

GTEST_TEST(Render_ClassId, PtrTest)
{
	Base* b1 = new Base();
	Base* b2 = new Base();
	Base* d1 = new Derived1();
	Base* d2 = new Derived1();
	Base* d3 = new Derived2<int>();
	Base* d4 = new Derived2<int>();
	Base* d5 = new Derived2<float>();
	Base* d6 = new Derived2<float>();

	EXPECT_EQ(Base::StaticClassId(), b1->class_id());
	EXPECT_NE(Derived1::StaticClassId(), b1->class_id());
	EXPECT_NE(Derived2<int>::StaticClassId(), b1->class_id());
	EXPECT_NE(Derived2<float>::StaticClassId(), b1->class_id());

	EXPECT_NE(Base::StaticClassId(), d1->class_id());
	EXPECT_EQ(Derived1::StaticClassId(), d1->class_id());
	EXPECT_NE(Derived2<int>::StaticClassId(), d1->class_id());
	EXPECT_NE(Derived2<float>::StaticClassId(), d1->class_id());

	EXPECT_NE(Base::StaticClassId(), d3->class_id());
	EXPECT_NE(Derived1::StaticClassId(), d3->class_id());
	EXPECT_EQ(Derived2<int>::StaticClassId(), d3->class_id());
	EXPECT_NE(Derived2<float>::StaticClassId(), d3->class_id());

	EXPECT_NE(Base::StaticClassId(), d5->class_id());
	EXPECT_NE(Derived1::StaticClassId(), d5->class_id());
	EXPECT_NE(Derived2<int>::StaticClassId(), d5->class_id());
	EXPECT_EQ(Derived2<float>::StaticClassId(), d5->class_id());

	EXPECT_EQ(b1->class_id(), b2->class_id());
	EXPECT_EQ(d1->class_id(), d2->class_id());
	EXPECT_EQ(d3->class_id(), d4->class_id());
	EXPECT_EQ(d5->class_id(), d6->class_id());
	EXPECT_NE(b1->class_id(), d1->class_id());
	EXPECT_NE(b1->class_id(), d3->class_id());
	EXPECT_NE(b1->class_id(), d5->class_id());
	EXPECT_NE(d1->class_id(), d3->class_id());
	EXPECT_NE(d1->class_id(), d5->class_id());
	EXPECT_NE(d3->class_id(), d5->class_id());

	delete b1;
	delete b2;
	delete d1;
	delete d2;
	delete d3;
	delete d4;
	delete d5;
	delete d6;
}

}	// namespace class_id_test

}	// namespace bksge_render_test
