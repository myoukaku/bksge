/**
 *	@file	unit_test_fnd_memory_unique_ptr.cpp
 *
 *	@brief	unique_ptr のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/utility/move.hpp>
//#include <bksge/fnd/functional/hash.hpp>
#include <functional>	// hash
#include <gtest/gtest.h>

namespace bksge_memory_test
{

namespace unique_ptr_test
{

static int s_base_default_ctor_count = 0;
static int s_base_copy_ctor_count = 0;
static int s_base_move_ctor_count = 0;
static int s_base_dtor_count = 0;

static int s_derived_default_ctor_count = 0;
static int s_derived_copy_ctor_count = 0;
static int s_derived_move_ctor_count = 0;
static int s_derived_dtor_count = 0;

static int s_deleter_default_ctor_count = 0;
static int s_deleter_copy_ctor_count = 0;
static int s_deleter_move_ctor_count = 0;
static int s_deleter_dtor_count = 0;
static int s_deleter_delete_base_count = 0;
static int s_deleter_delete_derived_count = 0;

struct Base
{
	Base()            { ++s_base_default_ctor_count; }
	Base(const Base&) { ++s_base_copy_ctor_count; }
	Base(Base&&)      { ++s_base_move_ctor_count; }
	virtual ~Base()   { ++s_base_dtor_count; }

	virtual int func() { return 1; }
};

struct Derived : public Base
{
	Derived()                 : Base()               { ++s_derived_default_ctor_count; }
	Derived(const Derived& d) : Base(d)              { ++s_derived_copy_ctor_count; }
	Derived(Derived&& d)      : Base(bksge::move(d)) { ++s_derived_move_ctor_count; }
	virtual ~Derived()                               { ++s_derived_dtor_count; }

	virtual int func() { return 2; }
};

struct Deleter
{
	Deleter()
	{
		++s_deleter_default_ctor_count;
	}

	Deleter(int value)
		: m_value(value)
	{
	}

	Deleter(const Deleter& d)
		: m_value(d.m_value)
	{
		++s_deleter_copy_ctor_count;
	}

	Deleter(Deleter&& d)
		: m_value(d.m_value)
	{
		++s_deleter_move_ctor_count;
	}
	
	~Deleter()
	{
		++s_deleter_dtor_count;
	}

	Deleter& operator=(Deleter const&) = default;
//	Deleter& operator=(Deleter &&) = default;
	
	void operator()(Base* p) const
	{
		++s_deleter_delete_base_count;
		delete p;
	}
	void operator()(Derived* p) const
	{
		++s_deleter_delete_derived_count;
		delete p;
	}

	int m_value = 0;
};

struct ArrayDeleter
{
	ArrayDeleter()
	{
		++s_deleter_default_ctor_count;
	}

	ArrayDeleter(int value)
		: m_value(value)
	{
	}

	ArrayDeleter(const ArrayDeleter& d)
		: m_value(d.m_value)
	{
		++s_deleter_copy_ctor_count;
	}

	ArrayDeleter(ArrayDeleter&& d)
		: m_value(d.m_value)
	{
		++s_deleter_move_ctor_count;
	}
	
	~ArrayDeleter()
	{
		++s_deleter_dtor_count;
	}

	ArrayDeleter& operator=(ArrayDeleter const&) = default;
//	ArrayDeleter& operator=(ArrayDeleter &&) = default;
	
	void operator()(Base* p) const
	{
		++s_deleter_delete_base_count;
		delete[] p;
	}
	void operator()(Derived* p) const
	{
		++s_deleter_delete_derived_count;
		delete[] p;
	}

	int m_value = 0;
};

static void ResetCount(void)
{
	s_base_default_ctor_count      = 0;
	s_base_copy_ctor_count         = 0;
	s_base_move_ctor_count         = 0;
	s_base_dtor_count              = 0;
	s_derived_default_ctor_count   = 0;
	s_derived_copy_ctor_count      = 0;
	s_derived_move_ctor_count      = 0;
	s_derived_dtor_count           = 0;
	s_deleter_default_ctor_count   = 0;
	s_deleter_copy_ctor_count      = 0;
	s_deleter_move_ctor_count      = 0;
	s_deleter_dtor_count           = 0;
	s_deleter_delete_base_count    = 0;
	s_deleter_delete_derived_count = 0;
}

GTEST_TEST(UniquePtrTest, ConstructTest)
{
	ResetCount();

	// (1)
	{
		bksge::unique_ptr<Base> up;
		EXPECT_EQ(0, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
	}
	EXPECT_EQ(0, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(0, s_base_dtor_count);
	ResetCount();
	{
		bksge::unique_ptr<Base> up(nullptr);
		EXPECT_EQ(0, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
	}
	EXPECT_EQ(0, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(0, s_base_dtor_count);
	ResetCount();
	{
		bksge::unique_ptr<Base[]> up;
		EXPECT_EQ(0, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
	}
	EXPECT_EQ(0, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(0, s_base_dtor_count);
	ResetCount();
	{
		bksge::unique_ptr<Base[]> up(nullptr);
		EXPECT_EQ(0, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
	}
	EXPECT_EQ(0, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(0, s_base_dtor_count);
	ResetCount();

	// (2)
	{
		bksge::unique_ptr<Base> up(new Base);
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(0, s_derived_default_ctor_count);
		EXPECT_EQ(0, s_derived_copy_ctor_count);
		EXPECT_EQ(0, s_derived_move_ctor_count);
		EXPECT_EQ(0, s_derived_dtor_count);
		EXPECT_EQ(1, up->func());
		EXPECT_EQ(1, (*up).func());
	}
	EXPECT_EQ(1, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(1, s_base_dtor_count);
	EXPECT_EQ(0, s_derived_default_ctor_count);
	EXPECT_EQ(0, s_derived_copy_ctor_count);
	EXPECT_EQ(0, s_derived_move_ctor_count);
	EXPECT_EQ(0, s_derived_dtor_count);
	ResetCount();
	{
		bksge::unique_ptr<Derived> up(new Derived);
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(1, s_derived_default_ctor_count);
		EXPECT_EQ(0, s_derived_copy_ctor_count);
		EXPECT_EQ(0, s_derived_move_ctor_count);
		EXPECT_EQ(0, s_derived_dtor_count);
		EXPECT_EQ(2, up->func());
		EXPECT_EQ(2, (*up).func());
	}
	EXPECT_EQ(1, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(1, s_base_dtor_count);
	EXPECT_EQ(1, s_derived_default_ctor_count);
	EXPECT_EQ(0, s_derived_copy_ctor_count);
	EXPECT_EQ(0, s_derived_move_ctor_count);
	EXPECT_EQ(1, s_derived_dtor_count);
	ResetCount();
	{
		bksge::unique_ptr<Base> up(new Derived);
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(1, s_derived_default_ctor_count);
		EXPECT_EQ(0, s_derived_copy_ctor_count);
		EXPECT_EQ(0, s_derived_move_ctor_count);
		EXPECT_EQ(0, s_derived_dtor_count);
		EXPECT_EQ(2, up->func());
		EXPECT_EQ(2, (*up).func());
	}
	EXPECT_EQ(1, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(1, s_base_dtor_count);
	EXPECT_EQ(1, s_derived_default_ctor_count);
	EXPECT_EQ(0, s_derived_copy_ctor_count);
	EXPECT_EQ(0, s_derived_move_ctor_count);
	EXPECT_EQ(1, s_derived_dtor_count);
	ResetCount();
	{
		bksge::unique_ptr<Base[]> up(new Base[3]);
		EXPECT_EQ(3, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(0, s_derived_default_ctor_count);
		EXPECT_EQ(0, s_derived_copy_ctor_count);
		EXPECT_EQ(0, s_derived_move_ctor_count);
		EXPECT_EQ(0, s_derived_dtor_count);
		EXPECT_EQ(1, up[0].func());
		EXPECT_EQ(1, up[1].func());
		EXPECT_EQ(1, up[2].func());
	}
	EXPECT_EQ(3, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(3, s_base_dtor_count);
	EXPECT_EQ(0, s_derived_default_ctor_count);
	EXPECT_EQ(0, s_derived_copy_ctor_count);
	EXPECT_EQ(0, s_derived_move_ctor_count);
	EXPECT_EQ(0, s_derived_dtor_count);
	ResetCount();

#if 0
	{
		bksge::unique_ptr<Base[]> up(new Derived[4]);
		EXPECT_EQ(4, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(4, s_derived_default_ctor_count);
		EXPECT_EQ(0, s_derived_copy_ctor_count);
		EXPECT_EQ(0, s_derived_move_ctor_count);
		EXPECT_EQ(0, s_derived_dtor_count);
		EXPECT_EQ(2, up[0].func());
		EXPECT_EQ(2, up[1].func());
		EXPECT_EQ(2, up[2].func());
		EXPECT_EQ(2, up[3].func());
	}
	EXPECT_EQ(4, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(4, s_base_dtor_count);
	EXPECT_EQ(4, s_derived_default_ctor_count);
	EXPECT_EQ(0, s_derived_copy_ctor_count);
	EXPECT_EQ(0, s_derived_move_ctor_count);
//	EXPECT_EQ(4, s_derived_dtor_count);		// TODO
	ResetCount();
#endif

	Deleter d;
	ArrayDeleter d2;

	// (3)
	ResetCount();
	{
		bksge::unique_ptr<Base, Deleter> up(new Base, d);
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(0, s_derived_default_ctor_count);
		EXPECT_EQ(0, s_derived_copy_ctor_count);
		EXPECT_EQ(0, s_derived_move_ctor_count);
		EXPECT_EQ(0, s_derived_dtor_count);
		EXPECT_EQ(0, s_deleter_default_ctor_count);
		EXPECT_EQ(1, s_deleter_copy_ctor_count);
		EXPECT_EQ(0, s_deleter_move_ctor_count);
		EXPECT_EQ(0, s_deleter_dtor_count);
		EXPECT_EQ(0, s_deleter_delete_base_count);
		EXPECT_EQ(0, s_deleter_delete_derived_count);
	}
	EXPECT_EQ(1, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(1, s_base_dtor_count);
	EXPECT_EQ(0, s_derived_default_ctor_count);
	EXPECT_EQ(0, s_derived_copy_ctor_count);
	EXPECT_EQ(0, s_derived_move_ctor_count);
	EXPECT_EQ(0, s_derived_dtor_count);
	EXPECT_EQ(0, s_deleter_default_ctor_count);
	EXPECT_EQ(1, s_deleter_copy_ctor_count);
	EXPECT_EQ(0, s_deleter_move_ctor_count);
	EXPECT_EQ(1, s_deleter_dtor_count);
	EXPECT_EQ(1, s_deleter_delete_base_count);
	EXPECT_EQ(0, s_deleter_delete_derived_count);
	ResetCount();
	{
		bksge::unique_ptr<Base, Deleter&> up(new Base, d);
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(0, s_derived_default_ctor_count);
		EXPECT_EQ(0, s_derived_copy_ctor_count);
		EXPECT_EQ(0, s_derived_move_ctor_count);
		EXPECT_EQ(0, s_derived_dtor_count);
		EXPECT_EQ(0, s_deleter_default_ctor_count);
		EXPECT_EQ(0, s_deleter_copy_ctor_count);
		EXPECT_EQ(0, s_deleter_move_ctor_count);
		EXPECT_EQ(0, s_deleter_dtor_count);
		EXPECT_EQ(0, s_deleter_delete_base_count);
		EXPECT_EQ(0, s_deleter_delete_derived_count);
	}
	EXPECT_EQ(1, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(1, s_base_dtor_count);
	EXPECT_EQ(0, s_derived_default_ctor_count);
	EXPECT_EQ(0, s_derived_copy_ctor_count);
	EXPECT_EQ(0, s_derived_move_ctor_count);
	EXPECT_EQ(0, s_derived_dtor_count);
	EXPECT_EQ(0, s_deleter_default_ctor_count);
	EXPECT_EQ(0, s_deleter_copy_ctor_count);
	EXPECT_EQ(0, s_deleter_move_ctor_count);
	EXPECT_EQ(0, s_deleter_dtor_count);
	EXPECT_EQ(1, s_deleter_delete_base_count);
	EXPECT_EQ(0, s_deleter_delete_derived_count);
	ResetCount();
	{
		bksge::unique_ptr<Base[], ArrayDeleter> up(new Base[2], d2);
		EXPECT_EQ(2, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(0, s_derived_default_ctor_count);
		EXPECT_EQ(0, s_derived_copy_ctor_count);
		EXPECT_EQ(0, s_derived_move_ctor_count);
		EXPECT_EQ(0, s_derived_dtor_count);
		EXPECT_EQ(0, s_deleter_default_ctor_count);
		EXPECT_EQ(1, s_deleter_copy_ctor_count);
		EXPECT_EQ(0, s_deleter_move_ctor_count);
		EXPECT_EQ(0, s_deleter_dtor_count);
		EXPECT_EQ(0, s_deleter_delete_base_count);
		EXPECT_EQ(0, s_deleter_delete_derived_count);
	}
	EXPECT_EQ(2, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(2, s_base_dtor_count);
	EXPECT_EQ(0, s_derived_default_ctor_count);
	EXPECT_EQ(0, s_derived_copy_ctor_count);
	EXPECT_EQ(0, s_derived_move_ctor_count);
	EXPECT_EQ(0, s_derived_dtor_count);
	EXPECT_EQ(0, s_deleter_default_ctor_count);
	EXPECT_EQ(1, s_deleter_copy_ctor_count);
	EXPECT_EQ(0, s_deleter_move_ctor_count);
	EXPECT_EQ(1, s_deleter_dtor_count);
	EXPECT_EQ(1, s_deleter_delete_base_count);
	EXPECT_EQ(0, s_deleter_delete_derived_count);
	ResetCount();
	{
		bksge::unique_ptr<Base[], ArrayDeleter&> up(new Base[4], d2);
		EXPECT_EQ(4, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(0, s_derived_default_ctor_count);
		EXPECT_EQ(0, s_derived_copy_ctor_count);
		EXPECT_EQ(0, s_derived_move_ctor_count);
		EXPECT_EQ(0, s_derived_dtor_count);
		EXPECT_EQ(0, s_deleter_default_ctor_count);
		EXPECT_EQ(0, s_deleter_copy_ctor_count);
		EXPECT_EQ(0, s_deleter_move_ctor_count);
		EXPECT_EQ(0, s_deleter_dtor_count);
		EXPECT_EQ(0, s_deleter_delete_base_count);
		EXPECT_EQ(0, s_deleter_delete_derived_count);
	}
	EXPECT_EQ(4, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(4, s_base_dtor_count);
	EXPECT_EQ(0, s_derived_default_ctor_count);
	EXPECT_EQ(0, s_derived_copy_ctor_count);
	EXPECT_EQ(0, s_derived_move_ctor_count);
	EXPECT_EQ(0, s_derived_dtor_count);
	EXPECT_EQ(0, s_deleter_default_ctor_count);
	EXPECT_EQ(0, s_deleter_copy_ctor_count);
	EXPECT_EQ(0, s_deleter_move_ctor_count);
	EXPECT_EQ(0, s_deleter_dtor_count);
	EXPECT_EQ(1, s_deleter_delete_base_count);
	EXPECT_EQ(0, s_deleter_delete_derived_count);
	ResetCount();

	// (4)
	{
		bksge::unique_ptr<Base, Deleter> up(new Base, Deleter());
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(0, s_derived_default_ctor_count);
		EXPECT_EQ(0, s_derived_copy_ctor_count);
		EXPECT_EQ(0, s_derived_move_ctor_count);
		EXPECT_EQ(0, s_derived_dtor_count);
		EXPECT_EQ(1, s_deleter_default_ctor_count);
		EXPECT_EQ(0, s_deleter_copy_ctor_count);
		EXPECT_EQ(1, s_deleter_move_ctor_count);
		EXPECT_EQ(1, s_deleter_dtor_count);
		EXPECT_EQ(0, s_deleter_delete_base_count);
		EXPECT_EQ(0, s_deleter_delete_derived_count);
	}
	EXPECT_EQ(1, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(1, s_base_dtor_count);
	EXPECT_EQ(0, s_derived_default_ctor_count);
	EXPECT_EQ(0, s_derived_copy_ctor_count);
	EXPECT_EQ(0, s_derived_move_ctor_count);
	EXPECT_EQ(0, s_derived_dtor_count);
	EXPECT_EQ(1, s_deleter_default_ctor_count);
	EXPECT_EQ(0, s_deleter_copy_ctor_count);
	EXPECT_EQ(1, s_deleter_move_ctor_count);
	EXPECT_EQ(2, s_deleter_dtor_count);
	EXPECT_EQ(1, s_deleter_delete_base_count);
	EXPECT_EQ(0, s_deleter_delete_derived_count);
	ResetCount();
	{
		bksge::unique_ptr<Base[], ArrayDeleter> up(new Base[3], ArrayDeleter());
		EXPECT_EQ(3, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(0, s_derived_default_ctor_count);
		EXPECT_EQ(0, s_derived_copy_ctor_count);
		EXPECT_EQ(0, s_derived_move_ctor_count);
		EXPECT_EQ(0, s_derived_dtor_count);
		EXPECT_EQ(1, s_deleter_default_ctor_count);
		EXPECT_EQ(0, s_deleter_copy_ctor_count);
		EXPECT_EQ(1, s_deleter_move_ctor_count);
		EXPECT_EQ(1, s_deleter_dtor_count);
		EXPECT_EQ(0, s_deleter_delete_base_count);
		EXPECT_EQ(0, s_deleter_delete_derived_count);
	}
	EXPECT_EQ(3, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(3, s_base_dtor_count);
	EXPECT_EQ(0, s_derived_default_ctor_count);
	EXPECT_EQ(0, s_derived_copy_ctor_count);
	EXPECT_EQ(0, s_derived_move_ctor_count);
	EXPECT_EQ(0, s_derived_dtor_count);
	EXPECT_EQ(1, s_deleter_default_ctor_count);
	EXPECT_EQ(0, s_deleter_copy_ctor_count);
	EXPECT_EQ(1, s_deleter_move_ctor_count);
	EXPECT_EQ(2, s_deleter_dtor_count);
	EXPECT_EQ(1, s_deleter_delete_base_count);
	EXPECT_EQ(0, s_deleter_delete_derived_count);
	ResetCount();

	// (5)
	{
		bksge::unique_ptr<Base> up1(new Base);
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);

		bksge::unique_ptr<Base> up2(bksge::move(up1));
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
	}
	EXPECT_EQ(1, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(1, s_base_dtor_count);
	ResetCount();
	{
		bksge::unique_ptr<Base[]> up1(new Base[2]);
		EXPECT_EQ(2, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);

		bksge::unique_ptr<Base[]> up2(bksge::move(up1));
		EXPECT_EQ(2, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
	}
	EXPECT_EQ(2, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(2, s_base_dtor_count);
	ResetCount();

	// (6)
	{
		bksge::unique_ptr<Base, Deleter> up1(new Base, d);
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(0, s_deleter_default_ctor_count);
		EXPECT_EQ(1, s_deleter_copy_ctor_count);
		EXPECT_EQ(0, s_deleter_move_ctor_count);
		EXPECT_EQ(0, s_deleter_dtor_count);
		EXPECT_EQ(0, s_deleter_delete_base_count);
		EXPECT_EQ(0, s_deleter_delete_derived_count);

		bksge::unique_ptr<Base, Deleter> up2(bksge::move(up1));
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(0, s_deleter_default_ctor_count);
		EXPECT_EQ(1, s_deleter_copy_ctor_count);
		EXPECT_EQ(1, s_deleter_move_ctor_count);
		EXPECT_EQ(0, s_deleter_dtor_count);
		EXPECT_EQ(0, s_deleter_delete_base_count);
		EXPECT_EQ(0, s_deleter_delete_derived_count);
	}
	EXPECT_EQ(1, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(1, s_base_dtor_count);
	EXPECT_EQ(0, s_deleter_default_ctor_count);
	EXPECT_EQ(1, s_deleter_copy_ctor_count);
	EXPECT_EQ(1, s_deleter_move_ctor_count);
	EXPECT_EQ(2, s_deleter_dtor_count);
	EXPECT_EQ(1, s_deleter_delete_base_count);
	EXPECT_EQ(0, s_deleter_delete_derived_count);
	ResetCount();
	{
		bksge::unique_ptr<Base, Deleter&> up1(new Base, d);
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(0, s_deleter_default_ctor_count);
		EXPECT_EQ(0, s_deleter_copy_ctor_count);
		EXPECT_EQ(0, s_deleter_move_ctor_count);
		EXPECT_EQ(0, s_deleter_dtor_count);
		EXPECT_EQ(0, s_deleter_delete_base_count);
		EXPECT_EQ(0, s_deleter_delete_derived_count);

		bksge::unique_ptr<Base, Deleter> up2(bksge::move(up1));
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(0, s_deleter_default_ctor_count);
		EXPECT_EQ(1, s_deleter_copy_ctor_count);
		EXPECT_EQ(0, s_deleter_move_ctor_count);
		EXPECT_EQ(0, s_deleter_dtor_count);
		EXPECT_EQ(0, s_deleter_delete_base_count);
		EXPECT_EQ(0, s_deleter_delete_derived_count);
	}
	EXPECT_EQ(1, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(1, s_base_dtor_count);
	EXPECT_EQ(0, s_deleter_default_ctor_count);
	EXPECT_EQ(1, s_deleter_copy_ctor_count);
	EXPECT_EQ(0, s_deleter_move_ctor_count);
	EXPECT_EQ(1, s_deleter_dtor_count);
	EXPECT_EQ(1, s_deleter_delete_base_count);
	EXPECT_EQ(0, s_deleter_delete_derived_count);
	ResetCount();
	{
		bksge::unique_ptr<Base, Deleter&> up1(new Base, d);
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(0, s_deleter_default_ctor_count);
		EXPECT_EQ(0, s_deleter_copy_ctor_count);
		EXPECT_EQ(0, s_deleter_move_ctor_count);
		EXPECT_EQ(0, s_deleter_dtor_count);
		EXPECT_EQ(0, s_deleter_delete_base_count);
		EXPECT_EQ(0, s_deleter_delete_derived_count);

		bksge::unique_ptr<Base, Deleter&> up2(bksge::move(up1));
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(0, s_deleter_default_ctor_count);
		EXPECT_EQ(0, s_deleter_copy_ctor_count);
		EXPECT_EQ(0, s_deleter_move_ctor_count);
		EXPECT_EQ(0, s_deleter_dtor_count);
		EXPECT_EQ(0, s_deleter_delete_base_count);
		EXPECT_EQ(0, s_deleter_delete_derived_count);
	}
	EXPECT_EQ(1, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(1, s_base_dtor_count);
	EXPECT_EQ(0, s_deleter_default_ctor_count);
	EXPECT_EQ(0, s_deleter_copy_ctor_count);
	EXPECT_EQ(0, s_deleter_move_ctor_count);
	EXPECT_EQ(0, s_deleter_dtor_count);
	EXPECT_EQ(1, s_deleter_delete_base_count);
	EXPECT_EQ(0, s_deleter_delete_derived_count);
	ResetCount();

	{
		bksge::unique_ptr<Base[], ArrayDeleter&> up1(new Base[5], d2);
		EXPECT_EQ(5, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(0, s_deleter_default_ctor_count);
		EXPECT_EQ(0, s_deleter_copy_ctor_count);
		EXPECT_EQ(0, s_deleter_move_ctor_count);
		EXPECT_EQ(0, s_deleter_dtor_count);
		EXPECT_EQ(0, s_deleter_delete_base_count);
		EXPECT_EQ(0, s_deleter_delete_derived_count);

		bksge::unique_ptr<Base[], ArrayDeleter> up2(bksge::move(up1));
		EXPECT_EQ(5, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(0, s_deleter_default_ctor_count);
		EXPECT_EQ(1, s_deleter_copy_ctor_count);
		EXPECT_EQ(0, s_deleter_move_ctor_count);
		EXPECT_EQ(0, s_deleter_dtor_count);
		EXPECT_EQ(0, s_deleter_delete_base_count);
		EXPECT_EQ(0, s_deleter_delete_derived_count);
	}
	EXPECT_EQ(5, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(5, s_base_dtor_count);
	EXPECT_EQ(0, s_deleter_default_ctor_count);
	EXPECT_EQ(1, s_deleter_copy_ctor_count);
	EXPECT_EQ(0, s_deleter_move_ctor_count);
	EXPECT_EQ(1, s_deleter_dtor_count);
	EXPECT_EQ(1, s_deleter_delete_base_count);
	EXPECT_EQ(0, s_deleter_delete_derived_count);
	ResetCount();

	{
		bksge::unique_ptr<Base[], ArrayDeleter&> up1(nullptr, d2);
		EXPECT_EQ(0, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(0, s_deleter_default_ctor_count);
		EXPECT_EQ(0, s_deleter_copy_ctor_count);
		EXPECT_EQ(0, s_deleter_move_ctor_count);
		EXPECT_EQ(0, s_deleter_dtor_count);
		EXPECT_EQ(0, s_deleter_delete_base_count);
		EXPECT_EQ(0, s_deleter_delete_derived_count);
	}
	EXPECT_EQ(0, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(0, s_base_dtor_count);
	EXPECT_EQ(0, s_deleter_default_ctor_count);
	EXPECT_EQ(0, s_deleter_copy_ctor_count);
	EXPECT_EQ(0, s_deleter_move_ctor_count);
	EXPECT_EQ(0, s_deleter_dtor_count);
	EXPECT_EQ(0, s_deleter_delete_base_count);
	EXPECT_EQ(0, s_deleter_delete_derived_count);
	ResetCount();

	{
		bksge::unique_ptr<Base[], ArrayDeleter> up1(nullptr, ArrayDeleter());
		EXPECT_EQ(0, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_EQ(1, s_deleter_default_ctor_count);
		EXPECT_EQ(0, s_deleter_copy_ctor_count);
		EXPECT_EQ(1, s_deleter_move_ctor_count);
		EXPECT_EQ(1, s_deleter_dtor_count);
		EXPECT_EQ(0, s_deleter_delete_base_count);
		EXPECT_EQ(0, s_deleter_delete_derived_count);
	}
	EXPECT_EQ(0, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(0, s_base_dtor_count);
	EXPECT_EQ(1, s_deleter_default_ctor_count);
	EXPECT_EQ(0, s_deleter_copy_ctor_count);
	EXPECT_EQ(1, s_deleter_move_ctor_count);
	EXPECT_EQ(2, s_deleter_dtor_count);
	EXPECT_EQ(0, s_deleter_delete_base_count);
	EXPECT_EQ(0, s_deleter_delete_derived_count);
	ResetCount();
}

GTEST_TEST(UniquePtrTest, AssignTest)
{
	ResetCount();
	{
		bksge::unique_ptr<Base> up1;
		EXPECT_EQ(0, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		{
			bksge::unique_ptr<Base> up2(new Base);
			EXPECT_EQ(1, s_base_default_ctor_count);
			EXPECT_EQ(0, s_base_copy_ctor_count);
			EXPECT_EQ(0, s_base_move_ctor_count);
			EXPECT_EQ(0, s_base_dtor_count);
			EXPECT_TRUE (up1.get() == nullptr);
			EXPECT_FALSE(up2.get() == nullptr);

			up1 = bksge::move(up2);
			EXPECT_EQ(1, s_base_default_ctor_count);
			EXPECT_EQ(0, s_base_copy_ctor_count);
			EXPECT_EQ(0, s_base_move_ctor_count);
			EXPECT_EQ(0, s_base_dtor_count);
			EXPECT_FALSE(up1.get() == nullptr);
			EXPECT_TRUE (up2.get() == nullptr);
		}
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);

		up1 = nullptr;
		EXPECT_TRUE (up1.get() == nullptr);

		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(1, s_base_dtor_count);
	}
	EXPECT_EQ(1, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(1, s_base_dtor_count);

	{
		Deleter d;
		ResetCount();

		bksge::unique_ptr<Base, Deleter> up1;
		EXPECT_EQ(0, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		{
			bksge::unique_ptr<Base, Deleter&> up2(new Base, d);
			EXPECT_EQ(1, s_base_default_ctor_count);
			EXPECT_EQ(0, s_base_copy_ctor_count);
			EXPECT_EQ(0, s_base_move_ctor_count);
			EXPECT_EQ(0, s_base_dtor_count);
			EXPECT_TRUE (up1.get() == nullptr);
			EXPECT_FALSE(up2.get() == nullptr);

			up1 = bksge::move(up2);
			EXPECT_EQ(1, s_base_default_ctor_count);
			EXPECT_EQ(0, s_base_copy_ctor_count);
			EXPECT_EQ(0, s_base_move_ctor_count);
			EXPECT_EQ(0, s_base_dtor_count);
			EXPECT_FALSE(up1.get() == nullptr);
			EXPECT_TRUE (up2.get() == nullptr);
		}
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
	}
	EXPECT_EQ(1, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(1, s_base_dtor_count);

	ResetCount();
	{
		bksge::unique_ptr<Base[]> up1;
		EXPECT_EQ(0, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		{
			bksge::unique_ptr<Base[]> up2(new Base[2]);
			EXPECT_EQ(2, s_base_default_ctor_count);
			EXPECT_EQ(0, s_base_copy_ctor_count);
			EXPECT_EQ(0, s_base_move_ctor_count);
			EXPECT_EQ(0, s_base_dtor_count);
			EXPECT_TRUE (up1.get() == nullptr);
			EXPECT_FALSE(up2.get() == nullptr);

			up1 = bksge::move(up2);
			EXPECT_EQ(2, s_base_default_ctor_count);
			EXPECT_EQ(0, s_base_copy_ctor_count);
			EXPECT_EQ(0, s_base_move_ctor_count);
			EXPECT_EQ(0, s_base_dtor_count);
			EXPECT_FALSE(up1.get() == nullptr);
			EXPECT_TRUE (up2.get() == nullptr);
		}
		EXPECT_EQ(2, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);

		up1 = nullptr;
		EXPECT_TRUE (up1.get() == nullptr);

		EXPECT_EQ(2, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(2, s_base_dtor_count);
	}
	EXPECT_EQ(2, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(2, s_base_dtor_count);

	{
		ArrayDeleter d;
		ResetCount();

		bksge::unique_ptr<Base[], ArrayDeleter> up1;
		EXPECT_EQ(0, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		{
			bksge::unique_ptr<Base[], ArrayDeleter&> up2(new Base[2], d);
			EXPECT_EQ(2, s_base_default_ctor_count);
			EXPECT_EQ(0, s_base_copy_ctor_count);
			EXPECT_EQ(0, s_base_move_ctor_count);
			EXPECT_EQ(0, s_base_dtor_count);
			EXPECT_TRUE (up1.get() == nullptr);
			EXPECT_FALSE(up2.get() == nullptr);

			up1 = bksge::move(up2);
			EXPECT_EQ(2, s_base_default_ctor_count);
			EXPECT_EQ(0, s_base_copy_ctor_count);
			EXPECT_EQ(0, s_base_move_ctor_count);
			EXPECT_EQ(0, s_base_dtor_count);
			EXPECT_FALSE(up1.get() == nullptr);
			EXPECT_TRUE (up2.get() == nullptr);
		}
		EXPECT_EQ(2, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
	}
	EXPECT_EQ(2, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(2, s_base_dtor_count);
}

GTEST_TEST(UniquePtrTest, ReleaseTest)
{
	ResetCount();
	{
		bksge::unique_ptr<Base> up(new Base);
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_FALSE(up.get() == nullptr);

		Base* p = up.release();

		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_TRUE(up.get() == nullptr);

		delete p;

		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(1, s_base_dtor_count);
	}
	EXPECT_EQ(1, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(1, s_base_dtor_count);

	ResetCount();
	{
		bksge::unique_ptr<Base[]> up(new Base[3]);
		EXPECT_EQ(3, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_FALSE(up.get() == nullptr);

		Base* p = up.release();

		EXPECT_EQ(3, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_TRUE(up.get() == nullptr);

		delete[] p;

		EXPECT_EQ(3, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(3, s_base_dtor_count);
	}
	EXPECT_EQ(3, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(3, s_base_dtor_count);
}

GTEST_TEST(UniquePtrTest, ResetTest)
{
	ResetCount();
	{
		bksge::unique_ptr<Base> up(new Base);
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_FALSE(up.get() == nullptr);
		EXPECT_TRUE(!!up);

		up.reset(new Base);

		EXPECT_EQ(2, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(1, s_base_dtor_count);
		EXPECT_FALSE(up.get() == nullptr);
		EXPECT_TRUE(!!up);
	}
	EXPECT_EQ(2, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(2, s_base_dtor_count);

	ResetCount();
	{
		bksge::unique_ptr<Base> up(new Base);
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_FALSE(up.get() == nullptr);
		EXPECT_TRUE(!!up);

		up.reset(new Derived);

		EXPECT_EQ(2, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(1, s_base_dtor_count);
		EXPECT_FALSE(up.get() == nullptr);
		EXPECT_TRUE(!!up);
	}
	EXPECT_EQ(2, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(2, s_base_dtor_count);

	ResetCount();
	{
		bksge::unique_ptr<Base> up(new Base);
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_FALSE(up.get() == nullptr);
		EXPECT_TRUE(!!up);

		up.reset(nullptr);

		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(1, s_base_dtor_count);
		EXPECT_TRUE(up.get() == nullptr);
		EXPECT_FALSE(!!up);
	}
	EXPECT_EQ(1, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(1, s_base_dtor_count);

	ResetCount();
	{
		bksge::unique_ptr<Base> up(new Base);
		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_FALSE(up.get() == nullptr);
		EXPECT_TRUE(!!up);

		up.reset();

		EXPECT_EQ(1, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(1, s_base_dtor_count);
		EXPECT_TRUE(up.get() == nullptr);
		EXPECT_FALSE(!!up);
	}
	EXPECT_EQ(1, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(1, s_base_dtor_count);

	ResetCount();
	{
		bksge::unique_ptr<Base[]> up(new Base[2]);
		EXPECT_EQ(2, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_FALSE(up.get() == nullptr);
		EXPECT_TRUE(!!up);

		up.reset(new Base[3]);

		EXPECT_EQ(5, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(2, s_base_dtor_count);
		EXPECT_FALSE(up.get() == nullptr);
		EXPECT_TRUE(!!up);
	}
	EXPECT_EQ(5, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(5, s_base_dtor_count);

#if 0
	ResetCount();
	{
		bksge::unique_ptr<Base[]> up(new Base[2]);
		EXPECT_EQ(2, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_FALSE(up.get() == nullptr);
		EXPECT_TRUE(!!up);

		up.reset(new Derived[3]);

		EXPECT_EQ(5, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(2, s_base_dtor_count);
		EXPECT_FALSE(up.get() == nullptr);
		EXPECT_TRUE(!!up);
	}
	EXPECT_EQ(5, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(5, s_base_dtor_count);
#endif

	ResetCount();
	{
		bksge::unique_ptr<Base[]> up(new Base[2]);
		EXPECT_EQ(2, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_FALSE(up.get() == nullptr);
		EXPECT_TRUE(!!up);

		up.reset(nullptr);

		EXPECT_EQ(2, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(2, s_base_dtor_count);
		EXPECT_TRUE(up.get() == nullptr);
		EXPECT_FALSE(!!up);
	}
	EXPECT_EQ(2, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(2, s_base_dtor_count);

	ResetCount();
	{
		bksge::unique_ptr<Base[]> up(new Base[2]);
		EXPECT_EQ(2, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(0, s_base_dtor_count);
		EXPECT_FALSE(up.get() == nullptr);
		EXPECT_TRUE(!!up);

		up.reset();

		EXPECT_EQ(2, s_base_default_ctor_count);
		EXPECT_EQ(0, s_base_copy_ctor_count);
		EXPECT_EQ(0, s_base_move_ctor_count);
		EXPECT_EQ(2, s_base_dtor_count);
		EXPECT_TRUE(up.get() == nullptr);
		EXPECT_FALSE(!!up);
	}
	EXPECT_EQ(2, s_base_default_ctor_count);
	EXPECT_EQ(0, s_base_copy_ctor_count);
	EXPECT_EQ(0, s_base_move_ctor_count);
	EXPECT_EQ(2, s_base_dtor_count);
}

GTEST_TEST(UniquePtrTest, SwapTest)
{
	{
		bksge::unique_ptr<int> up1(new int(2));
		bksge::unique_ptr<int> up2(new int(3));

		EXPECT_EQ(2, *up1);
		EXPECT_EQ(3, *up2);

		up1.swap(up2);

		EXPECT_EQ(3, *up1);
		EXPECT_EQ(2, *up2);

		swap(up1, up2);

		EXPECT_EQ(2, *up1);
		EXPECT_EQ(3, *up2);
	}
	{
		bksge::unique_ptr<int[]> up1(new int[3]);
		bksge::unique_ptr<int[]> up2(new int[4]);

		up1[0] = 1;
		up1[1] = 2;
		up1[2] = 3;
		up2[0] = 4;
		up2[1] = 5;
		up2[2] = 6;
		up2[3] = 7;

		EXPECT_EQ(1, up1[0]);
		EXPECT_EQ(2, up1[1]);
		EXPECT_EQ(3, up1[2]);
		EXPECT_EQ(4, up2[0]);
		EXPECT_EQ(5, up2[1]);
		EXPECT_EQ(6, up2[2]);
		EXPECT_EQ(7, up2[3]);

		up1.swap(up2);

		EXPECT_EQ(4, up1[0]);
		EXPECT_EQ(5, up1[1]);
		EXPECT_EQ(6, up1[2]);
		EXPECT_EQ(7, up1[3]);
		EXPECT_EQ(1, up2[0]);
		EXPECT_EQ(2, up2[1]);
		EXPECT_EQ(3, up2[2]);

		swap(up1, up2);

		EXPECT_EQ(1, up1[0]);
		EXPECT_EQ(2, up1[1]);
		EXPECT_EQ(3, up1[2]);
		EXPECT_EQ(4, up2[0]);
		EXPECT_EQ(5, up2[1]);
		EXPECT_EQ(6, up2[2]);
		EXPECT_EQ(7, up2[3]);
	}
}

GTEST_TEST(UniquePtrTest, GetDeleterTest)
{
	{
		bksge::unique_ptr<Base, Deleter> up(new Base, Deleter(42));
		Deleter& d = up.get_deleter();
		EXPECT_EQ(42, d.m_value);
	}
	{
		bksge::unique_ptr<Base, Deleter> const up(new Base, Deleter(42));
		Deleter const& d = up.get_deleter();
		EXPECT_EQ(42, d.m_value);
	}
	{
		bksge::unique_ptr<Base[], ArrayDeleter> up(new Base[2], ArrayDeleter(42));
		ArrayDeleter& d = up.get_deleter();
		EXPECT_EQ(42, d.m_value);
	}
	{
		bksge::unique_ptr<Base[], ArrayDeleter> const up(new Base[2], ArrayDeleter(42));
		ArrayDeleter const& d = up.get_deleter();
		EXPECT_EQ(42, d.m_value);
	}
}

GTEST_TEST(UniquePtrTest, IndexedAccessTest)
{
	int size = 10;

	bksge::unique_ptr<int[]> up(new int[size]);
	
	for (int i = 0; i < size; ++i)
	{
		up[i] = i * 2;
	}
	EXPECT_EQ( 0, up[0]);
	EXPECT_EQ( 2, up[1]);
	EXPECT_EQ( 4, up[2]);
	EXPECT_EQ(18, up[9]);
}

GTEST_TEST(UniquePtrTest, CompareTest)
{
	bksge::unique_ptr<int> up1(new int(42));
	bksge::unique_ptr<int> up2(new int(42));
	bksge::unique_ptr<int> up3;

	EXPECT_TRUE (up1 == up1);
	EXPECT_FALSE(up1 == up2);
	EXPECT_FALSE(up1 == up3);
	EXPECT_FALSE(up1 != up1);
	EXPECT_TRUE (up1 != up2);
	EXPECT_TRUE (up1 != up3);
	EXPECT_FALSE(up1 <  up1);
//	EXPECT_FALSE(up1 <  up2);
	EXPECT_FALSE(up1 <  up3);
	EXPECT_FALSE(up1 >  up1);
//	EXPECT_FALSE(up1 >  up1);
	EXPECT_TRUE (up1 >  up3);
	EXPECT_TRUE (up1 <= up1);
//	EXPECT_FALSE(up1 <= up2);
	EXPECT_FALSE(up1 <= up3);
	EXPECT_TRUE (up1 >= up1);
//	EXPECT_FALSE(up1 >= up1);
	EXPECT_TRUE (up1 >= up3);
	EXPECT_FALSE(up1 == nullptr);
	EXPECT_FALSE(up2 == nullptr);
	EXPECT_TRUE (up3 == nullptr);
	EXPECT_TRUE (up1 != nullptr);
	EXPECT_TRUE (up2 != nullptr);
	EXPECT_FALSE(up3 != nullptr);
	EXPECT_FALSE(up1 <  nullptr);
	EXPECT_FALSE(up2 <  nullptr);
	EXPECT_FALSE(up3 <  nullptr);
	EXPECT_TRUE (up1 >  nullptr);
	EXPECT_TRUE (up2 >  nullptr);
	EXPECT_FALSE(up3 >  nullptr);
	EXPECT_FALSE(up1 <= nullptr);
	EXPECT_FALSE(up2 <= nullptr);
	EXPECT_TRUE (up3 <= nullptr);
	EXPECT_TRUE (up1 >= nullptr);
	EXPECT_TRUE (up2 >= nullptr);
	EXPECT_TRUE (up3 >= nullptr);
	EXPECT_FALSE(nullptr == up1);
	EXPECT_FALSE(nullptr == up2);
	EXPECT_TRUE (nullptr == up3);
	EXPECT_TRUE (nullptr != up1);
	EXPECT_TRUE (nullptr != up2);
	EXPECT_FALSE(nullptr != up3);
	EXPECT_TRUE (nullptr <  up1);
	EXPECT_TRUE (nullptr <  up2);
	EXPECT_FALSE(nullptr <  up3);
	EXPECT_FALSE(nullptr >  up1);
	EXPECT_FALSE(nullptr >  up2);
	EXPECT_FALSE(nullptr >  up3);
	EXPECT_TRUE (nullptr <= up1);
	EXPECT_TRUE (nullptr <= up2);
	EXPECT_TRUE (nullptr <= up3);
	EXPECT_FALSE(nullptr >= up1);
	EXPECT_FALSE(nullptr >= up2);
	EXPECT_TRUE (nullptr >= up3);
}

GTEST_TEST(UniquePtrTest, HashTest)
{
	{
		const bksge::unique_ptr<int> up1;
		const bksge::unique_ptr<int> up2;
		EXPECT_EQ(
			std::hash<bksge::unique_ptr<int>>()(up1),
			std::hash<bksge::unique_ptr<int>>()(up2));
	}
	{
		const bksge::unique_ptr<int> up1(new int(42));
		const bksge::unique_ptr<int> up2(new int(42));
		EXPECT_NE(
			std::hash<bksge::unique_ptr<int>>()(up1),
			std::hash<bksge::unique_ptr<int>>()(up2));
	}
}

}	// namespace unique_ptr_test

}	// namespace bksge_memory_test
