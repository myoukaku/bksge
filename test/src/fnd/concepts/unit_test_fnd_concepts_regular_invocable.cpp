/**
 *	@file	unit_test_fnd_concepts_regular_invocable.cpp
 *
 *	@brief	regular_invocable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/regular_invocable.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_REGULAR_INVOCABLE_TEST(B, ...)	\
	static_assert(B == bksge::regular_invocable<__VA_ARGS__>, "")
#else
#  define BKSGE_REGULAR_INVOCABLE_TEST(B, ...) \
	static_assert(B == bksge::regular_invocable<__VA_ARGS__>::value, "")
#endif

namespace bksge_concepts_test
{

namespace regular_invocable_test
{

BKSGE_REGULAR_INVOCABLE_TEST(false, int);
BKSGE_REGULAR_INVOCABLE_TEST(true,  int());
BKSGE_REGULAR_INVOCABLE_TEST(true,  int(*)());
BKSGE_REGULAR_INVOCABLE_TEST(true,  int(&)());
BKSGE_REGULAR_INVOCABLE_TEST(false, int(), int);
BKSGE_REGULAR_INVOCABLE_TEST(false, int() const);

BKSGE_REGULAR_INVOCABLE_TEST(true,  int(const long*, short), long*, char);

struct A;
BKSGE_REGULAR_INVOCABLE_TEST(true,  int A::*, const A&);
BKSGE_REGULAR_INVOCABLE_TEST(false, void (A::*)(long&), const A*, long&);
BKSGE_REGULAR_INVOCABLE_TEST(true,  void (A::*)(long&) const, A*, long&);

struct F
{
	void operator()() const;
	void operator()(int);
};
BKSGE_REGULAR_INVOCABLE_TEST(true,  F);
BKSGE_REGULAR_INVOCABLE_TEST(true,  F, int);
BKSGE_REGULAR_INVOCABLE_TEST(true,  const F&);
BKSGE_REGULAR_INVOCABLE_TEST(false, const F&, int);

}	// namespace regular_invocable_test

}	// namespace bksge_concepts_test

#undef BKSGE_REGULAR_INVOCABLE_TEST
