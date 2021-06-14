/**
 *	@file	unit_test_fnd_concepts_common_with.cpp
 *
 *	@brief	common_with のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/common_with.hpp>
#include <bksge/fnd/type_traits/common_type.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_COMMON_WITH_TEST(B, T1, T2)	\
	static_assert(B == bksge::common_with<T1, T2>, "")
#else
#  define BKSGE_COMMON_WITH_TEST(B, T1, T2)	\
	static_assert(B == bksge::common_with<T1, T2>::value, "")
#endif

namespace bksge_concepts_test
{

namespace common_with_test
{

BKSGE_COMMON_WITH_TEST(true,  int, int);
BKSGE_COMMON_WITH_TEST(true,  int, const int);
BKSGE_COMMON_WITH_TEST(true,  int&&, const int&);
BKSGE_COMMON_WITH_TEST(true,  int&, const int&&);
BKSGE_COMMON_WITH_TEST(true,  void, void);
BKSGE_COMMON_WITH_TEST(false, int, void);
BKSGE_COMMON_WITH_TEST(false, int, int*);
BKSGE_COMMON_WITH_TEST(false, int, int());

BKSGE_COMMON_WITH_TEST(true,  int, short);
BKSGE_COMMON_WITH_TEST(true,  short, int);
#if (defined(_MSC_VER) && (_MSC_VER < 1920))
BKSGE_COMMON_WITH_TEST(false, void*, const int*);	// TODO
#else
BKSGE_COMMON_WITH_TEST(true,  void*, const int*);
#endif

struct A { A(int) { } };
BKSGE_COMMON_WITH_TEST(true,  A, int);

struct B { };
BKSGE_COMMON_WITH_TEST(false, A, B);

struct C { C(const A&) { } };
BKSGE_COMMON_WITH_TEST(true,  A, C);
BKSGE_COMMON_WITH_TEST(true,  A, const C);
BKSGE_COMMON_WITH_TEST(true,  const A, C);
BKSGE_COMMON_WITH_TEST(true,  const A, const C);

struct D;
struct E { E(const D&) { } };
struct D { D(const E&) { } };
BKSGE_COMMON_WITH_TEST(false, D, E); // ambiguous conversion

struct F { };
struct G { };
struct H {
	H(const F&) { }
	H(const G&) { }
};

}	// namespace common_with_test

}	// namespace bksge_concepts_test

namespace bksge
{

template<>
struct common_type<
	bksge_concepts_test::common_with_test::F,
	bksge_concepts_test::common_with_test::G
>
{
	using type = bksge_concepts_test::common_with_test::H;
};

template<>
struct common_type<
	bksge_concepts_test::common_with_test::G,
	bksge_concepts_test::common_with_test::F
>
{
	using type = bksge_concepts_test::common_with_test::H;
};

}	// namespace bksge

namespace bksge_concepts_test
{

namespace common_with_test
{

BKSGE_COMMON_WITH_TEST(true,  F, G);
BKSGE_COMMON_WITH_TEST(true,  F, const G);
BKSGE_COMMON_WITH_TEST(true,  const F, G);
BKSGE_COMMON_WITH_TEST(true,  const F, const G);

struct Base { };
struct Derived : Base { };
BKSGE_COMMON_WITH_TEST(true,  Derived, Base);
#if (defined(_MSC_VER) && (_MSC_VER < 1920))
BKSGE_COMMON_WITH_TEST(false, Derived*, Base*);	// TODO
#else
BKSGE_COMMON_WITH_TEST(true,  Derived*, Base*);
#endif

}	// namespace common_with_test

}	// namespace bksge_concepts_test

#undef BKSGE_COMMON_WITH_TEST
