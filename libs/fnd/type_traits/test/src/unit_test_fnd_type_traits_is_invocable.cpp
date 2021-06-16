/**
 *	@file	unit_test_fnd_type_traits_is_invocable.cpp
 *
 *	@brief	is_invocable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_invocable.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_INVOCABLE_TEST(b, ...)	\
	static_assert(bksge::is_invocable_v<__VA_ARGS__>      == b, "");	\
	static_assert(bksge::is_invocable<__VA_ARGS__>::value == b, "");	\
	static_assert(bksge::is_invocable<__VA_ARGS__>()      == b, "")

#else

#define BKSGE_IS_INVOCABLE_TEST(b, ...)	\
	static_assert(bksge::is_invocable<__VA_ARGS__>::value == b, "");	\
	static_assert(bksge::is_invocable<__VA_ARGS__>()      == b, "")

#endif

namespace bksge_type_traits_test
{

namespace is_invocable_test
{

using func_type_v0 = void(*)();

BKSGE_IS_INVOCABLE_TEST(true,  func_type_v0);
BKSGE_IS_INVOCABLE_TEST(false, func_type_v0, int);

using func_type_i0 = int(*)();

BKSGE_IS_INVOCABLE_TEST(true,  func_type_i0);
BKSGE_IS_INVOCABLE_TEST(false, func_type_i0, int);

using func_type_l0 = int&(*)();

BKSGE_IS_INVOCABLE_TEST(true,  func_type_l0);
BKSGE_IS_INVOCABLE_TEST(false, func_type_l0, int);

using func_type_ii = int(*)(int);

BKSGE_IS_INVOCABLE_TEST(false, func_type_ii);
BKSGE_IS_INVOCABLE_TEST(true,  func_type_ii, int);

using func_type_il = int(*)(int&);

BKSGE_IS_INVOCABLE_TEST(false, func_type_il);
BKSGE_IS_INVOCABLE_TEST(false, func_type_il, int);
BKSGE_IS_INVOCABLE_TEST(true,  func_type_il, int&);

using func_type_ir = int(*)(int&&);

BKSGE_IS_INVOCABLE_TEST(false, func_type_ir);
BKSGE_IS_INVOCABLE_TEST(true,  func_type_ir, int);
BKSGE_IS_INVOCABLE_TEST(false, func_type_ir, int&);

struct X {};
struct Y : X {};

using mem_type_i = int X::*;

BKSGE_IS_INVOCABLE_TEST(false, mem_type_i);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_i, int);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_i, int*);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_i, int&);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_i, int*&);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_i, int&&);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_i, int*&&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X               );
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X const         );
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X       volatile);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X const volatile);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X               *);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X const         *);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X       volatile*);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X const volatile*);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X               &);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X const         &);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X       volatile&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X const volatile&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X               *&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X const         *&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X       volatile*&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X const volatile*&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X               &&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X const         &&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X       volatile&&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X const volatile&&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X               *&&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X const         *&&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X       volatile*&&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, X const volatile*&&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y               );
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y const         );
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y       volatile);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y const volatile);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y               *);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y const         *);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y       volatile*);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y const volatile*);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y               &);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y const         &);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y       volatile&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y const volatile&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y               *&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y const         *&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y       volatile*&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y const volatile*&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y               &&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y const         &&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y       volatile&&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y const volatile&&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y               *&&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y const         *&&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y       volatile*&&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_i, Y const volatile*&&);

using mem_type_f = float Y::*;

BKSGE_IS_INVOCABLE_TEST(false, mem_type_f);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, float);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, float*);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, float&);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, float*&);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, float&&);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, float*&&);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X               );
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X const         );
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X       volatile);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X const volatile);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X               *);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X const         *);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X       volatile*);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X const volatile*);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X               &);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X const         &);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X       volatile&);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X const volatile&);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X               *&);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X const         *&);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X       volatile*&);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X const volatile*&);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X               &&);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X const         &&);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X       volatile&&);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X const volatile&&);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X               *&&);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X const         *&&);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X       volatile*&&);
BKSGE_IS_INVOCABLE_TEST(false, mem_type_f, X const volatile*&&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y               );
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y const         );
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y       volatile);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y const volatile);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y               *);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y const         *);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y       volatile*);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y const volatile*);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y               &);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y const         &);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y       volatile&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y const volatile&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y               *&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y const         *&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y       volatile*&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y const volatile*&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y               &&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y const         &&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y       volatile&&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y const volatile&&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y               *&&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y const         *&&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y       volatile*&&);
BKSGE_IS_INVOCABLE_TEST(true,  mem_type_f, Y const volatile*&&);

using memfun_type_i = int (X::*)();

BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i, int&);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_i,                X);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i, const          X);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i,       volatile X);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i, const volatile X);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_i,                X*);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i, const          X*);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i,       volatile X*);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i, const volatile X*);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_i,                X* const         );
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_i,                X*       volatile);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_i,                X* const volatile);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_i,                X&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i, const          X&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i,       volatile X&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i, const volatile X&);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_i,                X*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i, const          X*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i,       volatile X*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i, const volatile X*&);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_i,                X&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i, const          X&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i,       volatile X&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i, const volatile X&&);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_i,                X*&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i, const          X*&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i,       volatile X*&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i, const volatile X*&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i,                X,  int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i, const          X,  int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i,       volatile X,  int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i, const volatile X,  int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i,                X&, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i, const          X&, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i,       volatile X&, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i, const volatile X&, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i,                X*, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i, const          X*, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i,       volatile X*, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_i, const volatile X*, int);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_i, Y);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_i, Y*);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_i, Y&);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_i, Y*&);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_i, Y&&);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_i, Y*&&);

using memfun_type_f = float (Y::*)();

BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_f, Y);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_f, Y*);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_f, Y&);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_f, Y*&);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_f, Y&&);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_f, Y*&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_f, X);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_f, X*);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_f, X&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_f, X*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_f, X&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_f, X*&&);

using memfun_type_iic = int (X::*)(int&) const;

BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, int*);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, int&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, int*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, int&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, int*&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               , int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               , int*);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_iic, X               , int               &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               , int const         &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               , int       volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               , int const volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               , int*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               , int&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         , int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         , int*);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_iic, X const         , int               &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         , int const         &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         , int       volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         , int const volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         , int*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         , int&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile, int*);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile, int               &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile, int const         &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile, int       volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile, int const volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile, int*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile, int&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile, int*);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile, int               &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile, int const         &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile, int       volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile, int const volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile, int*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile, int&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               *, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               *, int*);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_iic, X               *, int               &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               *, int const         &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               *, int       volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               *, int const volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               *, int*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               *, int&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         *, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         *, int*);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_iic, X const         *, int               &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         *, int const         &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         *, int       volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         *, int const volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         *, int*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         *, int&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile*, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile*, int*);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile*, int               &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile*, int const         &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile*, int       volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile*, int const volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile*, int*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile*, int&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile*, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile*, int*);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile*, int               &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile*, int const         &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile*, int       volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile*, int const volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile*, int*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile*, int&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &, int*);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_iic, X               &, int               &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &, int const         &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &, int       volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &, int const volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &, int*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &, int&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &, int*);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_iic, X const         &, int               &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &, int const         &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &, int       volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &, int const volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &, int*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &, int&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&, int*);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&, int               &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&, int const         &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&, int       volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&, int const volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&, int*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&, int&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&, int*);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&, int               &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&, int const         &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&, int       volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&, int const volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&, int*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&, int&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &&, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &&, int*);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_iic, X               &&, int               &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &&, int const         &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &&, int       volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &&, int const volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &&, int*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &&, int&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &&, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &&, int*);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_iic, X const         &&, int               &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &&, int const         &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &&, int       volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &&, int const volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &&, int*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &&, int&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&&, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&&, int*);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&&, int               &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&&, int const         &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&&, int       volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&&, int const volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&&, int*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&&, int&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&&, int);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&&, int*);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&&, int               &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&&, int const         &);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&&, int       volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&&, int const volatile&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&&, int*&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&&, int&&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X, float&);
BKSGE_IS_INVOCABLE_TEST(false, memfun_type_iic, X, int&, int);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_iic, Y, int&);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_iic, Y*, int&);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_iic, Y&, int&);
BKSGE_IS_INVOCABLE_TEST(true,  memfun_type_iic, Y&&, int&);

struct F
{
	int operator()();
	int operator()(int);
	int operator()(float);
private:
	void operator()(int, int);
};

BKSGE_IS_INVOCABLE_TEST(true,  F);
BKSGE_IS_INVOCABLE_TEST(true,  F, int);
BKSGE_IS_INVOCABLE_TEST(true,  F, float);
BKSGE_IS_INVOCABLE_TEST(false, F, int, int);

}	// namespace is_invocable_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_INVOCABLE_TEST
