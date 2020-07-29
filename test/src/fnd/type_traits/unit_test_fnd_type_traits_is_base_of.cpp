/**
 *	@file	unit_test_fnd_type_traits_is_base_of.cpp
 *
 *	@brief	is_base_of のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_BASE_OF_TEST(b, T, U)	\
	static_assert(bksge::is_base_of<T, U>::value == b, "is_base_of<" #T ", " #U "> == " #b);	\
	static_assert(bksge::is_base_of<T, U>()      == b, "is_base_of<" #T ", " #U "> == " #b)

#define BKSGE_IS_BASE_OF_TEST_CV(b, T, U)	\
	BKSGE_IS_BASE_OF_TEST(b,                T,                U);	\
	BKSGE_IS_BASE_OF_TEST(b,                T, const          U);	\
	BKSGE_IS_BASE_OF_TEST(b,                T,       volatile U);	\
	BKSGE_IS_BASE_OF_TEST(b,                T, const volatile U);	\
	BKSGE_IS_BASE_OF_TEST(b, const          T,                U);	\
	BKSGE_IS_BASE_OF_TEST(b, const          T, const          U);	\
	BKSGE_IS_BASE_OF_TEST(b, const          T,       volatile U);	\
	BKSGE_IS_BASE_OF_TEST(b, const          T, const volatile U);	\
	BKSGE_IS_BASE_OF_TEST(b,       volatile T,                U);	\
	BKSGE_IS_BASE_OF_TEST(b,       volatile T, const          U);	\
	BKSGE_IS_BASE_OF_TEST(b,       volatile T,       volatile U);	\
	BKSGE_IS_BASE_OF_TEST(b,       volatile T, const volatile U);	\
	BKSGE_IS_BASE_OF_TEST(b, const volatile T,                U);	\
	BKSGE_IS_BASE_OF_TEST(b, const volatile T, const          U);	\
	BKSGE_IS_BASE_OF_TEST(b, const volatile T,       volatile U);	\
	BKSGE_IS_BASE_OF_TEST(b, const volatile T, const volatile U)

BKSGE_IS_BASE_OF_TEST_CV(false, int, int);
BKSGE_IS_BASE_OF_TEST_CV(false, int, char);
BKSGE_IS_BASE_OF_TEST_CV(false, int, float);
BKSGE_IS_BASE_OF_TEST_CV(false, int, void);
BKSGE_IS_BASE_OF_TEST_CV(false, char, int);
BKSGE_IS_BASE_OF_TEST_CV(false, float, int);
BKSGE_IS_BASE_OF_TEST_CV(false, void, int);
BKSGE_IS_BASE_OF_TEST_CV(false, void, void);
BKSGE_IS_BASE_OF_TEST_CV(false, int, int*);
BKSGE_IS_BASE_OF_TEST_CV(false, int, int&);
BKSGE_IS_BASE_OF_TEST_CV(false, int, int&&);
BKSGE_IS_BASE_OF_TEST_CV(false, int*, int);
BKSGE_IS_BASE_OF_TEST_CV(false, int*, int*);
BKSGE_IS_BASE_OF_TEST_CV(false, int*, int&);
BKSGE_IS_BASE_OF_TEST_CV(false, int*, int&&);
BKSGE_IS_BASE_OF_TEST_CV(false, int&, int);
BKSGE_IS_BASE_OF_TEST_CV(false, int&, int*);
BKSGE_IS_BASE_OF_TEST_CV(false, int&, int&);
BKSGE_IS_BASE_OF_TEST_CV(false, int&, int&&);
BKSGE_IS_BASE_OF_TEST_CV(false, int&&, int);
BKSGE_IS_BASE_OF_TEST_CV(false, int&&, int*);
BKSGE_IS_BASE_OF_TEST_CV(false, int&&, int&);
BKSGE_IS_BASE_OF_TEST_CV(false, int&&, int&&);
BKSGE_IS_BASE_OF_TEST_CV(false, enum_UDT, enum_UDT);
BKSGE_IS_BASE_OF_TEST_CV(false, enum_class_UDT, enum_class_UDT);
BKSGE_IS_BASE_OF_TEST_CV(false, f1, f1);
BKSGE_IS_BASE_OF_TEST_CV(false, f2, f2);
BKSGE_IS_BASE_OF_TEST_CV(false, f3, f3);
BKSGE_IS_BASE_OF_TEST_CV(false, mf1, mf1);
BKSGE_IS_BASE_OF_TEST_CV(false, mf2, mf2);
BKSGE_IS_BASE_OF_TEST_CV(false, mf3, mf3);
BKSGE_IS_BASE_OF_TEST_CV(false, mf4, mf4);
BKSGE_IS_BASE_OF_TEST_CV(false, mp, mp);
BKSGE_IS_BASE_OF_TEST_CV(false, cmf, cmf);
BKSGE_IS_BASE_OF_TEST_CV(true,  UDT, UDT);
BKSGE_IS_BASE_OF_TEST_CV(false, UDT*, UDT*);
BKSGE_IS_BASE_OF_TEST_CV(false, UDT&, UDT&);
BKSGE_IS_BASE_OF_TEST_CV(false, UDT&&, UDT&&);
BKSGE_IS_BASE_OF_TEST_CV(true,  POD_UDT, POD_UDT);
BKSGE_IS_BASE_OF_TEST_CV(true,  empty_UDT, empty_UDT);
BKSGE_IS_BASE_OF_TEST_CV(true,  empty_POD_UDT, empty_POD_UDT);
BKSGE_IS_BASE_OF_TEST_CV(false, union_UDT, union_UDT);
BKSGE_IS_BASE_OF_TEST_CV(false, POD_union_UDT, POD_union_UDT);
BKSGE_IS_BASE_OF_TEST_CV(false, empty_union_UDT, empty_union_UDT);
BKSGE_IS_BASE_OF_TEST_CV(false, empty_POD_union_UDT, empty_POD_union_UDT);
BKSGE_IS_BASE_OF_TEST_CV(false, Derived, Base);
BKSGE_IS_BASE_OF_TEST_CV(true,  Derived, Derived);
BKSGE_IS_BASE_OF_TEST_CV(true,  Base, Base);
BKSGE_IS_BASE_OF_TEST_CV(true,  Base, Derived);
BKSGE_IS_BASE_OF_TEST_CV(true,  Base, MultiBase);
BKSGE_IS_BASE_OF_TEST_CV(true,  Derived, MultiBase);
BKSGE_IS_BASE_OF_TEST_CV(true,  Derived2, MultiBase);
BKSGE_IS_BASE_OF_TEST_CV(true,  Base, PrivateBase);
BKSGE_IS_BASE_OF_TEST_CV(false, NonDerived, Base);
BKSGE_IS_BASE_OF_TEST_CV(false, Base, void);
BKSGE_IS_BASE_OF_TEST_CV(false, Derived, void);
BKSGE_IS_BASE_OF_TEST_CV(false, void, Base);
BKSGE_IS_BASE_OF_TEST_CV(false, void, Derived);
BKSGE_IS_BASE_OF_TEST_CV(true,  VB, VD);
BKSGE_IS_BASE_OF_TEST_CV(false, VD, VB);
BKSGE_IS_BASE_OF_TEST_CV(true,  test_abc1, test_abc3);
BKSGE_IS_BASE_OF_TEST_CV(false, test_abc3, test_abc1);
BKSGE_IS_BASE_OF_TEST_CV(true,  Base, virtual_inherit1);
BKSGE_IS_BASE_OF_TEST_CV(false, virtual_inherit1, Base);
BKSGE_IS_BASE_OF_TEST_CV(true,  virtual_inherit1, virtual_inherit2);
BKSGE_IS_BASE_OF_TEST_CV(false, virtual_inherit2, virtual_inherit1);
BKSGE_IS_BASE_OF_TEST_CV(true,  Base, virtual_inherit3);
BKSGE_IS_BASE_OF_TEST_CV(false, virtual_inherit3, Base);
BKSGE_IS_BASE_OF_TEST_CV(true,  polymorphic_base, polymorphic_derived1);
BKSGE_IS_BASE_OF_TEST_CV(true,  polymorphic_base, polymorphic_derived2);
BKSGE_IS_BASE_OF_TEST_CV(true,  polymorphic_base, polymorphic_base);
BKSGE_IS_BASE_OF_TEST_CV(true,  polymorphic_derived1, polymorphic_derived1);
BKSGE_IS_BASE_OF_TEST_CV(true,  polymorphic_derived2, polymorphic_derived2);
BKSGE_IS_BASE_OF_TEST_CV(false, polymorphic_derived1, polymorphic_base);
BKSGE_IS_BASE_OF_TEST_CV(false, polymorphic_derived2, polymorphic_base);

#undef BKSGE_IS_BASE_OF_TEST
#undef BKSGE_IS_BASE_OF_TEST_CV
