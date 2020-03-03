/**
 *	@file	unit_test_fnd_functional_reference_wrapper.cpp
 *
 *	@brief	reference_wrapper のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/reference_wrapper.hpp>
#include <bksge/fnd/functional/ref.hpp>
#include <bksge/fnd/functional/cref.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_trivially_copyable.hpp>
#include <gtest/gtest.h>

namespace bksge_functional_test
{

namespace reference_wrapper_test
{

struct test_type
{
};

struct functor1
{
	double operator()(int) const;
};

struct functor2
{
	double operator()(int, char) const;
};

struct OverloadedAddress
{
	struct Aux{};
	Aux operator&() const { return Aux(); }
};

int trunc(float x)
{
	return static_cast<int>(x);
}

struct X
{
	X() : bar(17) {}

	int foo(float x)                   { return trunc(x); }
	int foo_c(float x)  const          { return trunc(x); }
	int foo_v(float x)        volatile { return trunc(x); }
	int foo_cv(float x) const volatile { return trunc(x); }
	int foo_varargs(float x, ...)      { return trunc(x); }

	int operator()(float x)
	{
		return foo(x) + 1;
	}

	int operator()(float x) const
	{
		return foo_c(x) + 2;
	}

	int bar;

private:
	X(const X&);
	X& operator=(const X&);
};

struct ABC
{
	virtual bool operator()() const = 0;
};

struct Concrete : ABC
{
	virtual bool operator()() const { return true; }
};

struct NonTrivial
{
	~NonTrivial() {}
};

struct Noncopyable
{
	Noncopyable(int x) : m_value(x) {}
	int value() const { return m_value; }
private:
	Noncopyable(const Noncopyable&) = delete;
	Noncopyable& operator=(const Noncopyable&) = delete;
	int m_value;
};

GTEST_TEST(FunctionalTest, ReferenceWrapperTest)
{
	{
		test_type* null_tt = 0;
		const test_type* null_ttc = 0;
		int zero;

		bksge::reference_wrapper<double(int)>* pr1(0);
		bksge::reference_wrapper<float(*)(int)>* pr2(0);
		bksge::reference_wrapper<int (test_type::*)()>* pr3(0);
		bksge::reference_wrapper<short (test_type::*)()const>* pr4(0);
		bksge::reference_wrapper<functor1>* pr5(0);
		bksge::reference_wrapper<long(int, char)>* pr1b(0);
		bksge::reference_wrapper<bool(*)(int, char)>* pr2b(0);
		bksge::reference_wrapper<int (test_type::*)(char)>* pr3b(0);
		bksge::reference_wrapper<int (test_type::*)()const>* pr4b(0);
		bksge::reference_wrapper<functor2>* pr5b(0);

#define BKSGE_REFERENCE_WRAPPER_TEST(F, T)	\
	static_assert(bksge::is_same<decltype(F), T>::value, "")

		BKSGE_REFERENCE_WRAPPER_TEST((*pr1)(0), double);
		BKSGE_REFERENCE_WRAPPER_TEST((*pr2)(0), float);
		BKSGE_REFERENCE_WRAPPER_TEST((*pr3)(null_tt), int);
		BKSGE_REFERENCE_WRAPPER_TEST((*pr4)(null_ttc), short);
		BKSGE_REFERENCE_WRAPPER_TEST((*pr5)(0), double);
		BKSGE_REFERENCE_WRAPPER_TEST((*pr5)(zero), double);

		BKSGE_REFERENCE_WRAPPER_TEST((*pr1b)(0, 0), long);
		BKSGE_REFERENCE_WRAPPER_TEST((*pr2b)(0, 0), bool);
		BKSGE_REFERENCE_WRAPPER_TEST((*pr3b)(null_tt, zero), int);
		BKSGE_REFERENCE_WRAPPER_TEST((*pr4b)(null_ttc), int);
		BKSGE_REFERENCE_WRAPPER_TEST((*pr5b)(0, 0), double);
		BKSGE_REFERENCE_WRAPPER_TEST((*pr5b)(zero, zero), double);

#undef BKSGE_REFERENCE_WRAPPER_TEST

		(void)null_tt;
		(void)null_ttc;
		(void)zero;
		(void)pr1;
		(void)pr2;
		(void)pr3;
		(void)pr4;
		(void)pr5;
		(void)pr1b;
		(void)pr2b;
		(void)pr3b;
		(void)pr4b;
		(void)pr5b;
	}
	{
		OverloadedAddress oa;
		bksge::reference_wrapper<OverloadedAddress> rw(oa);
	}
	{
		X x;
		X* xp = &x;
		int (X::* p_foo)(float) = &X::foo;
		int (X::* p_foo_c)(float) const = &X::foo_c;
		int (X::* p_foo_v)(float) volatile = &X::foo_v;
		int (X::* p_foo_cv)(float) const volatile = &X::foo_cv;
		int X::* p_bar = &X::bar;

		const float pi = 3.14f;

		// Functions
		EXPECT_EQ(3, bksge::ref(trunc)(pi));

		// Function pointers
		EXPECT_EQ(3, bksge::cref(trunc)(pi));

		// Member function pointers
		EXPECT_EQ(3, bksge::ref(p_foo)(x, pi));
		EXPECT_EQ(3, bksge::ref(p_foo)(xp, pi));
		EXPECT_EQ(3, bksge::ref(p_foo_c)(x, pi));
		EXPECT_EQ(3, bksge::ref(p_foo_c)(xp, pi));
		EXPECT_EQ(3, bksge::ref(p_foo_v)(x, pi));
		EXPECT_EQ(3, bksge::ref(p_foo_v)(xp, pi));
		EXPECT_EQ(3, bksge::ref(p_foo_cv)(x, pi));
		EXPECT_EQ(3, bksge::ref(p_foo_cv)(xp, pi));

		// Member data pointers
		EXPECT_EQ(17, bksge::ref(p_bar)(x));
		EXPECT_EQ(17, bksge::ref(p_bar)(xp));
		int& i1 = bksge::ref(p_bar)(x);
		i1 = 18;
		EXPECT_EQ(18, x.bar);
		int& i2 = bksge::ref(p_bar)(xp);
		i2 = 19;
		EXPECT_EQ(19, x.bar);

		// Function objects
		EXPECT_EQ(4, bksge::ref(x)(pi));
		EXPECT_EQ(5, bksge::cref(x)(pi));
	}
	{
		Concrete c;
		ABC& abc = c;

		auto b = bksge::cref(abc)();
		EXPECT_EQ(true, b);
	}
	{
		using R = bksge::reference_wrapper<NonTrivial>;

		static_assert(bksge::is_copy_constructible<R>::value, "copy constructible");
		static_assert(bksge::is_copy_assignable<R>::value, "copy assignable");
		static_assert(bksge::is_trivially_copyable<R>::value, "trivially copyable");
	}
	{
		#define BKSGE_REFERENCE_WRAPPER_TYPE_TEST(T)	\
			static_assert(bksge::is_same<bksge::reference_wrapper<T>::type, T>::value, "")

		BKSGE_REFERENCE_WRAPPER_TYPE_TEST(int);
		BKSGE_REFERENCE_WRAPPER_TYPE_TEST(int(float));
		BKSGE_REFERENCE_WRAPPER_TYPE_TEST(int(float, char));
		BKSGE_REFERENCE_WRAPPER_TYPE_TEST(int(*)(float));
		BKSGE_REFERENCE_WRAPPER_TYPE_TEST(int(* const)(float));
		BKSGE_REFERENCE_WRAPPER_TYPE_TEST(int(* volatile)(float));
		BKSGE_REFERENCE_WRAPPER_TYPE_TEST(int(* const volatile)(float));
		BKSGE_REFERENCE_WRAPPER_TYPE_TEST(test_type);
		BKSGE_REFERENCE_WRAPPER_TYPE_TEST(OverloadedAddress);
		BKSGE_REFERENCE_WRAPPER_TYPE_TEST(NonTrivial);

		#undef BKSGE_REFERENCE_WRAPPER_TYPE_TEST
	}
	{
		Noncopyable x(17);
		auto rx  = bksge::ref(x);
		auto crx = bksge::cref(x);

		auto rx2 = rx;
		auto crx2 = crx;
		
		EXPECT_EQ(17, rx.get().value());
		EXPECT_EQ(17, crx.get().value());
		EXPECT_EQ(17, rx2.get().value());
		EXPECT_EQ(17, crx2.get().value());
	}
}

}	// namespace reference_wrapper_test

}	// namespace bksge_functional_test
