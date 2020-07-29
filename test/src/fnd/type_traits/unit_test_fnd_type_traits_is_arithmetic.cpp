/**
 *	@file	unit_test_fnd_type_traits_is_arithmetic.cpp
 *
 *	@brief	is_arithmetic のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <cstddef>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_ARITHMETIC_TEST(b, T)	\
	static_assert(bksge::is_arithmetic<T>::value == b, #T);	\
	static_assert(bksge::is_arithmetic<T>()      == b, #T)

BKSGE_IS_ARITHMETIC_TEST(true,                int);
BKSGE_IS_ARITHMETIC_TEST(true, const          int);
BKSGE_IS_ARITHMETIC_TEST(true,       volatile int);
BKSGE_IS_ARITHMETIC_TEST(true, const volatile int);
BKSGE_IS_ARITHMETIC_TEST(false, int*);
BKSGE_IS_ARITHMETIC_TEST(false, int&);
BKSGE_IS_ARITHMETIC_TEST(false, int&&);
BKSGE_IS_ARITHMETIC_TEST(false, int[2]);
BKSGE_IS_ARITHMETIC_TEST(false, int[]);
BKSGE_IS_ARITHMETIC_TEST(false, int(*)[2]);
BKSGE_IS_ARITHMETIC_TEST(false, int(*)[]);
BKSGE_IS_ARITHMETIC_TEST(false, int(&)[2]);
BKSGE_IS_ARITHMETIC_TEST(false, int(&)[]);
BKSGE_IS_ARITHMETIC_TEST(false, int(&&)[2]);
BKSGE_IS_ARITHMETIC_TEST(false, int(&&)[]);
	
BKSGE_IS_ARITHMETIC_TEST(false,                void);
BKSGE_IS_ARITHMETIC_TEST(false, const          void);
BKSGE_IS_ARITHMETIC_TEST(false,       volatile void);
BKSGE_IS_ARITHMETIC_TEST(false, const volatile void);

BKSGE_IS_ARITHMETIC_TEST(true, bool);
BKSGE_IS_ARITHMETIC_TEST(true, char);
BKSGE_IS_ARITHMETIC_TEST(true, wchar_t);
BKSGE_IS_ARITHMETIC_TEST(true, signed char);
BKSGE_IS_ARITHMETIC_TEST(true, short);
BKSGE_IS_ARITHMETIC_TEST(true, long);
BKSGE_IS_ARITHMETIC_TEST(true, long long);
BKSGE_IS_ARITHMETIC_TEST(true, unsigned char);
BKSGE_IS_ARITHMETIC_TEST(true, unsigned int);
BKSGE_IS_ARITHMETIC_TEST(true, unsigned short);
BKSGE_IS_ARITHMETIC_TEST(true, unsigned long);
BKSGE_IS_ARITHMETIC_TEST(true, unsigned long long);
BKSGE_IS_ARITHMETIC_TEST(true, std::size_t);
BKSGE_IS_ARITHMETIC_TEST(true, float);
BKSGE_IS_ARITHMETIC_TEST(true, double);
BKSGE_IS_ARITHMETIC_TEST(true, long double);
BKSGE_IS_ARITHMETIC_TEST(false, void*);
BKSGE_IS_ARITHMETIC_TEST(false, std::nullptr_t);
BKSGE_IS_ARITHMETIC_TEST(false, decltype(nullptr));
BKSGE_IS_ARITHMETIC_TEST(false, enum_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, enum_uint32_t_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, enum_uint16_t_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, enum_uint8_t_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, enum_int32_t_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, enum_int16_t_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, enum_int8_t_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, enum_class_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, enum_class_uint32_t_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, enum_class_uint16_t_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, enum_class_uint8_t_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, enum_class_int32_t_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, enum_class_int16_t_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, enum_class_int8_t_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, UDT);
BKSGE_IS_ARITHMETIC_TEST(false, POD_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, empty_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, empty_POD_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, union_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, POD_union_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, empty_union_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, empty_POD_union_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, nothrow_default_ctor_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, nothrow_dtor_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, nothrow_copy_ctor_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, nothrow_copy_assign_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, nothrow_move_ctor_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, nothrow_move_assign_UDT);
BKSGE_IS_ARITHMETIC_TEST(false, Base);
BKSGE_IS_ARITHMETIC_TEST(false, Derived);
BKSGE_IS_ARITHMETIC_TEST(false, Derived2);
BKSGE_IS_ARITHMETIC_TEST(false, MultiBase);
BKSGE_IS_ARITHMETIC_TEST(false, PrivateBase);
BKSGE_IS_ARITHMETIC_TEST(false, NonDerived);
BKSGE_IS_ARITHMETIC_TEST(false, enum1);
BKSGE_IS_ARITHMETIC_TEST(false, enum2);
BKSGE_IS_ARITHMETIC_TEST(false, VB);
BKSGE_IS_ARITHMETIC_TEST(false, VD);
BKSGE_IS_ARITHMETIC_TEST(false, non_pointer);
BKSGE_IS_ARITHMETIC_TEST(false, non_int_pointer);
BKSGE_IS_ARITHMETIC_TEST(false, int_constructible);
BKSGE_IS_ARITHMETIC_TEST(false, int_convertible);
BKSGE_IS_ARITHMETIC_TEST(false, test_abc1);
BKSGE_IS_ARITHMETIC_TEST(false, test_abc2);
BKSGE_IS_ARITHMETIC_TEST(false, test_abc3);
BKSGE_IS_ARITHMETIC_TEST(false, incomplete_type);
BKSGE_IS_ARITHMETIC_TEST(false, polymorphic_base);
BKSGE_IS_ARITHMETIC_TEST(false, polymorphic_derived1);
BKSGE_IS_ARITHMETIC_TEST(false, polymorphic_derived2);
BKSGE_IS_ARITHMETIC_TEST(false, virtual_inherit1);
BKSGE_IS_ARITHMETIC_TEST(false, virtual_inherit2);
BKSGE_IS_ARITHMETIC_TEST(false, virtual_inherit3);
BKSGE_IS_ARITHMETIC_TEST(false, virtual_inherit5);
BKSGE_IS_ARITHMETIC_TEST(false, virtual_inherit6);
BKSGE_IS_ARITHMETIC_TEST(false, trivial_except_construct);
BKSGE_IS_ARITHMETIC_TEST(false, trivial_except_destroy);
BKSGE_IS_ARITHMETIC_TEST(false, trivial_except_copy_ctor);
BKSGE_IS_ARITHMETIC_TEST(false, trivial_except_move_ctor);
BKSGE_IS_ARITHMETIC_TEST(false, trivial_except_copy_assign);
BKSGE_IS_ARITHMETIC_TEST(false, trivial_except_move_assign);
BKSGE_IS_ARITHMETIC_TEST(false, f1);
BKSGE_IS_ARITHMETIC_TEST(false, f2);
BKSGE_IS_ARITHMETIC_TEST(false, f3);
BKSGE_IS_ARITHMETIC_TEST(false, mf1);
BKSGE_IS_ARITHMETIC_TEST(false, mf2);
BKSGE_IS_ARITHMETIC_TEST(false, mf3);
BKSGE_IS_ARITHMETIC_TEST(false, mf4);
BKSGE_IS_ARITHMETIC_TEST(false, mp);
BKSGE_IS_ARITHMETIC_TEST(false, cmf);
BKSGE_IS_ARITHMETIC_TEST(false, foo0_t);
BKSGE_IS_ARITHMETIC_TEST(false, foo1_t);
BKSGE_IS_ARITHMETIC_TEST(false, foo2_t);
BKSGE_IS_ARITHMETIC_TEST(false, foo3_t);
BKSGE_IS_ARITHMETIC_TEST(false, foo4_t);

#undef BKSGE_IS_ARITHMETIC_TEST
