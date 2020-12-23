/**
 *	@file	unit_test_fnd_type_traits_is_bounded_array.cpp
 *
 *	@brief	is_bounded_array のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_bounded_array.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_BOUNDED_ARRAY_TEST(b, T)	\
	static_assert(bksge::is_bounded_array<T>::value == b, #T);	\
	static_assert(bksge::is_bounded_array<T>()      == b, #T)

#define BKSGE_IS_BOUNDED_ARRAY_TEST_CV(b, T)	\
	BKSGE_IS_BOUNDED_ARRAY_TEST(b,                T);	\
	BKSGE_IS_BOUNDED_ARRAY_TEST(b, const          T);	\
	BKSGE_IS_BOUNDED_ARRAY_TEST(b,       volatile T);	\
	BKSGE_IS_BOUNDED_ARRAY_TEST(b, const volatile T)

BKSGE_IS_BOUNDED_ARRAY_TEST_CV(false, int);
BKSGE_IS_BOUNDED_ARRAY_TEST_CV(false, int[]);
BKSGE_IS_BOUNDED_ARRAY_TEST_CV(true,  int[3]);
BKSGE_IS_BOUNDED_ARRAY_TEST_CV(true,  int[4][5]);
BKSGE_IS_BOUNDED_ARRAY_TEST_CV(false, int[][5]);
BKSGE_IS_BOUNDED_ARRAY_TEST_CV(false, int*);
BKSGE_IS_BOUNDED_ARRAY_TEST_CV(false, int&);
BKSGE_IS_BOUNDED_ARRAY_TEST_CV(false, int&&);

BKSGE_IS_BOUNDED_ARRAY_TEST_CV(false, char);
BKSGE_IS_BOUNDED_ARRAY_TEST_CV(false, char[]);
BKSGE_IS_BOUNDED_ARRAY_TEST_CV(true,  char[4]);
BKSGE_IS_BOUNDED_ARRAY_TEST_CV(false, float);
BKSGE_IS_BOUNDED_ARRAY_TEST_CV(false, void*);
BKSGE_IS_BOUNDED_ARRAY_TEST_CV(false, enum_UDT);
BKSGE_IS_BOUNDED_ARRAY_TEST_CV(false, enum_class_UDT);
BKSGE_IS_BOUNDED_ARRAY_TEST_CV(false, UDT);
BKSGE_IS_BOUNDED_ARRAY_TEST_CV(false, empty_UDT);
BKSGE_IS_BOUNDED_ARRAY_TEST_CV(false, union_UDT);
BKSGE_IS_BOUNDED_ARRAY_TEST_CV(false, incomplete_type);
BKSGE_IS_BOUNDED_ARRAY_TEST_CV(false, incomplete_type[]);
BKSGE_IS_BOUNDED_ARRAY_TEST_CV(true,  incomplete_type[5]);

#undef BKSGE_IS_BOUNDED_ARRAY_TEST
#undef BKSGE_IS_BOUNDED_ARRAY_TEST_CV
