/**
 *	@file	unit_test_fnd_type_traits_remove_reference.cpp
 *
 *	@brief	remove_reference のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

GTEST_TEST(TypeTraitsTest, RemoveReferenceTest)
{
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, /**/          , /**/          );
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, const         , const         );
	BKSGE_TRANSFORM_TEST(bksge::remove_reference,       volatile,       volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, const volatile, const volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference,                &, /**/          );
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, const          &, const         );
	BKSGE_TRANSFORM_TEST(bksge::remove_reference,       volatile &,       volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, const volatile &, const volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, *               , *               );
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, * const         , * const         );
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, *       volatile, *       volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, * const volatile, * const volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, const          *, const          *);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference,       volatile *,       volatile *);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, const volatile *, const volatile *);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference,                *&,                *);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, const          *&, const          *);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference,       volatile *&,       volatile *);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, const volatile *&, const volatile *);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference,                *&&,                *);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, const          *&&, const          *);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference,       volatile *&&,       volatile *);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, const volatile *&&, const volatile *);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference,                [2],                [2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, const          [2], const          [2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference,       volatile [2],       volatile [2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, const volatile [2], const volatile [2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference,                (&)[2],                [2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, const          (&)[2], const          [2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference,       volatile (&)[2],       volatile [2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, const volatile (&)[2], const volatile [2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference,                &&, /**/);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, const          &&, const);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference,       volatile &&,       volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, const volatile &&, const volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference,                (&&)[2],                [2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, const          (&&)[2], const          [2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference,       volatile (&&)[2],       volatile [2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_reference, const volatile (&&)[2], const volatile [2]);

#define BKSGE_REMOVE_REFERENCE_TEST(T1, T2)	\
	static_assert(bksge::is_same<bksge::remove_reference_t<T1>, T2>::value, "");	\
	static_assert(bksge::is_same<bksge::remove_reference<T1>::type, T2>::value, "")

	BKSGE_REMOVE_REFERENCE_TEST(               void,                void);
	BKSGE_REMOVE_REFERENCE_TEST(const          void, const          void);
	BKSGE_REMOVE_REFERENCE_TEST(      volatile void,       volatile void);
	BKSGE_REMOVE_REFERENCE_TEST(const volatile void, const volatile void);
	BKSGE_REMOVE_REFERENCE_TEST(void(void), void(void));
	BKSGE_REMOVE_REFERENCE_TEST(int(void), int(void));
	BKSGE_REMOVE_REFERENCE_TEST(void(int), void(int));
	BKSGE_REMOVE_REFERENCE_TEST(int(int), int(int));
	BKSGE_REMOVE_REFERENCE_TEST(int(char, short), int(char, short));
	BKSGE_REMOVE_REFERENCE_TEST(int(float, double, long double), int(float, double, long double));
	BKSGE_REMOVE_REFERENCE_TEST(int(*)(int), int(*)(int));
	BKSGE_REMOVE_REFERENCE_TEST(int(&)(int), int(int));
	BKSGE_REMOVE_REFERENCE_TEST(int(&&)(int), int(int));
	BKSGE_REMOVE_REFERENCE_TEST(void (UDT::*)(void), void (UDT::*)(void));
	BKSGE_REMOVE_REFERENCE_TEST(void (UDT::*&)(void), void (UDT::*)(void));
	BKSGE_REMOVE_REFERENCE_TEST(int (UDT::*)(int), int (UDT::*)(int));
	BKSGE_REMOVE_REFERENCE_TEST(int (UDT::*)(int, float), int (UDT::*)(int, float));
	BKSGE_REMOVE_REFERENCE_TEST(int (UDT::*)(int) const, int (UDT::*)(int) const);
	BKSGE_REMOVE_REFERENCE_TEST(int (UDT::*)(int) volatile, int (UDT::*)(int) volatile);
	BKSGE_REMOVE_REFERENCE_TEST(int (UDT::*)(int) const volatile, int (UDT::*)(int) const volatile);
	BKSGE_REMOVE_REFERENCE_TEST(int (UDT::*), int (UDT::*));
	BKSGE_REMOVE_REFERENCE_TEST(const float (UDT::*), const float (UDT::*));

#undef BKSGE_REMOVE_REFERENCE_TEST
}
