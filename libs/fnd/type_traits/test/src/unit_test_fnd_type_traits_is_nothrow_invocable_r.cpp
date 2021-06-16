/**
 *	@file	unit_test_fnd_type_traits_is_nothrow_invocable_r.cpp
 *
 *	@brief	is_nothrow_invocable_r のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_nothrow_invocable_r.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(b, ...)	\
	static_assert(bksge::is_nothrow_invocable_r_v<__VA_ARGS__>      == b, "");	\
	static_assert(bksge::is_nothrow_invocable_r<__VA_ARGS__>::value == b, "");	\
	static_assert(bksge::is_nothrow_invocable_r<__VA_ARGS__>()      == b, "")

#else

#define BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(b, ...)	\
	static_assert(bksge::is_nothrow_invocable_r<__VA_ARGS__>::value == b, "");	\
	static_assert(bksge::is_nothrow_invocable_r<__VA_ARGS__>()      == b, "")

#endif

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_CLANG("-Wundefined-internal")

namespace bksge_type_traits_test
{

namespace is_nothrow_invocable_r_test
{

using func_type_v0 = void(*)();

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void,  func_type_v0);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  void,  func_type_v0);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void*, func_type_v0);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int,   func_type_v0);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void,  func_type_v0, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void*, func_type_v0, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int,   func_type_v0, int);

#if defined(BKSGE_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)

using func_type_v0_nt = void(*)() noexcept;

BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  void,  func_type_v0_nt);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void*, func_type_v0_nt);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int,   func_type_v0_nt);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void,  func_type_v0_nt, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void*, func_type_v0_nt, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int,   func_type_v0_nt, int);

#endif

struct X {};
using mem_type = int X::*;

BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  int,  mem_type, X&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  int&, mem_type, X&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, mem_type, X&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  int&, mem_type, X*);

using memfun_type = int (X::*)();

BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type, int&);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type, X&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type, X*);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, memfun_type, X&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, memfun_type, X*);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type, X&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type, X*, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type, X&, int, char);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type, X*, int, char);

#if defined(BKSGE_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)

using memfun_type_nt = int (X::*)() noexcept;

BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type_nt);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type_nt, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type_nt, int&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, memfun_type_nt, X&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, memfun_type_nt, X*);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type_nt, X&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type_nt, X*, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type_nt, X&, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type_nt, X*, int, int);

#endif

struct F
{
	int&   operator()();
	long&  operator()() const BKSGE_NOEXCEPT;
	short& operator()(int);
	char&  operator()(int) volatile BKSGE_NOEXCEPT;
};

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F               );
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  int&, F               );
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const         );
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F       volatile);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const volatile);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F               );
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  long&, F const         );
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F       volatile);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F const volatile);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F               );
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const         );
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F       volatile);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const volatile);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F               );
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const         );
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F       volatile);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const volatile);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F               );
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  void, F               );
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  void, F const         );
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F       volatile);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F const volatile);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F               );
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, F               );
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, F const         );
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F       volatile);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F const volatile);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F               );
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, F               );
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, F const         );
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F       volatile);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F const volatile);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F               );
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  short, F               );
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  short, F const         );
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F       volatile);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F const volatile);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F               );
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  char, F               );
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  char, F const         );
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F       volatile);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F const volatile);

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F               &);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  int&, F               &);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const         &);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F       volatile&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const volatile&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F               &);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  long&, F const         &);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F       volatile&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F const volatile&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F               &);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const         &);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F       volatile&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const volatile&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F               &);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const         &);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F       volatile&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const volatile&);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F               &);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  void, F               &);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  void, F const         &);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F       volatile&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F const volatile&);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F               &);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, F               &);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, F const         &);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F       volatile&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F const volatile&);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F               &);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, F               &);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, F const         &);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F       volatile&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F const volatile&);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F               &);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  short, F               &);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  short, F const         &);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F       volatile&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F const volatile&);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F               &);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  char, F               &);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  char, F const         &);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F       volatile&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F const volatile&);

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F               &&);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  int&, F               &&);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const         &&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F       volatile&&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const volatile&&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F               &&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  long&, F const         &&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F       volatile&&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F const volatile&&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F               &&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const         &&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F       volatile&&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const volatile&&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F               &&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const         &&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F       volatile&&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const volatile&&);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F               &&);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  void, F               &&);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  void, F const         &&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F       volatile&&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F const volatile&&);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F               &&);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, F               &&);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, F const         &&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F       volatile&&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F const volatile&&);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F               &&);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, F               &&);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, F const         &&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F       volatile&&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F const volatile&&);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F               &&);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  short, F               &&);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  short, F const         &&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F       volatile&&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F const volatile&&);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F               &&);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  char, F               &&);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  char, F const         &&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F       volatile&&);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F const volatile&&);

BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F               &, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const         &, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F       volatile&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const volatile&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F               &, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F const         &, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F       volatile&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F const volatile&, int);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F               &, int);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  short&, F               &, int);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const         &, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F       volatile&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const volatile&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F               &, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const         &, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  char&, F       volatile&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const volatile&, int);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F               &, int);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  void, F               &, int);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F const         &, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  void, F       volatile&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F const volatile&, int);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F               &, int);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, F               &, int);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F const         &, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, F       volatile&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F const volatile&, int);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F               &, int);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, F               &, int);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F const         &, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, F       volatile&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F const volatile&, int);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F               &, int);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  short, F               &, int);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F const         &, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  short, F       volatile&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F const volatile&, int);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F               &, int);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  char, F               &, int);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F const         &, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  char, F       volatile&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F const volatile&, int);

BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F               &&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const         &&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F       volatile&&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const volatile&&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F               &&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F const         &&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F       volatile&&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F const volatile&&, int);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F               &&, int);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  short&, F               &&, int);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const         &&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F       volatile&&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const volatile&&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F               &&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const         &&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  char&, F       volatile&&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const volatile&&, int);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F               &&, int);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  void, F               &&, int);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F const         &&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  void, F       volatile&&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F const volatile&&, int);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F               &&, int);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, F               &&, int);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F const         &&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, F       volatile&&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F const volatile&&, int);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F               &&, int);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, F               &&, int);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F const         &&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, F       volatile&&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F const volatile&&, int);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F               &&, int);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  short, F               &&, int);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F const         &&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  short, F       volatile&&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F const volatile&&, int);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F               &&, int);
#else
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  char, F               &&, int);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F const         &&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(true,  char, F       volatile&&, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F const volatile&&, int);

BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F       volatile, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const volatile, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F const, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F       volatile, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F const volatile, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F       volatile, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const volatile, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F       volatile, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const volatile, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F const, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F       volatile, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F const volatile, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F const, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F       volatile, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F const volatile, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F const, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F       volatile, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F const volatile, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F const, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F       volatile, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F const volatile, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F const, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F       volatile, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F const volatile, int, int);

}	// namespace is_nothrow_invocable_r_test

}	// namespace bksge_type_traits_test

BKSGE_WARNING_POP()

#undef BKSGE_IS_NOTHROW_INVOCABLE_R_TEST
