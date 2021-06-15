/**
 *	@file	unit_test_fnd_type_traits_decay.cpp
 *
 *	@brief	decay のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_DECAY_TEST_IMPL(T1, T2)	\
	static_assert(bksge::is_same<bksge::decay<T1>::type, T2>::value, #T1 ", " #T2);	\
	static_assert(bksge::is_same<bksge::decay_t<T1>,     T2>::value, #T1 ", " #T2)

#define BKSGE_DECAY_TEST(T)	\
	BKSGE_DECAY_TEST_IMPL(               T, T);	\
	BKSGE_DECAY_TEST_IMPL(const          T, T);	\
	BKSGE_DECAY_TEST_IMPL(      volatile T, T);	\
	BKSGE_DECAY_TEST_IMPL(const volatile T, T);	\
	BKSGE_DECAY_TEST_IMPL(               T&, T);	\
	BKSGE_DECAY_TEST_IMPL(const          T&, T);	\
	BKSGE_DECAY_TEST_IMPL(      volatile T&, T);	\
	BKSGE_DECAY_TEST_IMPL(const volatile T&, T);	\
	BKSGE_DECAY_TEST_IMPL(               T&&, T);	\
	BKSGE_DECAY_TEST_IMPL(const          T&&, T);	\
	BKSGE_DECAY_TEST_IMPL(      volatile T&&, T);	\
	BKSGE_DECAY_TEST_IMPL(const volatile T&&, T);	\
	BKSGE_DECAY_TEST_IMPL(               T*,                T*);	\
	BKSGE_DECAY_TEST_IMPL(const          T*, const          T*);	\
	BKSGE_DECAY_TEST_IMPL(      volatile T*,       volatile T*);	\
	BKSGE_DECAY_TEST_IMPL(const volatile T*, const volatile T*);	\
	BKSGE_DECAY_TEST_IMPL(               T*&,                T*);	\
	BKSGE_DECAY_TEST_IMPL(const          T*&, const          T*);	\
	BKSGE_DECAY_TEST_IMPL(      volatile T*&,       volatile T*);	\
	BKSGE_DECAY_TEST_IMPL(const volatile T*&, const volatile T*);	\
	BKSGE_DECAY_TEST_IMPL(               T*&&,                T*);	\
	BKSGE_DECAY_TEST_IMPL(const          T*&&, const          T*);	\
	BKSGE_DECAY_TEST_IMPL(      volatile T*&&,       volatile T*);	\
	BKSGE_DECAY_TEST_IMPL(const volatile T*&&, const volatile T*);	\
	BKSGE_DECAY_TEST_IMPL(               T[2],                T*);	\
	BKSGE_DECAY_TEST_IMPL(const          T[3], const          T*);	\
	BKSGE_DECAY_TEST_IMPL(      volatile T[4],       volatile T*);	\
	BKSGE_DECAY_TEST_IMPL(const volatile T[5], const volatile T*);	\
	BKSGE_DECAY_TEST_IMPL(               T[],                T*);	\
	BKSGE_DECAY_TEST_IMPL(const          T[], const          T*);	\
	BKSGE_DECAY_TEST_IMPL(      volatile T[],       volatile T*);	\
	BKSGE_DECAY_TEST_IMPL(const volatile T[], const volatile T*);	\
	BKSGE_DECAY_TEST_IMPL(               T(*)[2],                T(*)[2]);	\
	BKSGE_DECAY_TEST_IMPL(const          T(*)[3], const          T(*)[3]);	\
	BKSGE_DECAY_TEST_IMPL(      volatile T(*)[4],       volatile T(*)[4]);	\
	BKSGE_DECAY_TEST_IMPL(const volatile T(*)[5], const volatile T(*)[5]);	\
	BKSGE_DECAY_TEST_IMPL(               T(&)[2],                T*);	\
	BKSGE_DECAY_TEST_IMPL(const          T(&)[3], const          T*);	\
	BKSGE_DECAY_TEST_IMPL(      volatile T(&)[4],       volatile T*);	\
	BKSGE_DECAY_TEST_IMPL(const volatile T(&)[5], const volatile T*);	\
	BKSGE_DECAY_TEST_IMPL(               T(&)[],                T*);	\
	BKSGE_DECAY_TEST_IMPL(const          T(&)[], const          T*);	\
	BKSGE_DECAY_TEST_IMPL(      volatile T(&)[],       volatile T*);	\
	BKSGE_DECAY_TEST_IMPL(const volatile T(&)[], const volatile T*);	\
	BKSGE_DECAY_TEST_IMPL(               T(&&)[2],                T*);	\
	BKSGE_DECAY_TEST_IMPL(const          T(&&)[3], const          T*);	\
	BKSGE_DECAY_TEST_IMPL(      volatile T(&&)[4],       volatile T*);	\
	BKSGE_DECAY_TEST_IMPL(const volatile T(&&)[5], const volatile T*);	\
	BKSGE_DECAY_TEST_IMPL(               T(&&)[],                T*);	\
	BKSGE_DECAY_TEST_IMPL(const          T(&&)[], const          T*);	\
	BKSGE_DECAY_TEST_IMPL(      volatile T(&&)[],       volatile T*);	\
	BKSGE_DECAY_TEST_IMPL(const volatile T(&&)[], const volatile T*);	\
	BKSGE_DECAY_TEST_IMPL(T(T), T(*)(T));	\
	BKSGE_DECAY_TEST_IMPL(T(void), T(*)(void));	\
	BKSGE_DECAY_TEST_IMPL(void(T), void(*)(T));	\
	BKSGE_DECAY_TEST_IMPL(T(T, T), T(*)(T, T))

BKSGE_DECAY_TEST(int);
BKSGE_DECAY_TEST(UDT);
BKSGE_DECAY_TEST_IMPL(f1, f1);
BKSGE_DECAY_TEST_IMPL(f2, f2);
BKSGE_DECAY_TEST_IMPL(f3, f3);
BKSGE_DECAY_TEST_IMPL(mf1, mf1);
BKSGE_DECAY_TEST_IMPL(mf2, mf2);
BKSGE_DECAY_TEST_IMPL(mf3, mf3);
BKSGE_DECAY_TEST_IMPL(mf4, mf4);
BKSGE_DECAY_TEST_IMPL(mp, mp);
BKSGE_DECAY_TEST_IMPL(cmf, cmf);
BKSGE_DECAY_TEST_IMPL(foo0_t, void (*)(void));
BKSGE_DECAY_TEST_IMPL(foo1_t, void (*)(int));
BKSGE_DECAY_TEST_IMPL(foo2_t, void (*)(int&, double));
BKSGE_DECAY_TEST_IMPL(foo3_t, void (*)(int&, bool, int, int));
BKSGE_DECAY_TEST_IMPL(foo4_t, void (*)(int, bool, int*, int[], int, int, int, int, int));

#undef BKSGE_DECAY_TEST
#undef BKSGE_DECAY_TEST_IMPL
