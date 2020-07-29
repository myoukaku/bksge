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

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_CLANG("-Wundefined-internal")

namespace bksge_type_traits_test
{

namespace is_nothrow_invocable_r_test
{

using func_type_v0 = void(*)();

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<void,  func_type_v0>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<void,   func_type_v0>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable_r<void*, func_type_v0>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int,   func_type_v0>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<void,  func_type_v0, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<void*, func_type_v0, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int,   func_type_v0, int>::value, "");

#if defined(BKSGE_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)

using func_type_v0_nt = void(*)() noexcept;

static_assert( bksge::is_nothrow_invocable_r<void,  func_type_v0_nt>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<void*, func_type_v0_nt>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int,   func_type_v0_nt>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<void,  func_type_v0_nt, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<void*, func_type_v0_nt, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int,   func_type_v0_nt, int>::value, "");

#endif

struct X {};
using mem_type = int X::*;

static_assert( bksge::is_nothrow_invocable_r<int,  mem_type, X&>::value, "");
static_assert( bksge::is_nothrow_invocable_r<int&, mem_type, X&>::value, "");
static_assert( bksge::is_nothrow_invocable_r<long, mem_type, X&>::value, "");
static_assert( bksge::is_nothrow_invocable_r<int&, mem_type, X*>::value, "");

using memfun_type = int (X::*)();

static_assert(!bksge::is_nothrow_invocable_r<int, memfun_type>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, memfun_type, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, memfun_type, int&>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<int, memfun_type, X&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, memfun_type, X*>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<int, memfun_type, X&>::value, "");
static_assert( bksge::is_nothrow_invocable_r<int, memfun_type, X*>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable_r<int, memfun_type, X&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, memfun_type, X*, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, memfun_type, X&, int, char>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, memfun_type, X*, int, char>::value, "");

#if defined(BKSGE_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)

using memfun_type_nt = int (X::*)() noexcept;

static_assert(!bksge::is_nothrow_invocable_r<int, memfun_type_nt>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, memfun_type_nt, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, memfun_type_nt, int&>::value, "");
static_assert( bksge::is_nothrow_invocable_r<int, memfun_type_nt, X&>::value, "");
static_assert( bksge::is_nothrow_invocable_r<int, memfun_type_nt, X*>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, memfun_type_nt, X&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, memfun_type_nt, X*, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, memfun_type_nt, X&, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, memfun_type_nt, X*, int, int>::value, "");

#endif

struct F
{
	int&   operator()();
	long&  operator()() const BKSGE_NOEXCEPT;
	short& operator()(int);
	char&  operator()(int) volatile BKSGE_NOEXCEPT;
};

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<int&, F               >::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<int&, F               >::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable_r<int&, F const         >::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int&, F       volatile>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int&, F const volatile>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F               >::value, "");
static_assert( bksge::is_nothrow_invocable_r<long&, F const         >::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F       volatile>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F const volatile>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short&, F               >::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short&, F const         >::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short&, F       volatile>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short&, F const volatile>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F               >::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F const         >::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F       volatile>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F const volatile>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<void, F               >::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<void, F               >::value, "");
#endif
static_assert( bksge::is_nothrow_invocable_r<void, F const         >::value, "");
static_assert(!bksge::is_nothrow_invocable_r<void, F       volatile>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<void, F const volatile>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<int, F               >::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<int, F               >::value, "");
#endif
static_assert( bksge::is_nothrow_invocable_r<int, F const         >::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, F       volatile>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, F const volatile>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<long, F               >::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<long, F               >::value, "");
#endif
static_assert( bksge::is_nothrow_invocable_r<long, F const         >::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long, F       volatile>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long, F const volatile>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<short, F               >::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<short, F               >::value, "");
#endif
static_assert( bksge::is_nothrow_invocable_r<short, F const         >::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short, F       volatile>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short, F const volatile>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<char, F               >::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<char, F               >::value, "");
#endif
static_assert( bksge::is_nothrow_invocable_r<char, F const         >::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char, F       volatile>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char, F const volatile>::value, "");

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<int&, F               &>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<int&, F               &>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable_r<int&, F const         &>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int&, F       volatile&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int&, F const volatile&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F               &>::value, "");
static_assert( bksge::is_nothrow_invocable_r<long&, F const         &>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F       volatile&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F const volatile&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short&, F               &>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short&, F const         &>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short&, F       volatile&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short&, F const volatile&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F               &>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F const         &>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F       volatile&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F const volatile&>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<void, F               &>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<void, F               &>::value, "");
#endif
static_assert( bksge::is_nothrow_invocable_r<void, F const         &>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<void, F       volatile&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<void, F const volatile&>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<int, F               &>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<int, F               &>::value, "");
#endif
static_assert( bksge::is_nothrow_invocable_r<int, F const         &>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, F       volatile&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, F const volatile&>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<long, F               &>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<long, F               &>::value, "");
#endif
static_assert( bksge::is_nothrow_invocable_r<long, F const         &>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long, F       volatile&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long, F const volatile&>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<short, F               &>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<short, F               &>::value, "");
#endif
static_assert( bksge::is_nothrow_invocable_r<short, F const         &>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short, F       volatile&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short, F const volatile&>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<char, F               &>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<char, F               &>::value, "");
#endif
static_assert( bksge::is_nothrow_invocable_r<char, F const         &>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char, F       volatile&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char, F const volatile&>::value, "");

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<int&, F               &&>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<int&, F               &&>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable_r<int&, F const         &&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int&, F       volatile&&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int&, F const volatile&&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F               &&>::value, "");
static_assert( bksge::is_nothrow_invocable_r<long&, F const         &&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F       volatile&&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F const volatile&&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short&, F               &&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short&, F const         &&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short&, F       volatile&&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short&, F const volatile&&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F               &&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F const         &&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F       volatile&&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F const volatile&&>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<void, F               &&>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<void, F               &&>::value, "");
#endif
static_assert( bksge::is_nothrow_invocable_r<void, F const         &&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<void, F       volatile&&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<void, F const volatile&&>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<int, F               &&>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<int, F               &&>::value, "");
#endif
static_assert( bksge::is_nothrow_invocable_r<int, F const         &&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, F       volatile&&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, F const volatile&&>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<long, F               &&>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<long, F               &&>::value, "");
#endif
static_assert( bksge::is_nothrow_invocable_r<long, F const         &&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long, F       volatile&&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long, F const volatile&&>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<short, F               &&>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<short, F               &&>::value, "");
#endif
static_assert( bksge::is_nothrow_invocable_r<short, F const         &&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short, F       volatile&&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short, F const volatile&&>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<char, F               &&>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<char, F               &&>::value, "");
#endif
static_assert( bksge::is_nothrow_invocable_r<char, F const         &&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char, F       volatile&&>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char, F const volatile&&>::value, "");

