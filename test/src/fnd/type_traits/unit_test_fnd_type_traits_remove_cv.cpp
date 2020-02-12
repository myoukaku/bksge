/**
 *	@file	unit_test_fnd_type_traits_remove_cv.cpp
 *
 *	@brief	remove_cv のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <type_traits>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

GTEST_TEST(TypeTraitsTest, RemoveCvTest)
{
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, /**/          , /**/);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const         , /**/);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,       volatile, /**/);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const volatile, /**/);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,                &,                &);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const          &, const          &);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,       volatile &,       volatile &);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const volatile &, const volatile &);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,                &&,                &&);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const          &&, const          &&);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,       volatile &&,       volatile &&);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const volatile &&, const volatile &&);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, *               , *               );
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, * const         , *               );
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, *       volatile, *               );
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, * const volatile, *               );
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const          *, const          *);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,       volatile *,       volatile *);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const volatile *, const volatile *);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,                [2],                [2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const          [2],                [2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,       volatile [2],                [2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const volatile [2],                [2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,                [],                []);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const          [],                []);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,       volatile [],                []);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const volatile [],                []);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,                (&)[2],                (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const          (&)[2], const          (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,       volatile (&)[2],       volatile (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const volatile (&)[2], const volatile (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,                (&)[],                (&)[]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const          (&)[], const          (&)[]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,       volatile (&)[],       volatile (&)[]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const volatile (&)[], const volatile (&)[]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,                (&&)[2],                (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const          (&&)[2], const          (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,       volatile (&&)[2],       volatile (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const volatile (&&)[2], const volatile (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,                (&&)[],                (&&)[]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const          (&&)[], const          (&&)[]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,       volatile (&&)[],       volatile (&&)[]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const volatile (&&)[], const volatile (&&)[]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,                (*)[2],                (*)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const          (*)[2], const          (*)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,       volatile (*)[2],       volatile (*)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const volatile (*)[2], const volatile (*)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,                (*)[],                (*)[]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const          (*)[], const          (*)[]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv,       volatile (*)[],       volatile (*)[]);
	BKSGE_TRANSFORM_TEST(bksge::remove_cv, const volatile (*)[], const volatile (*)[]);

#define BKSGE_REMOVE_CV_TEST(T1, T2)	\
	static_assert(std::is_same<bksge::remove_cv_t<T1>, T2>::value, "");	\
	static_assert(std::is_same<bksge::remove_cv<T1>::type, T2>::value, "")

	BKSGE_REMOVE_CV_TEST(               void, void);
	BKSGE_REMOVE_CV_TEST(const          void, void);
	BKSGE_REMOVE_CV_TEST(      volatile void, void);
	BKSGE_REMOVE_CV_TEST(const volatile void, void);
	BKSGE_REMOVE_CV_TEST(void(void), void(void));
	BKSGE_REMOVE_CV_TEST(int(void), int(void));
	BKSGE_REMOVE_CV_TEST(void(int), void(int));
	BKSGE_REMOVE_CV_TEST(int(int), int(int));
	BKSGE_REMOVE_CV_TEST(int(char, short), int(char, short));
	BKSGE_REMOVE_CV_TEST(int(float, double, long double), int(float, double, long double));
	BKSGE_REMOVE_CV_TEST(int(*)(int), int(*)(int));
	BKSGE_REMOVE_CV_TEST(int(&)(int), int(&)(int));
	BKSGE_REMOVE_CV_TEST(int(&&)(int), int(&&)(int));
	BKSGE_REMOVE_CV_TEST(void (UDT::*)(void), void (UDT::*)(void));
	BKSGE_REMOVE_CV_TEST(int (UDT::*)(int), int (UDT::*)(int));
	BKSGE_REMOVE_CV_TEST(int (UDT::*)(int, float), int (UDT::*)(int, float));
	BKSGE_REMOVE_CV_TEST(int (UDT::*)(int) const, int (UDT::*)(int) const);
	BKSGE_REMOVE_CV_TEST(int (UDT::*)(int) volatile, int (UDT::*)(int) volatile);
	BKSGE_REMOVE_CV_TEST(int (UDT::*)(int) const volatile, int (UDT::*)(int) const volatile);
	BKSGE_REMOVE_CV_TEST(int (UDT::*), int (UDT::*));
	BKSGE_REMOVE_CV_TEST(const float (UDT::*), const float (UDT::*));

#undef BKSGE_REMOVE_CV_TEST
}
