﻿/**
 *	@file	unit_test_fnd_type_traits_is_union.cpp
 *
 *	@brief	is_union のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_union.hpp>
#include <bksge/fnd/cstddef/nullptr_t.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_UNION_TEST(b, T)	\
	static_assert(bksge::is_union_v<T>      == b, #T);	\
	static_assert(bksge::is_union<T>::value == b, #T);	\
	static_assert(bksge::is_union<T>()      == b, #T)

#else

#define BKSGE_IS_UNION_TEST(b, T)	\
	static_assert(bksge::is_union<T>::value == b, #T);	\
	static_assert(bksge::is_union<T>()      == b, #T)

#endif

BKSGE_IS_UNION_TEST(true,                 union_UDT);
BKSGE_IS_UNION_TEST(true,  const          union_UDT);
BKSGE_IS_UNION_TEST(true,        volatile union_UDT);
BKSGE_IS_UNION_TEST(true,  const volatile union_UDT);
BKSGE_IS_UNION_TEST(false, union_UDT*);
BKSGE_IS_UNION_TEST(false, union_UDT&);
BKSGE_IS_UNION_TEST(false, union_UDT&&);
BKSGE_IS_UNION_TEST(false, union_UDT[2]);
BKSGE_IS_UNION_TEST(false, union_UDT[]);
BKSGE_IS_UNION_TEST(false, union_UDT(*)[2]);
BKSGE_IS_UNION_TEST(false, union_UDT(*)[]);
BKSGE_IS_UNION_TEST(false, union_UDT(&)[2]);
BKSGE_IS_UNION_TEST(false, union_UDT(&)[]);
BKSGE_IS_UNION_TEST(false, union_UDT(&&)[2]);
BKSGE_IS_UNION_TEST(false, union_UDT(&&)[]);

BKSGE_IS_UNION_TEST(false,                UDT);
BKSGE_IS_UNION_TEST(false, const          UDT);
BKSGE_IS_UNION_TEST(false,       volatile UDT);
BKSGE_IS_UNION_TEST(false, const volatile UDT);
BKSGE_IS_UNION_TEST(false, UDT*);
BKSGE_IS_UNION_TEST(false, UDT&);
BKSGE_IS_UNION_TEST(false, UDT&&);
BKSGE_IS_UNION_TEST(false, UDT[2]);
BKSGE_IS_UNION_TEST(false, UDT[]);
BKSGE_IS_UNION_TEST(false, UDT(*)[2]);
BKSGE_IS_UNION_TEST(false, UDT(*)[]);
BKSGE_IS_UNION_TEST(false, UDT(&)[2]);
BKSGE_IS_UNION_TEST(false, UDT(&)[]);
BKSGE_IS_UNION_TEST(false, UDT(&&)[2]);
BKSGE_IS_UNION_TEST(false, UDT(&&)[]);

BKSGE_IS_UNION_TEST(false,                void);
BKSGE_IS_UNION_TEST(false, const          void);
BKSGE_IS_UNION_TEST(false,       volatile void);
BKSGE_IS_UNION_TEST(false, const volatile void);

BKSGE_IS_UNION_TEST(false, bool);
BKSGE_IS_UNION_TEST(false, char);
BKSGE_IS_UNION_TEST(false, int);
BKSGE_IS_UNION_TEST(false, float);
BKSGE_IS_UNION_TEST(false, void*);
BKSGE_IS_UNION_TEST(false, bksge::nullptr_t);
BKSGE_IS_UNION_TEST(false, decltype(nullptr));
BKSGE_IS_UNION_TEST(false, enum_UDT);
BKSGE_IS_UNION_TEST(false, enum_uint32_t_UDT);
BKSGE_IS_UNION_TEST(false, enum_class_UDT);
BKSGE_IS_UNION_TEST(false, enum_class_uint32_t_UDT);
BKSGE_IS_UNION_TEST(false, UDT);
BKSGE_IS_UNION_TEST(false, POD_UDT);
BKSGE_IS_UNION_TEST(true,  union_UDT);
BKSGE_IS_UNION_TEST(true,  POD_union_UDT);
BKSGE_IS_UNION_TEST(true,  empty_union_UDT);
BKSGE_IS_UNION_TEST(true,  empty_POD_union_UDT);
BKSGE_IS_UNION_TEST(false, f1);
BKSGE_IS_UNION_TEST(false, f2);
BKSGE_IS_UNION_TEST(false, f3);
BKSGE_IS_UNION_TEST(false, mf1);
BKSGE_IS_UNION_TEST(false, mf2);
BKSGE_IS_UNION_TEST(false, mf3);
BKSGE_IS_UNION_TEST(false, mf4);
BKSGE_IS_UNION_TEST(false, mp);
BKSGE_IS_UNION_TEST(false, cmf);
BKSGE_IS_UNION_TEST(false, foo0_t);
BKSGE_IS_UNION_TEST(false, foo1_t);
BKSGE_IS_UNION_TEST(false, foo2_t);
BKSGE_IS_UNION_TEST(false, foo3_t);
BKSGE_IS_UNION_TEST(false, foo4_t);

#undef BKSGE_IS_UNION_TEST
