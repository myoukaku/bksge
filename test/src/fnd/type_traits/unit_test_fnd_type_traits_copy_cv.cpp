/**
 *	@file	unit_test_fnd_type_traits_copy_cv.cpp
 *
 *	@brief	copy_cv のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/copy_cv.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>

#define BKSGE_COPY_CV_TEST(T1, T2, T3)	\
	static_assert(bksge::is_same<bksge::copy_cv<T1, T2>::type, T3>::value, "");	\
	static_assert(bksge::is_same<bksge::copy_cv_t<T1, T2>,     T3>::value, "")

// 基本的なテスト
BKSGE_COPY_CV_TEST(               int,                void,                int);
BKSGE_COPY_CV_TEST(const          int,                void, const          int);
BKSGE_COPY_CV_TEST(      volatile int,                void,       volatile int);
BKSGE_COPY_CV_TEST(const volatile int,                void, const volatile int);

BKSGE_COPY_CV_TEST(               int, const          void, const          int);
BKSGE_COPY_CV_TEST(const          int, const          void, const          int);
BKSGE_COPY_CV_TEST(      volatile int, const          void, const volatile int);
BKSGE_COPY_CV_TEST(const volatile int, const          void, const volatile int);

BKSGE_COPY_CV_TEST(               int,       volatile void,       volatile int);
BKSGE_COPY_CV_TEST(const          int,       volatile void, const volatile int);
BKSGE_COPY_CV_TEST(      volatile int,       volatile void,       volatile int);
BKSGE_COPY_CV_TEST(const volatile int,       volatile void, const volatile int);

BKSGE_COPY_CV_TEST(               int, const volatile void, const volatile int);
BKSGE_COPY_CV_TEST(const          int, const volatile void, const volatile int);
BKSGE_COPY_CV_TEST(      volatile int, const volatile void, const volatile int);
BKSGE_COPY_CV_TEST(const volatile int, const volatile void, const volatile int);

BKSGE_COPY_CV_TEST(               int,                float[2],                int);
BKSGE_COPY_CV_TEST(const          int,                float[2], const          int);
BKSGE_COPY_CV_TEST(      volatile int,                float[2],       volatile int);
BKSGE_COPY_CV_TEST(const volatile int,                float[2], const volatile int);

BKSGE_COPY_CV_TEST(               int, const          float[2], const          int);
BKSGE_COPY_CV_TEST(const          int, const          float[2], const          int);
BKSGE_COPY_CV_TEST(      volatile int, const          float[2], const volatile int);
BKSGE_COPY_CV_TEST(const volatile int, const          float[2], const volatile int);

BKSGE_COPY_CV_TEST(               int,       volatile float[2],       volatile int);
BKSGE_COPY_CV_TEST(const          int,       volatile float[2], const volatile int);
BKSGE_COPY_CV_TEST(      volatile int,       volatile float[2],       volatile int);
BKSGE_COPY_CV_TEST(const volatile int,       volatile float[2], const volatile int);

BKSGE_COPY_CV_TEST(               int, const volatile float[2], const volatile int);
BKSGE_COPY_CV_TEST(const          int, const volatile float[2], const volatile int);
BKSGE_COPY_CV_TEST(      volatile int, const volatile float[2], const volatile int);
BKSGE_COPY_CV_TEST(const volatile int, const volatile float[2], const volatile int);

BKSGE_COPY_CV_TEST(               int,                float[],                int);
BKSGE_COPY_CV_TEST(const          int,                float[], const          int);
BKSGE_COPY_CV_TEST(      volatile int,                float[],       volatile int);
BKSGE_COPY_CV_TEST(const volatile int,                float[], const volatile int);

BKSGE_COPY_CV_TEST(               int, const          float[], const          int);
BKSGE_COPY_CV_TEST(const          int, const          float[], const          int);
BKSGE_COPY_CV_TEST(      volatile int, const          float[], const volatile int);
BKSGE_COPY_CV_TEST(const volatile int, const          float[], const volatile int);

BKSGE_COPY_CV_TEST(               int,       volatile float[],       volatile int);
BKSGE_COPY_CV_TEST(const          int,       volatile float[], const volatile int);
BKSGE_COPY_CV_TEST(      volatile int,       volatile float[],       volatile int);
BKSGE_COPY_CV_TEST(const volatile int,       volatile float[], const volatile int);

BKSGE_COPY_CV_TEST(               int, const volatile float[], const volatile int);
BKSGE_COPY_CV_TEST(const          int, const volatile float[], const volatile int);
BKSGE_COPY_CV_TEST(      volatile int, const volatile float[], const volatile int);
BKSGE_COPY_CV_TEST(const volatile int, const volatile float[], const volatile int);

BKSGE_COPY_CV_TEST(               int[2],                void,                int[2]);
BKSGE_COPY_CV_TEST(const          int[2],                void, const          int[2]);
BKSGE_COPY_CV_TEST(      volatile int[2],                void,       volatile int[2]);
BKSGE_COPY_CV_TEST(const volatile int[2],                void, const volatile int[2]);

BKSGE_COPY_CV_TEST(               int[2], const          void, const          int[2]);
BKSGE_COPY_CV_TEST(const          int[2], const          void, const          int[2]);
BKSGE_COPY_CV_TEST(      volatile int[2], const          void, const volatile int[2]);
BKSGE_COPY_CV_TEST(const volatile int[2], const          void, const volatile int[2]);

BKSGE_COPY_CV_TEST(               int[2],       volatile void,       volatile int[2]);
BKSGE_COPY_CV_TEST(const          int[2],       volatile void, const volatile int[2]);
BKSGE_COPY_CV_TEST(      volatile int[2],       volatile void,       volatile int[2]);
BKSGE_COPY_CV_TEST(const volatile int[2],       volatile void, const volatile int[2]);

BKSGE_COPY_CV_TEST(               int[2], const volatile void, const volatile int[2]);
BKSGE_COPY_CV_TEST(const          int[2], const volatile void, const volatile int[2]);
BKSGE_COPY_CV_TEST(      volatile int[2], const volatile void, const volatile int[2]);
BKSGE_COPY_CV_TEST(const volatile int[2], const volatile void, const volatile int[2]);

BKSGE_COPY_CV_TEST(               int[],                float,                int[]);
BKSGE_COPY_CV_TEST(const          int[],                float, const          int[]);
BKSGE_COPY_CV_TEST(      volatile int[],                float,       volatile int[]);
BKSGE_COPY_CV_TEST(const volatile int[],                float, const volatile int[]);

BKSGE_COPY_CV_TEST(               int[], const          float, const          int[]);
BKSGE_COPY_CV_TEST(const          int[], const          float, const          int[]);
BKSGE_COPY_CV_TEST(      volatile int[], const          float, const volatile int[]);
BKSGE_COPY_CV_TEST(const volatile int[], const          float, const volatile int[]);

BKSGE_COPY_CV_TEST(               int[],       volatile float,       volatile int[]);
BKSGE_COPY_CV_TEST(const          int[],       volatile float, const volatile int[]);
BKSGE_COPY_CV_TEST(      volatile int[],       volatile float,       volatile int[]);
BKSGE_COPY_CV_TEST(const volatile int[],       volatile float, const volatile int[]);

BKSGE_COPY_CV_TEST(               int[], const volatile float, const volatile int[]);
BKSGE_COPY_CV_TEST(const          int[], const volatile float, const volatile int[]);
BKSGE_COPY_CV_TEST(      volatile int[], const volatile float, const volatile int[]);
BKSGE_COPY_CV_TEST(const volatile int[], const volatile float, const volatile int[]);

BKSGE_COPY_CV_TEST(int,                int*,       int);
BKSGE_COPY_CV_TEST(int, const          int*,       int);
BKSGE_COPY_CV_TEST(int,       volatile int*,       int);
BKSGE_COPY_CV_TEST(int, const volatile int*,       int);
BKSGE_COPY_CV_TEST(int,                int&,       int);
BKSGE_COPY_CV_TEST(int, const          int&,       int);
BKSGE_COPY_CV_TEST(int,       volatile int&,       int);
BKSGE_COPY_CV_TEST(int, const volatile int&,       int);
BKSGE_COPY_CV_TEST(int,                int&&,      int);
BKSGE_COPY_CV_TEST(int, const          int&&,      int);
BKSGE_COPY_CV_TEST(int,       volatile int&&,      int);
BKSGE_COPY_CV_TEST(int, const volatile int&&,      int);
BKSGE_COPY_CV_TEST(int,                int(&)[2],  int);
BKSGE_COPY_CV_TEST(int, const          int(&)[2],  int);
BKSGE_COPY_CV_TEST(int,       volatile int(&)[2],  int);
BKSGE_COPY_CV_TEST(int, const volatile int(&)[2],  int);
BKSGE_COPY_CV_TEST(int,                int(&)[],   int);
BKSGE_COPY_CV_TEST(int, const          int(&)[],   int);
BKSGE_COPY_CV_TEST(int,       volatile int(&)[],   int);
BKSGE_COPY_CV_TEST(int, const volatile int(&)[],   int);
BKSGE_COPY_CV_TEST(int,                int(&&)[2], int);
BKSGE_COPY_CV_TEST(int, const          int(&&)[2], int);
BKSGE_COPY_CV_TEST(int,       volatile int(&&)[2], int);
BKSGE_COPY_CV_TEST(int, const volatile int(&&)[2], int);
BKSGE_COPY_CV_TEST(int,                int(&&)[],  int);
BKSGE_COPY_CV_TEST(int, const          int(&&)[],  int);
BKSGE_COPY_CV_TEST(int,       volatile int(&&)[],  int);
BKSGE_COPY_CV_TEST(int, const volatile int(&&)[],  int);
BKSGE_COPY_CV_TEST(int,                int(*)[2],  int);
BKSGE_COPY_CV_TEST(int, const          int(*)[2],  int);
BKSGE_COPY_CV_TEST(int,       volatile int(*)[2],  int);
BKSGE_COPY_CV_TEST(int, const volatile int(*)[2],  int);
BKSGE_COPY_CV_TEST(int,                int(*)[],   int);
BKSGE_COPY_CV_TEST(int, const          int(*)[],   int);
BKSGE_COPY_CV_TEST(int,       volatile int(*)[],   int);
BKSGE_COPY_CV_TEST(int, const volatile int(*)[],   int);

// 参照の時は変化しない
BKSGE_COPY_CV_TEST(               int&,                void, int               &);
BKSGE_COPY_CV_TEST(const          int&,                void, int const         &);
BKSGE_COPY_CV_TEST(      volatile int&,                void, int       volatile&);
BKSGE_COPY_CV_TEST(const volatile int&,                void, int const volatile&);

BKSGE_COPY_CV_TEST(               int&, const          void, int               &);
BKSGE_COPY_CV_TEST(const          int&, const          void, int const         &);
BKSGE_COPY_CV_TEST(      volatile int&, const          void, int       volatile&);
BKSGE_COPY_CV_TEST(const volatile int&, const          void, int const volatile&);

BKSGE_COPY_CV_TEST(               int&,       volatile void, int               &);
BKSGE_COPY_CV_TEST(const          int&,       volatile void, int const         &);
BKSGE_COPY_CV_TEST(      volatile int&,       volatile void, int       volatile&);
BKSGE_COPY_CV_TEST(const volatile int&,       volatile void, int const volatile&);

BKSGE_COPY_CV_TEST(               int&, const volatile void, int               &);
BKSGE_COPY_CV_TEST(const          int&, const volatile void, int const         &);
BKSGE_COPY_CV_TEST(      volatile int&, const volatile void, int       volatile&);
BKSGE_COPY_CV_TEST(const volatile int&, const volatile void, int const volatile&);

BKSGE_COPY_CV_TEST(               int(&)[2],                void, int               (&)[2]);
BKSGE_COPY_CV_TEST(const          int(&)[2],                void, int const         (&)[2]);
BKSGE_COPY_CV_TEST(      volatile int(&)[2],                void, int       volatile(&)[2]);
BKSGE_COPY_CV_TEST(const volatile int(&)[2],                void, int const volatile(&)[2]);

BKSGE_COPY_CV_TEST(               int(&)[2], const          void, int               (&)[2]);
BKSGE_COPY_CV_TEST(const          int(&)[2], const          void, int const         (&)[2]);
BKSGE_COPY_CV_TEST(      volatile int(&)[2], const          void, int       volatile(&)[2]);
BKSGE_COPY_CV_TEST(const volatile int(&)[2], const          void, int const volatile(&)[2]);

BKSGE_COPY_CV_TEST(               int(&)[2],       volatile void, int               (&)[2]);
BKSGE_COPY_CV_TEST(const          int(&)[2],       volatile void, int const         (&)[2]);
BKSGE_COPY_CV_TEST(      volatile int(&)[2],       volatile void, int       volatile(&)[2]);
BKSGE_COPY_CV_TEST(const volatile int(&)[2],       volatile void, int const volatile(&)[2]);

BKSGE_COPY_CV_TEST(               int(&)[2], const volatile void, int               (&)[2]);
BKSGE_COPY_CV_TEST(const          int(&)[2], const volatile void, int const         (&)[2]);
BKSGE_COPY_CV_TEST(      volatile int(&)[2], const volatile void, int       volatile(&)[2]);
BKSGE_COPY_CV_TEST(const volatile int(&)[2], const volatile void, int const volatile(&)[2]);

BKSGE_COPY_CV_TEST(               int(&)[],                void, int               (&)[]);
BKSGE_COPY_CV_TEST(const          int(&)[],                void, int const         (&)[]);
BKSGE_COPY_CV_TEST(      volatile int(&)[],                void, int       volatile(&)[]);
BKSGE_COPY_CV_TEST(const volatile int(&)[],                void, int const volatile(&)[]);

BKSGE_COPY_CV_TEST(               int(&)[], const          void, int               (&)[]);
BKSGE_COPY_CV_TEST(const          int(&)[], const          void, int const         (&)[]);
BKSGE_COPY_CV_TEST(      volatile int(&)[], const          void, int       volatile(&)[]);
BKSGE_COPY_CV_TEST(const volatile int(&)[], const          void, int const volatile(&)[]);

BKSGE_COPY_CV_TEST(               int(&)[],       volatile void, int               (&)[]);
BKSGE_COPY_CV_TEST(const          int(&)[],       volatile void, int const         (&)[]);
BKSGE_COPY_CV_TEST(      volatile int(&)[],       volatile void, int       volatile(&)[]);
BKSGE_COPY_CV_TEST(const volatile int(&)[],       volatile void, int const volatile(&)[]);

BKSGE_COPY_CV_TEST(               int(&)[], const volatile void, int               (&)[]);
BKSGE_COPY_CV_TEST(const          int(&)[], const volatile void, int const         (&)[]);
BKSGE_COPY_CV_TEST(      volatile int(&)[], const volatile void, int       volatile(&)[]);
BKSGE_COPY_CV_TEST(const volatile int(&)[], const volatile void, int const volatile(&)[]);

BKSGE_COPY_CV_TEST(               int&&,                void, int               &&);
BKSGE_COPY_CV_TEST(const          int&&,                void, int const         &&);
BKSGE_COPY_CV_TEST(      volatile int&&,                void, int       volatile&&);
BKSGE_COPY_CV_TEST(const volatile int&&,                void, int const volatile&&);

BKSGE_COPY_CV_TEST(               int&&, const          void, int               &&);
BKSGE_COPY_CV_TEST(const          int&&, const          void, int const         &&);
BKSGE_COPY_CV_TEST(      volatile int&&, const          void, int       volatile&&);
BKSGE_COPY_CV_TEST(const volatile int&&, const          void, int const volatile&&);

BKSGE_COPY_CV_TEST(               int&&,       volatile void, int               &&);
BKSGE_COPY_CV_TEST(const          int&&,       volatile void, int const         &&);
BKSGE_COPY_CV_TEST(      volatile int&&,       volatile void, int       volatile&&);
BKSGE_COPY_CV_TEST(const volatile int&&,       volatile void, int const volatile&&);

BKSGE_COPY_CV_TEST(               int&&, const volatile void, int               &&);
BKSGE_COPY_CV_TEST(const          int&&, const volatile void, int const         &&);
BKSGE_COPY_CV_TEST(      volatile int&&, const volatile void, int       volatile&&);
BKSGE_COPY_CV_TEST(const volatile int&&, const volatile void, int const volatile&&);

BKSGE_COPY_CV_TEST(               int(&&)[2],                void, int               (&&)[2]);
BKSGE_COPY_CV_TEST(const          int(&&)[2],                void, int const         (&&)[2]);
BKSGE_COPY_CV_TEST(      volatile int(&&)[2],                void, int       volatile(&&)[2]);
BKSGE_COPY_CV_TEST(const volatile int(&&)[2],                void, int const volatile(&&)[2]);

BKSGE_COPY_CV_TEST(               int(&&)[2], const          void, int               (&&)[2]);
BKSGE_COPY_CV_TEST(const          int(&&)[2], const          void, int const         (&&)[2]);
BKSGE_COPY_CV_TEST(      volatile int(&&)[2], const          void, int       volatile(&&)[2]);
BKSGE_COPY_CV_TEST(const volatile int(&&)[2], const          void, int const volatile(&&)[2]);

BKSGE_COPY_CV_TEST(               int(&&)[2],       volatile void, int               (&&)[2]);
BKSGE_COPY_CV_TEST(const          int(&&)[2],       volatile void, int const         (&&)[2]);
BKSGE_COPY_CV_TEST(      volatile int(&&)[2],       volatile void, int       volatile(&&)[2]);
BKSGE_COPY_CV_TEST(const volatile int(&&)[2],       volatile void, int const volatile(&&)[2]);

BKSGE_COPY_CV_TEST(               int(&&)[2], const volatile void, int               (&&)[2]);
BKSGE_COPY_CV_TEST(const          int(&&)[2], const volatile void, int const         (&&)[2]);
BKSGE_COPY_CV_TEST(      volatile int(&&)[2], const volatile void, int       volatile(&&)[2]);
BKSGE_COPY_CV_TEST(const volatile int(&&)[2], const volatile void, int const volatile(&&)[2]);

BKSGE_COPY_CV_TEST(               int(&&)[],                void, int               (&&)[]);
BKSGE_COPY_CV_TEST(const          int(&&)[],                void, int const         (&&)[]);
BKSGE_COPY_CV_TEST(      volatile int(&&)[],                void, int       volatile(&&)[]);
BKSGE_COPY_CV_TEST(const volatile int(&&)[],                void, int const volatile(&&)[]);

BKSGE_COPY_CV_TEST(               int(&&)[], const          void, int               (&&)[]);
BKSGE_COPY_CV_TEST(const          int(&&)[], const          void, int const         (&&)[]);
BKSGE_COPY_CV_TEST(      volatile int(&&)[], const          void, int       volatile(&&)[]);
BKSGE_COPY_CV_TEST(const volatile int(&&)[], const          void, int const volatile(&&)[]);

BKSGE_COPY_CV_TEST(               int(&&)[],       volatile void, int               (&&)[]);
BKSGE_COPY_CV_TEST(const          int(&&)[],       volatile void, int const         (&&)[]);
BKSGE_COPY_CV_TEST(      volatile int(&&)[],       volatile void, int       volatile(&&)[]);
BKSGE_COPY_CV_TEST(const volatile int(&&)[],       volatile void, int const volatile(&&)[]);

BKSGE_COPY_CV_TEST(               int(&&)[], const volatile void, int               (&&)[]);
BKSGE_COPY_CV_TEST(const          int(&&)[], const volatile void, int const         (&&)[]);
BKSGE_COPY_CV_TEST(      volatile int(&&)[], const volatile void, int       volatile(&&)[]);
BKSGE_COPY_CV_TEST(const volatile int(&&)[], const volatile void, int const volatile(&&)[]);

// ポインタの時 cv修飾が付く位置に注意
BKSGE_COPY_CV_TEST(               int*,                void,                int*);
BKSGE_COPY_CV_TEST(const          int*,                void, const          int*);
BKSGE_COPY_CV_TEST(      volatile int*,                void,       volatile int*);
BKSGE_COPY_CV_TEST(const volatile int*,                void, const volatile int*);

BKSGE_COPY_CV_TEST(               int*, const          void,                int* const);
BKSGE_COPY_CV_TEST(const          int*, const          void, const          int* const);
BKSGE_COPY_CV_TEST(      volatile int*, const          void,       volatile int* const);
BKSGE_COPY_CV_TEST(const volatile int*, const          void, const volatile int* const);

BKSGE_COPY_CV_TEST(               int*,       volatile void,                int* volatile);
BKSGE_COPY_CV_TEST(const          int*,       volatile void, const          int* volatile);
BKSGE_COPY_CV_TEST(      volatile int*,       volatile void,       volatile int* volatile);
BKSGE_COPY_CV_TEST(const volatile int*,       volatile void, const volatile int* volatile);

BKSGE_COPY_CV_TEST(               int*, const volatile void,                int* const volatile);
BKSGE_COPY_CV_TEST(const          int*, const volatile void, const          int* const volatile);
BKSGE_COPY_CV_TEST(      volatile int*, const volatile void,       volatile int* const volatile);
BKSGE_COPY_CV_TEST(const volatile int*, const volatile void, const volatile int* const volatile);

BKSGE_COPY_CV_TEST(               int(*)[2],                void,                int(*)[2]);
BKSGE_COPY_CV_TEST(const          int(*)[2],                void, const          int(*)[2]);
BKSGE_COPY_CV_TEST(      volatile int(*)[2],                void,       volatile int(*)[2]);
BKSGE_COPY_CV_TEST(const volatile int(*)[2],                void, const volatile int(*)[2]);

BKSGE_COPY_CV_TEST(               int(*)[2], const          void,                int(* const)[2]);
BKSGE_COPY_CV_TEST(const          int(*)[2], const          void, const          int(* const)[2]);
BKSGE_COPY_CV_TEST(      volatile int(*)[2], const          void,       volatile int(* const)[2]);
BKSGE_COPY_CV_TEST(const volatile int(*)[2], const          void, const volatile int(* const)[2]);

BKSGE_COPY_CV_TEST(               int(*)[2],       volatile void,                int(* volatile)[2]);
BKSGE_COPY_CV_TEST(const          int(*)[2],       volatile void, const          int(* volatile)[2]);
BKSGE_COPY_CV_TEST(      volatile int(*)[2],       volatile void,       volatile int(* volatile)[2]);
BKSGE_COPY_CV_TEST(const volatile int(*)[2],       volatile void, const volatile int(* volatile)[2]);

BKSGE_COPY_CV_TEST(               int(*)[2], const volatile void,                int(* const volatile)[2]);
BKSGE_COPY_CV_TEST(const          int(*)[2], const volatile void, const          int(* const volatile)[2]);
BKSGE_COPY_CV_TEST(      volatile int(*)[2], const volatile void,       volatile int(* const volatile)[2]);
BKSGE_COPY_CV_TEST(const volatile int(*)[2], const volatile void, const volatile int(* const volatile)[2]);

BKSGE_COPY_CV_TEST(               int(*)[],                void,                int(*)[]);
BKSGE_COPY_CV_TEST(const          int(*)[],                void, const          int(*)[]);
BKSGE_COPY_CV_TEST(      volatile int(*)[],                void,       volatile int(*)[]);
BKSGE_COPY_CV_TEST(const volatile int(*)[],                void, const volatile int(*)[]);

BKSGE_COPY_CV_TEST(               int(*)[], const          void,                int(* const)[]);
BKSGE_COPY_CV_TEST(const          int(*)[], const          void, const          int(* const)[]);
BKSGE_COPY_CV_TEST(      volatile int(*)[], const          void,       volatile int(* const)[]);
BKSGE_COPY_CV_TEST(const volatile int(*)[], const          void, const volatile int(* const)[]);

BKSGE_COPY_CV_TEST(               int(*)[],       volatile void,                int(* volatile)[]);
BKSGE_COPY_CV_TEST(const          int(*)[],       volatile void, const          int(* volatile)[]);
BKSGE_COPY_CV_TEST(      volatile int(*)[],       volatile void,       volatile int(* volatile)[]);
BKSGE_COPY_CV_TEST(const volatile int(*)[],       volatile void, const volatile int(* volatile)[]);

BKSGE_COPY_CV_TEST(               int(*)[], const volatile void,                int(* const volatile)[]);
BKSGE_COPY_CV_TEST(const          int(*)[], const volatile void, const          int(* const volatile)[]);
BKSGE_COPY_CV_TEST(      volatile int(*)[], const volatile void,       volatile int(* const volatile)[]);
BKSGE_COPY_CV_TEST(const volatile int(*)[], const volatile void, const volatile int(* const volatile)[]);

#undef BKSGE_COPY_CV_TEST
