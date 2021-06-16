/**
 *	@file	unit_test_fnd_concepts_totally_ordered.cpp
 *
 *	@brief	totally_ordered のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/totally_ordered.hpp>
#include <bksge/fnd/config.hpp>

#if BKSGE_HAS_INCLUDE(<compare>) && (BKSGE_CXX_STANDARD >= 20)
#include <compare>
#endif

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_TOTALLY_ORDERED_TEST(B, T)	\
	static_assert(B == bksge::totally_ordered<T>, "")
#else
#  define BKSGE_TOTALLY_ORDERED_TEST(B, T)	\
	static_assert(B == bksge::totally_ordered<T>::value, "")
#endif

namespace bksge_concepts_test
{

namespace totally_ordered_test
{

BKSGE_TOTALLY_ORDERED_TEST(false, void);
BKSGE_TOTALLY_ORDERED_TEST(true,  void*);
BKSGE_TOTALLY_ORDERED_TEST(true,  float);
BKSGE_TOTALLY_ORDERED_TEST(true,  char);
BKSGE_TOTALLY_ORDERED_TEST(true,  int);
BKSGE_TOTALLY_ORDERED_TEST(true,  int*);
BKSGE_TOTALLY_ORDERED_TEST(true,  int&);
BKSGE_TOTALLY_ORDERED_TEST(true,  int&&);
BKSGE_TOTALLY_ORDERED_TEST(true,  int const);
BKSGE_TOTALLY_ORDERED_TEST(true,  int const*);
BKSGE_TOTALLY_ORDERED_TEST(true,  int const&);
BKSGE_TOTALLY_ORDERED_TEST(true,  int const&&);
BKSGE_TOTALLY_ORDERED_TEST(true,  int[]);
BKSGE_TOTALLY_ORDERED_TEST(true,  int[2]);
BKSGE_TOTALLY_ORDERED_TEST(true,  int());
BKSGE_TOTALLY_ORDERED_TEST(true,  int(*)());
BKSGE_TOTALLY_ORDERED_TEST(true,  int(&)());

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON) && BKSGE_HAS_INCLUDE(<compare>)

struct ordered
{
	friend auto operator<=>(const ordered&, const ordered&) = default;
};

BKSGE_TOTALLY_ORDERED_TEST(true,  ordered);

#endif

struct A
{
	bool operator==(const A&) const;
	bool operator!=(const A&) const;
	bool operator< (const A&) const;
	bool operator> (const A&) const;
	bool operator<=(const A&) const;
	bool operator>=(const A&) const;
};
struct B
{
	bool operator==(const B&) const;
	bool operator!=(const B&) const = delete;
	bool operator< (const B&) const;
	bool operator> (const B&) const;
	bool operator<=(const B&) const;
	bool operator>=(const B&) const;
};
struct C
{
	bool operator==(const C&) const;
	bool operator!=(const C&) const;
	void operator< (const C&) const;
	bool operator> (const C&) const;
	bool operator<=(const C&) const;
	bool operator>=(const C&) const;
};
struct D
{
	bool operator==(const D&) const;
	bool operator!=(const D&) const;
	bool operator< (const D&) const;
	bool operator> (const D&) const = delete;
	bool operator<=(const D&) const;
	bool operator>=(const D&) const;
};
struct E
{
	bool operator==(const E&) const;
	bool operator!=(const E&) const;
	bool operator< (const E&) const;
	bool operator> (const E&) const;
	bool operator<=(const E&) const = delete;
	bool operator>=(const E&) const;
};
struct F
{
	bool operator==(const F&) const;
	bool operator!=(const F&) const;
	bool operator< (const F&) const;
	bool operator> (const F&) const;
	bool operator<=(const F&) const;
	void operator>=(const F&) const;
};

BKSGE_TOTALLY_ORDERED_TEST(true,  A);
BKSGE_TOTALLY_ORDERED_TEST(false, B);
BKSGE_TOTALLY_ORDERED_TEST(false, C);
BKSGE_TOTALLY_ORDERED_TEST(false, D);
BKSGE_TOTALLY_ORDERED_TEST(false, E);
BKSGE_TOTALLY_ORDERED_TEST(false, F);

}	// namespace totally_ordered_test

}	// namespace bksge_concepts_test

#undef BKSGE_TOTALLY_ORDERED_TEST
