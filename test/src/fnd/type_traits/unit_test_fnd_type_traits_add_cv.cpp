/**
 *	@file	unit_test_fnd_type_traits_add_cv.cpp
 *
 *	@brief	add_cv のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/add_cv.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

BKSGE_TRANSFORM_TEST(bksge::add_cv, /**/,           const volatile);
BKSGE_TRANSFORM_TEST(bksge::add_cv, const,          const volatile);
BKSGE_TRANSFORM_TEST(bksge::add_cv,       volatile, const volatile);
BKSGE_TRANSFORM_TEST(bksge::add_cv, const volatile, const volatile);
BKSGE_TRANSFORM_TEST(bksge::add_cv,                &,                &);
BKSGE_TRANSFORM_TEST(bksge::add_cv, const          &, const          &);
BKSGE_TRANSFORM_TEST(bksge::add_cv,       volatile &,       volatile &);
BKSGE_TRANSFORM_TEST(bksge::add_cv, const volatile &, const volatile &);
BKSGE_TRANSFORM_TEST(bksge::add_cv, *,               *const volatile);
BKSGE_TRANSFORM_TEST(bksge::add_cv, *const,          *const volatile);
BKSGE_TRANSFORM_TEST(bksge::add_cv, *      volatile, *const volatile);
BKSGE_TRANSFORM_TEST(bksge::add_cv, *const volatile, *const volatile);
BKSGE_TRANSFORM_TEST(bksge::add_cv, const          *, const          * const volatile);
BKSGE_TRANSFORM_TEST(bksge::add_cv,       volatile *,       volatile * const volatile);
BKSGE_TRANSFORM_TEST(bksge::add_cv, const volatile *, const volatile * const volatile);
BKSGE_TRANSFORM_TEST(bksge::add_cv,               [2], const volatile[2]);
BKSGE_TRANSFORM_TEST(bksge::add_cv, const         [2], const volatile[2]);
BKSGE_TRANSFORM_TEST(bksge::add_cv,       volatile[2], const volatile[2]);
BKSGE_TRANSFORM_TEST(bksge::add_cv, const volatile[2], const volatile[2]);
BKSGE_TRANSFORM_TEST(bksge::add_cv,                (&)[2],                (&)[2]);
BKSGE_TRANSFORM_TEST(bksge::add_cv, const          (&)[2], const          (&)[2]);
BKSGE_TRANSFORM_TEST(bksge::add_cv,       volatile (&)[2],       volatile (&)[2]);
BKSGE_TRANSFORM_TEST(bksge::add_cv, const volatile (&)[2], const volatile (&)[2]);
BKSGE_TRANSFORM_TEST(bksge::add_cv,                &&,                &&);
BKSGE_TRANSFORM_TEST(bksge::add_cv, const          &&, const          &&);
BKSGE_TRANSFORM_TEST(bksge::add_cv,       volatile &&,       volatile &&);
BKSGE_TRANSFORM_TEST(bksge::add_cv, const volatile &&, const volatile &&);
BKSGE_TRANSFORM_TEST(bksge::add_cv,                (&&)[2],                (&&)[2]);
BKSGE_TRANSFORM_TEST(bksge::add_cv, const          (&&)[2], const          (&&)[2]);
BKSGE_TRANSFORM_TEST(bksge::add_cv,       volatile (&&)[2],       volatile (&&)[2]);
BKSGE_TRANSFORM_TEST(bksge::add_cv, const volatile (&&)[2], const volatile (&&)[2]);

#define BKSGE_ADD_CV_TEST(T1, T2)	\
	static_assert(bksge::is_same<bksge::add_cv_t<T1>, T2>::value, "");	\
	static_assert(bksge::is_same<bksge::add_cv<T1>::type, T2>::value, "")

BKSGE_ADD_CV_TEST(               void, const volatile void);
BKSGE_ADD_CV_TEST(const          void, const volatile void);
BKSGE_ADD_CV_TEST(      volatile void, const volatile void);
BKSGE_ADD_CV_TEST(const volatile void, const volatile void);
BKSGE_ADD_CV_TEST(               void*,                void* const volatile);
BKSGE_ADD_CV_TEST(const          void*, const          void* const volatile);
BKSGE_ADD_CV_TEST(      volatile void*,       volatile void* const volatile);
BKSGE_ADD_CV_TEST(const volatile void*, const volatile void* const volatile);
BKSGE_ADD_CV_TEST(int(int), int(int));
BKSGE_ADD_CV_TEST(void (UDT::*)(void), void (UDT::* const volatile)(void));
BKSGE_ADD_CV_TEST(int (UDT::*)(int), int (UDT::* const volatile)(int));
BKSGE_ADD_CV_TEST(int (UDT::*)(int, float), int (UDT::* const volatile)(int, float));
BKSGE_ADD_CV_TEST(int (UDT::*)(int) const, int (UDT::* const volatile)(int) const);
BKSGE_ADD_CV_TEST(int (UDT::*)(int) volatile, int (UDT::* const volatile)(int) volatile);
BKSGE_ADD_CV_TEST(int (UDT::*)(int) const volatile, int (UDT::* const volatile)(int) const volatile);
BKSGE_ADD_CV_TEST(int (UDT::*), int (UDT::* const volatile));
BKSGE_ADD_CV_TEST(const float (UDT::*), const float (UDT::* const volatile));

#undef BKSGE_ADD_CV_TEST
