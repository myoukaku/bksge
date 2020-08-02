/**
 *	@file	unit_test_fnd_iterator_concepts_indirectly_regular_unary_invocable.cpp
 *
 *	@brief	indirectly_regular_unary_invocable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/indirectly_regular_unary_invocable.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(B, ...)	\
	static_assert(B == bksge::indirectly_regular_unary_invocable<__VA_ARGS__>, "")
#else
#  define BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(B, ...)	\
	static_assert(B == bksge::indirectly_regular_unary_invocable<__VA_ARGS__>::value, "")
#endif

namespace bksge_iterator_test
{

namespace indirectly_regular_unary_invocable_test
{

struct Pred1
{
	bool operator()(int) const;
};
struct Pred2
{
	void operator()(int const&) const;
};
struct Pred3
{
	bool operator()(int, int) const;
	bool operator()() const;
};
struct Pred4
{
	bool operator()(int&) const;
};

BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(true,  Pred1, int*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(true,  Pred1, int const*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(true,  Pred2, int*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(true,  Pred2, int const*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(false, Pred3, int*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(false, Pred3, int const*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(true,  Pred4, int*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(false, Pred4, int const*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(true,  Pred1, short*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(true,  Pred2, short*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(false, Pred3, short*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(false, Pred1, void*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(false, Pred2, void*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(false, Pred3, void*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(false, int, int*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(false, int(), int*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(false, int(int), int*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(false, int(int,int), int*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(false, int(*)(), int*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(true,  int(*)(int), int*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(false, int(*)(int,int), int*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(false, int(&)(), int*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(true,  int(&)(int), int*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(false, int(&)(int, int), int*);

struct A;
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(true,  int A::*, A*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(true,  int A::*, A const*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(true,  void (A::*)(),           A*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(true,  void (A::*)() const,     A*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(false, void (A::*)(long),       A*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(false, void (A::*)(long) const, A*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(false, void (A::*)(),           A const*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(true,  void (A::*)() const,     A const*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(false, void (A::*)(long),       A const*);
BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST(false, void (A::*)(long) const, A const*);

}	// namespace indirectly_regular_unary_invocable_test

}	// namespace bksge_iterator_test

#undef BKSGE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_TEST
