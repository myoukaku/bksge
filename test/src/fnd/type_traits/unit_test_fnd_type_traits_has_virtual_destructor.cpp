/**
 *	@file	unit_test_fnd_type_traits_has_virtual_destructor.cpp
 *
 *	@brief	has_virtual_destructor のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/has_virtual_destructor.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstddef/nullptr_t.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(b, T)	\
	static_assert(bksge::has_virtual_destructor<T>::value == b, #T)

GTEST_TEST(TypeTraitsTest, HasVirtualDestructorTest)
{
	IntegralConstantTest<bksge::has_virtual_destructor<int>, false>();
	IntegralConstantTest<bksge::has_virtual_destructor<VB>, true>();

	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false,                int);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, const          int);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false,       volatile int);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, const volatile int);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int*);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int&);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int&&);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int[2]);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int[]);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int(*)[2]);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int(*)[]);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int(&)[2]);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int(&)[]);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int(&&)[2]);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int(&&)[]);

	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(true,                 VB);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  const          VB);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(true,        volatile VB);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  const volatile VB);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB*);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB&);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB&&);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB[2]);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB[]);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB(*)[2]);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB(*)[]);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB(&)[2]);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB(&)[]);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB(&&)[2]);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB(&&)[]);

	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false,                void);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, const          void);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false,       volatile void);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, const volatile int);

	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, bool);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, char);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, wchar_t);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, signed char);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, short);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, long);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, long long);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, unsigned char);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, unsigned int);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, unsigned short);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, unsigned long);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, unsigned long long);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, bksge::size_t);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, float);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, double);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, long double);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, void*);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, bksge::nullptr_t);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, decltype(nullptr));
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_uint32_t_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_uint16_t_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_uint8_t_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_int32_t_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_int16_t_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_int8_t_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_class_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_class_uint32_t_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_class_uint16_t_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_class_uint8_t_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_class_int32_t_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_class_int16_t_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_class_int8_t_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, POD_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, empty_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, empty_POD_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, union_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, POD_union_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, empty_union_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, empty_POD_union_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, nothrow_default_ctor_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, nothrow_dtor_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, nothrow_copy_ctor_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, nothrow_copy_assign_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, nothrow_move_ctor_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, nothrow_move_assign_UDT);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, Base);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, Derived);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, Derived2);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, MultiBase);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, PrivateBase);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, NonDerived);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum1);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum2);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  VB);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  VD);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, non_pointer);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, non_int_pointer);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int_constructible);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int_convertible);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  test_abc1);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, test_abc2);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  test_abc3);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, test_concrete1);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  test_concrete2);
//	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, incomplete_type);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  polymorphic_base);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  polymorphic_derived1);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  polymorphic_derived2);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, virtual_inherit1);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, virtual_inherit2);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, virtual_inherit3);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, virtual_inherit5);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  virtual_inherit6);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, trivial_except_construct);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, trivial_except_destroy);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, trivial_except_copy_ctor);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, trivial_except_move_ctor);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, trivial_except_copy_assign);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, trivial_except_move_assign);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, f1);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, f2);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, f3);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, mf1);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, mf2);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, mf3);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, mf4);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, mp);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, cmf);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, foo0_t);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, foo1_t);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, foo2_t);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, foo3_t);
	BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST(false, foo4_t);
}

#undef BKSGE_HAS_VIRTUAL_DESTRUCTOR_TEST
