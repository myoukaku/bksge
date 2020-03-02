/**
 *	@file	unit_test_fnd_type_traits_is_invocable_r.cpp
 *
 *	@brief	is_invocable_r のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_invocable_r.hpp>
#include <gtest/gtest.h>

namespace bksge_type_traits_test
{

namespace is_invocable_r_test
{

GTEST_TEST(TypeTraitsTest, IsInvocableRTest)
{
	using func_type_v0 = void(*)();

	static_assert( bksge::is_invocable_r<void,  func_type_v0>::value, "");
	static_assert(!bksge::is_invocable_r<void*, func_type_v0>::value, "");
	static_assert(!bksge::is_invocable_r<int,   func_type_v0>::value, "");
	static_assert(!bksge::is_invocable_r<void,  func_type_v0, int>::value, "");
	static_assert(!bksge::is_invocable_r<void*, func_type_v0, int>::value, "");
	static_assert(!bksge::is_invocable_r<int,   func_type_v0, int>::value, "");

	using func_type_i0 = int(*)();

	static_assert( bksge::is_invocable_r<void, func_type_i0>::value, "");
	static_assert( bksge::is_invocable_r<int,  func_type_i0>::value, "");
	static_assert(!bksge::is_invocable_r<int&, func_type_i0>::value, "");
	static_assert( bksge::is_invocable_r<long, func_type_i0>::value, "");
	static_assert(!bksge::is_invocable_r<void, func_type_i0, int>::value, "");
	static_assert(!bksge::is_invocable_r<int,  func_type_i0, int>::value, "");
	static_assert(!bksge::is_invocable_r<int&, func_type_i0, int>::value, "");
	static_assert(!bksge::is_invocable_r<long, func_type_i0, int>::value, "");

	using func_type_l0 = int&(*)();

	static_assert( bksge::is_invocable_r<void,  func_type_l0>::value, "");
	static_assert( bksge::is_invocable_r<int,   func_type_l0>::value, "");
	static_assert( bksge::is_invocable_r<int&,  func_type_l0>::value, "");
	static_assert(!bksge::is_invocable_r<int&&, func_type_l0>::value, "");
	static_assert( bksge::is_invocable_r<long,  func_type_l0>::value, "");
	static_assert(!bksge::is_invocable_r<long&, func_type_l0>::value, "");
	static_assert(!bksge::is_invocable_r<void,  func_type_l0, int>::value, "");
	static_assert(!bksge::is_invocable_r<int,   func_type_l0, int>::value, "");
	static_assert(!bksge::is_invocable_r<int&,  func_type_l0, int>::value, "");
	static_assert(!bksge::is_invocable_r<long,  func_type_l0, int>::value, "");

	using func_type_ii = int(*)(int);

	static_assert(!bksge::is_invocable_r<int,  func_type_ii>::value, "");
	static_assert(!bksge::is_invocable_r<int&, func_type_ii>::value, "");
	static_assert(!bksge::is_invocable_r<long, func_type_ii>::value, "");
	static_assert( bksge::is_invocable_r<int,  func_type_ii, int>::value, "");
	static_assert(!bksge::is_invocable_r<int&, func_type_ii, int>::value, "");
	static_assert( bksge::is_invocable_r<long, func_type_ii, int>::value, "");

	using func_type_il = int(*)(int&);

	static_assert(!bksge::is_invocable_r<int,  func_type_il, int>::value, "");
	static_assert(!bksge::is_invocable_r<int&, func_type_il, int>::value, "");
	static_assert(!bksge::is_invocable_r<long, func_type_il, int>::value, "");
	static_assert( bksge::is_invocable_r<int,  func_type_il, int&>::value, "");
	static_assert(!bksge::is_invocable_r<int&, func_type_il, int&>::value, "");
	static_assert( bksge::is_invocable_r<long, func_type_il, int&>::value, "");

	using func_type_ir = int(*)(int&&);

	static_assert( bksge::is_invocable_r<int,  func_type_ir, int>::value, "");
	static_assert(!bksge::is_invocable_r<int&, func_type_ir, int>::value, "");
	static_assert( bksge::is_invocable_r<long, func_type_ir, int>::value, "");
	static_assert(!bksge::is_invocable_r<int,  func_type_ir, int&>::value, "");
	static_assert(!bksge::is_invocable_r<int&, func_type_ir, int&>::value, "");
	static_assert(!bksge::is_invocable_r<long, func_type_ir, int&>::value, "");

	struct X {};

	using mem_type_i = int X::*;

	static_assert(!bksge::is_invocable_r<int,  mem_type_i, int>::value, "");
	static_assert(!bksge::is_invocable_r<int&, mem_type_i, int>::value, "");
	static_assert(!bksge::is_invocable_r<long, mem_type_i, int>::value, "");
	static_assert(!bksge::is_invocable_r<int,  mem_type_i, int&>::value, "");
	static_assert(!bksge::is_invocable_r<int&, mem_type_i, int&>::value, "");
	static_assert(!bksge::is_invocable_r<long, mem_type_i, int&>::value, "");
	static_assert( bksge::is_invocable_r<int,  mem_type_i, X&>::value, "");
	static_assert( bksge::is_invocable_r<int&, mem_type_i, X&>::value, "");
	static_assert( bksge::is_invocable_r<long, mem_type_i, X&>::value, "");

	using memfun_type_i = int (X::*)();

	static_assert( bksge::is_invocable_r<int,  memfun_type_i, X&>::value, "");
	static_assert(!bksge::is_invocable_r<int&, memfun_type_i, X&>::value, "");
	static_assert( bksge::is_invocable_r<long, memfun_type_i, X&>::value, "");
	static_assert(!bksge::is_invocable_r<int,  memfun_type_i, const X&>::value, "");

	using memfun_type_iic = int& (X::*)(int&) const;

	static_assert( bksge::is_invocable_r<int,   memfun_type_iic, const X&, int&>::value, "");
	static_assert( bksge::is_invocable_r<int&,  memfun_type_iic, const X&, int&>::value, "");
	static_assert( bksge::is_invocable_r<long,  memfun_type_iic, const X&, int&>::value, "");
	static_assert(!bksge::is_invocable_r<long&, memfun_type_iic, const X&, int&>::value, "");

	struct F
	{
		int& operator()();
		long& operator()() const;
		short& operator()(int);
		char& operator()(int) const;
	};

	static_assert( bksge::is_invocable_r<int&,   F               >::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F const         >::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F       volatile>::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F const volatile>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F               >::value, "");
	static_assert( bksge::is_invocable_r<long&,  F const         >::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F       volatile>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F const volatile>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F               >::value, "");
	static_assert(!bksge::is_invocable_r<short&, F const         >::value, "");
	static_assert(!bksge::is_invocable_r<short&, F       volatile>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F const volatile>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F               >::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F const         >::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F       volatile>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F const volatile>::value, "");
	static_assert( bksge::is_invocable_r<void,   F               >::value, "");
	static_assert( bksge::is_invocable_r<void,   F const         >::value, "");
	static_assert(!bksge::is_invocable_r<void,   F       volatile>::value, "");
	static_assert(!bksge::is_invocable_r<void,   F const volatile>::value, "");
	static_assert( bksge::is_invocable_r<int,    F               >::value, "");
	static_assert( bksge::is_invocable_r<int,    F const         >::value, "");
	static_assert(!bksge::is_invocable_r<int,    F       volatile>::value, "");
	static_assert(!bksge::is_invocable_r<int,    F const volatile>::value, "");
	static_assert( bksge::is_invocable_r<long,   F               >::value, "");
	static_assert( bksge::is_invocable_r<long,   F const         >::value, "");
	static_assert(!bksge::is_invocable_r<long,   F       volatile>::value, "");
	static_assert(!bksge::is_invocable_r<long,   F const volatile>::value, "");
	static_assert( bksge::is_invocable_r<short,  F               >::value, "");
	static_assert( bksge::is_invocable_r<short,  F const         >::value, "");
	static_assert(!bksge::is_invocable_r<short,  F       volatile>::value, "");
	static_assert(!bksge::is_invocable_r<short,  F const volatile>::value, "");
	static_assert( bksge::is_invocable_r<char,   F               >::value, "");
	static_assert( bksge::is_invocable_r<char,   F const         >::value, "");
	static_assert(!bksge::is_invocable_r<char,   F       volatile>::value, "");
	static_assert(!bksge::is_invocable_r<char,   F const volatile>::value, "");

	static_assert( bksge::is_invocable_r<int&,   F               &>::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F const         &>::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F       volatile&>::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F const volatile&>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F               &>::value, "");
	static_assert( bksge::is_invocable_r<long&,  F const         &>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F       volatile&>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F const volatile&>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F               &>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F const         &>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F       volatile&>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F const volatile&>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F               &>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F const         &>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F       volatile&>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F const volatile&>::value, "");
	static_assert( bksge::is_invocable_r<void,   F               &>::value, "");
	static_assert( bksge::is_invocable_r<void,   F const         &>::value, "");
	static_assert(!bksge::is_invocable_r<void,   F       volatile&>::value, "");
	static_assert(!bksge::is_invocable_r<void,   F const volatile&>::value, "");
	static_assert( bksge::is_invocable_r<int,    F               &>::value, "");
	static_assert( bksge::is_invocable_r<int,    F const         &>::value, "");
	static_assert(!bksge::is_invocable_r<int,    F       volatile&>::value, "");
	static_assert(!bksge::is_invocable_r<int,    F const volatile&>::value, "");
	static_assert( bksge::is_invocable_r<long,   F               &>::value, "");
	static_assert( bksge::is_invocable_r<long,   F const         &>::value, "");
	static_assert(!bksge::is_invocable_r<long,   F       volatile&>::value, "");
	static_assert(!bksge::is_invocable_r<long,   F const volatile&>::value, "");
	static_assert( bksge::is_invocable_r<short,  F               &>::value, "");
	static_assert( bksge::is_invocable_r<short,  F const         &>::value, "");
	static_assert(!bksge::is_invocable_r<short,  F       volatile&>::value, "");
	static_assert(!bksge::is_invocable_r<short,  F const volatile&>::value, "");
	static_assert( bksge::is_invocable_r<char,   F               &>::value, "");
	static_assert( bksge::is_invocable_r<char,   F const         &>::value, "");
	static_assert(!bksge::is_invocable_r<char,   F       volatile&>::value, "");
	static_assert(!bksge::is_invocable_r<char,   F const volatile&>::value, "");

	static_assert( bksge::is_invocable_r<int&,   F               &&>::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F const         &&>::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F       volatile&&>::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F const volatile&&>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F               &&>::value, "");
	static_assert( bksge::is_invocable_r<long&,  F const         &&>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F       volatile&&>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F const volatile&&>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F               &&>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F const         &&>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F       volatile&&>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F const volatile&&>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F               &&>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F const         &&>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F       volatile&&>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F const volatile&&>::value, "");
	static_assert( bksge::is_invocable_r<void,   F               &&>::value, "");
	static_assert( bksge::is_invocable_r<void,   F const         &&>::value, "");
	static_assert(!bksge::is_invocable_r<void,   F       volatile&&>::value, "");
	static_assert(!bksge::is_invocable_r<void,   F const volatile&&>::value, "");
	static_assert( bksge::is_invocable_r<int,    F               &&>::value, "");
	static_assert( bksge::is_invocable_r<int,    F const         &&>::value, "");
	static_assert(!bksge::is_invocable_r<int,    F       volatile&&>::value, "");
	static_assert(!bksge::is_invocable_r<int,    F const volatile&&>::value, "");
	static_assert( bksge::is_invocable_r<long,   F               &&>::value, "");
	static_assert( bksge::is_invocable_r<long,   F const         &&>::value, "");
	static_assert(!bksge::is_invocable_r<long,   F       volatile&&>::value, "");
	static_assert(!bksge::is_invocable_r<long,   F const volatile&&>::value, "");
	static_assert( bksge::is_invocable_r<short,  F               &&>::value, "");
	static_assert( bksge::is_invocable_r<short,  F const         &&>::value, "");
	static_assert(!bksge::is_invocable_r<short,  F       volatile&&>::value, "");
	static_assert(!bksge::is_invocable_r<short,  F const volatile&&>::value, "");
	static_assert( bksge::is_invocable_r<char,   F               &&>::value, "");
	static_assert( bksge::is_invocable_r<char,   F const         &&>::value, "");
	static_assert(!bksge::is_invocable_r<char,   F       volatile&&>::value, "");
	static_assert(!bksge::is_invocable_r<char,   F const volatile&&>::value, "");

	static_assert(!bksge::is_invocable_r<int&,   F               , int>::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F const         , int>::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F       volatile, int>::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F const volatile, int>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F               , int>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F const         , int>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F       volatile, int>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F const volatile, int>::value, "");
	static_assert( bksge::is_invocable_r<short&, F               , int>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F const         , int>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F       volatile, int>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F const volatile, int>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F               , int>::value, "");
	static_assert( bksge::is_invocable_r<char&,  F const         , int>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F       volatile, int>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F const volatile, int>::value, "");
	static_assert( bksge::is_invocable_r<void,   F               , int>::value, "");
	static_assert( bksge::is_invocable_r<void,   F const         , int>::value, "");
	static_assert(!bksge::is_invocable_r<void,   F       volatile, int>::value, "");
	static_assert(!bksge::is_invocable_r<void,   F const volatile, int>::value, "");
	static_assert( bksge::is_invocable_r<int,    F               , int>::value, "");
	static_assert( bksge::is_invocable_r<int,    F const         , int>::value, "");
	static_assert(!bksge::is_invocable_r<int,    F       volatile, int>::value, "");
	static_assert(!bksge::is_invocable_r<int,    F const volatile, int>::value, "");
	static_assert( bksge::is_invocable_r<long,   F               , int>::value, "");
	static_assert( bksge::is_invocable_r<long,   F const         , int>::value, "");
	static_assert(!bksge::is_invocable_r<long,   F       volatile, int>::value, "");
	static_assert(!bksge::is_invocable_r<long,   F const volatile, int>::value, "");
	static_assert( bksge::is_invocable_r<short,  F               , int>::value, "");
	static_assert( bksge::is_invocable_r<short,  F const         , int>::value, "");
	static_assert(!bksge::is_invocable_r<short,  F       volatile, int>::value, "");
	static_assert(!bksge::is_invocable_r<short,  F const volatile, int>::value, "");
	static_assert( bksge::is_invocable_r<char,   F               , int>::value, "");
	static_assert( bksge::is_invocable_r<char,   F const         , int>::value, "");
	static_assert(!bksge::is_invocable_r<char,   F       volatile, int>::value, "");
	static_assert(!bksge::is_invocable_r<char,   F const volatile, int>::value, "");

	static_assert(!bksge::is_invocable_r<int&,   F               &, int>::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F const         &, int>::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F       volatile&, int>::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F const volatile&, int>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F               &, int>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F const         &, int>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F       volatile&, int>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F const volatile&, int>::value, "");
	static_assert( bksge::is_invocable_r<short&, F               &, int>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F const         &, int>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F       volatile&, int>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F const volatile&, int>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F               &, int>::value, "");
	static_assert( bksge::is_invocable_r<char&,  F const         &, int>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F       volatile&, int>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F const volatile&, int>::value, "");
	static_assert( bksge::is_invocable_r<void,   F               &, int>::value, "");
	static_assert( bksge::is_invocable_r<void,   F const         &, int>::value, "");
	static_assert(!bksge::is_invocable_r<void,   F       volatile&, int>::value, "");
	static_assert(!bksge::is_invocable_r<void,   F const volatile&, int>::value, "");
	static_assert( bksge::is_invocable_r<int,    F               &, int>::value, "");
	static_assert( bksge::is_invocable_r<int,    F const         &, int>::value, "");
	static_assert(!bksge::is_invocable_r<int,    F       volatile&, int>::value, "");
	static_assert(!bksge::is_invocable_r<int,    F const volatile&, int>::value, "");
	static_assert( bksge::is_invocable_r<long,   F               &, int>::value, "");
	static_assert( bksge::is_invocable_r<long,   F const         &, int>::value, "");
	static_assert(!bksge::is_invocable_r<long,   F       volatile&, int>::value, "");
	static_assert(!bksge::is_invocable_r<long,   F const volatile&, int>::value, "");
	static_assert( bksge::is_invocable_r<short,  F               &, int>::value, "");
	static_assert( bksge::is_invocable_r<short,  F const         &, int>::value, "");
	static_assert(!bksge::is_invocable_r<short,  F       volatile&, int>::value, "");
	static_assert(!bksge::is_invocable_r<short,  F const volatile&, int>::value, "");
	static_assert( bksge::is_invocable_r<char,   F               &, int>::value, "");
	static_assert( bksge::is_invocable_r<char,   F const         &, int>::value, "");
	static_assert(!bksge::is_invocable_r<char,   F       volatile&, int>::value, "");
	static_assert(!bksge::is_invocable_r<char,   F const volatile&, int>::value, "");

	static_assert(!bksge::is_invocable_r<int&,   F               &&, int>::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F const         &&, int>::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F       volatile&&, int>::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F const volatile&&, int>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F               &&, int>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F const         &&, int>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F       volatile&&, int>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F const volatile&&, int>::value, "");
	static_assert( bksge::is_invocable_r<short&, F               &&, int>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F const         &&, int>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F       volatile&&, int>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F const volatile&&, int>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F               &&, int>::value, "");
	static_assert( bksge::is_invocable_r<char&,  F const         &&, int>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F       volatile&&, int>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F const volatile&&, int>::value, "");
	static_assert( bksge::is_invocable_r<void,   F               &&, int>::value, "");
	static_assert( bksge::is_invocable_r<void,   F const         &&, int>::value, "");
	static_assert(!bksge::is_invocable_r<void,   F       volatile&&, int>::value, "");
	static_assert(!bksge::is_invocable_r<void,   F const volatile&&, int>::value, "");
	static_assert( bksge::is_invocable_r<int,    F               &&, int>::value, "");
	static_assert( bksge::is_invocable_r<int,    F const         &&, int>::value, "");
	static_assert(!bksge::is_invocable_r<int,    F       volatile&&, int>::value, "");
	static_assert(!bksge::is_invocable_r<int,    F const volatile&&, int>::value, "");
	static_assert( bksge::is_invocable_r<long,   F               &&, int>::value, "");
	static_assert( bksge::is_invocable_r<long,   F const         &&, int>::value, "");
	static_assert(!bksge::is_invocable_r<long,   F       volatile&&, int>::value, "");
	static_assert(!bksge::is_invocable_r<long,   F const volatile&&, int>::value, "");
	static_assert( bksge::is_invocable_r<short,  F               &&, int>::value, "");
	static_assert( bksge::is_invocable_r<short,  F const         &&, int>::value, "");
	static_assert(!bksge::is_invocable_r<short,  F       volatile&&, int>::value, "");
	static_assert(!bksge::is_invocable_r<short,  F const volatile&&, int>::value, "");
	static_assert( bksge::is_invocable_r<char,   F               &&, int>::value, "");
	static_assert( bksge::is_invocable_r<char,   F const         &&, int>::value, "");
	static_assert(!bksge::is_invocable_r<char,   F       volatile&&, int>::value, "");
	static_assert(!bksge::is_invocable_r<char,   F const volatile&&, int>::value, "");

	static_assert(!bksge::is_invocable_r<int&,   F               , int, int>::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F const         , int, int>::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F       volatile, int, int>::value, "");
	static_assert(!bksge::is_invocable_r<int&,   F const volatile, int, int>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F               , int, int>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F const         , int, int>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F       volatile, int, int>::value, "");
	static_assert(!bksge::is_invocable_r<long&,  F const volatile, int, int>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F               , int, int>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F const         , int, int>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F       volatile, int, int>::value, "");
	static_assert(!bksge::is_invocable_r<short&, F const volatile, int, int>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F               , int, int>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F const         , int, int>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F       volatile, int, int>::value, "");
	static_assert(!bksge::is_invocable_r<char&,  F const volatile, int, int>::value, "");
	static_assert(!bksge::is_invocable_r<void,   F               , int, int>::value, "");
	static_assert(!bksge::is_invocable_r<void,   F const         , int, int>::value, "");
	static_assert(!bksge::is_invocable_r<void,   F       volatile, int, int>::value, "");
	static_assert(!bksge::is_invocable_r<void,   F const volatile, int, int>::value, "");
	static_assert(!bksge::is_invocable_r<int,    F               , int, int>::value, "");
	static_assert(!bksge::is_invocable_r<int,    F const         , int, int>::value, "");
	static_assert(!bksge::is_invocable_r<int,    F       volatile, int, int>::value, "");
	static_assert(!bksge::is_invocable_r<int,    F const volatile, int, int>::value, "");
	static_assert(!bksge::is_invocable_r<long,   F               , int, int>::value, "");
	static_assert(!bksge::is_invocable_r<long,   F const         , int, int>::value, "");
	static_assert(!bksge::is_invocable_r<long,   F       volatile, int, int>::value, "");
	static_assert(!bksge::is_invocable_r<long,   F const volatile, int, int>::value, "");
	static_assert(!bksge::is_invocable_r<short,  F               , int, int>::value, "");
	static_assert(!bksge::is_invocable_r<short,  F const         , int, int>::value, "");
	static_assert(!bksge::is_invocable_r<short,  F       volatile, int, int>::value, "");
	static_assert(!bksge::is_invocable_r<short,  F const volatile, int, int>::value, "");
	static_assert(!bksge::is_invocable_r<char,   F               , int, int>::value, "");
	static_assert(!bksge::is_invocable_r<char,   F const         , int, int>::value, "");
	static_assert(!bksge::is_invocable_r<char,   F       volatile, int, int>::value, "");
	static_assert(!bksge::is_invocable_r<char,   F const volatile, int, int>::value, "");
}

}	// namespace is_invocable_r_test

}	// namespace bksge_type_traits_test
