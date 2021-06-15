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

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_NOTHROW_INVOCABLE_TEST(b, ...)	\
	static_assert(bksge::is_nothrow_invocable_v<__VA_ARGS__>      == b, "");	\
	static_assert(bksge::is_nothrow_invocable<__VA_ARGS__>::value == b, "");	\
	static_assert(bksge::is_nothrow_invocable<__VA_ARGS__>()      == b, "")

#else

#define BKSGE_IS_NOTHROW_INVOCABLE_TEST(b, ...)	\
	static_assert(bksge::is_nothrow_invocable<__VA_ARGS__>::value == b, "");	\
	static_assert(bksge::is_nothrow_invocable<__VA_ARGS__>()      == b, "")

#endif

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_CLANG("-Wundefined-internal")

namespace bksge_type_traits_test
{

namespace is_nothrow_invocable_test
{

using func_type_v0 = void(*)();

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_v0);
#else
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_v0);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_v0, int);

using func_type_i0 = int(*)();

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_i0);
#else
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_i0);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_i0, int);

using func_type_l0 = int&(*)();

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_l0);
#else
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_l0);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_l0, int);

using func_type_ii = int(*)(int);

BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_ii);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_ii, int);
#else
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_ii, int);
#endif

using func_type_il = int(*)(int&);

BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_il);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_il, int);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_il, int&);
#else
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_il, int&);
#endif

using func_type_ir = int(*)(int&&);

BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_ir);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_ir, int);
#else
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_ir, int);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_ir, int&);

#if defined(BKSGE_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)

using func_type_v0_nt = void(*)() noexcept;

BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_v0_nt);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_v0_nt, int);

using func_type_i0_nt = int(*)() noexcept;

BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_i0_nt);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_i0_nt, int);

using func_type_l0_nt = int&(*)() noexcept;

BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_l0_nt);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_l0_nt, int);

using func_type_ii_nt = int(*)(int) noexcept;

BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_ii_nt);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_ii_nt, int);

using func_type_il_nt = int(*)(int&) noexcept;

BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_il_nt);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_il_nt, int);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_il_nt, int&);

using func_type_ir_nt = int(*)(int&&) noexcept;

BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_ir_nt);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_ir_nt, int);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, func_type_ir_nt, int&);

#endif

struct X {};
using mem_type = int X::*;

BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, mem_type);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, mem_type, int);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, mem_type, int&);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  mem_type, X&);

using memfun_type = int (X::*)();

BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type, int);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type, int&);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type, X&);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type, X*);
#else
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  memfun_type, X&);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  memfun_type, X*);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type, X&, int);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type, X*, int);

#if defined(BKSGE_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)

using memfun_type_nt = int (X::*)() noexcept;

BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type_nt);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type_nt, int);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type_nt, int&);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  memfun_type_nt, X&);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  memfun_type_nt, X*);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type_nt, X&, int);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type_nt, X*, int);

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
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F               );
#else
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  F               );
#endif
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  F const         );
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F       volatile);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F const volatile);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F               &);
#else
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  F               &);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  F const         &);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F       volatile&);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F const volatile&);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F               &&);
#else
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  F               &&);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  F const         &&);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F       volatile&&);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F const volatile&&);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F               *);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F const         *);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F       volatile*);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F const volatile*);

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F, int);
#else
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  F, int);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F const, int);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  F       volatile, int);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F const volatile, int);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F               &, int);
#else
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  F               &, int);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F const         &, int);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  F       volatile&, int);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F const volatile&, int);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F, int&);
#else
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  F, int&);
#endif
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F const, int&);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  F       volatile, int&);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F const volatile, int&);

BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  F, int, int);
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F const, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F       volatile, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F const volatile, int, int);
#else
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  F const, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  F       volatile, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(true,  F const volatile, int, int);
#endif

BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F, int, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F const, int, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F       volatile, int, int, int);
BKSGE_IS_NOTHROW_INVOCABLE_TEST(false, F const volatile, int, int, int);

}	// namespace is_nothrow_invocable_test

}	// namespace bksge_type_traits_test

BKSGE_WARNING_POP()

#undef BKSGE_IS_NOTHROW_INVOCABLE_TEST
