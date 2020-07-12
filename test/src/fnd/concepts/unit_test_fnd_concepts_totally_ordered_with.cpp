/**
 *	@file	unit_test_fnd_concepts_totally_ordered_with.cpp
 *
 *	@brief	totally_ordered_with のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/totally_ordered_with.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_TOTALLY_ORDERED_WITH_TEST(B, ...)	\
	static_assert(B == bksge::totally_ordered_with<__VA_ARGS__>, " ");	\
	static_assert(B == bksge::totally_ordered_with_t<__VA_ARGS__>::value, " ")
#else
#  define BKSGE_TOTALLY_ORDERED_WITH_TEST(B, ...) \
	static_assert(B == bksge::totally_ordered_with_t<__VA_ARGS__>::value, " ")
#endif

namespace bksge_concepts_test
{

namespace totally_ordered_with_test
{

BKSGE_TOTALLY_ORDERED_WITH_TEST(true,  int, int);
BKSGE_TOTALLY_ORDERED_WITH_TEST(true,  int, char);
BKSGE_TOTALLY_ORDERED_WITH_TEST(true,  int, float);
BKSGE_TOTALLY_ORDERED_WITH_TEST(false, int, void);
BKSGE_TOTALLY_ORDERED_WITH_TEST(false, int, int*);
BKSGE_TOTALLY_ORDERED_WITH_TEST(true,  int, int&);
BKSGE_TOTALLY_ORDERED_WITH_TEST(true,  int, int&&);
BKSGE_TOTALLY_ORDERED_WITH_TEST(false, int, int[]);
BKSGE_TOTALLY_ORDERED_WITH_TEST(false, int, int[2]);
BKSGE_TOTALLY_ORDERED_WITH_TEST(false, int, int());
BKSGE_TOTALLY_ORDERED_WITH_TEST(false, int, int(*)());
BKSGE_TOTALLY_ORDERED_WITH_TEST(false, int, int(&)());

BKSGE_TOTALLY_ORDERED_WITH_TEST(true,  int, int const);
BKSGE_TOTALLY_ORDERED_WITH_TEST(true,  int const, int const);

BKSGE_TOTALLY_ORDERED_WITH_TEST(true,  int*, int*);
BKSGE_TOTALLY_ORDERED_WITH_TEST(false, int*, float*);
BKSGE_TOTALLY_ORDERED_WITH_TEST(true,  int*, void*);

}	// namespace totally_ordered_with_test

}	// namespace bksge_concepts_test

#undef BKSGE_TOTALLY_ORDERED_WITH_TEST
