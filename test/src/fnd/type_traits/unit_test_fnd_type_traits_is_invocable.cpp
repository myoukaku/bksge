/**
 *	@file	unit_test_fnd_type_traits_is_invocable.cpp
 *
 *	@brief	is_invocable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_invocable.hpp>
#include <gtest/gtest.h>

namespace bksge_type_traits_test
{

namespace is_invocable_test
{

GTEST_TEST(TypeTraitsTest, IsInvocableTest)
{
	using func_type_v0 = void(*)();

	static_assert( bksge::is_invocable<func_type_v0>::value, "");
	static_assert(!bksge::is_invocable<func_type_v0, int>::value, "");

	using func_type_i0 = int(*)();

	static_assert( bksge::is_invocable<func_type_i0>::value, "");
	static_assert(!bksge::is_invocable<func_type_i0, int>::value, "");

	using func_type_l0 = int&(*)();

	static_assert( bksge::is_invocable<func_type_l0>::value, "");
	static_assert(!bksge::is_invocable<func_type_l0, int>::value, "");

	using func_type_ii = int(*)(int);

	static_assert(!bksge::is_invocable<func_type_ii>::value, "");
	static_assert( bksge::is_invocable<func_type_ii, int>::value, "");

	using func_type_il = int(*)(int&);

	static_assert(!bksge::is_invocable<func_type_il>::value, "");
	static_assert(!bksge::is_invocable<func_type_il, int>::value, "");
	static_assert( bksge::is_invocable<func_type_il, int&>::value, "");

	using func_type_ir = int(*)(int&&);

	static_assert(!bksge::is_invocable<func_type_ir>::value, "");
	static_assert( bksge::is_invocable<func_type_ir, int>::value, "");
	static_assert(!bksge::is_invocable<func_type_ir, int&>::value, "");

	struct X {};
	struct Y : X {};

	using mem_type_i = int X::*;

	static_assert(!bksge::is_invocable<mem_type_i>::value, "");
	static_assert(!bksge::is_invocable<mem_type_i, int>::value, "");
	static_assert(!bksge::is_invocable<mem_type_i, int*>::value, "");
	static_assert(!bksge::is_invocable<mem_type_i, int&>::value, "");
	static_assert(!bksge::is_invocable<mem_type_i, int*&>::value, "");
	static_assert(!bksge::is_invocable<mem_type_i, int&&>::value, "");
	static_assert(!bksge::is_invocable<mem_type_i, int*&&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X               >::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X const         >::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X       volatile>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X const volatile>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X               *>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X const         *>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X       volatile*>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X const volatile*>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X               &>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X const         &>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X       volatile&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X const volatile&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X               *&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X const         *&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X       volatile*&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X const volatile*&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X               &&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X const         &&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X       volatile&&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X const volatile&&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X               *&&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X const         *&&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X       volatile*&&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, X const volatile*&&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y               >::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y const         >::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y       volatile>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y const volatile>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y               *>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y const         *>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y       volatile*>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y const volatile*>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y               &>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y const         &>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y       volatile&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y const volatile&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y               *&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y const         *&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y       volatile*&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y const volatile*&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y               &&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y const         &&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y       volatile&&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y const volatile&&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y               *&&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y const         *&&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y       volatile*&&>::value, "");
	static_assert( bksge::is_invocable<mem_type_i, Y const volatile*&&>::value, "");

	using mem_type_f = float Y::*;

	static_assert(!bksge::is_invocable<mem_type_f>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, float>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, float*>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, float&>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, float*&>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, float&&>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, float*&&>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X               >::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X const         >::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X       volatile>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X const volatile>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X               *>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X const         *>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X       volatile*>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X const volatile*>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X               &>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X const         &>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X       volatile&>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X const volatile&>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X               *&>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X const         *&>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X       volatile*&>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X const volatile*&>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X               &&>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X const         &&>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X       volatile&&>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X const volatile&&>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X               *&&>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X const         *&&>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X       volatile*&&>::value, "");
	static_assert(!bksge::is_invocable<mem_type_f, X const volatile*&&>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y               >::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y const         >::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y       volatile>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y const volatile>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y               *>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y const         *>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y       volatile*>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y const volatile*>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y               &>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y const         &>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y       volatile&>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y const volatile&>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y               *&>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y const         *&>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y       volatile*&>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y const volatile*&>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y               &&>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y const         &&>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y       volatile&&>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y const volatile&&>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y               *&&>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y const         *&&>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y       volatile*&&>::value, "");
	static_assert( bksge::is_invocable<mem_type_f, Y const volatile*&&>::value, "");

	using memfun_type_i = int (X::*)();

	static_assert(!bksge::is_invocable<memfun_type_i>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i, int&>::value, "");
	static_assert( bksge::is_invocable<memfun_type_i,                X>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i, const          X>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i,       volatile X>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i, const volatile X>::value, "");
	static_assert( bksge::is_invocable<memfun_type_i,                X*>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i, const          X*>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i,       volatile X*>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i, const volatile X*>::value, "");
	static_assert( bksge::is_invocable<memfun_type_i,                X* const         >::value, "");
	static_assert( bksge::is_invocable<memfun_type_i,                X*       volatile>::value, "");
	static_assert( bksge::is_invocable<memfun_type_i,                X* const volatile>::value, "");
	static_assert( bksge::is_invocable<memfun_type_i,                X&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i, const          X&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i,       volatile X&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i, const volatile X&>::value, "");
	static_assert( bksge::is_invocable<memfun_type_i,                X*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i, const          X*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i,       volatile X*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i, const volatile X*&>::value, "");
	static_assert( bksge::is_invocable<memfun_type_i,                X&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i, const          X&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i,       volatile X&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i, const volatile X&&>::value, "");
	static_assert( bksge::is_invocable<memfun_type_i,                X*&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i, const          X*&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i,       volatile X*&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i, const volatile X*&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i,                X,  int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i, const          X,  int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i,       volatile X,  int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i, const volatile X,  int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i,                X&, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i, const          X&, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i,       volatile X&, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i, const volatile X&, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i,                X*, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i, const          X*, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i,       volatile X*, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_i, const volatile X*, int>::value, "");
	static_assert( bksge::is_invocable<memfun_type_i, Y>::value, "");
	static_assert( bksge::is_invocable<memfun_type_i, Y*>::value, "");
	static_assert( bksge::is_invocable<memfun_type_i, Y&>::value, "");
	static_assert( bksge::is_invocable<memfun_type_i, Y*&>::value, "");
	static_assert( bksge::is_invocable<memfun_type_i, Y&&>::value, "");
	static_assert( bksge::is_invocable<memfun_type_i, Y*&&>::value, "");

	using memfun_type_f = float (Y::*)();

	static_assert( bksge::is_invocable<memfun_type_f, Y>::value, "");
	static_assert( bksge::is_invocable<memfun_type_f, Y*>::value, "");
	static_assert( bksge::is_invocable<memfun_type_f, Y&>::value, "");
	static_assert( bksge::is_invocable<memfun_type_f, Y*&>::value, "");
	static_assert( bksge::is_invocable<memfun_type_f, Y&&>::value, "");
	static_assert( bksge::is_invocable<memfun_type_f, Y*&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_f, X>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_f, X*>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_f, X&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_f, X*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_f, X&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_f, X*&&>::value, "");

	using memfun_type_iic = int (X::*)(int&) const;

	static_assert(!bksge::is_invocable<memfun_type_iic>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, int*>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, int&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, int*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, int&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, int*&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               , int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               , int*>::value, "");
	static_assert( bksge::is_invocable<memfun_type_iic, X               , int               &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               , int const         &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               , int       volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               , int const volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               , int*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               , int&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         , int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         , int*>::value, "");
	static_assert( bksge::is_invocable<memfun_type_iic, X const         , int               &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         , int const         &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         , int       volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         , int const volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         , int*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         , int&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile, int*>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile, int               &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile, int const         &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile, int       volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile, int const volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile, int*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile, int&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile, int*>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile, int               &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile, int const         &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile, int       volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile, int const volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile, int*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile, int&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               *, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               *, int*>::value, "");
	static_assert( bksge::is_invocable<memfun_type_iic, X               *, int               &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               *, int const         &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               *, int       volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               *, int const volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               *, int*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               *, int&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         *, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         *, int*>::value, "");
	static_assert( bksge::is_invocable<memfun_type_iic, X const         *, int               &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         *, int const         &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         *, int       volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         *, int const volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         *, int*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         *, int&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile*, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile*, int*>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile*, int               &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile*, int const         &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile*, int       volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile*, int const volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile*, int*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile*, int&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile*, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile*, int*>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile*, int               &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile*, int const         &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile*, int       volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile*, int const volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile*, int*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile*, int&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               &, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               &, int*>::value, "");
	static_assert( bksge::is_invocable<memfun_type_iic, X               &, int               &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               &, int const         &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               &, int       volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               &, int const volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               &, int*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               &, int&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         &, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         &, int*>::value, "");
	static_assert( bksge::is_invocable<memfun_type_iic, X const         &, int               &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         &, int const         &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         &, int       volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         &, int const volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         &, int*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         &, int&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile&, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile&, int*>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile&, int               &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile&, int const         &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile&, int       volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile&, int const volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile&, int*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile&, int&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile&, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile&, int*>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile&, int               &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile&, int const         &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile&, int       volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile&, int const volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile&, int*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile&, int&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               &&, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               &&, int*>::value, "");
	static_assert( bksge::is_invocable<memfun_type_iic, X               &&, int               &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               &&, int const         &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               &&, int       volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               &&, int const volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               &&, int*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X               &&, int&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         &&, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         &&, int*>::value, "");
	static_assert( bksge::is_invocable<memfun_type_iic, X const         &&, int               &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         &&, int const         &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         &&, int       volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         &&, int const volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         &&, int*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const         &&, int&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile&&, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile&&, int*>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile&&, int               &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile&&, int const         &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile&&, int       volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile&&, int const volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile&&, int*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X       volatile&&, int&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile&&, int>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile&&, int*>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile&&, int               &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile&&, int const         &>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile&&, int       volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile&&, int const volatile&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile&&, int*&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X const volatile&&, int&&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X, float&>::value, "");
	static_assert(!bksge::is_invocable<memfun_type_iic, X, int&, int>::value, "");
	static_assert( bksge::is_invocable<memfun_type_iic, Y, int&>::value, "");
	static_assert( bksge::is_invocable<memfun_type_iic, Y*, int&>::value, "");
	static_assert( bksge::is_invocable<memfun_type_iic, Y&, int&>::value, "");
	static_assert( bksge::is_invocable<memfun_type_iic, Y&&, int&>::value, "");

	struct F
	{
		int operator()();
		int operator()(int);
		int operator()(float);
	private:
		void operator()(int, int);
	};

	static_assert( bksge::is_invocable<F>::value, "");
	static_assert( bksge::is_invocable<F, int>::value, "");
	static_assert( bksge::is_invocable<F, float>::value, "");
	static_assert(!bksge::is_invocable<F, int, int>::value, "");
}

}	// namespace is_invocable_test

}	// namespace bksge_type_traits_test
