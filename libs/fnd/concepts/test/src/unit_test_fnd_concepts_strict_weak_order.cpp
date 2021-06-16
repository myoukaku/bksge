/**
 *	@file	unit_test_fnd_concepts_strict_weak_order.cpp
 *
 *	@brief	strict_weak_order のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/strict_weak_order.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_STRICT_WEAK_ORDER_TEST(B, ...)	\
	static_assert(B == bksge::strict_weak_order<__VA_ARGS__>, "")
#else
#  define BKSGE_STRICT_WEAK_ORDER_TEST(B, ...) \
	static_assert(B == bksge::strict_weak_order<__VA_ARGS__>::value, "")
#endif

namespace bksge_concepts_test
{

namespace strict_weak_order_test
{

BKSGE_STRICT_WEAK_ORDER_TEST(false, bool, void, void);
BKSGE_STRICT_WEAK_ORDER_TEST(false, bool(), void, void);
BKSGE_STRICT_WEAK_ORDER_TEST(false, bool(*)(), void, void);
BKSGE_STRICT_WEAK_ORDER_TEST(false, bool(&)(int, int), void, void);
BKSGE_STRICT_WEAK_ORDER_TEST(false, bool(), int, int);
BKSGE_STRICT_WEAK_ORDER_TEST(false, bool() const, int, int);

BKSGE_STRICT_WEAK_ORDER_TEST(true,  bool(*)(int, int), short, long);
BKSGE_STRICT_WEAK_ORDER_TEST(true,  bool(&)(const void*, const void*), char[2], int*);

BKSGE_STRICT_WEAK_ORDER_TEST(false, bool& (const long*, short), long*, char);

struct A;
BKSGE_STRICT_WEAK_ORDER_TEST(false, int A::*, const A&, const A&);
BKSGE_STRICT_WEAK_ORDER_TEST(false, void (A::*)(long&), const A*, long&);
BKSGE_STRICT_WEAK_ORDER_TEST(false, void (A::*)(long&) const, A*, long&);
BKSGE_STRICT_WEAK_ORDER_TEST(true,  long (A::*)(A*) const, A*, A*);

struct F
{
	void operator()(long, long) const;
	bool& operator()(int, const int&) const;
};
BKSGE_STRICT_WEAK_ORDER_TEST(false, F, long, long);
BKSGE_STRICT_WEAK_ORDER_TEST(true,  F&, int, int);
BKSGE_STRICT_WEAK_ORDER_TEST(true,  const F&, const int, const int);

}	// namespace strict_weak_order_test

}	// namespace bksge_concepts_test

#undef BKSGE_STRICT_WEAK_ORDER_TEST
