/**
 *	@file	unit_test_fnd_type_traits_rank.cpp
 *
 *	@brief	rank のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/rank.hpp>
#include <bksge/fnd/cstddef/nullptr_t.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_RANK_TEST_IMPL(T, N)	\
	static_assert(bksge::rank<T>::value == N, "");	\
	static_assert(bksge::rank<T>()      == N, "")

#define BKSGE_RANK_TEST_CV(T, N)	\
	BKSGE_RANK_TEST_IMPL(T, N);	\
	BKSGE_RANK_TEST_IMPL(const T, N);	\
	BKSGE_RANK_TEST_IMPL(volatile T, N);	\
	BKSGE_RANK_TEST_IMPL(const volatile T, N)

#define BKSGE_RANK_TEST(T)	\
	BKSGE_RANK_TEST_CV(T, 0);	\
	BKSGE_RANK_TEST_CV(T[], 1);	\
	BKSGE_RANK_TEST_CV(T[2], 1);	\
	BKSGE_RANK_TEST_CV(T[2][3], 2);	\
	BKSGE_RANK_TEST_CV(T[][3], 2);	\
	BKSGE_RANK_TEST_CV(T[4][5][6], 3);	\
	BKSGE_RANK_TEST_CV(T[][2][3], 3);	\
	BKSGE_RANK_TEST_CV(T[1][2][3][4], 4);	\
	BKSGE_RANK_TEST_CV(T[][2][3][4][6], 5)

BKSGE_RANK_TEST(bool);
BKSGE_RANK_TEST(char);
BKSGE_RANK_TEST(int);
BKSGE_RANK_TEST(float);
BKSGE_RANK_TEST(double);
BKSGE_RANK_TEST(void*);
BKSGE_RANK_TEST(bksge::nullptr_t);
BKSGE_RANK_TEST(decltype(nullptr));
BKSGE_RANK_TEST(enum_UDT);
BKSGE_RANK_TEST(enum_class_UDT);
BKSGE_RANK_TEST(UDT);
BKSGE_RANK_TEST(POD_UDT);
BKSGE_RANK_TEST(union_UDT);
BKSGE_RANK_TEST(POD_union_UDT);
BKSGE_RANK_TEST(f1);
BKSGE_RANK_TEST(f2);
BKSGE_RANK_TEST(f3);
BKSGE_RANK_TEST(mf1);
BKSGE_RANK_TEST(mf2);
BKSGE_RANK_TEST(mf3);
BKSGE_RANK_TEST(mf4);
BKSGE_RANK_TEST(mp);
BKSGE_RANK_TEST(cmf);

#undef BKSGE_RANK_TEST
#undef BKSGE_RANK_TEST_CV
#undef BKSGE_RANK_TEST_IMPL
