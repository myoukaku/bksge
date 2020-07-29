/**
 *	@file	unit_test_fnd_type_traits_is_literal_type.cpp
 *
 *	@brief	is_literal_type のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_literal_type.hpp>
#include <cstddef>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_LITERAL_TYPE_TEST(b, T)	\
	static_assert(bksge::is_literal_type<T>::value == b, #T " == " #b);	\
	static_assert(bksge::is_literal_type<T>()      == b, #T " == " #b)

BKSGE_IS_LITERAL_TYPE_TEST(true,                 int);
BKSGE_IS_LITERAL_TYPE_TEST(true,  const          int);
BKSGE_IS_LITERAL_TYPE_TEST(true,        volatile int);
BKSGE_IS_LITERAL_TYPE_TEST(true,  const volatile int);
BKSGE_IS_LITERAL_TYPE_TEST(true,  int*);
BKSGE_IS_LITERAL_TYPE_TEST(true,  int&);
BKSGE_IS_LITERAL_TYPE_TEST(true,  int&&);
BKSGE_IS_LITERAL_TYPE_TEST(true,  int[2]);
BKSGE_IS_LITERAL_TYPE_TEST(true,  int[]);
BKSGE_IS_LITERAL_TYPE_TEST(true,  int(&)[2]);
BKSGE_IS_LITERAL_TYPE_TEST(true,  int(&)[]);
BKSGE_IS_LITERAL_TYPE_TEST(true,  int(&&)[2]);
BKSGE_IS_LITERAL_TYPE_TEST(true,  int(&&)[]);

BKSGE_IS_LITERAL_TYPE_TEST(true,  bool);
BKSGE_IS_LITERAL_TYPE_TEST(true,  char);
BKSGE_IS_LITERAL_TYPE_TEST(true,  wchar_t);
BKSGE_IS_LITERAL_TYPE_TEST(true,  signed char);
BKSGE_IS_LITERAL_TYPE_TEST(true,  int);
BKSGE_IS_LITERAL_TYPE_TEST(true,  short);
BKSGE_IS_LITERAL_TYPE_TEST(true,  long);
BKSGE_IS_LITERAL_TYPE_TEST(true,  long long);
BKSGE_IS_LITERAL_TYPE_TEST(true,  unsigned char);
BKSGE_IS_LITERAL_TYPE_TEST(true,  unsigned int);
BKSGE_IS_LITERAL_TYPE_TEST(true,  unsigned short);
BKSGE_IS_LITERAL_TYPE_TEST(true,  unsigned long);
BKSGE_IS_LITERAL_TYPE_TEST(true,  unsigned long long);
BKSGE_IS_LITERAL_TYPE_TEST(true,  std::size_t);
BKSGE_IS_LITERAL_TYPE_TEST(true,  float);
BKSGE_IS_LITERAL_TYPE_TEST(true,  double);
BKSGE_IS_LITERAL_TYPE_TEST(true,  long double);
BKSGE_IS_LITERAL_TYPE_TEST(true,                 void);
BKSGE_IS_LITERAL_TYPE_TEST(true,  const          void);
BKSGE_IS_LITERAL_TYPE_TEST(true,        volatile void);
BKSGE_IS_LITERAL_TYPE_TEST(true,  const volatile void);
BKSGE_IS_LITERAL_TYPE_TEST(true,  void*);
BKSGE_IS_LITERAL_TYPE_TEST(true,  std::nullptr_t);
BKSGE_IS_LITERAL_TYPE_TEST(true,  decltype(nullptr));
BKSGE_IS_LITERAL_TYPE_TEST(true,  enum_UDT);
BKSGE_IS_LITERAL_TYPE_TEST(true,  enum_class_UDT);
BKSGE_IS_LITERAL_TYPE_TEST(false, UDT);
BKSGE_IS_LITERAL_TYPE_TEST(true,  UDT*);
BKSGE_IS_LITERAL_TYPE_TEST(true,  UDT&);
BKSGE_IS_LITERAL_TYPE_TEST(true,  UDT&&);
BKSGE_IS_LITERAL_TYPE_TEST(false, UDT[2]);
BKSGE_IS_LITERAL_TYPE_TEST(false, UDT[]);
BKSGE_IS_LITERAL_TYPE_TEST(true,  UDT(&)[2]);
BKSGE_IS_LITERAL_TYPE_TEST(true,  UDT(&)[]);
BKSGE_IS_LITERAL_TYPE_TEST(true,  UDT(&&)[2]);
BKSGE_IS_LITERAL_TYPE_TEST(true,  UDT(&&)[]);
BKSGE_IS_LITERAL_TYPE_TEST(true,  POD_UDT);
BKSGE_IS_LITERAL_TYPE_TEST(false, empty_UDT);
BKSGE_IS_LITERAL_TYPE_TEST(true,  empty_POD_UDT);
BKSGE_IS_LITERAL_TYPE_TEST(false, union_UDT);
BKSGE_IS_LITERAL_TYPE_TEST(true,  POD_union_UDT);
BKSGE_IS_LITERAL_TYPE_TEST(false, empty_union_UDT);
BKSGE_IS_LITERAL_TYPE_TEST(true,  empty_POD_union_UDT);
BKSGE_IS_LITERAL_TYPE_TEST(false, nothrow_default_ctor_UDT);
BKSGE_IS_LITERAL_TYPE_TEST(false, nothrow_dtor_UDT);
BKSGE_IS_LITERAL_TYPE_TEST(false, nothrow_copy_ctor_UDT);
BKSGE_IS_LITERAL_TYPE_TEST(false, nothrow_copy_assign_UDT);
BKSGE_IS_LITERAL_TYPE_TEST(false, nothrow_move_ctor_UDT);
BKSGE_IS_LITERAL_TYPE_TEST(false, nothrow_move_assign_UDT);
BKSGE_IS_LITERAL_TYPE_TEST(true,  Base);
BKSGE_IS_LITERAL_TYPE_TEST(true,  Derived);
BKSGE_IS_LITERAL_TYPE_TEST(true,  Derived2);
BKSGE_IS_LITERAL_TYPE_TEST(true,  MultiBase);
BKSGE_IS_LITERAL_TYPE_TEST(true,  PrivateBase);
BKSGE_IS_LITERAL_TYPE_TEST(true,  NonDerived);
BKSGE_IS_LITERAL_TYPE_TEST(true,  enum1);
BKSGE_IS_LITERAL_TYPE_TEST(true,  enum2);
BKSGE_IS_LITERAL_TYPE_TEST(false, VB);
BKSGE_IS_LITERAL_TYPE_TEST(false, VD);
BKSGE_IS_LITERAL_TYPE_TEST(true,  non_pointer);
BKSGE_IS_LITERAL_TYPE_TEST(true,  non_int_pointer);
BKSGE_IS_LITERAL_TYPE_TEST(false, int_constructible);
BKSGE_IS_LITERAL_TYPE_TEST(true,  int_convertible);
BKSGE_IS_LITERAL_TYPE_TEST(false, test_abc1);
//	BKSGE_IS_LITERAL_TYPE_TEST(false, test_abc2);
BKSGE_IS_LITERAL_TYPE_TEST(false, test_abc3);
BKSGE_IS_LITERAL_TYPE_TEST(false, polymorphic_base);
BKSGE_IS_LITERAL_TYPE_TEST(false, polymorphic_derived1);
BKSGE_IS_LITERAL_TYPE_TEST(false, polymorphic_derived2);
//	BKSGE_IS_LITERAL_TYPE_TEST(false, virtual_inherit1);
//	BKSGE_IS_LITERAL_TYPE_TEST(false, virtual_inherit2);
//	BKSGE_IS_LITERAL_TYPE_TEST(false, virtual_inherit3);
//	BKSGE_IS_LITERAL_TYPE_TEST(false, virtual_inherit5);
BKSGE_IS_LITERAL_TYPE_TEST(false, virtual_inherit6);
BKSGE_IS_LITERAL_TYPE_TEST(false, trivial_except_construct);
BKSGE_IS_LITERAL_TYPE_TEST(false, trivial_except_destroy);
BKSGE_IS_LITERAL_TYPE_TEST(false, trivial_except_copy_ctor);
BKSGE_IS_LITERAL_TYPE_TEST(false, trivial_except_move_ctor);
BKSGE_IS_LITERAL_TYPE_TEST(true,  trivial_except_copy_assign);
BKSGE_IS_LITERAL_TYPE_TEST(true,  trivial_except_move_assign);
BKSGE_IS_LITERAL_TYPE_TEST(true,  f1);
BKSGE_IS_LITERAL_TYPE_TEST(true,  f2);
BKSGE_IS_LITERAL_TYPE_TEST(true,  f3);
BKSGE_IS_LITERAL_TYPE_TEST(true,  mf1);
BKSGE_IS_LITERAL_TYPE_TEST(true,  mf2);
BKSGE_IS_LITERAL_TYPE_TEST(true,  mf3);
BKSGE_IS_LITERAL_TYPE_TEST(true,  mf4);
BKSGE_IS_LITERAL_TYPE_TEST(true,  mp);
BKSGE_IS_LITERAL_TYPE_TEST(true,  cmf);
BKSGE_IS_LITERAL_TYPE_TEST(false, foo0_t);
BKSGE_IS_LITERAL_TYPE_TEST(false, foo1_t);
BKSGE_IS_LITERAL_TYPE_TEST(false, foo2_t);
BKSGE_IS_LITERAL_TYPE_TEST(false, foo3_t);
BKSGE_IS_LITERAL_TYPE_TEST(false, foo4_t);

#undef BKSGE_IS_LITERAL_TYPE_TEST
