/**
 *	@file	unit_test_fnd_type_traits_is_standard_layout.cpp
 *
 *	@brief	is_standard_layout のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_standard_layout.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstddef/nullptr_t.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_STANDARD_LAYOUT_TEST(b, T)	\
	static_assert(bksge::is_standard_layout<T>::value == b, #T);	\
	static_assert(bksge::is_standard_layout<T>()      == b, #T)

BKSGE_IS_STANDARD_LAYOUT_TEST(true,                 int);
BKSGE_IS_STANDARD_LAYOUT_TEST(true,  const          int);
BKSGE_IS_STANDARD_LAYOUT_TEST(true,        volatile int);
BKSGE_IS_STANDARD_LAYOUT_TEST(true,  const volatile int);
BKSGE_IS_STANDARD_LAYOUT_TEST(true,  int*);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, int&);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, int&&);
BKSGE_IS_STANDARD_LAYOUT_TEST(true,  int[2]);
BKSGE_IS_STANDARD_LAYOUT_TEST(true,  int[]);
BKSGE_IS_STANDARD_LAYOUT_TEST(true,  int(*)[2]);
BKSGE_IS_STANDARD_LAYOUT_TEST(true,  int(*)[]);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, int(&)[2]);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, int(&)[]);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, int(&&)[2]);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, int(&&)[]);

BKSGE_IS_STANDARD_LAYOUT_TEST(true,                 UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true,  const          UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true,        volatile UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true,  const volatile UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true,  UDT*);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, UDT&);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, UDT&&);
BKSGE_IS_STANDARD_LAYOUT_TEST(true,  UDT[2]);
BKSGE_IS_STANDARD_LAYOUT_TEST(true,  UDT[]);
BKSGE_IS_STANDARD_LAYOUT_TEST(true,  UDT(*)[2]);
BKSGE_IS_STANDARD_LAYOUT_TEST(true,  UDT(*)[]);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, UDT(&)[2]);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, UDT(&)[]);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, UDT(&&)[2]);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, UDT(&&)[]);

BKSGE_IS_STANDARD_LAYOUT_TEST(false,                polymorphic_base);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, const          polymorphic_base);
BKSGE_IS_STANDARD_LAYOUT_TEST(false,       volatile polymorphic_base);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, const volatile polymorphic_base);
BKSGE_IS_STANDARD_LAYOUT_TEST(true,  polymorphic_base*);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, polymorphic_base&);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, polymorphic_base&&);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, polymorphic_base[2]);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, polymorphic_base[]);
BKSGE_IS_STANDARD_LAYOUT_TEST(true,  polymorphic_base(*)[2]);
BKSGE_IS_STANDARD_LAYOUT_TEST(true,  polymorphic_base(*)[]);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, polymorphic_base(&)[2]);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, polymorphic_base(&)[]);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, polymorphic_base(&&)[2]);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, polymorphic_base(&&)[]);

BKSGE_IS_STANDARD_LAYOUT_TEST(false,                void);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, const          void);
BKSGE_IS_STANDARD_LAYOUT_TEST(false,       volatile void);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, const volatile void);

BKSGE_IS_STANDARD_LAYOUT_TEST(true, bool);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, char);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, wchar_t);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, signed char);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, short);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, long);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, long long);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, unsigned char);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, unsigned int);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, unsigned short);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, unsigned long);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, unsigned long long);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, bksge::size_t);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, float);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, double);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, long double);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, void*);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, bksge::nullptr_t);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, decltype(nullptr));
BKSGE_IS_STANDARD_LAYOUT_TEST(true, enum_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, enum_uint32_t_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, enum_uint16_t_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, enum_uint8_t_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, enum_int32_t_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, enum_int16_t_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, enum_int8_t_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, enum_class_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, enum_class_uint32_t_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, enum_class_uint16_t_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, enum_class_uint8_t_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, enum_class_int32_t_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, enum_class_int16_t_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, enum_class_int8_t_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, POD_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, empty_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, empty_POD_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, union_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, POD_union_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, empty_union_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, empty_POD_union_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, nothrow_default_ctor_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, nothrow_dtor_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, nothrow_copy_ctor_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, nothrow_copy_assign_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, nothrow_move_ctor_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, nothrow_move_assign_UDT);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, Base);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, Derived);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, Derived2);
//	BKSGE_IS_STANDARD_LAYOUT_TEST(true, MultiBase);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, PrivateBase);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, NonDerived);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, enum1);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, enum2);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, VB);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, VD);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, non_pointer);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, non_int_pointer);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, int_constructible);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, int_convertible);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, test_abc1);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, test_abc2);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, test_abc3);
//	BKSGE_IS_STANDARD_LAYOUT_TEST(true, incomplete_type);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, polymorphic_base);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, polymorphic_derived1);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, polymorphic_derived2);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, virtual_inherit1);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, virtual_inherit2);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, virtual_inherit3);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, virtual_inherit5);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, virtual_inherit6);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, trivial_except_construct);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, trivial_except_destroy);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, trivial_except_copy_ctor);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, trivial_except_move_ctor);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, trivial_except_copy_assign);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, trivial_except_move_assign);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, f1);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, f2);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, f3);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, mf1);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, mf2);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, mf3);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, mf4);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, mp);
BKSGE_IS_STANDARD_LAYOUT_TEST(true, cmf);
#if !(defined(_MSC_VER) && (_MSC_VER >= 1911))
BKSGE_IS_STANDARD_LAYOUT_TEST(false, foo0_t);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, foo1_t);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, foo2_t);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, foo3_t);
BKSGE_IS_STANDARD_LAYOUT_TEST(false, foo4_t);
#endif

#undef BKSGE_IS_STANDARD_LAYOUT_TEST
