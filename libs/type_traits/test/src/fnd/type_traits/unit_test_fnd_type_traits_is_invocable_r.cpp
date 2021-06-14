/**
 *	@file	unit_test_fnd_type_traits_is_invocable_r.cpp
 *
 *	@brief	is_invocable_r のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_invocable_r.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_INVOCABLE_R_TEST(b, ...)	\
	static_assert(bksge::is_invocable_r_v<__VA_ARGS__>      == b, "");	\
	static_assert(bksge::is_invocable_r<__VA_ARGS__>::value == b, "");	\
	static_assert(bksge::is_invocable_r<__VA_ARGS__>()      == b, "")

#else

#define BKSGE_IS_INVOCABLE_R_TEST(b, ...)	\
	static_assert(bksge::is_invocable_r<__VA_ARGS__>::value == b, "");	\
	static_assert(bksge::is_invocable_r<__VA_ARGS__>()      == b, "")

#endif

namespace bksge_type_traits_test
{

namespace is_invocable_r_test
{

using func_type_v0 = void(*)();

BKSGE_IS_INVOCABLE_R_TEST(true,  void,  func_type_v0);
BKSGE_IS_INVOCABLE_R_TEST(false, void*, func_type_v0);
BKSGE_IS_INVOCABLE_R_TEST(false, int,   func_type_v0);
BKSGE_IS_INVOCABLE_R_TEST(false, void,  func_type_v0, int);
BKSGE_IS_INVOCABLE_R_TEST(false, void*, func_type_v0, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int,   func_type_v0, int);

using func_type_i0 = int(*)();

BKSGE_IS_INVOCABLE_R_TEST(true,  void, func_type_i0);
BKSGE_IS_INVOCABLE_R_TEST(true,  int,  func_type_i0);
BKSGE_IS_INVOCABLE_R_TEST(false, int&, func_type_i0);
BKSGE_IS_INVOCABLE_R_TEST(true,  long, func_type_i0);
BKSGE_IS_INVOCABLE_R_TEST(false, void, func_type_i0, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int,  func_type_i0, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int&, func_type_i0, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long, func_type_i0, int);

using func_type_l0 = int&(*)();

BKSGE_IS_INVOCABLE_R_TEST(true,  void,  func_type_l0);
BKSGE_IS_INVOCABLE_R_TEST(true,  int,   func_type_l0);
BKSGE_IS_INVOCABLE_R_TEST(true,  int&,  func_type_l0);
BKSGE_IS_INVOCABLE_R_TEST(false, int&&, func_type_l0);
BKSGE_IS_INVOCABLE_R_TEST(true,  long,  func_type_l0);
BKSGE_IS_INVOCABLE_R_TEST(false, long&, func_type_l0);
BKSGE_IS_INVOCABLE_R_TEST(false, void,  func_type_l0, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int,   func_type_l0, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int&,  func_type_l0, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long,  func_type_l0, int);

using func_type_ii = int(*)(int);

BKSGE_IS_INVOCABLE_R_TEST(false, int,  func_type_ii);
BKSGE_IS_INVOCABLE_R_TEST(false, int&, func_type_ii);
BKSGE_IS_INVOCABLE_R_TEST(false, long, func_type_ii);
BKSGE_IS_INVOCABLE_R_TEST(true,  int,  func_type_ii, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int&, func_type_ii, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  long, func_type_ii, int);

using func_type_il = int(*)(int&);

BKSGE_IS_INVOCABLE_R_TEST(false, int,  func_type_il, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int&, func_type_il, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long, func_type_il, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  int,  func_type_il, int&);
BKSGE_IS_INVOCABLE_R_TEST(false, int&, func_type_il, int&);
BKSGE_IS_INVOCABLE_R_TEST(true,  long, func_type_il, int&);

using func_type_ir = int(*)(int&&);

BKSGE_IS_INVOCABLE_R_TEST(true,  int,  func_type_ir, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int&, func_type_ir, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  long, func_type_ir, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int,  func_type_ir, int&);
BKSGE_IS_INVOCABLE_R_TEST(false, int&, func_type_ir, int&);
BKSGE_IS_INVOCABLE_R_TEST(false, long, func_type_ir, int&);

struct X {};

using mem_type_i = int X::*;

BKSGE_IS_INVOCABLE_R_TEST(false, int,  mem_type_i, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int&, mem_type_i, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long, mem_type_i, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int,  mem_type_i, int&);
BKSGE_IS_INVOCABLE_R_TEST(false, int&, mem_type_i, int&);
BKSGE_IS_INVOCABLE_R_TEST(false, long, mem_type_i, int&);
BKSGE_IS_INVOCABLE_R_TEST(true,  int,  mem_type_i, X&);
BKSGE_IS_INVOCABLE_R_TEST(true,  int&, mem_type_i, X&);
BKSGE_IS_INVOCABLE_R_TEST(true,  long, mem_type_i, X&);

using memfun_type_i = int (X::*)();

BKSGE_IS_INVOCABLE_R_TEST(true,  int,  memfun_type_i, X&);
BKSGE_IS_INVOCABLE_R_TEST(false, int&, memfun_type_i, X&);
BKSGE_IS_INVOCABLE_R_TEST(true,  long, memfun_type_i, X&);
BKSGE_IS_INVOCABLE_R_TEST(false, int,  memfun_type_i, const X&);

using memfun_type_iic = int& (X::*)(int&) const;

BKSGE_IS_INVOCABLE_R_TEST(true,  int,   memfun_type_iic, const X&, int&);
BKSGE_IS_INVOCABLE_R_TEST(true,  int&,  memfun_type_iic, const X&, int&);
BKSGE_IS_INVOCABLE_R_TEST(true,  long,  memfun_type_iic, const X&, int&);
BKSGE_IS_INVOCABLE_R_TEST(false, long&, memfun_type_iic, const X&, int&);

struct F
{
	int& operator()();
	long& operator()() const;
	short& operator()(int);
	char& operator()(int) const;
};

BKSGE_IS_INVOCABLE_R_TEST(true,  int&,   F               );
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F const         );
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F       volatile);
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F const volatile);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F               );
BKSGE_IS_INVOCABLE_R_TEST(true,  long&,  F const         );
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F       volatile);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F const volatile);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F               );
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F const         );
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F       volatile);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F const volatile);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F               );
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F const         );
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F       volatile);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F const volatile);
BKSGE_IS_INVOCABLE_R_TEST(true,  void,   F               );
BKSGE_IS_INVOCABLE_R_TEST(true,  void,   F const         );
BKSGE_IS_INVOCABLE_R_TEST(false, void,   F       volatile);
BKSGE_IS_INVOCABLE_R_TEST(false, void,   F const volatile);
BKSGE_IS_INVOCABLE_R_TEST(true,  int,    F               );
BKSGE_IS_INVOCABLE_R_TEST(true,  int,    F const         );
BKSGE_IS_INVOCABLE_R_TEST(false, int,    F       volatile);
BKSGE_IS_INVOCABLE_R_TEST(false, int,    F const volatile);
BKSGE_IS_INVOCABLE_R_TEST(true,  long,   F               );
BKSGE_IS_INVOCABLE_R_TEST(true,  long,   F const         );
BKSGE_IS_INVOCABLE_R_TEST(false, long,   F       volatile);
BKSGE_IS_INVOCABLE_R_TEST(false, long,   F const volatile);
BKSGE_IS_INVOCABLE_R_TEST(true,  short,  F               );
BKSGE_IS_INVOCABLE_R_TEST(true,  short,  F const         );
BKSGE_IS_INVOCABLE_R_TEST(false, short,  F       volatile);
BKSGE_IS_INVOCABLE_R_TEST(false, short,  F const volatile);
BKSGE_IS_INVOCABLE_R_TEST(true,  char,   F               );
BKSGE_IS_INVOCABLE_R_TEST(true,  char,   F const         );
BKSGE_IS_INVOCABLE_R_TEST(false, char,   F       volatile);
BKSGE_IS_INVOCABLE_R_TEST(false, char,   F const volatile);

BKSGE_IS_INVOCABLE_R_TEST(true,  int&,   F               &);
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F const         &);
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F       volatile&);
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F const volatile&);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F               &);
BKSGE_IS_INVOCABLE_R_TEST(true,  long&,  F const         &);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F       volatile&);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F const volatile&);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F               &);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F const         &);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F       volatile&);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F const volatile&);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F               &);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F const         &);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F       volatile&);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F const volatile&);
BKSGE_IS_INVOCABLE_R_TEST(true,  void,   F               &);
BKSGE_IS_INVOCABLE_R_TEST(true,  void,   F const         &);
BKSGE_IS_INVOCABLE_R_TEST(false, void,   F       volatile&);
BKSGE_IS_INVOCABLE_R_TEST(false, void,   F const volatile&);
BKSGE_IS_INVOCABLE_R_TEST(true,  int,    F               &);
BKSGE_IS_INVOCABLE_R_TEST(true,  int,    F const         &);
BKSGE_IS_INVOCABLE_R_TEST(false, int,    F       volatile&);
BKSGE_IS_INVOCABLE_R_TEST(false, int,    F const volatile&);
BKSGE_IS_INVOCABLE_R_TEST(true,  long,   F               &);
BKSGE_IS_INVOCABLE_R_TEST(true,  long,   F const         &);
BKSGE_IS_INVOCABLE_R_TEST(false, long,   F       volatile&);
BKSGE_IS_INVOCABLE_R_TEST(false, long,   F const volatile&);
BKSGE_IS_INVOCABLE_R_TEST(true,  short,  F               &);
BKSGE_IS_INVOCABLE_R_TEST(true,  short,  F const         &);
BKSGE_IS_INVOCABLE_R_TEST(false, short,  F       volatile&);
BKSGE_IS_INVOCABLE_R_TEST(false, short,  F const volatile&);
BKSGE_IS_INVOCABLE_R_TEST(true,  char,   F               &);
BKSGE_IS_INVOCABLE_R_TEST(true,  char,   F const         &);
BKSGE_IS_INVOCABLE_R_TEST(false, char,   F       volatile&);
BKSGE_IS_INVOCABLE_R_TEST(false, char,   F const volatile&);

BKSGE_IS_INVOCABLE_R_TEST(true,  int&,   F               &&);
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F const         &&);
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F       volatile&&);
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F const volatile&&);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F               &&);
BKSGE_IS_INVOCABLE_R_TEST(true,  long&,  F const         &&);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F       volatile&&);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F const volatile&&);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F               &&);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F const         &&);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F       volatile&&);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F const volatile&&);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F               &&);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F const         &&);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F       volatile&&);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F const volatile&&);
BKSGE_IS_INVOCABLE_R_TEST(true,  void,   F               &&);
BKSGE_IS_INVOCABLE_R_TEST(true,  void,   F const         &&);
BKSGE_IS_INVOCABLE_R_TEST(false, void,   F       volatile&&);
BKSGE_IS_INVOCABLE_R_TEST(false, void,   F const volatile&&);
BKSGE_IS_INVOCABLE_R_TEST(true,  int,    F               &&);
BKSGE_IS_INVOCABLE_R_TEST(true,  int,    F const         &&);
BKSGE_IS_INVOCABLE_R_TEST(false, int,    F       volatile&&);
BKSGE_IS_INVOCABLE_R_TEST(false, int,    F const volatile&&);
BKSGE_IS_INVOCABLE_R_TEST(true,  long,   F               &&);
BKSGE_IS_INVOCABLE_R_TEST(true,  long,   F const         &&);
BKSGE_IS_INVOCABLE_R_TEST(false, long,   F       volatile&&);
BKSGE_IS_INVOCABLE_R_TEST(false, long,   F const volatile&&);
BKSGE_IS_INVOCABLE_R_TEST(true,  short,  F               &&);
BKSGE_IS_INVOCABLE_R_TEST(true,  short,  F const         &&);
BKSGE_IS_INVOCABLE_R_TEST(false, short,  F       volatile&&);
BKSGE_IS_INVOCABLE_R_TEST(false, short,  F const volatile&&);
BKSGE_IS_INVOCABLE_R_TEST(true,  char,   F               &&);
BKSGE_IS_INVOCABLE_R_TEST(true,  char,   F const         &&);
BKSGE_IS_INVOCABLE_R_TEST(false, char,   F       volatile&&);
BKSGE_IS_INVOCABLE_R_TEST(false, char,   F const volatile&&);

BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F               , int);
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F const         , int);
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F       volatile, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F const volatile, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F               , int);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F const         , int);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F       volatile, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F const volatile, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  short&, F               , int);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F const         , int);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F       volatile, int);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F const volatile, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F               , int);
BKSGE_IS_INVOCABLE_R_TEST(true,  char&,  F const         , int);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F       volatile, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F const volatile, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  void,   F               , int);
BKSGE_IS_INVOCABLE_R_TEST(true,  void,   F const         , int);
BKSGE_IS_INVOCABLE_R_TEST(false, void,   F       volatile, int);
BKSGE_IS_INVOCABLE_R_TEST(false, void,   F const volatile, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  int,    F               , int);
BKSGE_IS_INVOCABLE_R_TEST(true,  int,    F const         , int);
BKSGE_IS_INVOCABLE_R_TEST(false, int,    F       volatile, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int,    F const volatile, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  long,   F               , int);
BKSGE_IS_INVOCABLE_R_TEST(true,  long,   F const         , int);
BKSGE_IS_INVOCABLE_R_TEST(false, long,   F       volatile, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long,   F const volatile, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  short,  F               , int);
BKSGE_IS_INVOCABLE_R_TEST(true,  short,  F const         , int);
BKSGE_IS_INVOCABLE_R_TEST(false, short,  F       volatile, int);
BKSGE_IS_INVOCABLE_R_TEST(false, short,  F const volatile, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  char,   F               , int);
BKSGE_IS_INVOCABLE_R_TEST(true,  char,   F const         , int);
BKSGE_IS_INVOCABLE_R_TEST(false, char,   F       volatile, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char,   F const volatile, int);

BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F               &, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F const         &, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F       volatile&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F const volatile&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F               &, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F const         &, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F       volatile&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F const volatile&, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  short&, F               &, int);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F const         &, int);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F       volatile&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F const volatile&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F               &, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  char&,  F const         &, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F       volatile&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F const volatile&, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  void,   F               &, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  void,   F const         &, int);
BKSGE_IS_INVOCABLE_R_TEST(false, void,   F       volatile&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, void,   F const volatile&, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  int,    F               &, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  int,    F const         &, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int,    F       volatile&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int,    F const volatile&, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  long,   F               &, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  long,   F const         &, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long,   F       volatile&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long,   F const volatile&, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  short,  F               &, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  short,  F const         &, int);
BKSGE_IS_INVOCABLE_R_TEST(false, short,  F       volatile&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, short,  F const volatile&, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  char,   F               &, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  char,   F const         &, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char,   F       volatile&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char,   F const volatile&, int);

BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F               &&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F const         &&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F       volatile&&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F const volatile&&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F               &&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F const         &&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F       volatile&&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F const volatile&&, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  short&, F               &&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F const         &&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F       volatile&&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F const volatile&&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F               &&, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  char&,  F const         &&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F       volatile&&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F const volatile&&, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  void,   F               &&, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  void,   F const         &&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, void,   F       volatile&&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, void,   F const volatile&&, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  int,    F               &&, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  int,    F const         &&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int,    F       volatile&&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int,    F const volatile&&, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  long,   F               &&, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  long,   F const         &&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long,   F       volatile&&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long,   F const volatile&&, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  short,  F               &&, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  short,  F const         &&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, short,  F       volatile&&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, short,  F const volatile&&, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  char,   F               &&, int);
BKSGE_IS_INVOCABLE_R_TEST(true,  char,   F const         &&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char,   F       volatile&&, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char,   F const volatile&&, int);

BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F               , int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F const         , int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F       volatile, int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int&,   F const volatile, int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F               , int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F const         , int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F       volatile, int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long&,  F const volatile, int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F               , int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F const         , int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F       volatile, int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, short&, F const volatile, int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F               , int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F const         , int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F       volatile, int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char&,  F const volatile, int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, void,   F               , int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, void,   F const         , int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, void,   F       volatile, int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, void,   F const volatile, int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int,    F               , int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int,    F const         , int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int,    F       volatile, int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, int,    F const volatile, int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long,   F               , int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long,   F const         , int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long,   F       volatile, int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, long,   F const volatile, int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, short,  F               , int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, short,  F const         , int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, short,  F       volatile, int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, short,  F const volatile, int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char,   F               , int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char,   F const         , int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char,   F       volatile, int, int);
BKSGE_IS_INVOCABLE_R_TEST(false, char,   F const volatile, int, int);

}	// namespace is_invocable_r_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_INVOCABLE_R_TEST
