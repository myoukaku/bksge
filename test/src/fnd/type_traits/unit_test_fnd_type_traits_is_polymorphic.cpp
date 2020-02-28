/**
 *	@file	unit_test_fnd_type_traits_is_polymorphic.cpp
 *
 *	@brief	is_polymorphic のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_polymorphic.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_POLYMORPHIC_TEST_IMPL(b, T)	\
	static_assert(bksge::is_polymorphic<T>::value == b, #T)

#define BKSGE_IS_POLYMORPHIC_TEST(b, T)	\
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(b,                T);	\
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(b, const          T);	\
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(b,       volatile T);	\
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(b, const volatile T);	\
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, T*);				\
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, T&);				\
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, T&&);				\
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, T[2]);			\
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, T[]);				\
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, T(*)[2]);			\
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, T(*)[]);			\
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, T(&)[2]);			\
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, T(&)[]);			\
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, T(&&)[2]);		\
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, T(&&)[])

GTEST_TEST(TypeTraitsTest, IsPolymorphicTest)
{
	IntegralConstantTest<bksge::is_polymorphic<UDT>, false>();
	IntegralConstantTest<bksge::is_polymorphic<polymorphic_base>, true>();
	IntegralConstantTest<bksge::is_polymorphic<polymorphic_derived1>, true>();

	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false,                void);
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, const          void);
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false,       volatile void);
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, const volatile void);

	BKSGE_IS_POLYMORPHIC_TEST(false, int);
	BKSGE_IS_POLYMORPHIC_TEST(false, float);
	BKSGE_IS_POLYMORPHIC_TEST(false, enum_UDT);
	BKSGE_IS_POLYMORPHIC_TEST(false, enum_class_UDT);
	BKSGE_IS_POLYMORPHIC_TEST(false, UDT);
	BKSGE_IS_POLYMORPHIC_TEST(false, POD_UDT);
	BKSGE_IS_POLYMORPHIC_TEST(false, Base);
	BKSGE_IS_POLYMORPHIC_TEST(false, Derived);
	BKSGE_IS_POLYMORPHIC_TEST(false, Derived2);
	BKSGE_IS_POLYMORPHIC_TEST(false, MultiBase);
	BKSGE_IS_POLYMORPHIC_TEST(false, PrivateBase);
	BKSGE_IS_POLYMORPHIC_TEST(false, NonDerived);
	BKSGE_IS_POLYMORPHIC_TEST(true, VB);
	BKSGE_IS_POLYMORPHIC_TEST(true, VD);
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(true, test_abc1);
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(true, test_abc2);
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(true, test_abc3);
	//BKSGE_IS_POLYMORPHIC_TEST(false, incomplete_type);
	BKSGE_IS_POLYMORPHIC_TEST(true, polymorphic_base);
	BKSGE_IS_POLYMORPHIC_TEST(true, polymorphic_derived1);
	BKSGE_IS_POLYMORPHIC_TEST(true, polymorphic_derived2);
	BKSGE_IS_POLYMORPHIC_TEST(false, virtual_inherit1);
	BKSGE_IS_POLYMORPHIC_TEST(false, virtual_inherit2);
	BKSGE_IS_POLYMORPHIC_TEST(false, virtual_inherit3);
	BKSGE_IS_POLYMORPHIC_TEST(false, virtual_inherit5);
	BKSGE_IS_POLYMORPHIC_TEST(true, virtual_inherit6);
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, f1);
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, f2);
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, f3);
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, mf1);
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, mf2);
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, mf3);
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, mf4);
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, mp);
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, cmf);
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, foo0_t);
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, foo1_t);
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, foo2_t);
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, foo3_t);
	BKSGE_IS_POLYMORPHIC_TEST_IMPL(false, foo4_t);
}

#undef BKSGE_IS_POLYMORPHIC_TEST
#undef BKSGE_IS_POLYMORPHIC_TEST_IMPL
