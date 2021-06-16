/**
 *	@file	unit_test_fnd_concepts_equality_comparable.cpp
 *
 *	@brief	equality_comparable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/equality_comparable.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_EQUALITY_COMPARABLE_TEST(B, T)	\
	static_assert(B == bksge::equality_comparable<T>, "")
#else
#  define BKSGE_EQUALITY_COMPARABLE_TEST(B, T)	\
	static_assert(B == bksge::equality_comparable<T>::value, "")
#endif

namespace bksge_concepts_test
{

namespace equality_comparable_test
{

BKSGE_EQUALITY_COMPARABLE_TEST(false, void);
BKSGE_EQUALITY_COMPARABLE_TEST(true,  void*);
BKSGE_EQUALITY_COMPARABLE_TEST(true,  float);
BKSGE_EQUALITY_COMPARABLE_TEST(true,  char);
BKSGE_EQUALITY_COMPARABLE_TEST(true,  int);
BKSGE_EQUALITY_COMPARABLE_TEST(true,  int*);
BKSGE_EQUALITY_COMPARABLE_TEST(true,  int&);
BKSGE_EQUALITY_COMPARABLE_TEST(true,  int&&);
BKSGE_EQUALITY_COMPARABLE_TEST(true,  int const);
BKSGE_EQUALITY_COMPARABLE_TEST(true,  int const*);
BKSGE_EQUALITY_COMPARABLE_TEST(true,  int const&);
BKSGE_EQUALITY_COMPARABLE_TEST(true,  int const&&);
BKSGE_EQUALITY_COMPARABLE_TEST(true,  int[]);
BKSGE_EQUALITY_COMPARABLE_TEST(true,  int[2]);
BKSGE_EQUALITY_COMPARABLE_TEST(true,  int());
BKSGE_EQUALITY_COMPARABLE_TEST(true,  int(*)());
BKSGE_EQUALITY_COMPARABLE_TEST(true,  int(&)());

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

struct eq_comp
{
	friend bool operator==(const eq_comp&, const eq_comp&) = default;
};
BKSGE_EQUALITY_COMPARABLE_TEST(true,  eq_comp);

#endif

struct not_eq_comp
{
	friend bool operator==(const not_eq_comp&, const not_eq_comp&) = delete;
};
BKSGE_EQUALITY_COMPARABLE_TEST(false, not_eq_comp);

struct A
{
	friend bool operator==(const A&, const A&);
	friend bool operator!=(const A&, const A&);
};
struct B
{
	friend bool operator==(const B&, const B&) = delete;
	friend bool operator!=(const B&, const B&);
};
struct C
{
	friend bool operator==(const C&, const C&);
	friend bool operator!=(const C&, const C&) = delete;
};
BKSGE_EQUALITY_COMPARABLE_TEST(true,  A);
BKSGE_EQUALITY_COMPARABLE_TEST(false, B);
BKSGE_EQUALITY_COMPARABLE_TEST(false, C);

}	// namespace equality_comparable_test

}	// namespace bksge_concepts_test

#undef BKSGE_EQUALITY_COMPARABLE_TEST
