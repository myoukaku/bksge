/**
 *	@file	unit_test_fnd_type_traits_alignment_of.cpp
 *
 *	@brief	alignment_of のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/alignment_of.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstddef/nullptr_t.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

namespace type_traits_test
{

namespace alignment_of_test
{

#define BKSGE_ALIGNMENT_OF_TEST_IMPL(x, T)	\
	static_assert(bksge::alignment_of<T>::value == x, #T);	\
	static_assert(bksge::alignment_of<T>()      == x, #T)

#define BKSGE_ALIGNMENT_OF_TEST(x, T)	\
	BKSGE_ALIGNMENT_OF_TEST_IMPL(x, T);	\
	BKSGE_ALIGNMENT_OF_TEST_IMPL(x, T&);	\
	BKSGE_ALIGNMENT_OF_TEST_IMPL(x, T&&);	\
	BKSGE_ALIGNMENT_OF_TEST_IMPL(x, T[2]);	\
	BKSGE_ALIGNMENT_OF_TEST_IMPL(x, T[]);	\
	BKSGE_ALIGNMENT_OF_TEST_IMPL(x, T(&)[2]);	\
	BKSGE_ALIGNMENT_OF_TEST_IMPL(x, T(&)[]);	\
	BKSGE_ALIGNMENT_OF_TEST_IMPL(x, T(&&)[2]);	\
	BKSGE_ALIGNMENT_OF_TEST_IMPL(x, T(&&)[])

#define BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(T)	\
	BKSGE_ALIGNMENT_OF_TEST(sizeof(T), T)

static auto const alignment_of_mf = bksge::alignment_of<mf1>::value;

BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(bool);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(char);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(wchar_t);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(signed char);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(int);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(short);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(long);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(long long);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(unsigned char);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(unsigned int);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(unsigned short);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(unsigned long);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(unsigned long long);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(bksge::size_t);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(float);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(double);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(long double);
//BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(void);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(void*);
//BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(bksge::nullptr_t);
//BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(decltype(nullptr));
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(enum_UDT);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(enum_uint32_t_UDT);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(enum_uint16_t_UDT);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(enum_uint8_t_UDT);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(enum_int32_t_UDT);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(enum_int16_t_UDT);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(enum_int8_t_UDT);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(enum_class_UDT);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(enum_class_uint32_t_UDT);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(enum_class_uint16_t_UDT);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(enum_class_uint8_t_UDT);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(enum_class_int32_t_UDT);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(enum_class_int16_t_UDT);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(enum_class_int8_t_UDT);
BKSGE_ALIGNMENT_OF_TEST(sizeof(int), UDT);
BKSGE_ALIGNMENT_OF_TEST(sizeof(int), POD_UDT);
BKSGE_ALIGNMENT_OF_TEST(1, empty_UDT);
BKSGE_ALIGNMENT_OF_TEST(1, empty_POD_UDT);
BKSGE_ALIGNMENT_OF_TEST(sizeof(double), union_UDT);
BKSGE_ALIGNMENT_OF_TEST(sizeof(double), POD_union_UDT);
BKSGE_ALIGNMENT_OF_TEST(1, empty_union_UDT);
BKSGE_ALIGNMENT_OF_TEST(1, empty_POD_union_UDT);
BKSGE_ALIGNMENT_OF_TEST(1, nothrow_default_ctor_UDT);
BKSGE_ALIGNMENT_OF_TEST(1, nothrow_dtor_UDT);
BKSGE_ALIGNMENT_OF_TEST(1, nothrow_copy_ctor_UDT);
BKSGE_ALIGNMENT_OF_TEST(1, nothrow_copy_assign_UDT);
BKSGE_ALIGNMENT_OF_TEST(1, nothrow_move_ctor_UDT);
BKSGE_ALIGNMENT_OF_TEST(1, nothrow_move_assign_UDT);
BKSGE_ALIGNMENT_OF_TEST(1, Base);
BKSGE_ALIGNMENT_OF_TEST(1, Derived);
BKSGE_ALIGNMENT_OF_TEST(1, Derived2);
BKSGE_ALIGNMENT_OF_TEST(1, MultiBase);
BKSGE_ALIGNMENT_OF_TEST(1, PrivateBase);
BKSGE_ALIGNMENT_OF_TEST(1, NonDerived);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(enum1);
BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE(enum2);
BKSGE_ALIGNMENT_OF_TEST(alignment_of_mf, VB);
BKSGE_ALIGNMENT_OF_TEST(alignment_of_mf, VD);
BKSGE_ALIGNMENT_OF_TEST(1, non_pointer);
BKSGE_ALIGNMENT_OF_TEST(sizeof(int), non_int_pointer);
BKSGE_ALIGNMENT_OF_TEST(1, int_constructible);
BKSGE_ALIGNMENT_OF_TEST(1, int_convertible);
//BKSGE_ALIGNMENT_OF_TEST_2(8, test_abc1);
//BKSGE_ALIGNMENT_OF_TEST_2(8, test_abc2);
//BKSGE_ALIGNMENT_OF_TEST_2(8, test_abc3);
//BKSGE_ALIGNMENT_OF_TEST(1, incomplete_type);
BKSGE_ALIGNMENT_OF_TEST(alignment_of_mf, polymorphic_base);
BKSGE_ALIGNMENT_OF_TEST(alignment_of_mf, polymorphic_derived1);
BKSGE_ALIGNMENT_OF_TEST(alignment_of_mf, polymorphic_derived2);
BKSGE_ALIGNMENT_OF_TEST(alignment_of_mf, virtual_inherit1);
BKSGE_ALIGNMENT_OF_TEST(alignment_of_mf, virtual_inherit2);
BKSGE_ALIGNMENT_OF_TEST(alignment_of_mf, virtual_inherit3);
BKSGE_ALIGNMENT_OF_TEST(alignment_of_mf, virtual_inherit5);
BKSGE_ALIGNMENT_OF_TEST(alignment_of_mf, virtual_inherit6);
BKSGE_ALIGNMENT_OF_TEST(sizeof(int), trivial_except_construct);
BKSGE_ALIGNMENT_OF_TEST(sizeof(int), trivial_except_destroy);
BKSGE_ALIGNMENT_OF_TEST(sizeof(int), trivial_except_copy_ctor);
BKSGE_ALIGNMENT_OF_TEST(sizeof(int), trivial_except_move_ctor);
BKSGE_ALIGNMENT_OF_TEST(sizeof(int), trivial_except_copy_assign);
BKSGE_ALIGNMENT_OF_TEST(sizeof(int), trivial_except_move_assign);
BKSGE_ALIGNMENT_OF_TEST_IMPL(sizeof(f1),		f1);
BKSGE_ALIGNMENT_OF_TEST_IMPL(sizeof(f2),		f2);
BKSGE_ALIGNMENT_OF_TEST_IMPL(sizeof(f3),		f3);
BKSGE_ALIGNMENT_OF_TEST_IMPL(alignment_of_mf,	mf1);
BKSGE_ALIGNMENT_OF_TEST_IMPL(alignment_of_mf,	mf2);
BKSGE_ALIGNMENT_OF_TEST_IMPL(alignment_of_mf,	mf3);
BKSGE_ALIGNMENT_OF_TEST_IMPL(alignment_of_mf,	mf4);
//BKSGE_ALIGNMENT_OF_TEST_IMPL(sizeof(mp),		mp);
BKSGE_ALIGNMENT_OF_TEST_IMPL(alignment_of_mf,	cmf);
//BKSGE_ALIGNMENT_OF_TEST_IMPL(8, foo0_t);
//BKSGE_ALIGNMENT_OF_TEST_IMPL(8, foo1_t);
//BKSGE_ALIGNMENT_OF_TEST_IMPL(8, foo2_t);
//BKSGE_ALIGNMENT_OF_TEST_IMPL(8, foo3_t);
//BKSGE_ALIGNMENT_OF_TEST_IMPL(8, foo4_t);

#undef BKSGE_ALIGNMENT_OF_TEST_PRIMITIVE
#undef BKSGE_ALIGNMENT_OF_TEST
#undef BKSGE_ALIGNMENT_OF_TEST_IMPL

}	// namespace alignment_of_test

}	// namespace type_traits_test
