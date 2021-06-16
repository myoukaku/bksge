/**
 *	@file	unit_test_fnd_concepts_invocable.cpp
 *
 *	@brief	invocable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/invocable.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_INVOCABLE_TEST(B, ...)	\
	static_assert(B == bksge::invocable<__VA_ARGS__>, " ")
#else
#  define BKSGE_INVOCABLE_TEST(B, ...) \
	static_assert(B == bksge::invocable<__VA_ARGS__>::value, " ")
#endif

namespace bksge_concepts_test
{

namespace invocable_test
{

BKSGE_INVOCABLE_TEST(false, int);
BKSGE_INVOCABLE_TEST(true,  int());
BKSGE_INVOCABLE_TEST(true,  int(*)());
BKSGE_INVOCABLE_TEST(true,  int(&)());
BKSGE_INVOCABLE_TEST(false, int(), int);
BKSGE_INVOCABLE_TEST(false, int() const);

BKSGE_INVOCABLE_TEST(true,  int(const long*, short), long*, char);

struct A;
BKSGE_INVOCABLE_TEST(true,  int A::*, const A&);
BKSGE_INVOCABLE_TEST(false, void (A::*)(long&), const A*, long&);
BKSGE_INVOCABLE_TEST(true,  void (A::*)(long&) const, A*, long&);

struct F
{
	void operator()() const;
	void operator()(int);
};
BKSGE_INVOCABLE_TEST(true,  F);
BKSGE_INVOCABLE_TEST(true,  F, int);
BKSGE_INVOCABLE_TEST(true,  const F&);
BKSGE_INVOCABLE_TEST(false, const F&, int);

}	// namespace invocable_test

}	// namespace bksge_concepts_test

#undef BKSGE_INVOCABLE_TEST
