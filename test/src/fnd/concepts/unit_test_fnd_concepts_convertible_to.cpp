/**
 *	@file	unit_test_fnd_concepts_convertible_to.cpp
 *
 *	@brief	convertible_to のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_CONVERTIBLE_TO_TEST(B, T1, T2)	\
	static_assert(B == bksge::convertible_to<T1, T2>, "convertible_to");	\
	static_assert(B == bksge::convertible_to_t<T1, T2>::value, "convertible_to_t")
#else
#  define BKSGE_CONVERTIBLE_TO_TEST(B, T1, T2)	\
	static_assert(B == bksge::convertible_to_t<T1, T2>::value, "convertible_to_t")
#endif

namespace bksge_concepts_test
{

namespace convertible_to_test
{

BKSGE_CONVERTIBLE_TO_TEST(true,  int, int);
BKSGE_CONVERTIBLE_TO_TEST(true,  int&, int);
BKSGE_CONVERTIBLE_TO_TEST(false, int, int&);
BKSGE_CONVERTIBLE_TO_TEST(true,  int, const int&);
BKSGE_CONVERTIBLE_TO_TEST(false, int&&, int&);
BKSGE_CONVERTIBLE_TO_TEST(true,  int&&, const int&);
BKSGE_CONVERTIBLE_TO_TEST(true,  const int, int);
BKSGE_CONVERTIBLE_TO_TEST(false, const int, int&);
BKSGE_CONVERTIBLE_TO_TEST(true,  const int, const int);
BKSGE_CONVERTIBLE_TO_TEST(true,  const int, const int&);

BKSGE_CONVERTIBLE_TO_TEST(true,  int, float);
BKSGE_CONVERTIBLE_TO_TEST(false, int, float&);
BKSGE_CONVERTIBLE_TO_TEST(false, int, int*);
BKSGE_CONVERTIBLE_TO_TEST(true,  int*, void*);
BKSGE_CONVERTIBLE_TO_TEST(true,  int*, const void*);
BKSGE_CONVERTIBLE_TO_TEST(false, const int*, void*);
BKSGE_CONVERTIBLE_TO_TEST(false, int, void);

struct A { };
BKSGE_CONVERTIBLE_TO_TEST(true,  A, A);
BKSGE_CONVERTIBLE_TO_TEST(true,  A, const A);
BKSGE_CONVERTIBLE_TO_TEST(true,  A const, const A);
BKSGE_CONVERTIBLE_TO_TEST(false, volatile A, const A);
BKSGE_CONVERTIBLE_TO_TEST(false, volatile A, const volatile A&);
BKSGE_CONVERTIBLE_TO_TEST(true,  volatile A&, const volatile A&);

struct B : A { };
BKSGE_CONVERTIBLE_TO_TEST(false, A, B);
BKSGE_CONVERTIBLE_TO_TEST(true,  B, A);
BKSGE_CONVERTIBLE_TO_TEST(true,  const B, A);
BKSGE_CONVERTIBLE_TO_TEST(true,  B, const A);
BKSGE_CONVERTIBLE_TO_TEST(true,  B, const A&);
BKSGE_CONVERTIBLE_TO_TEST(false, volatile B, const A);
BKSGE_CONVERTIBLE_TO_TEST(false, volatile B, const A&);

struct C : private A { };
BKSGE_CONVERTIBLE_TO_TEST(false, A, C);
BKSGE_CONVERTIBLE_TO_TEST(false, C, A);

struct D : A { };
struct E : B, D { };
BKSGE_CONVERTIBLE_TO_TEST(false, A, E);
BKSGE_CONVERTIBLE_TO_TEST(false, E, A);

struct F
{
	F(A) { }
	F(C&&) { }
};
BKSGE_CONVERTIBLE_TO_TEST(true,  A, F);
BKSGE_CONVERTIBLE_TO_TEST(true,  const A, F);
BKSGE_CONVERTIBLE_TO_TEST(true,  C, F);
BKSGE_CONVERTIBLE_TO_TEST(false, C&, F);
BKSGE_CONVERTIBLE_TO_TEST(false, const C, F);

struct G
{
	operator int() const;
};
BKSGE_CONVERTIBLE_TO_TEST(true,  G, int);
BKSGE_CONVERTIBLE_TO_TEST(false, int, G);
BKSGE_CONVERTIBLE_TO_TEST(true,  G&, int);
BKSGE_CONVERTIBLE_TO_TEST(true,  G&&, int);
BKSGE_CONVERTIBLE_TO_TEST(false, G*, int);
BKSGE_CONVERTIBLE_TO_TEST(false, G, int&);

struct H
{
	explicit operator int() const;
};
BKSGE_CONVERTIBLE_TO_TEST(false, H, int);
BKSGE_CONVERTIBLE_TO_TEST(false, int, H);
BKSGE_CONVERTIBLE_TO_TEST(false, H&, int);
BKSGE_CONVERTIBLE_TO_TEST(false, H&&, int);
BKSGE_CONVERTIBLE_TO_TEST(false, H*, int);

// Difference between std::is_convertible and std::convertible_to
// https://stackoverflow.com/questions/62644070/differences-between-stdis-convertible-and-stdconvertible-to-in-practice
struct From;
struct To {
	explicit To(From) = delete;
};
struct From {
	operator To();
};
BKSGE_CONVERTIBLE_TO_TEST(false, From, To);

}	// namespace convertible_to_test

}	// namespace bksge_concepts_test

#undef BKSGE_CONVERTIBLE_TO_TEST
