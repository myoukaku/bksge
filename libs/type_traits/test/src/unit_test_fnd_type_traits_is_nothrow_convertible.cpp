/**
 *	@file	unit_test_fnd_type_traits_is_nothrow_convertible.cpp
 *
 *	@brief	is_nothrow_convertible のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_nothrow_convertible.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

namespace bksge_type_traits_test
{

namespace is_nothrow_convertible_test
{

struct A {};

struct B
{
	operator A() { return a; } A a;
};

struct C
{
	operator A() noexcept { return a; } A a;
};

struct D
{
	D(A const&) {}
};

struct E
{
	E(A const&) noexcept {}
};

struct F
{
	explicit F(A const&) noexcept {}
};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(b, From, To)	\
	static_assert(bksge::is_nothrow_convertible_v<From, To>      == b, #From ", " #To);	\
	static_assert(bksge::is_nothrow_convertible<From, To>::value == b, #From ", " #To);	\
	static_assert(bksge::is_nothrow_convertible<From, To>()      == b, #From ", " #To)

#else

#define BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(b, From, To)	\
	static_assert(bksge::is_nothrow_convertible<From, To>::value == b, #From ", " #To);	\
	static_assert(bksge::is_nothrow_convertible<From, To>()      == b, #From ", " #To)

#endif

BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true,  int, int);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true,  int, double);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true,  int, char);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(false, int, void);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(false, int, int*);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(false, int, int[]);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(false, int[], int[]);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(false, int, int[3]);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(false, int[3], int[3]);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true,  int const, int);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true,  int* const, int*);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(false, int const*, int*);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(false, int*, int);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(false, int*, char*);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true,  int*, void*);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true,  int&, int);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true,  int const&, int);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true,  int&, long);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true,  int const&, long);

BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true,                void,                void);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true,                void, const          void);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true,                void,       volatile void);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true,                void, const volatile void);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true, const          void,                void);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true, const          void, const          void);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true, const          void,       volatile void);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true, const          void, const volatile void);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true,       volatile void,                void);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true,       volatile void, const          void);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true,       volatile void,       volatile void);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true,       volatile void, const volatile void);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true, const volatile void,                void);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true, const volatile void, const          void);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true, const volatile void,       volatile void);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true, const volatile void, const volatile void);

BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(false, A, B);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(false, B, A);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(false, A, C);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true,  C, A);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(false, A, D);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(false, D, A);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(true,  A, E);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(false, E, A);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(false, A, F);
BKSGE_IS_NOTHROW_CONVERTIBLE_TEST(false, F, A);

#undef BKSGE_IS_NOTHROW_CONVERTIBLE_TEST

}	// namespace is_nothrow_convertible_test

}	// namespace bksge_type_traits_test
