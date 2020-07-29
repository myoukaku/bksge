/**
 *	@file	unit_test_fnd_type_traits_type_identity.cpp
 *
 *	@brief	type_identity のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/type_identity.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_TYPE_IDENTITY_TEST_IMPL(T)	\
	static_assert(bksge::is_same<bksge::type_identity<T>::type, T>::value, "");	\
	static_assert(bksge::is_same<bksge::type_identity_t<T>, T>::value, "");	\
	/**/

#define BKSGE_TYPE_IDENTITY_TEST_IMPL_CV(T)	\
	BKSGE_TYPE_IDENTITY_TEST_IMPL(T);	\
	BKSGE_TYPE_IDENTITY_TEST_IMPL(const T);	\
	BKSGE_TYPE_IDENTITY_TEST_IMPL(volatile T);	\
	BKSGE_TYPE_IDENTITY_TEST_IMPL(const volatile T);	\
	/**/

#define BKSGE_TYPE_IDENTITY_TEST(T)	\
	BKSGE_TYPE_IDENTITY_TEST_IMPL_CV(T);	\
	BKSGE_TYPE_IDENTITY_TEST_IMPL_CV(T&);	\
	BKSGE_TYPE_IDENTITY_TEST_IMPL_CV(T&&);	\
	BKSGE_TYPE_IDENTITY_TEST_IMPL_CV(T*);	\
	BKSGE_TYPE_IDENTITY_TEST_IMPL_CV(T[2]);	\
	BKSGE_TYPE_IDENTITY_TEST_IMPL_CV(T[]);	\
	BKSGE_TYPE_IDENTITY_TEST_IMPL_CV(T(&)[2]);	\
	BKSGE_TYPE_IDENTITY_TEST_IMPL_CV(T(&&)[2]);	\
	/**/

BKSGE_TYPE_IDENTITY_TEST(int);
BKSGE_TYPE_IDENTITY_TEST(char);
BKSGE_TYPE_IDENTITY_TEST(float);
BKSGE_TYPE_IDENTITY_TEST(UDT);
BKSGE_TYPE_IDENTITY_TEST(enum_UDT);
BKSGE_TYPE_IDENTITY_TEST(void*);
BKSGE_TYPE_IDENTITY_TEST_IMPL_CV(void);

#undef BKSGE_TYPE_IDENTITY_TEST_IMPL
#undef BKSGE_TYPE_IDENTITY_TEST_IMPL_CV
#undef BKSGE_TYPE_IDENTITY_TEST
