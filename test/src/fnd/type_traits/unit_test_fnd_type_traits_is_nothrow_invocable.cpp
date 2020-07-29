/**
 *	@file	unit_test_fnd_type_traits_is_nothrow_invocable.cpp
 *
 *	@brief	is_nothrow_invocable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_nothrow_invocable.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_CLANG("-Wundefined-internal")

namespace bksge_type_traits_test
{

namespace is_nothrow_invocable_test
{

using func_type_v0 = void(*)();

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable<func_type_v0>::value, "");
#else
static_assert( bksge::is_nothrow_invocable<func_type_v0>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable<func_type_v0, int>::value, "");

using func_type_i0 = int(*)();

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable<func_type_i0>::value, "");
#else
static_assert( bksge::is_nothrow_invocable<func_type_i0>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable<func_type_i0, int>::value, "");

using func_type_l0 = int&(*)();

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable<func_type_l0>::value, "");
#else
static_assert( bksge::is_nothrow_invocable<func_type_l0>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable<func_type_l0, int>::value, "");

using func_type_ii = int(*)(int);

static_assert(!bksge::is_nothrow_invocable<func_type_ii>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable<func_type_ii, int>::value, "");
#else
static_assert( bksge::is_nothrow_invocable<func_type_ii, int>::value, "");
#endif

using func_type_il = int(*)(int&);

static_assert(!bksge::is_nothrow_invocable<func_type_il>::value, "");
static_assert(!bksge::is_nothrow_invocable<func_type_il, int>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable<func_type_il, int&>::value, "");
#else
static_assert( bksge::is_nothrow_invocable<func_type_il, int&>::value, "");
#endif

using func_type_ir = int(*)(int&&);

static_assert(!bksge::is_nothrow_invocable<func_type_ir>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable<func_type_ir, int>::value, "");
#else
static_assert( bksge::is_nothrow_invocable<func_type_ir, int>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable<func_type_ir, int&>::value, "");

#if defined(BKSGE_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)

using func_type_v0_nt = void(*)() noexcept;

static_assert( bksge::is_nothrow_invocable<func_type_v0_nt>::value, "");
static_assert(!bksge::is_nothrow_invocable<func_type_v0_nt, int>::value, "");

using func_type_i0_nt = int(*)() noexcept;

static_assert( bksge::is_nothrow_invocable<func_type_i0_nt>::value, "");
static_assert(!bksge::is_nothrow_invocable<func_type_i0_nt, int>::value, "");

using func_type_l0_nt = int&(*)() noexcept;

static_assert( bksge::is_nothrow_invocable<func_type_l0_nt>::value, "");
static_assert(!bksge::is_nothrow_invocable<func_type_l0_nt, int>::value, "");

using func_type_ii_nt = int(*)(int) noexcept;

static_assert(!bksge::is_nothrow_invocable<func_type_ii_nt>::value, "");
static_assert( bksge::is_nothrow_invocable<func_type_ii_nt, int>::value, "");

using func_type_il_nt = int(*)(int&) noexcept;

static_assert(!bksge::is_nothrow_invocable<func_type_il_nt>::value, "");
static_assert(!bksge::is_nothrow_invocable<func_type_il_nt, int>::value, "");
static_assert( bksge::is_nothrow_invocable<func_type_il_nt, int&>::value, "");

using func_type_ir_nt = int(*)(int&&) noexcept;

static_assert(!bksge::is_nothrow_invocable<func_type_ir_nt>::value, "");
static_assert( bksge::is_nothrow_invocable<func_type_ir_nt, int>::value, "");
static_assert(!bksge::is_nothrow_invocable<func_type_ir_nt, int&>::value, "");

#endif

struct X {};
using mem_type = int X::*;

static_assert(!bksge::is_nothrow_invocable<mem_type>::value, "");
static_assert(!bksge::is_nothrow_invocable<mem_type, int>::value, "");
static_assert(!bksge::is_nothrow_invocable<mem_type, int&>::value, "");
static_assert( bksge::is_nothrow_invocable<mem_type, X&>::value, "");

using memfun_type = int (X::*)();

static_assert(!bksge::is_nothrow_invocable<memfun_type>::value, "");
static_assert(!bksge::is_nothrow_invocable<memfun_type, int>::value, "");
static_assert(!bksge::is_nothrow_invocable<memfun_type, int&>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable<memfun_type, X&>::value, "");
static_assert(!bksge::is_nothrow_invocable<memfun_type, X*>::value, "");
#else
static_assert( bksge::is_nothrow_invocable<memfun_type, X&>::value, "");
static_assert( bksge::is_nothrow_invocable<memfun_type, X*>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable<memfun_type, X&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable<memfun_type, X*, int>::value, "");

#if defined(BKSGE_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)

using memfun_type_nt = int (X::*)() noexcept;

static_assert(!bksge::is_nothrow_invocable<memfun_type_nt>::value, "");
static_assert(!bksge::is_nothrow_invocable<memfun_type_nt, int>::value, "");
static_assert(!bksge::is_nothrow_invocable<memfun_type_nt, int&>::value, "");
static_assert( bksge::is_nothrow_invocable<memfun_type_nt, X&>::value, "");
static_assert( bksge::is_nothrow_invocable<memfun_type_nt, X*>::value, "");
static_assert(!bksge::is_nothrow_invocable<memfun_type_nt, X&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable<memfun_type_nt, X*, int>::value, "");

#endif

struct F
{
	int&    operator()();
	long&   operator()() const BKSGE_NOEXCEPT;
	short&  operator()(int);
	char&   operator()(int) volatile BKSGE_NOEXCEPT;
	float&  operator()(int, int) BKSGE_NOEXCEPT;
	double& operator()(int, int) const volatile;
};

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable<F               >::value, "");
#else
static_assert( bksge::is_nothrow_invocable<F               >::value, "");
#endif
static_assert( bksge::is_nothrow_invocable<F const         >::value, "");
static_assert(!bksge::is_nothrow_invocable<F       volatile>::value, "");
static_assert(!bksge::is_nothrow_invocable<F const volatile>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable<F               &>::value, "");
#else
static_assert( bksge::is_nothrow_invocable<F               &>::value, "");
#endif
static_assert( bksge::is_nothrow_invocable<F const         &>::value, "");
static_assert(!bksge::is_nothrow_invocable<F       volatile&>::value, "");
static_assert(!bksge::is_nothrow_invocable<F const volatile&>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable<F               &&>::value, "");
#else
static_assert( bksge::is_nothrow_invocable<F               &&>::value, "");
#endif
static_assert( bksge::is_nothrow_invocable<F const         &&>::value, "");
static_assert(!bksge::is_nothrow_invocable<F       volatile&&>::value, "");
static_assert(!bksge::is_nothrow_invocable<F const volatile&&>::value, "");
static_assert(!bksge::is_nothrow_invocable<F               *>::value, "");
static_assert(!bksge::is_nothrow_invocable<F const         *>::value, "");
static_assert(!bksge::is_nothrow_invocable<F       volatile*>::value, "");
static_assert(!bksge::is_nothrow_invocable<F const volatile*>::value, "");

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable<F, int>::value, "");
#else
static_assert( bksge::is_nothrow_invocable<F, int>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable<F const, int>::value, "");
static_assert( bksge::is_nothrow_invocable<F       volatile, int>::value, "");
static_assert(!bksge::is_nothrow_invocable<F const volatile, int>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable<F               &, int>::value, "");
#else
static_assert( bksge::is_nothrow_invocable<F               &, int>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable<F const         &, int>::value, "");
static_assert( bksge::is_nothrow_invocable<F       volatile&, int>::value, "");
static_assert(!bksge::is_nothrow_invocable<F const volatile&, int>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable<F, int&>::value, "");
#else
static_assert( bksge::is_nothrow_invocable<F, int&>::value, "");
#endif
static_assert(!bksge::is_nothrow_invocable<F const, int&>::value, "");
static_assert( bksge::is_nothrow_invocable<F       volatile, int&>::value, "");
static_assert(!bksge::is_nothrow_invocable<F const volatile, int&>::value, "");

static_assert( bksge::is_nothrow_invocable<F, int, int>::value, "");
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
static_assert(!bksge::is_nothrow_invocable<F const, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable<F       volatile, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable<F const volatile, int, int>::value, "");
#else
static_assert( bksge::is_nothrow_invocable<F const, int, int>::value, "");
static_assert( bksge::is_nothrow_invocable<F       volatile, int, int>::value, "");
static_assert( bksge::is_nothrow_invocable<F const volatile, int, int>::value, "");
#endif

static_assert(!bksge::is_nothrow_invocable<F, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable<F const, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable<F       volatile, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_invocable<F const volatile, int, int, int>::value, "");

}	// namespace is_nothrow_invocable_test

}	// namespace bksge_type_traits_test

BKSGE_WARNING_POP()
