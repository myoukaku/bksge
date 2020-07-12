/**
 *	@file	unit_test_fnd_concepts_swappable.cpp
 *
 *	@brief	swappable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/swappable.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_SWAPPABLE_TEST(B, T)	\
	static_assert(B == bksge::swappable<T>, " ");	\
	static_assert(B == bksge::swappable_t<T>::value, " ")
#else
#  define BKSGE_SWAPPABLE_TEST(B, T)	\
	static_assert(B == bksge::swappable_t<T>::value, " ")
#endif

namespace bksge_concepts_test
{

namespace swappable_test
{

struct S { bool swapped = false; };
BKSGE_CXX14_CONSTEXPR void swap(S&, S&) { }

struct T { int i; };

union U { char c; int i; };
BKSGE_CXX14_CONSTEXPR void swap(U&, U&) { }

BKSGE_SWAPPABLE_TEST(true,  S);
BKSGE_SWAPPABLE_TEST(false, S const);
BKSGE_SWAPPABLE_TEST(true,  T);
BKSGE_SWAPPABLE_TEST(false, T const);
BKSGE_SWAPPABLE_TEST(true,  U);
BKSGE_SWAPPABLE_TEST(false, U const);

}	// namespace swappable_test

}	// namespace bksge_concepts_test

#undef BKSGE_SWAPPABLE_TEST
