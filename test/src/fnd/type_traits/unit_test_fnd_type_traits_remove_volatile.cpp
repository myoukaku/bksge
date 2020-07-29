/**
 *	@file	unit_test_fnd_type_traits_remove_volatile.cpp
 *
 *	@brief	remove_volatile のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/remove_volatile.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

BKSGE_TRANSFORM_TEST(bksge::remove_volatile, /**/          , /**/);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const         , const);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,       volatile, /**/);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const volatile, const);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,                &,                &);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const          &, const          &);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,       volatile &,       volatile &);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const volatile &, const volatile &);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,                &&,                &&);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const          &&, const          &&);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,       volatile &&,       volatile &&);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const volatile &&, const volatile &&);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, *               , *               );
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, * const         , * const         );
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, *       volatile, *               );
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, * const volatile, * const         );
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const          *, const          *);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,       volatile *,       volatile *);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const volatile *, const volatile *);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,                [2],                [2]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const          [2], const          [2]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,       volatile [2],                [2]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const volatile [2], const          [2]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,                [],                []);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const          [], const          []);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,       volatile [],                []);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const volatile [], const          []);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,                (&)[2],                (&)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const          (&)[2], const          (&)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,       volatile (&)[2],       volatile (&)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const volatile (&)[2], const volatile (&)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,                (&)[],                (&)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const          (&)[], const          (&)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,       volatile (&)[],       volatile (&)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const volatile (&)[], const volatile (&)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,                (&&)[2],                (&&)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const          (&&)[2], const          (&&)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,       volatile (&&)[2],       volatile (&&)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const volatile (&&)[2], const volatile (&&)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,                (&&)[],                (&&)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const          (&&)[], const          (&&)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,       volatile (&&)[],       volatile (&&)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const volatile (&&)[], const volatile (&&)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,                (*)[2],                (*)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const          (*)[2], const          (*)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,       volatile (*)[2],       volatile (*)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const volatile (*)[2], const volatile (*)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,                (*)[],                (*)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const          (*)[], const          (*)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile,       volatile (*)[],       volatile (*)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_volatile, const volatile (*)[], const volatile (*)[]);

#define BKSGE_REMOVE_VOLATILE_TEST(T1, T2)	\
	static_assert(bksge::is_same<bksge::remove_volatile_t<T1>, T2>::value, "");	\
	static_assert(bksge::is_same<bksge::remove_volatile<T1>::type, T2>::value, "")

BKSGE_REMOVE_VOLATILE_TEST(               void,       void);
BKSGE_REMOVE_VOLATILE_TEST(const          void, const void);
BKSGE_REMOVE_VOLATILE_TEST(      volatile void,       void);
BKSGE_REMOVE_VOLATILE_TEST(const volatile void, const void);
BKSGE_REMOVE_VOLATILE_TEST(void(void), void(void));
BKSGE_REMOVE_VOLATILE_TEST(int(void), int(void));
BKSGE_REMOVE_VOLATILE_TEST(void(int), void(int));
BKSGE_REMOVE_VOLATILE_TEST(int(int), int(int));
BKSGE_REMOVE_VOLATILE_TEST(int(char, short), int(char, short));
BKSGE_REMOVE_VOLATILE_TEST(int(float, double, long double), int(float, double, long double));
BKSGE_REMOVE_VOLATILE_TEST(int(*)(int), int(*)(int));
BKSGE_REMOVE_VOLATILE_TEST(int(&)(int), int(&)(int));
BKSGE_REMOVE_VOLATILE_TEST(int(&&)(int), int(&&)(int));
BKSGE_REMOVE_VOLATILE_TEST(void (UDT::*)(void), void (UDT::*)(void));
BKSGE_REMOVE_VOLATILE_TEST(int (UDT::*)(int), int (UDT::*)(int));
BKSGE_REMOVE_VOLATILE_TEST(int (UDT::*)(int, float), int (UDT::*)(int, float));
BKSGE_REMOVE_VOLATILE_TEST(int (UDT::*)(int) const, int (UDT::*)(int) const);
BKSGE_REMOVE_VOLATILE_TEST(int (UDT::*)(int) volatile, int (UDT::*)(int) volatile);
BKSGE_REMOVE_VOLATILE_TEST(int (UDT::*)(int) const volatile, int (UDT::*)(int) const volatile);
BKSGE_REMOVE_VOLATILE_TEST(int (UDT::*), int (UDT::*));
BKSGE_REMOVE_VOLATILE_TEST(const float (UDT::*), const float (UDT::*));

#undef BKSGE_REMOVE_VOLATILE_TEST
