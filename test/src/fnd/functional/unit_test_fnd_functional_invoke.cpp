/**
 *	@file	unit_test_fnd_functional_invoke.cpp
 *
 *	@brief	invoke のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/functional/ref.hpp>
#include <bksge/fnd/functional/cref.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_functional_test
{

namespace invoke_test
{

BKSGE_CONSTEXPR int function1()
{
	return 0;
}

BKSGE_CONSTEXPR int function2(float)
{
	return 1;
}

BKSGE_CONSTEXPR int function3(int, float)
{
	return 2;
}

int throw_func(int);
int nothrow_func(int) BKSGE_NOEXCEPT;

struct Foo
{
	BKSGE_CONSTEXPR int operator()() const
	{
		return 3;
	}

	BKSGE_CONSTEXPR int member_func() const
	{
		return 4;
	}

	int throw_member_func();
	int nothrow_member_func() BKSGE_NOEXCEPT;
};

struct Base
{
	BKSGE_CONSTEXPR int nonvirtual_func(int) const
	{
		return 5;
	}

	virtual int virtual_func() const
	{
		return 6;
	}
};

struct Derived : public Base
{
	BKSGE_CONSTEXPR int nonvirtual_func(int, int) const
	{
		return 7;
	}

	virtual int virtual_func() const
	{
		return 8;
	}
};

struct Bar
{
	int f1()
	{
		return 9;
	}

	int f2() const
	{
		return 10;
	}

	int f3() volatile
	{
		return 11;
	}

	int f4() const volatile
	{
		return 12;
	}

	Bar()
		: x(17)
		, y(18)
		, z(19)
		, w(20)
	{}

	int x;
	const int y;
	volatile int z;
	const volatile int w;

private:
	Bar& operator=(const Bar&);
};

GTEST_TEST(FunctionalTest, InvokeTest)
{
#if 1
	static_assert(!noexcept(throw_func(0)), "");
	static_assert( noexcept(nothrow_func(0)), "");
	static_assert(!noexcept(bksge::invoke(throw_func, 0)), "");
	// TODO
//	static_assert( noexcept(bksge::invoke(nothrow_func, 0)), "");

	{
		Foo f{};
		static_assert(!noexcept(f.throw_member_func()), "");
		static_assert( noexcept(f.nothrow_member_func()), "");
		static_assert(!noexcept(bksge::invoke(&Foo::throw_member_func, &f)), "");
		// TODO
//		static_assert( noexcept(bksge::invoke(&Foo::nothrow_member_func, &f)), "");
	}
	// TODO
	//{
	//	Bar bar;
	//	static_assert( noexcept(bksge::invoke(&Bar::x, bar)), "");
	//	static_assert( noexcept(bksge::invoke(&Bar::x, &bar)), "");
	//	static_assert( noexcept(bksge::invoke(&Bar::x, bksge::ref(bar))), "");
	//	static_assert( noexcept(bksge::invoke(&Bar::x, bksge::cref(bar))), "");
	//}
#endif
	{
		BKSGE_CONSTEXPR Foo f{};
		BKSGE_CONSTEXPR Base b{};
		BKSGE_CONSTEXPR Derived d{};

		/*BKSGE_CONSTEXPR_*/EXPECT_EQ(0, bksge::invoke(function1));
		/*BKSGE_CONSTEXPR_*/EXPECT_EQ(1, bksge::invoke(function2, 0.0f));
		/*BKSGE_CONSTEXPR_*/EXPECT_EQ(2, bksge::invoke(function3, 0, 0.0f));
		/*BKSGE_CONSTEXPR_*/EXPECT_EQ(3, bksge::invoke(f));
		/*BKSGE_CONSTEXPR_*/EXPECT_EQ(4, bksge::invoke(&Foo::member_func, f));
		/*BKSGE_CONSTEXPR_*/EXPECT_EQ(4, bksge::invoke(&Foo::member_func, &f));
		/*BKSGE_CONSTEXPR_*/EXPECT_EQ(4, bksge::invoke(&Foo::member_func, bksge::ref(f)));
		/*BKSGE_CONSTEXPR_*/EXPECT_EQ(4, bksge::invoke(&Foo::member_func, bksge::cref(f)));
		/*BKSGE_CONSTEXPR_*/EXPECT_EQ(5, bksge::invoke(&Base::nonvirtual_func, b, 0));
		/*BKSGE_CONSTEXPR_*/EXPECT_EQ(5, bksge::invoke(&Base::nonvirtual_func, &b, 0));
		/*BKSGE_CONSTEXPR_*/EXPECT_EQ(5, bksge::invoke(&Base::nonvirtual_func, bksge::ref(b), 0));
		/*BKSGE_CONSTEXPR_*/EXPECT_EQ(5, bksge::invoke(&Base::nonvirtual_func, bksge::cref(b), 0));
		/*BKSGE_CONSTEXPR_*/EXPECT_EQ(5, bksge::invoke(&Base::nonvirtual_func, d, 0));
		/*                */EXPECT_EQ(5, bksge::invoke(&Base::nonvirtual_func, &d, 0));
		/*BKSGE_CONSTEXPR_*/EXPECT_EQ(5, bksge::invoke(&Base::nonvirtual_func, bksge::ref(d), 0));
		/*BKSGE_CONSTEXPR_*/EXPECT_EQ(5, bksge::invoke(&Base::nonvirtual_func, bksge::cref(d), 0));
		/*                */EXPECT_EQ(6, bksge::invoke(&Base::virtual_func, b));
		/*                */EXPECT_EQ(6, bksge::invoke(&Base::virtual_func, &b));
		/*                */EXPECT_EQ(6, bksge::invoke(&Base::virtual_func, bksge::ref(b)));
		/*                */EXPECT_EQ(6, bksge::invoke(&Base::virtual_func, bksge::cref(b)));
		/*                */EXPECT_EQ(8, bksge::invoke(&Base::virtual_func, d));
		/*                */EXPECT_EQ(8, bksge::invoke(&Base::virtual_func, &d));
		/*                */EXPECT_EQ(8, bksge::invoke(&Base::virtual_func, bksge::ref(d)));
		/*                */EXPECT_EQ(8, bksge::invoke(&Base::virtual_func, bksge::cref(d)));
		/*BKSGE_CONSTEXPR_*/EXPECT_EQ(7, bksge::invoke(&Derived::nonvirtual_func, d, 0, 0));
		/*BKSGE_CONSTEXPR_*/EXPECT_EQ(7, bksge::invoke(&Derived::nonvirtual_func, &d, 0, 0));
		/*BKSGE_CONSTEXPR_*/EXPECT_EQ(7, bksge::invoke(&Derived::nonvirtual_func, bksge::ref(d), 0, 0));
		/*BKSGE_CONSTEXPR_*/EXPECT_EQ(7, bksge::invoke(&Derived::nonvirtual_func, bksge::cref(d), 0, 0));
		/*                */EXPECT_EQ(8, bksge::invoke(&Derived::virtual_func, d));
		/*                */EXPECT_EQ(8, bksge::invoke(&Derived::virtual_func, &d));
		/*                */EXPECT_EQ(8, bksge::invoke(&Derived::virtual_func, bksge::ref(d)));
		/*                */EXPECT_EQ(8, bksge::invoke(&Derived::virtual_func, bksge::cref(d)));
	}
	{
		Bar bar;
		EXPECT_EQ( 9, bksge::invoke(&Bar::f1, bar));
		EXPECT_EQ( 9, bksge::invoke(&Bar::f1, &bar));
		EXPECT_EQ( 9, bksge::invoke(&Bar::f1, bksge::ref(bar)));
//		EXPECT_EQ( 9, bksge::invoke(&Bar::f1, bksge::cref(bar)));
		EXPECT_EQ(10, bksge::invoke(&Bar::f2, bar));
		EXPECT_EQ(10, bksge::invoke(&Bar::f2, &bar));
		EXPECT_EQ(10, bksge::invoke(&Bar::f2, bksge::ref(bar)));
		EXPECT_EQ(10, bksge::invoke(&Bar::f2, bksge::cref(bar)));
		EXPECT_EQ(11, bksge::invoke(&Bar::f3, bar));
		EXPECT_EQ(11, bksge::invoke(&Bar::f3, &bar));
		EXPECT_EQ(11, bksge::invoke(&Bar::f3, bksge::ref(bar)));
//		EXPECT_EQ(11, bksge::invoke(&Bar::f3, bksge::cref(bar)));
		EXPECT_EQ(12, bksge::invoke(&Bar::f4, bar));
		EXPECT_EQ(12, bksge::invoke(&Bar::f4, &bar));
		EXPECT_EQ(12, bksge::invoke(&Bar::f4, bksge::ref(bar)));
		EXPECT_EQ(12, bksge::invoke(&Bar::f4, bksge::cref(bar)));

		EXPECT_EQ(17, bksge::invoke(&Bar::x, bar));
		EXPECT_EQ(17, bksge::invoke(&Bar::x, &bar));
		EXPECT_EQ(17, bksge::invoke(&Bar::x, bksge::ref(bar)));
		EXPECT_EQ(17, bksge::invoke(&Bar::x, bksge::cref(bar)));
		EXPECT_EQ(18, bksge::invoke(&Bar::y, bar));
		EXPECT_EQ(18, bksge::invoke(&Bar::y, &bar));
		EXPECT_EQ(18, bksge::invoke(&Bar::y, bksge::ref(bar)));
		EXPECT_EQ(18, bksge::invoke(&Bar::y, bksge::cref(bar)));
		EXPECT_EQ(19, bksge::invoke(&Bar::z, bar));
		EXPECT_EQ(19, bksge::invoke(&Bar::z, &bar));
		EXPECT_EQ(19, bksge::invoke(&Bar::z, bksge::ref(bar)));
		EXPECT_EQ(19, bksge::invoke(&Bar::z, bksge::cref(bar)));
		EXPECT_EQ(20, bksge::invoke(&Bar::w, bar));
		EXPECT_EQ(20, bksge::invoke(&Bar::w, &bar));
		EXPECT_EQ(20, bksge::invoke(&Bar::w, bksge::ref(bar)));
		EXPECT_EQ(20, bksge::invoke(&Bar::w, bksge::cref(bar)));
	}
	{
		const Bar bar;
//		EXPECT_EQ( 9, bksge::invoke(&Bar::f1, bar));
//		EXPECT_EQ( 9, bksge::invoke(&Bar::f1, &bar));
//		EXPECT_EQ( 9, bksge::invoke(&Bar::f1, bksge::ref(bar)));
//		EXPECT_EQ( 9, bksge::invoke(&Bar::f1, bksge::cref(bar)));
		EXPECT_EQ(10, bksge::invoke(&Bar::f2, bar));
		EXPECT_EQ(10, bksge::invoke(&Bar::f2, &bar));
		EXPECT_EQ(10, bksge::invoke(&Bar::f2, bksge::ref(bar)));
		EXPECT_EQ(10, bksge::invoke(&Bar::f2, bksge::cref(bar)));
//		EXPECT_EQ(11, bksge::invoke(&Bar::f3, bar));
//		EXPECT_EQ(11, bksge::invoke(&Bar::f3, &bar));
//		EXPECT_EQ(11, bksge::invoke(&Bar::f3, bksge::ref(bar)));
//		EXPECT_EQ(11, bksge::invoke(&Bar::f3, bksge::cref(bar)));
		EXPECT_EQ(12, bksge::invoke(&Bar::f4, bar));
		EXPECT_EQ(12, bksge::invoke(&Bar::f4, &bar));
		EXPECT_EQ(12, bksge::invoke(&Bar::f4, bksge::ref(bar)));
		EXPECT_EQ(12, bksge::invoke(&Bar::f4, bksge::cref(bar)));

		EXPECT_EQ(17, bksge::invoke(&Bar::x, bar));
		EXPECT_EQ(17, bksge::invoke(&Bar::x, &bar));
		EXPECT_EQ(17, bksge::invoke(&Bar::x, bksge::ref(bar)));
		EXPECT_EQ(17, bksge::invoke(&Bar::x, bksge::cref(bar)));
		EXPECT_EQ(18, bksge::invoke(&Bar::y, bar));
		EXPECT_EQ(18, bksge::invoke(&Bar::y, &bar));
		EXPECT_EQ(18, bksge::invoke(&Bar::y, bksge::ref(bar)));
		EXPECT_EQ(18, bksge::invoke(&Bar::y, bksge::cref(bar)));
		EXPECT_EQ(19, bksge::invoke(&Bar::z, bar));
		EXPECT_EQ(19, bksge::invoke(&Bar::z, &bar));
		EXPECT_EQ(19, bksge::invoke(&Bar::z, bksge::ref(bar)));
		EXPECT_EQ(19, bksge::invoke(&Bar::z, bksge::cref(bar)));
		EXPECT_EQ(20, bksge::invoke(&Bar::w, bar));
		EXPECT_EQ(20, bksge::invoke(&Bar::w, &bar));
		EXPECT_EQ(20, bksge::invoke(&Bar::w, bksge::ref(bar)));
		EXPECT_EQ(20, bksge::invoke(&Bar::w, bksge::cref(bar)));
	}
	{
		volatile Bar bar;
//		EXPECT_EQ( 9, bksge::invoke(&Bar::f1, bar));
//		EXPECT_EQ( 9, bksge::invoke(&Bar::f1, &bar));
//		EXPECT_EQ( 9, bksge::invoke(&Bar::f1, bksge::ref(bar)));
//		EXPECT_EQ( 9, bksge::invoke(&Bar::f1, bksge::cref(bar)));
//		EXPECT_EQ(10, bksge::invoke(&Bar::f2, bar));
//		EXPECT_EQ(10, bksge::invoke(&Bar::f2, &bar));
//		EXPECT_EQ(10, bksge::invoke(&Bar::f2, bksge::ref(bar)));
//		EXPECT_EQ(10, bksge::invoke(&Bar::f2, bksge::cref(bar)));
		EXPECT_EQ(11, bksge::invoke(&Bar::f3, bar));
		EXPECT_EQ(11, bksge::invoke(&Bar::f3, &bar));
		EXPECT_EQ(11, bksge::invoke(&Bar::f3, bksge::ref(bar)));
//		EXPECT_EQ(11, bksge::invoke(&Bar::f3, bksge::cref(bar)));
		EXPECT_EQ(12, bksge::invoke(&Bar::f4, bar));
		EXPECT_EQ(12, bksge::invoke(&Bar::f4, &bar));
		EXPECT_EQ(12, bksge::invoke(&Bar::f4, bksge::ref(bar)));
		EXPECT_EQ(12, bksge::invoke(&Bar::f4, bksge::cref(bar)));

		EXPECT_EQ(17, bksge::invoke(&Bar::x, bar));
		EXPECT_EQ(17, bksge::invoke(&Bar::x, &bar));
		EXPECT_EQ(17, bksge::invoke(&Bar::x, bksge::ref(bar)));
		EXPECT_EQ(17, bksge::invoke(&Bar::x, bksge::cref(bar)));
		EXPECT_EQ(18, bksge::invoke(&Bar::y, bar));
		EXPECT_EQ(18, bksge::invoke(&Bar::y, &bar));
		EXPECT_EQ(18, bksge::invoke(&Bar::y, bksge::ref(bar)));
		EXPECT_EQ(18, bksge::invoke(&Bar::y, bksge::cref(bar)));
		EXPECT_EQ(19, bksge::invoke(&Bar::z, bar));
		EXPECT_EQ(19, bksge::invoke(&Bar::z, &bar));
		EXPECT_EQ(19, bksge::invoke(&Bar::z, bksge::ref(bar)));
		EXPECT_EQ(19, bksge::invoke(&Bar::z, bksge::cref(bar)));
		EXPECT_EQ(20, bksge::invoke(&Bar::w, bar));
		EXPECT_EQ(20, bksge::invoke(&Bar::w, &bar));
		EXPECT_EQ(20, bksge::invoke(&Bar::w, bksge::ref(bar)));
		EXPECT_EQ(20, bksge::invoke(&Bar::w, bksge::cref(bar)));
	}
	{
		const volatile Bar bar;
//		EXPECT_EQ( 9, bksge::invoke(&Bar::f1, bar));
//		EXPECT_EQ( 9, bksge::invoke(&Bar::f1, &bar));
//		EXPECT_EQ( 9, bksge::invoke(&Bar::f1, bksge::ref(bar)));
//		EXPECT_EQ( 9, bksge::invoke(&Bar::f1, bksge::cref(bar)));
//		EXPECT_EQ(10, bksge::invoke(&Bar::f2, bar));
//		EXPECT_EQ(10, bksge::invoke(&Bar::f2, &bar));
//		EXPECT_EQ(10, bksge::invoke(&Bar::f2, bksge::ref(bar)));
//		EXPECT_EQ(10, bksge::invoke(&Bar::f2, bksge::cref(bar)));
//		EXPECT_EQ(11, bksge::invoke(&Bar::f3, bar));
//		EXPECT_EQ(11, bksge::invoke(&Bar::f3, &bar));
//		EXPECT_EQ(11, bksge::invoke(&Bar::f3, bksge::ref(bar)));
//		EXPECT_EQ(11, bksge::invoke(&Bar::f3, bksge::cref(bar)));
		EXPECT_EQ(12, bksge::invoke(&Bar::f4, bar));
		EXPECT_EQ(12, bksge::invoke(&Bar::f4, &bar));
		EXPECT_EQ(12, bksge::invoke(&Bar::f4, bksge::ref(bar)));
		EXPECT_EQ(12, bksge::invoke(&Bar::f4, bksge::cref(bar)));

		EXPECT_EQ(17, bksge::invoke(&Bar::x, bar));
		EXPECT_EQ(17, bksge::invoke(&Bar::x, &bar));
		EXPECT_EQ(17, bksge::invoke(&Bar::x, bksge::ref(bar)));
		EXPECT_EQ(17, bksge::invoke(&Bar::x, bksge::cref(bar)));
		EXPECT_EQ(18, bksge::invoke(&Bar::y, bar));
		EXPECT_EQ(18, bksge::invoke(&Bar::y, &bar));
		EXPECT_EQ(18, bksge::invoke(&Bar::y, bksge::ref(bar)));
		EXPECT_EQ(18, bksge::invoke(&Bar::y, bksge::cref(bar)));
		EXPECT_EQ(19, bksge::invoke(&Bar::z, bar));
		EXPECT_EQ(19, bksge::invoke(&Bar::z, &bar));
		EXPECT_EQ(19, bksge::invoke(&Bar::z, bksge::ref(bar)));
		EXPECT_EQ(19, bksge::invoke(&Bar::z, bksge::cref(bar)));
		EXPECT_EQ(20, bksge::invoke(&Bar::w, bar));
		EXPECT_EQ(20, bksge::invoke(&Bar::w, &bar));
		EXPECT_EQ(20, bksge::invoke(&Bar::w, bksge::ref(bar)));
		EXPECT_EQ(20, bksge::invoke(&Bar::w, bksge::cref(bar)));
	}
}

}	// namespace invoke_test

}	// namespace bksge_functional_test
