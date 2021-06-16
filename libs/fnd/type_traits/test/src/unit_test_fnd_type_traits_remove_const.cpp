/**
 *	@file	unit_test_fnd_type_traits_remove_const.cpp
 *
 *	@brief	remove_const のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/remove_const.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

BKSGE_TRANSFORM_TEST(bksge::remove_const, /**/          , /**/);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const         , /**/);
BKSGE_TRANSFORM_TEST(bksge::remove_const,       volatile,       volatile);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const volatile,       volatile);
BKSGE_TRANSFORM_TEST(bksge::remove_const,                &,                &);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const          &, const          &);
BKSGE_TRANSFORM_TEST(bksge::remove_const,       volatile &,       volatile &);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const volatile &, const volatile &);
BKSGE_TRANSFORM_TEST(bksge::remove_const,                &&,                &&);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const          &&, const          &&);
BKSGE_TRANSFORM_TEST(bksge::remove_const,       volatile &&,       volatile &&);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const volatile &&, const volatile &&);
BKSGE_TRANSFORM_TEST(bksge::remove_const, *               , *               );
BKSGE_TRANSFORM_TEST(bksge::remove_const, * const         , *               );
BKSGE_TRANSFORM_TEST(bksge::remove_const, *       volatile, *       volatile);
BKSGE_TRANSFORM_TEST(bksge::remove_const, * const volatile, *       volatile);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const          *, const          *);
BKSGE_TRANSFORM_TEST(bksge::remove_const,       volatile *,       volatile *);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const volatile *, const volatile *);
BKSGE_TRANSFORM_TEST(bksge::remove_const,                [2],                [2]);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const          [2],                [2]);
BKSGE_TRANSFORM_TEST(bksge::remove_const,       volatile [2],       volatile [2]);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const volatile [2],       volatile [2]);
BKSGE_TRANSFORM_TEST(bksge::remove_const,                [],                []);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const          [],                []);
BKSGE_TRANSFORM_TEST(bksge::remove_const,       volatile [],       volatile []);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const volatile [],       volatile []);
BKSGE_TRANSFORM_TEST(bksge::remove_const,                (&)[2],                (&)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const          (&)[2], const          (&)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_const,       volatile (&)[2],       volatile (&)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const volatile (&)[2], const volatile (&)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_const,                (&)[],                (&)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const          (&)[], const          (&)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_const,       volatile (&)[],       volatile (&)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const volatile (&)[], const volatile (&)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_const,                (&&)[2],                (&&)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const          (&&)[2], const          (&&)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_const,       volatile (&&)[2],       volatile (&&)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const volatile (&&)[2], const volatile (&&)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_const,                (&&)[],                (&&)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const          (&&)[], const          (&&)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_const,       volatile (&&)[],       volatile (&&)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const volatile (&&)[], const volatile (&&)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_const,                (*)[2],                (*)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const          (*)[2], const          (*)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_const,       volatile (*)[2],       volatile (*)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const volatile (*)[2], const volatile (*)[2]);
BKSGE_TRANSFORM_TEST(bksge::remove_const,                (*)[],                (*)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const          (*)[], const          (*)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_const,       volatile (*)[],       volatile (*)[]);
BKSGE_TRANSFORM_TEST(bksge::remove_const, const volatile (*)[], const volatile (*)[]);

#define BKSGE_REMOVE_CONST_TEST(T1, T2)	\
	static_assert(bksge::is_same<bksge::remove_const_t<T1>, T2>::value, "");	\
	static_assert(bksge::is_same<bksge::remove_const<T1>::type, T2>::value, "")

BKSGE_REMOVE_CONST_TEST(               void,          void);
BKSGE_REMOVE_CONST_TEST(const          void,          void);
BKSGE_REMOVE_CONST_TEST(      volatile void, volatile void);
BKSGE_REMOVE_CONST_TEST(const volatile void, volatile void);
BKSGE_REMOVE_CONST_TEST(void(void), void(void));
BKSGE_REMOVE_CONST_TEST(int(void), int(void));
BKSGE_REMOVE_CONST_TEST(void(int), void(int));
BKSGE_REMOVE_CONST_TEST(int(int), int(int));
BKSGE_REMOVE_CONST_TEST(int(char, short), int(char, short));
BKSGE_REMOVE_CONST_TEST(int(float, double, long double), int(float, double, long double));
BKSGE_REMOVE_CONST_TEST(int(*)(int), int(*)(int));
BKSGE_REMOVE_CONST_TEST(int(&)(int), int(&)(int));
BKSGE_REMOVE_CONST_TEST(int(&&)(int), int(&&)(int));
BKSGE_REMOVE_CONST_TEST(void (UDT::*)(void), void (UDT::*)(void));
BKSGE_REMOVE_CONST_TEST(int (UDT::*)(int), int (UDT::*)(int));
BKSGE_REMOVE_CONST_TEST(int (UDT::*)(int, float), int (UDT::*)(int, float));
BKSGE_REMOVE_CONST_TEST(int (UDT::*)(int) const, int (UDT::*)(int) const);
BKSGE_REMOVE_CONST_TEST(int (UDT::*)(int) volatile, int (UDT::*)(int) volatile);
BKSGE_REMOVE_CONST_TEST(int (UDT::*)(int) const volatile, int (UDT::*)(int) const volatile);
BKSGE_REMOVE_CONST_TEST(int (UDT::*), int (UDT::*));
BKSGE_REMOVE_CONST_TEST(const float (UDT::*), const float (UDT::*));

#undef BKSGE_REMOVE_CONST_TEST
