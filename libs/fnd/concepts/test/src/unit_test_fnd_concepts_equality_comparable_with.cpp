/**
 *	@file	unit_test_fnd_concepts_equality_comparable_with.cpp
 *
 *	@brief	equality_comparable_with のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/equality_comparable_with.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_EQUALITY_COMPARABLE_WITH_TEST(B, T1, T2)	\
	static_assert(B == bksge::equality_comparable_with<T1, T2>, "")
#else
#  define BKSGE_EQUALITY_COMPARABLE_WITH_TEST(B, T1, T2)	\
	static_assert(B == bksge::equality_comparable_with<T1, T2>::value, "")
#endif

namespace bksge_concepts_test
{

namespace equality_comparable_with_test
{

BKSGE_EQUALITY_COMPARABLE_WITH_TEST(true,  int, int);
BKSGE_EQUALITY_COMPARABLE_WITH_TEST(true,  int, char);
BKSGE_EQUALITY_COMPARABLE_WITH_TEST(true,  int, float);
BKSGE_EQUALITY_COMPARABLE_WITH_TEST(false, int, void);
BKSGE_EQUALITY_COMPARABLE_WITH_TEST(false, int, int*);
BKSGE_EQUALITY_COMPARABLE_WITH_TEST(true,  int, int&);
BKSGE_EQUALITY_COMPARABLE_WITH_TEST(true,  int, int&&);
BKSGE_EQUALITY_COMPARABLE_WITH_TEST(false, int, int[]);
BKSGE_EQUALITY_COMPARABLE_WITH_TEST(false, int, int[2]);
BKSGE_EQUALITY_COMPARABLE_WITH_TEST(false, int, int());
BKSGE_EQUALITY_COMPARABLE_WITH_TEST(false, int, int(*)());
BKSGE_EQUALITY_COMPARABLE_WITH_TEST(false, int, int(&)());

BKSGE_EQUALITY_COMPARABLE_WITH_TEST(true,  int, int const);
BKSGE_EQUALITY_COMPARABLE_WITH_TEST(true,  int const, int const);

BKSGE_EQUALITY_COMPARABLE_WITH_TEST(true,  int*, int*);
BKSGE_EQUALITY_COMPARABLE_WITH_TEST(false, int*, float*);
BKSGE_EQUALITY_COMPARABLE_WITH_TEST(true,  int*, void*);

}	// namespace equality_comparable_with_test

}	// namespace bksge_concepts_test

#undef BKSGE_EQUALITY_COMPARABLE_WITH_TEST
