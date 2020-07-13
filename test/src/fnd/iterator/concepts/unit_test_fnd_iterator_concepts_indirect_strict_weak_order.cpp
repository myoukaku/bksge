/**
 *	@file	unit_test_fnd_iterator_concepts_indirect_strict_weak_order.cpp
 *
 *	@brief	indirect_strict_weak_order のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/indirect_strict_weak_order.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(B, ...)	\
	static_assert(B == bksge::indirect_strict_weak_order<__VA_ARGS__>, " ");	\
	static_assert(B == bksge::indirect_strict_weak_order_t<__VA_ARGS__>::value, " ")
#else
#  define BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(B, ...)	\
	static_assert(B == bksge::indirect_strict_weak_order_t<__VA_ARGS__>::value, " ")
#endif

namespace bksge_iterator_test
{

namespace indirect_strict_weak_order_test
{

struct S1 {};
struct S2 {};

struct P1
{
	bool operator()(S1 lhs, S1 rhs) const;
	bool operator()(S2 lhs, S2 rhs) const;
	bool operator()(S1 lhs, S2 rhs) const;
	bool operator()(S2 lhs, S1 rhs) const;
};

struct P2
{
	bool operator()(S1 lhs, S1 rhs) const;
};

struct P3
{
	bool operator()(S2 lhs, S2 rhs) const;
};

BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(true,  P1, S1*, S1*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(true,  P1, S1*, S2*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(true,  P1, S2*, S1*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(true,  P1, S2*, S2*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(true,  P2, S1*, S1*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(false, P2, S1*, S2*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(false, P2, S2*, S1*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(false, P2, S2*, S2*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(false, P3, S1*, S1*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(false, P3, S1*, S2*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(false, P3, S2*, S1*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(true,  P3, S2*, S2*);

BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(true,  P1, S1 const*, S1 const*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(true,  P1, S1 const*, S2 const*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(true,  P1, S2 const*, S1 const*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(true,  P1, S2 const*, S2 const*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(true,  P2, S1 const*, S1 const*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(false, P2, S1 const*, S2 const*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(false, P2, S2 const*, S1 const*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(false, P2, S2 const*, S2 const*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(false, P3, S1 const*, S1 const*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(false, P3, S1 const*, S2 const*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(false, P3, S2 const*, S1 const*);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(true,  P3, S2 const*, S2 const*);

BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(false, P1, S1&, S1&);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(false, P1, S1&&, S1&&);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(false, P1, S1[], S1[]);
BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(false, P1, S1[2], S1[2]);

BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST(false, P1, int*, int*);

}	// namespace indirect_strict_weak_order_test

}	// namespace bksge_iterator_test

#undef BKSGE_INDIRECT_STRICT_WEAK_ORDER_TEST
