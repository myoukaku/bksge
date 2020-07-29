/**
 *	@file	unit_test_fnd_type_traits_is_floating_point.cpp
 *
 *	@brief	is_floating_point のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_floating_point.hpp>
#include <cstddef>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_FLOATING_POINT_TEST(b, T)	\
	static_assert(bksge::is_floating_point<T>::value == b, #T);	\
	static_assert(bksge::is_floating_point<T>()      == b, #T)

BKSGE_IS_FLOATING_POINT_TEST(true,                 float);
BKSGE_IS_FLOATING_POINT_TEST(true,  const          float);
BKSGE_IS_FLOATING_POINT_TEST(true,        volatile float);
BKSGE_IS_FLOATING_POINT_TEST(true,  const volatile float);
BKSGE_IS_FLOATING_POINT_TEST(false, float*);
BKSGE_IS_FLOATING_POINT_TEST(false, float&);
BKSGE_IS_FLOATING_POINT_TEST(false, float&&);
BKSGE_IS_FLOATING_POINT_TEST(false, float[2]);
BKSGE_IS_FLOATING_POINT_TEST(false, float[]);
BKSGE_IS_FLOATING_POINT_TEST(false, float(*)[2]);
BKSGE_IS_FLOATING_POINT_TEST(false, float(*)[]);
BKSGE_IS_FLOATING_POINT_TEST(false, float(&)[2]);
BKSGE_IS_FLOATING_POINT_TEST(false, float(&)[]);
BKSGE_IS_FLOATING_POINT_TEST(false, float(&&)[2]);
BKSGE_IS_FLOATING_POINT_TEST(false, float(&&)[]);

BKSGE_IS_FLOATING_POINT_TEST(true, double);
BKSGE_IS_FLOATING_POINT_TEST(true, long double);

BKSGE_IS_FLOATING_POINT_TEST(false,                void);
BKSGE_IS_FLOATING_POINT_TEST(false, const          void);
BKSGE_IS_FLOATING_POINT_TEST(false,       volatile void);
BKSGE_IS_FLOATING_POINT_TEST(false, const volatile void);

BKSGE_IS_FLOATING_POINT_TEST(false, bool);
BKSGE_IS_FLOATING_POINT_TEST(false, char);
BKSGE_IS_FLOATING_POINT_TEST(false, wchar_t);
BKSGE_IS_FLOATING_POINT_TEST(false, signed char);
BKSGE_IS_FLOATING_POINT_TEST(false, int);
BKSGE_IS_FLOATING_POINT_TEST(false, short);
BKSGE_IS_FLOATING_POINT_TEST(false, long);
BKSGE_IS_FLOATING_POINT_TEST(false, long long);
BKSGE_IS_FLOATING_POINT_TEST(false, unsigned char);
BKSGE_IS_FLOATING_POINT_TEST(false, unsigned int);
BKSGE_IS_FLOATING_POINT_TEST(false, unsigned short);
BKSGE_IS_FLOATING_POINT_TEST(false, unsigned long);
BKSGE_IS_FLOATING_POINT_TEST(false, unsigned long long);
BKSGE_IS_FLOATING_POINT_TEST(false, std::size_t);
BKSGE_IS_FLOATING_POINT_TEST(false, void*);
BKSGE_IS_FLOATING_POINT_TEST(false, std::nullptr_t);
BKSGE_IS_FLOATING_POINT_TEST(false, decltype(nullptr));
BKSGE_IS_FLOATING_POINT_TEST(false, enum_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, enum_uint32_t_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, enum_uint16_t_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, enum_uint8_t_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, enum_int32_t_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, enum_int16_t_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, enum_int8_t_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, enum_class_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, enum_class_uint32_t_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, enum_class_uint16_t_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, enum_class_uint8_t_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, enum_class_int32_t_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, enum_class_int16_t_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, enum_class_int8_t_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, POD_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, empty_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, empty_POD_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, union_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, POD_union_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, empty_union_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, empty_POD_union_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, nothrow_default_ctor_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, nothrow_dtor_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, nothrow_copy_ctor_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, nothrow_copy_assign_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, nothrow_move_ctor_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, nothrow_move_assign_UDT);
BKSGE_IS_FLOATING_POINT_TEST(false, Base);
BKSGE_IS_FLOATING_POINT_TEST(false, Derived);
BKSGE_IS_FLOATING_POINT_TEST(false, Derived2);
BKSGE_IS_FLOATING_POINT_TEST(false, MultiBase);
BKSGE_IS_FLOATING_POINT_TEST(false, PrivateBase);
BKSGE_IS_FLOATING_POINT_TEST(false, NonDerived);
BKSGE_IS_FLOATING_POINT_TEST(false, enum1);
BKSGE_IS_FLOATING_POINT_TEST(false, enum2);
BKSGE_IS_FLOATING_POINT_TEST(false, VB);
BKSGE_IS_FLOATING_POINT_TEST(false, VD);
BKSGE_IS_FLOATING_POINT_TEST(false, non_pointer);
BKSGE_IS_FLOATING_POINT_TEST(false, non_int_pointer);
BKSGE_IS_FLOATING_POINT_TEST(false, int_constructible);
BKSGE_IS_FLOATING_POINT_TEST(false, int_convertible);
BKSGE_IS_FLOATING_POINT_TEST(false, test_abc1);
BKSGE_IS_FLOATING_POINT_TEST(false, test_abc2);
BKSGE_IS_FLOATING_POINT_TEST(false, test_abc3);
BKSGE_IS_FLOATING_POINT_TEST(false, incomplete_type);
BKSGE_IS_FLOATING_POINT_TEST(false, polymorphic_base);
BKSGE_IS_FLOATING_POINT_TEST(false, polymorphic_derived1);
BKSGE_IS_FLOATING_POINT_TEST(false, polymorphic_derived2);
BKSGE_IS_FLOATING_POINT_TEST(false, virtual_inherit1);
BKSGE_IS_FLOATING_POINT_TEST(false, virtual_inherit2);
BKSGE_IS_FLOATING_POINT_TEST(false, virtual_inherit3);
BKSGE_IS_FLOATING_POINT_TEST(false, virtual_inherit5);
BKSGE_IS_FLOATING_POINT_TEST(false, virtual_inherit6);
BKSGE_IS_FLOATING_POINT_TEST(false, trivial_except_construct);
BKSGE_IS_FLOATING_POINT_TEST(false, trivial_except_destroy);
BKSGE_IS_FLOATING_POINT_TEST(false, trivial_except_copy_ctor);
BKSGE_IS_FLOATING_POINT_TEST(false, trivial_except_move_ctor);
BKSGE_IS_FLOATING_POINT_TEST(false, trivial_except_copy_assign);
BKSGE_IS_FLOATING_POINT_TEST(false, trivial_except_move_assign);
BKSGE_IS_FLOATING_POINT_TEST(false, f1);
BKSGE_IS_FLOATING_POINT_TEST(false, f2);
BKSGE_IS_FLOATING_POINT_TEST(false, f3);
BKSGE_IS_FLOATING_POINT_TEST(false, mf1);
BKSGE_IS_FLOATING_POINT_TEST(false, mf2);
BKSGE_IS_FLOATING_POINT_TEST(false, mf3);
BKSGE_IS_FLOATING_POINT_TEST(false, mf4);
BKSGE_IS_FLOATING_POINT_TEST(false, mp);
BKSGE_IS_FLOATING_POINT_TEST(false, cmf);
BKSGE_IS_FLOATING_POINT_TEST(false, foo0_t);
BKSGE_IS_FLOATING_POINT_TEST(false, foo1_t);
BKSGE_IS_FLOATING_POINT_TEST(false, foo2_t);
BKSGE_IS_FLOATING_POINT_TEST(false, foo3_t);
BKSGE_IS_FLOATING_POINT_TEST(false, foo4_t);

#undef BKSGE_IS_FLOATING_POINT_TEST
