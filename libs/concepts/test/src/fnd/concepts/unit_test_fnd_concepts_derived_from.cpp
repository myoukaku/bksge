/**
 *	@file	unit_test_fnd_concepts_derived_from.cpp
 *
 *	@brief	derived_from のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/derived_from.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_DERIVED_FROM_TEST(B, T1, T2)	\
	static_assert(B == bksge::derived_from<T1, T2>, "")
#else
#  define BKSGE_DERIVED_FROM_TEST(B, T1, T2)	\
	static_assert(B == bksge::derived_from<T1, T2>::value, "")
#endif

namespace bksge_concepts_test
{

namespace derived_from_test
{

BKSGE_DERIVED_FROM_TEST(false, int, int);
BKSGE_DERIVED_FROM_TEST(false, int&, int);
BKSGE_DERIVED_FROM_TEST(false, int, int&);
BKSGE_DERIVED_FROM_TEST(false, int&&, int&);
BKSGE_DERIVED_FROM_TEST(false, const int, int);
BKSGE_DERIVED_FROM_TEST(false, const int, const int);

struct A { };
BKSGE_DERIVED_FROM_TEST(true,  A,                A);
BKSGE_DERIVED_FROM_TEST(true,  A,                A const);
BKSGE_DERIVED_FROM_TEST(true,  A,                A volatile);
BKSGE_DERIVED_FROM_TEST(true,  A,                A const volatile);
BKSGE_DERIVED_FROM_TEST(true,  A const,          A);
BKSGE_DERIVED_FROM_TEST(true,  A const,          A const);
BKSGE_DERIVED_FROM_TEST(true,  A const,          A volatile);
BKSGE_DERIVED_FROM_TEST(true,  A const,          A const volatile);
BKSGE_DERIVED_FROM_TEST(true,  A       volatile, A);
BKSGE_DERIVED_FROM_TEST(true,  A       volatile, A const);
BKSGE_DERIVED_FROM_TEST(true,  A       volatile, A volatile);
BKSGE_DERIVED_FROM_TEST(true,  A       volatile, A const volatile);
BKSGE_DERIVED_FROM_TEST(true,  A const volatile, A);
BKSGE_DERIVED_FROM_TEST(true,  A const volatile, A const);
BKSGE_DERIVED_FROM_TEST(true,  A const volatile, A volatile);
BKSGE_DERIVED_FROM_TEST(true,  A const volatile, A const volatile);
BKSGE_DERIVED_FROM_TEST(false, A&, A&);

struct B : A { };
BKSGE_DERIVED_FROM_TEST(false, A, B);
BKSGE_DERIVED_FROM_TEST(true,  B, A);
BKSGE_DERIVED_FROM_TEST(true,  B const, A);
BKSGE_DERIVED_FROM_TEST(true,  B, A const);
BKSGE_DERIVED_FROM_TEST(true,  B volatile, A const);
BKSGE_DERIVED_FROM_TEST(false, A&, B&);
BKSGE_DERIVED_FROM_TEST(false, B&, A&);

struct C : private A { };
BKSGE_DERIVED_FROM_TEST(false, A, C);
BKSGE_DERIVED_FROM_TEST(false, C, A);

struct D : A { };
struct E : B, D { };
BKSGE_DERIVED_FROM_TEST(false, A, E);
BKSGE_DERIVED_FROM_TEST(false, E, A);

}	// namespace derived_from_test

}	// namespace bksge_concepts_test

#undef BKSGE_DERIVED_FROM_TEST
