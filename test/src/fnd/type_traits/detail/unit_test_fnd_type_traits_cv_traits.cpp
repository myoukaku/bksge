/**
 *	@file	unit_test_fnd_type_traits_cv_traits.cpp
 *
 *	@brief	cv_traits のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/detail/cv_traits.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace bksge_type_traits_test
{

namespace cv_traits_test
{

struct S {};

#define BKSGE_CV_TRAITS_TEST(T, CV)	\
	static_assert(bksge::is_same<bksge::detail::cv_traits<T>::type, bksge::detail::CV>::value, "")

BKSGE_CV_TRAITS_TEST(               int, cv_qualifier_none);
BKSGE_CV_TRAITS_TEST(const          int, cv_qualifier_const);
BKSGE_CV_TRAITS_TEST(      volatile int, cv_qualifier_volatile);
BKSGE_CV_TRAITS_TEST(const volatile int, cv_qualifier_cv);
BKSGE_CV_TRAITS_TEST(void (S::*               )()               , cv_qualifier_none);
BKSGE_CV_TRAITS_TEST(void (S::*               )() const         , cv_qualifier_none);
BKSGE_CV_TRAITS_TEST(void (S::*               )()       volatile, cv_qualifier_none);
BKSGE_CV_TRAITS_TEST(void (S::*               )() const volatile, cv_qualifier_none);
BKSGE_CV_TRAITS_TEST(void (S::* const         )()               , cv_qualifier_const);
BKSGE_CV_TRAITS_TEST(void (S::* const         )() const         , cv_qualifier_const);
BKSGE_CV_TRAITS_TEST(void (S::* const         )()       volatile, cv_qualifier_const);
BKSGE_CV_TRAITS_TEST(void (S::* const         )() const volatile, cv_qualifier_const);
BKSGE_CV_TRAITS_TEST(void (S::*       volatile)()               , cv_qualifier_volatile);
BKSGE_CV_TRAITS_TEST(void (S::*       volatile)() const         , cv_qualifier_volatile);
BKSGE_CV_TRAITS_TEST(void (S::*       volatile)()       volatile, cv_qualifier_volatile);
BKSGE_CV_TRAITS_TEST(void (S::*       volatile)() const volatile, cv_qualifier_volatile);
BKSGE_CV_TRAITS_TEST(void (S::* const volatile)()               , cv_qualifier_cv);
BKSGE_CV_TRAITS_TEST(void (S::* const volatile)() const         , cv_qualifier_cv);
BKSGE_CV_TRAITS_TEST(void (S::* const volatile)()       volatile, cv_qualifier_cv);
BKSGE_CV_TRAITS_TEST(void (S::* const volatile)() const volatile, cv_qualifier_cv);

#undef BKSGE_CV_TRAITS_TEST

#define BKSGE_MEM_FN_CV_TRAITS_TEST(T, CV)	\
	static_assert(bksge::is_same<bksge::detail::member_function_cv_traits<T>::type, bksge::detail::CV>::value, "")

BKSGE_MEM_FN_CV_TRAITS_TEST(void (S::*               )()               , cv_qualifier_none);
BKSGE_MEM_FN_CV_TRAITS_TEST(void (S::*               )() const         , cv_qualifier_const);
BKSGE_MEM_FN_CV_TRAITS_TEST(void (S::*               )()       volatile, cv_qualifier_volatile);
BKSGE_MEM_FN_CV_TRAITS_TEST(void (S::*               )() const volatile, cv_qualifier_cv);
BKSGE_MEM_FN_CV_TRAITS_TEST(void (S::* const         )()               , cv_qualifier_none);
BKSGE_MEM_FN_CV_TRAITS_TEST(void (S::* const         )() const         , cv_qualifier_const);
BKSGE_MEM_FN_CV_TRAITS_TEST(void (S::* const         )()       volatile, cv_qualifier_volatile);
BKSGE_MEM_FN_CV_TRAITS_TEST(void (S::* const         )() const volatile, cv_qualifier_cv);
BKSGE_MEM_FN_CV_TRAITS_TEST(void (S::*       volatile)()               , cv_qualifier_none);
BKSGE_MEM_FN_CV_TRAITS_TEST(void (S::*       volatile)() const         , cv_qualifier_const);
BKSGE_MEM_FN_CV_TRAITS_TEST(void (S::*       volatile)()       volatile, cv_qualifier_volatile);
BKSGE_MEM_FN_CV_TRAITS_TEST(void (S::*       volatile)() const volatile, cv_qualifier_cv);
BKSGE_MEM_FN_CV_TRAITS_TEST(void (S::* const volatile)()               , cv_qualifier_none);
BKSGE_MEM_FN_CV_TRAITS_TEST(void (S::* const volatile)() const         , cv_qualifier_const);
BKSGE_MEM_FN_CV_TRAITS_TEST(void (S::* const volatile)()       volatile, cv_qualifier_volatile);
BKSGE_MEM_FN_CV_TRAITS_TEST(void (S::* const volatile)() const volatile, cv_qualifier_cv);

#undef BKSGE_MEM_FN_CV_TRAITS_TEST

}	// namespace cv_traits_test

}	// namespace bksge_type_traits_test
