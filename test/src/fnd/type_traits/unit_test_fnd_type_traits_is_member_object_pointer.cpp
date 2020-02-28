/**
 *	@file	unit_test_fnd_type_traits_is_member_object_pointer.cpp
 *
 *	@brief	is_member_object_pointer のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_member_object_pointer.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(b, T)	\
	static_assert(bksge::is_member_object_pointer<T>::value == b, #T)

GTEST_TEST(TypeTraitsTest, IsMemberObjectPointerTest)
{
	IntegralConstantTest<bksge::is_member_object_pointer<f1>, false>();
	IntegralConstantTest<bksge::is_member_object_pointer<mf1>, false>();
	IntegralConstantTest<bksge::is_member_object_pointer<mp>, true>();
	IntegralConstantTest<bksge::is_member_object_pointer<foo0_t>, false>();

	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false,                int);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, const          int);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false,       volatile int);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, const volatile int);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false,                int*);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, const          int*);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false,       volatile int*);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, const volatile int*);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, int**);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, int&);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, int&&);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, int[2]);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, int[]);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, int(*)[2]);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, int(*)[]);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, int(&)[2]);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, int(&)[]);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, int(&&)[2]);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, int(&&)[]);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(true,  int  (UDT::*               ));
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(true,  float(UDT::* const         ));
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(true,  char (UDT::*       volatile));
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(true,  void*(UDT::* const volatile));
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, int  (UDT::*               )()               );
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, int  (UDT::*               )() const         );
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, int  (UDT::*               )()       volatile);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, int  (UDT::*               )() const volatile);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, float(UDT::* const         )(int)               );
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, float(UDT::* const         )(int) const         );
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, float(UDT::* const         )(int)       volatile);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, float(UDT::* const         )(int) const volatile);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, void (UDT::*       volatile)(int, int)               );
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, void (UDT::*       volatile)(int, int) const         );
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, void (UDT::*       volatile)(int, int)       volatile);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, void (UDT::*       volatile)(int, int) const volatile);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, char (UDT::* const volatile)(int, int, int)               );
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, char (UDT::* const volatile)(int, int, int) const         );
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, char (UDT::* const volatile)(int, int, int)       volatile);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, char (UDT::* const volatile)(int, int, int) const volatile);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, int  (UDT::*               )(...)               );
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, int  (UDT::*               )(...) const         );
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, int  (UDT::*               )(...)       volatile);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, int  (UDT::*               )(...) const volatile);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, float(UDT::* const         )(int, ...)               );
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, float(UDT::* const         )(int, ...) const         );
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, float(UDT::* const         )(int, ...)       volatile);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, float(UDT::* const         )(int, ...) const volatile);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, void (UDT::*       volatile)(int, int, ...)               );
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, void (UDT::*       volatile)(int, int, ...) const         );
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, void (UDT::*       volatile)(int, int, ...)       volatile);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, void (UDT::*       volatile)(int, int, ...) const volatile);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, char (UDT::* const volatile)(int, int, int, ...)               );
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, char (UDT::* const volatile)(int, int, int, ...) const         );
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, char (UDT::* const volatile)(int, int, int, ...)       volatile);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, char (UDT::* const volatile)(int, int, int, ...) const volatile);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, f1);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, f2);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, f3);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, mf1);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, mf2);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, mf3);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, mf4);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(true,  mp);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, mp&);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, cmf);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, foo0_t);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, foo1_t);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, foo2_t);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, foo3_t);
	BKSGE_IS_MEMBER_OBJECT_POINTER_TEST(false, foo4_t);
}

#undef BKSGE_IS_MEMBER_OBJECT_POINTER_TEST