static_assert(!bksge::is_nothrow_invocable_r<int&, F               &, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int&, F const         &, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int&, F       volatile&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int&, F const volatile&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F               &, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F const         &, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F       volatile&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F const volatile&, int>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<short&, F               &, int>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<short&, F               &, int>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable_r<short&, F const         &, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short&, F       volatile&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short&, F const volatile&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F               &, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F const         &, int>::value, "");
static_assert( bksge::is_nothrow_invocable_r<char&, F       volatile&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F const volatile&, int>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<void, F               &, int>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<void, F               &, int>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable_r<void, F const         &, int>::value, "");
static_assert( bksge::is_nothrow_invocable_r<void, F       volatile&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<void, F const volatile&, int>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<int, F               &, int>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<int, F               &, int>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable_r<int, F const         &, int>::value, "");
static_assert( bksge::is_nothrow_invocable_r<int, F       volatile&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, F const volatile&, int>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<long, F               &, int>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<long, F               &, int>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable_r<long, F const         &, int>::value, "");
static_assert( bksge::is_nothrow_invocable_r<long, F       volatile&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long, F const volatile&, int>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<short, F               &, int>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<short, F               &, int>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable_r<short, F const         &, int>::value, "");
static_assert( bksge::is_nothrow_invocable_r<short, F       volatile&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short, F const volatile&, int>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<char, F               &, int>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<char, F               &, int>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable_r<char, F const         &, int>::value, "");
static_assert( bksge::is_nothrow_invocable_r<char, F       volatile&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char, F const volatile&, int>::value, "");

static_assert(!bksge::is_nothrow_invocable_r<int&, F               &&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int&, F const         &&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int&, F       volatile&&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int&, F const volatile&&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F               &&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F const         &&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F       volatile&&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F const volatile&&, int>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<short&, F               &&, int>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<short&, F               &&, int>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable_r<short&, F const         &&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short&, F       volatile&&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short&, F const volatile&&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F               &&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F const         &&, int>::value, "");
static_assert( bksge::is_nothrow_invocable_r<char&, F       volatile&&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F const volatile&&, int>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<void, F               &&, int>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<void, F               &&, int>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable_r<void, F const         &&, int>::value, "");
static_assert( bksge::is_nothrow_invocable_r<void, F       volatile&&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<void, F const volatile&&, int>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<int, F               &&, int>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<int, F               &&, int>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable_r<int, F const         &&, int>::value, "");
static_assert( bksge::is_nothrow_invocable_r<int, F       volatile&&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, F const volatile&&, int>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<long, F               &&, int>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<long, F               &&, int>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable_r<long, F const         &&, int>::value, "");
static_assert( bksge::is_nothrow_invocable_r<long, F       volatile&&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long, F const volatile&&, int>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<short, F               &&, int>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<short, F               &&, int>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable_r<short, F const         &&, int>::value, "");
static_assert( bksge::is_nothrow_invocable_r<short, F       volatile&&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short, F const volatile&&, int>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable_r<char, F               &&, int>::value, "");
#else
static_assert( bksge::is_nothrow_invocable_r<char, F               &&, int>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable_r<char, F const         &&, int>::value, "");
static_assert( bksge::is_nothrow_invocable_r<char, F       volatile&&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char, F const volatile&&, int>::value, "");

static_assert(!bksge::is_nothrow_invocable_r<int&, F, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int&, F const, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int&, F       volatile, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int&, F const volatile, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F const, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F       volatile, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long&, F const volatile, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short&, F, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short&, F const, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short&, F       volatile, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short&, F const volatile, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F const, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F       volatile, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char&, F const volatile, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<void, F, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<void, F const, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<void, F       volatile, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<void, F const volatile, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, F, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, F const, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, F       volatile, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<int, F const volatile, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long, F, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long, F const, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long, F       volatile, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<long, F const volatile, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short, F, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short, F const, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short, F       volatile, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<short, F const volatile, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char, F, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char, F const, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char, F       volatile, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable_r<char, F const volatile, int, int>::value, "");

}	// namespace is_nothrow_invocable_r_test

}	// namespace bksge_type_traits_test

BKSGE_WARNING_POP()
