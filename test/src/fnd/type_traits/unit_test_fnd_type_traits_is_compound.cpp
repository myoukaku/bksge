/**
 *	@file	unit_test_fnd_type_traits_is_compound.cpp
 *
 *	@brief	is_compound のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_compound.hpp>
#include <cstddef>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_COMPOUND_TEST(b, T)	\
	static_assert(bksge::is_compound<T>::value == b, #T)

GTEST_TEST(TypeTraitsTest, IsCompoundTest)
{
	IntegralConstantTest<bksge::is_compound<int>, false>();
	IntegralConstantTest<bksge::is_compound<enum_UDT>, true>();
	IntegralConstantTest<bksge::is_compound<UDT>, true>();

	BKSGE_IS_COMPOUND_TEST(false,                int);
	BKSGE_IS_COMPOUND_TEST(false, const          int);
	BKSGE_IS_COMPOUND_TEST(false,       volatile int);
	BKSGE_IS_COMPOUND_TEST(false, const volatile int);
	BKSGE_IS_COMPOUND_TEST(true,  int*);
	BKSGE_IS_COMPOUND_TEST(true,  int&);
	BKSGE_IS_COMPOUND_TEST(true,  int&&);
	BKSGE_IS_COMPOUND_TEST(true,  int[2]);
	BKSGE_IS_COMPOUND_TEST(true,  int[]);
	BKSGE_IS_COMPOUND_TEST(true,  int(&)[2]);
	BKSGE_IS_COMPOUND_TEST(true,  int(&)[]);
	BKSGE_IS_COMPOUND_TEST(true,  int(&&)[2]);
	BKSGE_IS_COMPOUND_TEST(true,  int(&&)[]);

	BKSGE_IS_COMPOUND_TEST(false,                void);
	BKSGE_IS_COMPOUND_TEST(false, const          void);
	BKSGE_IS_COMPOUND_TEST(false,       volatile void);
	BKSGE_IS_COMPOUND_TEST(false, const volatile void);

	BKSGE_IS_COMPOUND_TEST(false, bool);
	BKSGE_IS_COMPOUND_TEST(false, char);
	BKSGE_IS_COMPOUND_TEST(false, wchar_t);
	BKSGE_IS_COMPOUND_TEST(false, signed char);
	BKSGE_IS_COMPOUND_TEST(false, short);
	BKSGE_IS_COMPOUND_TEST(false, long);
	BKSGE_IS_COMPOUND_TEST(false, long long);
	BKSGE_IS_COMPOUND_TEST(false, unsigned char);
	BKSGE_IS_COMPOUND_TEST(false, unsigned int);
	BKSGE_IS_COMPOUND_TEST(false, unsigned short);
	BKSGE_IS_COMPOUND_TEST(false, unsigned long);
	BKSGE_IS_COMPOUND_TEST(false, unsigned long long);
	BKSGE_IS_COMPOUND_TEST(false, std::size_t);
	BKSGE_IS_COMPOUND_TEST(false, float);
	BKSGE_IS_COMPOUND_TEST(false, double);
	BKSGE_IS_COMPOUND_TEST(false, long double);
	BKSGE_IS_COMPOUND_TEST(false, std::nullptr_t);
	BKSGE_IS_COMPOUND_TEST(false, decltype(nullptr));

	BKSGE_IS_COMPOUND_TEST(true,                 UDT);
	BKSGE_IS_COMPOUND_TEST(true,  const          UDT);
	BKSGE_IS_COMPOUND_TEST(true,        volatile UDT);
	BKSGE_IS_COMPOUND_TEST(true,  const volatile UDT);
	BKSGE_IS_COMPOUND_TEST(true,  UDT*);
	BKSGE_IS_COMPOUND_TEST(true,  UDT&);
	BKSGE_IS_COMPOUND_TEST(true,  UDT&&);
	BKSGE_IS_COMPOUND_TEST(true,  UDT[2]);
	BKSGE_IS_COMPOUND_TEST(true,  UDT[]);
	BKSGE_IS_COMPOUND_TEST(true,  UDT(&)[2]);
	BKSGE_IS_COMPOUND_TEST(true,  UDT(&)[]);
	BKSGE_IS_COMPOUND_TEST(true,  UDT(&&)[2]);
	BKSGE_IS_COMPOUND_TEST(true,  UDT(&&)[]);

	BKSGE_IS_COMPOUND_TEST(true, void*);
	BKSGE_IS_COMPOUND_TEST(true, enum_UDT);
	BKSGE_IS_COMPOUND_TEST(true, enum_uint32_t_UDT);
	BKSGE_IS_COMPOUND_TEST(true, enum_uint16_t_UDT);
	BKSGE_IS_COMPOUND_TEST(true, enum_uint8_t_UDT);
	BKSGE_IS_COMPOUND_TEST(true, enum_int32_t_UDT);
	BKSGE_IS_COMPOUND_TEST(true, enum_int16_t_UDT);
	BKSGE_IS_COMPOUND_TEST(true, enum_int8_t_UDT);
	BKSGE_IS_COMPOUND_TEST(true, enum_class_UDT);
	BKSGE_IS_COMPOUND_TEST(true, enum_class_uint32_t_UDT);
	BKSGE_IS_COMPOUND_TEST(true, enum_class_uint16_t_UDT);
	BKSGE_IS_COMPOUND_TEST(true, enum_class_uint8_t_UDT);
	BKSGE_IS_COMPOUND_TEST(true, enum_class_int32_t_UDT);
	BKSGE_IS_COMPOUND_TEST(true, enum_class_int16_t_UDT);
	BKSGE_IS_COMPOUND_TEST(true, enum_class_int8_t_UDT);
	BKSGE_IS_COMPOUND_TEST(true, UDT);
	BKSGE_IS_COMPOUND_TEST(true, POD_UDT);
	BKSGE_IS_COMPOUND_TEST(true, empty_UDT);
	BKSGE_IS_COMPOUND_TEST(true, empty_POD_UDT);
	BKSGE_IS_COMPOUND_TEST(true, union_UDT);
	BKSGE_IS_COMPOUND_TEST(true, POD_union_UDT);
	BKSGE_IS_COMPOUND_TEST(true, empty_union_UDT);
	BKSGE_IS_COMPOUND_TEST(true, empty_POD_union_UDT);
	BKSGE_IS_COMPOUND_TEST(true, nothrow_default_ctor_UDT);
	BKSGE_IS_COMPOUND_TEST(true, nothrow_dtor_UDT);
	BKSGE_IS_COMPOUND_TEST(true, nothrow_copy_ctor_UDT);
	BKSGE_IS_COMPOUND_TEST(true, nothrow_copy_assign_UDT);
	BKSGE_IS_COMPOUND_TEST(true, nothrow_move_ctor_UDT);
	BKSGE_IS_COMPOUND_TEST(true, nothrow_move_assign_UDT);
	BKSGE_IS_COMPOUND_TEST(true, Base);
	BKSGE_IS_COMPOUND_TEST(true, Derived);
	BKSGE_IS_COMPOUND_TEST(true, Derived2);
	BKSGE_IS_COMPOUND_TEST(true, MultiBase);
	BKSGE_IS_COMPOUND_TEST(true, PrivateBase);
	BKSGE_IS_COMPOUND_TEST(true, NonDerived);
	BKSGE_IS_COMPOUND_TEST(true, enum1);
	BKSGE_IS_COMPOUND_TEST(true, enum2);
	BKSGE_IS_COMPOUND_TEST(true, VB);
	BKSGE_IS_COMPOUND_TEST(true, VD);
	BKSGE_IS_COMPOUND_TEST(true, non_pointer);
	BKSGE_IS_COMPOUND_TEST(true, non_int_pointer);
	BKSGE_IS_COMPOUND_TEST(true, int_constructible);
	BKSGE_IS_COMPOUND_TEST(true, int_convertible);
	BKSGE_IS_COMPOUND_TEST(true, test_abc1);
	BKSGE_IS_COMPOUND_TEST(true, test_abc2);
	BKSGE_IS_COMPOUND_TEST(true, test_abc3);
	BKSGE_IS_COMPOUND_TEST(true, incomplete_type);
	BKSGE_IS_COMPOUND_TEST(true, polymorphic_base);
	BKSGE_IS_COMPOUND_TEST(true, polymorphic_derived1);
	BKSGE_IS_COMPOUND_TEST(true, polymorphic_derived2);
	BKSGE_IS_COMPOUND_TEST(true, virtual_inherit1);
	BKSGE_IS_COMPOUND_TEST(true, virtual_inherit2);
	BKSGE_IS_COMPOUND_TEST(true, virtual_inherit3);
	BKSGE_IS_COMPOUND_TEST(true, virtual_inherit5);
	BKSGE_IS_COMPOUND_TEST(true, virtual_inherit6);
	BKSGE_IS_COMPOUND_TEST(true, trivial_except_construct);
	BKSGE_IS_COMPOUND_TEST(true, trivial_except_destroy);
	BKSGE_IS_COMPOUND_TEST(true, trivial_except_copy_ctor);
	BKSGE_IS_COMPOUND_TEST(true, trivial_except_move_ctor);
	BKSGE_IS_COMPOUND_TEST(true, trivial_except_copy_assign);
	BKSGE_IS_COMPOUND_TEST(true, trivial_except_move_assign);
	BKSGE_IS_COMPOUND_TEST(true, f1);
	BKSGE_IS_COMPOUND_TEST(true, f2);
	BKSGE_IS_COMPOUND_TEST(true, f3);
	BKSGE_IS_COMPOUND_TEST(true, mf1);
	BKSGE_IS_COMPOUND_TEST(true, mf2);
	BKSGE_IS_COMPOUND_TEST(true, mf3);
	BKSGE_IS_COMPOUND_TEST(true, mf4);
	BKSGE_IS_COMPOUND_TEST(true, mp);
	BKSGE_IS_COMPOUND_TEST(true, cmf);
	BKSGE_IS_COMPOUND_TEST(true, foo0_t);
	BKSGE_IS_COMPOUND_TEST(true, foo1_t);
	BKSGE_IS_COMPOUND_TEST(true, foo2_t);
	BKSGE_IS_COMPOUND_TEST(true, foo3_t);
	BKSGE_IS_COMPOUND_TEST(true, foo4_t);
}

#undef BKSGE_IS_COMPOUND_TEST
