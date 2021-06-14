/**
 *	@file	unit_test_fnd_type_traits_remove_constref.cpp
 *
 *	@brief	remove_constref のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/remove_constref.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_REMOVE_CONSTREF_TEST_IMPL(T1, T2)	\
	static_assert(bksge::is_same<bksge::remove_constref<T1>::type, T2>::value, #T1 ", " #T2);	\
	static_assert(bksge::is_same<bksge::remove_constref_t<T1>,     T2>::value, #T1 ", " #T2)

#define BKSGE_REMOVE_CONSTREF_TEST(T)	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(               T, T);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const          T, T);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(      volatile T, volatile T);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const volatile T, volatile T);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(               T&, T);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const          T&, T);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(      volatile T&, volatile T);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const volatile T&, volatile T);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(               T&&, T);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const          T&&, T);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(      volatile T&&, volatile T);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const volatile T&&, volatile T);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(               T*,                T*);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const          T*, const          T*);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(      volatile T*,       volatile T*);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const volatile T*, const volatile T*);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(               T*&,                T*);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const          T*&, const          T*);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(      volatile T*&,       volatile T*);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const volatile T*&, const volatile T*);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(               T*&&,                T*);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const          T*&&, const          T*);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(      volatile T*&&,       volatile T*);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const volatile T*&&, const volatile T*);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(               T[2],                T[2]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const          T[3],                T[3]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(      volatile T[4],       volatile T[4]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const volatile T[5],       volatile T[5]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(               T[],                T[]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const          T[],                T[]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(      volatile T[],       volatile T[]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const volatile T[],       volatile T[]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(               T(*)[2],                T(*)[2]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const          T(*)[3], const          T(*)[3]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(      volatile T(*)[4],       volatile T(*)[4]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const volatile T(*)[5], const volatile T(*)[5]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(               T(&)[2],                T[2]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const          T(&)[3],                T[3]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(      volatile T(&)[4],       volatile T[4]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const volatile T(&)[5],       volatile T[5]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(               T(&)[],                T[]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const          T(&)[],                T[]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(      volatile T(&)[],       volatile T[]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const volatile T(&)[],       volatile T[]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(               T(&&)[2],                T[2]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const          T(&&)[3],                T[3]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(      volatile T(&&)[4],       volatile T[4]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const volatile T(&&)[5],       volatile T[5]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(               T(&&)[],                T[]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const          T(&&)[],                T[]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(      volatile T(&&)[],       volatile T[]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(const volatile T(&&)[],       volatile T[]);	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(T(T), T(T));	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(T(void), T(void));	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(void(T), void(T));	\
	BKSGE_REMOVE_CONSTREF_TEST_IMPL(T(T, T), T(T, T))

BKSGE_REMOVE_CONSTREF_TEST(int);
BKSGE_REMOVE_CONSTREF_TEST(UDT);
BKSGE_REMOVE_CONSTREF_TEST_IMPL(f1, f1);
BKSGE_REMOVE_CONSTREF_TEST_IMPL(f2, f2);
BKSGE_REMOVE_CONSTREF_TEST_IMPL(f3, f3);
BKSGE_REMOVE_CONSTREF_TEST_IMPL(mf1, mf1);
BKSGE_REMOVE_CONSTREF_TEST_IMPL(mf2, mf2);
BKSGE_REMOVE_CONSTREF_TEST_IMPL(mf3, mf3);
BKSGE_REMOVE_CONSTREF_TEST_IMPL(mf4, mf4);
BKSGE_REMOVE_CONSTREF_TEST_IMPL(mp, mp);
BKSGE_REMOVE_CONSTREF_TEST_IMPL(cmf, cmf);
BKSGE_REMOVE_CONSTREF_TEST_IMPL(foo0_t, foo0_t);
BKSGE_REMOVE_CONSTREF_TEST_IMPL(foo1_t, foo1_t);
BKSGE_REMOVE_CONSTREF_TEST_IMPL(foo2_t, foo2_t);
BKSGE_REMOVE_CONSTREF_TEST_IMPL(foo3_t, foo3_t);
BKSGE_REMOVE_CONSTREF_TEST_IMPL(foo4_t, foo4_t);

#undef BKSGE_REMOVE_CONSTREF_TEST
#undef BKSGE_REMOVE_CONSTREF_TEST_IMPL
